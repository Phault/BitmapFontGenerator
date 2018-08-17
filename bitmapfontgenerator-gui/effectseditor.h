#ifndef EFFECTSEDITOR_H
#define EFFECTSEDITOR_H

#include "effectstreemodel.h"
#include "fonteditorwidget.h"

#include <QWidget>

namespace Ui {
class EffectsEditor;
}

class EffectsEditor : public FontEditorWidget
{
    Q_OBJECT

public:
    explicit EffectsEditor(FontGenerator &generator, QWidget *parent = nullptr);
    ~EffectsEditor() override;

private slots:
    void itemsChanged(const QModelIndex &parent, int first, int last);
    void itemDataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &roles);

private:
    Ui::EffectsEditor *ui;

    std::shared_ptr<EffectGroup> mEffects;
    EffectsTreeModel *mTreeModel;
};

#endif // EFFECTSEDITOR_H
