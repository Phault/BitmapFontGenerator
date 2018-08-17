#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fontgenerator.h>


class QGroupBox;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    void regenerateFont();

private:
    Ui::MainWindow *ui;
    FontGenerator fontGenerator;

    BitmapFont generatedFont;
};

#endif // MAINWINDOW_H
