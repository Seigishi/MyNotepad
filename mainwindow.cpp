#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    if(not_saved){
        int x=QMessageBox::question(this,"Save Changes","Do you wish to save your file",QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(x==QMessageBox::Yes){
            on_actionSave_triggered();
            ui->statusBar->showMessage("New form created",1500);
            not_saved=0;
        }else if(x==QMessageBox::No){
             ui->plainTextEdit->setPlainText("");
             ui->statusBar->showMessage("New form created",1500);
             not_saved=0;
        }
    }else{
        ui->statusBar->showMessage("You haven't added anything",2000);
    }
}

void MainWindow::on_actionOpen_triggered()
{

    if(not_saved){
        int x=QMessageBox::question(this,"Save Changes","Do you wish to save your file",QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(x==QMessageBox::Yes){
            on_actionSave_triggered();
            ui->statusBar->showMessage("New form created",1500);
            not_saved=0;
        }else if(x==QMessageBox::No){
             ui->plainTextEdit->setPlainText("");
             ui->statusBar->showMessage("New form created",1500);
             not_saved=0;
        }
    }
    QString fileName = QFileDialog::getOpenFileName(this,
           tr("Open Text"), "",
           tr("Text file (*.txt);;All Files (*)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
           return;
    QString txt;


    QTextStream in(&file);
    in.setAutoDetectUnicode(true);

    ui->plainTextEdit->setPlainText(in.readAll());

    ui->statusBar->showMessage("Form opened",1500);
}

void MainWindow::on_actionSave_triggered()
{
    qDebug()<<"check";
    QString txt = ui->plainTextEdit->toPlainText().toLatin1();
    ui->statusBar->showMessage("Form Saved",1500);
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save file"), "",
            tr("Text File (*.txt);;All Files (*)"));
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
           return;

    QTextStream out(&file);
    out << txt;
    qDebug()<<"Check Completed";

}

void MainWindow::on_plainTextEdit_textChanged()
{
    not_saved =1;
}
