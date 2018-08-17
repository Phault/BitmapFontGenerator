#include "characterswidget.h"
#include "ui_characterswidget.h"
#include <QMap>

CharactersWidget::CharactersWidget(FontGenerator &generator, QWidget *parent) :
    FontEditorWidget (generator, parent),
    ui(new Ui::CharactersWidget)
{
    ui->setupUi(this);

    ui->characters->setPlainText(generator.characters());

    connect(ui->characters, &QPlainTextEdit::textChanged, this, &CharactersWidget::textFieldChanged);
}

CharactersWidget::~CharactersWidget()
{
    delete ui;
}

QString CharactersWidget::characters() const
{
    return ui->characters->toPlainText();
}

void CharactersWidget::removeDuplicates(QString &chars) const
{
    struct MapDummyValue { };

    QMap <QChar, MapDummyValue> map;
    for (const auto &character : chars)
        map.insert(character, MapDummyValue());
    auto uniqueCharList = map.keys();

    chars.resize(uniqueCharList.count());
    for (int i = 0; i < uniqueCharList.count(); ++i)
        chars[i] = uniqueCharList[i];
}

void CharactersWidget::removeRepeatingCharacters(QString &chars) const
{
    if (chars.isNull())
        return;

    int last = 0;

    for (int i = 1; i < chars.length(); ++i)
    {
        if (chars[i] != chars[last])
        {
            ++last;
            chars[last] = chars[i];
        }
    }

    chars.resize(++last);
}

void CharactersWidget::textFieldChanged()
{
    auto chars = characters();

    std::sort(chars.begin(), chars.end());
    removeRepeatingCharacters(chars);

    if (chars != characters())
    {
        auto cursorPos = ui->characters->textCursor();
        ui->characters->setPlainText(chars);
        ui->characters->setTextCursor(cursorPos);
        fontGenerator().setCharacters(chars);

        emit changed();
    }
}
