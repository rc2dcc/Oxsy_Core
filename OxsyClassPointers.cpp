#include "OxsyLibrary.h"
#include "OxsyClassPointers.h"


COxsyClassPointers::COxsyClassPointers()
{
	m_pBasicCommands = NULL;
//	m_pCalculatePositions = NULL;
//	m_pCache = NULL;
	m_pClock = NULL;
	m_pCommandsList = NULL;
//	m_pConditions = NULL;
//	m_pCyclesInfo = NULL;
	m_pInfo = NULL;
	m_pLogger = NULL;
//	m_pMessage = NULL;
	m_pParameters = NULL;
	m_pPlay = NULL;
	m_pPlayMode = NULL;
//	m_pPositions = NULL;
	m_pScanInfo = NULL;
	m_pScoreInfo = NULL;
	m_pSensorInfo = NULL;
//	m_pSignal = NULL;
//	m_pSkills = NULL;
	m_pSocket = NULL;
	m_pSocketCommands = NULL;
//	m_pStrategyLoader = NULL;
	m_pTime = NULL;
	m_pUtility = NULL;
//	m_pWorldModel = NULL;
}


COxsyClassPointers::~COxsyClassPointers()
{

}
