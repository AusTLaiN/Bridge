#ifndef BLOCKTURN_H
#define BLOCKTURN_H

#include <QObject>

class BlockTurn : public QObject
{
    Q_OBJECT
public:
    explicit BlockTurn(QObject *parent = 0);

signals:

public slots:
};

#endif // BLOCKTURN_H