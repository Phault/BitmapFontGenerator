#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "fontoptions.h"
#include "characterswidget.h"
#include "textureatlaseditor.h"
#include "effectseditor.h"

#include <QGroupBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRawFont>
#include <bitmapfont.h>
#include <effectfactory.h>
#include <fontgenerator.h>

#include <effects/filleffect.h>
#include <effects/strokeeffect.h>
#include <effects/effectgroup.h>
#include <effects/blureffect.h>
#include <effects/dropshadoweffect.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLinearGradient gradient(QPoint(0, 0), QPoint(0, 72));
        gradient.setColorAt(0, QColor(195, 232, 130));
        gradient.setColorAt(1, QColor(152, 242, 56));
    auto fill = new FillEffect(gradient);
    fill->setName("Fill");

    auto stroke = new StrokeEffect(QColor(100, 170, 70), 5);
    stroke->setName("Green Stroke");
    stroke->setAdjustGlyphAdvances(true);
    stroke->setEnabled(false);

    auto extraStroke = new StrokeEffect(Qt::red, 5);
    extraStroke->setName("Red Stroke");

    auto font = QRawFont::fromFont(QFont("Arial Black"));
    font.setPixelSize(60);

    fontGenerator = FontGenerator(font, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+-,./()!? ");
    fontGenerator.setPageSize(256, 256);
    fontGenerator.setBackgroundColor(Qt::transparent);
    fontGenerator.setPackingMethod(rbp::FreeRectChoiceHeuristic::BestAreaFit);
    fontGenerator.setEffects({
                             fill,
                             new EffectGroup({ stroke, extraStroke }),
                             new DropShadowEffect(Qt::cyan, QPoint(3, 3), 5),
                             new BlurEffect(5),
                         });
    fontGenerator.setPadding(1, 1, 1, 1);
    fontGenerator.setSpacing(1, 1);
    fontGenerator.setAntiAliasing(true);

    auto fontEditor = new FontOptions(fontGenerator);
    auto charactersEditor = new CharactersWidget(fontGenerator);
    auto textureAtlasEditor = new TextureAtlasEditor(fontGenerator);
    auto effectsEditor = new EffectsEditor(fontGenerator);

    connect(fontEditor, &FontEditorWidget::changed, this, &MainWindow::regenerateFont);
    connect(charactersEditor, &FontEditorWidget::changed, this, &MainWindow::regenerateFont);
    connect(textureAtlasEditor, &FontEditorWidget::changed, this, &MainWindow::regenerateFont);
    connect(effectsEditor, &FontEditorWidget::changed, this, &MainWindow::regenerateFont);

    ui->optionsSidebar->addWidget("Font", fontEditor);
    ui->optionsSidebar->addWidget("Characters", charactersEditor);
    ui->optionsSidebar->addWidget("Texture Atlas", textureAtlasEditor);
    ui->effectsSidebar->addWidget("Effects", effectsEditor);

    connect(ui->actionNext, &QAction::triggered, ui->pagePreview, &PagePreview::nextPage);
    connect(ui->actionPrevious, &QAction::triggered, ui->pagePreview, &PagePreview::prevPage);

    regenerateFont();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::regenerateFont()
{
    generatedFont = fontGenerator.generate();
    ui->pagePreview->setBitmapFont(generatedFont);
}
