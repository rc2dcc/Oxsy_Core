#include "OxsyMain.h"
#include "OxsyClassPointers.h"

#include "OxsyBasicCommands.h"
//#include "OxsyCache.h"
//#include "OxsyCalculatePositions.h"
#include "OxsyClassPointers.h"
#include "OxsyClock.h"
#include "OxsyCommandsList.h"
//#include "OxsyConditions.h"
//#include "OxsyCyclesInfo.h"
#include "OxsyInfo.h"
#include "OxsyLogger.h"
//#include "OxsyMessage.h"
#include "OxsyParameters.h"
#include "OxsyPlay.h"
#include "OxsyPlayMode.h"
//#include "OxsyPositions.h"
#include "OxsyScanInfo.h"
#include "OxsyScoreInfo.h"
#include "OxsySensorInfo.h"
//#include "OxsySignal.h"
//#include "OxsySkills.h"
#include "OxsySocket.h"
#include "OxsySocketCommands.h"
//#include "OxsyStrategyLoader.h"
#include "OxsyTime.h"
#include "OxsyUtility.h"
//#include "OxsyWorldModel.h"


#ifdef WIN32
	#include <process.h>
#endif


COxsyClassPointers *COxsyMain::m_pClassPointers = NULL;

bool COxsyMain::m_bGameLogFileCreated = false;
bool COxsyMain::m_bRIThreadIsAlive = false;
bool COxsyMain::m_bSCCThreadIsAlive = false;
bool COxsyMain::m_bServerIsAlive = false;

char COxsyMain::m_strCurrentDirectory[FILE_PATH_LENGTH_MAX + 1] = "";
char COxsyMain::m_strTeamName[TEAM_NAME_LENGTH_MAX + 1] = "";
char COxsyMain::m_strServerIP[BUFFER_SIZE_MAX / 256] = "";
char COxsyMain::m_strServerPort[BUFFER_SIZE_MAX / 512] = "";
char COxsyMain::m_strServerVersion[BUFFER_SIZE_MAX / 512] = "";

#ifdef WIN32
	HANDLE COxsyMain::m_hSCCEvent = NULL;
	HANDLE COxsyMain::m_hRIThread = NULL;
	HANDLE COxsyMain::m_hSCCThread = NULL;
#else // _LINUX
	OxsyLinuxEvent COxsyMain::m_hSCCEvent;
	pthread_t COxsyMain::m_hRIThread;
	pthread_t COxsyMain::m_hSCCThread;
#endif


COxsyMain::COxsyMain()
{

}


COxsyMain::~COxsyMain()
{

}


#ifdef WIN32
	unsigned int WINAPI ReceiveInformationThreadProc(void* lpParameter)
#else // _LINUX
	void* ReceiveInformationThreadProc(void* lpParameter)
#endif
{
	COxsyMain::m_bRIThreadIsAlive = true;
	COxsyMain::m_pClassPointers->GetPlayPointer()->ReceiveInformation();
	COxsyMain::m_bRIThreadIsAlive = false;

	COxsyMain::m_bServerIsAlive = false;
	SetEvent(COxsyMain::m_hSCCEvent);

#ifdef WIN32
	_endthreadex(0);
#endif

	return 0;
}


#ifdef WIN32
	unsigned int WINAPI SimulationCycleControlerThreadProc(void* lpParameter)
#else // _LINUX
	void* SimulationCycleControlerThreadProc(void* lpParameter)
#endif
{
	COxsyMain::m_bSCCThreadIsAlive = true;
	COxsyMain::m_pClassPointers->GetPlayPointer()->SimulationCycleControler();
	COxsyMain::m_bSCCThreadIsAlive = false;

#ifdef WIN32
	_endthreadex(0);
#endif

	return 0;
}


void COxsyMain::InitOxsyPlayerClasses()
{
	m_pClassPointers = new COxsyClassPointers();

	m_pClassPointers->SetParametersPointer(new COxsyParameters(m_pClassPointers));
	m_pClassPointers->SetBasicCommandsPointer(new COxsyBasicCommands(m_pClassPointers));
//	m_pClassPointers->SetCachePointer(new COxsyCache(m_pClassPointers));
//	m_pClassPointers->SetCalculatePositionsPointer(new COxsyCalculatePositions(m_pClassPointers));
	m_pClassPointers->SetClockPointer(new COxsyClock(m_pClassPointers));
	m_pClassPointers->SetCommandsListPointer(new COxsyCommandsList(m_pClassPointers));
//	m_pClassPointers->SetConditionsPointer(new COxsyConditions(m_pClassPointers));
//	m_pClassPointers->SetCyclesInfoPointer(new COxsyCyclesInfo(m_pClassPointers));
	m_pClassPointers->SetInfoPointer(new COxsyInfo(m_pClassPointers));
	m_pClassPointers->SetLoggerPointer(new COxsyLogger(m_pClassPointers));
//	m_pClassPointers->SetMessagePointer(new COxsyMessage(m_pClassPointers));
	m_pClassPointers->SetPlayPointer(new COxsyPlay(m_pClassPointers));
	m_pClassPointers->SetPlayModePointer(new COxsyPlayMode(m_pClassPointers));
//	m_pClassPointers->SetPositionsPointer(new COxsyPositions(m_pClassPointers));
	m_pClassPointers->SetScanInfoPointer(new COxsyScanInfo(m_pClassPointers));
	m_pClassPointers->SetScoreInfoPointer(new COxsyScoreInfo(m_pClassPointers));
	m_pClassPointers->SetSensorInfoPointer(new COxsySensorInfo(m_pClassPointers));
//	m_pClassPointers->SetSignalPointer(new COxsySignal(m_pClassPointers));
//	m_pClassPointers->SetSkillsPointer(new COxsySkills(m_pClassPointers));
	m_pClassPointers->SetSocketPointer(new COxsySocket(m_pClassPointers));
	m_pClassPointers->SetSocketCommandsPointer(new COxsySocketCommands(m_pClassPointers));
//	m_pClassPointers->SetStrategyLoaderPointer(new COxsyStrategyLoader(m_pClassPointers));
	m_pClassPointers->SetTimePointer(new COxsyTime(m_pClassPointers));
	m_pClassPointers->SetUtilityPointer(new COxsyUtility(m_pClassPointers));
//	m_pClassPointers->SetWorldModelPointer(new COxsyWorldModel(m_pClassPointers));
}


void COxsyMain::ExitOxsyPlayer()
{
	COxsyCommandsList *pCommandsList = m_pClassPointers->GetCommandsListPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();

	if (pSocket->get_socket()->socketfd != SOCKET_ERROR)
	{
		// trimite comanda de deconectare catre server
		pCommandsList->Bye();
		// inchide conexiunea cu serverul
		pSocketCommands->close_connection(pSocket->get_socket());
	}

	// inchide fisierul log "Game" daca acesta este deschis
	CloseGameLogFile();

	#ifdef WIN32
		if (m_hSCCEvent) CloseHandle(m_hSCCEvent);
		if (m_hRIThread) CloseHandle(m_hRIThread);
		if (m_hSCCThread) CloseHandle(m_hSCCThread);
	#else // _LINUX
		m_hSCCEvent.destroy();
	#endif

	if (m_pClassPointers->GetLoggerPointer()) delete m_pClassPointers->GetLoggerPointer();

	if (m_pClassPointers->GetParametersPointer()) delete m_pClassPointers->GetParametersPointer();
	if (m_pClassPointers->GetBasicCommandsPointer()) delete m_pClassPointers->GetBasicCommandsPointer();
//	if (m_pClassPointers->GetCachePointer()) delete m_pClassPointers->GetCachePointer();
//	if (m_pClassPointers->GetCalculatePositionsPointer()) delete m_pClassPointers->GetCalculatePositionsPointer();
	if (m_pClassPointers->GetClockPointer()) delete m_pClassPointers->GetClockPointer();
	if (m_pClassPointers->GetCommandsListPointer()) delete m_pClassPointers->GetCommandsListPointer();
//	if (m_pClassPointers->GetConditionsPointer()) delete m_pClassPointers->GetConditionsPointer();
//	if (m_pClassPointers->GetCyclesInfoPointer()) delete m_pClassPointers->GetCyclesInfoPointer();
	if (m_pClassPointers->GetInfoPointer()) delete m_pClassPointers->GetInfoPointer();
//	if (m_pClassPointers->GetMessagePointer()) delete m_pClassPointers->GetMessagePointer();
	if (m_pClassPointers->GetPlayPointer()) delete m_pClassPointers->GetPlayPointer();
	if (m_pClassPointers->GetPlayModePointer()) delete m_pClassPointers->GetPlayModePointer();
//	if (m_pClassPointers->GetPositionsPointer()) delete m_pClassPointers->GetPositionsPointer();
	if (m_pClassPointers->GetScanInfoPointer()) delete m_pClassPointers->GetScanInfoPointer();
	if (m_pClassPointers->GetScoreInfoPointer()) delete m_pClassPointers->GetScoreInfoPointer();
	if (m_pClassPointers->GetSensorInfoPointer()) delete m_pClassPointers->GetSensorInfoPointer();
//	if (m_pClassPointers->GetSignalPointer()) delete m_pClassPointers->GetSignalPointer();
//	if (m_pClassPointers->GetSkillsPointer()) delete m_pClassPointers->GetSkillsPointer();
	if (m_pClassPointers->GetSocketPointer()) delete m_pClassPointers->GetSocketPointer();
	if (m_pClassPointers->GetSocketCommandsPointer()) delete m_pClassPointers->GetSocketCommandsPointer();
//	if (m_pClassPointers->GetStrategyLoaderPointer()) delete m_pClassPointers->GetStrategyLoaderPointer();
	if (m_pClassPointers->GetTimePointer()) delete m_pClassPointers->GetTimePointer();
	if (m_pClassPointers->GetUtilityPointer()) delete m_pClassPointers->GetUtilityPointer();
//	if (m_pClassPointers->GetWorldModelPointer()) delete m_pClassPointers->GetWorldModelPointer();

	if (m_pClassPointers) delete m_pClassPointers;
}


void COxsyMain::InitOxsyPlayerVariables()
{
	COxsyInfo *pInfo = m_pClassPointers->GetInfoPointer();
	
	if (!m_strTeamName[0]) 
	{
		if (!strcmp(DEFAULT_TEAM_SIDE, RIGHT_SIDE_NAME))
		{	
			strcpy(m_strTeamName, DEFAULT_OUR_RIGHT_TEAM_NAME);
		}
		else
		{
			strcpy(m_strTeamName, DEFAULT_OUR_LEFT_TEAM_NAME);
		}
	}

	if (!m_strServerIP[0]) strcpy(m_strServerIP, DEFAULT_SERVER_IP);
	if (!m_strServerPort[0]) strcpy(m_strServerPort, DEFAULT_SERVER_PORT);
	if (!m_strServerVersion[0]) strcpy(m_strServerVersion, DEFAULT_SERVER_VERSION);

////////////////////////////////////////// PMS //////////////////////////////////////////////

	// set default team name
	pInfo->set_our_team_name(m_strTeamName);
	pInfo->set_our_team_name_with_quotes(m_strTeamName);

	// set default opponent team name
	pInfo->set_opp_team_name(DEFAULT_OPPONENT_TEAM_NAME);

	// set default server IP
	pInfo->set_server_ip(m_strServerIP);
		
	// set default server port
	pInfo->set_server_port(atoi(m_strServerPort));

	// set default server version
	pInfo->set_server_version(atof(m_strServerVersion));

/////////////////////////////////////////////////////////////////////////////////////////////
}


bool COxsyMain::StartOxsyPlayer()
{
	COxsyCommandsList *pCommandsList = m_pClassPointers->GetCommandsListPointer();
	COxsyInfo *pInfo = m_pClassPointers->GetInfoPointer();
	COxsyParameters *pParameters = m_pClassPointers->GetParametersPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	
	char strGameLogFilePath[FILE_PATH_LENGTH_MAX + 1];

	#ifdef WIN32
		m_hSCCEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	#else // _LINUX
		m_hSCCEvent.init(false, false);
	#endif

	InitInfo info;
	PlayModeInfo playModeInfo;
	
	info = pCommandsList->Init(pInfo->get_our_team_name(), pInfo->get_server_version(), (pInfo->get_player_type() == PT_Goalie));

	if (info.side == S_Unknown || info.playMode == PM_Unknown || info.number == UNKNOWN_NUMBER || !strcmp(info.strPlayMode, UNKNOWN_NAME))
	{
		printf("Error to initiate connection with server.\n");
		return false;
	}
	else
	{
		pInfo->set_unum(info.number);
		pInfo->set_init_side(info.side);
		playModeInfo.play_mode_time = pTime->get_time();
		playModeInfo.play_mode = info.playMode;
		m_bServerIsAlive = true;
	}

	strcpy(strGameLogFilePath, m_strCurrentDirectory);
	strcat(strGameLogFilePath, GAME_LOG_FILE_NAME);

	pInfo->set_game_log_file_path(strGameLogFilePath);

	// creeaza fisierul log pentru inregistarea actziunilor din timpul jocului
	#ifdef CREATE_GAME_LOG_FILE
		CreateGameLogFile();
	#endif
		
	// takes parameters that will be sends by server or will be reads from file
	if (!pParameters->GetParameters())
	{
		if (USE_DEFAULT_PARAMETERS == false)
		{
			printf("Error to get parameters from server.\n");
			return false;
		}
	}

	// create application threads
	#ifdef WIN32

		m_hSCCThread = (HANDLE)_beginthreadex(NULL, 0, SimulationCycleControlerThreadProc, NULL, 0, NULL);
		if(m_hSCCThread == NULL)
		{
			printf("Error to create thread SimulationCycleControler.\n");
			return false;
		}

		m_hRIThread = (HANDLE)_beginthreadex(NULL, 0, ReceiveInformationThreadProc, NULL, 0, NULL);
		if(m_hRIThread == NULL)
		{
			printf("Error to create thread ReceiveInformation.\n");
			return false;
		}

	#else // _LINUX

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
		pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);

		if (pthread_create(&m_hRIThread, &attr, ReceiveInformationThreadProc, NULL) != 0)
		{
			printf("Error to create thread ReceiveInformation.\n");
			return false;
		}

		if (pthread_create(&m_hSCCThread, &attr, SimulationCycleControlerThreadProc, NULL) != 0)
		{
			printf("Error to create thread SimulationCycleControler.\n");
			return false;
		}

	#endif

//	enhance application threads priority
	#ifdef WIN32
		SetThreadPriority(m_hRIThread,THREAD_PRIORITY_TIME_CRITICAL);
		SetThreadPriority(m_hSCCThread,THREAD_PRIORITY_HIGHEST);
	#else // _LINUX
		struct sched_param param;
		int policy;
		pthread_getschedparam(m_hRIThread, &policy, &param);
		param.sched_priority = sched_get_priority_max(SCHED_RR) - 1;
		pthread_setschedparam(m_hRIThread, SCHED_RR, &param);
		param.sched_priority--;
		pthread_setschedparam(m_hSCCThread, SCHED_RR, &param);	
	#endif

	return true;
}


void COxsyMain::GetCommandLineParameters(int argc, char** argv)
{
	char *ptr;

	strcpy(m_strCurrentDirectory, argv[0]);

	#ifdef WIN32
		ptr = strrchr(m_strCurrentDirectory, '\\');
		if (ptr) *ptr = '\0';
	#else // _LINUX
		ptr = strrchr(m_strCurrentDirectory, '/');
		if (ptr) *ptr = '\0';
	#endif

	for(int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], "-team_name"))
		{
			i++;
			if (i < argc) strcpy(m_strTeamName, argv[i]);
		}
		else
			if(!strcmp(argv[i], "-server_ip"))
			{
				i++;
				if (i < argc) strcpy(m_strServerIP, argv[i]);
			}
			else
				if(!strcmp(argv[i], "-server_port"))
				{
					i++;
					if (i < argc) strcpy(m_strServerPort, argv[i]);
				}
				else
					if(!strcmp(argv[i], "-server_version"))
					{
						i++;
						if (i < argc) strcpy(m_strServerVersion, argv[i]);
					}
	}
/*
//	Only for tests purpose

	printf("%s\n", m_strCurrentDirectory);
	printf("%s\n", m_strTeamName);
	printf("%s\n", m_strServerIP);
	printf("%s\n", m_strServerPort);
	printf("%s\n", m_strServerVersion);
*/
	return;
}


void COxsyMain::CreateGameLogFile()
{
	COxsyInfo *pInfo = m_pClassPointers->GetInfoPointer();
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();

	// Deschide fisierul log "Game"
	if (pLogger->OpenFile(pInfo->get_game_log_file_path(), "w") != -1)
	{
		m_bGameLogFileCreated = true;
	}
}


void COxsyMain::CloseGameLogFile()
{
	COxsyInfo *pInfo = m_pClassPointers->GetInfoPointer();
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();

	if (pLogger->GetFileHandler(pInfo->get_game_log_file_path()))
	{
		// Inchide fisierul log "Game"
		pLogger->CloseFile(pInfo->get_game_log_file_path());
	}
}

// ------------------------------ Only for some tests purpose -----------------------------

void COxsyMain::Test()
{
	return;
	ExitOxsyPlayer();
	exit(0);
}

// ----------------------------------------------------------------------------------------
