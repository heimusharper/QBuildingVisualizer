#ifndef RGRAPHICSSCENE_H
#define RGRAPHICSSCENE_H

#include "qbuilding_global.h"
#include <QGraphicsScene>

namespace rintd {
    class QBUILDINGSHARED_EXPORT RGraphicsScene : public QGraphicsScene
    {
        Q_OBJECT
    public:
        explicit RGraphicsScene(QObject *parent = 0);
        ~RGraphicsScene();

    signals:

    public slots:
    };
}
#endif // RGRAPHICSSCENE_H
