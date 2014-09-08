/*******************************************************************************
    File        : PIPE1.cc
    Description : Pipe form popen() and pclose()
    Author      : abing0513

    Revision                   Change Log
    ----------    ---------    --------------------------------------------
    2014-09-08    abing0513    new add and implementation

*******************************************************************************/



/*******************************************************************************
    Inlcude 
*******************************************************************************/
#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
  
/*******************************************************************************
    很多时候，我们根本就不知道输出数据的长度，为了避免定义一个非常大的数组作为缓冲区，
    我们可以以块的方式来发送数据，一次读取一个块的数据并发送一个块的数据，直到把所有的
    数据都发送完。下面的例子就是采用这种方式的数据读取和发送方式。
*******************************************************************************/
int main()  
{  
    FILE *read_fp = NULL;  
    FILE *write_fp = NULL;  
    char buffer[BUFSIZ + 1];  
    int chars_read = 0;  
    //初始化缓冲区  
    memset(buffer, '\0', sizeof(buffer));  
    //打开ls和grep进程  
    read_fp = popen("ls -l", "r");  
    write_fp = popen("grep rwxrwxr-x", "w");  
    //两个进程都打开成功  
    if(read_fp && write_fp)  
    {  
        //读取一个数据块  
        chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);  
        while(chars_read > 0)  
        {  
            buffer[chars_read] = '\0';  
            //把数据写入grep进程  
            fwrite(buffer, sizeof(char), chars_read, write_fp);  
            //还有数据可读，循环读取数据，直到读完所有数据  
            chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);  
        }  
        //关闭文件流  
        pclose(read_fp);  
        pclose(write_fp);  
        exit(EXIT_SUCCESS);  
    }  
    exit(EXIT_FAILURE);  
}
/*******************************************************************************
    从运行结果来看，达到了信息筛选的目的。程序在进程ls中读取数据，再把数据发送到进程
    grep中进行筛选处理，相当于在shell中直接输入命令：ls -l | grep rwxrwxr-x。

    -rwxrwxr-x 1 abing abing    8636  9月  8 10:38 PIPE1
    -rwxrwxr-x 1 abing abing    8565  9月  7 22:48 test
    -rwxrwxr-x 1 abing abing    8872  9月  7 23:02 TestAlarmSignal
    -rwxrwxr-x 1 abing abing   84836  9月  7 21:51 TestLibAndSysEfficiency
    -rwxrwxr-x 1 abing abing    8574  9月  7 22:59 TestSysSignal

*******************************************************************************/