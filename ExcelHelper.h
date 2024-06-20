#ifndef EXCELHELPER_H
#define EXCELHELPER_H

#include <QAxObject>
#include <QVector>
#include <QString>
#include <QMessageBox>
#include <windows.h>
#include "UnitData.h"

class ExcelHelper : public QObject
{
    Q_OBJECT
public:

    static ExcelHelper& getInstance()
    {
        static ExcelHelper instance;
        return instance;
    }

    bool saveDataToExcel(const QVector<double>& data, const QString& filePath)
    {
        QAxObject* excel = initExcel(filePath, true);
        if (!excel)
        {
            QMessageBox::critical(nullptr, "Error", "Failed to initialize Excel.");
            return false;
        }

        QAxObject* workbook = excel->querySubObject("Workbooks")->querySubObject("Add");
        QAxObject* worksheet = workbook->querySubObject("Worksheets")->querySubObject("Item(int)", 1);

        int row = 1;
        for (double value : data)
        {
            worksheet->querySubObject("Cells")->querySubObject("Item(int,int)", row, 1)->dynamicCall("Value(const QVariant&)", value);
            ++row;
        }

        workbook->dynamicCall("SaveAs(const QString&)", filePath);
        closeExcel(excel);

        return true;
    }
    bool saveDataToExcel(const QVector<ChinnelData>& data, const QString& filePath)
    {
        QAxObject* excel = initExcel(filePath, true);
        if (!excel)
        {
            QMessageBox::critical(nullptr, "Error", "Failed to initialize Excel.");
            return false;
        }

        QAxObject* workbook = excel->querySubObject("Workbooks")->querySubObject("Add");
        QAxObject* worksheet = workbook->querySubObject("Worksheets");
//        worksheet->querySubObject("Item", 1);
        QAxObject* activeWorksheet = worksheet->querySubObject("Item(int)", 1);

        int row = 1;
        for (ChinnelData value : data)
        {
            for(int i = 0; i < CH_NUM; i++)
            {
                QAxObject *cells = activeWorksheet->querySubObject("Cells");
                QAxObject *cell  = cells->querySubObject("Item(int,int)", row, 1 + i);
                cell->dynamicCall("Value(const QVariant&)", value.mag_data.data[i]);
//                delete cell;
//                delete cells;
            }
//            delete activeWorksheet;
            ++row;
        }

        workbook->dynamicCall("SaveAs(const QString&)", filePath);
        closeExcel(excel);

        return true;
    }
    bool readDataFromExcel(QVector<double>& data, const QString& filePath)
    {
        QAxObject* excel = initExcel(filePath);
        if (!excel)
        {
            QMessageBox::critical(nullptr, "Error", "Failed to initialize Excel.");
            return false;
        }

        QAxObject* workbook = excel->querySubObject("Workbooks")->querySubObject("Open(const QString&)", filePath);
        QAxObject* worksheet = workbook->querySubObject("Worksheets")->querySubObject("Item", 1);

        int rowCount = worksheet->querySubObject("UsedRange")->dynamicCall("Rows()").toInt();
        for (int row = 1; row <= rowCount; ++row)
        {
            QAxObject* cell = worksheet->querySubObject("Cells")->querySubObject("Item", row, 1);
            double value = cell->dynamicCall("Value()").toDouble();
            data.append(value);
        }

        closeExcel(excel);
        return true;
    }

private:
    ExcelHelper(QObject *parent = nullptr): QObject(parent)
    {

    }
    ~ExcelHelper() {}
    QAxObject* initExcel(const QString& filePath, bool saveAs = false)
    {
        CoInitializeEx(NULL, COINIT_MULTITHREADED);
        QAxObject* excel =  new QAxObject("Excel.Application");
        excel->setProperty("Visible", false);
        excel->setProperty("DisplayAlerts", false);

        if (saveAs)
        {
            QAxObject* workbook = excel->querySubObject("Workbooks")->querySubObject("Add");
            return excel;
        }
        else
        {
            QAxObject* workbook = excel->querySubObject("Workbooks")->querySubObject("Open(const QString&)", filePath);
            return excel;
        }
    }
    void closeExcel(QAxObject* excel)
    {
        if (excel)
        {
            excel->dynamicCall("Quit()");
            delete excel;
        }
        CoUninitialize();
    }
};

//Q_DECLARE_METATYPE(QAxObject)
#endif // EXCELHELPER_H
