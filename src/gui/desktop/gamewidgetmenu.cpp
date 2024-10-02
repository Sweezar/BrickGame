#include "gamewidgetmenu.h"

GameWidgetMenu::GameWidgetMenu(QWidget *parent)
{
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);

    // Создание виджетов
    labelTetris = new QLabel("Tetris");
    labelSnake = new QLabel("Snake");
    labelTetris->setStyleSheet(QString("font-size: 40px;"));
    labelSnake->setStyleSheet(QString("font-size: 40px;"));

    labelTetris->setPalette(palette);
    labelSnake->setPalette(palette);
    
    currentLabel = labelTetris;
    currentLabel->setStyleSheet(QString("font-size: 60px"));

    // Создание макета
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(labelTetris);
    layout->addWidget(labelSnake);
    layout->setAlignment(Qt::AlignCenter);

    setLayout(layout);
}

GameWidgetMenu::~GameWidgetMenu()
{
}

void GameWidgetMenu::on_tetrisButton_clicked()
{
    emit startTetris();
}

void GameWidgetMenu::on_snakeButton_clicked()
{
    emit startSnake();
}

void GameWidgetMenu::keyPressEvent(QKeyEvent *event)
{
    // Проверяем, какая клавиша была нажата
    if (event->key() == Qt::Key_Up) {
        // Переключаемся на Tetris
        currentLabel = labelTetris;
        labelSnake->setStyleSheet(QString("font-size: 40px"));
        currentLabel->setStyleSheet(QString("font-size: 60px"));
    } else if (event->key() == Qt::Key_Down) {
        // Переключаемся на Snake
        currentLabel = labelSnake;
        labelTetris->setStyleSheet(QString("font-size: 40px"));
        currentLabel->setStyleSheet(QString("font-size: 60px"));
    } else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        currentLabel == labelTetris ? on_tetrisButton_clicked() : on_snakeButton_clicked();
    }
}