#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QFileDialog>
#include"fileManager.h"
#include<QStandardPaths>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

namespace global
{
QString directory;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_file_triggered()
{
    QString directory = QFileDialog::getExistingDirectory(this, "Create file", QStandardPaths::writableLocation(QStandardPaths::HomeLocation), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    FileManager::Create(directory);
    global::directory = directory + "Text document.txt";
}

void MainWindow::on_actionSave_triggered()
{
    if (global::directory != "")
    {
        try
        {
            QString text=ui->textEdit->toPlainText();
            FileManager::saveAs(global::directory, text);
        } catch (const std::runtime_error& e)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this,"Error","Seems like I can't save this file, do you want to chose new path?", QMessageBox::Yes | QMessageBox::No);
            if (QMessageBox::Yes)
                on_actionSave_as_triggered();
            else if (QMessageBox::No)
                delete ui;
        }
    }
    else
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Error","Seems like I can't save this file, do you want to chose new path?", QMessageBox::Yes | QMessageBox::No);
        if (QMessageBox::Yes)
            on_actionSave_as_triggered();
        else if (QMessageBox::No)
            delete ui;
    }
}

void MainWindow::on_actionOpen_file_triggered()
{
    global::directory = QFileDialog::getOpenFileName(this, "Open file", QStandardPaths::writableLocation(QStandardPaths::HomeLocation), "Text files (*.txt)");
    ui->textEdit->setPlainText(FileManager::open(global::directory));
    ui->textEdit->moveCursor(QTextCursor::End);
}

void MainWindow::on_actionSave_as_triggered()
{
    global::directory = QFileDialog::getSaveFileName(this, "Save txt", QStandardPaths::writableLocation(QStandardPaths::HomeLocation), "txt files (*.txt)");
    QString text=ui->textEdit->toPlainText();
    FileManager::saveAs(global::directory, text);
}
