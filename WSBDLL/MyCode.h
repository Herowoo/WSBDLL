#pragma once

#ifndef _MYCODE_H_
#define _MYCODE_H_

#ifdef DLLDEMO1_EXPORTS
#define EXPORTS_DEMO __declspec(dllexport)
#else
#define EXPORTS_DEMO __declspec(dllimport)
#endif // DLLDEMO1_EXPORTS
//extern struct  CUSTOMERINFO ;
//客户信息
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
	char CityCardNo[21];//卡号
}CUSTOMERINFO;//用户信息结构	
//交易信息
typedef struct tagConsumeInfo
{
	__int64 psamID;		//PSAM卡号，64位长整型
	long opFare;		//交易金额
	long opType;		//交易类型
	long psamJyNo;		//交易序号
	char jyDT[20];		//交易日期时间，YYYY-MM-DD HH:MM:SS
}CONSUMEINFO;

extern "C" 
{
	EXPORTS_DEMO long _stdcall  CapSetNBCardInfo_temp(long objNo, long uid, long opFare, LPSTR jyDT, LPSTR psamID, long *psamJyNo, char* tac,int redix);
	EXPORTS_DEMO long _stdcall  CapGetNBCardInfo(CUSTOMERINFO* info);
	EXPORTS_DEMO long _stdcall  OpenCom();
	EXPORTS_DEMO long _stdcall  CapNBQueryCard(long *UID);
	EXPORTS_DEMO void  CloseCom();
	EXPORTS_DEMO long _stdcall  CapSetNBCardInfo(long objNo, long UID, long opFare, LPSTR jyDT, __int64 *psamID, long *psamJyNo, long *tac);
	EXPORTS_DEMO long _stdcall  CapSetNBCardInfo_LMT(long objNo, long UID, long opFare, LPSTR jyDT, long onceLmt, long dayLmt, __int64 *psamID, long *psamJyNo, long *tac);
	EXPORTS_DEMO long _stdcall  CapSetNBCardInfo_Verify(long objNo, long UID, long opFare, LPSTR jyDT, long onceLmt, long dayLmt, LPSTR pwd, __int64 *psamID, long *psamJyNo, long *tac);
	EXPORTS_DEMO long _stdcall  CapUpdateNBCardStatus(long opFare, LPSTR jyDT);
	EXPORTS_DEMO long _stdcall  CapSetNBCardStatus(long onceLmt, long dayLmt);
	EXPORTS_DEMO long _stdcall  CapSetCardPwd(LPSTR oldPwd, LPSTR newPwd);
	EXPORTS_DEMO long _stdcall  CapChargeInit(long objNo, long fare, __int64 *termId, long *bFare, long *no, long *random, long *mac1);
	EXPORTS_DEMO long _stdcall  CapCharge(LPSTR dt, LPSTR mac2, LPSTR tac);
	EXPORTS_DEMO long _stdcall  CapSetNBCardInfo_Str(long objNo, long uid, long opFare, LPSTR jyDT, __int64 *psamID, long *psamJyNo, char *tac, int redix);
	EXPORTS_DEMO long _stdcall  CapGetConsumeTac(long no, LPTSTR tac);
	EXPORTS_DEMO long _stdcall  CapReadRecords(CONSUMEINFO* info);
	EXPORTS_DEMO HANDLE _stdcall OpenDevice(int port);
	EXPORTS_DEMO int _stdcall  CloseDevice(HANDLE hdev);
	EXPORTS_DEMO int _stdcall  PowerOn(HANDLE hdev, int slot, char* atr);
	EXPORTS_DEMO int _stdcall  SendAPDU(HANDLE hdev, unsigned char byslot, unsigned char* pbyccommand, unsigned long len, unsigned char* pbyrcommand, int* pnrs);
	EXPORTS_DEMO int _stdcall  iR_DDF1EF05Info(HANDLE hdev, char* klb, char* gfbb, char* fkjgmc, char* fkjgdm, char* fkjgzs, char* fksj, char* kh, char* aqm, char* xpxlh, char* yycsdm);
	EXPORTS_DEMO int _stdcall  iW_DDF1EF05Info(HANDLE hdev, char* klb, char* gfbb, char* fkjgmc, char* fkjgdm, char* fkjgzs, char* fksj, char* kh, char* aqm, char* xpxlh, char* yycsdm);
	EXPORTS_DEMO int _stdcall  iR_DDF1EF06Info(HANDLE hdev, char* xm, char* xb, char* mz, char* csrq, char* sfzh);
	EXPORTS_DEMO int _stdcall  iW_DDF1EF06Info(HANDLE hdev, char* xm, char* xb, char* mz, char* csrq, char* sfzh);
	EXPORTS_DEMO int _stdcall  iR_DDF1EF07Info(HANDLE hdev, char* zp_path);
	EXPORTS_DEMO int _stdcall  iW_DDF1EF07Info(HANDLE hdev, char* zp_path);
	EXPORTS_DEMO int _stdcall  iR_DDF1EF08Info(HANDLE hdev, char* kyxq, char* brdh1, char* brdh2, char* ylfs1, char* ylfs2, char* ylfs3);
	EXPORTS_DEMO int _stdcall  iW_DDF1EF08Info(HANDLE hdev, char* kyxq, char* brdh1, char* brdh2, char* ylfs1, char* ylfs2, char* ylfs3);
	EXPORTS_DEMO int _stdcall  iR_DF01EF05Info(HANDLE hdev, char* dzlb1, char* dz1, char* dzlb2, char* dz2);
	EXPORTS_DEMO int _stdcall  iW_DF01EF05Info(HANDLE hdev, char* dzlb1, char* dz1, char* dzlb2, char* dz2);
	EXPORTS_DEMO int _stdcall  iR_DF01EF06Info(HANDLE hdev, char* xm1, char* gx1, char* dh1, char* xm2, char* gx2, char* dh2, char* xm3, char* gx3, char* dh3);
	EXPORTS_DEMO int _stdcall  iW_DF01EF06Info(HANDLE hdev, char* xm1, char* gx1, char* dh1, char* xm2, char* gx2, char* dh2, char* xm3, char* gx3, char* dh3);
	EXPORTS_DEMO int _stdcall  iR_DF01EF07Info(HANDLE hdev, char* whcd, char* hyzk, char* zy);
	EXPORTS_DEMO int _stdcall  iW_DF01EF07Info(HANDLE hdev, char* whcd, char* hyzk, char* zy);
	EXPORTS_DEMO int _stdcall  iR_DF01EF08Info(HANDLE hdev, char* zjlb, char* zjhm, char* jkdah, char* xnhzh);
	EXPORTS_DEMO int _stdcall  iW_DF01EF08Info(HANDLE hdev, char* zjlb, char* zjhm, char* jkdah, char* xnhzh);
	EXPORTS_DEMO int _stdcall  iR_DF02EF05Info(HANDLE hdev, char* abo, char* rh, char* xc, char* xzb, char* xnxgb, char* dxb, char* nxwl, char* tnb, char* qgy, char* tx, char* qgyz, char* qgqs, char* kzxyz, char* xzqbq, char* qtyxjs);
	EXPORTS_DEMO int _stdcall  iW_DF02EF05Info(HANDLE hdev, char* abo, char* rh, char* xc, char* xzb, char* xnxgb, char* dxb, char* nxwl, char* tnb, char* qgy, char* tx, char* qgyz, char* qgqs, char* kzxyz, char* xzqbq, char* qtyxjs);
	EXPORTS_DEMO int _stdcall  iR_DF02EF06Info(HANDLE hdev, char* jsb);
	EXPORTS_DEMO int _stdcall  iW_DF02EF06Info(HANDLE hdev, char* jsb);
	EXPORTS_DEMO int _stdcall  iR_DF02EF07Info(HANDLE hdev, int recordNo, char* gmwz, char* gmmc);
	EXPORTS_DEMO int _stdcall  iW_DF02EF07Info(HANDLE hdev, char* gmwz, char* gmmc);
	EXPORTS_DEMO int _stdcall  iR_DF02EF08Info(HANDLE hdev, int recordNo, char* jzmc, char* jzsj);
	EXPORTS_DEMO int _stdcall  iW_DF02EF08Info(HANDLE hdev, char* jzmc, char* jzsj);
	EXPORTS_DEMO int _stdcall  iR_DF03EF05Info(HANDLE hdev, char* jl1, char* jl2, char* jl3);
	EXPORTS_DEMO int _stdcall  iW_DF03EF05Info(HANDLE hdev, int recordNo);
	EXPORTS_DEMO int _stdcall  iErase_DF03EF05Info(HANDLE hdev, int recordNo);
	EXPORTS_DEMO int _stdcall  iR_DF03EF06Info(HANDLE hdev, char* mzbs1, char* mzbs2, char* mzbs3, char* mzbs4, char* mzbs5);
	EXPORTS_DEMO int _stdcall  iW_DF03EF06Info(HANDLE hdev, int record);
	EXPORTS_DEMO int _stdcall  iErase_DF03EF06Info(HANDLE hdev, int record);
	EXPORTS_DEMO int _stdcall  iR_DF03EEInfo(HANDLE hdev, int record, char* szdata, int npos, int nlen, int nstyle);
	EXPORTS_DEMO int _stdcall  iW_DF03EEInfo(HANDLE hdev, int record, char* szdata, int npos, int nlen, int nstyle);
	EXPORTS_DEMO int _stdcall  iR_DF03EDInfo(HANDLE hdev, int record, char* szdata, int npos, int nlen, int nstyle);
	EXPORTS_DEMO int _stdcall  iW_DF03EDInfo(HANDLE hdev, int record, char* szdata, int npos, int nlen, int nstyle);
	EXPORTS_DEMO int _stdcall  SM3Digest(HANDLE hdev, BYTE* pbdata, int len, BYTE* pbhash, BYTE* pbhashlen);
	EXPORTS_DEMO int _stdcall  VerifyPin(HANDLE hdev, char* szpin, BYTE* pwdretry);
	EXPORTS_DEMO int _stdcall  SM2SignHash(HANDLE hdev, BYTE* pbdata, int len, BYTE* pbhash, BYTE* pbhashlen);
	EXPORTS_DEMO int _stdcall  IReader_GetDeviceCSN(HANDLE hdev, char* info);
	EXPORTS_DEMO int _stdcall  iReader_SAM_Public(HANDLE hdev, char* info);
	EXPORTS_DEMO int _stdcall  iReader_GetLastEEIndex(HANDLE hdev);
	EXPORTS_DEMO int _stdcall  iReader_GetLastEDIndex(HANDLE hdev);
	EXPORTS_DEMO int _stdcall  LockPersonalInfo(HANDLE hdev);

	EXPORTS_DEMO int _stdcall XDT_GetHisInfo(HANDLE hdev, char* kh, long* ye, char* xm, char* xb, char* csrq, char* sfzhm);
}
#endif // !_MYCODE_H_
