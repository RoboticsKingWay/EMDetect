#ifndef UNITCALC_H
#define UNITCALC_H

#include <iostream>
#include <cmath>
#include <vector>

// 差分
void centralDifference(const std::vector<int>& data, std::vector<int>& result,int order = 2)
{
    int n = data.size();
    result.resize(n);

//    for(int i = 0; i < order; i++)
//    {
//        result[i] = data[i];
//    }
    for (int i = 0; i < n; ++i)
    {
        int sum = 0.0;
        int count = 0;

        for (int j = -order; j <= order; ++j)
        {
            if (i + j >= 0 && i + j < n)
            {
                sum += data[i + j];
                count++;
            }
        }

        result[i] = sum / count;
    }
}

// 均值
double calAverage(const std::vector<int>& array)
{
    double sum = 0.0;
    for(int i = 0; i < array.size(); i++)
    {
        sum += array[i];
    }
    return sum / array.size();
}

// 标准差
double calculateStandardDeviation(const std::vector<int>& data)
{
    double sum = 0.0;
    double mean = 0.0;
    double standardDeviation = 0.0;

    // Calculate the sum of the data
    for (int i = 0; i < data.size(); ++i)
    {
        sum += data[i];
    }

    // Calculate the mean value
    mean = sum / data.size();

    // Calculate the sum of squared differences from the mean
    for (int i = 0; i < data.size(); ++i)
    {
        standardDeviation += pow(data[i] - mean, 2);
    }

    // Calculate the variance and then the standard deviation
    double variance = standardDeviation / data.size();
    standardDeviation = sqrt(variance);

    return standardDeviation;
}

//阈值上下限
void calcThreshold(double aver, double standar_diff, double sensitivity, double& max, double& min)
{
    max = aver + sensitivity * standar_diff;
    min = aver - sensitivity * standar_diff;
}

//
void calcMaxAndMin(const std::vector<std::vector<int>>& data,int& max_ret,int& min_ret)
{
    int max = -10000000;
    int min = 10000000;
    for(int i = 0; i < data.size(); i++)
    {
        for(int j = 0; j < data[i].size(); j++)
        {
            max = std::max(data[i][j],max);
            min = std::min(data[i][j],min);
        }
    }
    max_ret = max;
    min_ret = min;
}

void calcThresholdDistance(const std::vector<std::vector<int>>& data,int& max_ret,int& min_ret,std::vector<std::vector<int>>& distance_list)
{
    int max = -10000000;
    int min = 10000000;
    for(int i = 0; i < data.size(); i++)
    {
        for(int j = 0; j < data[i].size(); j++)
        {
//            if(data[i][j])
        }
    }
}

#endif // UNITCALC_H
