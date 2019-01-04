/********************************************************************************
* ���ڵõ����������ݺͶ������ݵĽ������ֱ�õ�������ʱ�䣬���׵��ź��̻�����
********************************************************************************/

#include <iostream>
#include <opencv2/opencv.hpp>
#include "OCR.h"

using namespace std;
using namespace cv;

//************************************
// Method:    Write������txt����д������
// FullName:  Write
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: const string strFolder���ļ��ı���·��("C:\\Users\\White\\Desktop")
// Parameter: const string strFilename���ļ���(test.txt)
// Parameter: string strConternt��Ҫ��д���ļ��е�����
// Parameter: bool bOver���Ƿ񸲸�ԭ�����ݣ�true�����ǣ�false�������ǣ�Ĭ��ֵfalse��
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
		ofstream fout(strPath); //����ԭ������
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
		ofstream fout(strPath, ios::app); //������
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
// Method:    isQQ���ж��ǲ���qq��ͼ
// FullName:  isQQ
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: string res�����
//************************************
bool isQQ(string res)
{
	int num = 0;
	string st1 = "����ʱ��";
	string st2 = "���׶���";
	string st3 = "�̻�����";
	string st4 = "�޸�����";
	string st5 = "���";
	string st6 = "��Ʒ";
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
// Method:    isWeChat���ж��ǲ���΢�Ž�ͼ
// FullName:  isWeChat
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: string res�����
//************************************
bool isWeChat(string res)
{
	int num = 0;
	//��ͼΪ΢��ͼƬ
	string st1 = "֧��ʱ��";
	string st2 = "֧����ʽ";
	string st3 = "���׵���";
	string st4 = "�̻�����";
	string st5 = "�ڴ��̻�";
	string st6 = "��ֵ����";
	string st7 = "��ǰ״̬";
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
// Method:    checkError������ʶ�����еĴ���
// FullName:  checkError
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: string & srcResult�����
//************************************
bool checkError(string &srcResult)
{
	if (srcResult.empty())
	{
		return false;
	}
	//ȥ��ʶ�����еĿո�
	int nIndex = 0;
	while ((nIndex = srcResult.find(' ', nIndex)) != string::npos)
	{
		srcResult.erase(nIndex, 1);
	}
	//ȥ��"�ַ�
	nIndex = 0;
	while ((nIndex = srcResult.find('"', nIndex)) != string::npos)
	{
		srcResult.erase(nIndex, 1);
	}
	//ȥ�����еĻ��з�
	int nIdx = srcResult.find("\n");
	while (nIdx >= 0)
	{
		srcResult.erase(nIdx, 1);
		nIdx = srcResult.find("\n");
	}

	//�ַ�������
	int nd = srcResult.find("��ȧ");
	if (nd >= 0)
	{
		srcResult.replace(nd, 4, "���");
	}
	nd = -1;
	nd = srcResult.find("��Ƶ");
	if (nd >= 0)
	{
		srcResult.replace(nd, 4, "���");
	}
	nd = -1;
	nd = srcResult.find("�𡦶�");
	if (nd >= 0)
	{
		srcResult.replace(nd, 6, "���");
	}
	nd = -1;
	nd = srcResult.find("��#");
	if (nd >= 0)
	{
		srcResult.replace(nd, 3, "���");
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
		srcResult.replace(nd, 9, "���615.60Ԫ");
	}
	nd = -1;
	nd = srcResult.find("&-�615.607.");
	if (nd >= 0)
	{
		srcResult.replace(nd, 12, "���615.60Ԫ");
	}
	nd = -1;
	nd = srcResult.find("aom615.60Ԫ");
	if (nd >= 0)
	{
		srcResult.replace(nd, 11, "���615.60Ԫ");
	}
	nd = -1;
	nd = srcResult.find("E283.10Ԫ");
	if (nd >= 0)
	{
		srcResult.replace(nd, 9, "���283.10Ԫ");
	}
	nd = -1;
	nd = srcResult.find("#&463.6070");
	if (nd >= 0)
	{
		srcResult.replace(nd, 10, "���463.60Ԫ");
	}
	nd = -1;
	nd = srcResult.find("##463.6077.");
	if (nd >= 0)
	{
		srcResult.replace(nd, 11, "���463.60Ԫ");
	}
	nd = -1;
	nd = srcResult.find("s#57.0077");
	if (nd >= 0)
	{
		srcResult.replace(nd, 9, "���57.00Ԫ");
	}
	nd = -1;
	nd = srcResult.find("#m311.6070");
	if (nd >= 0)
	{
		srcResult.replace(nd, 10, "���331.60Ԫ");
	}
	nd = -1;
	nd = srcResult.find("E463.60Ԫ");
	if (nd >= 0)
	{
		srcResult.replace(nd, 9, "���463.60Ԫ");
	}
	nd = -1;
	nd = srcResult.find("ܿ�׵���");
	if (nd >= 0)
	{
		srcResult.replace(nd, 8, "���׵���");
	}
	nd = -1;
	nd = srcResult.find("���׵���");
	if (nd >= 0)
	{
		srcResult.replace(nd, 8, "���׵���");
	}
	nd = -1;
	nd = srcResult.find("����i����");
	if (nd >= 0)
	{
		srcResult.replace(nd, 9, "���׶���");
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
	nd = srcResult.find("�̡�Ʒ");
	if (nd >= 0)
	{
		srcResult.replace(nd, 6, "��Ʒ");
	}
	nd = -1;
	nd = srcResult.find("CeԪ��");
	if (nd >= 0)
	{
		srcResult.replace(nd, 6, "��ƷԪ��");
	}
	nd = -1;
	nd = srcResult.find("%&Ԫ��");
	if (nd >= 0)
	{
		srcResult.replace(nd, 6, "��ƷԪ��");
	}
	nd = -1;
	nd = srcResult.find("��&Ԫ��");
	if (nd >= 0)
	{
		srcResult.replace(nd, 7, "��ƷԪ��");
	}
	nd = -1;
	nd = srcResult.find("B-?Ԫ��");
	if (nd >= 0)
	{
		srcResult.replace(nd, 7, "��ƷԪ��");
	}
	nd = -1;
	nd = srcResult.find("����Ԫ��");
	if (nd >= 0)
	{
		srcResult.replace(nd, 8, "��ƷԪ��");
	}
	nd = -1;
	nd = srcResult.find("֧��ʱ��_");
	if (nd >= 0)
	{
		srcResult.replace(nd, 9, "֧��ʱ��");
	}

	nd = -1;
	nd = srcResult.find("���׵���_");
	if (nd >= 0)
	{
		srcResult.replace(nd, 9, "���׵���");
	}
	nd = -1;
	nd = srcResult.find("���׵��š�");
	if (nd >= 0)
	{
		srcResult.replace(nd, 10, "���׵���");
	}
	nd = -1;
	nd = srcResult.find("#4#%-42");
	if (nd >= 0)
	{
		srcResult.replace(nd, 7, "���׵���42");
	}

	nd = -1;
	nd = srcResult.find("�̻�����_");
	if (nd >= 0)
	{
		srcResult.replace(nd, 9, "�̻�����");
	}
	nd = -1;
	nd = srcResult.find("�̻����š�");
	if (nd >= 0)
	{
		srcResult.replace(nd, 10, "�̻�����");
	}
	nd = -1;
	nd = srcResult.find("HPRS-");
	if (nd >= 0)
	{
		srcResult.replace(nd, 5, "�̻�����");
	}
	nd = -1;
	nd = srcResult.find("�ĸ�ʱ�䡦");
	if (nd >= 0)
	{
		srcResult.replace(nd, 10, "֧��ʱ��");
	}
	nd = -1;
	nd = srcResult.find("֧������");
	if (nd >= 0)
	{
		srcResult.replace(nd, 8, "֧����ʽ");
	}
	nd = -1;
	nd = srcResult.find("�޸����롵");
	if (nd >= 0)
	{
		srcResult.replace(nd, 9, "�޸�����");
	}
	nd = -1;
	nd = srcResult.find("product201");
	if (nd >= 0)
	{
		srcResult.replace(nd, 10, "product_201");
	}
	nd = -1;
	nd = srcResult.find("�����ɶ���");
	if (nd >= 0)
	{
		srcResult.replace(nd, 10, "���׶���");
	}
	nd = -1;
	nd = srcResult.find("%4�ɶ���");
	if (nd >= 0)
	{
		srcResult.replace(nd, 8, "���׶���");
	}
	nd = -1;
	nd = srcResult.find("�޸Ŀ���");
	if (nd >= 0)
	{
		srcResult.replace(nd, 8, "�޸�����");
	}
	nd = -1;
	nd = srcResult.find("�޸��ܸ�");
	if (nd >= 0)
	{
		srcResult.replace(nd, 8, "�޸�����");
	}
	nd = -1;
	nd = srcResult.find("����״̬");
	if (nd >= 0)
	{
		srcResult.replace(nd, 8, "��ǰ״̬");
	}
	return true;
}

//************************************
// Method:    ProcessResultAndWriteTxt������ʶ���������������̨
// FullName:  ProcessResultAndWriteTxt
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: string result��ʶ����
// Parameter: string img_path��ͼƬ·��
//************************************
void ProcessResult(string strSrcResult, string img_path)
{

	if (strSrcResult.empty() || img_path.empty())
	{
		return;
	}

	bool isQQImg = isQQ(strSrcResult);
	bool isWeChatImg = isWeChat(strSrcResult);
	//��ȡ��ǰͼƬ��
	string strImageName = img_path;
	int nIdx = strImageName.rfind('\\');
	strImageName = strImageName.substr(nIdx + 1, strImageName.size() - nIdx);	//ͼƬ����

	if (isQQImg)
	{
		//��ǰ��ͼΪQQ��ͼ
		string g_str1 = "�̻�����";		// �̻�����
		string g_str2 = "�޸�����";		// �޸�����
		string g_str3 = "���";			// ���
		string g_str4 = "�������";		// �������
		string g_str5 = "��Ʒ";			// ��Ʒ

		int nIndex1 = -1;	//ǰ�±�
		int nIndex2 = -1;	//���±�

		//��ȡ���
		//ͨ����ȡ�������ǰ�ַ������ͺ��ַ�����Ʒ���򡰶�������λ�ã���ȡ�����м���Ӵ����ǽ���������ַ���
		//���ǰ��λ�ö�û���ҵ�������Ϊû��ʶ������������ҵ�����һ����λ�ã���ͨ����ǰ���������ȡ��������������ַ���
		//�õ���������ַ�����ȷ���ַ�'.'С�����λ�ã����û���ҵ�'.'������Ϊ�ַ����Ǵ�ġ�
		//�ҵ�'.'��λ�ú���ǰ��ȡΪ���ֵ��ַ�������ȡ��λ�ַ������ǻ��ѽ����ַ���
		nIndex1 = (int)strSrcResult.find(g_str3);	//������λ��
		nIndex2 = (int)strSrcResult.find(g_str4);	//����������λ��
		if (nIndex2 < 0)
		{
			nIndex2 = (int)strSrcResult.find(g_str5); // ����Ʒ����λ��
		}
		string strMoney = "";	//���
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
			string g_strTmp = strSrcResult.substr(nIndex1, nIndex2 - nIndex1);
			int g_nIdx = g_strTmp.find('.');
			if (g_nIdx < 0)
			{
				nIndex2 = strSrcResult.find("Ԫ��");
				if (nIndex2 >= 0)
				{
					g_strTmp = strSrcResult.substr(nIndex2 - 12, 12);
				}
			}
			g_nIdx = g_strTmp.find('.');
			if (g_nIdx >= 0)
			{
				string g_money = ".";
				for (int i = g_nIdx-1; i > 0; i--)
				{
					if (g_strTmp[i] >= '0' && g_strTmp[i] <= '9' && g_money.size() <= 4)
					{
						g_money = g_strTmp[i] + g_money;
					}
					else
					{
						break;
					}
				}
				strMoney = g_money + g_strTmp.substr(g_nIdx + 1, 2);
			}
			else
			{
				strMoney = strImageName;
			}
		}
		cout << strMoney << endl;

		//��ȡ����ʱ��
		//����ȫ����Ѱ��"2018-"��"2019-"��Ȼ������λ�ÿ�ʼ��ȡ22���ַ���ͨ���ж�22���ַ��������ַ���������14����ȷ������ʱ�����һ���ַ���λ��
		//Ȼ���ȡ����ַ������ڵ�ʮ���ַ���߼���һ���ո�
		//���û���ҵ�"2018-"��"2019-"���߼�鵽��ȡ��22���ַ��������ַ�����14��������Ϊ�ַ���ʶ�����
		int g_n1 = (int)strSrcResult.find("2018-");
		int g_n2 = (int)strSrcResult.find("2019-");
		nIndex1 = (g_n1 >= g_n2) ? g_n1 : g_n2;
		string strTime = "";	//����ʱ��
		if (nIndex1 >= 0)
		{
			string g_strTmp = strSrcResult.substr(nIndex1, 22);
			int g_nIdx = 0;
			int g_num = 0;
			for (int i = 0; i < g_strTmp.size(); i++)
			{
				g_nIdx = i;
				if (g_num == 14)
				{
					break;
				}
				if (g_strTmp[i] >= '0' && g_strTmp[i] <= '9')
				{
					g_num++;
				}
				
			}

			if (g_num >= 14)
			{
				g_strTmp = g_strTmp.substr(0, g_nIdx);
				strTime = g_strTmp.substr(0, 10);
				strTime += ' ';
				strTime += g_strTmp.substr(10, g_nIdx - 10);
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

		//��ȡ���׶���
		//���׶�������"10000"��ͷ������ȷ��"10000"��λ�ã�Ȼ��ȷ���ַ���"�̻�����"��λ�ã�"�̻�����"�ڽ��׶����ŵĺ���
		//���û���ҵ�"�̻�����",���"10000"��ȡ34���ַ��������˽��׶����ŵĳ��ȣ��������ַ��ж��ǲ��������ַ�������������������ַ��ģ���Ϊ�ҵ���β��
		//����ҵ�"�̻�����"�����"10000"��ʼ��"�̻�����"���ַ���Ϊ���׶����š�
		//���û���ҵ�"10000"������Ϊû��ʶ�𵽽��׶���
		nIndex1 = (int)strSrcResult.find("10000");
		nIndex2 = (int)strSrcResult.find(g_str1);
		string strTransactionOrder = "";	//���׶���
		if (nIndex1 >= 0)
		{
			if (nIndex2 < 0 || nIndex2 < nIndex1)
			{
				strTransactionOrder = strSrcResult.substr(nIndex1, 34);
				string g_strTmp = "";
				for (int i = 0; i < strTransactionOrder.size(); i++)
				{
					if (strTransactionOrder[i] >= '0' && strTransactionOrder[i] <= '9')
					{
						g_strTmp += strTransactionOrder[i];
					}
					else
					{
						break;
					}
				}
				strTransactionOrder = g_strTmp;
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

		//��ȡ�̻�����
		//�̻���������"qqpro_"��ͷ�������ȼ����û��"qqpro_"��Ȼ������û��"�޸�����"���󲿷��̻������ź�߶���"�޸�����")
		//���"qqpro_"û���ҵ�����Ϊû��ʶ���̻�����
		//��ȡ"qqpro_"��"�޸�����"�м���ַ������û���ҵ�"�޸�����",���"qqpro_"��ȡ���ַ�����β��
		//Ȼ��Խ�ȡ���ַ�������ַ��ж��ǲ��������ַ����������������ַ��ĵط�����������ȡ�����̻�����
		nIndex1 = (int)strSrcResult.find("qqpro_");
		nIndex2 = (int)strSrcResult.find(g_str2);
		string strMerchantOrder = "";	//�̻�����
		if (nIndex1 >= 0)
		{
			//��ס���ŵĽ�β����ֹ���ֵ��ź�������ݵ����
			if (nIndex2 < 0 || nIndex2 < nIndex1)
			{
				nIndex2 = strSrcResult.size();
			}
			strMerchantOrder = strSrcResult.substr(nIndex1, (nIndex2 - nIndex1));
			string g_temp = "";
			for (int i = 0; i < strMerchantOrder.size(); i++)
			{
				if (strMerchantOrder[i] >= '0' && strMerchantOrder[i] <= '9')
				{
					g_temp += strMerchantOrder[i];
				}
			}
			strMerchantOrder = "qqpro_" + g_temp;
		}
		else
		{
			strMerchantOrder = strImageName;
		}
		cout << strMerchantOrder << endl;
	}
	else if (isWeChatImg)
	{
		//��ͼΪ΢��ͼƬ
		string g_str1 = "�̻�����";	// �̻�����
		string g_str2 = "�ڴ��̻�";	// �ڴ��̻�
		string g_str3 = "��ֵ����";
		string g_str4 = "��ǰ״̬";

		int nIndex1 = -1;
		int nIndex2 = -1;
		//�õ��������
		//ͨ����ȡ�������ǰ�ַ�"��ֵ����"�ͺ��ַ�"��ǰ״̬"��λ�ã���ȡ�����м���Ӵ����ǽ���������ַ���
		//���ǰ��λ�ö�û���ҵ�������Ϊû��ʶ������������ҵ�����һ����λ�ã���ͨ����ǰ���������ȡ��������������ַ���
		//�õ���������ַ�����ȷ���ַ�'.'С������ַ�'-'���ŵ�λ��
		//��ȡ'-'�ź�'.'֮����ַ���'.'��������ַ����Ƕ������
		nIndex1 = strSrcResult.find(g_str3);
		nIndex2 = strSrcResult.find(g_str4);
		string strMoney = "";  //���
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
			string g_strTmp = strSrcResult.substr(nIndex1, nIndex2 - nIndex1);
			int nIdx1 = g_strTmp.find('-');
			int nIdx2 = g_strTmp.find('.');
			if (nIdx1 >= 0 && nIdx2 >= 0)
			{
				strMoney = g_strTmp.substr(nIdx1 + 1, nIdx2 - nIdx1 - 1);
				for (int i = 0; i < strMoney.size(); i++)
				{
					if (strMoney[i] < '0' || strMoney[i] > '9')
					{
						strMoney.erase(i, 1);
					}
				}
				strMoney += g_strTmp.substr(nIdx2, 3);
			}
			else
			{
				strMoney = strImageName;
			}
		}
		cout << strMoney << endl;

		//�õ�֧��ʱ��
		//����ȫ����Ѱ��"2018-"��"2019-"��Ȼ������λ�ÿ�ʼ��ȡ22���ַ���ͨ���ж�22���ַ��������ַ���������14����ȷ������ʱ�����һ���ַ���λ��
		//Ȼ���ȡ����ַ������ڵ�ʮ���ַ���߼���һ���ո�
		//���û���ҵ�"2018-"��"2019-"���߼�鵽��ȡ��22���ַ��������ַ�����14��������Ϊ�ַ���ʶ�����
		int g_n1 = (int)strSrcResult.find("2018-");
		int g_n2 = (int)strSrcResult.find("2019-");
		nIndex1 = g_n1 > g_n2 ? g_n1 : g_n2;
		string strTime = "";	//֧��ʱ��
		if (nIndex1 >= 0)
		{
			string g_strTmp = strSrcResult.substr(nIndex1, 22);
			int g_nIdx = 0;
			int g_num = 0;
			for (int i = 0; i < g_strTmp.size(); i++)
			{
				g_nIdx = i;
				if (g_num == 14)
				{
					break;
				}
				if (g_strTmp[i] >= '0' && g_strTmp[i] <= '9')
				{
					g_num++;
				}
			}
			if (g_num >= 14)
			{
				g_strTmp = g_strTmp.substr(0, g_nIdx);
				strTime = g_strTmp.substr(0, 10);
				strTime += ' ';
				strTime += g_strTmp.substr(10, g_nIdx - 10);
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

		//�õ����׵���
		//���׵�����"42000"��ͷ������ȷ��"42000"��λ�ã�Ȼ��ȷ���ַ���"�̻�����"��λ�ã�"�̻�����"�ڽ��׵��ŵĺ���
		//����ҵ�"�̻�����"�����"42000"��ʼ��"�̻�����"���ַ���Ϊ���׶����š�
		//���û���ҵ�"�̻�����",���"42000"��ȡ30���ַ��������˽��׵��ŵĳ��ȣ��������ַ��ж��ǲ��������ַ�������������������ַ��ģ���Ϊ�ҵ���β��
		//���û���ҵ�"42000"������Ϊû��ʶ�𵽽��׵���
		nIndex1 = (int)strSrcResult.find("42000");
		nIndex2 = (int)strSrcResult.find(g_str1);
		string strTransactionNumber = "";	//���׵���
		if (nIndex1 >= 0)
		{
			if (nIndex2 >= 0)
			{
				strTransactionNumber = strSrcResult.substr(nIndex1, (nIndex2 - nIndex1));
			}
			else
			{
				strTransactionNumber = strSrcResult.substr(nIndex1, 30);
				string g_strTmp = "";
				for (int i = 0; i < strTransactionNumber.size(); i++)
				{
					if (strTransactionNumber[i] >= '0' && strTransactionNumber[i] <= '9')
					{
						g_strTmp += strTransactionNumber[i];
					}
					else
					{
						break;
					}
				}
				strTransactionNumber = g_strTmp;
			}
		}
		else
		{
			strTransactionNumber = strImageName;
		}
		cout << strTransactionNumber << endl;

		//�õ��̻�����
		//�̻�������"product_"��ͷ�������ȼ����û��"product_"��Ȼ������û��"�ڴ��̻�"���󲿷��̻����ź�߶���"�ڴ��̻�")
		//���"product_"û���ҵ�����Ϊû��ʶ���̻�����
		//��ȡ"product_"��"�ڴ��̻�"�м���ַ������û���ҵ�"�ڴ��̻�",���"qqpro_"��ȡ���ַ�����β��
		//Ȼ��Խ�ȡ���ַ�������ַ��ж��ǲ��������ַ����������������ַ��ĵط�����������ȡ�����̻�����
		nIndex1 = (int)strSrcResult.find("product_");
		nIndex2 = (int)strSrcResult.find(g_str2);
		string strMerchantNumber  = "";		//�̻�����
		if (nIndex1 >= 0)
		{
			if (nIndex2 < 0)
			{
				nIndex2 = strSrcResult.size();
			}
			strMerchantNumber = strSrcResult.substr(nIndex1, (nIndex2 - nIndex1));
			string g_strTmp = "";
			for (int i = 0; i < strMerchantNumber.size(); i++)
			{
				if (strMerchantNumber[i] >= '0' && strMerchantNumber[i] <= '9')
				{
					g_strTmp += strMerchantNumber[i];
				}
			}
			strMerchantNumber = "product_" + g_strTmp;
		}
		else
		{
			strMerchantNumber = strImageName;
		}
		cout << strMerchantNumber << endl;
	}
	else
	{
		//û�б��ϳ���΢�Ż���qqͼƬ
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
		//cout << "�밴exe·����ͼƬ·����ʽ���������" << endl;
		return 1;
	}
	//string qq = argv[1];

	string img_path = argv[1]; //   "C:\\Users\\White\\Desktop\\test\\327.png";

	Mat inputImg = imread(img_path);
	if (inputImg.empty())
	{
		//cout << "ͼƬ�����ڣ���" << endl;
		return 1;
	}
	if (inputImg.rows < inputImg.cols)
	{
		//cout << "����" << endl;
		return 1;
	}

	//��ͼƬ������ͨ����ֵ������150�ĵط���ͻ��Ϊ0�ĺ�ɫ
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

// 	imshow("��ǿ", inputImg);
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
	

	//����Ƿ��д�
	bool bChe = checkError(srcResult);
	if (!bChe)
	{
		return -1;
	}
	//cout << srcResult << endl;

	ProcessResult(srcResult, img_path);

	//cout << srcResult << endl;
	//16.png��
	return 0;
}
