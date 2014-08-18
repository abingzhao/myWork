/*******************************************************************************
    File: sList.h

    Description: The Knuth-Morris-Pratt Algorithm in my own words 

    Revision History
    ----------    ---------    --------------------------------------------
    2014-08-08    abing0513    Done !
*******************************************************************************/


/*******************************************************************************
    INLCUDES
*******************************************************************************/
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <iterator>
using namespace std;

/*******************************************************************************
 * @brief 朴素匹配算法
 * @details 朴素匹配算法,思想就是将目标串S的第一个字符与模式串T的第一个字符进行匹配，
 *          若相等，则继续比较S的第二个字符和 T的第二个字符；若不相等，则比较S的第二
 *          个字符和P的第一个字符，依次比较下去，直到得出最后的匹配结果.又称为蛮力算
 *          法，该算法最大缺点就是字符匹配失败指针就要回溯，所以性能很低。
 *          该算法最坏情况下要进行 M*(N-M+1)次比较，时间复杂度为 O(M*N)
 * 
 * @param str 目标串
 * @param pattern 模式串
 * 
 * @return 字符串匹配成功起始位置,
 ******************************************************************************/
int SimpleStringSearch(const char* str, const char* pattern)
{
    assert(str != NULL  &&  pattern != NULL);

    int strLen     = strlen(str);
    int patternLen = strlen(pattern);
    if(strLen < patternLen)
        return -1;
#if 0
    int i = 0;
    int j = 0;
    for (; i < strLen - patternLen + 1;)
    {
        for (; j < patternLen; )
        {
            if(str[i+j] != pattern[j])
            {
                ++i;
                j = 0;
                break;
            }
            else
            {
                if(++j == patternLen)
                    return i;
            }
        }
    }
#else
    int strIdx     = 0;
    int patternIdx = 0;
    while(strIdx < strLen && patternIdx < patternLen)
    {
        if(str[strIdx] == pattern[patternIdx])
        {
            if((++patternIdx) == patternLen)
            {   
                return ++strIdx - patternIdx;
            }
            ++strIdx;
        }
        else
        {
            strIdx -= patternIdx - 1;
            patternIdx = 0; 
        }
    }

#endif
    return -1;
}
/*******************************************************************************
 *  “部分匹配”表(又叫做“失配函数”):
 *  
 *          表的作用是让算法无需多次匹配str中的任何字符。能够实现线性时间搜索的关键是
 *      在主串的一些字段中检查模式串的初始字段，我们可以确切地知道在当前位置之前的一个
 *      潜在匹配的位置。换句话说，在不错过任何潜在匹配的情况下，我们"预搜索"这个模式
 *      串本身并将其译成一个包含所有可能失配的位置对应可以绕过最多无效字符的列表。
 *          对于 pattern中 的任何位置，我们都希望能够查询那个位置前（不包括那个位置）
 *      有可能的 pattern 的最长初始字段的长度，而不是从 pattern[0] 开始失配的整个字
 *      段，这长度就是我们查找下一个匹配时回退的距离。因此T[i]是W的可能的适当初始字段
 *      同时也是结束于W[i - 1]的子串的最大长度。我们使空串长度是0。当一个失配出现在
 *      模式串的最开始，无法回退
 *
 *"部分匹配值"就是"前缀"和"后缀"的最长的共有元素的长度,以"ABCDABD"为例:
    
    －　"A"的前缀和后缀都为空集，共有元素的长度为0；

　　－　"AB"的前缀为[A]，后缀为[B]，共有元素的长度为0；

　　－　"ABC"的前缀为[A, AB]，后缀为[BC, C]，共有元素的长度0；

　　－　"ABCD"的前缀为[A, AB, ABC]，后缀为[BCD, CD, D]，共有元素的长度为0；

　　－　"ABCDA"的前缀为[A, AB, ABC, ABCD]，后缀为[BCDA, CDA, DA, A]，共有元素为"A"，长度为1；

　　－　"ABCDAB"的前缀为[A, AB, ABC, ABCD, ABCDA]，后缀为[BCDAB, CDAB, DAB, AB, B]，共有元素为"AB"，长度为2；

　　－　"ABCDABD"的前缀为[A, AB, ABC, ABCD, ABCDA, ABCDAB]，后缀为[BCDABD, CDABD, DABD, ABD, BD, D]，共有元素的长度为0
 

    建立表的算法的复杂度是 O(n)，其中 n 是 pattern 的长度。除去一些初始化的工作，
    所有工作都是在 while 循环中完成的，足够说明这个循环执行用了 O(n) 的时间，同时
    还会检查 pos 和 pos - cnd 的大小。在第一个分支里，pos - cnd 被保留，而 pos 与 
    cnd 同时递增，自然，pos 增加了。在第二个分支里，cnd 被 T[cnd] 所替代，即以上
    总是严格低于 cnd，从而增加了 pos - cnd。在第三个分支里，pos 增加了，而 cnd 没有，
    所以 pos 和 pos - cnd 都增加了。因为 pos ≥ pos - cnd，即在每一个阶段要么 pos 
    增加，要么 pos 的一个下界增加；所以既然此算法只要有 pos = n 就终止了，这个循环
    必然最多在 2n 次迭代后终止, 因为 pos - cnd 从 1 开始。因此建立表的算法的复杂度是 O(n)。
 
    algorithm kmp_table:
    input:
        an array of characters, pattern (the word to be analyzed)
        an array of integers, T (the table to be filled)
    output:
        nothing (but during operation, it populates the table)

    define variables:
        an integer, pos ← 2 (the current position we are computing in T)
        an integer, cnd ← 0 (the zero-based index in pattern of the next 
character of the current candidate substring)

    (the first few values are fixed but different from what the algorithm 
might suggest)
    let T[0] ← -1, T[1] ← 0

    while pos < length(pattern) do
        (first case: the substring continues)
        if pattern[pos - 1] = pattern[cnd] then
            let cnd ← cnd + 1, T[pos] ← cnd, pos ← pos + 1

        (second case: it doesn't, but we can fall back)
        else if cnd > 0 then
            let cnd ← T[cnd]

        (third case: we have run out of candidates.  Note cnd = 0)
        else
            let T[pos] ← 0, pos ← pos + 1


 ******************************************************************************/
void CalPartialMatchTable(const char *pattern, int *table)
{
    int patternLen = strlen(pattern);
    table[0] = -1;
    table[1] = 0;
    int pos = 2;
    int cnd = 0;
    while(pos < patternLen)
    {
        if(pattern[pos-1] == pattern[cnd])
        {
            // Forward Branch
            ++cnd;
            table[pos] = cnd;
            ++pos;
        }
        else if(cnd > 0)
        {
            // The Fall back Branch
            cout << "cnd = " << cnd << "\t";
            cnd = table[cnd];
            cout << "cnd = " << cnd << endl;
        }
        else
        {
            // reset The cnd Branch
            table[pos] = 0;
            ++pos;
        }
    }
}
/*******************************************************************************
 * @brief 克努斯-莫里斯-普拉特算法(KMP)
 * @details 通过运用对这个词在不匹配时本身就包含足够的信息来确定下一个匹配将在
 *          哪里开始的发现，从而避免重新检查先前匹配的字符。
 *          
 *  The  example descriped in [1] 
 *  contains all the elements of the algorithm. For the moment, we assume the 
 *  existence of a "partial match" table T, described above, which indicates 
 *  where we need to look for the start of a new match in the event that the 
 *  current one ends in a mismatch. The entries of T are constructed so that 
 *  if we have a match starting at str[m] that fails when comparing str[m + i] 
 *  to pattern[i], then the next possible match will start at index m + i - T[i] 
 *  in str (that is, T[i] is the amount of "backtracking" we need to do after 
 *  a mismatch). This has two implications: first, T[0] = -1, which indicates 
 *  that if pattern[0] is a mismatch, we cannot backtrack and must simply check
 *  the next character; and second, although the next possible match will begin 
 *  at index m + i - T[i], as in the example above(see [1]), we need not actually 
 *  check any of the T[i] characters after that, so that we continue searching 
 *  from pattern[T[i]]. The following is a sample pseudocode implementation of 
 *  the KMP search algorithm.
 *  
 *  algorithm kmp_search:
    
    input:
        an array of characters, str (the text to be searched)
        an array of characters, pattern (the word sought)
    output:
        an integer (the zero-based position in str at which pattern is found)

    define variables:
        an integer, m ← 0 (the beginning of the current match in str)
        an integer, i ← 0 (the position of the current character in pattern)
        an array of integers, T (the table, computed elsewhere)

    while m + i < length(str) do
        if pattern[i] = str[m + i] then
            if i = length(pattern) - 1 then
                return m
            let i ← i + 1
        else
            if T[i] > -1 then
                let m ← m + i - T[i], i ← T[i]
            else
                let i ← 0, m ← m + 1
            
    (if we reach here, we have searched all of str unsuccessfully)
    return the length of str
 *  
 *  
 *  [1] http://en.wikipedia.org/wiki/Knuth-Morris-Pratt_algorithm
 *******************************************************************************/
int KMPSearch(const char *str, const char *pattern)
{
    int strLen     = strlen(str);
    int patternLen = strlen(pattern);
    int strIdx     = 0;
    int patternIdx = 0;

    std::vector<int> table(patternLen, 0);
    CalPartialMatchTable(pattern, &table[0]);
    while(strIdx + patternIdx < strLen)
    {
        if(pattern[patternIdx] == str[strIdx + patternIdx])
        {
            if(++patternIdx == patternLen)
                return strIdx;
        }
        else
        {
            if(table[patternIdx] > -1)
            {
                strIdx += patternIdx - table[patternIdx];
                patternIdx = table[patternIdx];
            }
            else
            {
                patternIdx = 0;
                ++strIdx;
            }
        }
    }
}


int main(int argc, char const *argv[])
{

    string str("aaabac");
    string pp("abac");
    int table[7] = {0};
    CalPartialMatchTable(str.c_str(), table);
    copy(table, table+7, ostream_iterator<int>(cout,", "));
    cout<<endl;
    cout << SimpleStringSearch(str.c_str(),pp.c_str()) << endl;
    cout << KMPSearch(str.c_str(),pp.c_str()) << endl;
    cout << SimpleStringSearch(str.c_str(),"aab") << endl;
    cout << KMPSearch(str.c_str(),"aab") << endl;
    cout << "Main Finished!" << endl;
    return 0;
}