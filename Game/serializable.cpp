#include "serializable.h"

using namespace bridge_game;

Serializable::Serializable()
{

}

Serializable::~Serializable()
{

}

QJsonDocument Serializable::toJsonDoc()
{
    return QJsonDocument(this->toJson());
}
