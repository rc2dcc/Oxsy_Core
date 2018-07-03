#ifndef __CLASSPOINTERS_H__
#define __CLASSPOINTERS_H__


class COxsyBasicCommands;
//class COxsyCalculatePositions;
//class COxsyCache;
class COxsyClock;
class COxsyCommandsList;
//class COxsyConditions;
//class COxsyCyclesInfo;
class COxsyInfo;
class COxsyLogger;
//class COxsyMessage;
class COxsyParameters;
class COxsyPlay;
class COxsyPlayMode;
//class COxsyPositions;
class COxsyScanInfo;
class COxsyScoreInfo;
class COxsySensorInfo;
//class COxsySignal;
//class COxsySkills;
class COxsySocket;
class COxsySocketCommands;
//class COxsyStrategyLoader;
class COxsyTime;
class COxsyUtility;
//class COxsyWorldModel;


class COxsyClassPointers
{

public:

	COxsyClassPointers();
	virtual ~COxsyClassPointers();

//	memebers functions

	void SetBasicCommandsPointer(COxsyBasicCommands *pBasicCommands) { m_pBasicCommands = pBasicCommands; }
//	void SetCalculatePositionsPointer(COxsyCalculatePositions *pCalculatePositions) { m_pCalculatePositions = pCalculatePositions; }
//	void SetCachePointer(COxsyCache *pCache) { m_pCache = pCache; }
	void SetClockPointer(COxsyClock *pClock) { m_pClock = pClock; }
	void SetCommandsListPointer(COxsyCommandsList *pCommandsList) { m_pCommandsList = pCommandsList; }
//	void SetConditionsPointer(COxsyConditions *pConditions) { m_pConditions = pConditions; }
//	void SetCyclesInfoPointer(COxsyCyclesInfo *pCyclesInfo) { m_pCyclesInfo = pCyclesInfo; }
	void SetInfoPointer(COxsyInfo *pInfo) { m_pInfo = pInfo; }
	void SetLoggerPointer(COxsyLogger *pLogger) { m_pLogger = pLogger; }
//	void SetMessagePointer(COxsyMessage *pMessage) { m_pMessage = pMessage; }
	void SetParametersPointer(COxsyParameters *pParameters) { m_pParameters = pParameters; }
	void SetPlayPointer(COxsyPlay *pPlay) { m_pPlay = pPlay; }
	void SetPlayModePointer(COxsyPlayMode *pPlayMode) { m_pPlayMode = pPlayMode; }
//	void SetPositionsPointer(COxsyPositions *pPositions) { m_pPositions = pPositions; }
	void SetScanInfoPointer(COxsyScanInfo *pScanInfo) { m_pScanInfo = pScanInfo; }
	void SetScoreInfoPointer(COxsyScoreInfo *pScoreInfo) { m_pScoreInfo = pScoreInfo; }
	void SetSensorInfoPointer(COxsySensorInfo *pSensorInfo) { m_pSensorInfo = pSensorInfo; }
//	void SetSignalPointer(COxsySignal *pSignal) { m_pSignal = pSignal; }
//	void SetSkillsPointer(COxsySkills *pSkills) { m_pSkills = pSkills; }
	void SetSocketPointer(COxsySocket *pSocket) { m_pSocket = pSocket; }
	void SetSocketCommandsPointer(COxsySocketCommands *pSocketCommands) { m_pSocketCommands = pSocketCommands; }
//	void SetStrategyLoaderPointer(COxsyStrategyLoader *pStrategyLoader) { m_pStrategyLoader = pStrategyLoader; }
	void SetTimePointer(COxsyTime *pTime) { m_pTime = pTime; }
	void SetUtilityPointer(COxsyUtility *pUtility) { m_pUtility = pUtility; }
//	void SetWorldModelPointer(COxsyWorldModel *pWorldModel) { m_pWorldModel = pWorldModel; }

	COxsyBasicCommands *GetBasicCommandsPointer(void) { return m_pBasicCommands; }
//	COxsyCalculatePositions *GetCalculatePositionsPointer(void) { return m_pCalculatePositions; }
//	COxsyCache *GetCachePointer(void) { return m_pCache; }
	COxsyClock *GetClockPointer(void) { return m_pClock; }
	COxsyCommandsList *GetCommandsListPointer(void) { return m_pCommandsList;}
//	COxsyConditions *GetConditionsPointer(void) { return m_pConditions;}
//	COxsyCyclesInfo *GetCyclesInfoPointer(void) { return m_pCyclesInfo;}
	COxsyInfo *GetInfoPointer(void) { return m_pInfo; }
	COxsyLogger *GetLoggerPointer(void) { return m_pLogger; }
//	COxsyMessage *GetMessagePointer(void) { return m_pMessage; }
	COxsyParameters *GetParametersPointer(void) { return m_pParameters; }
	COxsyPlay *GetPlayPointer(void) { return m_pPlay; }
	COxsyPlayMode *GetPlayModePointer(void) { return m_pPlayMode; }
//	COxsyPositions *GetPositionsPointer(void) { return m_pPositions; }
	COxsyScanInfo *GetScanInfoPointer(void) { return m_pScanInfo; }
	COxsyScoreInfo *GetScoreInfoPointer(void) { return m_pScoreInfo; }
	COxsySensorInfo *GetSensorInfoPointer(void) { return m_pSensorInfo; }
//	COxsySignal *GetSignalPointer(void) { return m_pSignal; }
//	COxsySkills *GetSkillsPointer(void) { return m_pSkills; }
	COxsySocket *GetSocketPointer(void) { return m_pSocket; }
	COxsySocketCommands *GetSocketCommandsPointer(void) { return m_pSocketCommands; }
//	COxsyStrategyLoader *GetStrategyLoaderPointer(void) { return m_pStrategyLoader; }
	COxsyTime *GetTimePointer(void) { return m_pTime; }
	COxsyUtility *GetUtilityPointer(void) { return m_pUtility; }
//	COxsyWorldModel *GetWorldModelPointer(void) { return m_pWorldModel; }

protected:

//	members variables

	COxsyBasicCommands *m_pBasicCommands;
//	COxsyCalculatePositions *m_pCalculatePositions;
//	COxsyCache *m_pCache;
	COxsyClock *m_pClock;
	COxsyCommandsList *m_pCommandsList;
//	COxsyConditions *m_pConditions;
//	COxsyCyclesInfo *m_pCyclesInfo;
	COxsyInfo *m_pInfo;
	COxsyLogger *m_pLogger;
//	COxsyMessage *m_pMessage;
	COxsyParameters *m_pParameters;
	COxsyPlay *m_pPlay;
	COxsyPlayMode *m_pPlayMode;
//	COxsyPositions *m_pPositions;
	COxsyScanInfo *m_pScanInfo;
	COxsyScoreInfo *m_pScoreInfo;
	COxsySensorInfo *m_pSensorInfo;
//	COxsySignal *m_pSignal;
//	COxsySkills *m_pSkills;
	COxsySocket *m_pSocket;
	COxsySocketCommands *m_pSocketCommands;
//	COxsyStrategyLoader *m_pStrategyLoader;
	COxsyTime *m_pTime;
	COxsyUtility *m_pUtility;
//	COxsyWorldModel *m_pWorldModel;
};


#endif // __CLASSPOINTERS_H__
