#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <RGraphicsWidget.h>
#include <RGraphicsScene.h>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    rintd::RGraphicsWidget *_graphicsView;
    rintd::RGraphicsScene *_scene;



    void retranslate();
    void clearAllButtons();

    // ui

    QPushButton *_crossButton;
    QPushButton *_addRoomButton;
    QPushButton *_removeButton;

};

#endif // MAINWINDOW_H
