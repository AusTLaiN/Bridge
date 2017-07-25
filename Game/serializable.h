#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace bridge_game {

class Serializable
{
public:
    template<typename T>
    using Parser = QJsonObject (*)(const T&);

public:
    Serializable();
    virtual ~Serializable();

    virtual QJsonObject toJson() = 0;
    virtual void fromJson(const QJsonObject &json) = 0;
    virtual QJsonDocument toJsonDoc();

    // Parse should have next signature:
    // QJsonObject example(const T &obj);
    // Where T is your class

    template <typename T, typename Parse>
    static QList<T> listFromJson(const QJsonArray &array, Parse parser);
    template <typename T>
    static QList<T> listFromJson(const QJsonArray &array);

    template <typename T, typename Parse>
    static QJsonArray listToJson(const QList<T> &list, Parse parser);
    template <typename T>
    static QJsonArray listToJson(const QList<T> &list);

};

// Converts list to Json.
// T must be inherited from Serializable
// virtual toJson() function is used to serialize single object

template<typename T>
QJsonArray Serializable::listToJson(const QList<T> &list)
{
    QJsonArray array;

    for (T obj : list)
    {
        array.append(obj->toJson());
    }

    return array;
}

// Same function, but with custom Parser

template<typename T, typename Parse>
QJsonArray Serializable::listToJson(const QList<T> &list, Parse parser)
{
    QJsonArray array;

    for (T obj : list)
    {
        array.append(parser(obj));
    }

    return array;
}


template<typename T>
QList<T> Serializable::listFromJson(const QJsonArray &array)
{
    QList<T> list;

    for (int i = 0; i < array.size(); ++i)
    {
        auto JsonObj = array[i].toObject();
        T obj;
        obj.fromJson(JsonObj);
        list.append(obj);
    }

    return list;
}

template<typename T, typename Parse>
QList<T> Serializable::listFromJson(const QJsonArray &array, Parse parser)
{
    QList<T> list;

    for (int i = 0; i < array.size(); ++i)
    {
        auto JsonObj = array[i].toObject();
        T obj = parser(JsonObj);
        list.append(obj);
    }

    return list;
}

} // bridge game namespace end


#endif // SERIALIZABLE_H
