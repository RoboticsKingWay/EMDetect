#ifndef CHASING_H
#define CHASING_H

#include <iostream>
#include <vector>
#include <cmath> // 包含cmath头文件以使用std::isinf

class Chasing
{
protected:
    int N;//Dimension of Martrix Ax=d;
    std::vector<double> d;//Ax=d;
    std::vector<double> Aa;//a in A;
    std::vector<double> Ab; //b in A:
    std::vector<double> Ac;// c in A;
    std::vector<double> L;//LU-->L;
    std::vector<double> U;//LU-->U;
    std::vector<double> S;//store the result;
public:
    //constructor without parameters;
     Chasing()
    {

    }
    ~Chasing()
    {

    }
    bool Init(std::vector<double> a, std::vector<double> b, std::vector<double> c, std::vector<double> d)
    {
        //check validation of dimentions;
        int na = a.size();
        int nb = b.size();
        int nc = c.size();
        int nd = d.size();
        if (nb < 3)
        {
            return false;
        }
        this->N = nb;
        if (na != this->N - 1 || nc != this->N - 1 || nd != this->N)
        {
            return false;
        }
        this->S.resize(N);
        this->L.resize(N - 1);
        this->U.resize(N);
        this->Aa.resize(N - 1);
        this->Ab.resize(N);
        this->Ac.resize(N - 1);
        this->d.resize(N);
        //init Aa,Ab,Ac,Ad;
        for (int i = 0; i <= this->N - 2; i++)
        {
            this->Ab[i] = b[i];
            this->d[i] = d[i];
            this->Aa[i] = a[i];
            this->Ac[i] = c[i];
        }
        this->Ab[this->N - 1] = b[this->N - 1];
        this->d[this->N - 1]  = d[this->N - 1];
        return true;
    }
    bool Solve(std::vector<double>& R)
    {
        R.resize(this->Ab.size());
        /*********************A=LU***********************************/
        this->U[0] = this->Ab[0];
        for (int i = 2; i <= N; i++)
        {
            // L[i] = Aa[i] / U[i - 1];
            this->L[i - 2] = this->Aa[i - 2] / this->U[i - 2];
            //U[i]=Ab[i]-Ac[i-1]*L[i];
            this->U[i - 1] = this->Ab[i - 1] - this->Ac[i - 2] * L[i - 2];
        }
        /*************************END of A=LU **********************/
        /**************** Ly=d ******************************/
        std::vector<double> Y;
        Y.resize(this->d.size());
        Y[0] = this->d[0];

        for (int i = 2; i <= this->N; i++)
        {
            //Y[k]=d[k]-L[k]*Y[k-1];
            Y[i - 1] = this->d[i - 1] - (this->L[i - 2]) * (Y[i - 2]);

        }
        /**************** End of Ly=d ****************************/
        /*************** Ux=Y ********************************/
        //X[n]=Y[n]/U[n];
        R[this->N - 1] = Y[this->N - 1] / this->U[N - 1];
        //X[k]=(Y[k]-C[k]*X[k+1])/U[k];(n-1,,.....1)
        for (int i = this->N - 1; i >= 1; i--)
        {
            R[i - 1] = (Y[i - 1] - this->Ac[i - 1] * R[i]) / this->U[i - 1];
        }
        /*************** End of Ux=Y *************************/
        for (int i = 0; i < R.size(); i++)
        {
            if (std::isinf(R[i]) || std::isnan(R[i]))
            {
                return false;
            }
        }
        return true;
    }
};
#endif // CHASING_H
