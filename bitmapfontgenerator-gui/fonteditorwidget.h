#ifndef FONTEDITORWIDGET_H
#define FONTEDITORWIDGET_H

#include <QWidget>
#include <fontgenerator.h>

class FontEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FontEditorWidget(FontGenerator &generator, QWidget *parent = nullptr);
    ~FontEditorWidget() override {}

    FontGenerator &fontGenerator() const;
    void setFontGenerator(FontGenerator &generator);

signals:
    void changed();

private:
    FontGenerator &mGenerator;
};

#endif // FONTEDITORWIDGET_H
