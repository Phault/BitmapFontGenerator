#include "fonteditorwidget.h"

FontEditorWidget::FontEditorWidget(FontGenerator &generator, QWidget *parent) :
    QWidget(parent),
    mGenerator(generator)
{

}

FontGenerator &FontEditorWidget::fontGenerator() const
{
    return mGenerator;
}

void FontEditorWidget::setFontGenerator(FontGenerator &generator)
{
    mGenerator = generator;
}
