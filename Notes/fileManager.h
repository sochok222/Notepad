#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include<QString>
#include<QDebug>
#include<QFile>
#include<QDir>
#include<QMessageBox>
#include<QTextStream>

class FileManager
{
public:
    static void saveAs(QString directory, QString text)
    {
        QFile file(directory);
        try {
            if(!file.exists()){
                qDebug() << "Creating txt file: "<<directory;
            }else{
                qDebug() << directory<<": this file already exists";
            }
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
                QTextStream out(&file);
                out<<text;
                file.close();
            }
        } catch (std::exception e) {
            QMessageBox messageBox;
            messageBox.critical(0, "Error", "Can't create fie");
        }

    }

    static QString open(const QString& directory)
    {
        QFile file(directory);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox messageBox;
            messageBox.critical(0, "Error", "Can't open file!");
            return "";
        }
        QTextStream in(&file);
        QString text = in.readAll();
        file.close();
        return text;
    }

    static int Create(const QString& directory)
    {
        QString name = "Text document.txt";
        QFile file(directory + name);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&file);
            file.close();
            return 0;
        }
        else
        {
            return 1;
        }
    }
};
#endif // FILEMANAGER_H
