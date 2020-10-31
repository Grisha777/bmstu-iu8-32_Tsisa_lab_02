#include <iostream>
#include "cmake-build-debug/TextTable.h"
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;
const double Right_limit = 1.5;
const double Left_limit=-2.5;

double Function(double x)
{
    return -0.5*cos(0.5*x)+1;
}
double Function1(double x)
{
    return Function(x)*sin(5*x);
}
double Probability(double P, double q)
{
    double numerator = log(1 - P);
    double denominator = log(1 - q);
    return (numerator / denominator);
}
double Function2(double function(double x), double N, int Left_limit, int Right_limit)
{
    double delta = (Right_limit - Left_limit) / N;
    double min = Left_limit + delta;
    for (size_t i = 2; i <= N; ++i)
    {
        double max = Left_limit + delta * i;
        if (function(min) < function(max))
        {
            continue;
        }
        else
            {
            min = max;
        }
    }
    return min;
}
template<typename T>
void Print(vector<vector<T>>& value)
{
    TextTable table('-', '|', '+');
    table.add("P/q");
    for (double p = 0.9; p < 1; p += 0.01)
    {
        table.add(to_string(p));
    }
    table.endOfRow();
    table.setAlignment(2, TextTable::Alignment::LEFT);
    for (double i = 0, q = 0.005; i < 20; ++i, q+=0.005)
    {
        table.add(to_string(q));
        for (size_t j = 0; j < 10; ++j)
        {
            T temp = value[j][i];
            table.add(to_string(temp));
        }
        table.endOfRow();
        table.setAlignment(2, TextTable::Alignment::LEFT);
    }
    cout << table;
}
void random_search(double function(double x), int Left_limit, int Right_limit)
{
    vector<vector<double>> result(10);
    vector<vector<int>> dependents(10);
    double P = 0.9;
    for (size_t i = 0; i < 10; ++i)
    {
        double q = 0.005;
        for (size_t j = 0; j < 20;  ++j)
        {
            double N = Probability(P, q);
            dependents[i].push_back(floor(N));
            result[i].push_back(Function2(function, N, Left_limit, Right_limit));
            q += 0.005;
        }
        P += 0.01;
    }
    cout << "Dependence of N on q" << endl;
    Print(dependents);
    cout << endl;
    cout << "Extremum search results Function depending on P and q" << endl;
    Print(result);
}

int main()
{
    cout<<"Variant 9"<<endl<<"Function: f(x)=-0.5*cos(0.5*x)+1"<<string(3,' ')<< "interval: [-2.5,1.5]"<<endl<<endl;
    random_search(Function, Left_limit, Right_limit);
    cout<<endl;
    cout<<"Function1: f(x)=Function(x)*sin(5x)"<<string(3,' ')<< "interval: [-2.5,1.5]"<<endl<<endl;
    random_search(Function1, Left_limit, Right_limit);
}

