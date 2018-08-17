#ifndef CHARACTERSWIDGET_H
#define CHARACTERSWIDGET_H

#include "fonteditorwidget.h"

#include <QWidget>

namespace Ui {
class CharactersWidget;
}

class CharactersWidget : public FontEditorWidget
{
    Q_OBJECT

public:
    explicit CharactersWidget(FontGenerator &generator, QWidget *parent = nullptr);
    ~CharactersWidget();

    QString characters() const;

    void removeDuplicates(QString &chars) const;
    void removeRepeatingCharacters(QString &chars) const;
    
private slots:
    void textFieldChanged();

private:
    Ui::CharactersWidget *ui;
};

#endif // CHARACTERSWIDGET_H
