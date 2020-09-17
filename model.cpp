#include "model.h"

#include <QSqlQuery>
#include <QFont>
#include <QColor>
#include <QAction>
#include <QDebug>
#include <QSqlError>


Model::Model(QObject *parent) : QSqlTableModel(parent)
{
    items = new QList<Data*>;
    //Список экшенов
  {
        QAction *A = actEditItem = new QAction(tr("Редактировать"), this);
        A->setShortcut(tr("Ctrl+E"));
        connect(A, SIGNAL(triggered()), this, SLOT(edit_item()));
        allActions << A;
    }{
        QAction *A = actDeleteItem = new QAction(tr("Удалить"), this);
        A->setShortcut(tr("Ctrl+D"));
        connect(A, SIGNAL(triggered()), this, SLOT(delete_item()));
        allActions << A;
    }

    selectAll();
}

Model::~Model(){}

void Model::selectAll()
{
    QSqlQuery qry;
    qry.prepare(
                "SELECT                   \n"
                "   id,                        \n"
                "   code,             \n"
                "   date,                  \n"
                "   person,                  \n"
                "   description                  \n"
                "   FROM myDB          \n"
                "   ORDER BY date DESC;   \n"
                );

    if(qry.exec()){
        while(qry.next()){
            Data *item = new Data(this, qry);
            addItem(item);
        }
    } else {
        qCritical() << "Cannot execute query!";
        QSqlError err = qry.lastError();
        qCritical() << err.nativeErrorCode();
        qCritical() << err.databaseText().toUtf8().data();
        qCritical() << err.driverText().toUtf8().data();
        qDebug() << qry.executedQuery();
    }
}

void Model::addItem(Data *item)
{
    if(item != NULL){
        items->append(item);
    }
    return;
}

void Model::addData()
{
    Data *item = new Data();

    beginResetModel();
    Dialog d(item);
    d.save();
    d.exec();
    endResetModel();

  save_to_db(item);//В базу данных
  addItem(item);//В модель
}

void Model::edit_item()
{
    Data *item = getItem(currentIndex);
    if(!item)return;

    beginResetModel();
    Dialog d(item);
    d.save();
    d.exec();
    items->replace(currentIndex.row(), item);
    endResetModel();

    update_in_db(item);
}

void Model::delete_item()
{
    Data *item = getItem(currentIndex);
    if(!item)return;

    beginRemoveRows(QModelIndex(), currentIndex.row(), currentIndex.row());
    items->removeOne(item);
    delete item;
    endRemoveRows();

    delete_from_db();//Из базы также удаляем
}

Model::delete_from_db()
{
    QSqlQuery query;
    query.setForwardOnly(true);
        query.prepare("DELETE FROM myDB WHERE id = :ID ;");
        query.bindValue(":ID", currentIndex.row());

        if(!query.exec()){
            qCritical() << query.lastError().databaseText().toUtf8().data();
            qCritical() << query.lastError().driverText();
            qCritical() << query.lastError().nativeErrorCode();
            return false;
        } else {
            return true;
        }
        return false;
}

Model::acceptIndexfromView(QModelIndex index)
{
    this->currentIndex = index;
}

bool Model::save_to_db(Data *item)
{   
    QSqlQuery query;
    query.setForwardOnly(true);

    query.prepare("INSERT INTO myDB (code, date, person, description)"
                              "VALUES (:code, :date, :person, :description)");

    query.bindValue(":code", item->Code());
    query.bindValue(":date", item->Date());
    query.bindValue(":person", item->Person());
    query.bindValue(":description", item->Description());

    if(query.exec()) return true;

    qCritical() << query.lastError().databaseText();
    qCritical() << query.lastError().driverText();
    qCritical() << query.lastError().nativeErrorCode();

    return false;
}

bool Model::update_in_db(Data *item)
{
    QSqlQuery query;
    query.setForwardOnly(true);
    query.prepare("UPDATE myDB SET      \n"
                  " code = :code,                     \n"
                  " date = :date,                                \n"
                  " person = :person,                        \n"
                  " description = :description            \n"
                  "WHERE id = :id;                                \n"
                  );

    query.bindValue(":code", item->Code());
    query.bindValue(":date", item->Date());
    query.bindValue(":person", item->Person());
    query.bindValue(":description", item->Description());

    if(query.exec()) {
        return true;
    } else {
        qCritical() << query.lastError().databaseText();
        qCritical() << query.lastError().driverText();
        qCritical() << query.lastError().nativeErrorCode();

        return false;
    }
}

QVariant Model::dataDisplay(const QModelIndex &index) const
{
    Data *item = items->at(index.row());
    switch (index.column()) {
    case 0: return item->Date().isValid() ? item->Date().toString("dd.MM.yyyy") : "";
    case 1: return item->Code();
    case 2: return item->Person();
    case 3: return item->Description();
    default: return QVariant();
    }
}



Data *Model::getItem(const QModelIndex &I) const
{
    int R = I.row();
    if(R < 0 || R >= items->size()) return 0;
    return items->at(R);
}

int Model::rowCount(const QModelIndex &parent) const
{
    //Если родитель существует, то кол-во строк 0
    if(!parent.isValid()){
        return items->count();
    } else {
        return 0;
    }
}

int Model::columnCount(const QModelIndex &parent) const
{
    if(!parent.isValid()){
        return 4;
    } else {
        return 0;
    }
}

QVariant Model::data(const QModelIndex &I, int role) const
{
    switch (role) {
    case Qt::DisplayRole:             return dataDisplay(I);//Вспомогательная функция
    default:  return QVariant();
    }
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    //Для горизонтальных заголовков оставляем данные по умолчанию
    if(orientation != Qt::Horizontal){
        return QAbstractTableModel::headerData(section,orientation,role);
    }

    switch (role) {
    case Qt::DisplayRole:
        switch (section) {
        case 0: return tr("Дата");
        case 1: return tr("Номер");
        case 2: return tr("ФИО");
        case 3: return tr("Комментарии");
        default: return QVariant();
        }
    case Qt::TextAlignmentRole:
        return QVariant(Qt::AlignBaseline | Qt::AlignHCenter);
    case Qt::ForegroundRole:
    {
//        QFont F;
//        F.setBold(true);
//        return F;
    }
    default: return QVariant();
    }
}

Qt::ItemFlags Model::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}



