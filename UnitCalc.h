#ifndef _UNITCALC_H
#define _UNITCALC_H

#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <QPointF>
#include <QVector>

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

static void calcMaxMinPoint(const QVector<QPointF>& data, QPointF& max_point, QPointF& min_point)
{
    QPointF max (0,-10000000);
    QPointF min (0,10000000);

    for(int i = 0; i < data.size(); i++)
    {
        if(max.y() < data[i].y())
        {
            max = data[i];
        }
        if(min.y() > data[i].y())
        {
            min = data[i];
        }
    }
    max_point = max;
    min_point = min;
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


// 拟合圆计算
// 计算点到直线的距离
static double pointToLineDistance(const QPointF& p, const QPointF& line1, const QPointF& line2)
{
    double dx = line2.x() - line1.x();
    double dy = line2.y() - line1.y();
    double numerator = std::abs(dy * p.x() - dx * p.y() + line2.y() * line1.x() - line2.x() * line1.y());
    double denominator = std::sqrt(dx * dx + dy * dy);
    return numerator / denominator;
}
// 计算圆的中心
static QPointF calculateCenter(const std::vector<QPointF>& points)
{
    double sumX = 0, sumY = 0, sumXX = 0, sumYY = 0, sumXY = 0;
    for (const auto& p : points)
    {
        sumX += p.x();
        sumY += p.y();
        sumXX += p.x() * p.x();
        sumYY += p.y() * p.y();
        sumXY += p.x() * p.y();
    }

    double centerX = (sumXX * sumYY - sumXY * sumXY) / (sumXX + sumYY);
    double centerY = (sumYY * sumX - sumXY * sumX) / (sumXX + sumYY);

    return QPointF(centerX, centerY);
}

// 计算圆的半径
static double calculateRadius(const QPointF& center, const std::vector<QPointF>& points)
{
    double radius = std::numeric_limits<double>::max();
    for (const auto& p : points)
    {
        radius = std::min(radius, std::sqrt(std::pow(p.x() - center.x(), 2) + std::pow(p.y() - center.y(), 2)));
    }
    return radius;
}
// RANSAC算法求拟合圆的圆心
static QPointF fitCircleRANSAC(const std::vector<QPointF>& points,double& radius, double inlierThreshold = 1.0)
{
    const int minPoints = 3;
    const int maxIterations = 100;
    const double goodEnoughInliers = points.size() * 0.5;

    std::vector<int> bestInliers;
    QPointF bestCenter;
    double bestRadius = std::numeric_limits<double>::max();

    for (int iter = 0; iter < maxIterations; ++iter)
    {
        std::vector<QPointF> sample;
        for (int i = 0; i < minPoints; ++i)
        {
            int index = rand() % points.size();
            sample.push_back(points[index]);
        }

        QPointF center = calculateCenter(sample);
        double radius = calculateRadius(center, sample);

        std::vector<int> inliers;
        for (size_t i = 0; i < points.size(); ++i)
        {
            if (std::pow(points[i].x() - center.x(), 2) + std::pow(points[i].y() - center.y(), 2) <= std::pow(radius, 2) + inlierThreshold * inlierThreshold)
            {
                inliers.push_back(i);
            }
        }

        if (inliers.size() > bestInliers.size())
        {
            bestInliers = inliers;
            bestCenter = center;
            bestRadius = radius;
        }

        if (inliers.size() > goodEnoughInliers)
        {
            break;
        }
    }

    return bestCenter;
}
// 计算点的均值（中心）
static QPointF calculatePointsCenter(const std::vector<QPointF>& points)
{
    double sumX = 0, sumY = 0;

    for (const QPointF& point : points)
    {
        sumX += point.x();
        sumY += point.y();
    }

    double centerX = sumX / points.size();
    double centerY = sumY / points.size();

    return QPointF(centerX, centerY);
}
//// 计算平均值
//static double mean(const std::vector<QPointF>& points)
//{
//    double sumX = 0, sumY = 0;
//    for (const QPointF& p : points) {
//        sumX += p.x();
//        sumY += p.y();
//    }
//    return points.size() / 2.0;
//}

//// 计算拟合圆的中心
//static QPointF calculateCenter(const std::vector<QPointF>& points)
//{
//    double xMean = mean(points);
//    double yMean = mean(points);
//    double centerX = 0, centerY = 0;
//    double sumXX = 0, sumYY = 0, sumXY = 0;

//    for (const QPointF& p : points) {
//        sumXX += (p.x() - xMean) * (p.x() - xMean);
//        sumYY += (p.y() - yMean) * (p.y() - yMean);
//        sumXY += (p.x() - xMean) * (p.y() - yMean);
//    }

//    centerX = xMean - sumXY / sumXX;
//    centerY = yMean - (sumXX * sumYY - sumXY * sumXY) / (sumXX * sumXX + sumYY * sumYY);

//    return QPointF(centerX, centerY);
//}

//// 计算拟合圆的半径
//static double calculateRadius(const QPointF& center, const std::vector<QPointF>& points)
//{
//    double minDistance = std::numeric_limits<double>::max();
//    for (const QPointF& p : points)
//    {
//        double distance = std::sqrt((p.x() - center.x()) * (p.x() - center.x()) + (p.y() - center.y()) * (p.y() - center.y()));
//        minDistance = std::min(minDistance, distance);
//    }
//    return minDistance;
//}

#endif // UNITCALC_H
