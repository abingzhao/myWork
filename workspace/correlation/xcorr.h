/*
 * autoc.h
 *
 *  Created on: 2013-11-2
 *      Author: abing
 */

#ifndef AUTOC_H_
#define AUTOC_H_

#include <complex>
#include <cstring>

typedef std::complex<float> complexf;

/*
 * Description : Calculate the autocorrelation of input sequence,default is not biased or unbiased
 * Parameter   : discrete_seq - input sequence with length seq_length and type float
 * 				 auto_corr    - output sequence with type float,the autocorrelation of discrete_seq
 * 				 seq_length   - the length of input sequence
 * */
void autoc(float *discrete_seq,float *auto_corr,unsigned int seq_length);

/*
 * Description : Calculate the autocorrelation of input sequence,default is not biased or unbiased
 * Parameter   : discrete_seq - input sequence with length seq_length and type float
 * 				 auto_corr    - output sequence with type float,the autocorrelation of discrete_seq
 * 				 seq_length   - the length of input sequence
 * 				 option       - specifies a normalization option for the cross-correlation,
 * 				 				'biased': Biased estimate of the autocorrelation function
 * 				 				'unbiased': Unbiased estimate of the autocorrelation function
 * */
void autoc(float *discrete_seq,float *auto_corr,unsigned int seq_length,std::string option);

/*
 * Description : Calculate the autocorrelation of input sequence,default is not biased or unbiased
 * Parameter   : discrete_seq - input sequence with length seq_length and type complex<float>
 * 				 auto_corr    - output sequence with type complex<float>,the autocorrelation
 * 				 				of discrete_seq
 * 				 seq_length   - the length of input sequence
 * */
void autoc(complexf *discrete_seq,complexf *auto_corr,unsigned int seq_length);

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
void autoc(	complexf *discrete_seq,
			complexf *auto_corr,
			unsigned int seq_length,
			std::string option);


/*
 * Description : Calculate the cross-correlation of input sequences,default is neither biased or unbiased
 * Parameter   : discrete_seq_x - first input sequence with type float
 * 				 discrete_seq_y - second input sequence with type float
 * 				 cross_corr     - float output sequence,the cross-correlation of input sequences
 * 				 seq_length_x   - the length of discrete_seq_x
 * 				 seq_length_y   - the length of discrete_seq_y
 *
 * */
void cross_c(	float 		*discrete_seq_x,
				float		*discrete_seq_y,
				float 		*cross_corr,
				unsigned int seq_length_x,
				unsigned int seq_length_y);

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
				std::string  option);

/*
 * Description : Calculate the cross-correlation of input sequences,default is neither biased or unbiased
 * Parameter   : discrete_seq_x - first input sequence with type float
 * 				 discrete_seq_y - second input sequence with type float
 * 				 cross_corr     - float output sequence,the cross-correlation of input sequences
 * 				 seq_length_x   - the length of discrete_seq_x
 * 				 seq_length_y   - the length of discrete_seq_y
 *
 * */
void cross_c(	complexf	*discrete_seq_x,
				complexf	*discrete_seq_y,
				complexf 	*cross_corr,
				unsigned int seq_length_x,
				unsigned int seq_length_y);

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
void cross_c(	complexf 	*discrete_seq_x,
				complexf	*discrete_seq_y,
				complexf 	*cross_corr,
				unsigned int seq_length_x,
				unsigned int seq_length_y,
				std::string  option);



#endif /* AUTOC_H_ */
