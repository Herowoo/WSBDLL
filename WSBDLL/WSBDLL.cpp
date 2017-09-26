// WSBDLL.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "MyCode.h"
#include <WinSock2.h>
#include "iostream"
#pragma comment(lib,"ws2_32.lib")

//typedef struct tagCustomerInfo
//{
//	long CardClass;		//卡类型：4-M1卡，8-CPU卡
//	long CustomerID;	//账号序号
//	long CardSN;		//个人持卡序号
//	long Status;		//卡状态 F1H=正常 F3H=挂失
//	long SubType;		//卡类别
//	long Ye;			//余额	单位：分
//	long OpCount;		//消费计数
//	char Name[32];		//姓名  
//	char ValidDate[12];	//有效日期，YYYY-MM-DD
//	char CardASN[24];	//卡应用序列号
//}CUSTOMERINFO;//用户信息结构
typedef long(WINAPI *opCom)();
typedef long(WINAPI *querycard)(long*);				//寻卡
typedef long(WINAPI *getcardinfo)(CUSTOMERINFO*);	//读取用户信息
/*
	此方法用来获取卡片的黑名单状态
	入口参数：	
		ip			socket服务器地址
		port		socket服务器端口
		asn			卡片asn
	出口参数：
		recv_buf	服务器返回字符
	返回值：
		-1			WSA启动失败
		-2			socket failed
		-3			socket连接失败
		-4			向服务器发送数据失败
		0			成功
*/
long GetBlackList(const char *ip, short port, char *asn, char *recv_buf)
{
	const int BUF_SIZE = 64;
	WSADATA         wsd;            //WSADATA变量  
	SOCKET          sHost;          //服务器套接字  
	SOCKADDR_IN     servAddr;       //服务器地址  
	char            buf[BUF_SIZE];  //接收数据缓冲区  
	//char            bufRecv[BUF_SIZE];
	int             retVal;         //返回值  
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		return -1;		//WSA启动失败
	}
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost)
	{
		WSACleanup();
		return -2;		//socket failed
	}
	//服务器套接字地址
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	servAddr.sin_addr.s_addr = inet_addr(ip);

	//连接服务器
	retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));
	if (SOCKET_ERROR == retVal)
	{
		closesocket(sHost);
		WSACleanup();
		return -3;		//连接失败
	}
	//向服务器发送数据
	ZeroMemory(buf, BUF_SIZE);
	strcpy_s(buf, asn);
	//strcpy(buf, asn);	//不安全
	retVal = send(sHost, buf, strlen(buf), 0);
	if (SOCKET_ERROR == retVal)
	{
		closesocket(sHost);
		WSACleanup();
		return -4;		//发送失败
	}
	char* recvbuf = recv_buf;
	recv(sHost, recvbuf, 1, 0);
	closesocket(sHost); //关闭套接字  
	WSACleanup();       //释放套接字资源  
	return  0;
}
//打开连接
long OpenCom()
{
	HMODULE hdllInst = LoadLibrary("Cap_RW.dll");
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		opCom opencom = (opCom)GetProcAddress(hdllInst, "OpenCom");
		if (opencom==NULL)
		{
			return -1701;
		}
		else
		{
			long status_opencom = opencom();
			return status_opencom;
		}
	}
}

//读取用户信息
long CapGetNBCardInfo(CUSTOMERINFO *info)
{
	HMODULE hdllInst = LoadLibrary("Cap_RW.dll");
	if (hdllInst==NULL)
	{
		return -1801;
	}
	else
	{
		getcardinfo GetCardInfo;
		GetCardInfo = (getcardinfo)GetProcAddress(hdllInst, "CapGetNBCardInfo");
		if (GetCardInfo==NULL)
		{
			return -1701;
		}
		else
		{
			CUSTOMERINFO ctm_info;
			long status_getinfo = GetCardInfo(&ctm_info);
			const char* ipaddr = "192.168.10.65";
			short port = 8000;
			char* asn = ctm_info.CardASN;
			char recv_buf = '9';
			long status = GetBlackList(ipaddr, port, asn, &recv_buf);

			if (recv_buf=='0')
			{
				return 463;
			}
			else
			{
				return status_getinfo;
			}
			
		}
	}
}
//寻卡
long CapNBQueryCard(long *UID)
{
	HMODULE  hdllInst = LoadLibrary("Cap_RW.dll");
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		querycard QueryCard;

		QueryCard = (querycard)GetProcAddress(hdllInst, "CapNBQueryCard");
		if (QueryCard == NULL)
		{

			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			long uid;
			long query_status = QueryCard(&uid);
			return query_status;
		}
	}
}
