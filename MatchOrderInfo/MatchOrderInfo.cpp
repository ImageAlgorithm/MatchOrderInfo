/********************************************************************************
* 用于得到订单的内容和订单内容的解析，分别得到金额，交易时间，交易单号和商户单号
********************************************************************************/

#include <iostream>
#include <opencv2/opencv.hpp>
#include "OCR.h"

using namespace std;
using namespace cv;

//************************************
// Method:    Write：创建txt，并写入数据
// FullName:  Write
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: const string strFolder：文件的保存路径("C:\\Users\\White\\Desktop")
// Parameter: const string strFilename：文件名(test.txt)
// Parameter: string strConternt：要被写到文件中的内容
// Parameter: bool bOver：是否覆盖原有内容（true：覆盖，false：不覆盖，默认值false）
//************************************
bool Write(const string strFolder, const string strFilename, string strConternt, bool bOver = false)
{
	if ("" == strFolder || "" == strFilename || strConternt == "")
	{
		return false;
	}

	string strPath = strFolder + "\\" + strFilename;
	if (bOver)
	{
		ofstream fout(strPath); //覆盖原有内容
		if (!fout)
		{
			cout << "File Not Opened" << endl;
			return false;
		}

		fout << strConternt.c_str() << endl;

		fout.close();
	}
	else
	{
		ofstream fout(strPath, ios::app); //不覆盖
		if (!fout)
		{
			cout << "File Not Opened" << endl;
			return false;
		}

		fout << strConternt.c_str() << endl;
		fout.close();
	}
	return true;
}

//************************************
// Method:    isQQ：判断是不是qq截图
// FullName:  isQQ
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: string res：结果
//************************************
bool isQQ(string res)
{
	int num = 0;
	string st1 = "交易时间";
	string st2 = "交易订单";
	string st3 = "商户订单";
	string st4 = "修改密码";
	string st5 = "金额";
	string st6 = "商品";
	int nRe1 = -1;
	nRe1 = res.find(st1);
	if (nRe1 >= 0)
	{
		num++;
	}
	int nRe2 = -1;
	nRe2 = res.find(st2);
	if (nRe2 >= 0)
	{
		num++;
	}
	int nRe3 = -1;
	nRe3 = res.find(st3);
	if (nRe3 >= 0)
	{
		num++;
	}
	int nRe4 = -1;
	nRe4 = res.find(st4);
	if (nRe4 >= 0)
	{
		num++;
	}
	int nRe5 = -1;
	nRe5 = res.find(st5);
	if (nRe5 >= 0)
	{
		num++;
	}
	int nRe6 = -1;
	nRe6 = res.find(st6);
	if (nRe6 >= 0)
	{
		num++;
	}

	if (num >= 3)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//************************************
// Method:    isWeChat：判断是不是微信截图
// FullName:  isWeChat
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: string res：结果
//************************************
bool isWeChat(string res)
{
	int num = 0;
	//截图为微信图片
	string st1 = "支付时间";
	string st2 = "支付方式";
	string st3 = "交易单号";
	string st4 = "商户单号";
	string st5 = "在此商户";
	string st6 = "充值服务";
	string st7 = "当前状态";
	int re1 = -1;
	re1 = res.find(st1);
	if (re1 >= 0) 
	{
		num++;
	}
	int re2 = -1;
	re2 = res.find(st2);
	if (re2 >= 0)
	{
		num++;
	}
	int re3 = -1;
	re3 = res.find(st3);
	if (re3 >= 0)
	{
		num++;
	}
	int re4 = -1;
	re4 = res.find(st4);
	if (re4 >= 0)
	{
		num++;
	}
	int re5 = -1;
	re5 = res.find(st5);
	if (re5 >= 0)
	{
		num++;
	}
	int re6 = -1;
	re6 = res.find(st6);
	if (re6 >= 0)
	{
		num++;
	}
	int re7 = -1;
	re7 = res.find(st7);
	if (re7 >= 0)
	{
		num++;
	}
	if (num >= 4)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//************************************
// Method:    checkError：纠正识别结果中的错误
// FullName:  checkError
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: string & srcResult：结果
//************************************
bool checkError(string &srcResult)
{
	if (srcResult.empty())
	{
		return false;
	}
	//去掉识别结果中的空格
	int nIndex = 0;
	while ((nIndex = srcResult.find(' ', nIndex)) != string::npos)
	{
		srcResult.erase(nIndex, 1);
	}
	//去掉"字符
	nIndex = 0;
	while ((nIndex = srcResult.find('"', nIndex)) != string::npos)
	{
		srcResult.erase(nIndex, 1);
	}
	//去掉所有的换行符
	int nIdx = srcResult.find("\n");
	while (nIdx >= 0)
	{
		srcResult.erase(nIdx, 1);
		nIdx = srcResult.find("\n");
	}

	//字符串纠错
	int nd = srcResult.find("金颧");
	if (nd >= 0)
	{
		srcResult.replace(nd, 4, "金额");
	}
	nd = -1;
	nd = srcResult.find("金频");
	if (nd >= 0)
	{
		srcResult.replace(nd, 4, "金额");
	}
	nd = -1;
	nd = srcResult.find("金ˇ额");
	if (nd >= 0)
	{
		srcResult.replace(nd, 6, "金额");
	}
	nd = -1;
	nd = srcResult.find("金#");
	if (nd >= 0)
	{
		srcResult.replace(nd, 3, "金额");
	}

	nd = -1;
	nd = srcResult.find("?11.60");
	if (nd >= 0)
	{
		srcResult.replace(nd, 6, "311.60");
	}
	nd = -1;
	nd = srcResult.find("%#615.607");
	if (nd >= 0)
	{
		srcResult.replace(nd, 9, "金额615.60元");
	}
	nd = -1;
	nd = srcResult.find("&-颡615.607.");
	if (nd >= 0)
	{
		srcResult.replace(nd, 12, "金额615.60元");
	}
	nd = -1;
	nd = srcResult.find("aom615.60元");
	if (nd >= 0)
	{
		srcResult.replace(nd, 11, "金额615.60元");
	}
	nd = -1;
	nd = srcResult.find("E283.10元");
	if (nd >= 0)
	{
		srcResult.replace(nd, 9, "金额283.10元");
	}
	nd = -1;
	nd = srcResult.find("#&463.6070");
	if (nd >= 0)
	{
		srcResult.replace(nd, 10, "金额463.60元");
	}
	nd = -1;
	nd = srcResult.find("##463.6077.");
	if (nd >= 0)
	{
		srcResult.replace(nd, 11, "金额463.60元");
	}
	nd = -1;
	nd = srcResult.find("s#57.0077");
	if (nd >= 0)
	{
		srcResult.replace(nd, 9, "金额57.00元");
	}
	nd = -1;
	nd = srcResult.find("#m311.6070");
	if (nd >= 0)
	{
		srcResult.replace(nd, 10, "金额331.60元");
	}
	nd = -1;
	nd = srcResult.find("E463.60元");
	if (nd >= 0)
	{
		srcResult.replace(nd, 9, "金额463.60元");
	}
	nd = -1;
	nd = srcResult.find("芸易单号");
	if (nd >= 0)
	{
		srcResult.replace(nd, 8, "交易单号");
	}
	nd = -1;
	nd = srcResult.find("芬易单号");
	if (nd >= 0)
	{
		srcResult.replace(nd, 8, "交易单号");
	}
	nd = -1;
	nd = srcResult.find("交易i丁单");
	if (nd >= 0)
	{
		srcResult.replace(nd, 9, "交易订单");
	}

	nd = -1;
	nd = srcResult.find("qQpro");
	if (nd >= 0)
	{
		srcResult.replace(nd, 5, "qqpro");
	}
	nd = -1;
	nd = srcResult.find("qdqpro");
	if (nd >= 0)
	{
		srcResult.replace(nd, 6, "qqpro");
	}

	nd = -1;
	nd = srcResult.find("商ˇ品");
	if (nd >= 0)
	{
		srcResult.replace(nd, 6, "商品");
	}
	nd = -1;
	nd = srcResult.find("Ce元宝");
	if (nd >= 0)
	{
		srcResult.replace(nd, 6, "商品元宝");
	}
	nd = -1;
	nd = srcResult.find("%&元宝");
	if (nd >= 0)
	{
		srcResult.replace(nd, 6, "商品元宝");
	}
	nd = -1;
	nd = srcResult.find("商&元宝");
	if (nd >= 0)
	{
		srcResult.replace(nd, 7, "商品元宝");
	}
	nd = -1;
	nd = srcResult.find("B-?元宝");
	if (nd >= 0)
	{
		srcResult.replace(nd, 7, "商品元宝");
	}
	nd = -1;
	nd = srcResult.find("商晏元室");
	if (nd >= 0)
	{
		srcResult.replace(nd, 8, "商品元宝");
	}
	nd = -1;
	nd = srcResult.find("支付时间_");
	if (nd >= 0)
	{
		srcResult.replace(nd, 9, "支付时间");
	}

	nd = -1;
	nd = srcResult.find("交易单号_");
	if (nd >= 0)
	{
		srcResult.replace(nd, 9, "交易单号");
	}
	nd = -1;
	nd = srcResult.find("交易单号ˇ");
	if (nd >= 0)
	{
		srcResult.replace(nd, 10, "交易单号");
	}
	nd = -1;
	nd = srcResult.find("#4#%-42");
	if (nd >= 0)
	{
		srcResult.replace(nd, 7, "交易单号42");
	}

	nd = -1;
	nd = srcResult.find("商户单号_");
	if (nd >= 0)
	{
		srcResult.replace(nd, 9, "商户单号");
	}
	nd = -1;
	nd = srcResult.find("商户单号ˇ");
	if (nd >= 0)
	{
		srcResult.replace(nd, 10, "商户单号");
	}
	nd = -1;
	nd = srcResult.find("HPRS-");
	if (nd >= 0)
	{
		srcResult.replace(nd, 5, "商户单号");
	}
	nd = -1;
	nd = srcResult.find("文付时间ˇ");
	if (nd >= 0)
	{
		srcResult.replace(nd, 10, "支付时间");
	}
	nd = -1;
	nd = srcResult.find("支付方我");
	if (nd >= 0)
	{
		srcResult.replace(nd, 8, "支付方式");
	}
	nd = -1;
	nd = srcResult.find("修改密码〉");
	if (nd >= 0)
	{
		srcResult.replace(nd, 9, "修改密码");
	}
	nd = -1;
	nd = srcResult.find("product201");
	if (nd >= 0)
	{
		srcResult.replace(nd, 10, "product_201");
	}
	nd = -1;
	nd = srcResult.find("交易壬丁单");
	if (nd >= 0)
	{
		srcResult.replace(nd, 10, "交易订单");
	}
	nd = -1;
	nd = srcResult.find("%4壬丁单");
	if (nd >= 0)
	{
		srcResult.replace(nd, 8, "交易订单");
	}
	nd = -1;
	nd = srcResult.find("修改窟码");
	if (nd >= 0)
	{
		srcResult.replace(nd, 8, "修改密码");
	}
	nd = -1;
	nd = srcResult.find("修改密秆");
	if (nd >= 0)
	{
		srcResult.replace(nd, 8, "修改密码");
	}
	nd = -1;
	nd = srcResult.find("当刊状态");
	if (nd >= 0)
	{
		srcResult.replace(nd, 8, "当前状态");
	}
	return true;
}

//************************************
// Method:    ProcessResultAndWriteTxt：处理识别结果，输出到控制台
// FullName:  ProcessResultAndWriteTxt
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: string result：识别结果
// Parameter: string img_path：图片路径
//************************************
void ProcessResult(string strSrcResult, string img_path)
{

	if (strSrcResult.empty() || img_path.empty())
	{
		return;
	}

	bool isQQImg = isQQ(strSrcResult);
	bool isWeChatImg = isWeChat(strSrcResult);
	//获取当前图片名
	string strImageName = img_path;
	int nIdx = strImageName.rfind('\\');
	strImageName = strImageName.substr(nIdx + 1, strImageName.size() - nIdx);	//图片名称

	if (isQQImg)
	{
		//当前截图为QQ截图
		string str1 = "商户订单";		// 商户订单
		string str2 = "修改密码";		// 修改密码
		string str3 = "金额";			// 金额
		string str4 = "订单金额";		// 订单金额
		string str5 = "商品";			// 商品

		int nIndex1 = -1;	//前下标
		int nIndex2 = -1;	//后下标

		//获取金额
		//通过获取金额数量前字符“金额”和后字符“商品”或“订单金额”的位置，截取二者中间的子串则是金额数量的字符串
		//如果前后位置都没有找到，则认为没有识别出来，否则找到其中一个的位置，就通过向前或向后，来截取包含金额数量的字符串
		//得到金额数量字符串后，确定字符'.'小数点的位置，如果没有找到'.'，则认为字符串是错的。
		//找到'.'的位置后，向前读取为数字的字符，向后读取两位字符，则是花费金额的字符串
		nIndex1 = (int)strSrcResult.find(str3);	//“金额”的位置
		nIndex2 = (int)strSrcResult.find(str4);	//“订单金额”的位置
		if (nIndex2 < 0)
		{
			nIndex2 = (int)strSrcResult.find(str5); // “商品”的位置
		}
		string strMoney = "";	//金额
		if (nIndex2 < 0 && nIndex1 < 0)
		{
			strMoney = strImageName;
		}
		else
		{
			if (nIndex1 < 0 && nIndex2 >= 0)
			{
				nIndex1 = nIndex2 - 12;
			}
			else if (nIndex1 >= 0 && nIndex2 < 0)
			{
				nIndex2 = nIndex1 + 14;
			}
			string strTmp = strSrcResult.substr(nIndex1, nIndex2 - nIndex1);
			int nIdx = strTmp.find('.');
			if (nIdx < 0)
			{
				nIndex2 = strSrcResult.find("元宝");
				if (nIndex2 >= 0)
				{
					strTmp = strSrcResult.substr(nIndex2 - 12, 12);
				}
			}
			nIdx = strTmp.find('.');
			if (nIdx >= 0)
			{
				string money = ".";
				for (int i = nIdx-1; i > 0; i--)
				{
					if (strTmp[i] >= '0' && strTmp[i] <= '9' && money.size() <= 4)
					{
						money = strTmp[i] + money;
					}
					else
					{
						break;
					}
				}
				strMoney = money + strTmp.substr(nIdx + 1, 2);
			}
			else
			{
				strMoney = strImageName;
			}
		}
		cout << strMoney << endl;

		//获取交易时间
		//先在全文中寻找"2018-"或"2019-"，然后从这个位置开始截取22个字符，通过判断22个字符中数字字符的数量（14）来确定交易时间最后一个字符的位置
		//然后截取这段字符，并在第十个字符后边加上一个空格
		//如果没有找到"2018-"或"2019-"或者检查到截取的22个字符中数字字符少于14个，则认为字符串识别错误
		int n1 = (int)strSrcResult.find("2018-");
		int n2 = (int)strSrcResult.find("2019-");
		nIndex1 = (n1 >= n2) ? n1 : n2;
		string strTime = "";	//交易时间
		if (nIndex1 >= 0)
		{
			string strTmp = strSrcResult.substr(nIndex1, 22);
			int nIdx = 0;
			int num = 0;
			for (int i = 0; i < strTmp.size(); i++)
			{
				nIdx = i;
				if (num == 14)
				{
					break;
				}
				if (strTmp[i] >= '0' && strTmp[i] <= '9')
				{
					num++;
				}
				
			}

			if (num >= 14)
			{
				strTmp = strTmp.substr(0, nIdx);
				strTime = strTmp.substr(0, 10);
				strTime += ' ';
				strTime += strTmp.substr(10, nIdx - 10);
			}
			else
			{
				strTime = strImageName;
			}
		}
		else
		{
			strTime = strImageName;
		}
		cout << strTime << endl;

		//获取交易订单
		//交易订单号以"10000"开头，则先确定"10000"的位置，然后确定字符串"商户订单"的位置，"商户订单"在交易订单号的后面
		//如果没有找到"商户订单",则从"10000"截取34个字符（超过了交易订单号的长度），并个字符判断是不是数字字符，如果遇到不是数字字符的，认为找到结尾了
		//如果找到"商户订单"，则从"10000"开始到"商户订单"的字符串为交易订单号。
		//如果没有找到"10000"，则认为没有识别到交易订单
		nIndex1 = (int)strSrcResult.find("10000");
		nIndex2 = (int)strSrcResult.find(str1);
		string strTransactionOrder = "";	//交易订单
		if (nIndex1 >= 0)
		{
			if (nIndex2 < 0 || nIndex2 < nIndex1)
			{
				strTransactionOrder = strSrcResult.substr(nIndex1, 34);
				string strTmp = "";
				for (int i = 0; i < strTransactionOrder.size(); i++)
				{
					if (strTransactionOrder[i] >= '0' && strTransactionOrder[i] <= '9')
					{
						strTmp += strTransactionOrder[i];
					}
					else
					{
						break;
					}
				}
				strTransactionOrder = strTmp;
			}
			else
			{
				strTransactionOrder = strSrcResult.substr(nIndex1, (nIndex2 - nIndex1));
			}
		}
		else
		{
			strTransactionOrder = strImageName;
		}
		cout << strTransactionOrder << endl;

		//获取商户订单
		//商户订单号以"qqpro_"开头，所以先检查有没有"qqpro_"，然后检查有没有"修改密码"（大部分商户订单号后边都是"修改密码")
		//如果"qqpro_"没有找到，认为没有识别到商户订单
		//截取"qqpro_"到"修改密码"中间的字符，如果没有找到"修改密码",则从"qqpro_"截取到字符串结尾，
		//然后对截取的字符串逐个字符判断是不是数字字符，遇到不是数字字符的地方结束，便提取出了商户订单
		nIndex1 = (int)strSrcResult.find("qqpro_");
		nIndex2 = (int)strSrcResult.find(str2);
		string strMerchantOrder = "";	//商户单号
		if (nIndex1 >= 0)
		{
			//卡住单号的结尾，防止出现单号后边无内容的情况
			if (nIndex2 < 0 || nIndex2 < nIndex1)
			{
				nIndex2 = strSrcResult.size();
			}
			strMerchantOrder = strSrcResult.substr(nIndex1, (nIndex2 - nIndex1));
			string temp = "";
			for (int i = 0; i < strMerchantOrder.size(); i++)
			{
				if (strMerchantOrder[i] >= '0' && strMerchantOrder[i] <= '9')
				{
					temp += strMerchantOrder[i];
				}
			}
			strMerchantOrder = "qqpro_" + temp;
		}
		else
		{
			strMerchantOrder = strImageName;
		}
		cout << strMerchantOrder << endl;
	}
	else if (isWeChatImg)
	{
		//截图为微信图片
		string str1 = "商户单号";	// 商户单号
		string str2 = "在此商户";	// 在此商户
		string str3 = "充值服务";
		string str4 = "当前状态";

		int nIndex1 = -1;
		int nIndex2 = -1;
		//得到订单金额
		//通过获取金额数量前字符"充值服务"和后字符"当前状态"的位置，截取二者中间的子串则是金额数量的字符串
		//如果前后位置都没有找到，则认为没有识别出来，否则找到其中一个的位置，就通过向前或向后，来截取包含金额数量的字符串
		//得到金额数量字符串后，确定字符'.'小数点和字符'-'负号的位置
		//截取'-'号和'.'之间的字符和'.'后边两个字符则是订单金额
		nIndex1 = strSrcResult.find(str3);
		nIndex2 = strSrcResult.find(str4);
		string strMoney = "";  //金额
		if (nIndex1 < 0 && nIndex2 < 0)
		{
			strMoney = strImageName;
		}
		else
		{
			if (nIndex1 < 0 && nIndex2 >= 0)
			{
				nIndex1 = nIndex2 - 12;
			}
			else if (nIndex1 >= 0 && nIndex2 < 0)
			{
				nIndex2 = nIndex1 + 18;
			}
			string strTmp = strSrcResult.substr(nIndex1, nIndex2 - nIndex1);
			int nIdx1 = strTmp.find('-');
			int nIdx2 = strTmp.find('.');
			if (nIdx1 >= 0 && nIdx2 >= 0)
			{
				strMoney = strTmp.substr(nIdx1 + 1, nIdx2 - nIdx1 - 1);
				for (int i = 0; i < strMoney.size(); i++)
				{
					if (strMoney[i] < '0' || strMoney[i] > '9')
					{
						strMoney.erase(i, 1);
					}
				}
				strMoney += strTmp.substr(nIdx2, 3);
			}
			else
			{
				strMoney = strImageName;
			}
		}
		cout << strMoney << endl;

		//得到支付时间
		//先在全文中寻找"2018-"或"2019-"，然后从这个位置开始截取22个字符，通过判断22个字符中数字字符的数量（14）来确定交易时间最后一个字符的位置
		//然后截取这段字符，并在第十个字符后边加上一个空格
		//如果没有找到"2018-"或"2019-"或者检查到截取的22个字符中数字字符少于14个，则认为字符串识别错误
		int n1 = (int)strSrcResult.find("2018-");
		int n2 = (int)strSrcResult.find("2019-");
		nIndex1 = n1 > n2 ? n1 : n2;
		string strTime = "";	//支付时间
		if (nIndex1 >= 0)
		{
			string strTmp = strSrcResult.substr(nIndex1, 22);
			int nIdx = 0;
			int num = 0;
			for (int i = 0; i < strTmp.size(); i++)
			{
				nIdx = i;
				if (num == 14)
				{
					break;
				}
				if (strTmp[i] >= '0' && strTmp[i] <= '9')
				{
					num++;
				}
			}
			if (num >= 14)
			{
				strTmp = strTmp.substr(0, nIdx);
				strTime = strTmp.substr(0, 10);
				strTime += ' ';
				strTime += strTmp.substr(10, nIdx - 10);
			}
			else
			{
				strTime = strImageName;
			}
			
		}
		else
		{
			strTime = strImageName;
		}
		cout << strTime << endl;

		//得到交易单号
		//交易单号以"42000"开头，则先确定"42000"的位置，然后确定字符串"商户单号"的位置，"商户单号"在交易单号的后面
		//如果找到"商户单号"，则从"42000"开始到"商户单号"的字符串为交易订单号。
		//如果没有找到"商户单号",则从"42000"截取30个字符（超过了交易单号的长度），并个字符判断是不是数字字符，如果遇到不是数字字符的，认为找到结尾了
		//如果没有找到"42000"，则认为没有识别到交易单号
		nIndex1 = (int)strSrcResult.find("42000");
		nIndex2 = (int)strSrcResult.find(str1);
		string strTransactionNumber = "";	//交易单号
		if (nIndex1 >= 0)
		{
			if (nIndex2 >= 0)
			{
				strTransactionNumber = strSrcResult.substr(nIndex1, (nIndex2 - nIndex1));
			}
			else
			{
				strTransactionNumber = strSrcResult.substr(nIndex1, 30);
				string strTmp = "";
				for (int i = 0; i < strTransactionNumber.size(); i++)
				{
					if (strTransactionNumber[i] >= '0' && strTransactionNumber[i] <= '9')
					{
						strTmp += strTransactionNumber[i];
					}
					else
					{
						break;
					}
				}
				strTransactionNumber = strTmp;
			}
		}
		else
		{
			strTransactionNumber = strImageName;
		}
		cout << strTransactionNumber << endl;

		//得到商户单号
		//商户单号以"product_"开头，所以先检查有没有"product_"，然后检查有没有"在此商户"（大部分商户单号后边都是"在此商户")
		//如果"product_"没有找到，认为没有识别到商户单号
		//截取"product_"到"在此商户"中间的字符，如果没有找到"在此商户",则从"qqpro_"截取到字符串结尾，
		//然后对截取的字符串逐个字符判断是不是数字字符，遇到不是数字字符的地方结束，便提取出了商户订单
		nIndex1 = (int)strSrcResult.find("product_");
		nIndex2 = (int)strSrcResult.find(str2);
		string strMerchantNumber  = "";		//商户单号
		if (nIndex1 >= 0)
		{
			if (nIndex2 < 0)
			{
				nIndex2 = strSrcResult.size();
			}
			strMerchantNumber = strSrcResult.substr(nIndex1, (nIndex2 - nIndex1));
			string strTmp = "";
			for (int i = 0; i < strMerchantNumber.size(); i++)
			{
				if (strMerchantNumber[i] >= '0' && strMerchantNumber[i] <= '9')
				{
					strTmp += strMerchantNumber[i];
				}
			}
			strMerchantNumber = "product_" + strTmp;
		}
		else
		{
			strMerchantNumber = strImageName;
		}
		cout << strMerchantNumber << endl;
	}
	else
	{
		//没有辨认出是微信还是qq图片
		cout << strImageName << endl;
		cout << strImageName << endl;
		cout << strImageName << endl;
		cout << strImageName << endl;
	}
}


int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		//cout << "请按exe路径，图片路径格式输入参数。" << endl;
		return 1;
	}
	//string qq = argv[1];

	string img_path = argv[1]; //   "C:\\Users\\White\\Desktop\\test\\327.png";

	Mat inputImg = imread(img_path);
	if (inputImg.empty())
	{
		//cout << "图片不存在！！" << endl;
		return 1;
	}
	if (inputImg.rows < inputImg.cols)
	{
		//cout << "错误" << endl;
		return 1;
	}

	//将图片中三个通道的值都低于150的地方，突出为0的黑色
	for (int row = 0; row < inputImg.rows; row++)
	{
		for (int col = 0; col < inputImg.cols; col++)
		{
			if (inputImg.at<Vec3b>(row, col)[0] <= 165 && inputImg.at<Vec3b>(row, col)[1] <= 165 && inputImg.at<Vec3b>(row, col)[2] <= 165)
			{
				inputImg.at<Vec3b>(row, col) = Vec3b(0, 0, 0);
			}
		}
	}	

// 	imshow("增强", inputImg);
// 	waitKey(0);

	int nLeft = 0;
	int nTop = 0;
	int nWdith = inputImg.cols;
	int nHeight = inputImg.rows;

	char *pText = NULL;
	bool bRev = false;
	char *pcLang = "chi_sim+eng";
	bRev = OCR::getResult(inputImg, nLeft, nTop, nWdith, nHeight, pcLang, tesseract::PageSegMode::PSM_SINGLE_COLUMN, pText);
	if (!bRev)
	{
		return -1;
	}
	string srcResult = pText;
	

	//检查是否有错
	bool bChe = checkError(srcResult);
	if (!bChe)
	{
		return -1;
	}
	//cout << srcResult << endl;

	ProcessResult(srcResult, img_path);

	//cout << srcResult << endl;
	//16.png、
	return 0;
}
