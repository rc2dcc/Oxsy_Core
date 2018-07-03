#include "OxsyLibrary.h"
#include "OxsyPlay.h"
#include "OxsyClassPointers.h"

#include "OxsyCommandsList.h"
#include "OxsyClock.h"
#include "OxsyInfo.h"
#include "OxsyMain.h"
#include "OxsyParameters.h"
#include "OxsyPlayMode.h"
#include "OxsySensorInfo.h"
#include "OxsyScanInfo.h"
#include "OxsySocket.h"
#include "OxsySocketCommands.h"

#include "OxsyLogger.h"
#include "OxsyTime.h"

COxsyPlay::COxsyPlay(COxsyClassPointers *pClassPointers)
{
	m_pClassPointers = pClassPointers;
}


COxsyPlay::~COxsyPlay()
{

}


void COxsyPlay::ReceiveInformation(void) 
{
	COxsyInfo *pInfo = m_pClassPointers->GetInfoPointer();
	COxsyParameters *pParameters = m_pClassPointers->GetParametersPointer();
	COxsyPlayMode *pPlayMode = m_pClassPointers->GetPlayModePointer();
	COxsySensorInfo *pSensorInfo = m_pClassPointers->GetSensorInfoPointer();
	COxsyScanInfo *pScanInfo = m_pClassPointers->GetScanInfoPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	#endif

	SensorInfo sinfo;

	char buf[BUFFER_SIZE_MAX];

	#ifdef CREATE_GAME_LOG_FILE
	char backup_buf[BUFFER_SIZE_MAX];
	#endif

	int nTry = 0;
	int nTryMax = pParameters->get_simulation_step() / SLEEP_TIME * CYCLES;

	while(TRUE)
	{
		#ifdef WIN32
			Sleep(SLEEP_TIME); // wait for the next cycle
		#else // _LINUX
			usleep( SLEEP_TIME * 1000); // wait for the next cycle
		#endif

		nTry++;

		if (nTry > nTryMax) break;

		while (pSocketCommands->receive_message(pSocket->get_socket(), buf, BUFFER_SIZE_MAX))
		{
			#ifdef CREATE_GAME_LOG_FILE
			if (LOG_IN && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%s\n\n", buf);
			#endif

			#ifdef CREATE_GAME_LOG_FILE
			if ((LOG_IN_SEE || LOG_IN_HEAR || LOG_IN_HEAR_REFEREE || LOG_IN_HEAR_PLAYERS || LOG_IN_HEAR_PLAYERS_OUR || LOG_IN_HEAR_PLAYERS_OPP || LOG_IN_HEAR_SELF || LOG_IN_SENSE_BODY || LOG_IN_FULL_STATE || LOG_IN_SERVER) && pLogger->GetFileHandler()) strcpy(backup_buf, buf);
			#endif

			nTry = 0;

			if (!pScanInfo->scan_info(buf, &sinfo, pInfo->get_our_team_name_with_quotes())) break;

			if (sinfo.type == SIT_See)
			{
				#ifdef CREATE_GAME_LOG_FILE
				if (LOG_IN_SEE && !LOG_IN && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%s\n\n", backup_buf);
				#endif

				pSensorInfo->set_see_info(sinfo.info.see);
				pSensorInfo->set_received_see_info_this_cycle(true); // pms
			}
			else 
				if (sinfo.type == SIT_Hear)
				{
					#ifdef CREATE_GAME_LOG_FILE
					if (LOG_IN_HEAR && !LOG_IN && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%s\n\n", backup_buf);
					#endif

					if (sinfo.info.hear.sender == ST_Referee) 
					{
						#ifdef CREATE_GAME_LOG_FILE
						if (LOG_IN_HEAR_REFEREE && !LOG_IN_HEAR && !LOG_IN && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%s\n\n", backup_buf);
						#endif

						pPlayMode->analyze_play_mode(sinfo.info.hear.message, sinfo.info.hear.time);
					}
					else 
						if (sinfo.info.hear.sender == ST_Our_Player || sinfo.info.hear.sender == ST_Opp_Player)
						{
							#ifdef CREATE_GAME_LOG_FILE
							if (LOG_IN_HEAR_PLAYERS && !LOG_IN_HEAR && !LOG_IN && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%s\n\n", backup_buf);
							#endif

							if (sinfo.info.hear.sender == ST_Our_Player)
							{
								#ifdef CREATE_GAME_LOG_FILE
								if (LOG_IN_HEAR_PLAYERS_OUR && !LOG_IN_HEAR_PLAYERS && !LOG_IN_HEAR && !LOG_IN && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%s\n\n", backup_buf);
								#endif

								pSensorInfo->set_hear_info(sinfo.info.hear);
								pSensorInfo->set_received_hear_info_this_cycle(true); // pms
							}
							else
							{
								#ifdef CREATE_GAME_LOG_FILE
								if (LOG_IN_HEAR_PLAYERS_OPP && !LOG_IN_HEAR_PLAYERS && !LOG_IN_HEAR && !LOG_IN && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%s\n\n", backup_buf);
								#endif
							}
						}
						else
							if(sinfo.info.hear.sender == ST_Self)
							{
								#ifdef CREATE_GAME_LOG_FILE
								if (LOG_IN_HEAR_SELF && !LOG_IN_HEAR && !LOG_IN && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%s\n\n", backup_buf);
								#endif
							}
				}
				else
					if (sinfo.type == SIT_SenseBody)
					{
						#ifdef CREATE_GAME_LOG_FILE
						if (LOG_IN_SENSE_BODY && !LOG_IN && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%s\n\n", backup_buf);
						#endif

						pSensorInfo->set_sense_body_info(sinfo.info.senseBody);
						pSensorInfo->set_received_sensebody_info_this_cycle(true); // pms

						pTime->set_time(sinfo.info.senseBody.time);
					}
					else
						if (sinfo.type == SIT_FullState)
						{
							#ifdef CREATE_GAME_LOG_FILE
							if (LOG_IN_FULL_STATE && !LOG_IN && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%s\n\n", backup_buf);
							#endif

							pSensorInfo->set_fullstate_info(sinfo.info.fullState);
							pSensorInfo->set_received_fullstate_info_this_cycle(true); // pms
						}
						else
							if(sinfo.type == SIT_Server)
							{
								#ifdef CREATE_GAME_LOG_FILE
								if (LOG_IN_SERVER && !LOG_IN && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%s\n\n", backup_buf);
								#endif

								break;
							}
		}
	
		if (pSensorInfo->is_received_sensebody_info_this_cycle())
		{
			if (pSensorInfo->is_received_see_info_this_cycle())
			{
				pSensorInfo->set_received_hear_info_this_cycle(false);
				pSensorInfo->set_received_sensebody_info_this_cycle(false);
				pSensorInfo->set_received_see_info_this_cycle(false);
				pSensorInfo->set_received_fullstate_info_this_cycle(false);

				SetEvent(COxsyMain::m_hSCCEvent);
			}
		}
	}
}


void COxsyPlay::SimulationCycleControler()
{
	#ifdef CREATE_GAME_LOG_FILE
	COxsyClock *pClock = m_pClassPointers->GetClockPointer();
	#endif

	while(TRUE)
	{
		#ifdef WIN32
			WaitForSingleObject(COxsyMain::m_hSCCEvent, INFINITE); // wait for the new cycle
		#else // _LINUX
			COxsyMain::m_hSCCEvent.WaitEvent(); // wait for the new cycle
		#endif

		if (!COxsyMain::m_bServerIsAlive) break;

		#ifdef CREATE_GAME_LOG_FILE
		pClock->start_clock();
		#endif
		
		Play();
		
		#ifdef CREATE_GAME_LOG_FILE
		pClock->stop_clock();
		pClock->get_elapsed_time();
		#endif
	}
}


void COxsyPlay::Play()
{
	COxsyCommandsList *pCommandsList = m_pClassPointers->GetCommandsListPointer();
	COxsyInfo *pInfo = m_pClassPointers->GetInfoPointer();
	COxsySensorInfo *pSensorInfo = m_pClassPointers->GetSensorInfoPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();

	pInfo->set_speed_value(pSensorInfo->get_sensebody_info()->speed_value);
	pInfo->set_head_angle(pSensorInfo->get_sensebody_info()->head_angle);

	static int n = 0;
	printf("%d Give me commands.. head = %lf  speed = %lf Ciclul = %d\n", pTime->get_time(), pInfo->get_head_angle(), pInfo->get_speed_value(), n);

	if (n == 0) pCommandsList->Move(-0.4, 0.0);
	if (n == 100) pCommandsList->Kick(100.0, 0.0);
	if (n > 100 && n < 120) pCommandsList->Dash(100.0);
	if (n >= 120)
	{
		if (n % 5)
		{
			pCommandsList->Dash(100.0);
		}
		else
		{
			pCommandsList->Turn(30.0);
		}
	}

	n++;
}
