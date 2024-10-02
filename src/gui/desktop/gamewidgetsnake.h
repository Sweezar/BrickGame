#ifndef GAMEWIDGETSNAKE_H
#define GAMEWIDGETSNAKE_H

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>

#include "../../brick_game/snake/controller.h"
#include "../../brick_game/snake/defines.h"

class GameWidgetSnake : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidgetSnake(s21::Controller *c, QWidget *parent = nullptr);
    ~GameWidgetSnake();

    UserAction_t getUserAction(QKeyEvent *event);
    void userInput(UserAction_t user_action, bool hold = true);
    void paintGame();
    void paintStart();
    void paintGameOver();

signals:
    void returnToMenu();

public slots:
    void updateWidget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

signals:

private:
    s21::Controller *controller;
    GameInfo_t gameInfo;
    QTimer *timer; // Таймер для обновления
};

#endif // GAMEWIDGETSNAKE_H
