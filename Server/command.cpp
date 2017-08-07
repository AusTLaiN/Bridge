#include "command.h"

using namespace bridge_server;

Command::Command()
    : m_action(ACTION::UndefinedAction)
{
}

Command::Command(ACTION action)
    : m_action(action)
{
}

Command::ACTION Command::getAction()
{
    return m_action;
}
