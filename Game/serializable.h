#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace bridge_game {

class Serializable
{
public:
    Serializable();
    virtual ~Serializable();

    virtual QJsonObject toJson() = 0;
    virtual void fromJson(const QJsonObject &json) = 0;
    virtual QJsonDocument toJsonDoc();



    // Functions for easy serialization of list of objects

    // Parser should have next signature:
    // QJsonObject example(const T &obj) for serialization
    // T example(const QJsonObject &obj) for deserialization
    // Where T is your class

    template <typename T, typename Parser>
    static QList<T> listFromJson(const QJsonArray &array, Parser parser);
    template <typename T, typename Parser>
    static QList<T> listFromJson(QList<T> &list, const QJsonArray &array, Parser parser);

    template <typename T, typename Parser>
    static QJsonArray listToJson(const QList<T> &list, Parser parser);

};


template<typename T, typename Parser>
QJsonArray Serializable::listToJson(const QList<T> &list, Parser parser)
{
    QJsonArray array;

    for (T obj : list)
    {
        array.append(parser(obj));
    }

    return array;
}

// Deserialization functions

// Overloaded function. Takes QList<T> as argument, so type T is passed to the function
// It enables function call without specifying template classes
// Fills list with objects and returns it. List is not checked for emptiness

template<typename T, typename Parser>
QList<T> Serializable::listFromJson(QList<T> &list, const QJsonArray &array, Parser parser)
{
    for (int i = 0; i < array.size(); ++i)
    {
        auto JsonObj = array[i].toObject();
        T obj = parser(JsonObj);
        list.append(obj);
    }

    return list;
}

// Overloaded function. Needs specifying template for each call

template<typename T, typename Parser>
QList<T> Serializable::listFromJson(const QJsonArray &array, Parser parser)
{
    QList<T> list;
    return listFromJson(list, array, parser);
}

} // bridge game namespace end


#endif // SERIALIZABLE_H
