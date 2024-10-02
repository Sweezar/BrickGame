#include "gamewidgettetris.h"

GameWidgetTetris::GameWidgetTetris(QWidget *parent)
    : QWidget{parent}
{
    game = gameT();

    createGame();

    timer = new QTimer(this);

    // Соединяем таймер с методом update()
    connect(timer, &QTimer::timeout, this, &GameWidgetTetris::updateWidget);

    timer->start(1); // Запускаем таймер
}

GameWidgetTetris::~GameWidgetTetris()
{
    freeGame();
}

UserAction_t GameWidgetTetris::getUserAction(QKeyEvent *event)
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

void GameWidgetTetris::userInput(UserAction_t user_action, bool hold)
{
    action act = NULL;
    if (!game->game_info->pause) {
        tetrisTimer();

        act = fsm(game->state, user_action);
    } else {
        if (user_action == Pause || user_action == Terminate) {
            act = fsm(game->state, user_action);
        }
    }

    if (act && hold) act();
}

void GameWidgetTetris::paintGame()
{
    QPainter painter(this);
    int** field = game->game_info->field;
    QColor color = getColor(game->figure);
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
                painter.fillRect(x * cellSize + 1, y * cellSize + 1, cellSize - 2, cellSize - 2, Qt::green);
            } else {
                painter.fillRect(x * cellSize + 1, y * cellSize + 1, cellSize - 2, cellSize - 2, Qt::lightGray);
            }

            if (game->figure && game->figure->blocks != NULL) {
                int fx = x - game->figure->x;
                int fy = y - game->figure->y;

                if (fx >= 0 && fx < FIGURE_SIZE && fy >= 0 && fy < FIGURE_SIZE) {
                if (game->figure->blocks[fy][fx] == 1) {
                    painter.fillRect(x * cellSize + 1, y * cellSize + 1, cellSize - 2, cellSize - 2, color);
                }
                }
            }
        }
    }

    // Следующая фигура
    color = getColor(game->next_figure);
    for (int i = 0; i < FIGURE_SIZE; i++) {
        for (int j = 0; j < FIGURE_SIZE; j++) {
          if (game->next_figure->blocks[j][i] != 0) {
            painter.fillRect(i * cellSize + 320, j * cellSize + 120, cellSize - 2, cellSize - 2, color);
          }
        }
      }

//     Остальной код для отображения информации о игре
    painter.setPen(Qt::white); // Цвет текста
    painter.setFont(QFont("Arial", 20)); // Шрифт и размер текста
    painter.drawText(350, 50, QString("Score: %1").arg(game->game_info->score));
    painter.drawText(350, 80, QString("High score: %1").arg(game->game_info->high_score));
    painter.drawText(350, 110, QString("Speed: %1").arg(game->game_info->speed));

    if(game->game_info->pause) {
        painter.drawText(80, 230, QString("Press P for game"));
    }
}

void GameWidgetTetris::paintStart()
{
    QPainter painter(this);

    painter.setPen(Qt::white); // Цвет текста
    painter.setFont(QFont("Arial", 40)); // Шрифт и размер текста
    painter.drawText(80, 50, QString("Tetris Game"));
    painter.setFont(QFont("Arial", 20)); // Шрифт и размер текста
    painter.drawText(80, 80, QString("Press Enter for start"));
    painter.drawText(80, 110, QString("Exit the game - Esc"));
    painter.drawText(80, 140, QString("Action - W"));
    painter.drawText(80, 170, QString("Pause - P"));
}

void GameWidgetTetris::paintGameOver()
{
    QPainter painter(this);

    painter.setPen(Qt::white); // Цвет текста
    painter.setFont(QFont("Arial", 40)); // Шрифт и размер текста
    painter.drawText(80, 50, QString("Game Over"));
    if (game->game_info->high_score < game->game_info->score) {
       painter.setFont(QFont("Arial", 20)); // Шрифт и размер текста
       painter.drawText(80, 80, QString( "You are the"));
       painter.setFont(QFont("Arial", 40)); // Шрифт и размер текста
       painter.drawText(80, 130, QString( "CHAMPION"));
    }
    painter.setFont(QFont("Arial", 20)); // Шрифт и размер текста
    painter.drawText(80, 180, QString( "You scored : %1").arg(game->game_info->score));
    painter.drawText(80, 210, QString( "High-score : %1").arg(game->game_info->high_score));
    painter.drawText(80, 240, QString( "Press Esc to exit"));

}

QColor GameWidgetTetris::getColor(Figure_t* figure)
{
 QColor color;
 switch (figure->color) {
 case 3:
     color = Qt::magenta;
     break;
 case 4:
     color = Qt::red;
     break;
 case 5:
     color = Qt::yellow;
     break;
 case 6:
     color = Qt::blue;
     break;
 case 7:
     color = Qt::cyan;
     break;
 default:
     break;
 }
 return color;
}

void GameWidgetTetris::updateWidget()
{
    userInput(NoAction);
    update();
}

void GameWidgetTetris::paintEvent(QPaintEvent *event)
{
    if(game->state == TET_START) {
        paintStart();
    } else if(game->state == TET_GAMEOVER) {
        paintGameOver();
    } else {
        paintGame();
    }
}

void GameWidgetTetris::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape && game->state == TET_GAMEOVER) {
        emit returnToMenu();
    }
    userInput(getUserAction(event), true);
    update();
}
