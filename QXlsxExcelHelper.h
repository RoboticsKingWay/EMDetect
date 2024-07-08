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

    bool saveDataToExcel(int size,double sensitivity,QString lable,double length,const QVector<ChinnelData>& data, const QString& filePath)
    {
        if(filePath == "")
        {
            return false;
        }
        try
        {

            QXlsx::Document doc = QXlsx::Document(filePath);
            doc.write(1,1,"point_size");
            doc.write(1,2,"sensitivity");
            doc.write(1,3,"file_lable");
            doc.write(1,4,"scan_length/mm");

            doc.write(2,1,size);
            doc.write(2,2,sensitivity);
            doc.write(2,3,lable);
            doc.write(2,4,length);
    //        for(int j = 1; j <= CH_NUM; j++)
    //        {
                doc.write(3,1,"CH1");
                doc.write(3,2,"CH2");
                doc.write(3,3,"CH3");
                doc.write(3,4,"CH4");
                doc.write(3,5,"CH5");
                doc.write(3,6,"CH6");
    //        }
            for(int i = 0; i < data.size(); i++)
            {
                for(int j = 0; j < CH_NUM; j++)
                {
                    doc.write(i+4,j+1,data.at(i).mag_data.data[j]);//从第4行开始写入数据
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
    bool readDataFromExcel(double& sensitivity,QString& lable,double& length,QVector<ChinnelData>& data, const QString& filePath)
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
            int count_points = doc.read(2,1).toInt();
            sensitivity      = doc.read(2,2).toDouble();
            lable            = doc.read(2,3).toString();
            length           = doc.read(2,4).toDouble();
            for(int i = 0; i < count -1; i++)
            {
                ChinnelData item;
                item.index = ++index;
                for(int j = 0; j < CH_NUM; j++)
                {
                    item.mag_data.data[j] = doc.read(i+4,j+1).toInt();//从第4行开始读取数据
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
