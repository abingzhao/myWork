#include <stdio.h>

int main(int argc, char const *argv[])
{
    char a[100];
    int flag = 0;
    int idx = 0;
    char c;
    scanf("%c",&c);
    while(c != '\n' && flag == 0)
    {
        switch(c)
        {
            case '(':
            case '[':
                a[idx++]=c;break;
            case ')':
                if (a[idx-1] == '(')
                {
                    a[idx-1] = '\0';
                    idx--;
                }
                else 
                    flag = 1;
                break;
            case ']':
                if (a[idx-1] == '[')
                {
                    a[idx-1] = '\0';
                    idx--;
                }
                else 
                    flag = 1;
                break;
        }
        scanf("%c",&c);
    }
    printf("%d\n", flag);
    return 0;
}