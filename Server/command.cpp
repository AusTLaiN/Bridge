#include "command.h"

using namespace bridge_server;

Command::Command(QObject* parent)
    : QObject(parent), m_action(ACTION::UndefinedAction)
{
}

Command::Command(ACTION action, QObject* parent)
    : QObject(parent),m_action(action)
{
}

Command::~Command()
{
    qDebug() << "cmdDestr";
}

Command::ACTION Command::getAction() const
{
    return m_action;
}
