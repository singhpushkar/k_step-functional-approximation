#include <iostream>
#include<cmath>
#include<fstream>
#include<time.h>
#include<iomanip>

using namespace std;
double** calculateDandAforType0(double points[][2],double** A,int n);
double** calculateDandAforType1(double points[][2],double** A,int n);
void printfunctionSteps(int** parti,double points[][2],double** A,int k, int x);
int** CalculatePartitionMatrix(double** D,int K,int n, int type);


int main(int argc, char* argv[])
{
    int K,n,i,type;
    cin>>K>>type;
    cin>>n;
    double points[n][2];
    for(i=0;i<n;i++)
        cin>>points[i][0]>>points[i][1];
    if(K>=n)//treival case.
    {
        cout<<n;
        for(i=0;i<n;i++)
            cout<<endl<<points[i][0]<<" "<<points[i][1];
        return 0;
    }

    double** A = new double*[n];
    double** D;
    if(type==0)
        D = calculateDandAforType0(points,A,n);
    else
        D = calculateDandAforType1(points,A,n);
    int** parti = CalculatePartitionMatrix(D,K,n,type);
    cout<<K<<endl;

    printfunctionSteps(parti,points,A,K-1,n-1);
    return 0;
}

double** calculateDandAforType1(double points[][2],double** A,int n)
{
    int i,j;
    double** D = new double*[n];
    for(i=0;i<n;i++)
    {
        A[i] = new double[n];
        D[i] = new double[n];
    }
    double minval,maxval;

    for(i=0;i<n;i++)
    {
        A[i][i] = points[i][1];
        D[i][i] = 0;
        minval =points[i][1];
        maxval = points[i][1];
        for(j=i+1;j<n;j++)
        {
            if(points[j][1] < minval)
                minval = points[j][1];
            else if(points[j][1] > maxval)
                maxval = points[j][1];

            A[i][j] = (minval + maxval)/2;
            D[i][j] = (maxval - minval)/2;
        }
    }
    return D;
}

double** calculateDandAforType0(double points[][2],double** A,int n)
{
    int i,j;
    double** D = new double*[n];
    for(i=0;i<n;i++)
    {
        A[i] = new double[n];
        D[i] = new double[n];
    }
    double avg,sumsqfun;

    for(i=0;i<n;i++)
    {
        avg = points[i][1];
        sumsqfun = avg*avg;
        A[i][i] = avg;
        D[i][i] = 0;
        for(j=i+1;j<n;j++)
        {
            D[i][j]=0;
            avg = avg +(points[j][1]-avg)/(j-i+1);
            sumsqfun +=(points[j][1]*points[j][1]);
            D[i][j] = sumsqfun - (avg*avg)*(j-i+1);
            A[i][j] = avg;
        }

    }
    return D;
}

void printfunctionSteps(int** parti,double points[][2],double** A,int k, int x)
{
	
    if(k<0)
    {
        return;
    }
    int index = parti[k][x];
    printfunctionSteps(parti,points,A,k-1,index-1);
    cout<<points[index][0]<<" "<<A[index][x]<<endl;
}

int** CalculatePartitionMatrix(double** D,int K,int n,int type)
{
    //double error[K][n];
    double** error = new double*[K];
    double minierr,temp;
    int miniindex,i,j,x;
    int** parti = new int*[n];
    for(i=0;i<K;i++)
        parti[i] = new int[n];
////////////////////////////////////////////////////
    for(i=0;i<n;i++)
    {
        error[i] = new double[n];
        error[0][i] = D[0][i];
        parti[0][i] = 0;
    }

    for(i=1;i<K;i++)
    {
        error[i] = new double[n];
        error[i][i]=0;
        parti[i][i] = i;
        for(j=i+1;j<n;j++)
        {
            minierr = D[i][j];
            miniindex = i;
            for(x=i; x<j;x++)
            {
                if(type == 0)
                    temp = error[i-1][x]+D[x+1][j];
                else
                    temp = error[i-1][x] >D[x+1][j] ?error[i-1][x]:D[x+1][j];

                if(temp<minierr)
                {
                    minierr = temp;
                    miniindex = x+1;
                }
            }
            error[i][j] = minierr;
            parti[i][j] = miniindex;
        }
        //if(i>1)
           // delete error[i-2];
    }
    //cout<<"The error is :"<<error[K-1][n-1]<<endl;
    return parti;
}
