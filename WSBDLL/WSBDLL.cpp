// WSBDLL.cpp : ���� DLL Ӧ�ó���ĵ���������
//
#include "stdafx.h"
#include <atlstr.h>
#include <stdlib.h>
#include "MyCode.h"
#include <WinSock2.h>
#include "iostream"
#include <io.h>
#include <direct.h>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <thread>
#include "json\json.h"
#include "scan\chuankou.h"
#pragma comment(lib,"ws2_32.lib")
#include <comdef.h>
#include <string.h>
#include <ctime>
#include <chrono>
#include <sstream>
//AES����ͷ�ļ�
//#include "aes.h";
//#include "aes_encryptor.h";
//ʹ��Cryptoo++��
#include "CryptoPP\include\aes.h";
#include "CryptoPP\include\rijndael.h";
#include "CryptoPP\include\randpool.h";
#include "CryptoPP\include\rsa.h";
#include "CryptoPP\include\hex.h";
#include "CryptoPP\include\filters.h";
#include "CryptoPP\include\modes.h";
//#pragma comment(lib, "cryptlib.lib")
//#pragma comment(lib,"JsonLib.lib")
using namespace std;
using namespace CryptoPP;

//���������״̬,��ʼֵΪ0����֤�������Ϊ-1���Ǻ�����Ϊ1
int is_black = 0;
//�ۺ���Ϣ�����ӿڼ�����ʱ��
const int T = 200;
LPCSTR CONDLL = "Cap_RW.dll";
LPCSTR iniFileName = "./ChgCity.ini";
LPSTR RIZHI = "debug.log";
LPSTR PREUPLOADFILE = "C:/PreUpload.dat";
//ȫ�����֤����
char ALLIDCARD[20] = { 0 };
//ȫ�ֵ��ӽ�������ά����Ϣ
char ALLQRCODE[100] = { 0 };
//�û���Ϣ
Json::Value js_vl;
//���ܺ���û���Ϣ
Json::Value js_dep;
//ȫ�ֿͻ���������
char CUSNAME[128] = { 0 };
//��ʱ����ʼʱ��
clock_t N = 0;
//
long R = 1;
//��ά��ӿڵ��ÿ���
int COM_OPEN = 0;
//Ѱ��ѭ������
bool SWITCH_QCARD = true;
HMODULE hdllInst = LoadLibraryA("KeeperClient.dll");
/*
	����MIS�ӿڶԽ�
*/
typedef struct
{
	char TransType[2]; //����ָ��
	char FuncID[4]; //������ɫ�ű�ID��
	char TransAmount[12]; //���׽��
	char TipAmount[12]; //С�ѽ��
	char TransDate[8]; //��������

	char MisTraceNo[6];	//MIS��ˮ��
	char CardNo[19]; //���׿���
	char ExpDate[4]; //��Ƭ��Ч��
	char Track2[37]; //���ŵ���Ϣ
	char Track3[104]; //���ŵ���Ϣ

	char ReferNo[8]; //ϵͳ������
	char AuthNo[6]; //��Ȩ��
	char MultiId[12]; //���̻����������� 
	char TerminalId[15]; //�����ն˺�
	char InstallmentTimes[2]; //��������

	char PreInput[256]; //Ԥ������ ����˵��1
	char AddDatas[256]; //�̶������� ����˵��2
	char QRCardNO[50]; //��ά��֧����
	char QROrderNo[50]; //��ά�붩����
	char PrintData[512]; //��ɫ��ӡ����
	char pospBak[60]; //������������
#ifdef ANDROID_MISPOS_TEST
	char StartDate[8]; //��ʼ����

	char EndDate[8]; //��������
	char PosHint[60]; //POS��Ļ��ʾ��Ϣ
	char HintType[1]; //POS������Ϣ��ʾ��ʽ 0-���� 1-�Ǻ�
					  //add by 2018-11-28 PHT
	char PGSInfo[32]; //PGS��Ϣ
	char ScanHead[1]; //ǰ����ɨ���־ 0��ǰ��ɨ����1������ɨ����
	char ScanTime[2]; //ɨ�볬ʱ
	char ScanUpInfo[40]; //ɨ����Ϸ���ʾ��Ϣ�����20����
	char ScanDnInfo[40]; //ɨ����·���ʾ��Ϣ�����20����
						 //add end
#endif
	char platId[20]; //��������

	char operId[20]; //����Ա��
	char CARDSLOT[2]; //
	char CARDAPDUSEND[300];
} ST_MISPOS_IN;
typedef struct
{
	char TransType[2]; //����ָ��
	char CardNo[19]; //���׿���
	char Amount[12]; //���׽��
	char TipAmount[12]; //С�ѽ��
	char TransTime[6]; //����ʱ��

	char TransDate[8]; //��������
	char ExpDate[4]; //��Ƭ��Ч��
	char Track2[37]; //���ŵ���Ϣ
	char Track3[104]; //���ŵ���Ϣ
	char ReferNo[8]; //ϵͳ������

	char AuthNo[6]; //��Ȩ��
	char RspCode[2]; //������
	char TerminalId[15]; //�����ն˺�
	char MerchantId[12]; //�����̻���
	char YLMerchantId[15]; //�����̻���

	char InstallmentTimes[2]; //��������
	char TCData[256]; //IC������
	char MerchantNameEng[50]; //Ӣ���̻�����
	char MerchantNameChs[40]; //�����̻�����
	char TerminalTraceNo[6]; //�ն���ˮ��

	char TerminalBatchNo[6]; //�ն����κ�
	char IcCardId[4]; //IC�����к�
	char BankName[20]; //����������
	char TransName[20]; //���Ľ�������
	char CardType[20]; //����� 

	char TotalInfo[800]; //���׻�����Ϣ����ӡ����ʱ��Ҫ
	char RspMessage[100]; //����ʧ��ʱ��MISPOSϵͳ�������Ĵ���������Ϣ
	char Remark[300]; //��ע��Ϣ
	char WTrace[24]; //�⿨��ˮ��
	char AIDDAT[34]; //AID(IC��������)

	char APPLBL[20]; //APPLABEL(IC��������)
	char APPNAM[20]; //APPNAME(IC��������)
	char ElecTotal[32]; //�ѻ����׻�����Ϣ
	char SettleAmount[12];//ʵ�۽��
	char QROrderNo[50]; //��ά�붩����
	char QRMemo[300]; /*��ά���Ż�֧����Ϣ:( ���ֵֿ�12+����ȯ�ֿ۽��12+�Ż�ȯ�ֿ۽��12+��������12+�̻�����12+������30���ֶ�ȫΪ�����ַ�������Ŀǰ���жԸ��ֶε�����ǳ��ȿɱ䣬���ֶο���Ϊ�գ�Ҳ����ֻ��һ�������ţ�����Ľ�����Ҳ��δ���ģ��п���һ����Ҳ���ܶ���������Թ���ʵ�ʷ���Ϊ׼������ϵͳ���Ҫ��������ý�����չ�ռ�)*/
	char refNum[23]; //23λ�����ο���
#ifdef ANDROID_MISPOS_TEST
	char PosInput[60]; //���������������
					   //add by 2018-11-28 PHT
	char ScanData[100]; //ɨ������
						//add end
						//add by 2018-12-05 PHT
	char PayCode[1]; //��ά��֧������ 1: ������ά��2: ������ά��3: ΢��֧�� 4: ֧����֧��
					 //add end
#endif
	char platId[20]; //��������
	char operId[20]; //����Ա��
	char CARDAPDURECV[300];
} ST_MISPOS_OUT;

typedef int(WINAPI *_mistrans)(void* input, void* output);
void DeleteAllMark(string &str, const string &mark)
{
	size_t nsize = mark.size();
	while (true)
	{
		size_t pos = str.find(mark);
		if (pos == string::npos)
		{
			return;
		}
		else
		{
			str.erase(pos, nsize);
		}
	}
}
string TransDate(char* jydt)
{
	std::string str_dt(jydt);
	std::string str_trunce;
	while (str_dt.find("-") != -1)
	{
		str_trunce = str_dt.replace(str_dt.find("-"), 1, "");
	}
	while (str_dt.find(":") != -1)
	{
		str_trunce = str_dt.replace(str_dt.find(":"), 1, "");
	}
	while (str_dt.find(" ") != -1)
	{
		str_trunce = str_dt.replace(str_dt.find(" "), 1, "");
	}
	return str_trunce;
}
//ͨ�������ļ���ȡ�ֶε�ֵ
LPSTR GetValueInIni(char* className, char* objName, LPCSTR fileName)
{
	LPSTR LP_PATH = new char[MAX_PATH];
	LPSTR rt_Value = new char[128];
	strcpy(LP_PATH, fileName);
	GetPrivateProfileStringA(className, objName, "NULL", rt_Value, 128, LP_PATH);
	delete[] LP_PATH;
	return rt_Value;
}
//д�������־
void W_ReadCardLog(const char* str)
{
	LPSTR MSG = GetValueInIni("MIS", "SHOWLOG", iniFileName);
	if (strcmp(MSG, "YES") == 0)
	{
		char* dir_path = "./Log";
		if (_access("./Log", 0) == -1)
		{
			_mkdir("./Log");
		}
		char log_name[128];
		char cur_time[24];
		time_t t = time(0);
		strftime(log_name, sizeof(log_name), "./Log/ReadCard%Y%m%d.log", localtime(&t));
		strftime(cur_time, sizeof(cur_time), "%Y-%m-%d %H:%M:%S", localtime(&t));
		ofstream fin;
		fin.open(log_name, std::ios::app);
		fin << cur_time << "\t" << str << endl;
		fin.close();
	}
}
LPSTR subchar(char *schar, int index, int len)
{
	char *tmp = new char[len + 1];
	//W_ReadCardLog("subchar line1");
	memcpy(tmp, "0x00", sizeof(tmp));
	//W_ReadCardLog("subchar line2");

	int _strlen = strlen(schar);
	if ((index + len) <= _strlen + 1)
	{
		//W_ReadCardLog("subchar line3");

		memcpy(tmp, schar + index, len);
		//W_ReadCardLog("subchar line4");

		tmp[len] = '\0';
		//W_ReadCardLog("subchar line5");

	}
	return tmp;
}
//�����񽡿�������
int _stdcall GetBankCardNo(char* bankNo)
{
	//HMODULE Inst = LoadLibraryA("KeeperClient.dll");
	_mistrans trans = (_mistrans)GetProcAddress(hdllInst, "misposTrans");

	ST_MISPOS_IN st_in;
	ST_MISPOS_OUT st_out;
	memset(&st_in, 0x00, sizeof(ST_MISPOS_IN));
	memset(&st_out, 0x00, sizeof(ST_MISPOS_OUT));
	LPSTR _mistradeno = GetValueInIni("MIS", "MisTraceNo", iniFileName);
	memcpy(st_in.TransType, "55", 2);	//�������ͣ���ֵ
	memcpy(st_in.MisTraceNo, _mistradeno, 6);
	//memcpy(st_in.operId, "01", 20);
	//memcpy(st_in.platId, "a1", 20);
	int rc = trans(&st_in, &st_out);
	if (0 == rc)
	{
		//��ȡ���п���
		std::string strTemp(subchar(st_out.TransType, 1586, 20));
		strTemp.erase(strTemp.find_first_of(" "));
		strcpy(bankNo, strTemp.c_str());
	}
	//memcpy(tac, st_out.ReferNo, sizeof(st_out.ReferNo));
	//memcpy(psamID, st_out.TerminalId, sizeof(st_out.TerminalId));
	//FreeLibrary(Inst);
	char log[100] = { 0 };
	sprintf(log, "�����֤���뷵�أ�%d", rc);
	W_ReadCardLog(log);
	return rc;
}

string _stdcall Stu2json(ST_MISPOS_OUT st, LPSTR idcardno)
{
	Json::Value root;
	Json::FastWriter fw;
	root["TransType"] = subchar(st.TransType, 0, 2);
	root["CardNo"] = subchar(st.CardNo, 0, 19);
	root["Amount"] = subchar(st.Amount, 0, 12);
	root["TipAmount"] = subchar(st.TipAmount, 0, 12);
	root["TransTime"] = subchar(st.TransTime, 0, 6);
	root["TransDate"] = subchar(st.TransDate, 0, 8);
	//root["ExpDate"] = subchar(st.TransType, 0, 2);
	//root["Track2"] = st.Track2;
	//root["Track3"] = st.Track3;
	root["ReferNo"] = subchar(st.ReferNo, 0, 8);
	root["AuthNo"] = subchar(st.AuthNo, 0, 6);
	root["RspCode"] = subchar(st.RspCode, 0, 2);
	root["TerminalId"] = subchar(st.TerminalId, 0, 15);
	root["MerchantId"] = subchar(st.MerchantId, 0, 12);
	root["YLMerchantId"] = subchar(st.YLMerchantId, 0, 15);
	root["IcCardId"] = subchar(st.IcCardId, 0, 4);
	root["TerminalTraceNo"] = subchar(st.TerminalTraceNo, 0, 6);
	root["idCard"] = idcardno;

	/*root["MerchantNameEng"] = st.MerchantNameEng;
	root["MerchantNameChs"] = st.MerchantNameChs;
	root["TerminalBatchNo"] = st.TerminalBatchNo;
	root["BankName"] = st.BankName;
	root["TransName"] = st.TransName;
	root["CardType"] = st.CardType;
	root["TotalInfo"] = st.TotalInfo;
	root["RspMessage"] = st.RspMessage;
	root["Remark"] = st.Remark;
	root["WTrace"] = st.WTrace;
	root["AIDDAT"] = st.AIDDAT;
	root["APPLBL"] = st.APPLBL;
	root["APPNAM"] = st.APPNAM;
	root["ElecTotal"] = st.ElecTotal;
	root["SettleAmount"] = st.SettleAmount;
	root["QROrderNo"] = st.QROrderNo;
	root["QRMemo"] = st.QRMemo;
	root["operId"] = st.operId;
	root["platId"] = st.platId;
	root["InstallmentTimes"] = st.InstallmentTimes;
	root["TCData"] = st.TCData;*/
	//W_ReadCardLog(subchar(st.TransType, 0, 626));
	//root["transType"] = subchar(st.TransType, 0, 2);
	//std::string str_cardno(subchar(st.TransType, 2, 19));
	//int n = str_cardno.find_first_of(" ");
	//if (n != -1)
	//{
	//	str_cardno.erase(n);
	//}
	//W_ReadCardLog("cardNo");
	//root["cardNo"] = str_cardno;
	//std::string str_temp(subchar(st.TransType, 21, 12));
	//std::string str_amount = str_temp.substr(str_temp.find_first_not_of("0"));
	//root["amount"] = str_amount;
	//W_ReadCardLog("amount");

	//root["transTime"] = subchar(st.TransType, 45, 6);
	//W_ReadCardLog("transTime");

	//root["transDate"] = subchar(st.TransType, 51, 8);
	//W_ReadCardLog("transDate");

	//root["track2"] = subchar(st.TransType, 63, 37);
	//W_ReadCardLog("track2");

	//root["referNo"] = subchar(st.TransType, 204, 8);
	//W_ReadCardLog("referNo");

	//root["authNo"] = subchar(st.TransType, 212, 6);
	//W_ReadCardLog("authNo");

	//root["rspCode"] = subchar(st.TransType, 218, 2);
	//W_ReadCardLog("rspCode");

	//root["terminalId"] = subchar(st.TransType, 220, 15);
	//W_ReadCardLog("terminalId");

	//root["merchantId"] = subchar(st.TransType, 235, 12);
	//W_ReadCardLog("merchantId");

	//root["yLMerchantId"] = subchar(st.TransType, 247, 15);
	//W_ReadCardLog("yLMerchantId");

	////root["merchantNameChs"] = subchar(st.TransType, 570, 40);
	//root["terminalTraceNo"] = subchar(st.TransType, 610, 6);
	//W_ReadCardLog("terminalTraceNo");

	//root["icCardId"] = subchar(st.TransType, 622, 4);
	//W_ReadCardLog("icCardId");

	//root["bankName"] = subchar(st.TransType, 626, 20);
	//root["platId"] = st.platId;
	//root["operId"] = st.operId;
	//string str_json = root.toStyledString();
	string str_json = fw.write(root);
	//ȥ���ո�
	DeleteAllMark(str_json, " ");
	W_ReadCardLog(str_json.c_str());
	return str_json;
}


int _stdcall GetBCNorIDC(char* misTradeNo, char* info, int* type)
{
	//HMODULE Inst = LoadLibraryA("KeeperClient.dll");
	_mistrans trans = (_mistrans)GetProcAddress(hdllInst, "misposTrans");

	ST_MISPOS_IN st_in;
	ST_MISPOS_OUT st_out;
	memset(&st_in, 0x00, sizeof(ST_MISPOS_IN));
	memset(&st_out, 0x00, sizeof(ST_MISPOS_OUT));
	memcpy(st_in.TransType, "56", 2);	//�������ͣ���ֵ
	memcpy(st_in.MisTraceNo, misTradeNo, 6);
	int rc = trans(&st_in, &st_out);
	if (0 == rc)
	{
		//��ȡ���п���
		std::string strTemp(st_out.Remark);
		strTemp.erase(strTemp.find_first_of(" "));
		strcpy(info, strTemp.c_str());
		*type = int(st_out.CardType[0]);
	}
	//memcpy(tac, st_out.ReferNo, sizeof(st_out.ReferNo));
	//memcpy(psamID, st_out.TerminalId, sizeof(st_out.TerminalId));
	//FreeLibrary(Inst);
	return rc;
}
void TransCharacter(const char* input, char* output)
{
	int _wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, input, strlen(input), NULL, 0);
	wchar_t* _wszString = new wchar_t[_wcsLen + 1];
	//ת��
	::MultiByteToWideChar(CP_UTF8, NULL, input, strlen(input), _wszString, _wcsLen);
	//������'\0'
	_wszString[_wcsLen] = '\0';
	_bstr_t _b(_wszString);
	strcpy(output, _b);
}

/*
	�¿��սӿڶԽ�
*/
//int seq = 1;
/*
�������ͨ�ӿں���
*/
//������
typedef long(WINAPI *opCom)();
//�ر�����
typedef void(WINAPI *closeCom)();
//Ѱ��
typedef long(WINAPI *querycard)(long*);
//��ȡ�û���Ϣ
typedef long(WINAPI *getcardinfo)(CUSTOMERINFO*);
//�ۿ�
typedef long(WINAPI *setcardinfo)(long, long, long, LPSTR, __int64*, long*, __int64*);
//5.6.	�ۿ�Ӵ�/���޶�ܣ�
typedef long(WINAPI *setcardinfoLMT)(long, long, long, LPSTR, long, long, __int64*, long*, long*);
//5.7.	�ۿ���޶����֤�������ѣ�
typedef long(WINAPI *setcardinfoVerify)(long, long, long, LPSTR, long, long, LPSTR, __int64*, long*, long*);
//5.8.	�������ۼ�����
typedef long(WINAPI *updatecardstatus)(long, LPSTR);
//5.9.	���¿���/���޶�
typedef long(WINAPI *setcardstatus)(long, long);
//5.10.	��������
typedef long(WINAPI *setcardPWD)(LPSTR, LPSTR);
//5.11.	��ֵ��ʼ��
typedef long(WINAPI *chargeInit)(long, long, __int64*, long*, long*, long*, long*);
//��ֵ
typedef long(WINAPI *capcharge)(LPSTR, LPSTR, LPSTR);
//5.12.	�ۿTAC�����ַ�����
typedef long(WINAPI *setcardinfo_str)(long, long, long, LPSTR, __int64*, long*, char*, int);
//5.13.	��ȡtacֵ
typedef long(WINAPI *gettac)(long, LPSTR);
//��ȡʮ�ν��׼�¼
typedef long(WINAPI *readrecords)(CONSUMEINFO*);

//�ۿ�,PSAM_IDʹ��LPSTR����
typedef long(WINAPI *setcardinfo_temp)(long, long, long, LPSTR, LPSTR, long*, char*, int);
//5.15.�ۿpsam���š�TAC�����ַ�����
typedef long(WINAPI *setcardinfo_str1)(long, long, long, LPSTR, char*, long*, char*, int);
/*
������񽡿����ӿں���
*/
//6.1.2	���豸
typedef HANDLE(WINAPI *opendevice)(int);
//6.1.3	�ر��豸
typedef int(WINAPI *closedevice)(HANDLE);
//6.1.4	�豸��λ
typedef int(WINAPI *poweron)(HANDLE, int, char*);
//6.1.5	����ָ��
typedef int(WINAPI *sendapdu)(HANDLE, unsigned char, unsigned char*, unsigned long, unsigned char*, int*);
//6.2.1	�������������������ļ��ӿ�
typedef int(WINAPI *r_ddf1ef05)(HANDLE, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*);
//6.2.2	���ֿ��˻�����Ϣ�����ļ��ӿ�
typedef int(WINAPI *r_ddf1ef06)(HANDLE, char*, char*, char*, char*, char*);
//����Ч�ڵ��ļ��ӿ�
typedef int(WINAPI *r_ddf1ef08)(HANDLE, char*, char*, char*, char*, char*, char*);
//д��Ч�ڵ��ļ��ӿ�
typedef int(WINAPI *w_ddf1ef08)(HANDLE, char*, char*, char*, char*, char*, char*);
//����ַ��Ϣ�ļ��ӿ�
typedef int(WINAPI *r_df01ef05)(HANDLE, char*, char*, char*, char*);
//д��ַ��Ϣ�ļ��ӿ�
typedef int(WINAPI *w_df01ef05)(HANDLE, char*, char*, char*, char*);
//����ϵ����Ϣ�ļ��ӿ�
typedef int(WINAPI *r_df01ef06)(HANDLE, char*, char*, char*, char*, char*, char*, char*, char*, char*);
//д��ϵ����Ϣ�ļ��ӿ�
typedef int(WINAPI *w_df01ef06)(HANDLE, char*, char*, char*, char*, char*, char*, char*, char*, char*);
//��ְҵ������Ϣ�ļ��ӿ�
typedef int(WINAPI *r_df01ef07)(HANDLE, char*, char*, char*);
//дְҵ������Ϣ�ļ��ӿ�
typedef int(WINAPI *w_df01ef07)(HANDLE, char*, char*, char*);
//��֤����¼��Ϣ�ļ��ӿ�
typedef int(WINAPI *r_df01ef08)(HANDLE, char*, char*, char*, char*);
//д֤����¼��Ϣ�ļ��ӿ�
typedef int(WINAPI *w_df01ef08)(HANDLE, char*, char*, char*, char*);
//���ٴ����������ļ��ӿ�
typedef int(WINAPI *r_df02ef05)(HANDLE, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*);
//д�ٴ����������ļ��ӿ�
typedef int(WINAPI *w_df02ef05)(HANDLE, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*);
//��������Ϣ�����ļ��ӿ�
typedef int(WINAPI *r_df02ef06)(HANDLE, char*);
//д������Ϣ�����ļ��ӿ�
typedef int(WINAPI *w_df02ef06)(HANDLE, char*);
//���������������ļ��ӿ�
typedef int(WINAPI *r_df02ef07)(HANDLE, int, char*, char*);
//д�������������ļ��ӿ�
typedef int(WINAPI *w_df02ef07)(HANDLE, char*, char*);
//�����߻��������ļ��ӿ�
typedef int(WINAPI *r_df02ef08)(HANDLE, int, char*, char*);
//д���߻��������ļ��ӿ�
typedef int(WINAPI *w_df02ef08)(HANDLE, char*, char*);
//��סԺ��Ϣ�����ļ��ӿ�
typedef int(WINAPI *r_df03ef05)(HANDLE, char*, char*, char*);
//дסԺ��Ϣ�����ļ��ӿ�
typedef int(WINAPI *w_df03ef05)(HANDLE, int);
//����סԺ��Ϣ�����ļ��ӿ�
typedef int(WINAPI *e_df03ef05)(HANDLE, int);
//��������Ϣ�����ļ��ӿ�
typedef int(WINAPI *r_df03ef06)(HANDLE, char*, char*, char*, char*, char*);
//д������Ϣ�����ļ��ӿ�
typedef int(WINAPI *w_df03ef06)(HANDLE, int);
//����������Ϣ�����ļ��ӿ�
typedef int(WINAPI *e_df03ef06)(HANDLE, int);
//��סԺ��Ϣ�ļ��ӿ�
typedef int(WINAPI *r_df03ee)(HANDLE, int, char*, int, int, int);
//дסԺ��Ϣ�ļ��ӿ�
typedef int(WINAPI *w_df03ee)(HANDLE, int, char*, int, int, int);
//����������Ϣ�ļ��ӿ�
typedef int(WINAPI *r_df03ed)(HANDLE, int, char*, int, int, int);
//д��������Ϣ�ļ��ӿ�
typedef int(WINAPI *w_df03ed)(HANDLE, int, char*, int, int, int);
//6.3.1	SM3ժҪ
typedef int(WINAPI *sm3)(HANDLE, BYTE*, int, BYTE*, BYTE*);
//6.3.2	PIN��֤����
typedef int(WINAPI *verifypin)(HANDLE, const char*, BYTE*);
//6.3.3	SM2ǩ������
typedef int(WINAPI *sm2)(HANDLE, BYTE*, BYTE, BYTE*, BYTE*);
//��ȡ�豸���к���Ϣ
typedef int(WINAPI *getcsn)(HANDLE, char*);
//��ȡSAM������Ϣ
typedef int(WINAPI *getsam)(HANDLE, char*);
//д�����������������ļ��ӿ�
typedef int(WINAPI *w_ddf1ef05)(HANDLE, char*, char*, char*, char*, char*, char*, char*, char*, char*, char*);
//д�ֿ��˻�����Ϣ�����ļ��ӿ�
typedef int(WINAPI *w_ddf1ef06)(HANDLE, char*, char*, char*, char*, char*);
//����Ƭ�ļ��ӿ�
typedef int(WINAPI *r_df1ef07)(HANDLE, char*);
//д��Ƭ�ļ��ӿ�
typedef int(WINAPI *w_df1ef07)(HANDLE, char*);
//��ȡסԺ�����Žӿ�
typedef int(WINAPI *get_eeindex)(HANDLE);
//��ȡ���������Žӿ�
typedef int(WINAPI *get_edindex)(HANDLE);
//������Ա��Ϣ��ʼ��
typedef int(WINAPI *lockinfo)(HANDLE);

//����ҽԺ���ƽӿڣ����������������������
typedef int(WINAPI *getinfo_his)(HANDLE, char*, long*, char*, char*, char*, char*);

/*========================================MD5����ʵ��=======================================================*/
typedef  unsigned  char  *POINTER;
typedef  unsigned  short  int  UINT2;
typedef  unsigned  long  int  UINT4;

typedef  struct
{
	UINT4  state[4];
	UINT4  count[2];
	unsigned  char  buffer[64];
}  MD5_CTX;


void  MD5Init(MD5_CTX  *);
void  MD5Update(MD5_CTX  *, unsigned  char  *, unsigned  int);
void  MD5Final(unsigned  char[16], MD5_CTX  *);

#define  S11  7 
#define  S12  12 
#define  S13  17 
#define  S14  22 
#define  S21  5 
#define  S22  9 
#define  S23  14 
#define  S24  20 
#define  S31  4 
#define  S32  11 
#define  S33  16 
#define  S34  23 
#define  S41  6 
#define  S42  10 
#define  S43  15 
#define  S44  21 

static  unsigned  char  PADDING[64] = {
	0x80,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

#define  F(x,  y,  z)  (((x)  &  (y))  |  ((~x)  &  (z))) 
#define  G(x,  y,  z)  (((x)  &  (z))  |  ((y)  &  (~z))) 
#define  H(x,  y,  z)  ((x)  ^  (y)  ^  (z)) 
#define  I(x,  y,  z)  ((y)  ^  ((x)  |  (~z))) 

#define  ROTATE_LEFT(x,  n)  (((x)  <<  (n))  |  ((x)  >>  (32-(n)))) 

#define  FF(a,  b,  c,  d,  x,  s,  ac)  {   (a)  +=  F  ((b),  (c),  (d))  +  (x)  +  (UINT4)(ac);   (a)  =  ROTATE_LEFT  ((a),  (s));   (a)  +=  (b);    } 
#define  GG(a,  b,  c,  d,  x,  s,  ac)  {   (a)  +=  G  ((b),  (c),  (d))  +  (x)  +  (UINT4)(ac);   (a)  =  ROTATE_LEFT  ((a),  (s));   (a)  +=  (b);    } 
#define  HH(a,  b,  c,  d,  x,  s,  ac)  {   (a)  +=  H  ((b),  (c),  (d))  +  (x)  +  (UINT4)(ac);   (a)  =  ROTATE_LEFT  ((a),  (s));   (a)  +=  (b);    } 
#define  II(a,  b,  c,  d,  x,  s,  ac)  {   (a)  +=  I  ((b),  (c),  (d))  +  (x)  +  (UINT4)(ac);   (a)  =  ROTATE_LEFT  ((a),  (s));   (a)  +=  (b);  } 


inline  void  Encode(unsigned  char  *output, UINT4  *input, unsigned  int  len)
{
	unsigned  int  i, j;

	for (i = 0, j = 0; j < len; i++, j += 4) {
		output[j] = (unsigned  char)(input[i] & 0xff);
		output[j + 1] = (unsigned  char)((input[i] >> 8) & 0xff);
		output[j + 2] = (unsigned  char)((input[i] >> 16) & 0xff);
		output[j + 3] = (unsigned  char)((input[i] >> 24) & 0xff);
	}
}

inline  void  Decode(UINT4  *output, unsigned  char  *input, unsigned  int  len)
{
	unsigned  int  i, j;

	for (i = 0, j = 0; j < len; i++, j += 4)
		output[i] = ((UINT4)input[j]) | (((UINT4)input[j + 1]) << 8) |
		(((UINT4)input[j + 2]) << 16) | (((UINT4)input[j + 3]) << 24);
}

inline  void  MD5Transform(UINT4  state[4], unsigned  char  block[64])
{
	UINT4  a = state[0], b = state[1], c = state[2], d = state[3], x[16];
	Decode(x, block, 64);
	FF(a, b, c, d, x[0], S11, 0xd76aa478);
	FF(d, a, b, c, x[1], S12, 0xe8c7b756);
	FF(c, d, a, b, x[2], S13, 0x242070db);
	FF(b, c, d, a, x[3], S14, 0xc1bdceee);
	FF(a, b, c, d, x[4], S11, 0xf57c0faf);
	FF(d, a, b, c, x[5], S12, 0x4787c62a);
	FF(c, d, a, b, x[6], S13, 0xa8304613);
	FF(b, c, d, a, x[7], S14, 0xfd469501);
	FF(a, b, c, d, x[8], S11, 0x698098d8);
	FF(d, a, b, c, x[9], S12, 0x8b44f7af);
	FF(c, d, a, b, x[10], S13, 0xffff5bb1);
	FF(b, c, d, a, x[11], S14, 0x895cd7be);
	FF(a, b, c, d, x[12], S11, 0x6b901122);
	FF(d, a, b, c, x[13], S12, 0xfd987193);
	FF(c, d, a, b, x[14], S13, 0xa679438e);
	FF(b, c, d, a, x[15], S14, 0x49b40821);
	GG(a, b, c, d, x[1], S21, 0xf61e2562);
	GG(d, a, b, c, x[6], S22, 0xc040b340);
	GG(c, d, a, b, x[11], S23, 0x265e5a51);
	GG(b, c, d, a, x[0], S24, 0xe9b6c7aa);
	GG(a, b, c, d, x[5], S21, 0xd62f105d);
	GG(d, a, b, c, x[10], S22, 0x2441453);
	GG(c, d, a, b, x[15], S23, 0xd8a1e681);
	GG(b, c, d, a, x[4], S24, 0xe7d3fbc8);
	GG(a, b, c, d, x[9], S21, 0x21e1cde6);
	GG(d, a, b, c, x[14], S22, 0xc33707d6);
	GG(c, d, a, b, x[3], S23, 0xf4d50d87);
	GG(b, c, d, a, x[8], S24, 0x455a14ed);
	GG(a, b, c, d, x[13], S21, 0xa9e3e905);
	GG(d, a, b, c, x[2], S22, 0xfcefa3f8);
	GG(c, d, a, b, x[7], S23, 0x676f02d9);
	GG(b, c, d, a, x[12], S24, 0x8d2a4c8a);
	HH(a, b, c, d, x[5], S31, 0xfffa3942);
	HH(d, a, b, c, x[8], S32, 0x8771f681);
	HH(c, d, a, b, x[11], S33, 0x6d9d6122);
	HH(b, c, d, a, x[14], S34, 0xfde5380c);
	HH(a, b, c, d, x[1], S31, 0xa4beea44);
	HH(d, a, b, c, x[4], S32, 0x4bdecfa9);
	HH(c, d, a, b, x[7], S33, 0xf6bb4b60);
	HH(b, c, d, a, x[10], S34, 0xbebfbc70);
	HH(a, b, c, d, x[13], S31, 0x289b7ec6);
	HH(d, a, b, c, x[0], S32, 0xeaa127fa);
	HH(c, d, a, b, x[3], S33, 0xd4ef3085);
	HH(b, c, d, a, x[6], S34, 0x4881d05);
	HH(a, b, c, d, x[9], S31, 0xd9d4d039);
	HH(d, a, b, c, x[12], S32, 0xe6db99e5);
	HH(c, d, a, b, x[15], S33, 0x1fa27cf8);
	HH(b, c, d, a, x[2], S34, 0xc4ac5665);
	II(a, b, c, d, x[0], S41, 0xf4292244);
	II(d, a, b, c, x[7], S42, 0x432aff97);
	II(c, d, a, b, x[14], S43, 0xab9423a7);
	II(b, c, d, a, x[5], S44, 0xfc93a039);
	II(a, b, c, d, x[12], S41, 0x655b59c3);
	II(d, a, b, c, x[3], S42, 0x8f0ccc92);
	II(c, d, a, b, x[10], S43, 0xffeff47d);
	II(b, c, d, a, x[1], S44, 0x85845dd1);
	II(a, b, c, d, x[8], S41, 0x6fa87e4f);
	II(d, a, b, c, x[15], S42, 0xfe2ce6e0);
	II(c, d, a, b, x[6], S43, 0xa3014314);
	II(b, c, d, a, x[13], S44, 0x4e0811a1);
	II(a, b, c, d, x[4], S41, 0xf7537e82);
	II(d, a, b, c, x[11], S42, 0xbd3af235);
	II(c, d, a, b, x[2], S43, 0x2ad7d2bb);
	II(b, c, d, a, x[9], S44, 0xeb86d391);
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	memset((POINTER)x, 0, sizeof(x));
}

inline  void  MD5Init(MD5_CTX  *context)
{
	context->count[0] = context->count[1] = 0;
	context->state[0] = 0x67452301;
	context->state[1] = 0xefcdab89;
	context->state[2] = 0x98badcfe;
	context->state[3] = 0x10325476;
}

inline  void  MD5Update(MD5_CTX  *context, unsigned  char  *input, unsigned  int  inputLen)
{
	unsigned  int  i, index, partLen;

	index = (unsigned  int)((context->count[0] >> 3) & 0x3F);
	if ((context->count[0] += ((UINT4)inputLen << 3))
		< ((UINT4)inputLen << 3))
		context->count[1]++;
	context->count[1] += ((UINT4)inputLen >> 29);

	partLen = 64 - index;

	if (inputLen >= partLen) {
		memcpy((POINTER)&context->buffer[index], (POINTER)input, partLen);
		MD5Transform(context->state, context->buffer);

		for (i = partLen; i + 63 < inputLen; i += 64)
			MD5Transform(context->state, &input[i]);
		index = 0;
	}
	else
		i = 0;

	memcpy((POINTER)&context->buffer[index], (POINTER)&input[i], inputLen - i);
}

inline  void  MD5Final(unsigned  char  digest[16], MD5_CTX  *context)
{
	unsigned  char  bits[8];
	unsigned  int  index, padLen;

	Encode(bits, context->count, 8);
	index = (unsigned  int)((context->count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	MD5Update(context, PADDING, padLen);
	MD5Update(context, bits, 8);
	Encode(digest, context->state, 16);
	memset((POINTER)context, 0, sizeof(*context));
}

void  MD5Digest(char  *pszInput, unsigned  long  nInputSize, char  *pszOutPut)
{
	MD5_CTX  context;
	unsigned  int  len = strlen(pszInput);

	MD5Init(&context);
	MD5Update(&context, (unsigned  char  *)pszInput, len);
	MD5Final((unsigned  char  *)pszOutPut, &context);
}
/*========================================BASE64ת��=======================================================*/

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
std::string base64_encode(char* bytes_to_encode, unsigned int in_len) {
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--) {
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';

	}

	return ret;

}
/*========================================�Զ��巽��=======================================================*/

///����������ȡIP
BOOL GetIpByDomainName(char *szHost, char* szIp)
{
	WSADATA        wsaData;

	HOSTENT   *pHostEnt;
	int             nAdapter = 0;
	struct       sockaddr_in   sAddr;
	if (WSAStartup(0x0101, &wsaData))
	{
		//printf(" gethostbyname error for host:\n");
		return FALSE;
	}

	pHostEnt = gethostbyname(szHost);
	if (pHostEnt)
	{
		if (pHostEnt->h_addr_list[nAdapter])
		{
			memcpy(&sAddr.sin_addr.s_addr, pHostEnt->h_addr_list[nAdapter], pHostEnt->h_length);
			sprintf(szIp, "%s", inet_ntoa(sAddr.sin_addr));
		}
	}
	else
	{
		//      DWORD  dwError = GetLastError();
		//      CString  csError;
		//      csError.Format("%d", dwError);
	}
	WSACleanup();
	return TRUE;
}

//д��̶�Ŀ¼��־
void W_log(const char* str)
{
	char* dir_path = "./Log";
	if (_access("./Log", 0) == -1)
	{
		_mkdir("./Log");
	}
	char log_name[128];
	char shijian[24];
	time_t t = time(0);
	strftime(log_name, sizeof(log_name), "./Log//%Y%m%d.log", localtime(&t));
	strftime(shijian, sizeof(shijian), "%Y-%m-%d %H:%M:%S", localtime(&t));

	ofstream fin;
	fin.open(log_name, std::ios::app);
	char HeadLine[128] = { 0 };
	sprintf(HeadLine, "################################%s --Begin################################", shijian);
	fin << shijian << ":\t" << str << endl;
	fin.close();
}


void W_UploadLog(const char* str)
{
	char* dir_path = "./Log//Upload";
	if (_access(dir_path, 0) == -1)
	{
		_mkdir(dir_path);
	}
	char log_name[128];
	char shijian[24];
	time_t t = time(0);
	strftime(log_name, sizeof(log_name), "./Log//Upload//%Y%m%d.log", localtime(&t));
	strftime(shijian, sizeof(shijian), "%Y-%m-%d %H:%M:%S", localtime(&t));

	ofstream fin;
	fin.open(log_name, std::ios::app);
	char HeadLine[128] = { 0 };
	sprintf(HeadLine, "################################%s --Begin################################", shijian);
	fin << HeadLine << "\r\n" << str << endl;
	fin.close();
}
//д���ı���filename���ı�·��+�ļ���,str_to_write����Ҫд�������
void WriteInFile(char* filename, std::string str_to_write)
{
	std::ofstream fout(filename, std::ios::app);
	fout << str_to_write.c_str();
	fout.close();
}
BYTE s_key[CryptoPP::AES::DEFAULT_KEYLENGTH], s_iv[CryptoPP::AES::BLOCKSIZE];
//��ʼ��key��IV
void initKV()
{
	/*memset(s_key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
	memset(s_iv, 0x00, CryptoPP::AES::BLOCKSIZE);*/
	char tempk[] = "xudutonghis20196";
	char tempiv[] = "1234560405060708";

	/*char tempk[] = "1234567890123456";
	char tempiv[] = "0000000000000000";*/
	for (int i = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH; i++)
	{
		s_key[i] = tempk[i];
	}
	for (int j = 0; j < CryptoPP::AES::BLOCKSIZE; j++)
	{
		s_iv[j] = tempiv[j];
	}
}
//AES CBCģʽ����
string encrypt(const string& plainText)
{
	string cipherText;
	CryptoPP::AES::Encryption aesEncryption(s_key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, s_iv);
	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(cipherText));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plainText.c_str()), plainText.length());
	stfEncryptor.MessageEnd();

	string cipherTextHex;
	for (int i = 0; i < cipherText.size(); i++)
	{
		char ch[3] = { 0 };
		sprintf(ch, "%02x", static_cast<BYTE>(cipherText[i]));
		cipherTextHex += ch;
	}
	return cipherTextHex;
}
//AES CBCģʽ����
string decrypt(string cipherTextHex)
{
	string cipherText;
	string decryptedText;

	int i = 0;
	while (true)
	{
		char c;
		int x;
		stringstream ss;
		ss << hex << cipherTextHex.substr(i, 2).c_str();
		ss >> x;
		c = (char)x;
		cipherText += c;
		if (i >= cipherTextHex.length() - 2)break;
		i += 2;
	}

	//  
	CryptoPP::AES::Decryption aesDecryption(s_key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, s_iv);
	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedText));
	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(cipherText.c_str()), cipherText.size());

	stfDecryptor.MessageEnd();

	return decryptedText;
}
/*
�˷���������ȡ��Ƭ�ĺ�����״̬
��ڲ�����
ip			socket��������ַ
port		socket�������˿�
uid			��Ƭuid
���ڲ�����
recv_buf	�����������ַ�
����ֵ��
-1			WSA����ʧ��
-2			socket failed
-3			socket����ʧ��
-4			���������������ʧ��
0			�ɹ�
*/
long _stdcall GetBlackList(const char *ip, short port, long uid, char *recv_buf)
{
	W_ReadCardLog("EVENT ���ú���GetBlackList��ʼ");
	char _log[64] = { 0 };
	sprintf(_log, "PARA UID:%ld", uid);
	W_ReadCardLog(_log);
	const int BUF_SIZE = 64;
	WSADATA         wsd;            //WSADATA����  
	SOCKET          sHost;          //�������׽���  
	SOCKADDR_IN     servAddr;       //��������ַ  
	char            buf[BUF_SIZE];  //�������ݻ�����  
	int             retVal;         //����ֵ  
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		W_ReadCardLog("ERROR -1 WSA����ʧ��");
		return -1;		//WSA����ʧ��
	}
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost)
	{
		W_ReadCardLog("ERROR -2 socket failed");
		WSACleanup();
		return -2;		//socket failed
	}
	//�������׽��ֵ�ַ
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	servAddr.sin_addr.s_addr = inet_addr(ip);

	//���ӷ�����
	retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));
	if (SOCKET_ERROR == retVal)
	{
		W_ReadCardLog("ERROR -3 ����ʧ��");
		closesocket(sHost);
		WSACleanup();
		return -3;		//����ʧ��
	}
	//���������������
	ZeroMemory(buf, BUF_SIZE);
	itoa(uid, buf, 10);
	//strcpy(buf, asn);	//����ȫ
	retVal = send(sHost, buf, strlen(buf), 0);
	if (SOCKET_ERROR == retVal)
	{
		W_ReadCardLog("ERROR -4 ����ʧ��");
		closesocket(sHost);
		WSACleanup();
		return -4;		//����ʧ��
	}
	char* recvbuf = recv_buf;
	recv(sHost, recvbuf, 1, 0);
	closesocket(sHost); //�ر��׽���  
	WSACleanup();       //�ͷ��׽�����Դ  
	W_ReadCardLog("INFO socket��֤���");
	return  0;
}

//��ȡ��������֤���ӳ�ʱʱ�����ƣ�
long _stdcall GetBlack_limit(const char *ip, short port, long uid, char *recv_buf)
{
	const int BUF_SIZE = 64;
	WSADATA         wsd;            //WSADATA����  
	SOCKET          sHost;          //�������׽���  
	SOCKADDR_IN     servAddr;       //��������ַ  
	char            buf[BUF_SIZE];  //�������ݻ�����  
	timeval			tm;
	//char            bufRecv[BUF_SIZE];
	int             retVal;         //����ֵ  
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		return -1;		//WSA����ʧ��
	}
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost)
	{
		WSACleanup();
		return -2;		//socket failed
	}
	//�������׽��ֵ�ַ
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	servAddr.sin_addr.s_addr = inet_addr(ip);

	//���ó�ʱʱ��
	fd_set set;
	int error = -1;
	int len = sizeof(int);
	unsigned long ul = 1;
	ioctlsocket(sHost, FIONBIO, &ul); //����Ϊ������ģʽ
	bool ret = false;
	if (connect(sHost, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1)
	{
		tm.tv_sec = 5;	//��ʱʱ�䣬��λ��
		tm.tv_usec = 0;
		FD_ZERO(&set);
		FD_SET(sHost, &set);
		if (select(sHost + 1, NULL, &set, NULL, &tm) > 0)
		{
			getsockopt(sHost, SOL_SOCKET, SO_ERROR, (char *)&error, &len);
			if (error == 0)
			{
				ret = true;
			}
			else
			{
				ret = false;
			}
		}
		else
		{
			ret = false;
		}
	}
	else
	{
		ret = true;
	}
	ul = 0;
	ioctlsocket(sHost, FIONBIO, &ul);
	if (!ret)
	{
		closesocket(sHost);
		return -101;
	}
	else
	{
		//���������������
		ZeroMemory(buf, BUF_SIZE);
		itoa(uid, buf, 10);
		//strcpy(buf, asn);	//����ȫ
		retVal = send(sHost, buf, strlen(buf), 0);
		if (SOCKET_ERROR == retVal)
		{
			closesocket(sHost);
			WSACleanup();
			return -4;		//����ʧ��
		}
		char* recvbuf = recv_buf;
		recv(sHost, recvbuf, 1, 0);
		closesocket(sHost); //�ر��׽���  
		WSACleanup();       //�ͷ��׽�����Դ  
		return  0;
	}
}
//����POST����
//long SendPostRequest(const char *ip, short port, char *bufSend, char *recv_buf)
//{
//	W_ReadCardLog("EVENT ���ú���SendPostRequest��ʼ");
//	const int BUF_SIZE = 64;
//	WSADATA         wsd;            //WSADATA����  
//	SOCKET          sHost;          //�������׽���  
//	SOCKADDR_IN     servAddr;       //��������ַ  
//	char            buf[BUF_SIZE];  //�������ݻ�����  
//	int             retVal;         //����ֵ  
//	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
//	{
//		W_ReadCardLog("ERROR -1 WSA����ʧ��");
//		return -1;		//WSA����ʧ��
//	}
//	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (INVALID_SOCKET == sHost)
//	{
//		W_ReadCardLog("ERROR -2 socket failed");
//
//		WSACleanup();
//		return -2;		//socket failed
//	}
//	//�������׽��ֵ�ַ
//	servAddr.sin_family = AF_INET;
//	servAddr.sin_port = htons(port);
//	servAddr.sin_addr.s_addr = inet_addr(ip);
//
//	//���ӷ�����
//	retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));
//	if (SOCKET_ERROR == retVal)
//	{
//		W_ReadCardLog("ERROR -3 ����ʧ��");
//		closesocket(sHost);
//		WSACleanup();
//		return -3;		//����ʧ��
//	}
//	//���������������
//	ZeroMemory(buf, BUF_SIZE);
//	retVal = send(sHost, bufSend, strlen(bufSend), 0);
//	string str = bufSend;
//	if (SOCKET_ERROR == retVal)
//	{
//		W_ReadCardLog("ERROR -4 ����ʧ��");
//		closesocket(sHost);
//		WSACleanup();
//		return -4;		//����ʧ��
//	}
//	char* recvbuf = recv_buf;
//	recv(sHost, recvbuf, 1024, 0);
//	//W_ReadCardLog(recvbuf);
//	closesocket(sHost); //�ر��׽���  
//	WSACleanup();       //�ͷ��׽�����Դ  
//	return  0;
//}
//long QrCodePay()
//{
//	Json::Value sendvalue;
//	string orgcode(GetValueInIni("MIS", "ORGCODE", iniFileName));
//	string serialNo(GetValueInIni("MIS", "SERIALNO", iniFileName));
//	sendvalue["organizationCode"] = orgcode;
//	sendvalue["serialNumber"] = serialNo;
//	sendvalue["method"] = "pay";
//	//ʹ��17λʱ�����Ϊ������
//	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
//		std::chrono::system_clock::now().time_since_epoch());
//	sendvalue["content"]["orderNo"] = ms.count();
//	sendvalue["content"]["orderTime"] = jyDT;
//	sendvalue["content"]["txnAmt"] = opFare;
//	sendvalue["content"]["termId"] = atoll(GetValueInIni("MIS", "TERMID", iniFileName));//�ն˺�
//	sendvalue["content"]["reqType"] = "��������";
//	sendvalue["content"]["couponInfo"] = 0;
//	sendvalue["content"]["qrNo"] = _info;
//	sendvalue["content"]["merId"] = GetValueInIni("MIS", "MERID", iniFileName);
//	sendvalue["content"]["merCatCode"] = GetValueInIni("MIS", "MERCATCODE", iniFileName);
//	sendvalue["content"]["merName"] = GetValueInIni("MIS", "MERNAME", iniFileName);
//	string sendJson = sendvalue.toStyledString();
//	char _send_buff[1024] = { 0 };
//	memcpy(_send_buff, sendJson.c_str(), 1024);
//	W_ReadCardLog(_send_buff);
//	//�ύ�ӿ�
//	LPSTR req_ip;
//	req_ip = GetValueInIni("MIS", "BCNIP", iniFileName);
//	short _port = GetPrivateProfileIntA("MIS", "BCNPORT", 80, iniFileName);
//	char req_resv[1024] = { 0 };
//	long ret_sendpost = SendPostRequest(req_ip, _port, _send_buff, req_resv);
//	if (0 == ret_sendpost)
//	{
//		char _rev_temp[1024] = { 0 };
//		TransCharacter(req_resv, _rev_temp);
//		//��ȡjson
//		string str_rev(_rev_temp);
//		string json_rel;
//		int json_bg = str_rev.find_first_of("{", 0);
//		int json_end = str_rev.find_last_of("}");
//		if (json_end > json_bg)
//		{
//			json_rel = str_rev.substr(json_bg, json_end - json_bg + 1);
//			W_ReadCardLog(json_rel.c_str());
//			//����Jsonʾ����
//			//{"code":"R00000","content":{"data":{"orderNo":"1558334758179","payResult":"�ɹ�","autoCode":"0","termId":"1"}},"desc":"֧���ɹ�","flag":1}
//			//����json
//			Json::Value root;
//			//js_vl.clear();
//			Json::Reader reader;
//			try
//			{
//				if (reader.parse(json_rel, root))
//				{
//					if (root["flag"].asString() == "1")
//					{
//						W_ReadCardLog("INFO ��ѯ�ɹ�");
//						//�������
//						*psamID = atoll(GetValueInIni("MIS", "TERMID", iniFileName));
//						*tac = ms.count();
//						*psamJyNo = atol(root["content"]["data"]["autoCode"].asString().c_str());
//						return 0;
//					}
//					else
//					{
//						W_ReadCardLog("ERROR ��ѯʧ��");
//						return -11;
//					}
//				}
//			}
//			catch (const std::exception&ex)
//			{
//				return -13;
//			}
//
//		}
//		else
//		{
//			W_ReadCardLog("ERROR ������Ϣ��ʽ����");
//			return -12;
//		}
//	}
//	else
//	{
//		return ret_sendpost;
//	}
//}
//��ȡ�����ļ�IP��ַ
long SendPostRequest(const char *ip, short port, char *bufSend, char *recv_buf)
{
	W_ReadCardLog("EVENT ���ú���SendPostRequest��ʼ");
	const int BUF_SIZE = 64;
	WSADATA         wsd;            //WSADATA����  
	SOCKET          sHost;          //�������׽���  
	SOCKADDR_IN     servAddr;       //��������ַ  
	char            buf[BUF_SIZE];  //�������ݻ�����  
	timeval			tm;
	//char            bufRecv[BUF_SIZE];
	int             retVal;         //����ֵ  
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		W_ReadCardLog("ERROR -1 WSA����ʧ��");
		return -1;		//WSA����ʧ��
	}
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost)
	{
		W_ReadCardLog("ERROR -2 socket failed");

		WSACleanup();
		return -2;		//socket failed
	}
	//�������׽��ֵ�ַ
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	servAddr.sin_addr.s_addr = inet_addr(ip);

	//���ó�ʱʱ��
	fd_set set;
	int error = -1;
	int len = sizeof(int);
	unsigned long ul = 1;
	ioctlsocket(sHost, FIONBIO, &ul); //����Ϊ������ģʽ
	bool ret = false;
	W_ReadCardLog("before connect");
	if (connect(sHost, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1)
	{
		W_ReadCardLog("connect failed");
		tm.tv_sec = 5;	//��ʱʱ�䣬��λ��
		tm.tv_usec = 0;
		FD_ZERO(&set);
		FD_SET(sHost, &set);
		if (select(sHost + 1, NULL, &set, NULL, &tm) > 0)
		{
			W_ReadCardLog("select true");
			getsockopt(sHost, SOL_SOCKET, SO_ERROR, (char *)&error, &len);
			if (error == 0)
			{
				ret = true;
			}
			else
			{
				ret = false;
			}
		}
		else
		{
			W_ReadCardLog("select false");
			ret = false;
		}
	}
	else
	{
		W_ReadCardLog("connect success");

		ret = true;
	}
	ul = 0;
	ioctlsocket(sHost, FIONBIO, &ul);
	if (!ret)
	{
		W_ReadCardLog("closesocket");
		closesocket(sHost);
		return -101;
	}
	else
	{
		ZeroMemory(buf, BUF_SIZE);
		retVal = send(sHost, bufSend, strlen(bufSend), 0);
		string str = bufSend;
		if (SOCKET_ERROR == retVal)
		{
			W_ReadCardLog("ERROR -4 ����ʧ��");
			closesocket(sHost);
			WSACleanup();
			return -4;		//����ʧ��
		}
		char* recvbuf = recv_buf;
		recv(sHost, recvbuf, 1024, 0);
		//W_ReadCardLog(recvbuf);
		closesocket(sHost); //�ر��׽���  
		WSACleanup();       //�ͷ��׽�����Դ  
		return  0;
	}
}
LPSTR _stdcall GetIPAddrINI()
{
	LPSTR LP_PATH = new char[MAX_PATH];
	LPSTR ipaddr = new char[20];
	strcpy(LP_PATH, "./ChgCity.ini");
	GetPrivateProfileStringA("SERVER", "IPADDR", "NULL", ipaddr, 20, LP_PATH);
	delete[] LP_PATH;
	return ipaddr;
}
//��ȡ�����ļ�port
short  GetPortINI()
{
	LPSTR LP_PATH = new char[MAX_PATH];
	strcpy(LP_PATH, "./ChgCity.ini");
	short port;
	port = GetPrivateProfileIntA("SERVER", "PORT", -1234, LP_PATH);
	delete[] LP_PATH;
	return port;
}

//ͨ��UID��֤������
long VerifiBlackCard_UID(long u_id)
{

	const char* ipaddr = GetIPAddrINI();
	short port = GetPortINI();
	char recv_buf = '9';
	long status = GetBlackList(ipaddr, port, u_id, &recv_buf);
	W_ReadCardLog("EVENT ���ú���GetBlackList����");
	if (status == 0)
	{
		if (recv_buf == '1')
		{
			return -777;
		}
		else if (recv_buf == '0')
		{
			return 0;
		}
		else
		{
			return -700;
		}
	}
	else
	{
		return -600;
	}
	//ȡ����֤������ʧ��ʱ�Ķ����֤����
	//if (status == 0)
	//{
	//	//socket����ֵΪ1����ʾ�˿�UID�ں���������
	//	if (recv_buf == '1')
	//	{
	//		is_black = -1;
	//		return 463;
	//	}
	//	//socket����ֵΪ2����ʾ�ӿڷ����쳣������������
	//	if (recv_buf == '2')
	//	{
	//		int i = 0;
	//		int max_count = 2;
	//		while ((recv_buf == '2') && (i < max_count))
	//		{
	//			GetBlackList(ipaddr, port, u_id, &recv_buf);
	//			i++;
	//		}
	//		switch (recv_buf)
	//		{
	//		case '2':
	//			is_black = 0;
	//			return 404;
	//			break;
	//		case '1':
	//			is_black = -1;
	//			return 463;
	//			break;
	//		case '0':
	//			is_black = 1;
	//			return 0;
	//			break;
	//		default:
	//			return 51;
	//			break;
	//		}
	//	}
	//	else
	//	{
	//		is_black = 1;
	//		return 0;
	//	}
	//}

	//else
	//{
	//	return 404;					//��������֤�ӿ������쳣
	//}
}

long WINAPI GetComInputInfo(LPSTR info)
{
	W_ReadCardLog("GetComInputInfo==================START");

	//HMODULE hdllInst = LoadLibraryA("KeeperClient.dll");
	_mistrans trans = (_mistrans)GetProcAddress(hdllInst, "misposTrans");

	ST_MISPOS_IN st_in;
	ST_MISPOS_OUT st_out;
	memset(&st_in, 0x00, sizeof(ST_MISPOS_IN));
	memset(&st_out, 0x00, sizeof(ST_MISPOS_OUT));
	memcpy(st_in.TransType, "54", 2);	//�������ͣ���ֵ
	LPSTR _mistradeno = GetValueInIni("MIS", "MisTraceNo", iniFileName);
	memcpy(st_in.MisTraceNo, _mistradeno, 6);
	int rc = trans(&st_in, &st_out);
	std::string strTemp(st_out.Remark);
	strTemp.erase(strTemp.find_last_not_of(" ") + 1);
	if (0 == rc)
	{
		//memcpy(info, st_out.Remark, sizeof(st_out.Remark));
		//strcpy(info, st_out.Remark);
		strcpy(info, strTemp.c_str());
	}
	//FreeLibrary(hdllInst);
	return rc;

}
//���ݹ������hashֵ
LPSTR _stdcall GetHash(char* appID, char* random, char* timestamp, char* hx_key)
{
	char _md5jiegou[16];
	/*char *x_key = hx_key;
	char *ppid = appID;
	char *andom = random;
	char *a_ts = timestamp;*/
	char sr[64];
	sprintf(sr, "%s%s%s%s", appID, timestamp, random, hx_key);
	MD5Digest(sr, strlen(sr), _md5jiegou);
	std::string a_hash = base64_encode(_md5jiegou, 16);
	return (char*)a_hash.data();
}
//�ϴ�MIS���Ѽ�¼
long UploadMisPost(string _json, char* host, char* url)
{
	char buf_Send[2048];
	sprintf(buf_Send,
		"POST %s HTTP/1.1\r\n"
		"Host: %s\r\n"
		"Cache-Control: no-cache\r\n"
		"Connection:Keep-Alive\r\n"
		"Accept-Encoding:gzip, deflate\r\n"
		"Accept-Language:zh-CN,en,*\r\n"
		"Content-Length:%d\r\n"
		"Content-Type:application/json\r\n\r\n"
		"%s", url, host, _json.length(), _json.c_str()
	);
	char req_resv[1024];
	char req_ip[24];
	GetIpByDomainName(host, req_ip);
	//2018-09-07 12:19	�˴��޸�Ϊ���ύpost֮ǰ����Ϣд���ύ��־��������������־���յ������д��
	W_UploadLog(buf_Send);
	short _port = GetPrivateProfileIntA("TransDetail", "PORT", 80, iniFileName);

	//�ύPOST
	long ret_sendpost = SendPostRequest(req_ip, _port, buf_Send, req_resv);
	char sendlog[64] = { 0 };
	sprintf(sendlog, "EVENT ���ú���SendPostRequest����,POST�����ύ���,����%ld", ret_sendpost);
	W_ReadCardLog(sendlog);
	if (0 == ret_sendpost)
	{
		char _rev_temp[1024] = { 0 };
		TransCharacter(req_resv, _rev_temp);
		//��ȡjson
		string str_rev(_rev_temp);
		W_ReadCardLog(str_rev.c_str());
		string json_rel;
		int json_bg = str_rev.find_first_of("{", 0);
		int json_end = str_rev.find_last_of("}");
		if (json_end > json_bg)
		{
			json_rel = str_rev.substr(json_bg, json_end - json_bg + 1);
			//д���ϴ���־
			/*string str_send(buf_Send);
			string str_log = str_send + json_rel;
			W_UploadLog(str_log.c_str());*/
			//ͬ�ϣ�ע�͵�������룬�˴��޸�Ϊ������������Ϣ����д��
			W_UploadLog(json_rel.c_str());
			//����json
			Json::Value jsvl;
			Json::Reader reader;
			if (reader.parse(json_rel, jsvl))
			{
				if (jsvl["flag"].asString() == "1")
				{
					W_ReadCardLog("INFO ������ϸ�ϴ�����");
					return 0;
				}
				else
				{
					W_ReadCardLog("ERROR ������ϸ�ϴ��쳣");
					return -11;
				}
			}
		}
		else
		{
			W_ReadCardLog("ERROR �ϴ��ӿڷ�����Ϣ��ʽ����");
			return -12;
		}
	}
	else
	{
		return ret_sendpost;
	}
}
long UploadMisBySocket(string _json)
{
	Json::Value root;
	Json::Value sendJson;
	Json::Reader reader;
	reader.parse(_json, root);
	string orgcode(GetValueInIni("MIS", "ORGCODE", iniFileName));
	string serialNo(GetValueInIni("MIS", "SERIALNO", iniFileName));
	sendJson["organizationCode"] = orgcode;
	sendJson["serialNumber"] = serialNo;
	sendJson["method"] = "posConsume";
	sendJson["content"]["amount"] = root["Amount"];
	sendJson["content"]["authNo"] = root["AuthNo"];
	sendJson["content"]["cardNo"] = root["CardNo"];
	sendJson["content"]["icCardId"] = root["IcCardId"];
	sendJson["content"]["idCard"] = root["idCard"];
	sendJson["content"]["merchantId"] = root["MerchantId"];
	sendJson["content"]["platId"] = root["PlatId"];
	sendJson["content"]["operId"] = root["OperId"];
	sendJson["content"]["referNo"] = root["ReferNo"];
	sendJson["content"]["rspCode"] = root["RspCode"];
	sendJson["content"]["terminalId"] = root["TerminalId"];
	sendJson["content"]["terminalTraceNo"] = root["TerminalTraceNo"];
	sendJson["content"]["track2"] = root["Track2"];
	sendJson["content"]["transDate"] = root["TransDate"];
	sendJson["content"]["transTime"] = root["TransTime"];
	sendJson["content"]["transType"] = root["TransType"];
	sendJson["content"]["yLMerchantId"] = root["YLMerchantId"];
	char jsonlog[1024];
	sprintf(jsonlog, "�������ݣ�%s,rootjosn��������:%s", _json.c_str(), root.toStyledString().c_str());
	W_ReadCardLog(jsonlog);
	char *req_ip = GetValueInIni("MIS", "BCNIP", iniFileName);
	short _port = GetPrivateProfileIntA("MIS", "BCNPORT", 80, iniFileName);
	char buf_Send[1024] = { 0 };
	strcpy(buf_Send, sendJson.toStyledString().c_str());
	char req_resv[1024] = { 0 };
	//�ύPOST
	long ret_sendpost = SendPostRequest(req_ip, _port, buf_Send, req_resv);
	char sendlog[1024] = { 0 };
	sprintf(sendlog, "EVENT ���ú���SendPostRequest����,POST�����ύ���,����%ld���������ݣ�%s", ret_sendpost, buf_Send);
	W_ReadCardLog(sendlog);
	if (0 == ret_sendpost)
	{
		char _rev_temp[1024] = { 0 };
		TransCharacter(req_resv, _rev_temp);
		//��ȡjson
		string str_rev(_rev_temp);
		W_ReadCardLog(str_rev.c_str());
		string json_rel;
		int json_bg = str_rev.find_first_of("{", 0);
		int json_end = str_rev.find_last_of("}");
		if (json_end > json_bg)
		{
			json_rel = str_rev.substr(json_bg, json_end - json_bg + 1);
			//д���ϴ���־
			/*string str_send(buf_Send);
			string str_log = str_send + json_rel;
			W_UploadLog(str_log.c_str());*/
			//ͬ�ϣ�ע�͵�������룬�˴��޸�Ϊ������������Ϣ����д��
			W_UploadLog(json_rel.c_str());
			//����json
			Json::Value jsvl;
			Json::Reader reader;
			if (reader.parse(json_rel, jsvl))
			{
				if (jsvl["flag"].asString() == "1")
				{
					W_ReadCardLog("INFO ������ϸ�ϴ�����");
					return 0;
				}
				else
				{
					W_ReadCardLog("ERROR ������ϸ�ϴ��쳣");
					return -11;
				}
			}
		}
		else
		{
			W_ReadCardLog("ERROR �ϴ��ӿڷ�����Ϣ��                                                                                                               ʽ����");
			return -12;
		}
	}
	else
	{
		return ret_sendpost;
	}
}
//post�ϴ����Ѽ�¼
long UploadDetailByPost(char* http_req, char* host, char* url)
{
	W_ReadCardLog("EVENT ���ú���UploadDetailByPost��ʼ");
	int _appid = GetPrivateProfileIntA("TransDetail", "appID", -1, iniFileName); //41;
	int _apptypeid = GetPrivateProfileIntA("TransDetail", "appTypeID", -1, iniFileName); //11;
	char *ip = GetValueInIni("TransDetail", "IP", iniFileName); //"192.168.10.205";
	char *hxKey = GetValueInIni("TransDetail", "key", iniFileName);
	//����hashֵ
	char md5jiegou[16];
	char *random = "1";
	SYSTEMTIME _st = { 0 };
	GetLocalTime(&_st);
	char ts[15];
	sprintf(ts, "%d%02d%02d%02d%02d%02d", _st.wYear, _st.wMonth, _st.wDay, _st.wHour, _st.wMinute, _st.wSecond);
	char shuru[64];
	sprintf(shuru, "%d%s%s%s", _appid, ts, random, hxKey);
	MD5Digest(shuru, strlen(shuru), md5jiegou);
	std::string hash = base64_encode(md5jiegou, 16);
	//hash�������
	Json::Value req;
	req["posCode"] = GetValueInIni("TransDetail", "posCode", iniFileName);//"090001000004";
	req["merchantNo"] = GetValueInIni("TransDetail", "MerchantNo", iniFileName);//"09000001";
	req["TestFlag"] = GetValueInIni("TransDetail", "TestFlag", iniFileName);//���Լ�¼����ʽ��¼��ĳ�1
	req["Collectdt"] = ts;
	//���в����ǹ̶�ֵ
	req["TradeCityCode"] = "0374";
	req["OwneityCode"] = "4610";
	req["AssCardType"] = 1;
	req["TradeKind"] = "-1";
	req["eCode"] = "08600000001";
	req["WalletType"] = 0;
	req["BatchNo"] = "0";
	req["OperatorID"] = "0";
	req["CardClass"] = 2;
	req["FavouredFare"] = 0;
	req["TradeAppType"] = 0;
	req["MainCardType"] = 0;
	req["AssCardType"] = 1;
	req["CardVersion"] = 0;
	req["UserDefinedType"] = 0;
	req["UnionPoscode"] = "";
	req["UnionMerchantcode"] = "";
	req["UnionCardno"] = "";
	req["UnionExt"] = "";
	req["CustomExt1"] = "";
	req["CustomExt2"] = "";
	req["doubleUpload"] = 0;
	req["planID"] = 0;
	req["saveOpCount"] = 0;
	//��������json
	std::string str_req(http_req);
	Json::Value root;
	Json::Reader reader;
	if (reader.parse(str_req, root))
	{
		req["samCardNo"] = root["psamId"];
		req["TAC"] = root["TAC"];
		req["SAMTradeNo"] = root["psamJyNo"];
		req["OpDateTime"] = root["opDatetime"];
		req["OpFare"] = root["opfare"];
		req["Oddfare"] = root["Oddfare"];
		req["CardNo"] = root["CardNo"];
		req["CustomerId"] = root["CustomerId"];
		req["OpCount"] = root["OpCount"];
		//�Ӽ�¼��ȡ���׼�¼��ˮ��
		//�����¼��û��TradeRecNo�ļ�ֵ������0
		if (root["TradeRecNo"])
		{
			req["TradeRecNo"] = root["TradeRecNo"];
		}
		else
		{
			req["TradeRecNo"] = 0;
		}
		req["id"] = req["TradeRecNo"];
		//����׼��������ֶ�Ret����ʾ�ۿ�״̬ 2018-11-01 14:32:23
		req["Ret"] = root["Ret"];
	}
	string req_to_str = req.toStyledString();

	char buf_Send[2048];
	sprintf(buf_Send,
		"POST %s HTTP/1.1\r\n"
		"Host: %s\r\n"
		"Cache-Control: no-cache\r\n"
		"Connection:Keep-Alive\r\n"
		"Accept-Encoding:gzip, deflate\r\n"
		"Accept-Language:zh-CN,en,*\r\n"
		"Content-Length:%d\r\n"
		"ver: 2.0\r\n"
		"appid: %d\r\n"
		"apptypeid: %d\r\n"
		"timestamp: %s\r\n"
		"hash: %s\r\n"
		"random: 1\r\n"
		"ip:%s\r\n"
		"Content-Type:application/json\r\n\r\n"
		"%s", url, host, req_to_str.length(), _appid, _apptypeid, ts, hash.c_str(), ip, req_to_str.c_str()
	);
	W_ReadCardLog("INFO ���ϴ�����json�������");
	char req_resv[1024];
	char req_ip[24];
	GetIpByDomainName(host, req_ip);
	//2018-09-07 12:19	�˴��޸�Ϊ���ύpost֮ǰ����Ϣд���ύ��־��������������־���յ������д��
	W_UploadLog(buf_Send);
	short _port = GetPrivateProfileIntA("TransDetail", "PORT", 80, iniFileName);

	//�ύPOST
	long ret_sendpost = SendPostRequest(req_ip, _port, buf_Send, req_resv);
	char sendlog[64] = { 0 };
	sprintf(sendlog, "EVENT ���ú���SendPostRequest����,POST�����ύ���,����%ld", ret_sendpost);
	W_ReadCardLog(sendlog);
	if (0 == ret_sendpost)
	{
		////��������
		//int _wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, req_resv, strlen(req_resv), NULL, 0);
		////����ռ�Ҫ��'\0'�����ռ䣬MultiByteToWideChar�����'\0'�ռ�
		//wchar_t* _wszString = new wchar_t[_wcsLen + 1];
		////ת��
		//::MultiByteToWideChar(CP_UTF8, NULL, req_resv, strlen(req_resv), _wszString, _wcsLen);
		////������'\0'
		//_wszString[_wcsLen] = '\0';
		//_bstr_t _b(_wszString);
		//char *_rev_temp = _b;
		char _rev_temp[1024] = { 0 };
		TransCharacter(req_resv, _rev_temp);
		//��ȡjson
		string str_rev(_rev_temp);
		string json_rel;
		int json_bg = str_rev.find_first_of("{", 0);
		int json_end = str_rev.find_last_of("}");
		if (json_end > json_bg)
		{
			json_rel = str_rev.substr(json_bg, json_end - json_bg + 1);
			//д���ϴ���־
			/*string str_send(buf_Send);
			string str_log = str_send + json_rel;
			W_UploadLog(str_log.c_str());*/
			//ͬ�ϣ�ע�͵�������룬�˴��޸�Ϊ������������Ϣ����д��
			W_UploadLog(json_rel.c_str());
			//����json
			Json::Value js_vl;
			Json::Reader reader;
			if (reader.parse(json_rel, js_vl))
			{
				if (js_vl["outMsg"].asString() == "������ϸ�ϴ�����")
				{
					W_ReadCardLog("INFO ������ϸ�ϴ�����");
					return 0;
				}
				else
				{
					W_ReadCardLog("ERROR ������ϸ�ϴ��쳣");
					return -11;
				}
			}
		}
		else
		{
			W_ReadCardLog("ERROR �ϴ��ӿڷ�����Ϣ��ʽ����");
			return -12;
		}
	}
	else
	{
		return ret_sendpost;
	}


}
//�ļ������ʹ���Ŀǰֻ�������ĵ���
void OpFile()
{
	W_ReadCardLog("EVENT ���ú���OpFile��ʼ");
	/*SYSTEMTIME st = { 0 };
	GetLocalTime(&st);
	char filename[64] = { 0 };
	sprintf(filename, ".//Log//Pre//Pre_%d%02d%02d.dat", st.wYear, st.wMonth, st.wDay);*/
	//������ʱ�ļ�
	ofstream outf("temp_comp.txt", ios::out | ios::trunc);
	ofstream unload_file("temp_unload.txt", ios::out | ios::trunc);

	//LPSTR HOST = GetValueInIni("TransDetail", "HOST", iniFileName);	//�����ϴ�����
	//LPSTR URL = GetValueInIni("TransDetail", "URL", iniFileName);	//�����ϴ���ַ
	//char _log[256] = { 0 };
	//sprintf(_log, "EVENT �������ļ���ȡ����,HOST:%s,URL:%s", HOST, URL);
	//W_ReadCardLog(_log);
	//��Ԥ�ϴ��ı��ļ�
	char buffer[1024] = { 0 };
	std::ifstream fin;
	fin.open(PREUPLOADFILE, std::ios::in);
	if (!fin.eof())
	{
		fin.getline(buffer, 1024, '\n');
		int size = strlen(buffer);
		if (size > 2)
		{
			long ret = UploadMisBySocket(buffer);
			if (ret == 0)
			{
				//���ϴ���¼д����ʱ�ļ�
				outf << buffer << endl;
			}
			else
			{
				//δ�ϴ��ɹ���¼д����ʱ�ļ�
				unload_file << buffer << endl;
			}
		}
	}
	else
	{
		return;
	}
	//int count = 3;	//����ÿ������ϴ�����
	//for (int i = 0; i < count; i++)
	//{
	//	if (!fin.eof())
	//	{
	//		fin.getline(buffer, 1024, '\n');
	//		int size = strlen(buffer);
	//		if (size > 2)
	//		{
	//			long ret = UploadMisBySocket(buffer);
	//			if (ret == 0)
	//			{
	//				//���ϴ���¼д����ʱ�ļ�
	//				outf << buffer << endl;
	//			}
	//			else
	//			{
	//				//δ�ϴ��ɹ���¼д����ʱ�ļ�
	//				unload_file << buffer << endl;
	//			}
	//		}
	//	}
	//	else
	//	{
	//		return;
	//	}

	//}
	fin.close();
	outf.close();
	unload_file.close();
	//���ύ��¼�ļ�·��
	const char* comp_path = "./Log//Comp";
	if (_access(comp_path, 0) == -1)
	{
		_mkdir(comp_path);
	}
	char uped_file[64] = { 0 };
	SYSTEMTIME st = { 0 };
	sprintf(uped_file, "./Log//Comp//Comp_%d%02d%02d.dat", st.wYear, st.wMonth, st.wDay);
	ofstream comp_f(uped_file, ios::out | ios::app);
	ifstream f_temp_comp;
	f_temp_comp.open("temp_comp.txt", std::ios::in);
	char buff_comp[1024] = { 0 };
	while (!f_temp_comp.eof())
	{
		f_temp_comp.getline(buff_comp, 1024, '\n');
		if (strlen(buff_comp) > 2)
		{
			comp_f << buff_comp << endl;
		}
	}
	comp_f.close();
	f_temp_comp.close();
	//�޸�Pre�ļ�
	ofstream f_prefile;
	f_prefile.open(PREUPLOADFILE, ios::out | ios::trunc);
	ifstream f_temp_uload;
	f_temp_uload.open("temp_unload.txt", ios::in);
	char buff_uload[1024] = { 0 };
	while (!f_temp_uload.eof())
	{
		f_temp_uload.getline(buff_uload, 1024, '\n');
		if (strlen(buff_uload) > 2)
		{
			f_prefile << buff_uload << endl;
		}
	}
	f_temp_uload.close();
	f_prefile.close();
	remove("temp_comp.txt");
	remove("temp_unload.txt");
	W_ReadCardLog("INFO ɾ����Ŀ¼��ʱ�ļ�");
}
//ͨ���������ά���ȡ������Ϣ
long GetCusInfoByUnion(char* outMsg, int* type)
{
	W_ReadCardLog("iR_DDF1EF05Info==================START");
	js_vl.clear();
	memset(ALLIDCARD, 0x00, 20);
	char _info[200] = { 0 };
	//��ȷ��֧����ʽ
	bool ISGETINFO = false;
	int ret = -1;
	ret = GetBankCardNo(_info);
	string content;
	string searchtype;
	//��ʵ�忨
	if (ret == 0)
	{
		W_ReadCardLog("������ʽ");
		string content_temp(_info);
		//�������֤���뵽IDCARD��
		strcpy(ALLIDCARD, _info);
		content = content_temp;
		ISGETINFO = true;
		searchtype = "searchIdCard";
		*type = 2;
	}
	else
	{

		int read_qrcode = GetComInputInfo(_info);
		if (read_qrcode == 0)//ɨ��ɹ�
		{
			W_ReadCardLog("����ά�뷽ʽ");
			string content_qrcode(_info);
			ISGETINFO = true;
			content = content_qrcode;
			//���ȫ�ֱ���IDCARD
			memset(ALLQRCODE, 0x00, 100);
			searchtype = "search";
			*type = 1;
		}
		else
		{
			W_ReadCardLog("ɨ��ʧ��");
			ISGETINFO = false;
		}
	}
	if (ISGETINFO)
	{

		char req_resv[1024];
		LPSTR req_ip;
		req_ip = GetValueInIni("MIS", "BCNIP", iniFileName);
		short _port = GetPrivateProfileIntA("MIS", "BCNPORT", 80, iniFileName);
		//���岢��ʼ��Json����
		Json::Value sendvalue;
		//string content(_info);
		string orgcode(GetValueInIni("MIS", "ORGCODE", iniFileName));
		string serialNo(GetValueInIni("MIS", "SERIALNO", iniFileName));
		sendvalue["content"] = content;
		sendvalue["organizationCode"] = orgcode;
		sendvalue["serialNumber"] = serialNo;
		sendvalue["method"] = searchtype;
		string sendJson = sendvalue.toStyledString();
		char _send_buff[1024] = { 0 };
		//��ʼ����
		initKV();
		string str_sendbuff = encrypt(sendJson);
		memcpy(_send_buff, str_sendbuff.c_str(), 1024);
		string log1 = "�ύ��ǰ�û���Ϣ���ܺ��ַ���Ϊ��" + str_sendbuff;
		W_ReadCardLog(log1.c_str());
		//��������
		long ret_sendpost = SendPostRequest(req_ip, _port, _send_buff, req_resv);
		if (0 == ret_sendpost)
		{
			char _rev_temp[1024] = { 0 };
			TransCharacter(req_resv, _rev_temp);
			//��ȡjson
			string str_rev(_rev_temp);
			string json_rel;
			int json_bg = str_rev.find_first_of("{", 0);
			int json_end = str_rev.find_last_of("}");
			if (json_end > json_bg)
			{
				json_rel = str_rev.substr(json_bg, json_end - json_bg + 1);
				W_ReadCardLog(json_rel.c_str());
				strcpy(outMsg, json_rel.c_str());
				return 0;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -2;
		}
	}
	else
	{
		return -3;
	}
}
/*========================================ʵ�ֳ���ͨ�ӿ�=======================================================*/
//������
long _stdcall OpenCom()
{
	W_ReadCardLog("EVENT OPENCOM===========================START");
	SWITCH_QCARD = true;

	return 0;
}
//�ر�����
void _stdcall CloseCom()
{
	W_ReadCardLog("EVENT CLOSECOM===============================START");
	SWITCH_QCARD = false;
}
//��ȡ�û���Ϣ
long _stdcall  CapGetNBCardInfo(CUSTOMERINFO *info)
{
	W_ReadCardLog("CapGetNBCardInfo==================START");
	//CUSTOMERINFO custinfo;
	//��ʼ����ͨ��HIS�۷�ǰУ��
	info->Ye = 1000 * 100;
	strcpy(info->CardASN, "17082537");
	info->CardClass = 8;
	strcpy(info->Name, CUSNAME);
	info->Status = 241;
	return 0;
}

//Ѱ��
long _stdcall CapNBQueryCard(long *UID)
{
	W_ReadCardLog("CapNBQueryCard==================START");
	clock_t end = clock();
	int sec = (int)(end - N) / CLOCKS_PER_SEC;
	int TOUT = atoi(GetValueInIni("MIS", "TIMEOUT", iniFileName));
	//����ϴε��ñ��ӿ���˴ε��ýӿڼ��ʱ�����$��
	if ((sec > TOUT) && (TOUT > 0))
	{
		char shijian[24];
		time_t t = time(0);
		strftime(shijian, sizeof(shijian), "%d%H%M%S", localtime(&t));
		long testuid = 0;
		testuid = atol(shijian);
		*UID = testuid;
		//ȫ�ּ�ʱ��ˢ��Ϊ���ε��ýӿ�ʱ��
		N = end;
		//ȫ�������ˢ��Ϊ�˴�uid
		R = *UID;
	}
	else
	{
		//�����ϴ�UID
		*UID = R;
	}
	char _log[100] = { 0 };
	sprintf(_log, "INFO Ѱ������UID��%d", *UID);
	W_ReadCardLog(_log);
	return 0;
}

//�ۿ�Ӵ�/���޶�ܣ�
long _stdcall CapSetNBCardInfo_LMT(long objNo, long UID, long opFare, LPSTR jyDT, long onceLmt, long dayLmt, __int64 *psamID, long *psamJyNo, long *tac)
{
	return -1;
}
//5.7.	�ۿ���޶����֤�������ѣ�
long _stdcall CapSetNBCardInfo_Verify(long objNo, long UID, long opFare, LPSTR jyDT, long onceLmt, long dayLmt, LPSTR pwd, __int64 *psamID, long *psamJyNo, long *tac)
{
	return -1;
}

//�۷ѣ����ϴι��ܣ��޺�����У��
long WINAPI CapSetNBCardInfo_SLYY(long objNo, long uid, long opFare, LPSTR jyDT, char *psamID, long *psamJyNo, char *tac, int redix)
{
	W_ReadCardLog("CapSetNBCardInfo_SLYY==================START");
	return 0;
}




//5.15.	�ۿpsam���š�TAC�����ַ�����
long WINAPI CapSetNBCardInfo_Str1(long objNo, long uid, long opFare, LPSTR jyDT, char *psamID, long *psamJyNo, char *tac, int redix)
{
	W_ReadCardLog("CapSetNBCardInfo_Str1===================START");
	//��ȷ��֧����ʽ
	LPSTR _mistradeno = GetValueInIni("MIS", "MisTraceNo", iniFileName);
	char _info[100] = { 0 };
	int _cardtype = 0;
	int ret = GetBCNorIDC(_mistradeno, _info, &_cardtype);
	char _testlog[20000] = { 0 };
	sprintf(_testlog, "info:%s,cardtype:%d", _info, _cardtype);
	W_ReadCardLog(_testlog);
	if (ret == 0)
	{
		if (1 == _cardtype)//ɨ��
		{
			Json::Value sendvalue;
			string orgcode(GetValueInIni("MIS", "ORGCODE", iniFileName));
			string serialNo(GetValueInIni("MIS", "SERIALNO", iniFileName));
			sendvalue["organizationCode"] = orgcode;
			sendvalue["serialNumber"] = serialNo;
			sendvalue["method"] = "pay";
			//ʹ��17λʱ�����Ϊ������
			std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::system_clock::now().time_since_epoch());
			sendvalue["content"]["orderNo"] = ms.count();
			sendvalue["content"]["orderTime"] = TransDate(jyDT);
			sendvalue["content"]["txnAmt"] = opFare;
			sendvalue["content"]["termId"] = atoll(GetValueInIni("MIS", "TERMID", iniFileName));//�ն˺�
			sendvalue["content"]["reqType"] = "��������";
			sendvalue["content"]["couponInfo"] = 0;
			sendvalue["content"]["qrNo"] = _info;
			sendvalue["content"]["merId"] = GetValueInIni("MIS", "MERID", iniFileName);
			sendvalue["content"]["merCatCode"] = GetValueInIni("MIS", "MERCATCODE", iniFileName);
			sendvalue["content"]["merName"] = GetValueInIni("MIS", "MERNAME", iniFileName);
			string sendJson = sendvalue.toStyledString();
			char _send_buff[1024] = { 0 };
			memcpy(_send_buff, sendJson.c_str(), 1024);
			W_ReadCardLog(_send_buff);
			//�ύ�ӿ�
			LPSTR req_ip;
			req_ip = GetValueInIni("MIS", "BCNIP", iniFileName);
			short _port = GetPrivateProfileIntA("MIS", "BCNPORT", 80, iniFileName);
			char req_resv[1024] = { 0 };
			long ret_sendpost = SendPostRequest(req_ip, _port, _send_buff, req_resv);
			if (0 == ret_sendpost)
			{
				char _rev_temp[1024] = { 0 };
				TransCharacter(req_resv, _rev_temp);
				//��ȡjson
				string str_rev(_rev_temp);
				string json_rel;
				int json_bg = str_rev.find_first_of("{", 0);
				int json_end = str_rev.find_last_of("}");
				if (json_end > json_bg)
				{
					json_rel = str_rev.substr(json_bg, json_end - json_bg + 1);
					W_ReadCardLog(json_rel.c_str());
					//����Jsonʾ����
					//{"code":"R00000","content":{"data":{"orderNo":"1558334758179","payResult":"�ɹ�","autoCode":"0","termId":"1"}},"desc":"֧���ɹ�","flag":1}
					//����json
					Json::Value root;
					//js_vl.clear();
					Json::Reader reader;
					try
					{
						if (reader.parse(json_rel, root))
						{
							if (root["flag"].asString() == "1")
							{
								W_ReadCardLog("INFO ֧���ɹ�");
								//�������
								strcpy(psamID, GetValueInIni("MIS", "TERMID", iniFileName));
								char tac_temp[20] = { 0 };
								_i64toa(ms.count(), tac_temp, 10);
								strcpy(tac, tac_temp);
								*psamJyNo = atol(root["content"]["data"]["autoCode"].asString().c_str());
								return 0;
							}
							else
							{
								W_ReadCardLog("ERROR ֧��ʧ��");
								return -11;
							}
						}
					}
					catch (const std::exception&ex)
					{
						return -13;
					}

				}
				else
				{
					W_ReadCardLog("ERROR ������Ϣ��ʽ����");
					return -12;
				}
			}
			else
			{
				return ret_sendpost;
			}
		}
		else if ((2 == _cardtype) || (3 == _cardtype))//cardtype=2,��ͨ����cardtype=3,�ǽӿ�����һ���ǽ���IC����
		{
			//HMODULE hdllInst = LoadLibraryA("KeeperClient.dll");
			_mistrans trans = (_mistrans)GetProcAddress(hdllInst, "misposTrans");

			//W_ReadCardLog("INFO ������������ṹ");
			ST_MISPOS_IN st_in;
			ST_MISPOS_OUT st_out;
			memset(&st_in, 0x00, sizeof(ST_MISPOS_IN));
			memset(&st_out, 0x00, sizeof(ST_MISPOS_OUT));
			memcpy(st_in.TransType, "05", 2);	//�������ͣ���ֵ
			char amount_temp[13] = { 0 };
			sprintf(amount_temp, "%012.12d", opFare);
			amount_temp[12] = '\0';
			memcpy(st_in.TransAmount, amount_temp, 12);

			memcpy(st_in.MisTraceNo, _mistradeno, 6);
			W_ReadCardLog("INFO �۷Ѳ����������");
			int rc = trans(&st_in, &st_out);
			char koufeilog[100] = { 0 };
			sprintf(koufeilog, "�۷����,���أ�%d", rc);

			if (rc == 0)
			{
				strcpy(psamID, subchar(st_out.TransType, 220, 15));//�ն˺�
				strcpy(tac, subchar(st_out.TransType, 204, 8));		//ϵͳ������
				*psamJyNo = atol(subchar(st_out.TransType, 610, 6));//�ն���ˮ��
				char _log[1024] = { 0 };
				sprintf(_log, "psamID=%s,tac=%s,psamjyNo=%ld", psamID, tac, psamJyNo);
				W_ReadCardLog("׼������JSON");
				string str_json = Stu2json(st_out, ALLIDCARD);
				char _jsonlog[1024];
				sprintf(_jsonlog, "����json:%s", str_json.c_str());
				W_ReadCardLog(_jsonlog);
				//���Ѽ�¼�ϴ�
				//UploadMisBySocket(str_json);
				WriteInFile(PREUPLOADFILE, str_json);
				return 0;
			}
			else if (rc == -5)
			{
				return 1;
			}
			else
			{
				return rc;
			}
		}
		else
		{
			return -10;
		}
	}
	else
	{
		return -11;
	}
}
//5.8.	�������ۼ�����
long _stdcall CapUpdateNBCardStatus(long opFare, LPSTR jyDT)
{
	return -1;
}
//5.9.	���¿���/���޶�
long _stdcall CapSetNBCardStatus(long onceLmt, long dayLmt)
{
	return -1;
}
//5.10.	��������
long _stdcall CapSetCardPwd(LPSTR oldPwd, LPSTR newPwd)
{
	return -1;
}
//5.11.	��ֵ��ʼ��
long _stdcall CapChargeInit(long objNo, long fare, __int64 *termId, long *bFare, long *no, long *random, long *mac1)
{
	return -1;
}
//��ֵ
long _stdcall CapCharge(LPSTR dt, LPSTR mac2, LPSTR tac)
{
	return -1;
}
int GetTime()
{
	return clock();
}
//�ۿ�
long _stdcall CapSetNBCardInfo_Str(long objNo, long uid, long opFare, LPSTR jyDT, __int64 *psamID, long *psamJyNo, char *tac, int redix)
{

	/*W_ReadCardLog("������ǰ����");
	DWORD dwProcessId = ::GetCurrentProcessId();
	char log1[100];
	sprintf(log1, "��ǰ����ID��%ld", dwProcessId);
	W_ReadCardLog(log1);
	HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE, false, dwProcessId);
	W_ReadCardLog("codeline1");
	::TerminateProcess(hProcess, 0);
	W_ReadCardLog("codeline2");*/

	W_ReadCardLog("CapSetNBCardInfo_Str=================START");
	//��ȷ��֧����ʽ
	LPSTR _mistradeno = GetValueInIni("MIS", "MisTraceNo", iniFileName);
	char _info[100] = { 0 };
	int _cardtype = 0;	//1Ϊɨ�룬2Ϊʵ�忨
	int ret = GetBCNorIDC(_mistradeno, _info, &_cardtype);
	char _testlog[2000] = { 0 };
	sprintf(_testlog, "info:%s,cardtype:%d", _info, _cardtype);
	W_ReadCardLog(_testlog);
	if (ret == 0)
	{
		if (1 == _cardtype)//ɨ��
		{
			Json::Value sendvalue;
			string orgcode(GetValueInIni("MIS", "ORGCODE", iniFileName));
			string serialNo(GetValueInIni("MIS", "SERIALNO", iniFileName));
			sendvalue["organizationCode"] = orgcode;
			sendvalue["serialNumber"] = serialNo;
			sendvalue["method"] = "pay";
			//ʹ��17λʱ�����Ϊ������
			std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::system_clock::now().time_since_epoch());
			sendvalue["content"]["orderNo"] = ms.count();
			sendvalue["content"]["orderTime"] = TransDate(jyDT);
			sendvalue["content"]["txnAmt"] = opFare;
			sendvalue["content"]["termId"] = atoll(GetValueInIni("MIS", "TERMID", iniFileName));//�ն˺�
			sendvalue["content"]["reqType"] = "��������";
			sendvalue["content"]["couponInfo"] = 0;
			sendvalue["content"]["qrNo"] = _info;
			sendvalue["content"]["merId"] = GetValueInIni("MIS", "MERID", iniFileName);
			sendvalue["content"]["merCatCode"] = GetValueInIni("MIS", "MERCATCODE", iniFileName);
			sendvalue["content"]["merName"] = GetValueInIni("MIS", "MERNAME", iniFileName);
			string sendJson = sendvalue.toStyledString();
			char _send_buff[1024] = { 0 };
			initKV();
			string str_enp = encrypt(sendJson);
			memcpy(_send_buff, str_enp.c_str(), 1024);
			W_ReadCardLog(_send_buff);
			//�ύ�ӿ�
			LPSTR req_ip;
			req_ip = GetValueInIni("MIS", "BCNIP", iniFileName);
			short _port = GetPrivateProfileIntA("MIS", "BCNPORT", 80, iniFileName);
			char req_resv[1024] = { 0 };
			long ret_sendpost = SendPostRequest(req_ip, _port, _send_buff, req_resv);
			if (0 == ret_sendpost)
			{
				char _rev_temp[1024] = { 0 };
				TransCharacter(req_resv, _rev_temp);
				//��ȡjson
				string str_rev(_rev_temp);
				string json_rel;
				int json_bg = str_rev.find_first_of("{", 0);
				int json_end = str_rev.find_last_of("}");
				if (json_end > json_bg)
				{
					json_rel = str_rev.substr(json_bg, json_end - json_bg + 1);
					W_ReadCardLog(json_rel.c_str());
					//����Jsonʾ����
					//{"code":"R00000","content":{"data":{"orderNo":"1558334758179","payResult":"�ɹ�","autoCode":"0","termId":"1"}},"desc":"֧���ɹ�","flag":1}
					//����json
					Json::Value root;
					//js_vl.clear();
					Json::Reader reader;
					try
					{
						if (reader.parse(json_rel, root))
						{
							if (root["flag"].asString() == "1")
							{
								W_ReadCardLog("INFO ֧���ɹ�");
								string str_dep = decrypt(root["content"]["data"].asString());
								Json::Value json_dep;
								reader.parse(str_dep, json_dep);
								//�������
								*psamID = atoll(GetValueInIni("MIS", "TERMID", iniFileName));
								char tac_temp[20] = { 0 };
								_i64toa(ms.count(), tac_temp, 10);
								strcpy(tac, tac_temp);
								*psamJyNo = atol(json_dep["autoCode"].asString().c_str());
								return 0;
							}
							else
							{
								W_ReadCardLog("ERROR ֧��ʧ��");

								return -11;
							}
						}
					}
					catch (const std::exception&ex)
					{

						return -13;
					}

				}
				else
				{
					W_ReadCardLog("ERROR ������Ϣ��ʽ����");

					return -12;
				}
			}
			else
			{

				return ret_sendpost;
			}
		}
		else if ((2 == _cardtype) || (3 == _cardtype))//cardtype=2,��ͨ����cardtype=3,�ǽӿ�����һ���ǽ���IC����
		{
			//HMODULE hdllInst = LoadLibraryA("KeeperClient.dll");
			_mistrans trans = (_mistrans)GetProcAddress(hdllInst, "misposTrans");

			//W_ReadCardLog("INFO ������������ṹ");
			ST_MISPOS_IN st_in;
			ST_MISPOS_OUT st_out;
			memset(&st_in, 0x00, sizeof(ST_MISPOS_IN));
			memset(&st_out, 0x00, sizeof(ST_MISPOS_OUT));
			memcpy(st_in.TransType, "05", 2);	//�������ͣ���ֵ
			char amount_temp[13] = { 0 };
			sprintf(amount_temp, "%012.12d", opFare);
			amount_temp[12] = '\0';
			memcpy(st_in.TransAmount, amount_temp, 12);

			memcpy(st_in.MisTraceNo, _mistradeno, 6);
			W_ReadCardLog("INFO �۷Ѳ����������");
			int rc = -1;
			try
			{
				rc = trans(&st_in, &st_out);

			}
			catch (const std::exception&)
			{
				W_ReadCardLog("MIS�۷Ѻ����쳣");

				return rc;
			}
			char koufeilog[100] = { 0 };
			sprintf(koufeilog, "�۷����,���أ�%d", rc);
			W_ReadCardLog(koufeilog);

			if (rc == 0)
			{
				string str_json;
				try
				{
					*psamID = atoll(subchar(st_out.TransType, 220, 15));//�ն˺�
					strcpy(tac, subchar(st_out.TransType, 204, 8));		//ϵͳ������
					*psamJyNo = atol(subchar(st_out.TransType, 610, 6));//�ն���ˮ��
					char _log[1024] = { 0 };
					sprintf(_log, "psamID=%lld,tac=%s,psamjyNo=%ld", psamID, tac, psamJyNo);
					str_json = Stu2json(st_out, ALLIDCARD);
					char _jsonlog[1024];
					sprintf(_jsonlog, "����json:%s", str_json.c_str());
					W_ReadCardLog(_jsonlog);
					//���Ѽ�¼�ϴ�
					UploadMisBySocket(str_json);
					//д����ϴ��ļ�
					WriteInFile(PREUPLOADFILE, str_json);
					//UploadMisBySocket(str_json);

					return 0;

				}
				catch (const std::exception&)
				{
					WriteInFile(PREUPLOADFILE, str_json);

					return 0;
				}

			}
			else if (rc == -5)
			{

				return 1;
			}
			else
			{

				return rc;
			}
			//W_ReadCardLog(Stu2json(st_out).c_str());
			//FreeLibrary(hdllInst);
		}
		else
		{

			return -10;
		}
	}
	else
	{

		return ret;
		//��ά��۷ѷ���-3�����ﴦ��
	}




}
//5.13.	��ȡtacֵ
long _stdcall CapGetConsumeTac(long no, LPSTR tac)
{
	return -1;
}
//��ȡʮ�ν��׼�¼
long _stdcall CapReadRecords(CONSUMEINFO* info)
{
	return -1;
}
void trim(LPSTR str, LPSTR info)
{
	std::string strTemp(str);
	strTemp.erase(strTemp.find_last_not_of(" ") + 1);

	strcpy(info, strTemp.c_str());
}

//MIS�ӿڿ۷�
long _stdcall CapSetNBCardInfo(long objNo, long UID, long opFare, LPSTR jyDT, __int64 *psamID, long *psamJyNo, __int64 *tac)
{
	W_ReadCardLog("CapSetNBCardInfo=================START");
	//��ȷ��֧����ʽ
	LPSTR _mistradeno = GetValueInIni("MIS", "MisTraceNo", iniFileName);
	char _info[100] = { 0 };
	int _cardtype = 0;
	int ret = GetBCNorIDC(_mistradeno, _info, &_cardtype);
	char _testlog[2000] = { 0 };
	sprintf(_testlog, "info:%s,cardtype:%d", _info, _cardtype);
	W_ReadCardLog(_testlog);
	if (ret == 0)
	{
		if (1 == _cardtype)//ɨ��
		{
			Json::Value sendvalue;
			string orgcode(GetValueInIni("MIS", "ORGCODE", iniFileName));
			string serialNo(GetValueInIni("MIS", "SERIALNO", iniFileName));
			sendvalue["organizationCode"] = orgcode;
			sendvalue["serialNumber"] = serialNo;
			sendvalue["method"] = "pay";
			//ʹ��17λʱ�����Ϊ������
			std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::system_clock::now().time_since_epoch());
			sendvalue["content"]["orderNo"] = ms.count();
			sendvalue["content"]["orderTime"] = TransDate(jyDT);
			sendvalue["content"]["txnAmt"] = opFare;
			sendvalue["content"]["termId"] = atoll(GetValueInIni("MIS", "TERMID", iniFileName));//�ն˺�
			sendvalue["content"]["reqType"] = "��������";
			sendvalue["content"]["couponInfo"] = 0;
			sendvalue["content"]["qrNo"] = _info;
			sendvalue["content"]["merId"] = GetValueInIni("MIS", "MERID", iniFileName);
			sendvalue["content"]["merCatCode"] = GetValueInIni("MIS", "MERCATCODE", iniFileName);
			sendvalue["content"]["merName"] = GetValueInIni("MIS", "MERNAME", iniFileName);
			string sendJson = sendvalue.toStyledString();
			char _send_buff[1024] = { 0 };
			memcpy(_send_buff, sendJson.c_str(), 1024);
			W_ReadCardLog(_send_buff);
			//�ύ�ӿ�
			LPSTR req_ip;
			req_ip = GetValueInIni("MIS", "BCNIP", iniFileName);
			short _port = GetPrivateProfileIntA("MIS", "BCNPORT", 80, iniFileName);
			char req_resv[1024] = { 0 };
			long ret_sendpost = SendPostRequest(req_ip, _port, _send_buff, req_resv);
			if (0 == ret_sendpost)
			{
				char _rev_temp[1024] = { 0 };
				TransCharacter(req_resv, _rev_temp);
				//��ȡjson
				string str_rev(_rev_temp);
				string json_rel;
				int json_bg = str_rev.find_first_of("{", 0);
				int json_end = str_rev.find_last_of("}");
				if (json_end > json_bg)
				{
					json_rel = str_rev.substr(json_bg, json_end - json_bg + 1);
					W_ReadCardLog(json_rel.c_str());
					//����Jsonʾ����
					//{"code":"R00000","content":{"data":{"orderNo":"1558334758179","payResult":"�ɹ�","autoCode":"0","termId":"1"}},"desc":"֧���ɹ�","flag":1}
					//����json
					Json::Value root;
					//js_vl.clear();
					Json::Reader reader;
					try
					{
						if (reader.parse(json_rel, root))
						{
							if (root["flag"].asString() == "1")
							{
								W_ReadCardLog("INFO ֧���ɹ�");
								//�������
								*psamID = atoll(GetValueInIni("MIS", "TERMID", iniFileName));
								*tac = ms.count();
								*psamJyNo = atol(root["content"]["data"]["autoCode"].asString().c_str());
								return 0;
							}
							else
							{
								W_ReadCardLog("ERROR ֧��ʧ��");
								return -11;
							}
						}
						else
						{
							W_ReadCardLog("ERROR JSON����ʧ��");
							return -2;
						}
					}
					catch (const std::exception&ex)
					{
						W_ReadCardLog("ERROR JSON�����쳣");

						return -2;
					}

				}
				else
				{
					W_ReadCardLog("ERROR ������Ϣ��ʽ����");
					return -12;
				}
			}
			else
			{
				return ret_sendpost;
			}
		}
		else if ((2 == _cardtype) || (3 == _cardtype))//cardtype=2,��ͨ����cardtype=3,�ǽӿ�����һ���ǽ���IC����
		{
			//HMODULE hdllInst = LoadLibraryA("KeeperClient.dll");
			_mistrans trans = (_mistrans)GetProcAddress(hdllInst, "misposTrans");

			//W_ReadCardLog("INFO ������������ṹ");
			ST_MISPOS_IN st_in;
			ST_MISPOS_OUT st_out;
			memset(&st_in, 0x00, sizeof(ST_MISPOS_IN));
			memset(&st_out, 0x00, sizeof(ST_MISPOS_OUT));
			memcpy(st_in.TransType, "05", 2);	//�������ͣ���ֵ
			char amount_temp[13] = { 0 };
			sprintf(amount_temp, "%012.12d", opFare);
			amount_temp[12] = '\0';
			memcpy(st_in.TransAmount, amount_temp, 12);

			memcpy(st_in.MisTraceNo, _mistradeno, 6);
			W_ReadCardLog("INFO �۷Ѳ����������");
			int rc = trans(&st_in, &st_out);
			W_ReadCardLog("�۷����");
			if (rc == 0)
			{
				*psamID = atoll(subchar(st_out.TransType, 220, 15));//�ն˺�
				*tac = atoll(subchar(st_out.TransType, 204, 8));//ϵͳ������
				*psamJyNo = atol(subchar(st_out.TransType, 610, 6));//�ն���ˮ��
				char _log[1024] = { 0 };
				sprintf(_log, "����ֵ��%d,psamID=%lld,tac=%lld,psamjyNo=%ld", rc, psamID, tac, psamJyNo);
				W_ReadCardLog("���δ������");
				W_ReadCardLog(_log);
				string str_json = Stu2json(st_out, ALLIDCARD);
				char _jsonlog[1024];
				sprintf(_jsonlog, "����json:%s", str_json.c_str());
				W_ReadCardLog(_jsonlog);
				//���Ѽ�¼�ϴ�
				//char* _host = GetValueInIni("TransDetail", "HOST", iniFileName);
				//char* _url = GetValueInIni("TransDetail", "URL", iniFileName);
				//UploadMisBySocket(str_json);
				//д����ϴ��ļ�
				WriteInFile(PREUPLOADFILE, str_json);
				return 0;
			}
			else if (rc == -5)
			{
				return 1;
			}
			else
			{
				W_ReadCardLog("ERROR �۷�ʧ��");
				return rc;
			}

			//W_ReadCardLog(Stu2json(st_out).c_str());
			////FreeLibrary(hdllInst);

		}
		else
		{
			return -10;
		}
	}
	else
	{
		return -11;
	}
}

/*========================================ʵ�־��񽡿����ӿ�=======================================================*/

HANDLE _stdcall OpenDevice(int port)
{
	return NULL;
}
int _stdcall CloseDevice(HANDLE hdev)
{
	return 0;
}
int _stdcall PowerOn(HANDLE hdev, int slot, char* atr)
{
	return 0;
}
int _stdcall SendAPDU(HANDLE hdev, unsigned char byslot, unsigned char* pbyccommand, unsigned long len, unsigned char* pbyrcommand, int* pnrs)
{
	return 0;
}
int _stdcall iR_DDF1EF05Info(HANDLE hdev, char* klb, char* gfbb, char* fkjgmc, char* fkjgdm, char* fkjgzs, char* fksj, char* kh, char* aqm, char* xpxlh, char* yycsdm)
{
	/*strcpy(kh, "411082198204179056");
	return 0;*/
	//������ʱ����
	int type = 0;
	char outJson[1024] = { 0 };
	long ret = GetCusInfoByUnion(outJson, &type);
	if (ret == 0)
	{
		//����json
		js_vl.clear();
		js_dep.clear();
		Json::Reader reader;
		try
		{
			string strJson(outJson);
			reader.parse(strJson, js_vl);
			if (js_vl["flag"].asString() == "1")//��ѯ�ɹ�
			{
				initKV();
				string str_dep = decrypt(js_vl["content"]["data"].asString());//����data����
				char deptemp[1024] = { 0 };
				TransCharacter(str_dep.c_str(), deptemp);
				string strtemp(deptemp);
				string strlog = "���ܺ��ַ�����" + strtemp;
				W_ReadCardLog(strlog.c_str());
				reader.parse(strtemp, js_dep);
				W_ReadCardLog("INFO ��ѯ�ɹ�");
				//�������
				strcpy(kh, js_dep["papersNum"].asString().c_str());
				W_ReadCardLog("���ſ������");
				strcpy(ALLIDCARD, kh);
				W_ReadCardLog("ȫ��CARDID�������");
				return 0;
			}
			else
			{
				W_ReadCardLog("ERROR ��ѯʧ��");
				return -11;
			}

		}
		catch (const std::exception&ex)
		{
			return -13;
		}
	}
	else
	{
		return ret;
	}
}
int _stdcall iW_DDF1EF05Info(HANDLE hdev, char* klb, char* gfbb, char* fkjgmc, char* fkjgdm, char* fkjgzs, char* fksj, char* kh, char* aqm, char* xpxlh, char* yycsdm)
{
	return 0;
}
int _stdcall GetBCNAndICN(char* bcn, char* icn)//�˺�������
{
	char _bankNo[20];
	LPSTR _mistradeno = GetValueInIni("MIS", "MisTraceNo", iniFileName);
	int ret = GetBankCardNo(_bankNo);
	if (ret == 0)
	{
		strcpy(_bankNo, bcn);
		char req_resv[1024];
		LPSTR req_ip;
		req_ip = GetValueInIni("MIS", "BCNIP", iniFileName);
		short _port = GetPrivateProfileIntA("MIS", "BCNPORT", 80, iniFileName);
		//req_ip = "192.168.70.163";
		//short _port = 7002;
		//�ύPOST

		long ret_sendpost = SendPostRequest(req_ip, _port, _bankNo, req_resv);
		W_ReadCardLog("EVENT  SendPostRequest����");
		if (0 == ret_sendpost)
		{
			char _rev_temp[1024] = { 0 };
			TransCharacter(req_resv, _rev_temp);
			//���봦�����
			W_ReadCardLog("INFO  ���봦�����");
			//��ȡjson
			string str_rev(_rev_temp);
			string json_rel;
			int json_bg = str_rev.find_first_of("{", 0);
			int json_end = str_rev.find_last_of("}");
			if (json_end > json_bg)
			{
				json_rel = str_rev.substr(json_bg, json_end - json_bg + 1);
				//ͬ�ϣ�ע�͵�������룬�˴��޸�Ϊ������������Ϣ����д��
				W_ReadCardLog(json_rel.c_str());
				//����json
				Json::Value value;
				value.clear();
				Json::Reader reader;
				char sfzh[20] = { 0 };
				if (reader.parse(json_rel, value))
				{
					if (value["desc"].asString() == "��ѯ�ɹ�")
					{
						W_ReadCardLog("INFO ��ѯ�ɹ�");
						//�������
						strcpy(sfzh, value["content"]["data"]["idCardValue"].asString().c_str());
						strcpy(sfzh, icn);
						return 0;
					}
					else
					{
						W_ReadCardLog("ERROR ��ѯʧ��");
						return -11;
					}
				}
			}
			else
			{
				W_ReadCardLog("ERROR ������Ϣ��ʽ����");
				return -12;
			}
		}
		else
		{
			return ret_sendpost;
		}
	}
	else
	{
		return ret;
	}
}
int _stdcall iR_DDF1EF06Info(HANDLE hdev, char* xm, char* xb, char* mz, char* csrq, char* sfzh)
{
	/*strcpy(xm, "������");
	strcpy(xb, "1");
	strcpy(csrq, "19820417");
	strcpy(sfzh, "411082198204179056");
	return 0;*/
	//������ʱ����
	W_ReadCardLog("iR_DDF1EF06Info==================START");
	if (js_vl["flag"].asString() == "1")
	{
		//W_ReadCardLog("INFO ��ѯ�ɹ�");
		//�������
		memset(CUSNAME, 0x00, 128);
		try
		{

			strcpy(xm, js_dep["userName"].asString().c_str());
			strcpy(CUSNAME, js_dep["userName"].asString().c_str());
			strcpy(sfzh, js_dep["papersNum"].asString().c_str());
			strcpy(ALLIDCARD, sfzh);
			if (18 == strlen(sfzh))
			{
				string str_sfz(sfzh);
				string str_sex = str_sfz.substr(16, 1);
				string str_csrq = str_sfz.substr(6, 8);
				int sex = (stoi(str_sex) % 2) == 0 ? 2 : 1;
				itoa(sex, xb, 10);
				strcpy(csrq, str_csrq.c_str());
				char log[200] = { 0 };
				sprintf(log, "������%s,�Ա�%s,�������ڣ�%s,���֤�ţ�%s", xm, xb, csrq, sfzh);
				W_ReadCardLog(log);
				return 0;
			}
		}
		catch (const std::exception&)
		{
			return -1;
		}

	}
	else
	{
		//W_ReadCardLog("ERROR ��ѯʧ��");
		return -11;
	}
}
int _stdcall iW_DDF1EF06Info(HANDLE hdev, char* xm, char* xb, char* mz, char* csrq, char* sfzh)
{
	return 0;
}
int _stdcall iR_DDF1EF07Info(HANDLE hdev, char* zp_path)
{
	W_ReadCardLog("iR_DDF1EF07Info==================START");
	return 0;
}
int _stdcall iW_DDF1EF07Info(HANDLE hdev, char* zp_path)
{
	return 0;
}
int _stdcall iR_DDF1EF08Info(HANDLE hdev, char* kyxq, char* brdh1, char* brdh2, char* ylfs1, char* ylfs2, char* ylfs3)
{
	/*strcpy(brdh1, "15617480655");
	strcpy(brdh2, "15617480655");
	return 0;*/
	//������ʱ����
	W_ReadCardLog("iR_DDF1EF08Info==================START");
	if (js_vl["flag"].asString() == "1")
	{
		//�������
		try
		{
			strcpy(brdh1, js_dep["telephone"].asString().c_str());
			strcpy(brdh2, js_dep["telephone"].asString().c_str());
			return 0;
		}
		catch (const std::exception&)
		{
			return -1;
		}

	}
	else
	{
		return -11;
	}
}
int _stdcall iW_DDF1EF08Info(HANDLE hdev, char* kyxq, char* brdh1, char* brdh2, char* ylfs1, char* ylfs2, char* ylfs3)
{
	return 0;
}
int _stdcall iR_DF01EF05Info(HANDLE hdev, char* dzlb1, char* dz1, char* dzlb2, char* dz2)
{
	/*strcpy(dz1, "����о���һ��ͨ��Ӫ���޹�˾");
	return 0;*/
	//������ʱ����
	W_ReadCardLog("iR_DF01EF05Info==================START");

	if (js_vl["flag"].asString() == "1")
	{
		//�������
		try
		{
			strcpy(dz1, js_dep["patientAddr"].asString().c_str());
			return 0;
		}
		catch (const std::exception&)
		{
			return -1;
		}

	}
	else
	{
		return -11;
	}
}
int _stdcall iW_DF01EF05Info(HANDLE hdev, char* dzlb1, char* dz1, char* dzlb2, char* dz2)
{
	W_ReadCardLog("iW_DF01EF05Info==================START");
	return 0;
}
int _stdcall iR_DF01EF06Info(HANDLE hdev, char* xm1, char* gx1, char* dh1, char* xm2, char* gx2, char* dh2, char* xm3, char* gx3, char* dh3)
{
	W_ReadCardLog("iR_DF01EF06Info==================START");

	return 0;

}
int _stdcall iW_DF01EF06Info(HANDLE hdev, char* xm1, char* gx1, char* dh1, char* xm2, char* gx2, char* dh2, char* xm3, char* gx3, char* dh3)
{
	return 0;

}
int _stdcall iR_DF01EF07Info(HANDLE hdev, char* whcd, char* hyzk, char* zy)
{
	W_ReadCardLog("iR_DF01EF07Info==================START");

	return 0;

}
int _stdcall iW_DF01EF07Info(HANDLE hdev, char* whcd, char* hyzk, char* zy)
{
	return 0;

}
int _stdcall iR_DF01EF08Info(HANDLE hdev, char* zjlb, char* zjhm, char* jkdah, char* xnhzh)
{
	W_ReadCardLog("iR_DF01EF08Info==================START");

	return 0;

}
int _stdcall iW_DF01EF08Info(HANDLE hdev, char* zjlb, char* zjhm, char* jkdah, char* xnhzh)
{
	return 0;

}
int _stdcall iR_DF02EF05Info(HANDLE hdev, char* abo, char* rh, char* xc, char* xzb, char* xnxgb, char* dxb, char* nxwl, char* tnb, char* qgy, char* tx, char* qgyz, char* qgqs, char* kzxyz, char* xzqbq, char* qtyxjs)
{
	return 0;

}
int _stdcall iW_DF02EF05Info(HANDLE hdev, char* abo, char* rh, char* xc, char* xzb, char* xnxgb, char* dxb, char* nxwl, char* tnb, char* qgy, char* tx, char* qgyz, char* qgqs, char* kzxyz, char* xzqbq, char* qtyxjs)
{
	return 0;

}
int _stdcall iR_DF02EF06Info(HANDLE hdev, char* jsb)
{
	return 0;

}
int _stdcall iW_DF02EF06Info(HANDLE hdev, char* jsb)
{
	return 0;

}
int _stdcall iR_DF02EF07Info(HANDLE hdev, int recordNo, char* gmwz, char* gmmc)
{
	return 0;

}
int _stdcall iW_DF02EF07Info(HANDLE hdev, char* gmwz, char* gmmc)
{
	return 0;
}
int _stdcall iR_DF02EF08Info(HANDLE hdev, int recordNo, char* jzmc, char* jzsj)
{
	return 0;

}
int _stdcall iW_DF02EF08Info(HANDLE hdev, char* jzmc, char* jzsj)
{
	return 0;

}
int _stdcall iR_DF03EF05Info(HANDLE hdev, char* jl1, char* jl2, char* jl3)
{
	return 0;
}
int _stdcall iW_DF03EF05Info(HANDLE hdev, int recordNo)
{
	return 0;
}
int _stdcall iErase_DF03EF05Info(HANDLE hdev, int recordNo)
{
	return 0;
}
int _stdcall iR_DF03EF06Info(HANDLE hdev, char* mzbs1, char* mzbs2, char* mzbs3, char* mzbs4, char* mzbs5)
{
	return 0;
}
int _stdcall iW_DF03EF06Info(HANDLE hdev, int record)
{
	return 0;
}
int _stdcall iErase_DF03EF06Info(HANDLE hdev, int record)
{
	return 0;
}
int _stdcall iR_DF03EEInfo(HANDLE hdev, int record, char* szdata, int npos, int nlen, int nstyle)
{
	return 0;
}
int _stdcall iW_DF03EEInfo(HANDLE hdev, int record, char* szdata, int npos, int nlen, int nstyle)
{
	return 0;
}
int _stdcall iR_DF03EDInfo(HANDLE hdev, int record, char* szdata, int npos, int nlen, int nstyle)
{
	return 0;
}
int _stdcall iW_DF03EDInfo(HANDLE hdev, int record, char* szdata, int npos, int nlen, int nstyle)
{
	return 0;
}
int _stdcall SM3Digest(HANDLE hdev, BYTE* pbdata, int len, BYTE* pbhash, BYTE* pbhashlen)
{
	return 0;
}
int _stdcall VerifyPin(HANDLE hdev, char* szpin, BYTE* pwdretry)
{
	return 0;
}
int _stdcall SM2SignHash(HANDLE hdev, BYTE* pbdata, int len, BYTE* pbhash, BYTE* pbhashlen)
{
	return 0;
}
int _stdcall IReader_GetDeviceCSN(HANDLE hdev, char* info)
{
	return 0;
}
int _stdcall iReader_SAM_Public(HANDLE hdev, char* info)
{
	return 0;
}
int _stdcall iReader_GetLastEEIndex(HANDLE hdev)
{
	return 0;
}
int _stdcall iReader_GetLastEDIndex(HANDLE hdev)
{
	return 0;
}
int _stdcall LockPersonalInfo(HANDLE hdev)
{
	return 0;
}
/*========================================�����ۺ϶������۷ѽӿ�=======================================================*/

int _stdcall XDT_GetHisInfo(HANDLE hdev, char* cardno, long* ye, char* xm, char* xb, char* csrq, char* sfzhm)
{
	return -1;

}
//�����Ǿ���̬��ӿں�������������������������Ϳ۷�
//����
long WINAPI XDT_BaseInfo(BASEINFO *info)
{
	return -1;
}
//�۷�
long WINAPI XDT_SetCardInfo(long objNo, long opFare, LPSTR TradeRecNo, LPSTR jyDT, LPSTR psamID, long *psamJyNo, LPSTR tac)
{
	return -1;
}
long WINAPI XDT_BaseInfo_Json(char* _json, char* _name, long *UID)
{
	return 0;
}
//��ȡɨ��ǹsocketIP��ַ
LPSTR WINAPI GetIPScanner()
{
	LPSTR LP_PATH = new char[MAX_PATH];
	LPSTR ipaddr = new char[20];
	strcpy(LP_PATH, "./ChgCity.ini");
	GetPrivateProfileStringA("SCNNER", "IP", "NULL", ipaddr, 20, LP_PATH);
	delete[] LP_PATH;
	return ipaddr;
}
//��ȡɨ��ǹ���ں�
short WINAPI GetSERIALPORT()
{
	LPSTR LP_PATH = new char[MAX_PATH];
	strcpy(LP_PATH, "./ChgCity.ini");
	short port;
	port = GetPrivateProfileIntA("SCNNER", "SERIALPORT", -1, LP_PATH);
	delete[] LP_PATH;
	return port;
}
//��ȡɨ��ǹsocket �˿�
short WINAPI GetSCANNERPORT()
{
	LPSTR LP_PATH = new char[MAX_PATH];
	strcpy(LP_PATH, "./ChgCity.ini");
	short port;
	port = GetPrivateProfileIntA("SCNNER", "PORT", -1, LP_PATH);
	delete[] LP_PATH;
	return port;
}

LPSTR WINAPI GetComInputInfo_Temp()
{
	W_ReadCardLog("GetComInputInfo==================START");
	//HMODULE hdllInst = LoadLibraryA("KeeperClient.dll");
	_mistrans trans = (_mistrans)GetProcAddress(hdllInst, "misposTrans");

	ST_MISPOS_IN st_in;
	ST_MISPOS_OUT st_out;
	memset(&st_in, 0x00, sizeof(ST_MISPOS_IN));
	memset(&st_out, 0x00, sizeof(ST_MISPOS_OUT));
	memcpy(st_in.TransType, "54", 2);	//�������ͣ���ֵ
										//ʹ�ó������в���
	memcpy(st_in.MisTraceNo, "000002", 6);
	int rc = trans(&st_in, &st_out);
	char info[300] = { 0 };
	if (0 == rc)
	{
		//memcpy(info, st_out.Remark, sizeof(st_out.Remark));
		//strcpy(info, st_out.Remark);
		std::string strTemp(st_out.Remark);
		strTemp.erase(strTemp.find_last_not_of(" ") + 1);
		strcpy(info, strTemp.c_str());
	}
	//FreeLibrary(hdllInst);
	return info;

}
int WINAPI test1(int a, int b)
{
	return a + b;
}
int WINAPI MisRund(long opFare, LPSTR ReferNo, LPSTR TransDate, LPSTR TerminalId)
{
	//HMODULE hdllInst = LoadLibraryA("KeeperClient.dll");
	_mistrans trans = (_mistrans)GetProcAddress(hdllInst, "misposTrans");

	ST_MISPOS_IN st_in;
	ST_MISPOS_OUT st_out;
	memset(&st_in, 0x00, sizeof(ST_MISPOS_IN));
	memset(&st_out, 0x00, sizeof(ST_MISPOS_OUT));
	memcpy(st_in.TransType, "04", 2);
	char amount_temp[13] = { 0 };
	char refer_temp[9] = { 0 };
	char terminal_temp[16] = { 0 };
	char date_temp[9] = { 0 };

	//sprintf(amount_temp, "%012d", opFare);
	//sprintf(refer_temp, "%08s", ReferNo);
	//sprintf(terminal_temp, "%015s", TerminalId);


	sprintf(refer_temp, "%08.8s", ReferNo);
	refer_temp[8] = '\0';
	sprintf(terminal_temp, "%-15.15s", TerminalId);
	terminal_temp[15] = '\0';
	sprintf(amount_temp, "%012.12d", opFare);
	amount_temp[12] = '\0';
	sprintf(date_temp, "%08.8s", TransDate);
	date_temp[8] = '\0';
	/*strcpy(st_in.TransAmount, amount_temp);
	strcpy(st_in.ReferNo, refer_temp);
	strcpy(st_in.TransDate, TransDate);
	strcpy(st_in.TerminalId, terminal_temp);*/
	memcpy(st_in.TransAmount, amount_temp, 12);
	memcpy(st_in.ReferNo, refer_temp, 8);
	memcpy(st_in.TransDate, date_temp, 8);
	memcpy(st_in.TerminalId, terminal_temp, 15);

	int rc = trans(&st_in, &st_out);
	//char info[300] = { 0 };
	//if (0 == rc)
	//{
	//	//memcpy(info, st_out.Remark, sizeof(st_out.Remark));
	//	//strcpy(info, st_out.Remark);
	//	std::string strTemp(st_out.Remark);
	//	strTemp.erase(strTemp.find_last_not_of(" ") + 1);
	//	strcpy(info, strTemp.c_str());
	//}
	//FreeLibrary(hdllInst);
	return rc;
}