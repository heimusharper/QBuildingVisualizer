#ifndef RNODE_H
#define RNODE_H

#include <QObject>
#include <QUuid>

namespace rintd {
    class RNode : public QObject
    {
       Q_OBJECT
    public:
        explicit RNode(QObject *parent = 0);

        QUuid uuid() const;

    private:

        QUuid _uuid;

    signals:

    public slots:
    };
}
#endif // RNODE_H
