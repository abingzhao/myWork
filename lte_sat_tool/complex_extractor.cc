#include <stdio.h>
#include <stdlib.h>
#include <complex>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 5) {
        printf("complex_extractor 文件名 sample_begin sample_count dst_file\n");
        return 0;
    }

    const char* sfilename = argv[1];
    const char* dfilename = argv[4];
    int samp_begin = atoi(argv[2]);
    int samp_count = atoi(argv[3]);
    FILE* fi = fopen(sfilename, "rb");
    FILE* fo = fopen(dfilename, "wb");
    if(!fi || !fo) {
        printf("open file error!\n");
        return 0;
    }
    fseek(fi, samp_begin*sizeof(complex<float>), SEEK_SET);
    complex<float>* arr = new complex<float>[samp_count];
    int read = fread(arr, sizeof(complex<float>), samp_count, fi);
    fwrite(arr, sizeof(complex<float>), read, fo);
    fclose(fi);
    fclose(fo);
    delete[] arr;
    return 0;
}