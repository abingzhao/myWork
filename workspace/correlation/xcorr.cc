/*
 * autoc.cc
 *
 *  Created on: 2013-11-2
 *      Author: abing
 */

// Not concern about the smart ptr for now
//#include "boost/shared_ptr.hpp"


#include "xcorr.h"
#include <cstring>
#include <stdexcept>
#include <iostream>



/*
 * Description : Calculate the autocorrelation of input sequence,default is not biased or unbiased
 * Parameter   : discrete_seq - input sequence with length seq_length and type float
 * 				 auto_corr    - output sequence with type float,the autocorrelation of discrete_seq
 * 				 seq_length   - the length of input sequence
 * */
void autoc(float *discrete_seq,float *auto_corr,unsigned int seq_length)
{
	for (unsigned int m=0;m<seq_length;m++)
	{
		float temp=0;
		for(unsigned int n=0;n<=seq_length-1 - m;n++)
		{
			temp +=discrete_seq [n + m] * discrete_seq[n];
		}
		if (0 == m)
		{
			auto_corr[seq_length - 1] = temp;
		}
		else
		{
			auto_corr[seq_length-1 + m] = temp;
			auto_corr[seq_length-1 - m] = temp;
		}
	}
}


/*
 * Description : Calculate the autocorrelation of input sequence,default is not biased or unbiased
 * Parameter   : discrete_seq - input sequence with length seq_length and type float
 * 				 auto_corr    - output sequence with type float,the autocorrelation of discrete_seq
 * 				 seq_length   - the length of input sequence
 * 				 option       - specifies a normalization option for the cross-correlation,
 * 				 				'biased': Biased estimate of the autocorrelation function
 * 				 				'unbiased': Unbiased estimate of the autocorrelation function
 * */
void autoc(float *discrete_seq,float *auto_corr,unsigned int seq_length,std::string option)
{
	if (option == "unbiased")
	{
		for (unsigned int m=0;m<seq_length;m++)
		{
			float temp=0;
			for(unsigned int n=0;n<=seq_length-1 - m;n++)
			{
				temp +=discrete_seq [n + m] * discrete_seq[n];
			}
			temp /= (seq_length-m);
			if (0 == m)
			{
				auto_corr[seq_length - 1] = temp;
			}
			else
			{
				auto_corr[seq_length-1 + m] = temp;
				auto_corr[seq_length-1 - m] = temp;
			}
		}
	}
	else if (option == "biased")
	{
		for (unsigned int m=0;m<seq_length;m++)
		{
			float temp=0;
			for(unsigned int n=0;n<=seq_length-1 - m;n++)
			{
				temp +=discrete_seq [n + m] * discrete_seq[n];
			}
			temp /= seq_length;
			if (0 == m)
			{
				auto_corr[seq_length - 1] = temp;
			}
			else
			{
				auto_corr[seq_length-1 + m] = temp;
				auto_corr[seq_length-1 - m] = temp;
			}
		}//end for
	}
	else
		throw std::invalid_argument("Invalid Arithmetic Mode option:Must be biased or unbiased");
}//end function


/*
 * Description : Calculate the autocorrelation of input sequence,default is not biased or unbiased
 * Parameter   : discrete_seq - input sequence with length seq_length and type complex<float>
 * 				 auto_corr    - output sequence with type complex<float>,the autocorrelation
 * 				 				of discrete_seq
 * 				 seq_length   - the length of input sequence
 * */
void autoc(complexf *discrete_seq,complexf *auto_corr,unsigned int seq_length)
{
	for (unsigned int m=0;m<seq_length;m++)
	{
		complexf temp=0;
		for(unsigned int n=0;n<=seq_length-1 - m;n++)
		{
			temp +=discrete_seq [n + m] *conj( discrete_seq[n]);
		}
		if (0 == m)
		{
			auto_corr[seq_length - 1] = temp;
		}
		else
		{
			auto_corr[seq_length-1 + m] = conj(temp);
			auto_corr[seq_length-1 - m] = (temp);
		}
	}
}


/*
 * Description : Calculate the autocorrelation of input sequence,default is not biased or unbiased
 * Parameter   : discrete_seq - input sequence with length seq_length and type complex<float>
 * 				 auto_corr    - output sequence with type complex<float>,the autocorrelation
 * 				 				of discrete_seq
 * 				 seq_length   - the length of input sequence
 * 				 option       - specifies a normalization option for the cross-correlation,
 * 				 				'biased': Biased estimate of the autocorrelation function
 * 				 				'unbiased': Unbiased estimate of the autocorrelation function
 * */
void autoc(complexf *discrete_seq,complexf *auto_corr,unsigned int seq_length,std::string option)
{
	if (option == "unbiased")
	{
		for (unsigned int m=0;m<seq_length;m++)
		{
			complexf temp=0;
			for(unsigned int n=0;n<=seq_length-1 - m;n++)
			{
				temp +=discrete_seq [n + m] *conj( discrete_seq[n]);
			}
			temp /= seq_length-m;
			if (0 == m)
			{
				auto_corr[seq_length - 1] = temp;
			}
			else
			{
				auto_corr[seq_length-1 + m] = conj(temp);
				auto_corr[seq_length-1 - m] = (temp);
			}
		}
	}
	else if (option == "biased")
	{
		for (unsigned int m=0;m<seq_length;m++)
		{
			complexf temp=0;
			for(unsigned int n=0;n<=seq_length-1 - m;n++)
			{
				temp +=discrete_seq [n + m] *conj( discrete_seq[n]);
			}
			temp /= seq_length;
			if (0 == m)
			{
				auto_corr[seq_length - 1] = temp;
			}
			else
			{
				auto_corr[seq_length-1 + m] = conj(temp);
				auto_corr[seq_length-1 - m] = (temp);
			}
		}
	}
	else
		throw std::invalid_argument("Invalid Arithmetic Mode option:Must be 'biased' or 'unbiased'!");
}


/*
 * Description : Calculate the cross-correlation of input sequences,default is not biased or unbiased
 * Parameter   : discrete_seq_x - first input sequence with type float
 * 				 discrete_seq_y - second input sequence with type float
 * 				 cross_corr     - output sequence with type float,the cross-correlation of input sequences
 *
 * */
void cross_c(	float 		*discrete_seq_x,
				float		*discrete_seq_y,
				float 		*cross_corr,
				unsigned int seq_length_x,
				unsigned int seq_length_y)
{
	/*
	 * Compare the length of the input sequences,if they were not equal,insert some zeros
	 * at the end of the shorter one
	 * */
	unsigned int seq_length = std::max(seq_length_x,seq_length_y);
	std::cout<<seq_length<<std::endl;
	float *temp_seq_x = new float[seq_length];
	float *temp_seq_y = new float[seq_length];
	for (unsigned int i=0;i<seq_length;i++)
	{
		if (i < seq_length_x)
			temp_seq_x[i] = discrete_seq_x[i];
		else
			temp_seq_x[i] = 0;
		if (i < seq_length_y)
			temp_seq_y[i] = discrete_seq_y[i];
		else
			temp_seq_y[i] = 0;
	}
	//Calculate cross-correlation
	
	for (unsigned int m=0;m<(2*seq_length-1);m++)
	{
		float temp = 0;
		// Corresponding to the index of cross-corr under zero
		if (m<seq_length-1)
		{
			for(unsigned int n=0;n<=seq_length-1 - (seq_length-1-m);n++)
				temp += temp_seq_x[n] * temp_seq_y[n+(seq_length-1-m)];
		}
		// Calculate the cross-correlation
		else
		{
			for(unsigned int n=0;n<=seq_length-1 - (m-(seq_length-1));n++)
				temp += temp_seq_x[n+(m-(seq_length-1))] * temp_seq_y[n];
		}
		cross_corr[m] = temp;
	}
	delete []temp_seq_x;
	delete []temp_seq_y;
}

/*
 * Description : Calculate the cross-correlation of input sequences
 * Parameter   : discrete_seq_x - first input sequence with type float
 * 				 discrete_seq_y - second input sequence with type float
 * 				 cross_corr     - float output sequence,the cross-correlation of input sequences
 * 				 seq_length_x   - the length of discrete_seq_x
 * 				 seq_length_y   - the length of discrete_seq_y
 * 				 option         - specifies a normalization option for the cross-correlation,
 * 				 				  'biased'  : Biased estimate of the autocorrelation function
 * 				 				  'unbiased': Unbiased estimate of the autocorrelation function
 *
 * */
void cross_c(	float 		*discrete_seq_x,
				float		*discrete_seq_y,
				float 		*cross_corr,
				unsigned int seq_length_x,
				unsigned int seq_length_y,
				std::string  option)
{
	/*
	 * Compare the length of the input sequences,if they were not equal,insert some zeros
	 * at the end of the shorter one
	 * */
	unsigned int seq_length = std::max(seq_length_x,seq_length_y);
	float *temp_seq_x = new float[seq_length];
	float *temp_seq_y = new float[seq_length];
	for (unsigned int i=0;i<seq_length;i++)
	{
		if (i < seq_length_x)
			temp_seq_x[i] = discrete_seq_x[i];
		else
			temp_seq_x[i] = 0;
		if (i < seq_length_y)
			temp_seq_y[i] = discrete_seq_y[i];
		else
			temp_seq_y[i] = 0;
	}
	//Calculate cross-correlation

	if (option == "unbiased")
	{
		for (unsigned int m=0;m<(2*seq_length-1);m++)
		{
			float temp = 0;
			// Corresponding to the index of cross-corr under zero
			if (m<seq_length-1)
			{
				for(unsigned int n=0;n<=seq_length-1 - (seq_length-1-m);n++)
					temp += temp_seq_x[n] * temp_seq_y[n+(seq_length-1-m)];
			}
			// Calculate the cross-correlation
			else
			{
				for(unsigned int n=0;n<=seq_length-1 - (m-(seq_length-1));n++)
					temp += temp_seq_x[n+(m-(seq_length-1))] * temp_seq_y[n];
			}
			temp /= m<seq_length-1 ? (m+1):(2*seq_length-1-m);
			cross_corr[m] = temp;
		}
	}

	else if (option == "biased")
	{
		for (unsigned int m=0;m<(2*seq_length-1);m++)
		{
			float temp = 0;
			// Corresponding to the index of cross-corr under zero
			if (m<seq_length-1)
			{
				for(unsigned int n=0;n<=seq_length-1 - (seq_length-1-m);n++)
					temp += temp_seq_x[n] * temp_seq_y[n+(seq_length-1-m)];
			}
			// Calculate the cross-correlation
			else
			{
				for(unsigned int n=0;n<=seq_length-1 - (m-(seq_length-1));n++)
					temp += temp_seq_x[n+(m-(seq_length-1))] * temp_seq_y[n];
			}
			temp /= seq_length;
			cross_corr[m] = temp;
		}
	}
	else
		throw std::invalid_argument("Invalid Arithmetic Mode option:Must be 'biased' or 'unbiased'!");
	delete []temp_seq_x;
	delete []temp_seq_y;
}



/*
 * Description : Calculate the cross-correlation of input sequences,default is not biased or unbiased
 * Parameter   : discrete_seq_x - first input sequence with type float
 * 				 discrete_seq_y - second input sequence with type float
 * 				 cross_corr     - output sequence with type float,the cross-correlation of input sequences
 *
 * */
void cross_c(	complexf 	*discrete_seq_x,
				complexf	*discrete_seq_y,
				complexf 	*cross_corr,
				unsigned int seq_length_x,
				unsigned int seq_length_y)
{
	/*
	 * Compare the length of the input sequences,if they were not equal,insert some zeros
	 * at the end of the shorter one
	 * */
	unsigned int seq_length = std::max(seq_length_x,seq_length_y);
	complexf *temp_seq_x = new complexf[seq_length];
	complexf *temp_seq_y = new complexf[seq_length];
	for (unsigned int i=0;i<seq_length;i++)
	{
		if (i < seq_length_x)
			temp_seq_x[i] = discrete_seq_x[i];
		else
			temp_seq_x[i] = 0;
		if (i < seq_length_y)
			temp_seq_y[i] = discrete_seq_y[i];
		else
			temp_seq_y[i] = 0;
	}
	//Calculate cross-correlation
	for (unsigned int m=0;m<(2*seq_length-1);m++)
	{
		complexf temp = 0;
		// Corresponding to the index of cross-corr under zero
		if (m<seq_length-1)
		{
			for(unsigned int n=0;n<=seq_length-1 - (seq_length-1-m);n++)
				temp += conj(temp_seq_x[n]) * temp_seq_y[n+(seq_length-1-m)];
			temp=(temp);
		}
		// Calculate the cross-correlation
		else
		{
			for(unsigned int n=0;n<=seq_length-1 - (m-(seq_length-1));n++)
				temp += temp_seq_x[n+(m-(seq_length-1))] * conj(temp_seq_y[n]);
			temp=conj(temp);
		}
		cross_corr[m] = (temp);
	}
	delete []temp_seq_x;
	delete []temp_seq_y;
}

/*
 * Description : Calculate the cross-correlation of input sequences
 * Parameter   : discrete_seq_x - first input sequence with type float
 * 				 discrete_seq_y - second input sequence with type float
 * 				 cross_corr     - float output sequence,the cross-correlation of input sequences
 * 				 seq_length_x   - the length of discrete_seq_x
 * 				 seq_length_y   - the length of discrete_seq_y
 * 				 option         - specifies a normalization option for the cross-correlation,
 * 				 				  'biased'  : Biased estimate of the autocorrelation function
 * 				 				  'unbiased': Unbiased estimate of the autocorrelation function
 *
 * */
void cross_c(	complexf	*discrete_seq_x,
				complexf	*discrete_seq_y,
				complexf 	*cross_corr,
				unsigned int seq_length_x,
				unsigned int seq_length_y,
				std::string  option)
{
	/*
	 * Compare the length of the input sequences,if they were not equal,insert some zeros
	 * at the end of the shorter one
	 * */
	unsigned int seq_length = std::max(seq_length_x,seq_length_y);
	complexf *temp_seq_x = new complexf[seq_length];
	complexf *temp_seq_y = new complexf[seq_length];
	for (unsigned int i=0;i<seq_length;i++)
	{
		if (i < seq_length_x)
			temp_seq_x[i] = discrete_seq_x[i];
		else
			temp_seq_x[i] = 0;
		if (i < seq_length_y)
			temp_seq_y[i] = discrete_seq_y[i];
		else
			temp_seq_y[i] = 0;
	}
	//Calculate cross-correlation

	if (option == "unbiased")
	{
		for (unsigned int m=0;m<(2*seq_length-1);m++)
		{
			complexf temp = 0;
			// Corresponding to the index of cross-corr under zero
			if (m<seq_length-1)
			{
				for(unsigned int n=0;n<=seq_length-1 - (seq_length-1-m);n++)
					temp += conj(temp_seq_x[n]) * temp_seq_y[n+(seq_length-1-m)];
				temp=(temp);
			}
			// Calculate the cross-correlation
			else
			{
				for(unsigned int n=0;n<=seq_length-1 - (m-(seq_length-1));n++)
					temp += temp_seq_x[n+(m-(seq_length-1))] * conj(temp_seq_y[n]);
				temp= conj(temp);
			}
			temp /= m<seq_length-1 ? (m+1):(2*seq_length-1-m);
			cross_corr[m] =(temp);
		}
	}

	else if (option == "biased")
	{
		for (unsigned int m=0;m<(2*seq_length-1);m++)
		{
			complexf temp = 0;
			// Corresponding to the index of cross-corr under zero
			if (m<seq_length-1)
			{
				for(unsigned int n=0;n<=seq_length-1 - (seq_length-1-m);n++)
					temp += conj(temp_seq_x[n]) * temp_seq_y[n+(seq_length-1-m)];
				temp =(temp);
			}
			// Calculate the cross-correlation
			else
			{
				for(unsigned int n=0;n<=seq_length-1 - (m-(seq_length-1));n++)
					temp += temp_seq_x[n+(m-(seq_length-1))] * conj(temp_seq_y[n]);
				temp=conj(temp);
			}
			temp /= seq_length;
			cross_corr[m] = (temp);
		}
	}
	else
		throw std::invalid_argument("Invalid Arithmetic Mode option:Must be 'biased' or 'unbiased'!");
	delete []temp_seq_x;
	delete []temp_seq_y;
}
