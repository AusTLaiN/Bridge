#include "htmldataobject.h"

using namespace bridge_game;
using namespace bridge_server;


HtmlDataObject::HtmlDataObject()
    : DataObject(), m_html("")
{}

HtmlDataObject::HtmlDataObject(const QJsonObject& json)
    : DataObject(), m_html("")
{
    this->fromJson(json);
}

QString HtmlDataObject::toString()
{
    return QString("HtmlDataObject");
}

QJsonObject HtmlDataObject::toJson()
{
    QJsonObject jObj = DataObject::toJson();
    jObj["html"] = m_html;
    jObj["name"] = toString();

    return jObj;
}

void HtmlDataObject::fromJson(const QJsonObject &json)
{
    DataObject::fromJson(json);
    if(!json["html"].isUndefined() && json["html"].isString())
        m_html = json["html"].toString();
    else
        addJsonError("html");

    hasJsonError(true);
}

QString HtmlDataObject::getText()
{
    return m_html;
}

void HtmlDataObject::setText(QString text)
{
    m_html = text;
}
