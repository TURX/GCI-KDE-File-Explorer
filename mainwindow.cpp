#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(400, 300));

    buildList();
}

void MainWindow::recPath(QString path) {
    ui->listWidget->addItem(path);
    if((!findDetail[path]) || QFileInfo(path).isFile()) return;
    foreach(QFileInfo subObj, QDir(path).entryInfoList()) {
        if(subObj.absoluteFilePath().contains(".") || subObj.absoluteFilePath() == path) continue;
        recPath(subObj.absoluteFilePath());
    }
}

void MainWindow::buildList() {
    ui->listWidget->clear();
    foreach (QFileInfo drive, QDir().drives()) {
        findDetail[drive.absoluteFilePath()] = true;
        recPath(drive.absoluteFilePath());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if(QFileInfo(item->text()).isFile()) return;
    findDetail[item->text()] = !findDetail[item->text()];
    buildList();
}
