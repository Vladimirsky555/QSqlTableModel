#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(Data *item, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    this->item = item;
    setWindowTitle("Добавление варки");

    this->item->setCode(0);
    this->item->setPerson("Вася");
    this->item->setDescription("Комментарий по умолчанию");

    load();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::load()
{    
    ui->edtCode->setText(QString::number(item->Code()));
    ui->dateEdit->setDateTime(item->Date());
    ui->cbxPerson->setText(item->Person());
    ui->textEdit->setText(item->Description());

}

void Dialog::save()
{
    item->setCode(ui->edtCode->text().toInt());
    item->setDate(ui->dateEdit->dateTime());
    item->setPerson(ui->cbxPerson->text());
    item->setDescription(ui->textEdit->toPlainText());
}

void Dialog::on_btnCancel_clicked()
{
    close();
}

void Dialog::on_btnAdd_clicked()
{
    save();
    close();
}

