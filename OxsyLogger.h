#ifndef __LOGGER_H__
#define __LOGGER_H__


class COxsyClassPointers;
class COxsyLogger
{

public:

	COxsyLogger(COxsyClassPointers *pClassPointers);
	virtual ~COxsyLogger();

	void InitFileInfoArray(void);

	int OpenFile(char *strFilePath, char *strMode);

	bool CloseAllFiles(void);
	bool CloseFile(int index = 0);
	bool CloseFile(char *strFilePath);

	FILE* GetFileHandler(int index = 0);
	FILE* GetFileHandler(char *strFilePath);

protected:

	int GetFileIndex(char *strFilePath);
	int GetFirstFreeIndex(void);

	COxsyClassPointers *m_pClassPointers;
	FileInfo m_FileInfoArray[OPENED_FILES_MAX];
};


#endif // __LOGGER_H__
