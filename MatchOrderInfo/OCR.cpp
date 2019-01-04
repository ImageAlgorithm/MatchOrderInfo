/********************************************************************************
* ����ʶ���������ݵ��ļ���ʵ����OCR.h�������ĺ���
********************************************************************************/

#include "OCR.h"

wchar_t* OCR::Utf_8ToUnicode(char* szU8)
{
	//UTF8 to Unicode  
	//��������ֱ�Ӹ��ƹ���������룬��������ʱ�ᱨ���ʲ���16������ʽ  

	//Ԥת�����õ�����ռ�Ĵ�С  
	size_t wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);
	//����ռ�Ҫ��'\0'�����ռ䣬MultiByteToWideChar�����'\0'�ռ�  
	wchar_t *wszString = new wchar_t[wcsLen + 1];
	//ת��  
	::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);
	//������'\0'  
	wszString[wcsLen] = '\0';
	return wszString;
}

//�����ֽ�wchar_t*ת��Ϊ���ֽ�char*    
char* OCR::UnicodeToAnsi(const wchar_t* szStr)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
	{
		return NULL;
	}
	char *pResult = new char[nLen];

	WideCharToMultiByte(CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL);

	return pResult;
}

bool OCR::getResult(Mat srcImg, int nROILeft, int nROITop, int nROIWidth, int nROIHeight,
	const char *pcLang, tesseract::PageSegMode mode, char* &pcRstText)
{

	if (srcImg.empty())
	{
		cout << "srcImg not exist" << endl;
		return false;
	}

	if (nROILeft < 0 || nROILeft > srcImg.cols || nROITop < 0 || nROITop > srcImg.rows
		|| (nROILeft + nROIWidth) > srcImg.cols || (nROITop + nROIHeight) > srcImg.rows
		|| nROIWidth > srcImg.cols || nROIHeight > srcImg.rows)
	{
		cout << "ROI left, top, width, height error" << endl;
		return false;
	}

	Mat ROIImg;
	ROIImg.create(nROIHeight, nROIWidth, CV_8UC3);
	if (ROIImg.empty())
	{
		cout << "ROI image create failed!" << endl;
		return false;
	}

	for (int i = 0; i < nROIHeight; ++i)
	{
		for (int j = 0; j < nROIWidth; ++j)
		{
			ROIImg.at<Vec3b>(i, j)[0] = srcImg.at<Vec3b>(i + nROITop, j + nROILeft)[0];
			ROIImg.at<Vec3b>(i, j)[1] = srcImg.at<Vec3b>(i + nROITop, j + nROILeft)[1];
			ROIImg.at<Vec3b>(i, j)[2] = srcImg.at<Vec3b>(i + nROITop, j + nROILeft)[2];
		}
	}

	//imwrite("OCR.bmp", ROIImg);

	// tesseract������ռ䣬TessBaseAPI������,����һ����pAPI
	tesseract::TessBaseAPI *pTess = new tesseract::TessBaseAPI();
	// Initialize tesseract-ocr with English, without specifying tessdata path
	// ����1���������������õ�tessdata·����
	// ����2��ʶ����Ҫ�����ԣ�����֮�䲻�ܼӿո�
	// �������ʹ������Ϊ��chi_sim
	//if (pTess->Init(NULL, "chi_sim+eng"))  // "D:/Program Files (x86)/tessdata/"  "chi_sim"
	if (pTess->Init(NULL, pcLang))
	{
		cout << "OCRTesseract: Could not initialize tesseract." << endl;
		return false;
	}

	// setup, ������PSM_AUTOʶ��Ϊ���ŷ���
	// PSM_AUTO_ONLY: ������ƪ���ֵ�ʶ�������������Ϣ
	// PSM_SINGLE_LINE: ����һ�����ֵ�ʶ�����ɫ����������
	// PSM_AUTO: ���ڴ�ֱһ���еķ���
	// PSM_SINGLE_BLOCK:����һ��һ�е�ʶ��,ͬһ�е����ּ䲻���д��϶
	//pTess->SetPageSegMode(tesseract::PageSegMode::PSM_SINGLE_BLOCK); // PSM_SINGLE_BLOCK  PSM_SINGLE_LINE
	pTess->SetPageSegMode(mode);
	pTess->SetVariable("save_best_choices", "T");

	// Input color image, last parameter is bytes_per_line
	pTess->SetImage((uchar*)ROIImg.data, ROIImg.cols, ROIImg.rows, 3, ROIImg.cols * 3);
	//pTess->SetImage
	pTess->Recognize(0);

	// Get OCR result������������ʾΪ���룬UTF��ʽӢ��ռ1���ֽڣ�����ռ3���ֽ�
	char *pOutText = pTess->GetUTF8Text();
	wchar_t *pTempChar = Utf_8ToUnicode(pOutText);
	pcRstText = UnicodeToAnsi(pTempChar);

	//cout << "OCR Result: " << pcRstText;

	pTess->End();
	//delete[] pOutText;
	delete[] pTempChar;
	//delete[] pcRstText;
	return true;
}