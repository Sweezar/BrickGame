#include "gamewidgetsnake.h"

GameWidgetSnake::GameWidgetSnake(s21::Controller *c, QWidget *parent)
    : QWidget{parent}, controller(c)
{
    gameInfo = controller->getGameInfo();

    timer = new QTimer(this);

    // Соединяем таймер с методом update()
    connect(timer, &QTimer::timeout, this, &GameWidgetSnake::updateWidget);

    timer->start(1); // Запускаем таймер
}

GameWidgetSnake::~GameWidgetSnake()
{

}

UserAction_t GameWidgetSnake::getUserAction(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        return Up;
    case Qt::Key_Right:
        return Right;
    case Qt::Key_Down:
        return Down;
    case Qt::Key_Left:
        return Left;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        return Start;
    case Qt::Key_Escape:
        return Terminate;
    case Qt::Key_P:
        return Pause;
    case Qt::Key_W:
        return Action;
    default:
        return NoAction;
    }
}

void GameWidgetSnake::userInput(UserAction_t user_action, bool hold)
{
    if (hold)
    switch (user_action)
    {
    case Start:
        controller->startGame();
        break;
    case Pause:
        controller->pauseGame();
        break;
    case Terminate:
        if(gameInfo.pause == GAMEOVER || gameInfo.pause == GAMEWIN) {
            // нужно добавить возврат к главному окну
            emit returnToMenu();
        } else {
            controller->terminateGame();
        }
        break;
    case Left:
        controller->left();

        break;
    case Right:
        controller->right();
        break;
    case Up:
        controller->up();
        break;
    case Down:
        controller->down();
        break;
    case Action:
        controller->action();
        break;
    default:
        break;
    }

    this->gameInfo = controller->getGameInfo();
}

void GameWidgetSnake::updateWidget()
{
    controller->noAction();
    this->gameInfo = controller->getGameInfo();

    update();

}

void GameWidgetSnake::paintEvent(QPaintEvent *event)
{
    switch (gameInfo.pause) {
    case PAUSE:
    case UNPAUSE:
        paintGame();
        break;
    case GAMESTART:
        paintStart();
        break;
    case GAMEWIN:
    case GAMEOVER:
        paintGameOver();
    default:
        break;
    }
}

void GameWidgetSnake::keyPressEvent(QKeyEvent *event)
{
    userInput(getUserAction(event), true);
    update();
}

void GameWidgetSnake::paintGame()
{
    QPainter painter(this);
    int** field = gameInfo.field;
    Point_t applePos = controller->getApple().position;
    // Размеры ячеек
    const int cellSize = 30;

    // Закрашиваем поле под сеткой в белый цвет
    painter.fillRect(0, 0, MAP_WIDTH * cellSize, MAP_HEIGHT * cellSize, Qt::white);

    // Рисуем сетку
    painter.setPen(Qt::lightGray); // Цвет линий сетки
    for (int i = 0; i <= MAP_WIDTH; ++i) {
        painter.drawLine(i * cellSize, 0, i * cellSize, MAP_HEIGHT * cellSize);
    }
    for (int j = 0; j <= MAP_HEIGHT; ++j) {
        painter.drawLine(0, j * cellSize, MAP_WIDTH * cellSize, j * cellSize);
    }


    // Отрисовываем поле
    for (int x = 0; x < MAP_WIDTH; ++x) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            if (field[y][x]) {
                if(applePos.x == x && applePos.y == y) {
                    painter.fillRect(x * cellSize + 1, y * cellSize + 1, cellSize - 2, cellSize - 2, Qt::red);
                } else {
                    painter.fillRect(x * cellSize + 1, y * cellSize + 1, cellSize - 2, cellSize - 2, Qt::green);
                }

            } else {
                painter.fillRect(x * cellSize + 1, y * cellSize + 1, cellSize - 2, cellSize - 2, Qt::lightGray);
            }
        }
    }

    // Остальной код для отображения информации о игре
    painter.setPen(Qt::white); // Цвет текста
    painter.setFont(QFont("Arial", 20)); // Шрифт и размер текста
    painter.drawText(350, 50, QString("Score: %1").arg(gameInfo.score));
    painter.drawText(350, 80, QString("High score: %1").arg(gameInfo.high_score));
    painter.drawText(350, 110, QString("Speed: %1").arg(gameInfo.speed));

    if(gameInfo.pause == PAUSE) {
        painter.drawText(80, 230, QString("Press P for game"));
    }
}

void GameWidgetSnake::paintStart()
{
    QPainter painter(this);

    painter.setPen(Qt::white); // Цвет текста
    painter.setFont(QFont("Arial", 20)); // Шрифт и размер текста
    painter.drawText(80, 50, QString("Snake Game"));
    painter.drawText(80, 80, QString("Press Enter for start"));
    painter.drawText(80, 150, QString("Exit the game - Esc"));
    painter.drawText(80, 180, QString("Action - W"));
    painter.drawText(80, 210, QString("Pause - P"));
}

void GameWidgetSnake::paintGameOver()
{
    QPainter painter(this);

    painter.setPen(Qt::white); // Цвет текста
    painter.setFont(QFont("Arial", 20)); // Шрифт и размер текста
    painter.drawText(80, 50, QString("Game Over"));
    if(gameInfo.pause == GAMEWIN) {
        painter.drawText(80, 80, QString("You are CHAMPION"));
    }
    painter.drawText(80, 120, QString("You score: %1").arg(gameInfo.score));
    painter.drawText(80, 150, QString("High score: %1").arg(gameInfo.high_score));
    painter.drawText(80, 180, QString("Press Esc for exit"));
}
