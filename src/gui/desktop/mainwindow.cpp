#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMinimumSize(600, 640);
    setStyleSheet("background-color: rgb(55, 55, 55)");

    startMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startTetris() {
    // Создание и отображение виджета игры Tetris
    GameWidgetTetris* gameWidget = new GameWidgetTetris(this);
    setCentralWidget(gameWidget);

    connect(gameWidget, &GameWidgetTetris::returnToMenu, this, &MainWindow::returnToMenu);

    gameWidget->setFocus();
    gameWidget->show();
    // Отключаем фокус для главного окна
    setFocusPolicy(Qt::NoFocus);
}

void MainWindow::startSnake() {
    // Создание и отображение виджета игры Snake
    s21::Model* model = new s21::Model();
    s21::Controller* controller = new s21::Controller(model);
    GameWidgetSnake* gameWidget = new GameWidgetSnake(controller,this);
    setCentralWidget(gameWidget);

    connect(gameWidget, &GameWidgetSnake::returnToMenu, this, &MainWindow::returnToMenu);

    gameWidget->setFocus();
    gameWidget->show();
    // Отключаем фокус для главного окна
    setFocusPolicy(Qt::NoFocus);
}

void MainWindow::startMenu()
{
    // Создание и отображение виджета Menu
    GameWidgetMenu* menu = new GameWidgetMenu(this);
    setCentralWidget(menu);

    connect(menu, &GameWidgetMenu::startTetris, this, &MainWindow::startTetris);
    connect(menu, &GameWidgetMenu::startSnake, this, &MainWindow::startSnake);

    menu->setFocus();
    menu->show();
    // Отключаем фокус для главного окна
    setFocusPolicy(Qt::NoFocus);
}

void MainWindow::returnToMenu()
{
    startMenu();
}


