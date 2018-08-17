#include "effectseditor.h"
#include "effectstreemodel.h"
#include "ui_effectseditor.h"

#include <effects/effectgroup.h>

EffectsEditor::EffectsEditor(FontGenerator &generator, QWidget *parent) :
    FontEditorWidget(generator, parent),
    ui(new Ui::EffectsEditor),
    mEffects(new EffectGroup(*generator.effects())),
    mTreeModel(nullptr)
{
    ui->setupUi(this);

    generator.setEffects(mEffects);
    mTreeModel = new EffectsTreeModel(*mEffects, this);
    mTreeModel->setGroupIcon(style()->standardIcon(QStyle::SP_DirIcon));
    ui->treeView->setModel(mTreeModel);
    ui->treeView->expandAll();

    connect(mTreeModel, &QAbstractItemModel::rowsInserted, this, &EffectsEditor::itemsChanged);
    connect(mTreeModel, &QAbstractItemModel::rowsAboutToBeRemoved, this, &EffectsEditor::itemsChanged);
    connect(mTreeModel, &QAbstractItemModel::dataChanged, this, &EffectsEditor::itemDataChanged);
}

EffectsEditor::~EffectsEditor()
{
    delete ui;
    delete mTreeModel;
}

void EffectsEditor::itemsChanged(const QModelIndex &parent, int first, int last)
{
    if (parent.isValid() && !parent.data(EffectsTreeModel::EnabledRole).toBool())
        return;

    for (int i = first; i <= last; ++i)
    {
        if (mTreeModel->index(i, 0, parent).data(EffectsTreeModel::EnabledRole).toBool())
        {
            emit changed();
            return;
        }
    }
}

void EffectsEditor::itemDataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &roles)
{
    if (roles.contains(EffectsTreeModel::EnabledRole))
        emit changed();
}
