#include "textureatlaseditor.h"
#include "ui_textureatlaseditor.h"
#include "rectanglebinpack/maxrectsbinpack.h"

TextureAtlasEditor::TextureAtlasEditor(FontGenerator &generator, QWidget *parent) :
    FontEditorWidget(generator, parent),
    ui(new Ui::TextureAtlasEditor)
{
    ui->setupUi(this);

    ui->textureWidth->setValue(generator.pageWidth());
    ui->textureHeight->setValue(generator.pageHeight());

    auto margin = generator.padding();
    ui->marginTop->setValue(margin.top);
    ui->marginRight->setValue(margin.right);
    ui->marginBottom->setValue(margin.left);
    ui->marginLeft->setValue(margin.bottom);

    ui->glyphSpacingHorizontal->setValue(generator.spacingHorizontal());
    ui->glyphSpacingVertical->setValue(generator.spacingVertical());

    ui->packingMethod->setCurrentIndex(static_cast<int>(generator.packingMethod()));

    connect(ui->textureWidth, QOverload<int>::of(&QSpinBox::valueChanged), this, &TextureAtlasEditor::on_textureSize_valueChanged);
    connect(ui->textureHeight, QOverload<int>::of(&QSpinBox::valueChanged), this, &TextureAtlasEditor::on_textureSize_valueChanged);

    connect(ui->marginTop, QOverload<int>::of(&QSpinBox::valueChanged), this, &TextureAtlasEditor::on_pageMargin_valueChanged);
    connect(ui->marginRight, QOverload<int>::of(&QSpinBox::valueChanged), this, &TextureAtlasEditor::on_pageMargin_valueChanged);
    connect(ui->marginBottom, QOverload<int>::of(&QSpinBox::valueChanged), this, &TextureAtlasEditor::on_pageMargin_valueChanged);
    connect(ui->marginLeft, QOverload<int>::of(&QSpinBox::valueChanged), this, &TextureAtlasEditor::on_pageMargin_valueChanged);

    connect(ui->glyphSpacingHorizontal, QOverload<int>::of(&QSpinBox::valueChanged), this, &TextureAtlasEditor::on_glyphSpacing_valueChanged);
    connect(ui->glyphSpacingVertical, QOverload<int>::of(&QSpinBox::valueChanged), this, &TextureAtlasEditor::on_glyphSpacing_valueChanged);
}

TextureAtlasEditor::~TextureAtlasEditor()
{
    delete ui;
}

void TextureAtlasEditor::on_textureSize_valueChanged(int)
{
    fontGenerator().setPageSize(ui->textureWidth->value(), ui->textureHeight->value());

    emit changed();
}

void TextureAtlasEditor::on_pageMargin_valueChanged(int)
{
    auto top = ui->marginTop->value();
    auto right = ui->marginRight->value();
    auto bottom = ui->marginBottom->value();
    auto left = ui->marginLeft->value();

    fontGenerator().setPadding(top, right, bottom, left);

    emit changed();
}

void TextureAtlasEditor::on_glyphSpacing_valueChanged(int)
{
    fontGenerator().setSpacing(ui->glyphSpacingHorizontal->value(), ui->glyphSpacingVertical->value());

    emit changed();
}

void TextureAtlasEditor::on_packingMethod_currentIndexChanged(int index)
{
    fontGenerator().setPackingMethod(static_cast<rbp::FreeRectChoiceHeuristic>(index));

    emit changed();
}
