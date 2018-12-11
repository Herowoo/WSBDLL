#include "stdafx.h"
#include "chuankou.h"
#include <stdio.h>

CSerial::CSerial()
{
	memset(&m_OverlappedRead, 0, sizeof(OVERLAPPED));
	memset(&m_OverlappedWrite, 0, sizeof(OVERLAPPED));
	m_hIDComDev = NULL;
	m_bOpened = FALSE;
}

CSerial::~CSerial()
{
	Close();
}

BOOL CSerial::Open(int nPort/*=2*/, int nBaud/*=9600*/)
{
	if (m_bOpened)
	{
		return TRUE;
	}

	char szPort[15];
	DCB dcb = { 0 };

	sprintf(szPort, "COM%d", nPort);
	m_hIDComDev = CreateFileA(szPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	//m_hIDComDev = CreateFile(szPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if (m_hIDComDev == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	if (!SetCommMask(m_hIDComDev, EV_RXCHAR | EV_TXEMPTY))
	{
		return FALSE;
	}

	memset(&m_OverlappedRead, 0, sizeof(OVERLAPPED));
	memset(&m_OverlappedWrite, 0, sizeof(OVERLAPPED));

	m_OverlappedRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_OverlappedWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	dcb.DCBlength = sizeof(DCB);
	GetCommState(m_hIDComDev, &dcb);
	dcb.BaudRate = nBaud;
	dcb.ByteSize = 8;

	BYTE byStopBits = 1;

	dcb.Parity = 0;
	if (byStopBits == 1)
		dcb.StopBits = ONESTOPBIT;
	else if (byStopBits == 2)
		dcb.StopBits = TWOSTOPBITS;
	else
		dcb.StopBits = ONE5STOPBITS;

	dcb.fDsrSensitivity = 0;
	dcb.fDtrControl = DTR_CONTROL_ENABLE;
	dcb.fOutxDsrFlow = 0;

	if (!SetCommState(m_hIDComDev, &dcb) ||
		!SetupComm(m_hIDComDev, 10000, 10000) ||
		m_OverlappedRead.hEvent == NULL ||
		m_OverlappedWrite.hEvent == NULL)
	{
		DWORD dwError = GetLastError();
		if (m_OverlappedRead.hEvent != NULL)
			CloseHandle(m_OverlappedRead.hEvent);
		if (m_OverlappedWrite.hEvent != NULL)
			CloseHandle(m_OverlappedWrite.hEvent);
		CloseHandle(m_hIDComDev);
		return FALSE;
	}

	COMMTIMEOUTS CommTimeOuts;
	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 0;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 0;	//5000;
	PurgeComm(m_hIDComDev, PURGE_TXCLEAR);
	PurgeComm(m_hIDComDev, PURGE_RXCLEAR);
	SetCommTimeouts(m_hIDComDev, &CommTimeOuts);
	m_bOpened = TRUE;

	return m_bOpened;
}

BOOL CSerial::Close()
{
	if (!m_bOpened || m_hIDComDev == NULL)
		return TRUE;

	if (m_OverlappedRead.hEvent != NULL)
		CloseHandle(m_OverlappedRead.hEvent);
	if (m_OverlappedWrite.hEvent != NULL)
		CloseHandle(m_OverlappedWrite.hEvent);
	CloseHandle(m_hIDComDev);
	m_bOpened = FALSE;
	m_hIDComDev = NULL;

	return TRUE;
}

BOOL CSerial::Clear()
{
	PurgeComm(m_hIDComDev, PURGE_TXABORT);
	PurgeComm(m_hIDComDev, PURGE_RXABORT);
	PurgeComm(m_hIDComDev, PURGE_TXCLEAR);
	PurgeComm(m_hIDComDev, PURGE_RXCLEAR);
	return TRUE;
}

BOOL CSerial::WriteCommByte(unsigned char ucByte)
{
	BOOL bWriteStat;
	DWORD dwBytesWritten;

	bWriteStat = WriteFile(m_hIDComDev, &ucByte, 1, &dwBytesWritten, &m_OverlappedWrite);
	if (!bWriteStat && (GetLastError() == ERROR_IO_PENDING))
	{
		if (WaitForSingleObject(m_OverlappedWrite.hEvent, 10 * 1000))
		{
			dwBytesWritten = 0;
		}
		else
		{
			GetOverlappedResult(m_hIDComDev, &m_OverlappedWrite, &dwBytesWritten, TRUE);
			m_OverlappedWrite.Offset += dwBytesWritten;
		}
	}

	return TRUE;
}

int CSerial::SendData(const char *buffer, int size)
{
	if (!m_bOpened || m_hIDComDev == NULL)
	{
		return 0;
	}

	BOOL bWriteStat;
	DWORD dwBytesWritten = 0;
	bWriteStat = WriteFile(m_hIDComDev, buffer, size, &dwBytesWritten, &m_OverlappedWrite);
	if (!bWriteStat && (GetLastError() == ERROR_IO_PENDING))
	{
		if (WaitForSingleObject(m_OverlappedWrite.hEvent, 10 * 1000))
		{
			dwBytesWritten = 0;
		}
		else
		{
			GetOverlappedResult(m_hIDComDev, &m_OverlappedWrite, &dwBytesWritten, TRUE);
			m_OverlappedWrite.Offset += dwBytesWritten;
		}
	}
	return (int)dwBytesWritten;
}

int CSerial::ReadDataWaiting()
{
	if (!m_bOpened || m_hIDComDev == NULL)
		return 0;

	DWORD dwErrorFlags;
	COMSTAT ComStat;

	ClearCommError(m_hIDComDev, &dwErrorFlags, &ComStat);

	return (int)ComStat.cbInQue;
}

int CSerial::ReadData(void *buffer, int limit)
{
	if (!m_bOpened || m_hIDComDev == NULL)
		return 0;

	BOOL bReadStatus;
	DWORD dwBytesRead, dwErrorFlags;
	COMSTAT ComStat;

	ClearCommError(m_hIDComDev, &dwErrorFlags, &ComStat);
	if (!ComStat.cbInQue)
		return 0;

	dwBytesRead = (DWORD)ComStat.cbInQue;
	if (limit<(int)dwBytesRead)
		dwBytesRead = (DWORD)limit;

	bReadStatus = ReadFile(m_hIDComDev, buffer, dwBytesRead, &dwBytesRead, &m_OverlappedRead);
	if (!bReadStatus)
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			WaitForSingleObject(m_OverlappedRead.hEvent, 2000);
			return (int)dwBytesRead;
		}
		return 0;
	}

	return (int)dwBytesRead;
}