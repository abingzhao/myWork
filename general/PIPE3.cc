#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int data_processed = 0;
    int pipes[2];
    const char data[] = "123";
    pid_t pid;

    if(pipe(pipes) == 0)
    {
        pid = fork();
        if(pid == -1)
        {
            fprintf(stderr, "Fork failure!\n");
            exit(EXIT_FAILURE);
        }
        if(pid == 0)
        {
            //子进程中
            //使标准输入指向fildes[0]
            close(0);
            dup(pipes[0]);
            //关闭pipes[0]和pipes[1]，只剩下标准输入
            close(pipes[0]);
            close(pipes[1]);
            //启动新进程od
            execlp("od", "od", "-c", 0);
            exit(EXIT_FAILURE);
        }
        else
        {
            //关闭pipes[0],因为父进程不用读取数据
            close(pipes[0]);
            data_processed = write(pipes[1], data, strlen(data));
            //写完数据后，关闭pipes[1]
            close(pipes[1]);
            printf("%d - Wrote %d bytes\n", getpid(), data_processed);
        }
    }
    exit(EXIT_SUCCESS);
}