#include "MainWindow.h"
#include "ui_MainWindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // scene




    _graphicsView = new rintd::RGraphicsWidget(this);
    ui->centralGridLayout->addWidget(_graphicsView);
    _scene = new rintd::RGraphicsScene(_graphicsView);
    _graphicsView->setScene(_scene);
    _graphicsView->setSceneRect(QRectF(0, 0, 2000, 2000));



    // ui
    // выделение
    _crossButton = new QPushButton(this);
    _crossButton->setIcon(QIcon());
    _crossButton->setIconSize(QSize(22, 22));
    _crossButton->setCheckable(true);
    connect(_crossButton, &QPushButton::clicked, [this]() {
        clearAllButtons();
        _crossButton->setChecked(true);
        _graphicsView->setCurrentMode(rintd::RGraphicsWidget::mode::MODE_SELECT);
    });

    ui->mainToolBar->addWidget(_crossButton);
    // создание комнаты
    _addRoomButton = new QPushButton(this);
    _addRoomButton->setIcon(QIcon(":/img/add_room.png"));
    _addRoomButton->setIconSize(QSize(22, 22));
    _addRoomButton->setCheckable(true);
    connect(_addRoomButton, &QPushButton::clicked, [this]() {
        clearAllButtons();
        _addRoomButton->setChecked(true);
        _graphicsView->setCurrentMode(rintd::RGraphicsWidget::mode::MODE_DRAW_ROOM);
    });

    ui->mainToolBar->addWidget(_addRoomButton);
    // удаление
    _removeButton = new QPushButton(this);
    _removeButton->setIcon(QIcon(":/img/delete.pngg"));
    _removeButton->setIconSize(QSize(22, 22));
    _removeButton->setEnabled(false);
    connect(_removeButton, &QPushButton::clicked, [this]() {
        _graphicsView->removeSelected();
    });
    connect(_graphicsView, &rintd::RGraphicsWidget::emptySelection, [this](){
        _removeButton->setEnabled(false);
    });
    connect(_graphicsView, &rintd::RGraphicsWidget::selected, [this](){
        _removeButton->setEnabled(true);
    });

    ui->mainToolBar->addWidget(_removeButton);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::retranslate()
{
    _addRoomButton->setToolTip(tr("Draw room"));
}

void MainWindow::clearAllButtons()
{
    _crossButton->setChecked(false);
    _addRoomButton->setChecked(false);
}
