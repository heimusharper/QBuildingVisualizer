#include "RGraphicsWidget.h"
#include <QDebug>

namespace rintd {
    RGraphicsWidget::RGraphicsWidget(QWidget *parent) : QGraphicsView(parent)
    {
        setMouseTracking(true);
    }

    RGraphicsWidget::~RGraphicsWidget()
    {

    }

    void RGraphicsWidget::setScene(RGraphicsScene *scene)
    {
        _scene = scene;
        QGraphicsView::setScene(scene);

    }


    void RGraphicsWidget::mouseDoubleClickEvent(QMouseEvent *e)
    {
        switch (_currentMode) {
        case mode::MODE_DRAW_ROOM: {

            QPolygonF tmpPolygonF = ((QGraphicsPolygonItem*)_tmpDrawableItem)->polygon();
            if (tmpPolygonF.size() > 1) {
                tmpPolygonF.append(QPointF(mapToScene(e->pos())));
                ((QGraphicsPolygonItem*)_tmpDrawableItem)->setPolygon(tmpPolygonF);
            } else {
                _scene->removeItem(_tmpDrawableItem);
                delete _tmpDrawableItem;
            }
            _tmpDrawableItem = nullptr;

            break;
        }
        case mode::MODE_SELECT: {
            break;
        }
        default:
            break;
        }
    }

    void RGraphicsWidget::mouseMoveEvent(QMouseEvent *e)
    {
        switch (_currentMode) {
        case mode::MODE_DRAW_ROOM: {

            if (_tmpDrawableItem != nullptr) {
                if (!((QGraphicsPolygonItem*)_tmpDrawableItem)) {
                    // чет он не пустой, надо очистить к ебеням
                    _scene->removeItem(_tmpDrawableItem);
                    delete _tmpDrawableItem;
                    _tmpDrawableItem = new QGraphicsPolygonItem();
                    _scene->addItem(_tmpDrawableItem);
                    _tmpDrawableItem->setData(DATA_TYPE, QString("MODE_DRAW_ROOM"))  ;
                }
            } else {
                _tmpDrawableItem = new QGraphicsPolygonItem();
                _tmpDrawableItem->setData(DATA_TYPE, QString("MODE_DRAW_ROOM"))  ;
                _scene->addItem(_tmpDrawableItem);
            }
            QPolygonF tmpPolygonF = ((QGraphicsPolygonItem*)_tmpDrawableItem)->polygon();
            if (!tmpPolygonF.isEmpty())
                tmpPolygonF.removeLast();
            tmpPolygonF.append(QPointF(mapToScene(e->pos())));
            ((QGraphicsPolygonItem*)_tmpDrawableItem)->setPolygon(tmpPolygonF);

            break;
        }
        case mode::MODE_SELECT: {
            break;
        }
        default:
            break;
        }
    }

    void RGraphicsWidget::mousePressEvent(QMouseEvent *e)
    {
        switch (_currentMode) {
        case mode::MODE_DRAW_ROOM: {

            QPolygonF tmpPolygonF = ((QGraphicsPolygonItem*)_tmpDrawableItem)->polygon();

            tmpPolygonF.append(QPointF(mapToScene(e->pos())));
            ((QGraphicsPolygonItem*)_tmpDrawableItem)->setPolygon(tmpPolygonF);

            // если есть пересечения, точку не ставить
            for (auto *it : _scene->items(mapToScene(rect()), Qt::IntersectsItemBoundingRect)) {
                if (((QGraphicsPolygonItem*)it) && it != _tmpDrawableItem) {
                    bool contains = false;
                    qDebug() << "SIZE " << tmpPolygonF.size() << tmpPolygonF;
                    if (tmpPolygonF.size() <= 3) {
                        for (auto pointFromTmp : tmpPolygonF) {
                            if (((QGraphicsPolygonItem*)it)->polygon().containsPoint(pointFromTmp, Qt::OddEvenFill)) {
                                contains = true;
                                break;
                            }
                        }

                    } else if (!tmpPolygonF.intersected(((QGraphicsPolygonItem*)it)->polygon()).isEmpty()) {
                        contains = true;
                    }

                    if (contains) {
                        tmpPolygonF.removeLast();
                        ((QGraphicsPolygonItem*)_tmpDrawableItem)->setPolygon(tmpPolygonF);
                        break;
                    }
                }
            }

            break;
        }
        case mode::MODE_SELECT: {

            QGraphicsItem *it = itemAt(e->pos());
            if (it) {
                // очистим предыдущий
                if (_lastSelected != nullptr) {
                    if ( (QGraphicsRectItem*)_lastSelected) {
                        // прямоугольник
                        ((QGraphicsRectItem*)_lastSelected)->setBrush(QBrush(QColor(_lastSelected->data(DATA_COLOR).toString())));
                    }
                }
                // нашли элемент, определяем что это и красим

                if ( (QGraphicsRectItem*)it) {
                    // прямоугольник
                    ((QGraphicsRectItem*)it)->setBrush(QBrush(QColor(255, 255, 0)));
                }
                // запоминаем последний выделенный
                _lastSelected = it;
                emit selected();
            } else {
                // пустое пр-во
                // очищаем выделение
                if (_lastSelected != nullptr) {
                    if ( (QGraphicsRectItem*)_lastSelected) {
                        // прямоугольник
                        ((QGraphicsRectItem*)_lastSelected)->setBrush(QBrush(QColor(_lastSelected->data(DATA_COLOR).toString())));
                    }
                    _lastSelected = nullptr;
                }
                emit emptySelection();
            }
            break;
        }
        default:
            break;
        }
    }

    void RGraphicsWidget::resizeEvent(QResizeEvent *e)
    {
    }

    void RGraphicsWidget::setCurrentMode(const mode &currentMode)
    {
        _currentMode = currentMode;
        switch (_currentMode) {
        case mode::MODE_SELECT:
            setCursor(Qt::ArrowCursor);
            break;
        case mode::MODE_DRAW_ROOM:
            setCursor(Qt::CrossCursor);
            break;
        default:
            break;
        }
    }

    void RGraphicsWidget::removeSelected()
    {
        if (_lastSelected == _tmpDrawableItem)
            _tmpDrawableItem = nullptr;
        _scene->removeItem(_lastSelected);
        delete _lastSelected;
        _lastSelected = nullptr;
    }

    void RGraphicsWidget::setSceneRect(const QRectF &sceneRect)
    {
        _sceneRect = sceneRect;
        _scene->setSceneRect(_sceneRect);
    }
}

