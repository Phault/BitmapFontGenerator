#ifndef FONTOPTIONS_H
#define FONTOPTIONS_H

#include "fonteditorwidget.h"

#include <QWidget>

namespace Ui {
class FontOptions;
}

class FontOptions : public FontEditorWidget
{
    Q_OBJECT

public:
    explicit FontOptions(FontGenerator &generator, QWidget *parent = nullptr);
    ~FontOptions() override;

private slots:
    void on_fontSize_valueChanged(int arg1);

    void on_italic_toggled(bool checked);

    void on_bold_toggled(bool checked);

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_antiAliasing_toggled(bool checked);

private:
    Ui::FontOptions *ui;
    QFont font;
};

#endif // FONTOPTIONS_H
