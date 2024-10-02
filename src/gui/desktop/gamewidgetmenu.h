#ifndef GAMEWIDGETMENU_H
#define GAMEWIDGETMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QLabel>

#include "gamewidgetsnake.h"
#include "gamewidgettetris.h"

class GameWidgetMenu : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidgetMenu(QWidget *parent = nullptr);
    ~GameWidgetMenu();

public slots:

protected:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void startTetris();
    void startSnake();

private slots:
    void on_tetrisButton_clicked();
    void on_snakeButton_clicked();

private:
    QLabel* currentLabel;
    QLabel* labelTetris;
    QLabel* labelSnake;
};

#endif // GAMEWIDGETSNAKE_H
