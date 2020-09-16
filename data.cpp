#include "data.h"

#include <QtSql>

Data::Data(QObject *parent) : QObject(parent)
{
    date = QDateTime();
}

Data::Data(QObject *parent, QSqlQuery &qry) :
    QObject(parent)
{
    this->id = qry.value("id").toInt();
    this->code = qry.value("code").toInt();
    this->date = qry.value("date").toDateTime();
    this->person = qry.value("person").toString();
    this->description = qry.value("description").toString();
}


int Data::Id()
{
    return id;
}

void Data::setId(int id)
{
    this->id = id;
}

int Data::Code()
{
    return this->code;
}

void Data::setCode(int value)
{
    this->code = value;
}


QDateTime Data::Date()
{
    return this->date;
}

void Data::setDate(QDateTime value)
{
    this->date = value;
}

QString Data::Person()
{
    return this->person;
}

void Data::setPerson(QString person)
{
    this->person = person;
}

QString Data::Description()
{
    return this->description;
}

void Data::setDescription(QString text)
{
    this->description = text;
}


