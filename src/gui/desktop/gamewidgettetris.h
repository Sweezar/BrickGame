#ifndef GAMEWIDGETTETRIS_H
#define GAMEWIDGETTETRIS_H

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>

extern "C" {
    #include "../../brick_game/tetris/tetris.h"
    #include "../../brick_game/tetris/objects.h"
    #include "../../brick_game/tetris/fsm.h"
}

class GameWidgetTetris : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidgetTetris(QWidget *parent = nullptr);
    ~GameWidgetTetris();

    UserAction_t getUserAction(QKeyEvent *event);
    void userInput(UserAction_t user_action, bool hold = true);
    void paintGame();
    void paintStart();
    void paintGameOver();
    QColor getColor(Figure_t* figure);

signals:
    void returnToMenu();

public slots:
    void updateWidget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    Game_t* game;
    QTimer *timer;

};

#endif // GAMEWIDGETTETRIS_H
