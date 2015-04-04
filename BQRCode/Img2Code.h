#pragma once
using namespace cv;
class CImg2Code
{
public:
	CImg2Code(void);
	void Img2bit(Mat input_image,unsigned char imgBits[37][37]);
	~CImg2Code(void);
protected:
	unsigned char getValue(Mat roiImg);
    void ImgCut(Mat binaryImg,unsigned char imgBits[37][37]);
};

