#include <stdio.h>
#include <string.h>
void string_math(const char *expression, char *result)
{
    if(NULL == expression)
        return;
    // int len = strlen(expression);
    // int space_count = 0;
    // for (int i = 0; i < len; ++i)
    // {
    //     if(' ' == expression[i] )
    //         ++space_count;
    // }
    // if (2 != space_count)
        // return;
    int lhs = 0;
    int rhs = 0;
    char operation[10];
    sscanf(expression,"%d %s %d", &lhs, operation, &rhs);
    printf("%d , rhs= %d\n", lhs, rhs);
    printf("%s\n", operation);
    switch(operation[0])
    {
        case '+' :
            sprintf(result,"%d",lhs+rhs);
            printf("%d\n", lhs+rhs);
            break;
        case '-' :
            sprintf(result,"%d",lhs-rhs);
            printf("%d\n", lhs-rhs);
            break;
        default  :return;
    }
}
int main(int argc, char const *argv[])
{
    char stt[20];
    char result[20];
    // scanf("%20s", stt);
    // gets(stt);
    // string_math(stt,result);
    char a[] = "Hello";
    char b[] = "World";
    sprintf(stt,"%s", a);
    sprintf(stt,"%s", b);
    printf("%s\n", stt);
    // printf("%ld\n", strlen(&stt[0]));
    printf("Have Done!\n");
    return 0;
}