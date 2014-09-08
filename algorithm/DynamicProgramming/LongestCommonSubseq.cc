/*******************************************************************************
    File        : LongestCommonSubseq.cc
    Description : Solve LCS Problem with Dynamic Programming
    Author      : abing0513

    Revision                   Change Log
    ----------    ---------    --------------------------------------------
    2014-09-01    abing0513    New add ,Learn Principle, Try to commplete 
    2014-09-04    abing0513    Implement the Print of LCS sequence

*******************************************************************************/



/*******************************************************************************
    include
*******************************************************************************/
#include <iostream>
#include <cstring>
#include <vector>
#include "../sort/Sort.hpp"

/*******************************************************************************
    DEFINES
*******************************************************************************/
enum direction
{
    toUp = 0,
    toLeft,
    toInit,
};
using namespace std;
/*******************************************************************************
    Problem Description:

        如果字符串一的所有字符按其在字符串中的顺序出现在另外一个字符串二中，则字符串一
    称之为字符串二的子串。
    注意，并不要求子串（字符串一）的字符必须连续出现在字符串二中。
    
        请编写一个函数，输入两个字符串，求它们的最长公共子串，并打印出最长公共子串。例
    如：输入两个字符串BDCABA和ABCBDAB，字符串BCBA和BDAB都是是它们的最长公共子序列，则
    输出它们的长度4，并打印任意一个子序列。
*******************************************************************************/
/*******************************************************************************
    Algorithm Description:

    Procedure LCS-LENGTH(X,Y);  
    begin  
      m:=length[X];  
      n:=length[Y];  
      for i:=1 to m do c[i,0]:=0;  
      for j:=1 to n do c[0,j]:=0;  
      for i:=1 to m do  
        for j:=1 to n do  
          if x[i]=y[j] then  
            begin  
              c[i,j]:=c[i-1,j-1]+1;  
              b[i,j]:="↖";  
            end  
          else if c[i-1,j]≥c[i,j-1] then  
            begin  
              c[i,j]:=c[i-1,j];  
              b[i,j]:="↑";  
            end  
          else  
            begin  
              c[i,j]:=c[i,j-1];  
              b[i,j]:="←"  
            end;  
      return(c,b);  
    end;  


    Procedure LCS(b,X,i,j);  
    begin  
      if i=0 or j=0 then return;  
      if b[i,j]="↖" then  
        begin  
          LCS(b,X,i-1,j-1);  
          print(x[i]); {打印x[i]}  
        end  
      else if b[i,j]="↑" then LCS(b,X,i-1,j)   
                          else LCS(b,X,i,j-1);  
    end;  
*******************************************************************************/
void GetLCSstr( std::vector<std::vector<direction> >& lcsD, 
                const char* strLhs, 
                int i, int j)
{
    if( i == 0 || j == 0)
        return;
    if(lcsD[i][j] == toInit)
    {
        GetLCSstr(lcsD, strLhs, i-1, j-1);
        cout << strLhs[i-1] << ", ";
    }
    else if (lcsD[i][j] == toUp )
    {
        GetLCSstr(lcsD, strLhs, i - 1, j);
    }
    else
    {
        GetLCSstr(lcsD, strLhs, i, j - 1);
    }
}

int LongestCommonSubseq(const char *strLhs, const char *strRhs, char *lcsStr)
{
    int lhsLen = strlen(strLhs);
    int rhsLen = strlen(strRhs);
    int lcs    = 0;
    std::vector<std::vector<int> > lcsLen(lhsLen+1,std::vector<int>(rhsLen+1,0));
    std::vector<std::vector<direction> > lcsD(lhsLen+1,std::vector<direction>(rhsLen+1));
    for (int i = 1; i <= lhsLen; ++i)
    {
        for (int j = 1; j <= rhsLen; ++j)
        {
            if(strLhs[i-1] == strRhs[j-1])
            {
                lcsLen[i][j] = lcsLen[i-1][j-1]+1;
                lcsD[i][j]   = toInit;
            }
            else if(lcsLen[i-1][j] >= lcsLen[i][j-1])
            {
                lcsLen[i][j] = lcsLen[i-1][j];
                lcsD[i][j]   = toUp;
            }
            else
            {
                lcsLen[i][j] = lcsLen[i][j-1];
                lcsD[i][j]   = toLeft;
            }
            if(lcsLen[i][j] > lcs)
                lcs = lcsLen[i][j];
        }
    }
    cout << "The LCS is :\n\t";
    GetLCSstr(lcsD, strLhs, lhsLen, rhsLen);
    cout << endl;
    return lcs;
}

int main(int argc, char const *argv[])
{
    const char* s1 = "13455";
    const char* s2 = "245576";
    char *ss;

    cout << "The Length is : \n\t" << LongestCommonSubseq(s1,s2,ss) << endl;
    
    std::cout << "\nMain Finished" << std::endl;
    return 0;
}



