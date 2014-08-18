#include   <string>   
#include   <iostream> 
#include   <string.h>  
#include   <stdio.h>
using   namespace   std;   

string& replace_all(string& str,const string& old_value,const string& new_value)   
{   
    while(true)  
    {
        string::size_type pos(0);   
        if((pos=str.find(old_value))!=string::npos)   
            str.replace(pos,old_value.length(),new_value);   
        else break;   
    }   
    return str;   
}   
string& replace_all_distinct(string& str,const string& old_value,const string& new_value)   
{   
    for(string::size_type   pos(0);   pos!=string::npos;   pos+=new_value.length())
    {   
        if( (pos=str.find(old_value,pos))!=string::npos )   
            str.replace(pos,old_value.length(),new_value);   
        else   break;   
    }   
    return   str;   
}   

//
void get_next(const char *str, int *next)  
{  
    for (int i = 0; i <sizeof(next) ; ++i)
     {
         next[i] = 0;
     } 
  
    int i = -1;
    int j = 0;
    int  PreOverlay;  
    next[0] = -1;  
  
    for(i=1; i<strlen(str); i++){  
        PreOverlay = next[i-1];  
          
        while(PreOverlay >= 0 && str[i] != str[PreOverlay+1]){  
            PreOverlay = next[PreOverlay];  
        }  
  
        if(str[i] == str[PreOverlay+1]){  
            next[i] = PreOverlay + 1;  
        }else{  
            next[i] = -1;  
        }  
    }  
}  
  
// 查询子串  
char* strreplace(char *str, const char *sub, const char *rep)
{  
    if(NULL==str || NULL==sub) return  str;
    int sub_l = strlen(sub);
    if(strlen(sub)>100) 
    {
        std::cout<<"\n*****the code no sport the \"\n"<<sub<<"\"\nSEARCH ,length overflow!\n\n";
    }
    int next[100] = {0};
    get_next(sub, next); 
    int idx_sub = 0;  
    int idx_str = 0;  
    while(idx_str <= strlen(str))
    {  
        if(idx_sub == strlen(sub))
        {
            for (int i = 0; i < sub_l; ++i)
            {
                str[idx_str-sub_l+i] = rep[i];
            }
            idx_sub = 0;
        }
        if(str[idx_str] == sub[idx_sub])
        {  
            idx_str++;  
            idx_sub++;  
        }else if(idx_sub == 0)
        {  
            idx_str++;  
        }else{  
            idx_sub = next[idx_sub - 1] + 1;  
        }

    }  
    
    return str;
}  


char *base64_encode(const char *data, const size_t len)
{
    //编码表
    const char EncodeTable[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    //返回值
    char *encode_str = malloc();
    unsigned char Tmp[4]={0};
    int LineLength=0;
    for(int i=0;i<(int)(len / 3);i++)
    {
        Tmp[1] = *data++;
        Tmp[2] = *data++;
        Tmp[3] = *data++;
        encode_str += EncodeTable[Tmp[1] >> 2];
        encode_str += EncodeTable[((Tmp[1] << 4) | (Tmp[2] >> 4)) & 0x3F];
        encode_str += EncodeTable[((Tmp[2] << 2) | (Tmp[3] >> 6)) & 0x3F];
        encode_str += EncodeTable[Tmp[3] & 0x3F];
        if(LineLength+=4,LineLength==76) {encode_str +="\r\n";LineLength=0;}
    }
    //对剩余数据进行编码
    int Mod=len % 3;
    if(Mod==1)
    {
        Tmp[1] = *data++;
        encode_str += EncodeTable[(Tmp[1] & 0xFC) >> 2];
        encode_str += EncodeTable[((Tmp[1] & 0x03) << 4)];
        encode_str += "==";
    }
    else if(Mod==2)
    {
        Tmp[1] = *data++;
        Tmp[2] = *data++;
        encode_str += EncodeTable[(Tmp[1] & 0xFC) >> 2];
        encode_str += EncodeTable[((Tmp[1] & 0x03) << 4) | ((Tmp[2] & 0xF0) >> 4)];
        encode_str += EncodeTable[((Tmp[2] & 0x0F) << 2)];
        encode_str += "=";
    }
    
    return encode_str ;
}
  
int  main()   
{   
    char ss[]= "ababababababababababababababababababababababababa";
    cout<<ss<<endl;
    cout<<endl<<strreplace(ss, "ababababababababababa", "ccccccccccccccccccccc")<<endl;
}   