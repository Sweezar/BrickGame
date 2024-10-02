#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QLabel>

#include "gamewidgetsnake.h"
#include "gamewidgettetris.h"
#include "gamewidgetmenu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startTetris();
    void startSnake();
    void startMenu();
    // void keyPressEvent(QKeyEvent *event);
    void returnToMenu();

private:
    Ui::MainWindow *ui;
    QLabel* currentLabel;
    QLabel* labelTetris;
    QLabel* labelSnake;
};
#endif // MAINWINDOW_H
