#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "helper.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_load_csv_clicked() {

    QString filePath = QFileDialog::getOpenFileName(nullptr, "Open File", QDir::homePath(), "CSV Files (*.csv);;All Files (*)");

    if (!filePath.isEmpty()) {
        fileN = filePath;
    } else {
        qDebug() << "No file selected.";
    }

    auto stringPtr = std::make_shared<std::string>(filePath.toStdString());
    DataParser sampleCSV = DataParser(stringPtr);
    auto csvData = sampleCSV.getCSVContent();

    array_size = csvData.size();

    for (int i = 1; i < array_size; i++) {

        // For invalid Times
        QString timeNow = QString::fromStdString(csvData[i][0]);
        QString formattedTime;
        QTime time;

        QStringList timeComponents = timeNow.split(" ")[0].split(":");
        if (timeComponents.length() == 3) {
            QString hour = timeComponents[0].trimmed();
            if (hour.length() == 1) {
                timeComponents[0] = "0" + hour;
            }
            formattedTime = timeComponents.join(":") + " " + timeNow.split(" ")[1];
            time = QTime::fromString(formattedTime, "hh:mm:ss AP");
            if (time.isValid()) {
                qDebug() << "Parsed time: " << time.toString("hh:mm:ss AP");
            } else {
                qDebug() << "Invalid time format: " << timeNow;
            }
        }

        Data data(time, std::stod(csvData[i][1]), std::stod(csvData[i][2]), stoint(csvData[i][3]), stoint(csvData[i][4]), stoint(csvData[i][5]), stoint(csvData[i][6]), csvData[i][7]);
        //qDebug() << QTime::fromString(QString::fromStdString(csvData[i][0]), "hh:mm:ss AP");
        objectArr.push_back(data);
    }

    showPopupMessage("INFO", "Loaded CSV Succesfully", QMessageBox::Information);
}


void MainWindow::on_sort_data_clicked() {

    std::sort(objectArr.begin(), objectArr.end(), [](const Data& obj1, const Data& obj2) {
        return obj1.time < obj2.time;
    });

    showPopupMessage("INFO", "CSV Sorted accordingly Succesfully", QMessageBox::Information);

    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(array_size);
    ui->tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->tableWidget->setHorizontalHeaderLabels(QString("Time;Latitude;Longitude;Course;kts;mph;AltitudeFeet;Reporting Faculty").split(";"));

    int row = 0;
    QTableWidgetItem *tmpItem;

    for (int j = 1; j < array_size - 1; j++) {
        auto &dObj = objectArr[j];
        std::cout << row << std::endl;

        std::vector<QString> colNames {dObj.time.toString(Qt::ISODate), QString::number(dObj.latitude), QString::number(dObj.langitude), QString::number(dObj.course), QString::number(dObj.kts), QString::number(dObj.mph), QString::number(dObj.altitudeFeet), QString::fromStdString(dObj.reportingFaculty)};
        int col = 0;

        for (int i = 0; i < 8; i++) {
            colNames[i] = (colNames[i].isEmpty()) ? "Empty" : colNames[i];
            tmpItem = new QTableWidgetItem(tr("%1").arg(colNames[i]));
            ui->tableWidget->setItem(row, col, tmpItem);
            col += 1;
        }
        row += 1;
    }
}


void MainWindow::on_write_json_clicked() {
    // Json conversion
    QJsonArray dataArr;

    std::cout << array_size << std::endl;
    std::cout << objectArr[1].latitude << std::endl;

    for (int i = 1; i < array_size - 1; i++) {
        QJsonObject dataJObj;
        dataJObj["Time"] = objectArr[i].time.toString(Qt::ISODate);
        dataJObj["Latitude"] = objectArr[i].latitude;
        dataJObj["Longitude"] = objectArr[i].langitude;
        dataJObj["Course"] = objectArr[i].course;
        dataJObj["kts"] = objectArr[i].kts;
        dataJObj["mph"] = objectArr[i].mph;
        dataJObj["AltitudeFeet"] = objectArr[i].altitudeFeet;
        dataJObj["Reporting_Faculty"] = QString::fromStdString(objectArr[i].reportingFaculty);
        dataArr.append(dataJObj);
        std::cout << i << std::endl;
    }

    QJsonDocument jsonDoc(dataArr);
    QByteArray jsonData = jsonDoc.toJson();

    QFile file("data.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonData);
        file.close();
        qDebug() << "Data saved!!";
    } else {
        qDebug() << "Failed to save!!";
    }

    showPopupMessage("INFO", "JSON created Succesfully", QMessageBox::Information);
}


void MainWindow::on_writeDB_clicked() {
    dbInternalHelper dbinter;

    if (!dbinter.createDataBase() || !dbinter.setUpTLDB()) {
        qDebug() << "[WARNING]: Database had some issue.";
    }

    // This is taking a bit of time we can also put this in a threadpool and devide the objectArr to processed on multiple threads
    dbinter.addData(objectArr);

    dbinter.closeDB();
    showPopupMessage("INFO", "Database Stored Succesfully", QMessageBox::Information);
}

void showPopupMessage(const QString& title, const QString& message, QMessageBox::Icon icon) {
    QMessageBox messageBox;
    messageBox.setIcon(icon);
    messageBox.setText(message);
    messageBox.setWindowTitle(title);
    messageBox.exec();
}
