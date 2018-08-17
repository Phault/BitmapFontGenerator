#include "fontoptions.h"
#include "ui_fontoptions.h"

FontOptions::FontOptions(FontGenerator &generator, QWidget *parent) :
    FontEditorWidget(generator, parent),
    ui(new Ui::FontOptions)
{
    ui->setupUi(this);

    font = QFont(fontGenerator().font().familyName());
    font.setPixelSize(int(fontGenerator().font().pixelSize()));
    font.setStyle(fontGenerator().font().style());

    ui->fontComboBox->setCurrentFont(font);
    ui->fontSize->setValue(int(fontGenerator().font().pixelSize()));
    ui->bold->setChecked(font.bold());
    ui->italic->setChecked(font.italic());
    ui->antiAliasing->setChecked(fontGenerator().antiAliasing());
}

FontOptions::~FontOptions()
{
    delete ui;
}

void FontOptions::on_fontSize_valueChanged(int fontSize)
{
    font.setPixelSize(fontSize);
    fontGenerator().setFont(QRawFont::fromFont(font));

    emit changed();
}

void FontOptions::on_italic_toggled(bool checked)
{
    font.setItalic(checked);
    fontGenerator().setFont(QRawFont::fromFont(font));

    emit changed();
}

void FontOptions::on_bold_toggled(bool checked)
{
    font.setBold(checked);
    fontGenerator().setFont(QRawFont::fromFont(font));

    emit changed();
}

void FontOptions::on_fontComboBox_currentFontChanged(const QFont &f)
{
    font = f;
    font.setPixelSize(ui->fontSize->value());
    font.setStyle(fontGenerator().font().style());

    fontGenerator().setFont(QRawFont::fromFont(font));

    emit changed();
}

void FontOptions::on_antiAliasing_toggled(bool checked)
{
    fontGenerator().setAntiAliasing(checked);

    emit changed();
}
