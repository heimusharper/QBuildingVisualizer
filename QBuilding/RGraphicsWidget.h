#ifndef RGRAPHICSWIDGET_H
#define RGRAPHICSWIDGET_H

#include <QObject>
#include <QGraphicsView>
#include "qbuilding_global.h"
#include "RGraphicsScene.h"
#include "graph/RNode.h"
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsPolygonItem>

namespace rintd {

    class QBUILDINGSHARED_EXPORT RGraphicsWidget : public QGraphicsView
    {
        Q_OBJECT
    public:

        enum class mode {
            MODE_SELECT,
            MODE_DRAW_ROOM
        };
        enum data_ : int {
            DATA_COLOR = 1,
            DATA_TYPE = 2
        };

        explicit RGraphicsWidget(QWidget *parent = Q_NULLPTR);
        ~RGraphicsWidget();

        void setScene(RGraphicsScene *scene);

        void setSceneRect(const QRectF &sceneRect);

        void setCurrentMode(const mode &currentMode);

        void removeSelected();

    protected:

        void mouseDoubleClickEvent(QMouseEvent *e);

        void mouseMoveEvent(QMouseEvent *e);

        void mousePressEvent(QMouseEvent *e);

        void resizeEvent(QResizeEvent *e);



    private:

        QGraphicsItem *_lastSelected = nullptr;

        QGraphicsItem *_tmpDrawableItem = nullptr;


        mode _currentMode = mode::MODE_SELECT;

        RGraphicsScene *_scene;

        QRectF _sceneRect;

    signals:

        void emptySelection();
        void selected();

    public slots:
    };
}

#endif // RGRAPHICSWIDGET_H
