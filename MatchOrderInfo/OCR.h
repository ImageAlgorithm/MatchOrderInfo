/********************************************************************************
 * 用于识别文字内容的头文件，函数都声明在命名空间OCR下面
********************************************************************************/

#ifndef _OCR_HPP_
#define _OCR_HPP_

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <baseapi.h>

using namespace std;
using namespace cv;

namespace OCR{
	wchar_t *Utf_8ToUnicode(char* szU8);

	//将宽字节wchar_t*转化为单字节char*    
	char* UnicodeToAnsi(const wchar_t* szStr);

	bool getResult(Mat srcImg, int nROILeft, int nROITop, int nROIWidth, int nROIHeight,
		const char *pcLang, tesseract::PageSegMode mode, char* &pcRstText);
}

#endif