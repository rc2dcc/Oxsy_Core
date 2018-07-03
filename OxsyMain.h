#ifndef __MAIN_H__
#define __MAIN_H__


#include "OxsyLibrary.h"

#ifndef WIN32 // _LINUX
#include "OxsyLinuxEvent.h"
#endif

using namespace std;

class COxsyClassPointers;
class COxsyMain
{

public:

	COxsyMain();
	virtual ~COxsyMain();

//  members functions
	static void InitOxsyPlayerClasses(void);
	static void InitOxsyPlayerVariables(void);
	static void GetCommandLineParameters(int argc, char** argv);

	static void CreateGameLogFile(void);
	static void CloseGameLogFile(void);
	static bool StartOxsyPlayer(void);
	static void ExitOxsyPlayer(void);

	// only for some tests purpose
	static void Test(void);

//  members variables
	static COxsyClassPointers *m_pClassPointers;

	static char m_strCurrentDirectory[FILE_PATH_LENGTH_MAX + 1];
	static char m_strTeamName[TEAM_NAME_LENGTH_MAX + 1];
	static char m_strPlayerID[BUFFER_SIZE_MAX / 256];
	static char m_strServerIP[BUFFER_SIZE_MAX / 256];
	static char m_strServerPort[BUFFER_SIZE_MAX / 512];
	static char m_strServerVersion[BUFFER_SIZE_MAX / 512];

	static bool m_bGameLogFileCreated;
	static bool m_bRIThreadIsAlive;
	static bool m_bSCCThreadIsAlive;
	static bool m_bServerIsAlive;

	#ifdef WIN32
		static HANDLE m_hSCCEvent;
		static HANDLE m_hRIThread;
		static HANDLE m_hSCCThread;
	#else // _LINUX
		static OxsyLinuxEvent m_hSCCEvent;
		static pthread_t m_hRIThread;
		static pthread_t m_hSCCThread;
	#endif	
};


#ifdef WIN32
	unsigned int WINAPI SimulationCycleControlerThreadProc(void* lpParameter);
	unsigned int WINAPI ReceiveInformationThreadProc(void* lpParameter);
#else // _LINUX
	void* SimulationCycleControlerThreadProc(void* lpParameter);
	void* ReceiveInformationThreadProc(void* lpParameter);
#endif


#endif // __MAIN_H__
