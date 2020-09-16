#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QVariant>
#include <QDateTime>
#include <QTime>

class QSqlQuery;

class Data : public QObject
{
    Q_OBJECT

    int id;//идентификационный номер
    int code;
    QDateTime date;
    QString person;//варщик
    QString description;//Описание


public:
    Data(QObject *parent = 0);
    Data(QObject *parent, QSqlQuery &qry);
    virtual ~Data(){}

    int Id();
    int Code();
    QDateTime Date();
    QString Person();
    QString Description();

    void setId(int id);
    void setCode(int value);
    void setDate(QDateTime value);
    void setPerson(QString person);
    void setDescription(QString text);
};

#endif // DATA_H
