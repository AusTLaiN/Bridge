#include <QCoreApplication>
#include <QMetaEnum>
#include <QTextStream>

#include "Server/game.h"
#include "Server/Cards/six.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream qcin(stdin);
    QTextStream qcout(stdout);

    qcout << "Server started" << endl;

    Six card(Card::Clubs);

    qcout << card.getName() << endl;
    qcout << card.getValue() << endl;

    qcout.flush();
    return a.exec();
}
