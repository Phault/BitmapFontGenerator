#ifndef BITMAPOPTIONS_H
#define BITMAPOPTIONS_H

#include "fonteditorwidget.h"

#include <QWidget>

namespace Ui {
class TextureAtlasEditor;
}

class TextureAtlasEditor  : public FontEditorWidget
{
    Q_OBJECT

public:
    explicit TextureAtlasEditor(FontGenerator &generator, QWidget *parent = nullptr);
    ~TextureAtlasEditor() override;

private slots:
    void on_textureSize_valueChanged(int);
    void on_pageMargin_valueChanged(int);
    void on_glyphSpacing_valueChanged(int);
    void on_packingMethod_currentIndexChanged(int index);

private:
    Ui::TextureAtlasEditor *ui;
};

#endif // BITMAPOPTIONS_H
