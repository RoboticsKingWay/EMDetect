#ifndef DYNAMICFILTER_H
#define DYNAMICFILTER_H

#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

#define _THRESHOLD_SUM_  1.1
#define _THRESHOLD_MEAN_ 1.02

class DynamicFilter
{
private:
    std::vector<double> window;
    size_t window_size;
    double mean_ {0.};
    double sum_  {0.};
public:
    explicit DynamicFilter(size_t size) : window_size(size) {}

    void setWindowSize(size_t size)
    {
        window_size = size;
        window.clear();
    }

    bool filter(double value)//, double output)
    {
        if (window.size() < window_size)
        {
            window.push_back(value);
        }
        else
        {
            double sum = std::accumulate(window.begin(), window.end(), 0.0);
            double mean = sum / window.size();
            double variance = std::accumulate(window.begin(), window.end(), 0.0,
                                              [mean](double acc, double val) { return acc + (val - mean) * (val - mean); });
            variance /= window.size();

            window.erase(window.begin());
            window.push_back(value);

            double new_mean = (sum + value - window.front()) / window_size;
            double new_variance = std::accumulate(window.begin(), window.end(), 0.0,
                                                  [new_mean](double acc, double val) { return acc + (val - new_mean) * (val - new_mean); });
            new_variance /= window_size;

            double threshold = std::sqrt(variance + new_variance) * 2; // Adjust the threshold as needed

            if (std::abs(value - mean) > threshold)
            {
//                return value;
//                output = value;
                return true;
            }
            else
            {
//                return mean;
                return false;
            }
        }
//        output = value;
        return true;
    }
    bool filter_mean(double value)
    {
        if (window.size() < window_size)
        {
            window.push_back(value);
            return false;
        }
        double sum = std::accumulate(window.begin(), window.end(), 0.0);
        double mean = sum / window.size();
        if(std::abs(sum - sum_) > sum_ * _THRESHOLD_SUM_)
        {
            window.erase(window.begin());
            window.push_back(value);
        }
        return true;
    }
};

#endif // DYNAMICFILTER_H
