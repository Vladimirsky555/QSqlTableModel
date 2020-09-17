#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(Data *item, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    this->item = item;
    setWindowTitle("Добавление");

    fillBoxes();
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

    if(item->Person() == "Никто"){
        ui->cbxPerson->setCurrentIndex(0);
    } else if(item->Person() == "Ален Делон"){
        ui->cbxPerson->setCurrentIndex(1);
    }else if(item->Person() == "Александр Македонский"){
        ui->cbxPerson->setCurrentIndex(2);
    }else if(item->Person() == "Владимир Мономах"){
        ui->cbxPerson->setCurrentIndex(3);
    }else if(item->Person() == "Мадонна"){
        ui->cbxPerson->setCurrentIndex(4);
    }else if(item->Person() == "Чингисхан"){
        ui->cbxPerson->setCurrentIndex(5);
    }

    ui->textEdit->setText(item->Description());

}

void Dialog::save()
{
    item->setCode(ui->edtCode->text().toInt());
    item->setDate(ui->dateEdit->dateTime());

    if(ui->cbxPerson->currentIndex() == 0){
        item->setPerson("Никто");
    } else if(ui->cbxPerson->currentIndex() == 1){
        item->setPerson("Ален Делон");
    }else if(ui->cbxPerson->currentIndex() == 2){
        item->setPerson("Александр Македонский");
    }else if(ui->cbxPerson->currentIndex() == 3){
        item->setPerson("Владимир Мономах");
    }else if(ui->cbxPerson->currentIndex() == 4){
        item->setPerson("Мадонна");
    }else if(ui->cbxPerson->currentIndex() == 5){
        item->setPerson("Чингисхан");
    }

    item->setDescription(ui->textEdit->toPlainText());
}

void Dialog::fillBoxes()
{
    ui->cbxPerson->addItem("Никто");
    ui->cbxPerson->addItem("Ален Делон");
    ui->cbxPerson->addItem("Александр Македонский");
    ui->cbxPerson->addItem("Владимир Мономах");
    ui->cbxPerson->addItem("Мадонна");
    ui->cbxPerson->addItem("Чингисхан");
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

