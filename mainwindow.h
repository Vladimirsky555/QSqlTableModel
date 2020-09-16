#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "data.h"
#include "dialog.h"
#include "model.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Model *M;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createUI();

private slots:
    void on_tableView_clicked(const QModelIndex &index);
    void on_addData_clicked();

signals:
    void sendIndextoModel(QModelIndex index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
