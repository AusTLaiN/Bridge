#ifndef CARDLISTDATAOBJECT_H
#define CARDLISTDATAOBJECT_H

#include "dataobject.h"

namespace bridge_server {

class CardListDataObject : public DataObject
{
    bridge_game::CardList m_cardList;
public:
    CardListDataObject();
    CardListDataObject(const QJsonObject& json);

    virtual QString toString() override;
    virtual QJsonObject toJson() override;
    virtual void fromJson(const QJsonObject &json) override;
};

} // bridge_server
#endif // CARDLISTDATAOBJECT_H
