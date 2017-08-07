#ifndef DATAOBJECTFACTORY_H
#define DATAOBJECTFACTORY_H

#include "DataObjects/dataobject.h"
#include "DataObjects/htmldataobject.h"
#include "DataObjects/intdataobject.h"
#include "DataObjects/flagdataobject.h"
#include "DataObjects/cardlistdataobject.h"
#include "command.h"
#include "global.h"

namespace bridge_server {

class DataObjectFactory
{
public:
    DataObjectFactory();

    static DataObjectPtr getInnerDataObject(Command& cmd, const QJsonObject& json);
    static DataObjectPtr getOuterDataObject(Command& cmd);
};

} // bridge_server

#endif // DATAOBJECTFACTORY_H
