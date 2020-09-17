#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QSqlTableModel>


#include "data.h"
#include "dialog.h"

class Model : public QSqlTableModel
{

    Q_OBJECT

    QList<Data*>*items;//Список указателей на элементы
    QModelIndex currentIndex;

public:
    //Экшены
    QList<QAction*> allActions;
    QAction *actEditItem;
    QAction *actDeleteItem;

public:
    Model(QObject *parent = 0);
    virtual ~Model();

    void selectAll();
    void addItem(Data *item);//В модель
    void addData();//В модель и базу

protected slots:
    void edit_item();//В модель и базу
    void delete_item();

private:
    delete_from_db(Data* item);

public slots:
    acceptIndexfromView(QModelIndex index);

private slots:
    bool save_to_db(Data *item);
    bool update_in_db(Data *item);

    //Вспомогательные функции
protected:
    virtual QVariant    dataDisplay(const QModelIndex &index) const;
    virtual Data *getItem(const QModelIndex &I)const;

    // QSqlTableModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &I, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // MODEL_H
