#ifndef _UNITCALC_H
#define _UNITCALC_H

#include <iostream>
#include <cmath>
#include <vector>
#include <utility>

// 差分
static void centralDifference(const std::vector<int>& data, std::vector<int>& result,int order = 2)
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
static double calAverage(const std::vector<int>& array)
{
    double sum = 0.0;
    for(int i = 0; i < array.size(); i++)
    {
        sum += array[i];
    }
    return sum / array.size();
}

// 标准差
static double calculateStandardDeviation(const std::vector<int>& data)
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
static void calcThreshold(double aver, double standar_diff, double sensitivity, double& max, double& min)
{
    max = aver + sensitivity * standar_diff;
    min = aver - sensitivity * standar_diff;
}

//
static void calcMaxAndMin(const std::vector<std::vector<int>>& data,int& max_ret,int& min_ret)
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

static void calcMaxMin(const std::vector<int>& data,int& max_ret,int& min_ret)
{
    int max = -10000000;
    int min = 10000000;
    for(int i = 0; i < data.size(); i++)
    {
        max = std::max(data[i],max);
        min = std::min(data[i],min);
    }
    max_ret = max;
    min_ret = min;
}

static void calcThresholdDistance(const std::vector<std::vector<int>>& data,int& max_ret,int& min_ret,std::vector<std::vector<int>>& distance_list)
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

// 计算两点之间的距离
static double distance(const std::pair<double, double>& p1, const std::pair<double, double>& p2)
{
    return std::sqrt((p2.first - p1.first) * (p2.first - p1.first) + (p2.second - p1.second) * (p2.second - p1.second));
}

// 最小二乘法线性回归
static std::pair<double, double> leastSquares(const std::vector<std::pair<double, double>>& points)
{
    if (points.size() < 3)
    {
        throw std::invalid_argument("At least two points are required for regression.");
    }

    double n = points.size();
    double sum_x = 0, sum_y = 0, sum_xx = 0, sum_xy = 0;

    for (const auto& point : points)
    {
        sum_x += point.first;
        sum_y += point.second;
        sum_xx += point.first * point.first;
        sum_xy += point.first * point.second;
    }

    double x_mean = sum_x / n;
    double y_mean = sum_y / n;

    double numerator = (n * sum_xy) - (sum_x * sum_y);
    double denominator = (n * sum_xx) - (sum_x * sum_x);

    if (denominator == 0)
    {
        throw std::runtime_error("Denominator is zero, cannot calculate slope.");
    }

    double slope = numerator / denominator;
    double intercept = y_mean - (slope * x_mean);

    return {slope, intercept};
}


#endif // UNITCALC_H
