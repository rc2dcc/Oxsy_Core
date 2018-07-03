#include "OxsyLibrary.h"
#include "OxsyLogger.h"
#include "OxsyClassPointers.h"


COxsyLogger::COxsyLogger(COxsyClassPointers *pClassPointers)
{
	m_pClassPointers = pClassPointers;
	InitFileInfoArray();
}


COxsyLogger::~COxsyLogger()
{
	CloseAllFiles();
}


void COxsyLogger::InitFileInfoArray()
{
	for (int i = 0; i < OPENED_FILES_MAX; i++)
	{
		m_FileInfoArray[i].fileHandler = NULL;
		m_FileInfoArray[i].strFilePath = NULL;
	}
}


int COxsyLogger::OpenFile(char *strFilePath, char *strMode)
{
	char strMessage[BUFFER_SIZE_MAX / 8];
	int index = GetFirstFreeIndex();

	if (index >= 0 && index < OPENED_FILES_MAX)
	{
		if ((m_FileInfoArray[index].fileHandler = fopen(strFilePath, strMode)) == NULL)
		{
			strcpy(strMessage, "Error open file ");
			strcat(strMessage, strFilePath);
			printf("%s\n", strMessage);
			return -1;
		}

		m_FileInfoArray[index].strFilePath = new char[strlen(strFilePath) + 1];
		strcpy(m_FileInfoArray[index].strFilePath, strFilePath);
	}
	else
	{
		strcpy(strMessage, "Index out of limits.");
		printf("%s\n", strMessage);
		return -1;
	}

	return index;
}


bool COxsyLogger::CloseAllFiles()
{
	int i;
	bool bReturn = true;
	char strMessage[BUFFER_SIZE_MAX / 8];

	for (i = 0; i < OPENED_FILES_MAX; i++)
	{
		if (m_FileInfoArray[i].fileHandler)
		{
			if (fclose(m_FileInfoArray[i].fileHandler) == EOF) 
			{
				bReturn = false;
				strcpy(strMessage, "Error close file ");
				strcat(strMessage, m_FileInfoArray[i].strFilePath);
				printf("%s\n", strMessage);
				continue;
			}

			m_FileInfoArray[i].fileHandler = NULL;
		}

		if(m_FileInfoArray[i].strFilePath)
		{
			delete m_FileInfoArray[i].strFilePath;
			m_FileInfoArray[i].strFilePath = NULL;
		}
	}

	return bReturn;
}


bool COxsyLogger::CloseFile(int index)
{
	char strMessage[BUFFER_SIZE_MAX / 8];

	if (index >= 0 && index < OPENED_FILES_MAX)
	{
		if (m_FileInfoArray[index].fileHandler)
		{
			if (fclose(m_FileInfoArray[index].fileHandler) == EOF) 
			{
				strcpy(strMessage, "Error close file ");
				strcat(strMessage, m_FileInfoArray[index].strFilePath);
				printf("%s\n", strMessage);
				return false;
			}

			m_FileInfoArray[index].fileHandler = NULL;
		}

		if(m_FileInfoArray[index].strFilePath)
		{
			delete m_FileInfoArray[index].strFilePath;
			m_FileInfoArray[index].strFilePath = NULL;
		}
	}
	else
	{
		strcpy(strMessage, "Index out of limits.");
		printf("%s\n", strMessage);
		return false;
	}

	return true;
}


bool COxsyLogger::CloseFile(char *strFilePath)
{
	return CloseFile(GetFileIndex(strFilePath));
}


FILE* COxsyLogger::GetFileHandler(int index)
{
	if (index >= 0 && index < OPENED_FILES_MAX)
	{
		return m_FileInfoArray[index].fileHandler;
	}
	else
	{
		return (FILE*)NULL;
	}
}


FILE* COxsyLogger::GetFileHandler(char *strFilePath)
{
	return GetFileHandler(GetFileIndex(strFilePath));
}


int COxsyLogger::GetFileIndex(char *strFilePath)
{
	for (int i = 0; i < OPENED_FILES_MAX; i++)
	{
		if (m_FileInfoArray[i].fileHandler && !strcmp(strFilePath, m_FileInfoArray[i].strFilePath)) return i;
	}

	return -1;
}


int COxsyLogger::GetFirstFreeIndex()
{
	for (int i = 0; i < OPENED_FILES_MAX; i++)
	{
		if (m_FileInfoArray[i].fileHandler == NULL && m_FileInfoArray[i].strFilePath == NULL) return i;
	}

	return -1;
}
