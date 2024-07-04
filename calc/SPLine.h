#ifndef SPLINE_H
#define SPLINE_H
#include <iostream>
#include <vector>
#include "Chasing.h"

class SPLine
{
protected:
    std::vector<double> Xi;
    std::vector<double> Yi;
    std::vector<double> A;
    std::vector<double> B;
    std::vector<double> C;
    std::vector<double> H;
    std::vector<double> Lamda;
    std::vector<double> Mu;
    std::vector<double> G;
    std::vector<double> M;
    int N;//
    int n;//
public :
    SPLine()
    {
        N = 0;
        n = 0;
    }
    ~SPLine(){}
    bool Init(std::vector<double>& Xi, std::vector<double>& Yi)
    {
        if (Xi.size() != Yi.size())
        {
            return false;
        }
        if (Xi.size() == 0)
        {
            return false;
        }

        //根据给定的Xi,Yi元素的数目来确定N的大小。
        this->N = Xi.size();
        this->n = this->N - 1;

        //根据实际大小给各个成员变量分配内存
        A.resize(N - 1);
        B.resize(N);
        C.resize(N - 1);

        this->Xi.resize(N);
        this->Yi.resize(N);
        this->H.resize(N - 1);
        this->Lamda.resize(N - 1);
        this->Mu.resize(N - 1);
        this->G.resize(N);
        this->M.resize(N);
        //把输入数据点的数值赋给成员变量。
        for (int i = 0; i <= n; i++)
        {
            this->Xi[i] = Xi[i];
            this->Yi[i] = Yi[i];
        }
        /************ 求出hi,Lamda(i),Mu(i),gi *******************/
        GetH();
        GetLamda_Mu_G();
        GetABC();
        /***************** 调用追赶法求出系数矩阵M *********************/
        Chasing chase;
        chase.Init(A, B, C, G);
        chase.Solve(M);
        return true;
    }
public:
    void GetH()
    {
        //Get H first;
        for (int i = 0; i <= n - 1; i++)
        {
            H[i] = Xi[i + 1] - Xi[i];
        }
    }
    void GetLamda_Mu_G()
    {
        double t1, t2;
        for (int i = 1; i <= n - 1; i++)
        {
            Lamda[i] = H[i] / (H[i] + H[i - 1]);
            Mu[i] = 1 - Lamda[i];
            t1 = (Yi[i] - Yi[i - 1]) / H[i - 1];
            t2 = (Yi[i + 1] - Yi[i]) / H[i];
            G[i] = 3 * (Lamda[i] * t1 + Mu[i] * t2);
        }
        G[0] = 3 * (Yi[1] - Yi[0]) / H[0];
        G[n] = 3 * (Yi[n] - Yi[n - 1]) / H[n - 1];
        Mu[0] = 1;
        Lamda[0] = 0;
    }
    void GetABC()
    {
        for (int i = 1; i <= n - 1; i++)
        {
            A[i - 1] = Lamda[i];
            C[i] = Mu[i];
        }
        A[n - 1] = 1; C[0] = 1;
        for (int i = 0; i <= n; i++)
        {
            B[i] = 2;
        }
    }
    double fai0(double x)
    {
        double t1, t2;
        double s;
        t1 = 2 * x + 1;
        t2 = (x - 1) * (x - 1);
        s = t1 * t2;

        return s;
    }
    double fai1(double x)
    {
        double s;
        s = x * (x - 1) * (x - 1);
        return s;
    }
    double Interpolate(double x)     //interpolate插值
    {
        double s = 0;
        double P1, P2;
        double t = x;
        int iNum;

        iNum = GetSection(x);
        if (iNum == -1) //
        {
            iNum = 0;
            t = Xi[iNum];
            return Yi[0];
        }
        if (iNum == -999)//
        {
            iNum = n - 1;
            t = Xi[iNum + 1];
            return Yi[n];

        }
        P1 = (t - Xi[iNum]) / H[iNum];
        P2 = (Xi[iNum + 1] - t) / H[iNum];
        s = Yi[iNum] * fai0(P1) + Yi[iNum + 1] * fai0(P2) +
            M[iNum] * H[iNum] * fai1(P1) - M[iNum + 1] * H[iNum] * fai1(P2);
        return s;
    }
    int GetSection(double x)
    {
        int iNum = -1;
        // double EPS = 1.0e-6;
        if (x < Xi[0])
        {
            return -1;
        }
        if (x > Xi[N - 1])
        {
            return -999;
        }
        for (int i = 0; i <= n - 1; i++)
        {
            if (x >= Xi[i] && x <= Xi[i + 1])
            {
                iNum = i;
                break;
            }
        }
        return iNum;
    }
};

#endif // SPLINE_H
