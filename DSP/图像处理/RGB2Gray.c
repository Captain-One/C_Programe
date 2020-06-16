/*
 * apdkd.c
 *
 *  Created on: 2019年11月18日
 *      Author: Pu
 */

#include <stdio.h>

uint8_t *in_rgb_image;
uint8_t *out_gray_image;


typedef struct image_rgb_{
	uint8_t *r;
	uint8_t *g;
	uint8_t *b;
	uint64_t row;
	uint64_t cloumn;
}imageRgb_t;

typedef struct image_gray_{
	uint8_t *gray;
	uint64_t row;
	uint64_t cloumn;
}imageGray_t;

typedef enum rgb2gray_algorithms_{
	WEIGHTED_AVERAGE = 0,
	AVERAGING,
	MAXIMUM,
}rgb2GrayAlgorithms_t;

int rgb2GrayProcess(imageRgb_t *in_image, imageGray_t *out_image, rgb2GrayAlgorithms_t algorithms)
{
	int re;

	switch(algorithms){
		case WEIGHTED_AVERAGE: re = rgb2Gray_WeightedAverageAlogrithms(in_image, out_image); break;
		case AVERAGING: re = rgb2Gray_AverageAlogrithms(in_image, out_image);break;
		case MAXIMUM: re = rgb2Gray_MaximumAlogrithms(in_image, out_image);break;
		default: return -1;
	}
	return re;
}

int rgb2Gray_WeightedAverageAlogrithms(imageRgb_t *in_image, imageGray_t *out_image)
{
	//F(i,j) = 0.3*R(i,j) + 0.59*G(i,j) + 0.11*B(i,j)

	uint64_t i, row, cloumn;

	row = in_image->row;
	cloumn = in_image->cloumn;

	for(i = 0; i < row * cloumn; i++){
		out_image->gray[i] = 0.3*(in_image->r[i]) + 0.59*(in_image->g[i]) + 0.11*(in_image->b[i]);
	}

	out_image->cloumn = cloumn;
	out_image->row = row;

	return 0;
}

int rgb2Gray_AverageAlogrithms(imageRgb_t *in_image, imageGray_t *out_image)
{
	//F(i,j) = [R(i,j) + G(i,j) + B(i,j)]/3

	uint64_t i, row, cloumn;

	row = in_image->row;
	cloumn = in_image->cloumn;

	for(i = 0; i < row * cloumn; i++){
		out_image->gray[i] = ((in_image->r[i]) + (in_image->g[i]) + (in_image->b[i]))/3;
	}

	out_image->cloumn = cloumn;
	out_image->row = row;

	return 0;
}

int rgb2Gray_MaximumAlogrithms(imageRgb_t *in_image, imageGray_t *out_image)
{
	//F(i,j) = Max[R(i,j) , G(i,j) , B(i,j)]

	uint64_t i, row, cloumn;

	row = in_image->row;
	cloumn = in_image->cloumn;

	for(i = 0; i < row * cloumn; i++){
		out_image->gray[i] = (in_image->r[i]) + 0.59*(in_image->g[i]) + 0.11*(in_image->b[i]);
	}

	out_image->cloumn = cloumn;
	out_image->row = row;

	return 0;
}
