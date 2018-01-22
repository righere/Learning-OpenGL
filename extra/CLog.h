#pragma once
#include <windows.h>
#include <atltime.h>
#include <sys/timeb.h>
#include <iostream>
using namespace std;

class RcLogInfo
{
public:
	RcLogInfo(void);
	~RcLogInfo(void);

public:
	//日志文件
	FILE* m_pfLogFile;
	char m_cInfo[255];

	int  SetLogFile(FILE *pfLogFile);
	int  WriteLogInfo(const char *pInfo);
};

RcLogInfo::RcLogInfo(void)
{
	m_pfLogFile = NULL;
	memset(m_cInfo, NULL, sizeof(m_cInfo));
}

RcLogInfo::~RcLogInfo(void)
{
	if (NULL != m_pfLogFile)
	{
		fclose(m_pfLogFile);
		m_pfLogFile = NULL;
	}
}

int RcLogInfo::SetLogFile(FILE *pfLogFile)
{
	m_pfLogFile = pfLogFile;
	return 0;
}

int RcLogInfo::WriteLogInfo(const char *pInfo)
{
	if (NULL != m_pfLogFile)
	{
		fprintf(m_pfLogFile, "%s", pInfo);
		fflush(m_pfLogFile);
		return 0;
	}
	return 1;
}