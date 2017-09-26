#pragma once
typedef struct tagCustomerInfo
{
	long CardClass;		//卡类型：4-M1卡，8-CPU卡
	long CustomerID;	//账号序号
	long CardSN;		//个人持卡序号
	long Status;		//卡状态 F1H=正常 F3H=挂失
	long SubType;		//卡类别
	long Ye;			//余额	单位：分
	long OpCount;		//消费计数
	char Name[32];		//姓名  
	char ValidDate[12];	//有效日期，YYYY-MM-DD
	char CardASN[24];	//卡应用序列号
}CUSTOMERINFO;//用户信息结构
#ifndef _MYCODE_H_
#define _MYCODE_H_
#ifdef DLLDEMO1_EXPORTS
#define EXPORTS_DEMO __declspec(dllexport)
#else
#define EXPORTS_DEMO __declspec(dllimport)
#endif // DLLDEMO1_EXPORTS
extern "C" {
	EXPORTS_DEMO long CapGetNBCardInfo(CUSTOMERINFO *info);
	EXPORTS_DEMO long OpenCom();
	EXPORTS_DEMO long CapNBQueryCard(long *UID);
}

#endif // !_MYCODE_H_
