#include "OxsyLibrary.h"
#include "OxsyClock.h"
#include "OxsyClassPointers.h"

#include "OxsyLogger.h"
#include "OxsyTime.h"

COxsyClock::COxsyClock(COxsyClassPointers *pClassPointers)
{
	m_pClassPointers = pClassPointers;

//	m_dCorrectionFactor = 1.0;
	m_dElapsedTime = 0.0;

	#ifdef WIN32
	m_nClockStartValue.QuadPart = 0;
	m_nClockStopValue.QuadPart = 0;
//	m_nClockFrequency.QuadPart = 0;
	QueryPerformanceFrequency(&m_nClockFrequency);
	#else // _LINUX
	m_nClockStartValue.tv_sec = 0;
	m_nClockStartValue.tv_usec = 0;
	m_nClockStopValue.tv_sec = 0;
	m_nClockStopValue.tv_usec = 0;
//	m_nClockFrequency.tv_sec = 0;
//	m_nClockFrequency.tv_usec = 0;
	gettimeofday(&m_nClockFrequency, NULL);
	#endif
}


COxsyClock::~COxsyClock()
{

}


//--------------------------------- Define variable for log -----------------------------------
	#define LOG_CLOCK_START_CLOCK
//---------------------------------------------------------------------------------------------

void COxsyClock::start_clock()
{
	#ifdef CREATE_GAME_LOG_FILE
	#ifdef LOG_CLOCK_START_CLOCK
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	#endif
	#endif

	#ifdef WIN32
//	if (QueryPerformanceFrequency(&m_nClockFrequency))
		if (QueryPerformanceCounter(&m_nClockStartValue))
		{
			#ifdef CREATE_GAME_LOG_FILE
			#ifdef LOG_CLOCK_START_CLOCK
			if (pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d ____________________ START CLOCK = %.0lf ____________________\n\n", pTime->get_time(), (double)m_nClockStartValue.QuadPart);
			#endif
			#endif
		}
	#else // _LINUX
//	if (gettimeofday(&m_nClockFrequency, NULL))
//		if (gettimeofday(&m_nClockStartValue, NULL))
//		{
			gettimeofday(&m_nClockStartValue, NULL);

			#ifdef CREATE_GAME_LOG_FILE
			#ifdef LOG_CLOCK_START_CLOCK
			if (pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d ____________________ START CLOCK = %.0lf ____________________\n\n", pTime->get_time(), (double)(m_nClockStartValue.tv_sec * 1000000 + m_nClockStartValue.tv_usec));
			#endif
			#endif
//		}
	#endif
}


//--------------------------------- Define variable for log -----------------------------------
	#define LOG_CLOCK_STOP_CLOCK
//---------------------------------------------------------------------------------------------

void COxsyClock::stop_clock()
{
	#ifdef CREATE_GAME_LOG_FILE
	#ifdef LOG_CLOCK_STOP_CLOCK
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	#endif
	#endif

	#ifdef WIN32
//	if (QueryPerformanceFrequency(&m_nClockFrequency))
		if(QueryPerformanceCounter(&m_nClockStopValue))
		{
			m_dElapsedTime = TIME_DIF_TO_MS(m_nClockStartValue, m_nClockStopValue, m_nClockFrequency);

			#ifdef CREATE_GAME_LOG_FILE
			#ifdef LOG_CLOCK_STOP_CLOCK
			if (pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d ____________________ STOP CLOCK = %.0lf ____________________\n\n", pTime->get_time(), (double)m_nClockStopValue.QuadPart);
			if (pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d ____________________ ELAPSED TIME = %lf ____________________\n\n", pTime->get_time(), m_dElapsedTime);
			#endif
			#endif
		}
	#else // _LINUX
//	if (gettimeofday(&m_nClockFrequency, NULL))
//		if (gettimeofday(&m_nClockStopValue, NULL))
//		{
			gettimeofday(&m_nClockStopValue, NULL);
			m_dElapsedTime = TIME_DIF_TO_MS(m_nClockStartValue, m_nClockStopValue); // / m_dCorrectionFactor;

			#ifdef CREATE_GAME_LOG_FILE
			#ifdef LOG_CLOCK_STOP_CLOCK
			if (pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d ____________________ STOP CLOCK = %.0lf ____________________\n\n", pTime->get_time(), (double)(m_nClockStopValue.tv_sec * 1000000 + m_nClockStopValue.tv_usec));
			if (pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d ____________________ ELAPSED TIME = %lf ____________________\n\n", pTime->get_time(), m_dElapsedTime);
			#endif
			#endif
//		}
	#endif
}


//--------------------------------- Define variable for log -----------------------------------
	#define LOG_CLOCK_GET_ELAPSED_TIME
//---------------------------------------------------------------------------------------------

double COxsyClock::get_elapsed_time()
{
	#ifdef CREATE_GAME_LOG_FILE
	#ifdef LOG_CLOCK_GET_ELAPSED_TIME
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	#endif
	#endif

	#ifdef CREATE_GAME_LOG_FILE
	#ifdef LOG_CLOCK_GET_ELAPSED_TIME
	if (pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d ____________________ ELAPSED TIME = %lf ____________________\n\n", pTime->get_time(), m_dElapsedTime);
	#endif
	#endif

	return m_dElapsedTime;
}
