/*******************************************************************************
    File        : TestLinAndSysEfficiency.cc
    Description : Test The Efficiency between stdlibrary and System Call
    Author      : abing0513

    Revision                   Change Log
    ----------    ---------    --------------------------------------------
    2014-09-07    abing0513    Change Log

*******************************************************************************/

/*******************************************************************************
    Include 
*******************************************************************************/
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "CodeTiming.h"
/*******************************************************************************
    namespace
*******************************************************************************/
using namespace std;





int main(int argc, char const *argv[])
{
    CodeTiming cc;
    cc.Start();
    char c = '\0';  
    int in = -1, out = -1;  
    //以只读方式打开数据文件  
    in = open("aa.dat", O_RDONLY);  
    //以只写方式创建文件，如果文件不存在就创建一个新的文件  
    //文件属主具有读和写的权限  
    out = open("copy_system_out.dat", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);  
    while(read(in, &c, 1) == 1)//读一个字节的数据  
        write(out, &c, 1);//写一个字节的数据  
  
    //关闭文件描述符  
    close(in);  
    close(out);  
    cc.EndAndPrint("copy_system_out");



    cc.Start();
    ifstream fin("aa.dat",ios::binary|ios::in);
    ofstream fout("copy_stdio_out.dat",ios::out|ios::binary);
    while(!fin.eof())
    {
        fin.read(&c,1);
        fout.write(&c,1);
    }
    fout.close();
    fin.close();
    cc.EndAndPrint("copy_stdio_out");


    cc.Start();
    char buff[1024];  
    int in2 = -1, out2 = -1;  
    int nread = 0;  
  
    in2 = open("aa.dat", O_RDONLY);  
    out2 = open("copy_system_out2.dat", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);  
    //一次读写1024个字节  
    while((nread = read(in2, buff, sizeof(buff))) > 0)  
        write(out2, buff, nread);  
  
    close(in2);  
    close(out2); 
    cc.EndAndPrint("copy_stdio_out2");

    std::cout << "\nMain Finished" << std::endl;
    return 0;
}
/*******************************************************************************
    Result:
        Run copy_system_out Takes :1.4347s
        Run copy_stdio_out Takes :0.023964s
        Run copy_system_out2 Takes :0.001724s
*******************************************************************************/