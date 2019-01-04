/********************************************************************************
 * ����ʶ���������ݵ�ͷ�ļ��������������������ռ�OCR����
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

	//�����ֽ�wchar_t*ת��Ϊ���ֽ�char*    
	char* UnicodeToAnsi(const wchar_t* szStr);

	bool getResult(Mat srcImg, int nROILeft, int nROITop, int nROIWidth, int nROIHeight,
		const char *pcLang, tesseract::PageSegMode mode, char* &pcRstText);
}

#endif