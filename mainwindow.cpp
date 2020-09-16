#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Таблица учёта");

    M = new Model(this);
//    M->setEditStrategy(QSqlTableModel::OnFieldChange);
    createUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createUI()
{
    ui->tableView->setModel(M);

    connect(this, SIGNAL(sendIndextoModel(QModelIndex)),
            M, SLOT(acceptIndexfromView(QModelIndex)));

    ui->tableView->addActions(M->allActions);
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
//    ui->tableView->setColumnHidden(2, true);
    ui->tableView->setAlternatingRowColors(true);
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    emit sendIndextoModel(index);
}

void MainWindow::on_addData_clicked()
{
    M->addData();
}
