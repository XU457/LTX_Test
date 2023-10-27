#ifndef DBINTERNALHELPER_H
#define DBINTERNALHELPER_H

#include <iostream>
#include <vector>
#include <QString>
#include <QtSql/QSqlQuery>
#include <QSqlError>
#include <QtSql/QSqlDatabase>
#include <QVariant>
#include <QDebug>
#include "data.h"

class dbInternalHelper
{
private:
    QSqlDatabase lainDatabase;
public:

    dbInternalHelper();

    bool createDataBase();
    bool setUpTLDB();
    void addData(std::vector<Data>& dObjArr);
    void closeDB();
};

#endif // DBINTERNALHELPER_H
