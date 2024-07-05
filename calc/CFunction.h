#ifndef CFUNCTION_H
#define CFUNCTION_H

#include <cstdlib>
#include "SPLine.h"
#include "UnitData.h"

#define CALC_COUNT_MAX DetectSettings::instance().max_points_count()

class CFunction
{
protected:
//    std::vector<std::vector<double>> C;
    std::vector<std::vector<double>> C1;
    std::vector<std::vector<double>> x;
    std::vector<std::vector<double>> xx;
    std::vector<std::vector<double>> y_lvbo;
    std::vector<std::vector<double>> y;
    std::vector<std::vector<double>> somechannel_max;
    std::vector<double> somechannel_max1;
//    std::vector<double> somechannel_max2;
    std::vector<double> somechannel_max3;
    std::vector<double> somechannel_min1;
//    std::vector<double> somechannel_min2;
    std::vector<double> somechannel_min3;
    std::vector<std::vector<double>> somechannel_min;
    int tongdao_num = 0;
    long ioriginal_num = 0;
public:
    CFunction() = default;
    ~CFunction() = default;
    void Function(std::vector<std::vector<double>>& x, int n, long m)
    {
        C1 = std::vector<std::vector<double>>(80,std::vector<double>(CALC_COUNT_MAX,0));
        x  = std::vector<std::vector<double>>(2,std::vector<double>(CALC_COUNT_MAX,0));
        xx = std::vector<std::vector<double>>(2,std::vector<double>(CALC_COUNT_MAX,0));
        y_lvbo = std::vector<std::vector<double>>(2,std::vector<double>(CALC_COUNT_MAX,0));
        y  = std::vector<std::vector<double>>(2,std::vector<double>(CALC_COUNT_MAX,0));
        somechannel_max  = std::vector<std::vector<double>>(12,std::vector<double>(30,0));
        somechannel_max1.resize(12);
        somechannel_max3.resize(12);
        somechannel_min1.resize(12);
        somechannel_min3.resize(12);
        somechannel_max1.resize(12);
        somechannel_min  = std::vector<std::vector<double>>(12,std::vector<double>(30,0));
        this->x = x;
        this->tongdao_num = n;
        this->ioriginal_num = m;

    }

    std::vector<std::vector<double>> col_lip_1()
    {
        double y1temp = 0, y2temp = 0;
        int x1temp = 0, x2temp = 0;
        std::vector<std::vector<double>> V_1 (2 * 40, std::vector<double>(this->ioriginal_num,0));
        for (int i = 0; i < tongdao_num; i++)
        {
            for (long j = 0; j < this->ioriginal_num - 1; j++)
            {
                this->xx[i][j] = this->x[i][j + 1] - this->x[i][j];
            }
        }
        // DepthOfC = this->DepthOfCorrosion();
        for (int i = 0; i < this->tongdao_num-1; i++)
        {

            for (long line = 0; line < this->ioriginal_num; line++)
            {
                y1temp = std::abs(this->xx[i][line]);
                y2temp = std::abs(this->xx[i + 1][line]);
                x1temp = i * 40;
                x2temp = (i + 1) * 40 - 1;
                for (int j = 0; j < 20; j++)
                {
                    V_1[x1temp + j][line] = y1temp + j * (y2temp - y1temp) / 19;
                }
                // x1temp是第一个点，然后依次做差的19个点，再接着又是19个点，最后是x2temp为最后一个点
                // 所以就是在通道i与通道i+1之间插入38个点，xx[i, line]为起点，xx[i+1, line]位终点
                for (int m = 0; m < 20; m++)
                {
                    V_1[x2temp - m][line] = y2temp - (20 - m) * (y1temp - y2temp) / 19;
                }
            }

        }
        return V_1;
    }

    void defect(double p,std::vector<std::vector<double>>& C)
    {
        //double[,] xt = new double[12, 10000];
        double somechannel_sum = 0;
        double somechannel_mean[2];
        double somechannel_biaozhuncha_sum = 0;
        double somechannel_biaozhuncha [2];
        for (int i = 0; i < this->tongdao_num; i++)
        {
            for (long j = 0; j < this->ioriginal_num - 1; j++)
            {

                y_lvbo[i][j] = x[i][j + 1] - x[i][j];
                if (j < 25 || j > this->ioriginal_num - 1 - 25)  //去掉原始曲线前后各25个点
                {
                    //y_lvbo[i + u, j] = 0;
                }

            }
        }
        // 求平均值
        for (int i = 0; i < this->tongdao_num; i++)
        {
            for (int j = 0; j < this->ioriginal_num - 2; j++)
            {
                somechannel_sum = somechannel_sum + y_lvbo[i][j];
            }
            somechannel_mean[i] = somechannel_sum / (this->ioriginal_num - 2);
            somechannel_sum = 0;
        }
        //求标准差
        for (int i = 0; i < this->tongdao_num; i++)
        {
            for (int j = 0; j < this->ioriginal_num - 2; j++)
            {
                somechannel_biaozhuncha_sum = somechannel_biaozhuncha_sum + std::pow((y_lvbo[i][j] - somechannel_mean[i]), 2);
            }
            somechannel_biaozhuncha[i] = std::sqrt(somechannel_biaozhuncha_sum / (ioriginal_num - 2));
            somechannel_biaozhuncha_sum = 0;
        }
        for (int i = 0; i < this->tongdao_num; i++)
        {
            somechannel_max3[i] = somechannel_mean[i] + p * somechannel_biaozhuncha[i];          //求出阈值线的最大值
            somechannel_min3[i] = somechannel_mean[i] - p * somechannel_biaozhuncha[i];          //求出阈值线的最小值
            somechannel_max1[i] = somechannel_mean[i] + 3 * somechannel_biaozhuncha[i];
            somechannel_min1[i] = somechannel_mean[i] - 3 * somechannel_biaozhuncha[i];
        }
        for (int i = 0; i < this->tongdao_num; i++)
        {
            for (int j = 0; j < this->ioriginal_num - 2; j++)
            {
                if (y_lvbo[i][j] > somechannel_max3[i])
                {
                    y[i][j] = y_lvbo[i][j] - somechannel_max3[i]; // 差值Q1,Q4; Q1,Q4以上的点差值数组
                }
                if (y_lvbo[i][j] <= somechannel_min3[i])
                {
                    y[i][j] = somechannel_min3[i] - y_lvbo[i][j]; // 差值Q3,Q2; Q3,Q2以下的点差值数组
                }
                if (somechannel_min3[i] < y_lvbo[i][j] && y_lvbo[i][j] < somechannel_max3[i])
                {
                    //y[i, j] = 0;
                }
            }
        }

        double max = -10000000000;
        double min = 10000000000;
        double a = 0;
        double b = 0;
        for (int i = 0; i < this->ioriginal_num - 1; i++)
        {
            for (int j = 0; j < this->tongdao_num; j++)
            {
                if (y[j][i] > max)
                {
                    max = y[j][i]; // 求极大值
                }
                if (y[j][i] < min && y[j][i] > 0)
                {
                    min = y[j][i]; // 大于0 极小值
                }
            }
        }
        for (int i = 0; i < this->ioriginal_num - 1; i++)
        {
            for (int j = 0; j < this->tongdao_num; j++)
            {

                a = 5 * max / 4 - 25 * min / 4;
                b = 25 * min / 4 - 1 * max / 4;
                if (y[j][i] > 0)
                { y[j][i] = std::abs((-b + std::sqrt(std::abs(b * b - 4 * a * y[j][i]))) / (2 * a)); }
                else
                {
                    y[j][i] = y[j][i];
                }
            }
        }

        std::vector<std::vector<double>> B (this->tongdao_num * 40, std::vector<double>(this->ioriginal_num - 1,0));
        if (this->tongdao_num > 1)
        {
            for (int j = 0; j < this->ioriginal_num - 1; j++)
            {
                std::vector<double> X;
                std::vector<double> Y;
                X.resize(this->tongdao_num + 2);
                Y.resize(this->tongdao_num + 2);
                X[0] = 0;
                Y[0] = 0;
                for (int i = 0; i < this->tongdao_num; i++)
                {
                    X[i + 1] = i * 40 + 20;
                    Y[i + 1] = y[i][j];
                }
                X[this->tongdao_num + 1] = this->tongdao_num * 40 - 1;
                Y[this->tongdao_num + 1] = 0;
                SPLine sp;
                sp.Init(X, Y);
                for (int h = 0; h < (this->tongdao_num) * 40; h++)
                {
                    B[h][j] = sp.Interpolate(h);
                }
            }
        }
        if (this->tongdao_num == 1)
        {
            for (int j = 0; j < this->ioriginal_num - 1; j++)
            {
                for (int i = 0; i < 20; i++)
                {
                    B[i][j] = (y[0][j] - 0) * i / 20;
                    B[i + 20][j] = y[0][j] - (y[0][j] - 0) * i / 20;
                }
            }
        }

        //横向样条插值
        for (int i = 0; i < this->tongdao_num * 40; i++)
        {
            std::vector<double> X;
            std::vector<double> Y;
            X.resize(this->ioriginal_num);
            Y.resize(this->ioriginal_num);
            X[0] = 0;
            Y[0] = 0;
            for (int j = 0; j < this->ioriginal_num - 1; j++)
            {
                X[j + 1] = j * 5 + 2;
                Y[j + 1] = B[i][j];
            }
            X[this->ioriginal_num - 1] = (this->ioriginal_num - 1) * 5 - 1;
            Y[this->ioriginal_num - 1] = 0;
            SPLine sp;
            sp.Init(X, Y);
            for (int h = 0; h < (this->ioriginal_num - 1) * 5; h++)
            {
                C[i][h] = sp.Interpolate(h);
            }
        }
        for (int i = 0; i < this->tongdao_num * 40; i++)
        {
            for (int j = 0; j < (this->ioriginal_num - 1) * 5; j++)
            {
                if(j < 20 || j > (this->ioriginal_num - 1) * 5 - 20)
                {
                    C[i][j] = 0;
                }
                if (C[i][j] < 0)
                {
                    C[i][j] = 0;
                }
            }

        }

//        return C;
        //for (int i = 0; i < this->tongdao_num * 40; i++)
        //{
        //    for (int j = 0; j < (this->ioriginal_num - 1) * 5-1; j=j+1)
        //    {
        //        double ssum = 0;
        //        double mean = 0;
        //        for (int ii = 0; ii < j + 6; ii++)
        //        {
        //            ssum = ssum + C[i, ii];
        //        }
        //        mean = ssum / 6;
        //        for (int ii = 0; ii < j + 6; ii++)
        //        {
        //            if (C[i, ii] < mean)
        //            {
        //                C[i, ii] = mean;
        //            }
        //        }
        //    }
        //}
        //for (int i = 0; i < this->tongdao_num * 40; i++)
        //{
        //    for (int j = (int)((this->ioriginal_num - 1) * 5-1); j > 6; j=j-1)
        //    {
        //        double ssum = 0;
        //        double mean = 0;
        //        for (int ii = 0; ii > j - 6; ii--)
        //        {
        //            ssum = ssum + C[i, ii];
        //        }
        //        mean = ssum / 6;
        //        for (int ii = 0; ii > j - 6; ii--)
        //        {
        //            if (C[i, ii] < mean)
        //            {
        //                C[i, ii] = mean;
        //            }
        //        }

        //    }
        //}
        //C1[0, 0] = (C[0, 1] + C[1, 0] + C[1, 1]) / 3;
        //C1[0, (this->ioriginal_num - 1) * 5 - 1] = (C[0, (this->ioriginal_num - 1) * 5 - 2] + C[1, (this->ioriginal_num - 1) * 5 - 2] + C[1, (this->ioriginal_num - 1) * 5 - 1]) / 3;
        //C1[this->tongdao_num * 40 - 1, 0] = (C[this->tongdao_num * 40 - 2, 0] + C[this->tongdao_num * 40 - 2, 1] + C[this->tongdao_num * 40 - 1, 1]) / 3;
        //C1[this->tongdao_num * 40 - 1, (this->ioriginal_num - 1) * 5 - 1] = (C[this->tongdao_num * 40 - 2, (this->ioriginal_num - 1) * 5 - 1] + C[this->tongdao_num * 40 - 1, (this->ioriginal_num - 1) * 5 - 2] + C[this->tongdao_num * 40 - 2, (this->ioriginal_num - 1) * 5 - 2]);
        //for (int i = 1; i < this->tongdao_num * 40 - 1; i++)
        //{
        //    C1[i, 0] = (C[i - 1, 0] + C[i - 1, 1] + C[i, 1] + C[i + 1, 1] + C[i + 1, 0]) / 5;
        //    C1[i, (this->ioriginal_num - 1) * 5 - 1] = (C[i - 1, (this->ioriginal_num - 1) * 5 - 1] + C[i - 1, (this->ioriginal_num - 1) * 5 - 2] + C[i, (this->ioriginal_num - 1) * 5 - 2] + C[i + 1, (this->ioriginal_num - 1) * 5 - 2] + C[i + 1, (this->ioriginal_num - 1) * 5 - 1]) / 5;
        //}
        //for (int j = 1; j < (this->ioriginal_num - 1) * 5 - 1; j++)
        //{
        //    C1[0, j] = (C[0, j - 1] + C[0, j + 1] + C[1, j - 1] + C[1, j] + C[1, j + 1]) / 5;
        //    C1[this->tongdao_num * 40 - 1, j] = (C[this->tongdao_num * 40 - 1, j - 1] + C[this->tongdao_num * 40 - 1, j + 1] + C[this->tongdao_num * 40 - 2, j - 1] + C[this->tongdao_num * 40 - 2, j] + C[this->tongdao_num * 40 - 2, j + 1]) / 5;
        //}
        //for (int i = 1; i < this->tongdao_num * 40 - 1; i++)
        //{
        //    for (int j = 1; j < (this->ioriginal_num - 1) * 5 - 1; j++)
        //    {
        //        C1[i, j] = (C[i - 1, j - 1] + C[i - 1, j] + C[i - 1, j + 1] + C[i, j - 1] + C[i, j + 1] + C[i + 1, j - 1] + C[i + 1, j] + C[i + 1, j + 1]) / 8;
        //    }
        //}
        //for (int i = 0; i < this->tongdao_num * 40; i++)//
        //{
        //    for (long j = (this->ioriginal_num) * 5 - 1; j < 100; j--)
        //    {
        //        C1[i, j] = 0;
        //    }
        //}
        //return C1;

    }
    void calcMaxAndMin(std::vector<std::vector<double>>& data,double& max_ret,double& min_ret)
    {
        double max = -10000000;
        double min = 10000000;
        //找S最大、最小值
        for (int i = 0; i < data.size(); i++)
        {
            for (int j = 0; j < data[0].size(); j++)
            {
                data[i][j] = std::abs(data[i][j]);
                max = data[i][j] >= max ? data[i][j] : max;
                min = data[i][j] <= min ? data[i][j] : min;
            }
        }
        max = max == 0.0 ? 0.001 : max;
        max_ret = max;
        min_ret = min;
        qDebug()<<"max:"<<max<<" min:"<<min;
    }
};

#endif // CFUNCTION_H
