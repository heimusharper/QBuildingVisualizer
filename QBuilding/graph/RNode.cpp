#include "RNode.h"
namespace rintd {
    RNode::RNode(QObject *parent) : QObject(parent)
    {
        _uuid = QUuid::createUuid();
    }

    QUuid RNode::uuid() const
    {
        return _uuid;
    }
}
