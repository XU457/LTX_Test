#include "dbinternalhelper.h"

dbInternalHelper::dbInternalHelper() { }

bool dbInternalHelper::createDataBase() {
    bool db_status = false;
    lainDatabase = QSqlDatabase::addDatabase("QSQLITE", "TempDB");
    lainDatabase.setDatabaseName("userDB.db");

    db_status = (lainDatabase.open());
    //qDebug() << db_status;
    //lainDatabase.close();
    lainDatabase.commit();

    return db_status;
}

bool dbInternalHelper::setUpTLDB() {
    bool db_status = false;

    const QString setUpString1 = "CREATE TABLE IF NOT EXISTS Data ("
                                "      Time TEXT,"
                                "      Latitude DOUBLE,"
                                "      Longitude DOUBLE,"
                                "      Course INT,"
                                "      kts INT,"
                                "      mph INT,"
                                "      AltitudeFeet INT,"
                                "      Reporting_Facility TEXT"
                                ");";

    QSqlQuery query(lainDatabase);
    db_status = (query.exec(setUpString1));
    if (!db_status)
    {
        const QSqlError error = query.lastError();
        qDebug() << error.text();
    }

    qDebug() << db_status;
    lainDatabase.commit();

    return db_status;
}

void dbInternalHelper::addData(std::vector<Data>& dObjArr) {
    QString dbString = "";
    bool db_status = false;
    int iter = 0;
    for (auto& dObj : dObjArr) {
        dbString = "INSERT INTO Data VALUES(:time, :lat, :long, :course, :kts, :mph, :alt, :rFac);";
        QSqlQuery query(lainDatabase);
        query.prepare(dbString);
        query.bindValue(":time", dObj.time);
        query.bindValue(":lat", dObj.latitude);
        query.bindValue(":long", dObj.langitude);
        query.bindValue(":course", dObj.course);
        query.bindValue(":kts", dObj.kts);
        query.bindValue(":mph", dObj.mph);
        query.bindValue(":alt", dObj.altitudeFeet);
        query.bindValue(":rFac", QString::fromStdString(dObj.reportingFaculty));
        std::cout << iter << std::endl;
        iter += 1;

        query.exec();
    }
    lainDatabase.commit();
}

void dbInternalHelper::closeDB() {
    lainDatabase.close();
}
