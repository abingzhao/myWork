
#include <ctime>
#include <complex>
#include <vector>
#include <iostream>
#include <fstream>

int main(void)
{
	FILE* ff;
	float data[100];
	std::vector<std::complex<float> > cc;
	ff = fopen("../../data_ays/cell_dui_dao_cuo.dat", "rb");
	while(!feof(ff))
	{
		int rr = fread(data, sizeof(float), 100, ff);
		if(rr < 100) break;
		for(int j = 0; j < 50; ++j) {
			cc.push_back(std::complex<float>(data[2*j], data[2*j+1]));
		}
	}
	std::ofstream file("../../octave/data.txt");
	for(int i = 1920000*1; i < 1920000*2; ++i) {
		std::complex<float> sum = 0;
		std::complex<float> aaa = 0;
		std::complex<float> bbb = 0;
		for(int j = 0; j < 9; ++j)
		{
			sum = sum + cc[i+j]*std::conj(cc[i+j+128]);
			aaa = aaa + cc[i+j]*std::conj(cc[i+j]);
			bbb = bbb + cc[i+j+128]*std::conj(cc[i+j+128]);
		}
		file<< (std::abs(sum)*std::abs(sum)) / (std::abs(aaa)*std::abs(bbb)) <<std::endl;
		//std::cout << i << "," << (std::abs(sum)*std::abs(sum)) / (std::abs(aaa)*std::abs(bbb)) << std::endl;
	}
	fclose(ff);
	file.close();
	return 0;
}





