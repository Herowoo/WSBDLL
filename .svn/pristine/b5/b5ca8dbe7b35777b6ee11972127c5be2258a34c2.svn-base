#if !defined(AFX_SERIAL_H__68E5E7F5_077F_4BD4_8577_513757B01671__INCLUDED_)
#define AFX_SERIAL_H__68E5E7F5_077F_4BD4_8577_513757B01671__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

class CSerial
{
public:
	CSerial();
	virtual ~CSerial();

	BOOL Open(int nPort = 2, int nBaud = 9600);
	BOOL Close();

	BOOL Clear();

	int ReadData(void *buffer, int limit);
	int SendData(const char *buffer, int size);
	int ReadDataWaiting();

	BOOL IsOpened() { return m_bOpened; };

protected:
	BOOL WriteCommByte(unsigned char ucByte);

	HANDLE m_hIDComDev;
	OVERLAPPED m_OverlappedRead, m_OverlappedWrite;
	BOOL m_bOpened;
};

#endif // !defined(AFX_SERIAL_H__68E5E7F5_077F_4BD4_8577_513757B01671__INCLUDED_)