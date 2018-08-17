#ifndef EFFECTSTREEMODEL_H
#define EFFECTSTREEMODEL_H

#include <QAbstractItemModel>
#include <QIcon>

#include <effects/effect.h>
#include <effects/effectgroup.h>

class EffectsTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        EnabledRole
    };

    explicit EffectsTreeModel(EffectGroup &rootEffect, QObject *parent = nullptr);

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    QModelIndex findParent(int row, EffectGroup *root, const QModelIndex &target) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QModelIndex addEffect(Effect &effect, const QModelIndex &parent = QModelIndex());

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Qt::DropActions supportedDropActions() const override;

    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

    const QIcon &groupIcon() const;
    void setGroupIcon(const QIcon &groupIcon);

private:
    EffectGroup *indexToGroup(const QModelIndex &index) const;

    EffectGroup &mRootEffect;
    QIcon mGroupIcon;
};

#endif // EFFECTSTREEMODEL_H
