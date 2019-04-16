// WSBDLL.cpp : ���� DLL Ӧ�ó���ĵ���������
//
#include "stdafx.h"

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
using namespace std;
//���������״̬,��ʼֵΪ0����֤�������Ϊ-1���Ǻ�����Ϊ1
int is_black = 0;
const int T = 200;
LPCSTR CONDLL = "Cap_RW.dll";
LPCSTR iniFileName = "./ChgCity.ini";
LPSTR RIZHI = "debug.log";

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
//д�������־
void W_ReadCardLog(const char* str)
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
long SendPostRequest(const char *ip, short port, char *bufSend, char *recv_buf)
{
	W_ReadCardLog("EVENT ���ú���SendPostRequest��ʼ");
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
	closesocket(sHost); //�ر��׽���  
	WSACleanup();       //�ͷ��׽�����Դ  
	return  0;
}

//��ȡ�����ļ�IP��ַ
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
		//��������
		int _wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, req_resv, strlen(req_resv), NULL, 0);
		//����ռ�Ҫ��'\0'�����ռ䣬MultiByteToWideChar�����'\0'�ռ�
		wchar_t* _wszString = new wchar_t[_wcsLen + 1];
		//ת��
		::MultiByteToWideChar(CP_UTF8, NULL, req_resv, strlen(req_resv), _wszString, _wcsLen);
		//������'\0'
		_wszString[_wcsLen] = '\0';
		_bstr_t _b(_wszString);
		char *_rev_temp = _b;
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
	SYSTEMTIME st = { 0 };
	GetLocalTime(&st);
	char filename[64] = { 0 };
	sprintf(filename, ".//Log//Pre//Pre_%d%02d%02d.dat", st.wYear, st.wMonth, st.wDay);
	//������ʱ�ļ�
	ofstream outf("temp_comp.txt", ios::out | ios::trunc);
	ofstream unload_file("temp_unload.txt", ios::out | ios::trunc);

	LPSTR HOST = GetValueInIni("TransDetail", "HOST", iniFileName);	//�����ϴ�����
	LPSTR URL = GetValueInIni("TransDetail", "URL", iniFileName);	//�����ϴ���ַ
	char _log[256] = { 0 };
	sprintf(_log, "EVENT �������ļ���ȡ����,HOST:%s,URL:%s", HOST, URL);
	W_ReadCardLog(_log);
	//��Ԥ�ϴ��ı��ļ�
	char buffer[1024] = { 0 };
	std::ifstream fin;
	fin.open(filename, std::ios::in);
	while (!fin.eof())
	{
		fin.getline(buffer, 1024, '\n');
		int size = strlen(buffer);

		if (size > 2)
		{
			Json::Reader reader;
			Json::Value root;
			reader.parse(buffer, root, true);
			int upload_st = root["Upload"].asInt();
			if (upload_st == 0)
			{
				//�����ϴ�����
				long ret = UploadDetailByPost(buffer, HOST, URL);
				W_ReadCardLog("EVENT ���ú���UploadDetailByPost����");
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
	}
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
	f_prefile.open(filename, ios::out | ios::trunc);
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
/*========================================ʵ�ֳ���ͨ�ӿ�=======================================================*/
//������
long _stdcall OpenCom()
{
	W_ReadCardLog("EVENT ���ú���OpenCom");

	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		W_ReadCardLog("ERROR -1801 ���ض�̬��ʧ��");

		return -1801;
	}
	else
	{
		opCom opencom = (opCom)GetProcAddress(hdllInst, "OpenCom");
		if (opencom == NULL)
		{
			W_ReadCardLog("ERROR -1701 ���غ���OpenComʧ��");

			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			long status_opencom = opencom();
			char _log[64] = { 0 };
			sprintf(_log, "EVENT ���ú���OpenCom������%ld", status_opencom);
			FreeLibrary(hdllInst);
			return status_opencom;
		}
	}
}
//�ر�����
void _stdcall CloseCom()
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	closeCom c_com = (closeCom)GetProcAddress(hdllInst, "CloseCom");
	W_ReadCardLog("EVENT ���ú���CloseCom");
	c_com();
	FreeLibrary(hdllInst);
}
//��ȡ�û���Ϣ
long _stdcall  CapGetNBCardInfo(CUSTOMERINFO *info)
{
	W_ReadCardLog("EVENT ���ú���CapGetNBCardInfo");
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		W_ReadCardLog("ERROR -1801 ���ض�̬��ʧ��");
		return -1801;
	}
	else
	{
		getcardinfo GetCardInfo;
		GetCardInfo = (getcardinfo)GetProcAddress(hdllInst, "CapGetNBCardInfo");
		if (GetCardInfo == NULL)
		{
			W_ReadCardLog("ERROR -1701 δ���ҵ�CapGetNBCardInfo�ӿ�");
			return -1701;
		}
		else
		{
			//CUSTOMERINFO *ctm_info;
			long status_getinfo = GetCardInfo(info);

			//���Ӷ���-402��ѭ���������ܣ����ٶ���ʧ�ܼ��� 2018-11-14 11:41:51
			const int MAX_TEST = 3;
			int i = 0;
			while ((-402 == status_getinfo) && (i < MAX_TEST))
			{
				W_ReadCardLog("ERROR ����״̬-402�����¶���");
				CloseCom();
				OpenCom();
				status_getinfo = GetCardInfo(info);
				char _testlog[64] = { 0 };
				sprintf(_testlog, "INFO ��%d�γ��Զ���,״̬��%ld", i + 1, status_getinfo);
				W_ReadCardLog(_testlog);
				i++;
			}
			char _log[64] = { 0 };
			sprintf(_log, "INFO ��������������%ld", status_getinfo);
			W_ReadCardLog(_log);
			return status_getinfo;
		}
	}
}
long _stdcall CapNBQueryCard_NoVerify(long *UID)
{
	W_ReadCardLog("EVENT ���ú���CapNBQueryCard_NoVerify");
	HMODULE  hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		W_ReadCardLog("ERROR -1801 Ѱ�����ض�̬��ʧ��");

		return -1801;
	}
	else
	{
		querycard qCard;
		qCard = (querycard)GetProcAddress(hdllInst, "CapNBQueryCard");
		if (qCard == NULL)
		{
			W_ReadCardLog("ERROR -1701 δ���ҵ�CapNBQueryCard�ӿ�");
			return -1701;
		}
		else
		{
			long status_qCard = qCard(UID);
			char _log[64] = { 0 };
			sprintf(_log, "EVENT ���ú���CapNBQueryCard_NoVerify����������%ld", status_qCard);
			W_ReadCardLog(_log);
			return status_qCard;
		}
	}
}
//Ѱ��
long _stdcall CapNBQueryCard(long *UID)
{
	W_ReadCardLog("EVENT ���ú���CapNBQueryCard");
	HMODULE  hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		W_ReadCardLog("ERROR -1801 Ѱ�����ض�̬��ʧ��");

		return -1801;
	}
	else
	{
		querycard qCard;
		qCard = (querycard)GetProcAddress(hdllInst, "CapNBQueryCard");
		if (qCard == NULL)
		{
			W_ReadCardLog("ERROR -1701 δ���ҵ�CapNBQueryCard�ӿ�");
			return -1701;
		}
		else
		{
			long status_qCard = qCard(UID);
			char _log[64] = { 0 };
			sprintf(_log, "EVENT ���ú���CapNBQueryCard����������%ld", status_qCard);
			W_ReadCardLog(_log);
			return status_qCard;
		}
	}
}

//�ۿԭ�ӿ�
long _stdcall CapSetNBCardInfo_Unload(long objNo, long UID, long opFare, LPSTR jyDT, __int64 *psamID, long *psamJyNo, __int64 *tac)
{
	W_ReadCardLog("EVENT ���ú���CapSetNBCardInfo_Unload");
	char log[128] = { 0 };
	sprintf(log, "PARA objNo:%d,UID:%d,opFare:%d,jyDT:%s", objNo, UID, opFare, jyDT);
	W_ReadCardLog(log);
	if (is_black != 1)
	{
		W_ReadCardLog("ERROR -777 �ڿ�");
		return -777;
	}
	else
	{
		HMODULE hdllInst = LoadLibraryA(CONDLL);
		if (hdllInst == NULL)
		{
			W_ReadCardLog("ERROR -1801 Ѱ�����ض�̬��ʧ��");

			return -1801;
		}
		else
		{
			setcardinfo Set_CardInfo = (setcardinfo)GetProcAddress(hdllInst, "CapSetNBCardInfo");
			if (Set_CardInfo == NULL)
			{
				W_ReadCardLog("ERROR -1701 δ���ҵ�CapSetNBCardInfo�ӿ�");
				FreeLibrary(hdllInst);
				return -1701;
			}
			else
			{
				long _objNo = objNo;
				long _UID = UID;
				long _opFare = opFare;
				LPSTR _jyDT = jyDT;
				__int64* _psamID = psamID;
				long* _psamJyNo = psamJyNo;
				__int64* _tac = tac;
				long status_setinfo = Set_CardInfo(_objNo, _UID, _opFare, _jyDT, _psamID, _psamJyNo, _tac);
				__int64 pid = *_psamID;
				long pjyno = *_psamJyNo;
				__int64 tc = *_tac;
				//��¼�ۿ���־

				char _log[256] = { 0 };
				sprintf(_log, "PARA objNO:%ld,UID:%ld,opFare:%ld,jyDT:%s,psamID:%lld,psamJyNo:%ld,tac:%lld;status:%ld", _objNo, _UID, _opFare, _jyDT, pid, pjyno, tc, status_setinfo);
				//W_log(_log);
				W_ReadCardLog(_log);
				FreeLibrary(hdllInst);
				return status_setinfo;
			}
		}
	}
}

//�ۿ�,PSAM_IDʹ��LPSTR
long _stdcall  CapSetNBCardInfo_temp(long objNo, long UID, long opFare, LPSTR jyDT, LPSTR psamID, long *psamJyNo, char *tac, int redix)
{
	if (VerifiBlackCard_UID(UID) != 0)
	{
		return -777;
	}
	else
	{
		HMODULE hdllInst = LoadLibraryA(CONDLL);
		if (hdllInst == NULL)
		{
			return -1801;
		}
		else
		{
			setcardinfo_str Set_CardInfo = (setcardinfo_str)GetProcAddress(hdllInst, "CapSetNBCardInfo_str");
			if (Set_CardInfo == NULL)
			{
				FreeLibrary(hdllInst);
				return -1701;
			}
			else
			{
				long _objNo = objNo;
				long _UID = UID;
				long _opFare = opFare;
				LPSTR _jyDT = jyDT;
				char temp[100];
				strcpy(temp, psamID);
				__int64 _psamID = atoll(temp);
				long* _psamJyNo = psamJyNo;
				char* _tac = tac;
				long status_setinfo = Set_CardInfo(_objNo, _UID, _opFare, _jyDT, &_psamID, _psamJyNo, _tac, redix);
				char ch_temp[254];
				psamID = _i64toa(_psamID, ch_temp, 10);
				FreeLibrary(hdllInst);
				return status_setinfo;
			}
		}
	}
}
//�ۿ�Ӵ�/���޶�ܣ�
long _stdcall CapSetNBCardInfo_LMT(long objNo, long UID, long opFare, LPSTR jyDT, long onceLmt, long dayLmt, __int64 *psamID, long *psamJyNo, long *tac)
{
	if (is_black != 1)
	{
		return -777;
	}
	else
	{


		HMODULE hdllInst = LoadLibraryA(CONDLL);
		if (hdllInst == NULL)
		{
			return -1801;
		}
		else
		{
			setcardinfoLMT Set_CardInfoLMT = (setcardinfoLMT)GetProcAddress(hdllInst, "CapSetNBCardInfo_LMT");
			if (Set_CardInfoLMT == NULL)
			{
				FreeLibrary(hdllInst);
				return -1701;
			}
			else
			{

				long status_setinfoLMT = Set_CardInfoLMT(objNo, UID, opFare, jyDT, onceLmt, dayLmt, psamID, psamJyNo, tac);
				FreeLibrary(hdllInst);
				return status_setinfoLMT;
			}
		}
	}
}
//5.7.	�ۿ���޶����֤�������ѣ�
long _stdcall CapSetNBCardInfo_Verify(long objNo, long UID, long opFare, LPSTR jyDT, long onceLmt, long dayLmt, LPSTR pwd, __int64 *psamID, long *psamJyNo, long *tac)
{
	if (is_black != 1)
	{
		return -777;
	}
	else
	{
		HMODULE hdllInst = LoadLibraryA(CONDLL);
		if (hdllInst == NULL)
		{
			return -1801;
		}
		else
		{
			setcardinfoVerify Set_CardInfoVerify = (setcardinfoVerify)GetProcAddress(hdllInst, "CapSetNBCardInfo_Verify");
			if (Set_CardInfoVerify == NULL)
			{
				FreeLibrary(hdllInst);
				return -1701;
			}
			else
			{

				long status_setinfoVerify = Set_CardInfoVerify(objNo, UID, opFare, jyDT, onceLmt, dayLmt, pwd, psamID, psamJyNo, tac);
				FreeLibrary(hdllInst);
				return status_setinfoVerify;
			}
		}
	}
}

//�۷ѣ��Զ������ϴ�����
long WINAPI CapSetNBCardInfo_Str1_Unload(long objNo, long uid, long opFare, LPSTR jyDT, char *psamID, long *psamJyNo, char *tac, int redix)
{
	W_ReadCardLog("EVENT ���ú���CapSetNBCardInfo_Str1_Unload");
	char log[128] = { 0 };
	sprintf(log, "PARA objNo:%d,UID:%d,opFare:%d,jyDT:%s", objNo, uid, opFare, jyDT);
	W_ReadCardLog(log);
	//����UID���к�������֤
	long getblack_status = VerifiBlackCard_UID(uid);
	if (getblack_status != 0)
	{
		W_ReadCardLog("ERROR -777 �ڿ�");
		return -777;
	}
	else
	{
		HMODULE hdllInst = LoadLibraryA(CONDLL);
		if (hdllInst == NULL)
		{
			W_ReadCardLog("ERROR -1801 Ѱ�����ض�̬��ʧ��");
			return -1801;
		}
		else
		{
			setcardinfo_str1 set_cardstr = (setcardinfo_str1)GetProcAddress(hdllInst, "CapSetNBCardInfo_Str1");
			if (set_cardstr == NULL)
			{
				W_ReadCardLog("ERROR -1701 δ���ҵ�CapSetNBCardInfo_Str1�ӿ�");
				FreeLibrary(hdllInst);
				return -1701;
			}
			else
			{
				long status_setcardstr = set_cardstr(objNo, uid, opFare, jyDT, psamID, psamJyNo, tac, redix);
				char* str_jydt = jyDT;
				char* str_psamid = psamID;
				char* str_tac = tac;
				char _log[1024];
				sprintf(_log, "PARA objNO:%ld,UID:%ld,opFare:%ld,jyDT:%s,redix:%d,psamID:%s,psamJyNo:%ld,tac:%s;status:%d", objNo, uid, opFare, str_jydt, redix, str_psamid, *psamJyNo, str_tac, status_setcardstr);
				//W_log(_log);	//ԭ��־���ã����ϵ�./Log/ReadCard.log
				W_ReadCardLog(_log);
				FreeLibrary(hdllInst);
				return status_setcardstr;
			}
		}
	}
}
//�۷ѣ����ϴι��ܣ��޺�����У��
long WINAPI CapSetNBCardInfo_SLYY(long objNo, long uid, long opFare, LPSTR jyDT, char *psamID, long *psamJyNo, char *tac, int redix)
{
	W_ReadCardLog("EVENT ���ú���CapSetNBCardInfo_SLYY��ʼ");
	char log[128] = { 0 };
	sprintf(log, "PARA objNo:%d,UID:%d,opFare:%d,jyDT:%s", objNo, uid, opFare, jyDT);
	W_ReadCardLog(log);

	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		W_ReadCardLog("ERROR -1801 Ѱ�����ض�̬��ʧ��");
		return -1801;
	}
	else
	{
		setcardinfo_str1 set_cardstr = (setcardinfo_str1)GetProcAddress(hdllInst, "CapSetNBCardInfo_Str1");
		if (set_cardstr == NULL)
		{
			W_ReadCardLog("ERROR -1701 δ���ҵ�CapSetNBCardInfo_Str1�ӿ�");
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			long status_setcardstr = set_cardstr(objNo, uid, opFare, jyDT, psamID, psamJyNo, tac, redix);
			char* str_jydt = jyDT;
			char* str_psamid = psamID;
			char* str_tac = tac;
			char _log[1024];
			sprintf(_log, "PARA objNO:%ld,UID:%ld,opFare:%ld,jyDT:%s,redix:%d,psamID:%s,psamJyNo:%ld,tac:%s;status:%d", objNo, uid, opFare, str_jydt, redix, str_psamid, psamJyNo, str_tac, status_setcardstr);
			//W_log(_log);	ԭ��־���ã����ϵ�./Log/ReadCard.log
			W_ReadCardLog(_log);
			FreeLibrary(hdllInst);
			return status_setcardstr;
		}
	}

}
//5.15.	�ۿpsam���š�TAC�����ַ�����
long WINAPI CapSetNBCardInfo_Str1(long objNo, long uid, long opFare, LPSTR jyDT, char *psamID, long *psamJyNo, char *tac, int redix)
{
	W_ReadCardLog("EVENT ���ú���CapSetNBCardInfo_Str1��ʼ");
	//�Կ۷�JSON����ֵ
	Json::Value Charging;
	Json::FastWriter fw;
	//���ö�����������ȡ�˻����
	Sleep(T);
	if (VerifiBlackCard_UID(uid) != 0)
	{
		return -777;
	}
	else
	{
		CUSTOMERINFO custinfo;
		long ret_getcard = CapGetNBCardInfo(&custinfo);
		W_ReadCardLog("EVENT ���ú���CapGetNBCardInfo����");
		if (ret_getcard != 0)
		{
			W_ReadCardLog("ERROR ����ʧ��");
			return ret_getcard;
		}
		else
		{
			long ye = custinfo.Ye;
			//�жϿ�������Ƿ���ڿ۷ѽ��
			if (ye < opFare)
			{
				W_ReadCardLog("ERROR -11 �������С�ڿ۷ѽ��");
				return -11;
			}
			else
			{
				Charging["Oddfare"] = ye;
				string str_asn(custinfo.CardASN);
				//CARDASN��ʽ����
				string real_asn = str_asn.substr(4, strlen(custinfo.CardASN) - 6);
				char *str_temp;
				__int64 itemp = _strtoi64(real_asn.c_str(), &str_temp, 16);
				Charging["CardNo"] = std::to_string(itemp);
				Charging["OpCount"] = custinfo.OpCount;
				Charging["CustomerId"] = std::to_string(custinfo.CustomerID);
			}
		}
		//Ϊ���ٿ۷��쳣���ڲ�������ԭʼ����֮�����߳�����һС��ʱ��
		Sleep(T);

		int _redix = 10;
		//��ʼ�۷�
		
		long ret_setcard = CapSetNBCardInfo_SLYY(objNo, uid, opFare, jyDT, psamID,psamJyNo, tac, _redix);
		W_ReadCardLog("EVENT ���ú���CapSetNBCardInfo_SLYY����");
		Charging["objNo"] = objNo;
		Charging["uid"] = uid;
		Charging["opfare"] = opFare;
		Charging["psamId"] = psamID;
		Charging["psamJyNo"] = *psamJyNo;
		Charging["TAC"] = tac;
		Charging["Ret"] = ret_setcard;
		Charging["Upload"] = 0;
		//���ӽ��׼�¼��ˮ�����
		//������ʱ���ʽ
		std::string str_dt(jyDT);
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
		Charging["opDatetime"] = str_trunce.c_str();

		//����д���ı�������д��ԭʼ�ĵ�Ŀ¼��
		W_ReadCardLog("EVENT ��ʼд����ϴ�����");
		std::string jsonstr = fw.write(Charging);
		const char* org_path = "./Log//ORG";
		if (_access(org_path, 0) == -1)
		{
			_mkdir(org_path);
		}
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		char filename[64] = { 0 };
		sprintf(filename, "./Log//ORG//ORG_%d%02d%02d.dat", st.wYear, st.wMonth, st.wDay);
		WriteInFile(filename, jsonstr);
		//ͬʱд��һ�ݵ�Ԥ����Ŀ¼
		const char* pre_path = "./Log//Pre";
		if (_access(pre_path, 0) == -1)
		{
			_mkdir(pre_path);
		}
		char pre_filename[64] = { 0 };
		sprintf(pre_filename, "./Log//Pre//Pre_%d%02d%02d.dat", st.wYear, st.wMonth, st.wDay);
		WriteInFile(pre_filename, jsonstr);
		/*std::thread t(OpFile);
		t.detach();*/
		OpFile();
		W_ReadCardLog("EVENT ���ú���OpFile����");
		return ret_setcard;
	}
}
//5.8.	�������ۼ�����
long _stdcall CapUpdateNBCardStatus(long opFare, LPSTR jyDT)
{
	if (is_black != 1)
	{
		return -777;
	}
	else
	{
		HMODULE hdllInst = LoadLibraryA(CONDLL);
		if (hdllInst == NULL)
		{
			return -1801;
		}
		else
		{
			updatecardstatus update_CardStatus = (updatecardstatus)GetProcAddress(hdllInst, "CapUpdateNBCardStatus");
			if (update_CardStatus == NULL)
			{
				FreeLibrary(hdllInst);
				return -1701;
			}
			else
			{

				long status_updatecard = update_CardStatus(opFare, jyDT);
				FreeLibrary(hdllInst);
				return status_updatecard;
			}
		}
	}
}
//5.9.	���¿���/���޶�
long _stdcall CapSetNBCardStatus(long onceLmt, long dayLmt)
{
	if (is_black != 1)
	{
		return -777;
	}
	else
	{
		HMODULE hdllInst = LoadLibraryA(CONDLL);
		if (hdllInst == NULL)
		{
			return -1801;
		}
		else
		{
			setcardstatus set_CardStaus = (setcardstatus)GetProcAddress(hdllInst, "CapSetNBCardStatus");
			if (set_CardStaus == NULL)
			{
				FreeLibrary(hdllInst);
				return -1701;
			}
			else
			{
				long status_setcardstatus = set_CardStaus(onceLmt, dayLmt);
				FreeLibrary(hdllInst);
				return status_setcardstatus;
			}
		}
	}
}
//5.10.	��������
long _stdcall CapSetCardPwd(LPSTR oldPwd, LPSTR newPwd)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		setcardPWD set_CardPWD = (setcardPWD)GetProcAddress(hdllInst, "CapSetCardPwd");
		if (set_CardPWD == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			long status_setPWD = set_CardPWD(oldPwd, newPwd);
			FreeLibrary(hdllInst);
			return status_setPWD;
		}
	}
}
//5.11.	��ֵ��ʼ��
long _stdcall CapChargeInit(long objNo, long fare, __int64 *termId, long *bFare, long *no, long *random, long *mac1)
{
	if (is_black)
	{
		return -777;
	}
	else
	{
		HMODULE hdllInst = LoadLibraryA(CONDLL);
		if (hdllInst == NULL)
		{
			return -1801;
		}
		else
		{
			chargeInit charge_init = (chargeInit)GetProcAddress(hdllInst, "CapChargeInit");
			if (charge_init == NULL)
			{
				FreeLibrary(hdllInst);
				return -1701;
			}
			else
			{
				long status_chargeinit = charge_init(objNo, fare, termId, bFare, no, random, mac1);
				FreeLibrary(hdllInst);
				return status_chargeinit;
			}
		}
	}
}
//��ֵ
long _stdcall CapCharge(LPSTR dt, LPSTR mac2, LPSTR tac)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		capcharge cap_charge = (capcharge)GetProcAddress(hdllInst, "CapCharge");
		if (cap_charge == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			long status_capcharge = cap_charge(dt, mac2, tac);
			FreeLibrary(hdllInst);
			return status_capcharge;
		}
	}
}

//5.12.	�ۿTAC�����ַ�����,ԭ�ӿ�
long _stdcall CapSetNBCardInfo_Str_Unload(long objNo, long uid, long opFare, LPSTR jyDT, __int64 *psamID, long *psamJyNo, char *tac, int redix)
{
	W_ReadCardLog("EVENT ���ú���CapSetNBCardInfo_Str_Unload");
	char log[128] = { 0 };
	sprintf(log, "PARA objNo:%d,UID:%d,opFare:%d,jyDT:%s", objNo, uid, opFare, jyDT);
	W_ReadCardLog(log);

	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		W_ReadCardLog("ERROR -1801 Ѱ�����ض�̬��ʧ��");
		return -1801;
	}
	else
	{
		setcardinfo_str set_cardstr = (setcardinfo_str)GetProcAddress(hdllInst, "CapSetNBCardInfo_Str");
		if (set_cardstr == NULL)
		{
			W_ReadCardLog("ERROR -1701 δ���ҵ�CapSetNBCardInfo_Str�ӿ�");
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			long status_setcardstr = set_cardstr(objNo, uid, opFare, jyDT, psamID, psamJyNo, tac, redix);
			char* str_jydt = jyDT;

			//char* str_tac = tac;
			char _log[512];
			sprintf(_log, "PARA objNO:%ld,UID:%ld,opFare:%ld,jyDT:%s,redix:%d,psamID:%lld,psamJyNo:%ld,tac:%s;status:%d", objNo, uid, opFare, str_jydt, redix, psamID, psamJyNo, tac, status_setcardstr);
			//W_log(_log);	//ԭ��־���ã����ϵ�./Log/ReadCard.log
			W_ReadCardLog(_log);
			FreeLibrary(hdllInst);
			return status_setcardstr;
		}
	}

}
//�ۿ�����ϴ�����
long _stdcall CapSetNBCardInfo_Str(long objNo, long uid, long opFare, LPSTR jyDT, __int64 *psamID, long *psamJyNo, char *tac, int redix)
{
	W_ReadCardLog("EVENT ���ú���CapSetNBCardInfo_Str��ʼ");
	//�Կ۷�JSON����ֵ
	Json::Value Charging;
	Json::FastWriter fw;
	if (VerifiBlackCard_UID(uid) != 0)
	{
		return -777;
	}
	else
	{
		//���ö�����������ȡ�˻����
		Sleep(T);

		CUSTOMERINFO custinfo;
		long ret_getcard = CapGetNBCardInfo(&custinfo);
		W_ReadCardLog("EVENT ���ú���CapGetNBCardInfo����");
		if (ret_getcard != 0)
		{
			W_ReadCardLog("ERROR ����ʧ��");
			return ret_getcard;
		}
		else
		{
			long ye = custinfo.Ye;
			//�жϿ�������Ƿ���ڿ۷ѽ��
			if (ye < opFare)
			{
				W_ReadCardLog("ERROR -11 �������С�ڿ۷ѽ��");
				return -11;
			}
			else
			{
				Charging["Oddfare"] = ye;
				string str_asn(custinfo.CardASN);
				//CARDASN��ʽ����
				string real_asn = str_asn.substr(4, strlen(custinfo.CardASN) - 6);
				char *str_temp;
				__int64 itemp = _strtoi64(real_asn.c_str(), &str_temp, 16);
				Charging["CardNo"] = std::to_string(itemp);
				Charging["OpCount"] = custinfo.OpCount;
				Charging["CustomerId"] = std::to_string(custinfo.CustomerID);
			}
		}
		//Ϊ���ٿ۷��쳣���ڲ�������ԭʼ����֮�����߳�����һС��ʱ��
		Sleep(T);

		int _redix = 10;
		//��ʼ�۷�
		LONGLONG c_psamID = 0;
		char c_tac[24] = { 0 };
		long _psamJyNo = 0;
		long ret_setcard = CapSetNBCardInfo_Str_Unload(objNo, uid, opFare, jyDT, &c_psamID, &_psamJyNo, c_tac, _redix);
		W_ReadCardLog("EVENT ���ú���CapSetNBCardInfo_Str_Unload����");
		*psamID = c_psamID;
		*psamJyNo = _psamJyNo;
		strcpy(tac, c_tac);
		Charging["objNo"] = objNo;
		Charging["uid"] = uid;
		Charging["opfare"] = opFare;
		Charging["psamId"] = c_psamID;
		Charging["psamJyNo"] = _psamJyNo;
		Charging["TAC"] = c_tac;
		Charging["Ret"] = ret_setcard;
		Charging["Upload"] = 0;
		//���ӽ��׼�¼��ˮ�����
		//������ʱ���ʽ
		std::string str_dt(jyDT);
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
		Charging["opDatetime"] = str_trunce.c_str();

		//����д���ı�������д��ԭʼ�ĵ�Ŀ¼��
		W_ReadCardLog("EVENT ��ʼд����ϴ�����");
		std::string jsonstr = fw.write(Charging);
		const char* org_path = "./Log//ORG";
		if (_access(org_path, 0) == -1)
		{
			_mkdir(org_path);
		}
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		char filename[64] = { 0 };
		sprintf(filename, "./Log//ORG//ORG_%d%02d%02d.dat", st.wYear, st.wMonth, st.wDay);
		WriteInFile(filename, jsonstr);
		//ͬʱд��һ�ݵ�Ԥ����Ŀ¼
		const char* pre_path = "./Log//Pre";
		if (_access(pre_path, 0) == -1)
		{
			_mkdir(pre_path);
		}
		char pre_filename[64] = { 0 };
		sprintf(pre_filename, "./Log//Pre//Pre_%d%02d%02d.dat", st.wYear, st.wMonth, st.wDay);
		WriteInFile(pre_filename, jsonstr);
		/*std::thread t(OpFile);
		t.detach();*/
		OpFile();
		W_ReadCardLog("EVENT ���ú���OpFile����");
		return ret_setcard;
	}
}
//5.13.	��ȡtacֵ
long _stdcall CapGetConsumeTac(long no, LPSTR tac)
{
	/*std::thread t(OpFile);
	t.detach();*/
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		gettac get_tac = (gettac)GetProcAddress(hdllInst, "CapGetConsumeTac");
		if (get_tac == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{

			long status_gettac = get_tac(no, tac);
			FreeLibrary(hdllInst);
			return status_gettac;
		}
	}
}
//��ȡʮ�ν��׼�¼
long _stdcall CapReadRecords(CONSUMEINFO* info)
{
	HMODULE hinstance = LoadLibraryA(CONDLL);
	if (hinstance == NULL)
	{
		return -1801;
	}
	else
	{
		readrecords records = (readrecords)GetProcAddress(hinstance, "CapReadRecords");
		if (records == NULL)
		{
			FreeLibrary(hinstance);
			return -1701;
		}
		else
		{
			CONSUMEINFO* _info = info;
			long s = records(_info);
			FreeLibrary(hinstance);
			return s;
		}
	}
}

//�۷ѣ������ϴ�����
long _stdcall CapSetNBCardInfo(long objNo, long UID, long opFare, LPSTR jyDT, __int64 *psamID, long *psamJyNo, __int64 *tac)
{
	W_ReadCardLog("EVENT ���ú���CapSetNBCardInfo��ʼ");
	Json::Value Charging;
	Json::FastWriter fw;
	if (VerifiBlackCard_UID(UID) != 0)
	{
		return -777;
	}
	else
	{
		//���ö�����������ȡ�˻����
		Sleep(T);

		CUSTOMERINFO custinfo;
		long ret_getcard = CapGetNBCardInfo(&custinfo);
		W_ReadCardLog("EVENT ���ú���CapGetNBCardInfo����");
		if (ret_getcard != 0)
		{
			W_ReadCardLog("ERROR ����ʧ��");
			return ret_getcard;
		}
		else
		{
			long ye = custinfo.Ye;
			//�жϿ�������Ƿ���ڿ۷ѽ��
			if (ye < opFare)
			{
				W_ReadCardLog("ERROR -11 �������С�ڿ۷ѽ��");
				return -11;
			}
			else
			{
				Charging["Oddfare"] = custinfo.Ye;
				string str_asn(custinfo.CardASN);
				string real_asn = str_asn.substr(4, strlen(custinfo.CardASN) - 6);
				char *str_temp;
				__int64 itemp = _strtoi64(real_asn.c_str(), &str_temp, 16);
				Charging["CardNo"] = std::to_string(itemp);
				Charging["OpCount"] = custinfo.OpCount;
				Charging["CustomerId"] = std::to_string(custinfo.CustomerID);
			}
		}

		//Ϊ���ٿ۷��쳣���ڲ�������ԭʼ����֮�����߳�����һС��ʱ��
		Sleep(T);

		int _redix = 10;
		char c_psamID[24] = { 0 };
		char c_tac[24] = { 0 };
		long _psamJyNo = 0;
		long ret_setcard = CapSetNBCardInfo_SLYY(objNo, UID, opFare, jyDT, c_psamID, &_psamJyNo, c_tac, _redix);
		W_ReadCardLog("EVENT ���ú���CapSetNBCardInfo_SLYY����");
		*psamID = _atoi64(c_psamID);
		*psamJyNo = _psamJyNo;
		*tac = _atoi64(c_tac);
		//�Կ۷�JSON����ֵ
		Charging["objNo"] = objNo;
		Charging["uid"] = UID;
		Charging["opfare"] = opFare;
		char str_psamID[24] = { 0 };
		_i64toa(*psamID, str_psamID, 10);
		Charging["psamId"] = str_psamID;
		Charging["psamJyNo"] = _psamJyNo;
		char str_tac[24] = { 0 };
		_i64toa(*tac, str_tac, 10);
		Charging["TAC"] = str_tac;
		Charging["Ret"] = ret_setcard;
		Charging["Upload"] = 0;
		//���ӽ��׼�¼��ˮ�����
		//Charging["TradeRecNo"] = TradeRecNo;
		//������ʱ���ʽ
		std::string str_dt(jyDT);
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
		Charging["opDatetime"] = str_trunce.c_str();
		//����д���ı�������д��ԭʼ�ĵ�Ŀ¼��
		W_ReadCardLog("EVENT ��ʼд����ϴ�����");
		std::string jsonstr = fw.write(Charging);
		//����д���ı�������д��ԭʼ�ĵ�Ŀ¼��
		const char* org_path = "./Log//ORG";
		if (_access(org_path, 0) == -1)
		{
			_mkdir(org_path);
		}
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		char filename[64] = { 0 };
		sprintf(filename, "./Log//ORG//ORG_%d%02d%02d.dat", st.wYear, st.wMonth, st.wDay);
		WriteInFile(filename, jsonstr);
		//ͬʱд��һ�ݵ�Ԥ����Ŀ¼
		const char* pre_path = "./Log//Pre";
		if (_access(pre_path, 0) == -1)
		{
			_mkdir(pre_path);
		}
		char pre_filename[64] = { 0 };
		sprintf(pre_filename, "./Log//Pre//Pre_%d%02d%02d.dat", st.wYear, st.wMonth, st.wDay);
		WriteInFile(pre_filename, jsonstr);

		OpFile();
		W_ReadCardLog("EVENT ���ú���OpFile����");
		return ret_setcard;
	}

}

/*========================================ʵ�־��񽡿����ӿ�=======================================================*/

HANDLE _stdcall OpenDevice(int port)
{
	W_ReadCardLog("EVENT ���ú���OpenDevice��ʼ");
	HMODULE hinstance = LoadLibraryA(CONDLL);
	if (hinstance == NULL)
	{
		W_ReadCardLog("ERROR -1 ���ض�̬��ʧ��");
		return (HANDLE)-1;
	}
	else
	{
		opendevice OPDV = (opendevice)GetProcAddress(hinstance, "OpenDevice");
		if (OPDV == NULL)
		{
			W_ReadCardLog("ERROR -2 �򿪺���OpenDeviceʧ��");
			FreeLibrary(hinstance);
			return (HANDLE)-2;
		}
		else
		{
			HANDLE h_status = OPDV(port);
			FreeLibrary(hinstance);
			return h_status;
		}

	}
}
int _stdcall CloseDevice(HANDLE hdev)
{
	W_ReadCardLog("EVENT ���ú���CloseDevice��ʼ");
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		closedevice close_device = (closedevice)GetProcAddress(hdllInst, "CloseDevice");
		if (close_device == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			HANDLE _hdev = hdev;
			int status_closedevice = close_device(_hdev);
			FreeLibrary(hdllInst);
			return status_closedevice;
		}
	}

}
int _stdcall PowerOn(HANDLE hdev, int slot, char* atr)
{
	W_ReadCardLog("EVENT ���ú���PowerOn��ʼ");
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		W_ReadCardLog("ERROR -1801 ���ض�̬��ʧ��");
		return -1801;
	}
	else
	{
		poweron power_on = (poweron)GetProcAddress(hdllInst, "PowerOn");
		if (power_on == NULL)
		{
			W_ReadCardLog("ERROR -1701 �򿪺���PowerOnʧ��");

			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			HANDLE _hdev = hdev;
			int _slot = slot;
			char* _atr = atr;
			int status_poweron = power_on(hdev, slot, atr);
			if (status_poweron != 0)
			{
				if (1 == slot)
				{
					W_ReadCardLog("ERROR �û�����λʧ��");
				}
				else if (3 == slot)
				{
					W_ReadCardLog("ERROR PSAM����λʧ��");

				}
				else
				{
					char _log[64] = { 0 };
					sprintf(_log, "ERROR ���뿨�ۺŲ���%d����", _slot);
					W_ReadCardLog(_log);
				}
			}
			return status_poweron;
		}
	}
}
int _stdcall SendAPDU(HANDLE hdev, unsigned char byslot, unsigned char* pbyccommand, unsigned long len, unsigned char* pbyrcommand, int* pnrs)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		sendapdu send_apdu = (sendapdu)GetProcAddress(hdllInst, "SendAPDU");
		if (send_apdu == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			HANDLE _hdev = hdev;
			unsigned char _byslot = byslot;
			unsigned char* _pbyc = pbyccommand;
			unsigned long _len = len;
			unsigned char* _pbyr = pbyrcommand;
			int* _pnrs = pnrs;
			int stauts_sendapdu = send_apdu(_hdev, _byslot, _pbyc, _len, _pbyr, _pnrs);
			FreeLibrary(hdllInst);
			return stauts_sendapdu;
		}
	}
}
int _stdcall iR_DDF1EF05Info(HANDLE hdev, char* klb, char* gfbb, char* fkjgmc, char* fkjgdm, char* fkjgzs, char* fksj, char* kh, char* aqm, char* xpxlh, char* yycsdm)
{
	W_ReadCardLog("EVENT ���ú���iR_DDF1EF05Info��ʼ");
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		r_ddf1ef05 ef05 = (r_ddf1ef05)GetProcAddress(hdllInst, "iR_DDF1EF05Info");
		if (ef05 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_ef05 = ef05(hdev, klb, gfbb, fkjgmc, fkjgdm, fkjgzs, fksj, kh, aqm, xpxlh, yycsdm);
			FreeLibrary(hdllInst);
			return stauts_ef05;
		}
	}
}
int _stdcall iW_DDF1EF05Info(HANDLE hdev, char* klb, char* gfbb, char* fkjgmc, char* fkjgdm, char* fkjgzs, char* fksj, char* kh, char* aqm, char* xpxlh, char* yycsdm)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		w_ddf1ef05 ef05 = (w_ddf1ef05)GetProcAddress(hdllInst, "iW_DDF1EF05Info");
		if (ef05 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{

			int stauts_ef05 = ef05(hdev, klb, gfbb, fkjgmc, fkjgdm, fkjgzs, fksj, kh, aqm, xpxlh, yycsdm);
			FreeLibrary(hdllInst);
			return stauts_ef05;
		}
	}
}
int _stdcall iR_DDF1EF06Info(HANDLE hdev, char* xm, char* xb, char* mz, char* csrq, char* sfzh)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		r_ddf1ef06 ef06 = (r_ddf1ef06)GetProcAddress(hdllInst, "iR_DDF1EF06Info");
		if (ef06 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{

			int stauts_ef06 = ef06(hdev, xm, xb, mz, csrq, sfzh);
			FreeLibrary(hdllInst);
			return stauts_ef06;
		}
	}
}
int _stdcall iW_DDF1EF06Info(HANDLE hdev, char* xm, char* xb, char* mz, char* csrq, char* sfzh)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		w_ddf1ef06 ef06 = (w_ddf1ef06)GetProcAddress(hdllInst, "iW_DDF1EF06Info");
		if (ef06 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{

			int stauts_ef06 = ef06(hdev, xm, xb, mz, csrq, sfzh);
			FreeLibrary(hdllInst);
			return stauts_ef06;
		}
	}
}
int _stdcall iR_DDF1EF07Info(HANDLE hdev, char* zp_path)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		r_df1ef07 ef07 = (r_df1ef07)GetProcAddress(hdllInst, "iR_DDF1EF07Info");
		if (ef07 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{

			int stauts_ef07 = ef07(hdev, zp_path);
			FreeLibrary(hdllInst);
			return stauts_ef07;
		}
	}
}
int _stdcall iW_DDF1EF07Info(HANDLE hdev, char* zp_path)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		w_df1ef07 ef07 = (w_df1ef07)GetProcAddress(hdllInst, "iW_DDF1EF07Info");
		if (ef07 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{

			int stauts_ef07 = ef07(hdev, zp_path);
			FreeLibrary(hdllInst);
			return stauts_ef07;
		}
	}
}
int _stdcall iR_DDF1EF08Info(HANDLE hdev, char* kyxq, char* brdh1, char* brdh2, char* ylfs1, char* ylfs2, char* ylfs3)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		r_ddf1ef08 ef08 = (r_ddf1ef08)GetProcAddress(hdllInst, "iR_DDF1EF08Info");
		if (ef08 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{

			int stauts_ef08 = ef08(hdev, kyxq, brdh1, brdh2, ylfs1, ylfs2, ylfs3);
			FreeLibrary(hdllInst);
			return stauts_ef08;
		}
	}
}
int _stdcall iW_DDF1EF08Info(HANDLE hdev, char* kyxq, char* brdh1, char* brdh2, char* ylfs1, char* ylfs2, char* ylfs3)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		w_ddf1ef08 ef08 = (w_ddf1ef08)GetProcAddress(hdllInst, "iW_DDF1EF08Info");
		if (ef08 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{

			int stauts_ef08 = ef08(hdev, kyxq, brdh1, brdh2, ylfs1, ylfs2, ylfs3);
			FreeLibrary(hdllInst);
			return stauts_ef08;
		}
	}
}
int _stdcall iR_DF01EF05Info(HANDLE hdev, char* dzlb1, char* dz1, char* dzlb2, char* dz2)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		r_df01ef05 df01ef05 = (r_df01ef05)GetProcAddress(hdllInst, "iR_DF01EF05Info");
		if (df01ef05 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{

			int stauts_df01ef05 = df01ef05(hdev, dzlb1, dz1, dzlb2, dz2);
			FreeLibrary(hdllInst);
			return stauts_df01ef05;
		}
	}
}
int _stdcall iW_DF01EF05Info(HANDLE hdev, char* dzlb1, char* dz1, char* dzlb2, char* dz2)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		w_df01ef05 df01ef05 = (w_df01ef05)GetProcAddress(hdllInst, "iW_DF01EF05Info");
		if (df01ef05 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df01ef05 = df01ef05(hdev, dzlb1, dz1, dzlb2, dz2);
			FreeLibrary(hdllInst);
			return stauts_df01ef05;
		}
	}
}
int _stdcall iR_DF01EF06Info(HANDLE hdev, char* xm1, char* gx1, char* dh1, char* xm2, char* gx2, char* dh2, char* xm3, char* gx3, char* dh3)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		r_df01ef06 df01ef06 = (r_df01ef06)GetProcAddress(hdllInst, "iR_DF01EF06Info");
		if (df01ef06 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			HANDLE _hdev = hdev;
			char* _xm1 = xm1;
			char* _gx1 = gx1;
			char* _dh1 = dh1;
			char* _xm2 = xm2;
			char* _gx2 = gx2;
			char* _dh2 = dh2;
			char* _xm3 = xm3;
			char* _gx3 = gx3;
			char* _dh3 = dh3;
			int stauts_df01ef06 = df01ef06(_hdev, _xm1, _gx1, _dh1, _xm2, _gx2, _dh2, _xm3, _gx3, _dh3);
			FreeLibrary(hdllInst);
			return stauts_df01ef06;
		}
	}
}
int _stdcall iW_DF01EF06Info(HANDLE hdev, char* xm1, char* gx1, char* dh1, char* xm2, char* gx2, char* dh2, char* xm3, char* gx3, char* dh3)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		w_df01ef06 df01ef06 = (w_df01ef06)GetProcAddress(hdllInst, "iW_DF01EF06Info");
		if (df01ef06 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df01ef06 = df01ef06(hdev, xm1, gx1, dh1, xm2, gx2, dh2, xm3, gx3, dh3);
			FreeLibrary(hdllInst);
			return stauts_df01ef06;
		}
	}
}
int _stdcall iR_DF01EF07Info(HANDLE hdev, char* whcd, char* hyzk, char* zy)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		r_df01ef07 df01ef07 = (r_df01ef07)GetProcAddress(hdllInst, "iR_DF01EF07Info");
		if (df01ef07 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df01ef07 = df01ef07(hdev, whcd, hyzk, zy);
			FreeLibrary(hdllInst);
			return stauts_df01ef07;
		}
	}
}
int _stdcall iW_DF01EF07Info(HANDLE hdev, char* whcd, char* hyzk, char* zy)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		w_df01ef07 df01ef07 = (w_df01ef07)GetProcAddress(hdllInst, "iW_DF01EF07Info");
		if (df01ef07 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df01ef07 = df01ef07(hdev, whcd, hyzk, zy);
			FreeLibrary(hdllInst);
			return stauts_df01ef07;
		}
	}
}
int _stdcall iR_DF01EF08Info(HANDLE hdev, char* zjlb, char* zjhm, char* jkdah, char* xnhzh)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		r_df01ef08 df01ef08 = (r_df01ef08)GetProcAddress(hdllInst, "iR_DF01EF08Info");
		if (df01ef08 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df01ef08 = df01ef08(hdev, zjlb, zjhm, jkdah, xnhzh);
			FreeLibrary(hdllInst);
			return stauts_df01ef08;
		}
	}
}
int _stdcall iW_DF01EF08Info(HANDLE hdev, char* zjlb, char* zjhm, char* jkdah, char* xnhzh)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		w_df01ef08 df01ef08 = (w_df01ef08)GetProcAddress(hdllInst, "iW_DF01EF08Info");
		if (df01ef08 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df01ef08 = df01ef08(hdev, zjlb, zjhm, jkdah, xnhzh);
			FreeLibrary(hdllInst);
			return stauts_df01ef08;
		}
	}
}
int _stdcall iR_DF02EF05Info(HANDLE hdev, char* abo, char* rh, char* xc, char* xzb, char* xnxgb, char* dxb, char* nxwl, char* tnb, char* qgy, char* tx, char* qgyz, char* qgqs, char* kzxyz, char* xzqbq, char* qtyxjs)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		r_df02ef05 df02ef05 = (r_df02ef05)GetProcAddress(hdllInst, "iR_DF02EF05Info");
		if (df02ef05 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df02ef05 = df02ef05(hdev, abo, rh, xc, xzb, xnxgb, dxb, nxwl, tnb, qgy, tx, qgyz, qgqs, kzxyz, xzqbq, qtyxjs);
			FreeLibrary(hdllInst);
			return stauts_df02ef05;
		}
	}
}
int _stdcall iW_DF02EF05Info(HANDLE hdev, char* abo, char* rh, char* xc, char* xzb, char* xnxgb, char* dxb, char* nxwl, char* tnb, char* qgy, char* tx, char* qgyz, char* qgqs, char* kzxyz, char* xzqbq, char* qtyxjs)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		w_df02ef05 df02ef05 = (w_df02ef05)GetProcAddress(hdllInst, "iW_DF02EF05Info");
		if (df02ef05 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df02ef05 = df02ef05(hdev, abo, rh, xc, xzb, xnxgb, dxb, nxwl, tnb, qgy, tx, qgyz, qgqs, kzxyz, xzqbq, qtyxjs);
			FreeLibrary(hdllInst);
			return stauts_df02ef05;
		}
	}
}
int _stdcall iR_DF02EF06Info(HANDLE hdev, char* jsb)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		r_df02ef06 df02ef06 = (r_df02ef06)GetProcAddress(hdllInst, "iR_DF02EF06Info");
		if (df02ef06 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df02ef06 = df02ef06(hdev, jsb);
			FreeLibrary(hdllInst);
			return stauts_df02ef06;
		}
	}
}
int _stdcall iW_DF02EF06Info(HANDLE hdev, char* jsb)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		w_df02ef06 df02ef06 = (w_df02ef06)GetProcAddress(hdllInst, "iW_DF02EF06Info");
		if (df02ef06 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df02ef06 = df02ef06(hdev, jsb);
			FreeLibrary(hdllInst);
			return stauts_df02ef06;
		}
	}
}
int _stdcall iR_DF02EF07Info(HANDLE hdev, int recordNo, char* gmwz, char* gmmc)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		r_df02ef07 df02ef07 = (r_df02ef07)GetProcAddress(hdllInst, "iR_DF02EF07Info");
		if (df02ef07 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df02ef07 = df02ef07(hdev, recordNo, gmwz, gmmc);
			FreeLibrary(hdllInst);
			return stauts_df02ef07;
		}
	}
}
int _stdcall iW_DF02EF07Info(HANDLE hdev, char* gmwz, char* gmmc)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		w_df02ef07 df02ef07 = (w_df02ef07)GetProcAddress(hdllInst, "iW_DF02EF07Info");
		if (df02ef07 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df02ef07 = df02ef07(hdev, gmwz, gmmc);
			FreeLibrary(hdllInst);
			return stauts_df02ef07;
		}
	}
}
int _stdcall iR_DF02EF08Info(HANDLE hdev, int recordNo, char* jzmc, char* jzsj)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		r_df02ef08 df02ef08 = (r_df02ef08)GetProcAddress(hdllInst, "iR_DF02EF08Info");
		if (df02ef08 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df02ef08 = df02ef08(hdev, recordNo, jzmc, jzsj);
			FreeLibrary(hdllInst);
			return stauts_df02ef08;
		}
	}
}
int _stdcall iW_DF02EF08Info(HANDLE hdev, char* jzmc, char* jzsj)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		w_df02ef08 df02ef08 = (w_df02ef08)GetProcAddress(hdllInst, "iW_DF02EF08Info");
		if (df02ef08 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df02ef08 = df02ef08(hdev, jzmc, jzsj);
			FreeLibrary(hdllInst);
			return stauts_df02ef08;
		}
	}
}
int _stdcall iR_DF03EF05Info(HANDLE hdev, char* jl1, char* jl2, char* jl3)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		r_df03ef05 df03ef05 = (r_df03ef05)GetProcAddress(hdllInst, "iR_DF03EF05Info");
		if (df03ef05 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df03ef05 = df03ef05(hdev, jl1, jl2, jl3);
			FreeLibrary(hdllInst);
			return stauts_df03ef05;
		}
	}
}
int _stdcall iW_DF03EF05Info(HANDLE hdev, int recordNo)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		w_df03ef05 df03ef05 = (w_df03ef05)GetProcAddress(hdllInst, "iW_DF03EF05Info");
		if (df03ef05 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df03ef05 = df03ef05(hdev, recordNo);
			FreeLibrary(hdllInst);
			return stauts_df03ef05;
		}
	}
}
int _stdcall iErase_DF03EF05Info(HANDLE hdev, int recordNo)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		e_df03ef05 df03ef05 = (e_df03ef05)GetProcAddress(hdllInst, "iErase_DF03EF05Info");
		if (df03ef05 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df03ef05 = df03ef05(hdev, recordNo);
			FreeLibrary(hdllInst);
			return stauts_df03ef05;
		}
	}
}
int _stdcall iR_DF03EF06Info(HANDLE hdev, char* mzbs1, char* mzbs2, char* mzbs3, char* mzbs4, char* mzbs5)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		r_df03ef06 df03ef06 = (r_df03ef06)GetProcAddress(hdllInst, "iR_DF03EF06Info");
		if (df03ef06 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df03ef06 = df03ef06(hdev, mzbs1, mzbs2, mzbs3, mzbs4, mzbs5);
			FreeLibrary(hdllInst);
			return stauts_df03ef06;
		}
	}
}
int _stdcall iW_DF03EF06Info(HANDLE hdev, int record)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		w_df03ef06 df03ef06 = (w_df03ef06)GetProcAddress(hdllInst, "iW_DF03EF06Info");
		if (df03ef06 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df03ef06 = df03ef06(hdev, record);
			FreeLibrary(hdllInst);
			return stauts_df03ef06;
		}
	}
}
int _stdcall iErase_DF03EF06Info(HANDLE hdev, int record)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		e_df03ef06 df03ef06 = (e_df03ef06)GetProcAddress(hdllInst, "iErase_DF03EF06Info");
		if (df03ef06 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df03ef06 = df03ef06(hdev, record);
			FreeLibrary(hdllInst);
			return stauts_df03ef06;
		}
	}
}
int _stdcall iR_DF03EEInfo(HANDLE hdev, int record, char* szdata, int npos, int nlen, int nstyle)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		r_df03ee df03ee = (r_df03ee)GetProcAddress(hdllInst, "iR_DF03EEInfo");
		if (df03ee == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df03ee = df03ee(hdev, record, szdata, npos, nlen, nstyle);
			FreeLibrary(hdllInst);
			return stauts_df03ee;
		}
	}
}
int _stdcall iW_DF03EEInfo(HANDLE hdev, int record, char* szdata, int npos, int nlen, int nstyle)
{
	W_ReadCardLog("EVENT ����дסԺ��Ϣ�ӿ�iW_DF03EEInfo��ʼ");
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		w_df03ee df03ee = (w_df03ee)GetProcAddress(hdllInst, "iW_DF03EEInfo");
		if (df03ee == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			char _log[128] = { 0 };
			int stauts_df03ee = df03ee(hdev, record, szdata, npos, nlen, nstyle);
			if (0 == stauts_df03ee)
			{
				sprintf(_log, "INFO record:%d,npos:%d,nlen:%d,д��ɹ�", record, npos, nlen);
			}
			else
			{
				sprintf(_log, "ERROR record:%d,npos:%d,nlen:%d,д��ʧ�ܣ�����%d", record, npos, nlen, stauts_df03ee);
			}
			FreeLibrary(hdllInst);
			return stauts_df03ee;
		}
	}
}
int _stdcall iR_DF03EDInfo(HANDLE hdev, int record, char* szdata, int npos, int nlen, int nstyle)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		r_df03ed df03ed = (r_df03ed)GetProcAddress(hdllInst, "iR_DF03EDInfo");
		if (df03ed == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_df03ed = df03ed(hdev, record, szdata, npos, nlen, nstyle);
			FreeLibrary(hdllInst);
			return stauts_df03ed;
		}
	}
}
int _stdcall iW_DF03EDInfo(HANDLE hdev, int record, char* szdata, int npos, int nlen, int nstyle)
{
	W_ReadCardLog("EVENT ����д������Ϣ�ӿ�iW_DF03EDInfo��ʼ");
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		w_df03ed df03ed = (w_df03ed)GetProcAddress(hdllInst, "iW_DF03EDInfo");
		if (df03ed == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			char _log[128] = { 0 };
			int stauts_df03ed = df03ed(hdev, record, szdata, npos, nlen, nstyle);
			if (0 == stauts_df03ed)
			{
				sprintf(_log, "INFO record:%d,npos:%d,nlen:%d,д��ɹ�", record, npos, nlen);
			}
			else
			{
				sprintf(_log, "ERROR record:%d,npos:%d,nlen:%d,д��ʧ�ܣ�����%d", record, npos, nlen, stauts_df03ed);
			}
			FreeLibrary(hdllInst);
			return stauts_df03ed;
		}
	}
}
int _stdcall SM3Digest(HANDLE hdev, BYTE* pbdata, int len, BYTE* pbhash, BYTE* pbhashlen)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		sm3 _sm3 = (sm3)GetProcAddress(hdllInst, "SM3Digest");
		if (_sm3 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_sm3 = _sm3(hdev, pbdata, len, pbhash, pbhashlen);
			FreeLibrary(hdllInst);
			return stauts_sm3;
		}
	}
}
int _stdcall VerifyPin(HANDLE hdev, char* szpin, BYTE* pwdretry)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		verifypin pin = (verifypin)GetProcAddress(hdllInst, "VerifyPin");
		if (pin == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_pin = pin(hdev, szpin, pwdretry);
			FreeLibrary(hdllInst);
			return stauts_pin;
		}
	}
}
int _stdcall SM2SignHash(HANDLE hdev, BYTE* pbdata, int len, BYTE* pbhash, BYTE* pbhashlen)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		sm2 _sm2 = (sm2)GetProcAddress(hdllInst, "SM2SignHash");
		if (_sm2 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int stauts_sm2 = _sm2(hdev, pbdata, len, pbhash, pbhashlen);
			FreeLibrary(hdllInst);
			return stauts_sm2;
		}
	}
}
int _stdcall IReader_GetDeviceCSN(HANDLE hdev, char* info)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		getcsn get_csn = (getcsn)GetProcAddress(hdllInst, "IReader_GetDeviceCSN");
		if (get_csn == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int status_csn = get_csn(hdev, info);
			FreeLibrary(hdllInst);
			return status_csn;
		}
	}
}
int _stdcall iReader_SAM_Public(HANDLE hdev, char* info)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		getsam get_sam = (getsam)GetProcAddress(hdllInst, "iReader_SAM_Public");
		if (get_sam == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int status_sam = get_sam(hdev, info);
			FreeLibrary(hdllInst);
			return status_sam;
		}
	}
}
int _stdcall iReader_GetLastEEIndex(HANDLE hdev)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		get_eeindex eeindex = (get_eeindex)GetProcAddress(hdllInst, "iReader_GetLastEEIndex");
		if (eeindex == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int status_eeindex = eeindex(hdev);
			FreeLibrary(hdllInst);
			return status_eeindex;
		}
	}
}
int _stdcall iReader_GetLastEDIndex(HANDLE hdev)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		get_edindex edindex = (get_edindex)GetProcAddress(hdllInst, "iReader_GetLastEDIndex");
		if (edindex == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int status_edindex = edindex(hdev);
			FreeLibrary(hdllInst);
			return status_edindex;
		}
	}
}
int _stdcall LockPersonalInfo(HANDLE hdev)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		lockinfo lock_info = (lockinfo)GetProcAddress(hdllInst, "LockPersonalInfo");
		if (lock_info == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			int status_lock = lock_info(hdev);
			FreeLibrary(hdllInst);
			return status_lock;
		}
	}
}
/*========================================�����ۺ϶������۷ѽӿ�=======================================================*/

int _stdcall XDT_GetHisInfo(HANDLE hdev, char* cardno, long* ye, char* xm, char* xb, char* csrq, char* sfzhm)
{
	HMODULE hdllInst = LoadLibraryA(CONDLL);
	if (hdllInst == NULL)
	{
		return -1801;
	}
	else
	{
		//����ͨ��ȡ�ͻ���Ϣ
		CUSTOMERINFO info;
		getcardinfo GetCardInfo;
		GetCardInfo = (getcardinfo)GetProcAddress(hdllInst, "CapGetNBCardInfo");
		if (GetCardInfo == NULL)
		{
			return -1701;
		}
		else
		{
			//CUSTOMERINFO *ctm_info;
			long status_getinfo = GetCardInfo(&info);
			cardno = info.CityCardNo;
			*ye = info.Ye;
			//xm = info.Name;
		}
		//�������ϵ�
		char _atr[64];
		poweron jkk_poweron = (poweron)GetProcAddress(hdllInst, "PowerOn");
		long s_pn1 = jkk_poweron(hdev, 1, _atr);
		long s_pn3 = jkk_poweron(hdev, 3, _atr);
		//����������
		r_ddf1ef06 ef06 = (r_ddf1ef06)GetProcAddress(hdllInst, "iR_DDF1EF06Info");
		if (ef06 == NULL)
		{
			FreeLibrary(hdllInst);
			return -1701;
		}
		else
		{
			char mz[12];
			int stauts_ef06 = ef06(hdev, xm, xb, mz, csrq, sfzhm);
			FreeLibrary(hdllInst);
			return stauts_ef06;
		}
	}
}
//�����Ǿ���̬��ӿں�������������������������Ϳ۷�
//����
long WINAPI XDT_BaseInfo(BASEINFO *info)
{
	W_ReadCardLog("EVENT ���ú���XDT_BaseInfo��ʼ");
	BASEINFO _info;
	int op = OpenCom();
	long _uid = -1;
	if (op != 0)
	{
		return -1;
	}
	else
	{
		{
			int query_st = CapNBQueryCard(&_uid);
			if (query_st != 0)
			{
				return -2;
			}
			else
			{
				Sleep(T);
				CUSTOMERINFO custinfo;
				//����
				int getinfo_st = CapGetNBCardInfo(&custinfo);
				if (getinfo_st != 0)
				{
					return -3;
				}
				else
				{
					strcpy(info->CardASN, custinfo.CardASN);
					info->CardClass = custinfo.CardClass;
					strcpy(info->CityCardNo, custinfo.CityCardNo);
					info->CustomerID = custinfo.CustomerID;
					info->CardSN = custinfo.CardSN;
					info->Status = custinfo.Status;
					info->SubType = custinfo.SubType;
					info->Ye = custinfo.Ye;
					info->OpCount = custinfo.OpCount;
					strcpy(info->Name, custinfo.Name);
					strcpy(info->ValidDate, custinfo.ValidDate);
					CloseCom();
					//�������񽡿����ӿ�
					Sleep(T);
					HANDLE hdev = opendevice(0);

					if (hdev != (HANDLE)0)
					{
						return -4;
					}
					else
					{
						char _atr[64] = { 0 };
						Sleep(T);

						long pw1_st = PowerOn(hdev, 1, _atr);
						Sleep(T);
						long pw3_st = PowerOn(hdev, 3, _atr);

						if ((pw1_st != 0) || (pw3_st != 0))
						{
							return -5;
						}
						else
						{
							char _sfzh[18 + 1] = { 0 };
							char _xm[30 + 1] = { 0 };
							char _xb[2 + 1] = { 0 };
							char _mz[2 + 1] = { 0 };
							char _csrq[8 + 1] = { 0 };
							//��ȡ���֤��Ϣ
							Sleep(T);
							iR_DDF1EF06Info(hdev, _xm, _xb, _mz, _csrq, _sfzh);
							int len = strlen(_sfzh);
							if (len == 18)
							{
								strcpy(info->IdCardNo, _sfzh);
								std::string str_sfz(_sfzh);
								string str_sex = str_sfz.substr(16, 1);
								string str_csrq = str_sfz.substr(6, 4);
								int sex = (stoi(str_sex) % 2) == 0 ? 2 : 1;
								SYSTEMTIME _st = { 0 };
								GetLocalTime(&_st);
								char ts[24];
								sprintf(ts, "%d", _st.wYear);
								int age = stoi(ts) - stoi(str_csrq);
								info->Sex = sex;
								info->Age = age;
							}
							//��ȡ��ַ��Ϣ
							char dzlb1[3] = { 0 };
							char dz1[128] = { 0 };
							char dzlb2[3] = { 0 };
							char dz2[128] = { 0 };
							iR_DF01EF05Info(hdev, dzlb1, dz1, dzlb2, dz2);
							strcpy(info->Address1, dz1);
							strcpy(info->Address, dz2);
							return 0;
						}
					}
				}


			}
		}
	}
}
//�۷�
long WINAPI XDT_SetCardInfo(long objNo, long opFare, LPSTR TradeRecNo, LPSTR jyDT, LPSTR psamID, long *psamJyNo, LPSTR tac)
{
	W_ReadCardLog("EVENT ���ú���XDT_SetCardInfo");
	char info[128] = { 0 };
	sprintf(info, "PARA objNo:%ld,opFare:%ld,TradeRecNo:%s,jyDT:%s", objNo, opFare, TradeRecNo, jyDT);
	W_ReadCardLog(info);
	long _uid = 0;
	long ret_qcard = CapNBQueryCard(&_uid);
	W_ReadCardLog("EVENT ����CapNBQueryCard����");
	if (ret_qcard != 0)
	{
		W_ReadCardLog("ERROR -1 Ѱ��ʧ��");
		return -1;
	}
	else
	{
		if (VerifiBlackCard_UID(_uid) != 0)
		{
			return -777;
		}
		else
		{
			//�Կ۷�JSON����ֵ
			Json::Value Charging;
			Json::FastWriter fw;
			//���ö�����������ȡ�˻����
			Sleep(T);

			CUSTOMERINFO custinfo;
			long ret_getcard = CapGetNBCardInfo(&custinfo);
			W_ReadCardLog("EVENT ���ú���CapGetNBCardInfo����");
			if (ret_getcard != 0)
			{
				W_ReadCardLog("ERROR ����ʧ��");
				return ret_getcard;
			}
			else
			{
				long ye = custinfo.Ye;
				//�жϿ�������Ƿ���ڿ۷ѽ��
				if (ye < opFare)
				{
					W_ReadCardLog("ERROR -11 �������С�ڿ۷ѽ��");
					return -11;
				}
				else
				{
					Charging["Oddfare"] = ye;
					string str_asn(custinfo.CardASN);
					//CARDASN��ʽ����
					string real_asn = str_asn.substr(4, strlen(custinfo.CardASN) - 6);
					char *str_temp;
					__int64 itemp = _strtoi64(real_asn.c_str(), &str_temp, 16);
					Charging["CardNo"] = std::to_string(itemp);
					Charging["OpCount"] = custinfo.OpCount;
					Charging["CustomerId"] = std::to_string(custinfo.CustomerID);
				}
			}
			//Ϊ���ٿ۷��쳣���ڲ�������ԭʼ����֮�����߳�����һС��ʱ��
			Sleep(T);

			int _redix = 10;
			char c_psamID[24] = { 0 };
			char c_tac[24] = { 0 };
			long _psamJyNo = 0;
			//��ʼ�۷�
			long ret_setcard = CapSetNBCardInfo_SLYY(objNo, _uid, opFare, jyDT, c_psamID, &_psamJyNo, c_tac, _redix);
			W_ReadCardLog("EVENT ���ú���CapSetNBCardInfo_SLYY����");
			strcpy(psamID, c_psamID);
			*psamJyNo = _psamJyNo;
			strcpy(tac, c_tac);
			Charging["objNo"] = objNo;
			Charging["uid"] = _uid;
			Charging["opfare"] = opFare;
			Charging["psamId"] = c_psamID;
			Charging["psamJyNo"] = _psamJyNo;
			Charging["TAC"] = c_tac;
			Charging["Ret"] = ret_setcard;
			Charging["Upload"] = 0;
			//���ӽ��׼�¼��ˮ�����
			Charging["TradeRecNo"] = TradeRecNo;
			//������ʱ���ʽ
			std::string str_dt(jyDT);
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
			Charging["opDatetime"] = str_trunce.c_str();

			//����д���ı�������д��ԭʼ�ĵ�Ŀ¼��
			W_ReadCardLog("EVENT ��ʼд����ϴ�����");
			std::string jsonstr = fw.write(Charging);
			const char* org_path = "./Log//ORG";
			if (_access(org_path, 0) == -1)
			{
				_mkdir(org_path);
			}
			SYSTEMTIME st = { 0 };
			GetLocalTime(&st);
			char filename[64] = { 0 };
			sprintf(filename, "./Log//ORG//ORG_%d%02d%02d.dat", st.wYear, st.wMonth, st.wDay);
			WriteInFile(filename, jsonstr);
			//ͬʱд��һ�ݵ�Ԥ����Ŀ¼
			const char* pre_path = "./Log//Pre";
			if (_access(pre_path, 0) == -1)
			{
				_mkdir(pre_path);
			}
			char pre_filename[64] = { 0 };
			sprintf(pre_filename, "./Log//Pre//Pre_%d%02d%02d.dat", st.wYear, st.wMonth, st.wDay);
			WriteInFile(pre_filename, jsonstr);
			/*std::thread t(OpFile);
			t.detach();*/
			OpFile();
			W_ReadCardLog("EVENT ���ú���OpFile����");
			return ret_setcard;
		}
	}
}
long WINAPI XDT_BaseInfo_Json(char* _json, char* _name, long *UID)
{
	BASEINFO _info;
	Json::Value root;
	Json::FastWriter fw;
	int op = OpenCom();
	//long _uid = -1;
	if (op != 0)
	{
		return -1;
	}
	else
	{
		{
			int query_st = CapNBQueryCard(UID);	//ͬ��
			//int query_st = CapNBQueryCard_NoVerify(UID);	//ר��Ϊ����ҽԺ�ṩ�ķ���,����֤������
			if (query_st != 0)
			{
				CloseCom();
				return -2;
			}
			else
			{
				//UID = _uid;
				Sleep(T);
				CUSTOMERINFO custinfo;
				//����
				int getinfo_st = CapGetNBCardInfo(&custinfo);
				if (getinfo_st != 0)
				{
					CloseCom();
					return -3;
				}
				else
				{
					root["CardASN"] = custinfo.CardASN;
					root["CardClass"] = custinfo.CardClass;
					root["CityCardNo"] = custinfo.CityCardNo;
					root["CustomerID"] = custinfo.CustomerID;
					root["CardSN"] = custinfo.CardSN;
					root["Status"] = custinfo.Status;
					root["SubType"] = custinfo.SubType;
					root["Ye"] = custinfo.Ye;
					root["OpCount"] = custinfo.OpCount;
					strcpy(_name, custinfo.Name);
					//root["Name"] = custinfo.Name;
					root["ValidDate"] = custinfo.ValidDate;
					CloseCom();
					//�������񽡿����ӿ�
					Sleep(T);
					HANDLE hdev = opendevice(0);

					if (hdev != (HANDLE)0)
					{
						return -4;
					}
					else
					{
						char _atr[64] = { 0 };
						Sleep(T);

						long pw1_st = PowerOn(hdev, 1, _atr);
						Sleep(T);
						long pw3_st = PowerOn(hdev, 3, _atr);
						if ((pw1_st != 0) || (pw3_st != 0))
						{

							return -5;
						}
						else
						{
							char _sfzh[18 + 1] = { 0 };
							char _xm[30 + 1] = { 0 };
							char _xb[2 + 1] = { 0 };
							char _mz[2 + 1] = { 0 };
							char _csrq[8 + 1] = { 0 };
							Sleep(T);

							iR_DDF1EF06Info(hdev, _xm, _xb, _mz, _csrq, _sfzh);
							int len = strlen(_sfzh);
							if (len == 18)
							{
								root["IdCardNo"] = _sfzh;

								std::string str_sfz(_sfzh);
								string str_sex = str_sfz.substr(16, 1);
								string str_csrq = str_sfz.substr(6, 4);
								int sex = (stoi(str_sex) % 2) == 0 ? 2 : 1;
								SYSTEMTIME _st = { 0 };
								GetLocalTime(&_st);
								char ts[24];
								sprintf(ts, "%d", _st.wYear);
								int age = stoi(ts) - stoi(str_csrq);
								root["Sex"] = sex;
								root["Age"] = age;
							}

						}
					}
				}


			}
		}
	}
	strcpy(_json, fw.write(root).data());
	//��������
	int _wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, _json, strlen(_json), NULL, 0);
	//����ռ�Ҫ��'\0'�����ռ䣬MultiByteToWideChar�����'\0'�ռ�
	wchar_t* _wszString = new wchar_t[_wcsLen + 1];
	//ת��
	::MultiByteToWideChar(CP_UTF8, NULL, _json, strlen(_json), _wszString, _wcsLen);
	//������'\0'
	_wszString[_wcsLen] = '\0';
	_bstr_t _b(_wszString);
	char *_rev_temp = _b;
	strcpy(_json, _b);
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
long WINAPI GetComInputInfo(LPSTR info)
{
	CSerial cs;
	short sPort = 0;

	short serial_port = GetSERIALPORT();
	//�������ļ�SERIALPORTΪ0����û�д˲������Զ�ʶ�𴮿ںţ����޶˿ں�С��10��
	if ((serial_port == 0) || (serial_port == -1))
	{
		for (int i = 1; i < 10; i++)
		{
			bool isOpen = cs.Open(i);
			if (isOpen)
			{
				sPort = i;
				cs.Close();
			}
		}
	}
	else
	{
		sPort = serial_port;
	}
	bool bs = cs.Open(sPort);
	char rev[1024] = { 0 };
	DWORD T = 0;
	DWORD TOTAL = 20000;
	long ret = 0;
	while (T < TOTAL)
	{
		char *p = strchr(rev, '\r');
		if (p)
		{
			ret = 0;
			break;
		}
		else
		{
			Sleep(500);
			cs.ReadData(rev, 1024);
			T += 500;
			ret = -1;
		}

	}
	cs.Close();
	string str_input(rev);
	int len_r = str_input.find_first_of("\r", 0);
	string str_finnal = str_input.substr(0, len_r);
	strcpy(info, str_finnal.c_str());
	return ret;
}
LPSTR WINAPI GetComInputInfo_Temp()
{
	CSerial cs;
	short sPort = 0;

	short serial_port = GetSERIALPORT();
	if ((serial_port == 0) || (serial_port == -1))
	{
		//�Զ�ʶ�𴮿ں�
		for (int i = 1; i < 10; i++)
		{
			bool isOpen = cs.Open(i);
			if (isOpen)
			{
				sPort = i;
				cs.Close();
			}
		}
	}
	else
	{
		sPort = serial_port;
	}
	bool bs = cs.Open(sPort);
	char rev[1024] = { 0 };
	DWORD T = 0;
	DWORD TOTAL = 20000;
	long ret = 0;
	while (T < TOTAL)
	{
		char *p = strchr(rev, '\r');
		if (p)
		{
			ret = 0;
			break;
		}
		else
		{
			Sleep(500);
			cs.ReadData(rev, 1024);
			T += 500;
			ret = -1;
		}

	}
	cs.Close();
	string str_input(rev);
	int len_r = str_input.find_first_of("\r", 0);
	string str_finnal = str_input.substr(0, len_r);
	/*char info[1024] = { 0 };
	strcpy(info, str_finnal.c_str());*/
	return (char*)str_finnal.data();
}
int WINAPI test1(int a, int b)
{
	return a + b;
}
