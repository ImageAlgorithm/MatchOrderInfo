/********************************************************************************
* 用于识别文字内容的文件，实现了OCR.h中声明的函数
********************************************************************************/

#include "OCR.h"

wchar_t* OCR::Utf_8ToUnicode(char* szU8)
{
	//UTF8 to Unicode  
	//由于中文直接复制过来会成乱码，编译器有时会报错，故采用16进制形式  

	//预转换，得到所需空间的大小  
	size_t wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);
	//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间  
	wchar_t *wszString = new wchar_t[wcsLen + 1];
	//转换  
	::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);
	//最后加上'\0'  
	wszString[wcsLen] = '\0';
	return wszString;
}

//将宽字节wchar_t*转化为单字节char*    
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

	// tesseract是命令空间，TessBaseAPI是类名,定义一对象pAPI
	tesseract::TessBaseAPI *pTess = new tesseract::TessBaseAPI();
	// Initialize tesseract-ocr with English, without specifying tessdata path
	// 参数1：环境变量内设置的tessdata路径；
	// 参数2：识别需要的语言，语言之间不能加空格；
	// 聊天程序使用语言为：chi_sim
	//if (pTess->Init(NULL, "chi_sim+eng"))  // "D:/Program Files (x86)/tessdata/"  "chi_sim"
	if (pTess->Init(NULL, pcLang))
	{
		cout << "OCRTesseract: Could not initialize tesseract." << endl;
		return false;
	}

	// setup, 参数：PSM_AUTO识别为竖着方向
	// PSM_AUTO_ONLY: 用于整篇文字的识别，如聊天截屏信息
	// PSM_SINGLE_LINE: 用于一行文字的识别，如角色名、区服等
	// PSM_AUTO: 用于垂直一列列的方向
	// PSM_SINGLE_BLOCK:用于一行一行的识别,同一行的文字间不能有大间隙
	//pTess->SetPageSegMode(tesseract::PageSegMode::PSM_SINGLE_BLOCK); // PSM_SINGLE_BLOCK  PSM_SINGLE_LINE
	pTess->SetPageSegMode(mode);
	pTess->SetVariable("save_best_choices", "T");

	// Input color image, last parameter is bytes_per_line
	pTess->SetImage((uchar*)ROIImg.data, ROIImg.cols, ROIImg.rows, 3, ROIImg.cols * 3);
	//pTess->SetImage
	pTess->Recognize(0);

	// Get OCR result，由于中文显示为乱码，UTF格式英文占1个字节，中文占3个字节
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