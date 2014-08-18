#include <iostream>
#include <cstring> // strlen,strcpy
#include <string>
#include <cstdlib>

const int    MAX_LENGTH          = 256;
const size_t BITS_IN_BYTES       = 8;
const size_t BITS_IN_BASE64_CODE = 6;
// unsigned int mystrlen(const char * const str)
// {
//     const char *char_ptr;  
//     const unsigned int *int_ptr;  
//     unsigned int intword, himagic, lomagic;  
  
//     // 
//     for (char_ptr = str; ((unsigned int) char_ptr  
//             & (sizeof (intword) - 1)) != 0;  
//         ++char_ptr)  
//     if (*char_ptr == '\0')  
//       return char_ptr - str;  
  
  
//     intword = (unsigned long int *) char_ptr;  
    

//   himagic = 0x80808080L;  
//   lomagic = 0x01010101L;  
//   if (sizeof (longword) > 4)  
//     {  
//       /* 64-bit version of the magic.  */  
//       /* Do the shift in two steps to avoid a warning if long has 32 bits.  */  
//       himagic = ((himagic << 16) << 16) | himagic;  
//       lomagic = ((lomagic << 16) << 16) | lomagic;  
//     }  
//   if (sizeof (longword) > 8)  
//     abort ();  
  
//    Instead of the traditional loop which tests each character, 
//      we will test a longword at a time.  The tricky part is testing 
//      if *any of the four* bytes in the longword in question are zero.    
//   for (;;)  
//     {  
//       longword = *longword_ptr++;  
  
//       if (((longword - lomagic) & ~longword & himagic) != 0)  
//     {  
//       /* Which of the bytes was the zero?  If none of them were, it was 
//          a misfire; continue the search.  */  
  
//       const char *cp = (const char *) (longword_ptr - 1);  
  
//       if (cp[0] == 0)  
//         return cp - str;  
//       if (cp[1] == 0)  
//         return cp - str + 1;  
//       if (cp[2] == 0)  
//         return cp - str + 2;  
//       if (cp[3] == 0)  
//         return cp - str + 3;  
//       if (sizeof (longword) > 4)  
//         {  
//           if (cp[4] == 0)  
//         return cp - str + 4;  
//           if (cp[5] == 0)  
//         return cp - str + 5;  
//           if (cp[6] == 0)  
//         return cp - str + 6;  
//           if (cp[7] == 0)  
//         return cp - str + 7;  
//         }  
//     }  
//     } 

// }

unsigned int  mystrlen(const char *str)
{
    if(NULL == str)
        return 0;
    unsigned int strLen = 0;
    const char* sptr = str;
    while('\0' != *str++)
        ++strLen;
    return strLen;
}

char *mystrncpy(char *dest, const char *src, int n)
{
    if (NULL == dest || NULL == src)
    {
        return 0;
    }
    const char *inptr = src;
    char *outptr = dest;
    while(--n >= 0)
        *outptr++ = *inptr++;
    return dest;
}
void getnext(const char *str, int *next)  
{  
    unsigned int strLen = mystrlen(str);
    for (int i = 0; i < strLen; ++i)
    {
        next[i] = 0;
    } 
  
    int i = -1;
    int j = 0;
    int  tmpNext;  
    next[0] = -1;  
  
    for(i=1; i<strlen(str); i++)
    {  
        tmpNext = next[i-1];  
          
        while(tmpNext >= 0 && str[i] != str[tmpNext+1])
            tmpNext = next[tmpNext];  
  
        if(str[i] == str[tmpNext+1])
            next[i] = tmpNext + 1;  
        else  
            next[i] = -1;  
    } 
}
char* strreplace(char *str, const char *sub, const char *rep)
{  
    if(NULL==str || NULL==sub) return  str;
    int subLen = mystrlen(sub);
    int strLen = mystrlen(str);
    if(subLen > MAX_LENGTH)
    {
        std::cout<<" "<<std::endl;
        return 0;
    }
    int next[MAX_LENGTH] = {0};
    getnext(sub, next); 
    int subIdx = 0;  
    int strIdx = 0;  
    while(strIdx <= strLen)
    {  
        if(subIdx == subLen)
        {
            for (int i = 0; i < subLen ; ++i)
            {
                str[strIdx-subLen +i] = rep[i];
            }
            mystrncpy(str - strIdx, rep, subLen);
            subIdx = 0;
        }
        if(str[strIdx] == sub[subIdx])
        {  
            ++strIdx;
            ++subIdx;
        }
        else if(subIdx == 0)
        {  
            ++strIdx;
        }
        else
        {  
            subIdx = next[subIdx - 1] + 1;
        }
    }  
    return str;
}  

const char *base64_encode(const char *data, const size_t len)
{
    const char codeTable[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string base64CodeWord;
    const char *codePtr    = data;
    unsigned char tmpCodeBytes[4]={0};
    int lineLength=0;
    for(int i=0;i<(int)(len / 3);i++)
    {
        tmpCodeBytes[1] = *codePtr++;
        tmpCodeBytes[2] = *codePtr++;
        tmpCodeBytes[3] = *codePtr++;
        base64CodeWord += codeTable[tmpCodeBytes[1] >> 2];
        base64CodeWord += codeTable[((tmpCodeBytes[1] << 4) | (tmpCodeBytes[2] >> 4)) & 0x3F];
        base64CodeWord += codeTable[((tmpCodeBytes[2] << 2) | (tmpCodeBytes[3] >> 6)) & 0x3F];
        base64CodeWord += codeTable[tmpCodeBytes[3] & 0x3F];
        if(lineLength+=4,lineLength==76) {base64CodeWord +="\r\n";lineLength=0;}
    }
    int Mod=len % 3;
    if(Mod==1)
    {
        tmpCodeBytes[1] = *codePtr++;
        base64CodeWord += codeTable[(tmpCodeBytes[1] & 0xFC) >> 2];
        base64CodeWord += codeTable[((tmpCodeBytes[1] & 0x03) << 4)];
        base64CodeWord += "==";
    }
    else if(Mod==2)
    {
        tmpCodeBytes[1] = *codePtr++;
        tmpCodeBytes[2] = *codePtr++;
        base64CodeWord += codeTable[(tmpCodeBytes[1] & 0xFC) >> 2];
        base64CodeWord += codeTable[((tmpCodeBytes[1] & 0x03) << 4) | ((tmpCodeBytes[2] & 0xF0) >> 4)];
        base64CodeWord += codeTable[((tmpCodeBytes[2] & 0x0F) << 2)];
        base64CodeWord += "=";
    }
    char * out = (char*)malloc(sizeof(char)*base64CodeWord.size());
    memcpy(out,base64CodeWord.c_str(),base64CodeWord.size());
    return out;
}

int main(int argc, char const *argv[])
{
    char aa[] = {'a','a','a','a','a','b'};//,'a','c'}; 
    char ss[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    // char bb[] = "abb";
    // char cc[] = "ccc";
    // std::cout<<ss<<endl;
    const char* oo = base64_encode(ss,mystrlen(ss));
    std::cout<<oo<<std::endl;
    // std::cout<<base64_encode(ss,mystrlen(ss))<<std::endl;
    return 0;
}
