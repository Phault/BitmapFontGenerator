#include "effectstreemodel.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QMimeData>
#include <effectfactory.h>
#include <QIcon>

EffectsTreeModel::EffectsTreeModel(EffectGroup &rootEffect, QObject *parent)
    : QAbstractItemModel(parent),
      mRootEffect(rootEffect),
      mGroupIcon()
{
}

QModelIndex EffectsTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    EffectGroup *group = indexToGroup(parent);

    Effect *childItem = group->effects().at(row);

    if (childItem)
        return createIndex(row, column, childItem);

    return QModelIndex();
}

QModelIndex EffectsTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    auto parent = findParent(0, &mRootEffect, index);
    return parent.internalPointer() != &mRootEffect
            ? parent
            : QModelIndex();
}

QModelIndex EffectsTreeModel::findParent(int row, EffectGroup *root, const QModelIndex &target) const
{
    const auto &children = root->constEffects();

    if (target.row() < children.length() && children.at(target.row()) == target.internalPointer())
        return createIndex(row, 0, root);

    for (int i = 0; i < children.length(); ++i)
    {
        const auto &child = children[i];
        const auto &group = dynamic_cast<EffectGroup *>(child);

        if (!group || group->effects().length() == 0)
            continue;

        auto parent = findParent(i, group, target);
        if (parent.isValid())
            return parent;
    }

    return QModelIndex();
}

int EffectsTreeModel::rowCount(const QModelIndex &parent) const
{
    EffectGroup *group = indexToGroup(parent);

    if (!group)
        return 0;

    return group->effects().count();
}

int EffectsTreeModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 1;
}

QVariant EffectsTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    Effect *effect = static_cast<Effect*>(index.internalPointer());

    switch (role)
    {
        case Qt::DisplayRole:
        case Qt::EditRole:
        case Roles::NameRole:
            return effect->name();
        case Roles::EnabledRole:
            return effect->enabled();
        case Qt::CheckStateRole:
            return effect->enabled() ? Qt::Checked : Qt::Unchecked;
        case Qt::DecorationRole:
            return indexToGroup(index) != nullptr ? mGroupIcon : QVariant();
        default:
            return QVariant();
    }
}

bool EffectsTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if (data(index, role) != value) {

        Effect *effect = static_cast<Effect*>(index.internalPointer());

        auto changedRoles = QVector<int>();

        switch (role) {
            case Qt::DisplayRole:
            case Qt::EditRole:
            case Roles::NameRole:
                effect->setName(value.toString());
                changedRoles << Roles::NameRole
                               << Qt::DisplayRole
                               << Qt::EditRole;
                break;
            case Roles::EnabledRole:
                effect->setEnabled(value.toBool());
                changedRoles << Roles::EnabledRole
                               << Qt::CheckStateRole;
                break;
            case Qt::CheckStateRole:
                effect->setEnabled(value == Qt::Checked);
                changedRoles << Roles::EnabledRole
                               << Qt::CheckStateRole;
                break;

            default:
                return false;
        }

        emit dataChanged(index, index, changedRoles);
        return true;
    }
    return false;
}

Qt::ItemFlags EffectsTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsDropEnabled;

    EffectGroup *group = indexToGroup(index);

    static Qt::ItemFlags defaultFlags = Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsDragEnabled;

    if (group)
        return defaultFlags | Qt::ItemIsDropEnabled;

    return defaultFlags | Qt::ItemNeverHasChildren;
}

QModelIndex EffectsTreeModel::addEffect(Effect &effect, const QModelIndex &parent)
{
    EffectGroup *group = indexToGroup(parent);

    if (!group)
        return QModelIndex();

    int rowIndex = rowCount(parent);
    beginInsertRows(parent, rowIndex, rowIndex);
    group->effects().append(&effect);
    endInsertRows();

    return index(rowIndex, 0, parent);
}

bool EffectsTreeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    auto last = row + count - 1;

    if (row < 0
            || row >= rowCount(parent)
            || count < 1
            || last >= rowCount(parent))
        return false;

    beginRemoveRows(parent, row, last);

    EffectGroup *group = indexToGroup(parent);

    for (auto iter = group->effects().begin() + row; iter != group->effects().begin() + last + 1; ++iter)
        delete iter.i->t();

    group->effects().erase(group->effects().begin() + row, group->effects().begin() + last + 1);

    endRemoveRows();

    return true;
}

Qt::DropActions EffectsTreeModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

EffectGroup *EffectsTreeModel::indexToGroup(const QModelIndex &index) const
{
    if (index.isValid())
    {
        Effect *effect = static_cast<Effect *>(index.internalPointer());
        return dynamic_cast<EffectGroup *>(effect);
    }

    return &mRootEffect;
}

const QIcon &EffectsTreeModel::groupIcon() const
{
    return mGroupIcon;
}

void EffectsTreeModel::setGroupIcon(const QIcon &groupIcon)
{
    mGroupIcon = groupIcon;
}

bool EffectsTreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    Q_UNUSED(column);

    if (!data || !(action & supportedDropActions()))
            return false;

    auto format = mimeTypes().at(0);

    if (!data->hasFormat(format))
        return false;

    auto group = indexToGroup(parent);

    if (!group)
        return false;

    if (row > rowCount(parent))
        row = rowCount(parent);
    if (row == -1)
        row = rowCount(parent);
    if (column == -1)
        column = 0;

    auto bytes = data->data(format);
    auto json = QJsonDocument::fromBinaryData(bytes);
    if (!json.isObject())
        return false;

    qDebug().noquote() << json.toJson(QJsonDocument::Indented);

    auto effect = EffectFactory::instance()->deserialize(json.object());

    if (!effect)
        return false;

    beginInsertRows(parent, row, row);
    group->effects().insert(row, effect);
    endInsertRows();

    return true;
}


QStringList EffectsTreeModel::mimeTypes() const
{
    return { "application/x-bitmapfontgenerator-effect" };
}

QMimeData *EffectsTreeModel::mimeData(const QModelIndexList &indexes) const
{
    if (indexes.count() <= 0)
            return nullptr;

    auto data = new QMimeData();

    auto *effect = static_cast<Effect*>(indexes[0].internalPointer());
    QJsonDocument json(effect->toJson());

    data->setData(mimeTypes().at(0), json.toBinaryData());

    return data;
}
