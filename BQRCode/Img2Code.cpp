#include "stdafx.h"
#include "Img2Code.h"
CImg2Code::CImg2Code(void)
{

}

void CImg2Code:: Img2bit(Mat input_image,unsigned char imgBits[37][37]){
	Mat binaryImg;
	/* 图像二值化*/
	adaptiveThreshold(input_image,binaryImg,255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY,15,5);
	//threshold(input_image,binaryImg,50, 255,2);
	/*图像分割*/

}
void CImg2Code::ImgCut(Mat binaryImg,unsigned char imgBits[37][37]){
}
unsigned char CImg2Code::getValue(Mat roiImg){
	/*获取小区域的值*/

	if(1){// 深颜色

		return '1';
	}else
	{
		return '0';
	}
}
CImg2Code::~CImg2Code(void)
{
}
