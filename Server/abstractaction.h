#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H

#include <QObject>

class AbstractAction : public QObject
{
    Q_OBJECT
public:
    explicit AbstractAction(QObject *parent = 0);

signals:

public slots:
};

#endif // ABSTRACTACTION_H