#ifndef QXLSXEXCELHELPER_H
#define QXLSXEXCELHELPER_H

#include <QObject>
#include <QVector>
#include <iostream>
#include <QMessageBox>
#include "UnitData.h"
#include "xlsxdocument.h"
#include "xlsxworkbook.h"
#include "xlsxworksheet.h"
#include "xlsxcell.h"

class QXlsxExcelHelper : public QObject
{
    Q_OBJECT
public:
    static QXlsxExcelHelper& getInstance()
    {
        static QXlsxExcelHelper instance;
        return instance;
    }

    bool saveDataToExcel(const QVector<ChinnelData>& data, const QString& filePath)
    {
        if(filePath == "")
        {
            return false;
        }
        try
        {

            QXlsx::Document doc = QXlsx::Document(filePath);
    //        for(int j = 1; j <= CH_NUM; j++)
    //        {
                doc.write(1,1,"CH1");
                doc.write(1,2,"CH2");
                doc.write(1,3,"CH3");
                doc.write(1,4,"CH4");
                doc.write(1,5,"CH5");
                doc.write(1,6,"CH6");
    //        }
            for(int i = 0; i < data.size(); i++)
            {
                for(int j = 0; j < CH_NUM; j++)
                {
                    doc.write(i+2,j+1,data.at(i).mag_data.data[j]);
                }
            }
            doc.save();
            return true;
        }
        catch (const std::exception &e)
        {
            qDebug() << "saveDataToExcel Exception occurred: " << e.what();
        }
    }
    bool readDataFromExcel(QVector<ChinnelData>& data, const QString& filePath)
    {

        int count = 0;
        int index = 0;
        if(filePath == "")
        {
            return false;
        }
        try
        {
            QXlsx::Document doc = QXlsx::Document(filePath);
            QXlsx::Workbook *wb  = static_cast<QXlsx::Workbook*>(doc.sheet("Sheet1")->workbook());
            QXlsx::Worksheet *workSheet = nullptr;
            if(wb)
            {
                workSheet = static_cast<QXlsx::Worksheet*>(wb->sheet(0));
                if(workSheet)
                {
                    count = workSheet->dimension().rowCount();
                }
            }
            else
            {
                QMessageBox::critical(nullptr, "Error", "work Sheet1 not exist!");
                return false;
            }
            for(int i = 0; i < count; i++)
            {
                ChinnelData item;
                item.index = ++index;
                for(int j = 0; j < CH_NUM; j++)
                {
                    item.mag_data.data[j] = doc.read(i+2,j+1).toInt();
                }
                data.append(item);
            }
            doc.save();
            return true;
        }
        catch (const std::exception &e)
        {
            qDebug() << "readDataFromExcel Exception occurred: " << e.what();
        }
    }
private:
    QXlsxExcelHelper(QObject *parent = nullptr): QObject(parent)
    {

    }
    virtual ~QXlsxExcelHelper() {}
};

#endif // QXLSXEXCELHELPER_H
