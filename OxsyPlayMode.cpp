#include "OxsyLibrary.h"
#include "OxsyPlayMode.h"
#include "OxsyClassPointers.h"

#include "OxsyInfo.h"
#include "OxsyScoreInfo.h"
#include "OxsyStatics.h"


COxsyPlayMode::COxsyPlayMode(COxsyClassPointers *pClassPointers)
{
	m_pClassPointers = pClassPointers;

	m_PlayModeInfo.play_mode_time = 0;
	m_PlayModeInfo.play_mode = PM_before_kick_off;
}


COxsyPlayMode::~COxsyPlayMode()
{
	m_PlayModeInfoArray.clear();
}


void COxsyPlayMode::analyze_play_mode(char *strRefereeMessage, int nRefereeMessageTime) 
{
	COxsyInfo *pInfo = m_pClassPointers->GetInfoPointer();
	COxsyScoreInfo *pScoreInfo = m_pClassPointers->GetScoreInfoPointer();
	ScoreInfo scoreInfo;
	
	m_PlayModeInfo.play_mode_time = nRefereeMessageTime;
	m_PlayModeInfo.play_mode = get_play_mode(strRefereeMessage);

	if (m_PlayModeInfo.play_mode == PM_Unknown) 
	{
		if (strlen(strRefereeMessage) > 5 && !strncmp(strRefereeMessage, "goal_", 5)) 
		{
			if (strRefereeMessage[5] == 'l') 
			{
				m_PlayModeInfo.play_mode = PM_goal_l;

				scoreInfo = pScoreInfo->get_score_info();

				if (pInfo->get_init_side() == S_Left)
				{
					scoreInfo.our_score_time = nRefereeMessageTime;
					scoreInfo.our_score = atoi(strRefereeMessage + 7);
				}
				else
				{
					scoreInfo.opp_score_time = nRefereeMessageTime;
					scoreInfo.opp_score = atoi(strRefereeMessage + 7);
				}

				pScoreInfo->set_score_info(scoreInfo);
			} 
			else
				if (strRefereeMessage[5] == 'r') 
				{
					m_PlayModeInfo.play_mode = PM_goal_r;
					scoreInfo = pScoreInfo->get_score_info();

					if (pInfo->get_init_side() == S_Right)
					{
						scoreInfo.our_score_time = nRefereeMessageTime;
						scoreInfo.our_score = atoi(strRefereeMessage + 7);
					}
					else
					{
						scoreInfo.opp_score_time = nRefereeMessageTime;
						scoreInfo.opp_score = atoi(strRefereeMessage + 7);
					}

					pScoreInfo->set_score_info(scoreInfo);
				}
		}
	}
	else 
		if (m_PlayModeInfo.play_mode == PM_before_kick_off) 
		{
			pInfo->init_player_state();
			pInfo->inc_match_state();
		}

	if (m_PlayModeInfoArray.size() > 0)
	{
		if (m_PlayModeInfoArray[0].play_mode_time != m_PlayModeInfo.play_mode_time)
		{
			m_PlayModeInfoArray.clear();
		}
	}

	m_PlayModeInfoArray.push_back(m_PlayModeInfo);
}


PlayMode COxsyPlayMode::get_play_mode(char *strPlayMode)
{
	int i;

	for (i = 0; COxsyStatics::playModeTable[i].strPlayMode != NULL; i++) 
	{
		if (!strcmp(strPlayMode, COxsyStatics::playModeTable[i].strPlayMode))
		{
			return COxsyStatics::playModeTable[i].playMode;
		}
	}

	return PM_Unknown;
}
