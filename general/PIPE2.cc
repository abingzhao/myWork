
/*******************************************************************************
    File        : PIPE2.cc
    Description : Pipe from pipe
    Author      : abing0513

    Revision                   Change Log
    ----------    ---------    --------------------------------------------
    2014-09-08    abing0513    new add and implementation

*******************************************************************************/

/*******************************************************************************
    inlude 
*******************************************************************************/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*******************************************************************************
    首先，我们在原先的进程中创建一个管道，然后再调用fork创建一个新的进程，
    最后通过管道在两个进程之间传递数据。
*******************************************************************************/
int main()
{
    int data_processed = 0;
    int filedes[2];
    const char data[] = "Hello pipe!";
    char buffer[BUFSIZ + 1];
    pid_t pid;
    //清空缓冲区
    memset(buffer, '\0', sizeof(buffer));

    if(pipe(filedes) == 0)
    {
        //创建管道成功
        //通过调用fork创建子进程
        pid = fork();
        printf("%d\n", pid);
        if(pid == -1)
        {
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }
        if(pid == 0)
        {
            //子进程中
            //读取数据
            data_processed = read(filedes[0], buffer, BUFSIZ);
            printf("Read %d bytes: %s\n", data_processed, buffer);
            exit(EXIT_SUCCESS);
        }
        else
        {
            //父进程中
            //写数据
            data_processed = write(filedes[1], data, strlen(data));
            printf("Wrote %d bytes: %s\n", data_processed, data);
            //休眠2秒，主要是为了等子进程先结束，这样做也只是纯粹为了输出好看而已
            //父进程其实没有必要等等子进程结束
            sleep(2);
            exit(EXIT_SUCCESS);
        }
    }
    exit(EXIT_FAILURE);
}