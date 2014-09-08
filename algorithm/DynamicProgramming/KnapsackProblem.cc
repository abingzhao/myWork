/*******************************************************************************
    File        : KnapspackProblem.cc
    Description : Solve Knapsack Problem with Dynamic Programming
    Author      : abing0513

    Revision                   Change Log
    ----------    ---------    --------------------------------------------
    2014-08-31    abing0513    add 0-1 Problem and sovle

*******************************************************************************/

/*******************************************************************************
    Inlcude
*******************************************************************************/
#include <iostream>
#include <vector>
#include "../sort/Sort.hpp"

/*******************************************************************************
    namespace
*******************************************************************************/
using namespace std;

/*******************************************************************************
0-1 Knapsack Problem:

        我们有 n 种物品，物品 j 的重量为wj，价格为pj。
    我们假定所有物品的重量和价格都是非负的。背包所能承受的最大重量为W。
    如果限定每种物品只能选择0个或1个，则问题称为0-1背包问题。

        这是最基础的背包问题,特点是:每种物品仅有一件,可以选择放或不放。
    用子问题定义状态:即 F [i, v] 表示前 i 件物品恰放入一个容量为 v 的背包可以获得
    的最大价值。则其状态转移方程便是:
    F [i, v] = max{F [i − 1, v], F [i − 1, v − Ci] + Wi}


    F [0, 0..V ] ← 0
    for i ← 1 to N
        for v ← 0 to Ci − 1
            F [i, v] ← F [i − 1, v]
        for v ← Ci to V
            F [i, v] ← max{F [i − 1, v], F [i − 1, v − Ci] + Wi}

复杂度:
    
        以上方法的时间和空间复杂度均为 O(V N ),其中时间复杂度应该已经不能再优化
    了,但空间复杂度却可以优化到 O(V )。

*******************************************************************************/
// template <typename T>
int ZeroOneKnapsackSolution( int *wj, 
                             int *value, 
                             int  totNum,
                             int  packCapacity, 
                             std::vector<std::vector<int> >& valArray)
{
    valArray.assign(totNum+1,std::vector<int>(packCapacity+1,0));
    int maxVal = 0;
    for (int i = 1; i <= totNum; ++i)
    {
#if 0
        for(int v = 0; v < wj[i-1] - 1; ++v)
        {
            valArray[i][v] = valArray[i-1][v];
        }
        for (int v = wj[i-1]; v <= packCapacity; ++v)
        {
            valArray[i][v] = max(valArray[i-1][v], valArray[i-1][v-wj[i-1]] + value[i-1]);
            if(valArray[i][v] > maxVal)
                maxVal = valArray[i][v];
        }
#else
        for (int j = 0; j <= packCapacity; ++j)
        {
            if(j - wj[i-1] < 0)
                valArray[i][j] = valArray[i-1][j];
            else
            {
                valArray[i][j] =  max(valArray[i-1][j], valArray[i-1][j-wj[i-1]] + value[i-1]);
                if(valArray[i][j] > maxVal)
                    maxVal = valArray[i][j];
            }
        }
#endif
    }
    return maxVal;
}

int ZeroOneKnapsackSolution( int *wj, 
                             int *value, 
                             int  totNum,
                             int  packCapacity, 
                             std::vector<int>& valArray)
{
    valArray.assign(packCapacity+1,0);
    int maxVal = 0;
    for (int i = 0; i < totNum; ++i)
    {
        for (int v = packCapacity; v >= wj[i]; --v)
        {
            valArray[v] = max(valArray[v], valArray[v-wj[i]] + value[i]);
            if (valArray[v] > maxVal)
            {
                maxVal = valArray[v];
            }
        }
    }
    return maxVal;
}

int main(int argc, char const *argv[])
{
    const int totNum = 4;
    int wj[totNum]   = {7, 2, 3, 2};
    int cost[totNum] = {400, 150, 150, 120};
    int packCapacity = 8;

    std::vector<std::vector<int> > valArray;
    std::vector<int>  valArray1;
    int totalValue = ZeroOneKnapsackSolution(wj,cost,totNum,packCapacity,valArray);
    int totalValue1 = ZeroOneKnapsackSolution(wj,cost,totNum,packCapacity,valArray1);
    for (int i = 0; i < valArray.size(); ++i)
    {
        for (int j = 0; j < valArray[i].size(); ++j)
        {
            cout << "\t" << valArray[i][j];
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < valArray1.size(); ++i)
    {
        cout << "\t" << valArray1[i];
    }
    cout << endl;
    cout << totalValue << endl;
    cout << totalValue1 << endl;
    cout << "\nMain Finished" << endl;
    return 0;
}





