#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dataparser.h"
#include <QFileDialog>
#include <QtDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include "dbinternalhelper.h"
#include "data.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString fileN;
    std::vector<Data> objectArr;
    int array_size;

private slots:
    void on_load_csv_clicked();
    void on_sort_data_clicked();
    void on_write_json_clicked();
    void on_writeDB_clicked();

private:
    Ui::MainWindow *ui;
};

void showPopupMessage(const QString& title, const QString& message, QMessageBox::Icon icon);
#endif // MAINWINDOW_H
