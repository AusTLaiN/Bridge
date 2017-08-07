#ifndef HTMLDATAOBJECT_H
#define HTMLDATAOBJECT_H

#include "dataobject.h"

namespace bridge_server {

class HtmlDataObject : public DataObject
{
    QString m_html;
public:
    HtmlDataObject();
    HtmlDataObject(const QJsonObject& json);

    virtual QString toString() override;
    virtual QJsonObject toJson() override;
    virtual void fromJson(const QJsonObject &json) override;
};

typedef HtmlDataObject StringDataObject;

} // bridge_server

#endif // HTMLDATAOBJECT_H
