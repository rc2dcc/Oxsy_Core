#include "OxsyLibrary.h"
#include "OxsyScanInfo.h"
#include "OxsyClassPointers.h"

#include "OxsyInfo.h"
#include "OxsyParameters.h"
#include "OxsyPlayMode.h"
#include "OxsyScoreInfo.h"
#include "OxsyStatics.h"
#include "OxsyTime.h"
//#include "OxsyWorldModel.h"

#include "OxsyLogger.h"


COxsyScanInfo::COxsyScanInfo(COxsyClassPointers *pClassPointers)
{
	m_pClassPointers  = pClassPointers;
}


COxsyScanInfo::~COxsyScanInfo()
{

}


char *COxsyScanInfo::next_token(char *buf, char *separators)
{
	int i, quotes;

	quotes = 0;

	while (true) 
	{
		if (*buf == '\0')
		{
			return (char *)NULL;
		}

		if (*buf == '"')
		{
			if (*(buf - 1) == '\\')
			{
				if ((quotes % 2))
				{
					buf++;
					continue;
				}
			}

			quotes++;
			buf++;
			continue;
		}

		if ((quotes % 2))
		{
			buf++;
			continue;
		}

		for(i = 0; i < (int)strlen(separators); i++)
		{
			if (*buf == separators[i])
			{
				*buf = '\0';
				buf++;
				return buf;
			}
		}

		buf++;
	}
}


char *COxsyScanInfo::next_token(char *buf)
{
	int i = 0;

	while (true) 
	{
		if (*buf == '(')
		{
			i++;
		}
		else 
			if (*buf == ')') 
			{
				if (i == 0) 
				{
					*buf = '\0';
					return (char *)NULL;
				}

				i--;
			}
			else 
				if (*buf == ' ' && i == 0)
				{
					break;
				}
				else 
					if (*buf == '\0')
					{
						return (char *)NULL;
					}
		buf++ ;
	}

	*buf = '\0';
	buf++;

	return buf;
}


bool COxsyScanInfo::scan_info(char *buffer, SensorInfo *sinfo, char *teamname)
{
	char com[BUFFER_SIZE_MAX / 128];
	
	sscanf(buffer, "(%s ", com);
	
	if (!strcmp(com, "see"))
	{
		sinfo->type = SIT_See;
		return scan_visual_info(buffer, &(sinfo->info.see), teamname);
	}
	else
		if (!strcmp(com, "hear"))
		{
			sinfo->type = SIT_Hear;
			return scan_auditorial_info(buffer, &(sinfo->info.hear));
		}
		else
			if (!strcmp(com, "sense_body"))
			{
				sinfo->type = SIT_SenseBody;
				return scan_sensebody_info(buffer, &(sinfo->info.senseBody));
			}
			else
				if (!strcmp(com, "fullstate"))
				{
					sinfo->type = SIT_FullState;
					return scan_fullstate_info(buffer, &(sinfo->info.fullState));
				}
				else
					if (!strcmp(com, "score"))
					{
						sinfo->type = SIT_Server;
						return scan_score_info(buffer);
					}
					else
						if(!strcmp(com, "change_player_type"))
						{
							sinfo->type = SIT_Server;
							return scan_change_player_type_info(buffer);
						}

	return false;
}

void COxsyScanInfo::rescan_visual_info(SeeInfo *sinfo)
{
	COxsyInfo *pInfo = m_pClassPointers->GetInfoPointer();
//	COxsyWorldModel *pWorldModel = m_pClassPointers->GetWorldModelPointer();

//	WorldModel *wm = pWorldModel->get_world_model();

	int i, j;
	int our_index, opp_index, index;
	int start_index = -1, stop_index = -1;
	int our_range_begin = 1, opp_range_begin = 1;
	int our_range_end = TEAM_PLAYERS_MAX, opp_range_end = TEAM_PLAYERS_MAX;
//	int nOurPlayers = 0, nOpponentPlayers = 0, nUnknownPlayers = 0;

	static Side init_side = pInfo->get_init_side();
	static int unum = pInfo->get_unum();

//////////////////// Find start and stop index for players in sinfo structure //////////////

	for(i = 0; i < sinfo->n_obj; i++)
	{
		if (sinfo->obj[i].type == OT_Player)
		{
			start_index = i;
			break;
		}
	}

	if (start_index == -1) return;

	for(i = sinfo->n_obj - 1; i >= 0; i--)
	{
		if (sinfo->obj[i].type == OT_Player)
		{
			stop_index = i;
			break;
		}
	}
	
	if (stop_index == -1) return;

////////////////////////////////////// Set OUR and OPPONENT index /////////////////////////////

	if (init_side == S_Left)
	{
		our_index = start_index;
		opp_index = stop_index;

		if (stop_index - start_index >= TEAM_PLAYERS_MAX)
		{
			our_index = stop_index - TEAM_PLAYERS_MAX + 1;

			for (i = start_index; i <= stop_index - TEAM_PLAYERS_MAX; i++) 
			{
				sinfo->obj[i].id.player.team = WT_Our;
			}
		}

		if(stop_index - start_index >= TEAM_PLAYERS_MAX - 1)
		{
			opp_index = start_index + TEAM_PLAYERS_MAX - 2;

			for (i = stop_index; i >= start_index + TEAM_PLAYERS_MAX - 1; i--) 
			{
				sinfo->obj[i].id.player.team = WT_Opponent;
			}
		}
	}
	else
	{
		our_index = stop_index;
		opp_index = start_index;

		if (stop_index - start_index >= TEAM_PLAYERS_MAX)
		{
			our_index = start_index + TEAM_PLAYERS_MAX - 1;

			for (i = stop_index; i >= start_index + TEAM_PLAYERS_MAX; i--) 
			{
				sinfo->obj[i].id.player.team = WT_Our;
			}
		}

		if(stop_index - start_index >= TEAM_PLAYERS_MAX - 1)
		{
			opp_index = stop_index - TEAM_PLAYERS_MAX + 2;

			for (i = start_index; i <= stop_index - TEAM_PLAYERS_MAX + 1; i++)
			{
				sinfo->obj[i].id.player.team = WT_Opponent;
			}
		}
	}

//////////////////////////////////////// Set teams ////////////////////////////////////////////

	for(i = start_index; i <= stop_index; i++)
	{
		switch(sinfo->obj[i].id.player.team)
		{
			case WT_Our:

//				nOurPlayers++;

				if (sinfo->obj[i].id.player.unum != UNKNOWN_NUMBER) our_range_begin = sinfo->obj[i].id.player.unum;
				else if (our_range_begin == unum) our_range_begin++;
				sinfo->obj[i].our_range.begin = our_range_begin;

				switch(init_side)
				{
					case S_Left:
/*
						if (nUnknownPlayers > 0)
						{
							nOurPlayers += nUnknownPlayers;
							nUnknownPlayers = 0;
						}
*/
						if (our_index < i)
						{
							for (j = our_index; j < i; j++) sinfo->obj[j].id.player.team = WT_Our;
						}

						our_index = i + 1;

						if (sinfo->obj[i].id.player.unum != UNKNOWN_NUMBER)
						{
							index = i + TEAM_PLAYERS_MAX - our_range_begin;
							index += (our_range_begin < unum) ? 0 : 1;

							if (opp_index >= index)
							{
								for (j = opp_index; j >= index; j--)
								{
									sinfo->obj[j].id.player.team = WT_Opponent;
								}

								opp_index = index - 1;
							}
						}

						break;

					case S_Right:

						if (our_index > i)
						{
							for (j = our_index; j > i; j--) sinfo->obj[j].id.player.team = WT_Our;
						}

						if (our_index >= i)
						{
							our_index = i - 1;
						}

						if (sinfo->obj[i].id.player.unum != UNKNOWN_NUMBER)
						{
							index = i - our_range_begin;

							if (opp_index <= index)
							{
								for (j = opp_index; j <= index; j++)
								{
									sinfo->obj[j].id.player.team = WT_Opponent;
								}
	
								opp_index = index + 1;
							}
						}

						break;

					case S_Unknown:
						break;

					default:
						break;
				}

				our_range_begin++;

				break;

			case WT_Opponent:

//				nOpponentPlayers++;

				if (sinfo->obj[i].id.player.unum != UNKNOWN_NUMBER) opp_range_begin = sinfo->obj[i].id.player.unum;
				sinfo->obj[i].opp_range.begin = opp_range_begin;

				switch(init_side)
				{
					case S_Left:

						if (opp_index > i)
						{
							for (j = opp_index; j > i; j--) sinfo->obj[j].id.player.team = WT_Opponent;
						}

						if (opp_index >= i)
						{
							opp_index = i - 1;
						}

						if (sinfo->obj[i].id.player.unum != UNKNOWN_NUMBER)
						{
							index = i - opp_range_begin;

							if (our_index <= index)
							{
								for (j = our_index; j <= index; j++)
								{
									sinfo->obj[j].id.player.team = WT_Our;
								}
	
								our_index = index + 1;
							}
						}

						break;

					case S_Right:
/*
						if(nUnknownPlayers > 0)
						{
							nOpponentPlayers += nUnknownPlayers;
							nUnknownPlayers = 0;
						}
*/
						if (opp_index < i)
						{
							for (j = opp_index; j < i; j++) sinfo->obj[j].id.player.team = WT_Opponent;
						}

						opp_index = i + 1;

						if (sinfo->obj[i].id.player.unum != UNKNOWN_NUMBER)
						{
							index = i + TEAM_PLAYERS_MAX - opp_range_begin + 1;

							if (our_index >= index)
							{
								for (j = our_index; j >= index; j--)
								{
									sinfo->obj[j].id.player.team = WT_Our;
								}

								our_index = index - 1;
							}
						}

						break;

					case S_Unknown:
						break;

					default:
						break;
				}

				opp_range_begin++;

				break;

			case WT_Unknown:

//				nUnknownPlayers++;

				if (our_range_begin == unum) our_range_begin++;
				sinfo->obj[i].our_range.begin = our_range_begin;
				sinfo->obj[i].opp_range.begin = opp_range_begin;

				switch(init_side)
				{
					case S_Left:
						our_range_begin++;
						break;
					case S_Right:
						opp_range_begin++;
						break;
					case S_Unknown:
						break;
					default:
						break;
				}

				break;

			default:
				break;			
		}
	}

//////////////////////////////////////// Set numbers //////////////////////////////////////////

	for(i = stop_index; i >= start_index; i--)
	{
		switch(sinfo->obj[i].id.player.team)
		{
			case WT_Our:

				if (sinfo->obj[i].id.player.unum != UNKNOWN_NUMBER) our_range_end = sinfo->obj[i].id.player.unum;
				else if (our_range_end == unum) our_range_end--;
				sinfo->obj[i].our_range.end = our_range_end;

				if (sinfo->obj[i].id.player.unum == UNKNOWN_NUMBER)
				{
					if(sinfo->obj[i].our_range.begin == our_range_end)
					{
						sinfo->obj[i].id.player.unum = our_range_end;

//						if (wm->tmate[sinfo->obj[i].id.player.unum - 1].type_time != UNKNOWN_TIME)
//						{
//							sinfo->obj[i].id.player.type = wm->tmate[sinfo->obj[i].id.player.unum - 1].type;
//						}
					}
				}

				our_range_end--;

				break;

			case WT_Opponent:

				if (sinfo->obj[i].id.player.unum != UNKNOWN_NUMBER) opp_range_end = sinfo->obj[i].id.player.unum;
				sinfo->obj[i].opp_range.end = opp_range_end;

				if (sinfo->obj[i].id.player.unum == UNKNOWN_NUMBER)
				{
					if(sinfo->obj[i].opp_range.begin == opp_range_end)
					{
						sinfo->obj[i].id.player.unum = opp_range_end;

//						if (wm->opp[sinfo->obj[i].id.player.unum - 1].type_time != UNKNOWN_TIME)
//						{
//							sinfo->obj[i].id.player.type = wm->opp[sinfo->obj[i].id.player.unum - 1].type;
//						}
					}
				}

				opp_range_end--;

				break;

			case WT_Unknown:

				if (our_range_end == unum) our_range_end--;
				sinfo->obj[i].our_range.end = our_range_end;
				sinfo->obj[i].opp_range.end = opp_range_end;

				switch(init_side)
				{
					case S_Left:
						opp_range_end--;
						break;
					case S_Right:
						our_range_end--;
						break;
					case S_Unknown:
						break;
					default:
						break;
				}

				break;

			default:
				break;
		}
	}

/*
	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();

	for(i = start_index; i <= stop_index; i++)
	{
		if(sinfo->obj[i].id.player.team == WT_Our)
		{
			if (LOG_IN_SEE && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "WT_Our  Our range begin = %d  Our range end = %d\n", sinfo->obj[i].our_range.begin, sinfo->obj[i].our_range.end);
		}
		else
			if(sinfo->obj[i].id.player.team == WT_Opponent)
			{
				if (LOG_IN_SEE && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "WT_Opponent  Opp range begin = %d  Opp range end = %d\n", sinfo->obj[i].opp_range.begin, sinfo->obj[i].opp_range.end);
			}
			else
				if(sinfo->obj[i].id.player.team == WT_Unknown)
				{
					if (LOG_IN_SEE && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "WT_Unknown  Our range begin = %d  Our range end = %d  Opp range begin = %d  Opp range end = %d\n", sinfo->obj[i].our_range.begin, sinfo->obj[i].our_range.end, sinfo->obj[i].opp_range.begin, sinfo->obj[i].opp_range.end);
				}
	}

	#endif
*/
}


bool COxsyScanInfo::scan_visual_info(char *buffer, SeeInfo *sinfo, char *teamname)
{
	COxsyInfo *pInfo = m_pClassPointers->GetInfoPointer();
//	COxsyParameters *pParameters = m_pClassPointers->GetParametersPointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
//	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	#endif

//	ViewWidth viewWidthWithSeeInfo;
	bool bIsTackling;
	char *next, *obj, *param, *tmp;
	double p[7], min_dir = 0.0, max_dir = 0.0;
	int num = 0, num_param = 0;
	
	sscanf(buffer, "(see %d ", &(sinfo->time));
	buffer = next_token(buffer + 1);
	if(buffer != NULL) buffer = next_token(buffer);
	
	while(buffer != NULL) 
	{
		next = next_token(buffer++);
		param = next_token(buffer++);
		
		bIsTackling = false;
		num_param = 0;

		while (param != NULL) 
		{
			tmp = param;
			param = next_token(tmp);
			if (strcmp(tmp, "t") == 0)
			{
				bIsTackling = true;
			}
			else
			{
				p[num_param] = atof(tmp);
				num_param++;
			}
		}
		
		if (num_param == 1)
		{
			sinfo->obj[num].dist = UNKNOWN_DISTANCE;
			sinfo->obj[num].dir = p[0];// + ((p[0] >= 0.0) ? 0.5 : -0.5);
			sinfo->obj[num].dist_chng = UNKNOWN_DISTANCE_CHANGE;
			sinfo->obj[num].dir_chng = UNKNOWN_DIRECTION_CHANGE;
			sinfo->obj[num].body_dir = UNKNOWN_BODY_DIRECTION;
			sinfo->obj[num].head_dir = UNKNOWN_HEAD_DIRECTION;
			sinfo->obj[num].pointto_dir = UNKNOWN_POINTTO_DIRECTION;
			sinfo->obj[num].bIsTackling = bIsTackling;
		} 
		else 
			if (num_param == 2)
			{
				sinfo->obj[num].dist = p[0];
				sinfo->obj[num].dir = p[1];// + ((p[1] >= 0.0) ? 0.5 : -0.5);
				sinfo->obj[num].dist_chng = UNKNOWN_DISTANCE_CHANGE;
				sinfo->obj[num].dir_chng = UNKNOWN_DIRECTION_CHANGE;
				sinfo->obj[num].body_dir = UNKNOWN_BODY_DIRECTION;
				sinfo->obj[num].head_dir = UNKNOWN_HEAD_DIRECTION;
				sinfo->obj[num].pointto_dir = UNKNOWN_POINTTO_DIRECTION;
				sinfo->obj[num].bIsTackling = bIsTackling;
			} 
			else
				if (num_param == 3)
				{
					sinfo->obj[num].dist = p[0];
					sinfo->obj[num].dir = p[1];// + ((p[1] >= 0.0) ? 0.5 : -0.5);
					sinfo->obj[num].dist_chng = UNKNOWN_DISTANCE_CHANGE;
					sinfo->obj[num].dir_chng = UNKNOWN_DIRECTION_CHANGE;
					sinfo->obj[num].body_dir = UNKNOWN_BODY_DIRECTION;
					sinfo->obj[num].head_dir = UNKNOWN_HEAD_DIRECTION;
					sinfo->obj[num].pointto_dir = p[2];
					sinfo->obj[num].bIsTackling = bIsTackling;
				}
				else
					if (num_param == 4)
					{
						sinfo->obj[num].dist = p[0];
						sinfo->obj[num].dir = p[1];// + ((p[1] >= 0.0) ? 0.5 : -0.5);
						sinfo->obj[num].dist_chng = p[2];
						sinfo->obj[num].dir_chng = p[3];
						sinfo->obj[num].body_dir = UNKNOWN_BODY_DIRECTION;
						sinfo->obj[num].head_dir = UNKNOWN_HEAD_DIRECTION;
						sinfo->obj[num].pointto_dir = UNKNOWN_POINTTO_DIRECTION;
						sinfo->obj[num].bIsTackling = bIsTackling;
					} 
					else 
						if (num_param == 6) 
						{
							sinfo->obj[num].dist = p[0];
							sinfo->obj[num].dir = p[1];// + ((p[1] >= 0.0) ? 0.5 : -0.5);
							sinfo->obj[num].dist_chng = p[2];
							sinfo->obj[num].dir_chng = p[3];
							sinfo->obj[num].body_dir = p[4];// + ((p[4] >= 0.0) ? 0.5 : -0.5);
							sinfo->obj[num].head_dir = p[5];// + ((p[5] >= 0.0) ? 0.5 : -0.5);
							sinfo->obj[num].pointto_dir = UNKNOWN_POINTTO_DIRECTION;
							sinfo->obj[num].bIsTackling = bIsTackling;
						} 
						else 
							if (num_param == 7) 
							{
								sinfo->obj[num].dist = p[0];
								sinfo->obj[num].dir = p[1];// + ((p[1] >= 0.0) ? 0.5 : -0.5);
								sinfo->obj[num].dist_chng = p[2];
								sinfo->obj[num].dir_chng = p[3];
								sinfo->obj[num].body_dir = p[4];// + ((p[4] >= 0.0) ? 0.5 : -0.5);
								sinfo->obj[num].head_dir = p[5];// + ((p[5] >= 0.0) ? 0.5 : -0.5);
								sinfo->obj[num].pointto_dir = p[6];
								sinfo->obj[num].bIsTackling = bIsTackling;
							} 
							else 
							{
								#ifdef CREATE_GAME_LOG_FILE
								if (LOG_IN && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "scan_visual_info: parse error\n");
								#endif

								return false;
							}
		
		obj = next_token(buffer);
		
		if (strcmp(buffer, "b") == 0) 
		{
			// pms : din studiul metodei de quantificare a distantelor pana la obiectele
			// mobile (minge, jucatori) 0.9 (primit) => 0.8 (real)
//			if (sinfo->obj[num].dist == 0.9) sinfo->obj[num].dist = 0.8;

			sinfo->obj[num].type = OT_Ball;
			sinfo->obj[num].viewCone = VC_In;
		}
		else 
			if(strcmp(buffer, "B") == 0) 
			{
				// pms : din studiul metodei de quantificare a distantelor pana la obiectele
				// mobile (minge, jucatori) 0.9 (primit) => 0.8 (real)
//				if (sinfo->obj[num].dist == 0.9) sinfo->obj[num].dist = 0.8;

				sinfo->obj[num].type = OT_Ball;
				sinfo->obj[num].viewCone = VC_Out;
			}
			else 
				if(strcmp(buffer, "p") == 0)
				{
					// pms : din studiul metodei de quantificare a distantelor pana la
					// obiectele mobile (minge, jucatori) 0.9 (primit) => 0.8 (real)
//					if (sinfo->obj[num].dist == 0.9) sinfo->obj[num].dist = 0.8;

					sinfo->obj[num].type = OT_Player;
					sinfo->obj[num].viewCone = VC_In;
					sinfo->obj[num].id.player.team = WT_Unknown;
					sinfo->obj[num].id.player.unum = UNKNOWN_NUMBER;
					sinfo->obj[num].id.player.type = PT_Unknown;
					//////////////////// Range /////////////////////
					sinfo->obj[num].our_range.begin = 1;
					sinfo->obj[num].our_range.end = TEAM_PLAYERS_MAX;
					sinfo->obj[num].opp_range.begin = 1;
					sinfo->obj[num].opp_range.end = TEAM_PLAYERS_MAX;
					////////////////////////////////////////////////

					if (obj != NULL) 
					{
						buffer = obj;
						obj = next_token(buffer);
					
						if (strcmp(buffer, teamname) == 0)
						{
							sinfo->obj[num].id.player.team = WT_Our;
						}
						else
						{
							sinfo->obj[num].id.player.team = WT_Opponent;

							if (strcmp(pInfo->get_opp_team_name(), DEFAULT_OPPONENT_TEAM_NAME) == 0)
							{
								char opp_team_name[TEAM_NAME_LENGTH_MAX + 1];
								strncpy(opp_team_name, (buffer + 1), strlen(buffer) - 2);
								opp_team_name[strlen(buffer) - 2]= '\0';
								pInfo->set_opp_team_name(opp_team_name);
							}
						}
								
						if (obj != NULL) 
						{
							buffer = obj;
							obj = next_token(buffer);
							sinfo->obj[num].id.player.unum = atoi(buffer);
						}

						// pms
						if (obj != NULL)
						{
							(void)next_token(obj);
							if (strcmp(obj, GOALIE_NAME) == 0)
							{
								sinfo->obj[num].id.player.type = PT_Goalie;
							}
						}
					}
				}
				else 
					if(strcmp(buffer, "P") == 0)
					{
						// pms : din studiul metodei de quantificare a distantelor pana la
						// obiectele mobile (minge, jucatori) 0.9 (primit) => 0.8 (real)
//						if (sinfo->obj[num].dist == 0.9) sinfo->obj[num].dist = 0.8;

						sinfo->obj[num].type = OT_Player;
						sinfo->obj[num].viewCone = VC_Out;
						sinfo->obj[num].id.player.team = WT_Unknown;
						sinfo->obj[num].id.player.unum = UNKNOWN_NUMBER;
						sinfo->obj[num].id.player.type = PT_Unknown;
						//////////////////// Range /////////////////////
						sinfo->obj[num].our_range.begin = 1;
						sinfo->obj[num].our_range.end = TEAM_PLAYERS_MAX;
						sinfo->obj[num].opp_range.begin = 1;
						sinfo->obj[num].opp_range.end = TEAM_PLAYERS_MAX;
						////////////////////////////////////////////////
					}
					else 
						if(strcmp(buffer, "g") == 0)
						{
							sinfo->obj[num].type = OT_Goal;
							sinfo->obj[num].viewCone = VC_In;
							sinfo->obj[num].id.side = S_Unknown;

							if (obj != NULL) 
							{
								buffer = obj;
								if (*buffer == 'l')
								{
									sinfo->obj[num].id.side = S_Left;
								}
								else 
									if (*buffer == 'r')
									{
										sinfo->obj[num].id.side = S_Right;
									}
							}
						}
						else 
							if(strcmp(buffer, "G") == 0)
							{
								sinfo->obj[num].type = OT_Goal;
								sinfo->obj[num].viewCone = VC_Out;
								sinfo->obj[num].id.side = S_Unknown;
							}
							else 
								if(strcmp(buffer, "f") == 0)
								{
									sinfo->obj[num].type = OT_Flag;
									sinfo->obj[num].viewCone = VC_In;
									sinfo->obj[num].id.flagType = FT_Unknown;

									if (obj != NULL) 
									{
										unsigned int nFlagNameLength;
										int i;

										buffer = obj;

										for (nFlagNameLength = 0; buffer[nFlagNameLength] != ')'; nFlagNameLength++);

										for (i = 0; i < FT_Max - 1; i++)
										{
											if (nFlagNameLength == strlen(COxsyStatics::flagTable[i].strFlagType))
											{
												if(strncmp(buffer, COxsyStatics::flagTable[i].strFlagType, nFlagNameLength) == 0)
												{
													sinfo->obj[num].id.flagType = COxsyStatics::flagTable[i].flagType;
													break;
												}
											}
										}
									}
								}
								else 
									if(strcmp(buffer, "F") == 0) 
									{
										sinfo->obj[num].type = OT_Flag;
										sinfo->obj[num].viewCone = VC_Out;
										sinfo->obj[num].id.flagType = FT_Unknown;
									}
									else 
										if(strcmp(buffer, "l") == 0) 
										{
											sinfo->obj[num].type = OT_Line;
											sinfo->obj[num].viewCone = VC_In;
											sinfo->obj[num].id.lineType = LT_Unknown;

											if (obj != NULL) 
											{
												buffer = obj;
												if (*buffer == 'l')
												{
													sinfo->obj[num].id.lineType = LT_L;
												}
												else 
													if (*buffer == 't')
													{
														sinfo->obj[num].id.lineType = LT_T;
													}
													else 
														if (*buffer == 'b')
														{
															sinfo->obj[num].id.lineType = LT_B;
														}
														else 
															if (*buffer == 'r')
															{
																sinfo->obj[num].id.lineType = LT_R;
															}
											}
										}
										else 
											if(strcmp(buffer, "L") == 0) 
											{
												sinfo->obj[num].type = OT_Line;
												sinfo->obj[num].viewCone = VC_Out;
												sinfo->obj[num].id.lineType = LT_Unknown;
											}
											else 
												{
													#ifdef CREATE_GAME_LOG_FILE
													if (LOG_IN && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "scan_visual_info: miss obj\n");
													#endif

													return false;
												}

		// incercam sa identificam View Width-ul jucatorului dupa unghiurile obiectelor vazute
		if (sinfo->obj[num].viewCone == VC_In)
		{
			if (sinfo->obj[num].type != OT_Line)
			{
				if (sinfo->obj[num].dir > max_dir) max_dir = sinfo->obj[num].dir;
				else
					if(sinfo->obj[num].dir < min_dir) min_dir = sinfo->obj[num].dir;
			}
		}

		buffer = next;
		num++;
	}

	sinfo->n_obj = num;

//	rescan_visual_info(sinfo); // PMS: ATENTIE aceasta functie se apeleaza
							   // numai in cazul in care ordinea jucatorilor in informatia
							   // vizuala ramine neschimbata. (adica jucatorii vazuti sunt
							   // tranmisi in ordinea numerelor de pe tricou incepand cu echipa
							   // care s-a conectat prima (care a inceput jocul in partea 
							   // stinga a terenului)).


	// seteaza View_Width-ul cu care s-au receptzionat informatzile vizuale
//	if (max_dir > (pParameters->get_visible_angle() / 2.0 + SECURE_DIR) || min_dir < -(pParameters->get_visible_angle() / 2.0 + SECURE_DIR))
//	{
//		viewWidthWithSeeInfo = VW_Wide;
//	}
//	else
//		if (max_dir > (pParameters->get_visible_angle() / 4.0 + SECURE_DIR) || min_dir < -(pParameters->get_visible_angle() / 4.0 + SECURE_DIR))
//		{
//			viewWidthWithSeeInfo = VW_Normal;
//		}
//		else
//			{
//				viewWidthWithSeeInfo = VW_Narrow;
//			}

	// salveaza View_Width-ul cu care s-au receptzionat informatzile vizuale
//	pInfo->set_view_width_with_see_info(viewWidthWithSeeInfo);


//	#ifdef CREATE_GAME_LOG_FILE
//	if (LOG_IN_SEE && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d COxsyScanInfo::scan_visual_info : Max_Dir = %lf Min_Dir = %lf ViewWidth = %d\n", pTime->get_time(), max_dir, min_dir, viewWidthWithSeeInfo);
//	#endif


	return true;
}


// message from players
// (hear time direction TEAM [UNUM] "message") 
// (hear time TEAM [UNUM])
bool COxsyScanInfo::scan_auditorial_info(char *buffer, HearInfo *hinfo)
{
	char *param[4];
	int nParam, wParam;
	bool bMessage;

	wParam = 0;
	nParam = 0;
	bMessage = false;
	hinfo->time = UNKNOWN_TIME;
	hinfo->direction = UNKNOWN_DIRECTION;
	hinfo->sender = ST_Unknown;
	hinfo->unum = UNKNOWN_NUMBER;
	strcpy(hinfo->message, "");
	
	sscanf(buffer, "(hear %d", &(hinfo->time));
	buffer++;
	buffer = next_token(buffer);

	param[nParam] = next_token(buffer);

	while (param[nParam])
	{
		nParam++;
		if (param[nParam - 1][0] == '\"') break;
		param[nParam] = next_token(param[nParam - 1]);
	}

	switch(nParam)
	{
		case 1:

			hinfo->sender = GetSender(param[0]); // ST_Opp_Player
			break;

		case 2:

			hinfo->sender = GetSender(param[0]);
			switch(hinfo->sender)
			{
				case ST_Our_Player:
					hinfo->unum = atoi(param[1]);
					break;
				case ST_Opp_Player:
					// nu exista acest caz
					break;
				case ST_Self:
					wParam = 1;
					bMessage = true;
					break;
				case ST_Referee:
					wParam = 1;
					bMessage = true;
					break;
				default:
					return false;
					break;
			}

			break;

		case 3:

			hinfo->direction = atof(param[0]);
			hinfo->sender = GetSender(param[1]); // ST_Opp_Player
			wParam = 2;
			bMessage = true;
			break;

		case 4:

			hinfo->direction = atof(param[0]);
			hinfo->sender = GetSender(param[1]); // ST_Our_Player
			hinfo->unum = atoi(param[2]);
			wParam = 3;
			bMessage = true;
			break;

		default:

			return false;
			break;
	}

	if (bMessage)
	{
		if (hinfo->sender == ST_Referee)
		{
			strcpy(hinfo->message, param[wParam]);
		}
		else
		{
			strncpy(hinfo->message, (param[wParam] + 1), strlen(param[wParam]) - 3);
			hinfo->message[strlen(param[wParam]) - 3] = '\0';
		}
	}

	return true;
}


bool COxsyScanInfo::scan_sensebody_info(char *buffer, SenseBodyInfo *sbinfo) 
{
	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	#endif

	char *next, *param, *nparam;
	
	sscanf(buffer, "(sense_body %d ", &(sbinfo->time));
	buffer = next_token(buffer + 1);
	buffer = next_token(buffer);

	while(buffer != NULL) 
	{
		next = next_token(buffer);
		param = next_token(++buffer);
		
		if (!strcmp(buffer,"view_mode")) 
		{
			nparam = next_token(param) ;
			if(!strcmp(param,"high")) 
			{
				sbinfo->viewQuality = VQ_High ;
			} 
			else 
				if(!strcmp(param,"low")) 
				{
					sbinfo->viewQuality = VQ_Low ;
				}
				else
					{
						#ifdef CREATE_GAME_LOG_FILE
						if (LOG_IN && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "Illegal view quality mode\n");
						#endif

						return false;						
					}

			if(!strcmp(nparam,"wide)")) 
			{
				sbinfo->viewWidth = VW_Wide ;
			} 
			else 
				if(!strcmp(nparam,"normal)")) 
				{
					sbinfo->viewWidth = VW_Normal ;
				} 
				else 
					if(!strcmp(nparam,"narrow)")) 
					{
						sbinfo->viewWidth = VW_Narrow ;
					}
					else
						{
							#ifdef CREATE_GAME_LOG_FILE
							if (LOG_IN && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "Illegal view width mode\n");
							#endif

							return false;						
						}
		} 
		else 
			if (!strcmp(buffer,"stamina")) 
			{
				sscanf(param,"%lf %lf)",&sbinfo->stamina, &sbinfo->effort);
			} 
			else 
				if (!strcmp(buffer,"speed")) 
				{
					sscanf(param,"%lf %lf",&sbinfo->speed_value, &sbinfo->speed_dir);
				} 
				else 
					if (!strcmp(buffer,"head_angle")) 
					{
						sscanf(param,"%lf",&sbinfo->head_angle);
					} 
					else 
						if (!strcmp(buffer,"kick")) 
						{
							sscanf(param,"%d",&sbinfo->commandsCounter.kickCounter);
						} 
						else 
							if (!strcmp(buffer,"dash")) 
							{
								sscanf(param,"%d",&sbinfo->commandsCounter.dashCounter);
							} 
							else 
								if (!strcmp(buffer,"turn")) 
								{
									sscanf(param,"%d",&sbinfo->commandsCounter.turnCounter);
								} 
								else 
									if (!strcmp(buffer,"say")) 
									{
										sscanf(param,"%d",&sbinfo->commandsCounter.sayCounter);
									} 
									else 
										if (!strcmp(buffer,"turn_neck")) 
										{
											sscanf(param,"%d",&sbinfo->commandsCounter.turnNeckCounter);
										} 
										else 
											if (!strcmp(buffer,"catch")) 
											{
												sscanf(param,"%d",&sbinfo->commandsCounter.catchCounter);
											} 
											else 
												if (!strcmp(buffer,"move")) 
												{
													sscanf(param,"%d",&sbinfo->commandsCounter.moveCounter);
												} 
												else 
													if (!strcmp(buffer,"change_view")) 
													{
														sscanf(param,"%d",&sbinfo->commandsCounter.changeViewCounter);
													} 
													else 
														if (!strcmp(buffer,"arm"))
														{
															sscanf(param,"(movable %d) (expires %d) (target %lf %lf) (count %d)", &sbinfo->armInfo.movable,
															&sbinfo->armInfo.expires, &sbinfo->armInfo.dist, &sbinfo->armInfo.dir, &sbinfo->commandsCounter.pointToCounter);

															///////////// PMS: ATENTIE - Directia inspre care pointeaza bratul este  //////
															///////////// primita in radiani, si o transformam in grade              //////

//															sbinfo->armInfo.dir = rad2deg(sbinfo->armInfo.dir);

															///////////////////////////////////////////////////////////////////////////////
														}
														else
															if (!strcmp(buffer,"tackle"))
															{
																sscanf(param,"(expires %d) (count %d)", &sbinfo->tackleInfo.expires, &sbinfo->commandsCounter.tackleCounter);
															}
															else
																if(!strcmp(buffer,"focus"))
																{
																	nparam = next_token(param);
																	sscanf(nparam,"(count %d)", &sbinfo->commandsCounter.attentionToCounter);
																	nparam = next_token(++param);
																	if (!strcmp(param,"target"))
																	{
																		param = next_token(nparam);
																		if (!strcmp(nparam,"none"))
																		{
																			sbinfo->focusInfo.team_side = '0';
																			sbinfo->focusInfo.unum = 0;
																		}
																		else
																		{
																			sscanf(nparam,"%c", &sbinfo->focusInfo.team_side);
																			nparam = next_token(param);
																			sscanf(param,"%d", &sbinfo->focusInfo.unum);
																		}
																	}
																	
																	
																}
																else
																	{
																		#ifdef CREATE_GAME_LOG_FILE
																		if (LOG_IN && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "Illegal sense_body info:(%s %s\n", buffer, param);
																		#endif

																		return false;
																	}
		buffer = next;
	}

//	sbinfo->head_angle += (sbinfo->head_angle >= 0.0) ? 0.5 : -0.5;	
	return true;
}


bool COxsyScanInfo::scan_fullstate_info(char *buffer, FullStateInfo *fsinfo)
{
	COxsyInfo *pInfo = m_pClassPointers->GetInfoPointer();
	COxsyParameters *pParameters = m_pClassPointers->GetParametersPointer();
	COxsyPlayMode *pPlayMode = m_pClassPointers->GetPlayModePointer();

	char *param_name, *param_value, *next;
	int nObj = 0;

	param_name = ++buffer;
	next = next_token(param_name, " \0");
//	param_name = "fullstate"
	if (strcmp(param_name, "fullstate") != 0) return false;

	param_value = next;
	next = next_token(param_value, " \0");
//	param_value = time as integer

	fsinfo->time = atoi(param_value);
	if (fsinfo->time < 0 || fsinfo->time > pParameters->get_half_time() * (pParameters->get_nr_normal_halfs() + pParameters->get_nr_extra_halfs())) return false;

	while (*next == '(')
	{
		param_name = ++next;
		next = next_token(param_name, " \0");

		// (pmode {goalie_catch_ball_{l|r}|<play mode>})
		if (!strcmp(param_name, "pmode"))
		{
			param_value = next;
			next = next_token(param_value, ")\0");
			// param_value = play_mode as string name

			fsinfo->play_mode = pPlayMode->get_play_mode(param_value);
			if (fsinfo->play_mode == PM_Unknown) return false;

			next++;

			continue;
		}

		// (vmode {high|low} {narrow|normal|high})
		if (!strcmp(param_name, "vmode"))
		{
			param_value = next;
			next = next_token(param_value, " \0");
			// param_value = view_quality as string name

			if (!strcmp(param_value, "high"))
			{
				fsinfo->view_quality = VQ_High;
			}
			else
				if (!strcmp(param_value, "low"))
				{
					fsinfo->view_quality = VQ_Low;
				}
				else
					{
						fsinfo->view_quality = VQ_Unknown;
						return false;
					}

			param_value = next;
			next = next_token(param_value, ")\0");
			// param_value = view_width as string name

			if (!strcmp(param_value, "narrow"))
			{
				fsinfo->view_width = VW_Narrow;
			}
			else
				if (!strcmp(param_value, "normal"))
				{
					fsinfo->view_width = VW_Normal;
				}
				else
					if (!strcmp(param_value, "wide"))
					{
						fsinfo->view_width = VW_Wide;
					}
					else
						{
							fsinfo->view_width = VW_Unknown;
							return false;
						}

			next++;

			continue;
		}

		// (count <kicks> <dashes> <turns> <catches> <moves> <turn_necks> <change_views>
		// <says>)
		if (!strcmp(param_name, "count"))
		{
			param_value = next;
			next = next_token(param_value, ")\0");
			// param_value = (kick, dash, turn, catch, move, turn_neck, change_view, say) 
			// counters as integers

			if (sscanf(param_value, "%d %d %d %d %d %d %d %d",
				&fsinfo->commands_counter.kickCounter,
				&fsinfo->commands_counter.dashCounter,
				&fsinfo->commands_counter.turnCounter,
				&fsinfo->commands_counter.catchCounter,
				&fsinfo->commands_counter.moveCounter,
				&fsinfo->commands_counter.turnNeckCounter,
				&fsinfo->commands_counter.changeViewCounter,
				&fsinfo->commands_counter.sayCounter) != 8) return false;

			next++;

			continue;
		}

		// (arm (movable <MOVABLE>) (expires <EXPIRES>) (target <DIST> <DIR>) (count <COUNT>))
		if (!strcmp(param_name, "arm"))
		{
			param_name = ++next;
			next = next_token(param_name, " \0");
			// param_name = "movable"

			if (strcmp(param_name, "movable") != 0) return false;

			param_value = next;
			next = next_token(param_value, ")\0");
			// param_value = movable as integer

			fsinfo->arm_info.movable = atoi(param_value);

			next++;

			param_name = ++next;
			next = next_token(param_name, " \0");
			// param_name = "expires"

			if (strcmp(param_name, "expires") != 0) return false;

			param_value = next;
			next = next_token(param_value, ")\0");
			// param_value = expires as integer

			fsinfo->arm_info.expires = atoi(param_value);

			next++;

			param_name = ++next;
			next = next_token(param_name, " \0");
			// param_name = "target"

			if (strcmp(param_name, "target") != 0) return false;

			param_value = next;
			next = next_token(param_value, ")\0");
			// param_value = (pointto_dist, pointto_dir) as doubles

			if (sscanf(param_value, "%lf %lf",
				&fsinfo->arm_info.dist,
				&fsinfo->arm_info.dir) != 2) return false;

			next++;

			param_name = ++next;
			next = next_token(param_name, " \0");
			// param_name = "count"

			if (strcmp(param_name, "count") != 0) return false;

			param_value = next;
			next = next_token(param_value, ")\0");
			// param_value = point_to counter as integer

			fsinfo->commands_counter.pointToCounter = atoi(param_value);

			next++;
			next++;

			continue;
		}

		// (score <team_points> <enemy_points>)
		if (!strcmp(param_name, "score"))
		{
			param_value = next;
			next = next_token(param_value, ")\0");
			// param_value = (our_score, opp_score) as integers

			if (sscanf(param_value, "%d %d",
				&fsinfo->score.our_score,
				&fsinfo->score.opp_score) != 2) return false;

			next++;

			continue;
		}

		// ((b) <pos.x> <pos.y> <vel.x> <vel.y>)
		if (!strcmp(param_name, "(b)"))
		{
			param_value = next;
			next = next_token(param_value, ")\0");
			// param_value = (ball.pos.x, ball.pos.y, ball.speed.x, ball.speed.y) as doubles

			fsinfo->obj[nObj].type = OT_Ball;

			if (sscanf(param_value, "%lf %lf %lf %lf",
				&fsinfo->obj[nObj].pos.x,
				&fsinfo->obj[nObj].pos.y,
				&fsinfo->obj[nObj].speed.x,
				&fsinfo->obj[nObj].speed.y) != 4) return false;

			nObj++;

			next++;

			continue;
		}

		// ((p {l|r} <unum> {g|<player_type_id>}) <pos.x> <pos.y> <vel.x> <vel.y> <body_angle>
		// <neck_angle>)
		if (!strcmp(param_name, "(p"))
		{
			param_value = next;
			next = next_token(param_value, " \0");
			// param_value = (player_init_side) as "l" or "r"

			fsinfo->obj[nObj].type = OT_Player;
			
			if (!strcmp(param_value, "l"))
			{
				if (pInfo->get_init_side() == S_Left)
				{
					fsinfo->obj[nObj].player_info.team = WT_Our;
				}
				else
					if(pInfo->get_init_side() == S_Right)
					{
						fsinfo->obj[nObj].player_info.team = WT_Opponent;
					}
					else
						{
							fsinfo->obj[nObj].player_info.team = WT_Unknown;
							return false;
						}
			}
			else
				if(!strcmp(param_value, "r"))
				{
					if (pInfo->get_init_side() == S_Right)
					{
						fsinfo->obj[nObj].player_info.team = WT_Our;
					}
					else
						if(pInfo->get_init_side() == S_Left)
						{
							fsinfo->obj[nObj].player_info.team = WT_Opponent;
						}
						else
							{
								fsinfo->obj[nObj].player_info.team = WT_Unknown;
								return false;
							}
				}
				else
					{
						return false;
					}

			param_value = next;
			next = next_token(param_value, " \0");
			// param_value = (player number) as 1 - 11

			fsinfo->obj[nObj].player_info.unum = atoi(param_value);
			if (fsinfo->obj[nObj].player_info.unum < 1 || fsinfo->obj[nObj].player_info.unum > TEAM_PLAYERS_MAX) return false;

			param_value = next;
			next = next_token(param_value, ")\0");
			// param_value = (goalie | player_type) as (g | 0-6)

			if (!strcmp(param_value, "g"))
			{
				fsinfo->obj[nObj].player_info.type = PT_Goalie;
			}
			else
				{
					fsinfo->obj[nObj].player_info.type = (PlayerType)atoi(param_value);
					if (fsinfo->obj[nObj].player_info.type < 0 || fsinfo->obj[nObj].player_info.type >= pParameters->get_player_types()) return false;
				}

			next++;

			param_value = next;
			next = next_token(param_value, " \0");
			// param_value = player.pos.x as double

			fsinfo->obj[nObj].pos.x = atof(param_value);

			param_value = next;
			next = next_token(param_value, " \0");
			// param_value = player.pos.y as double

			fsinfo->obj[nObj].pos.y = atof(param_value);

			param_value = next;
			next = next_token(param_value, " \0");
			// param_value = player.speed.x as double

			fsinfo->obj[nObj].speed.x = atof(param_value);

			param_value = next;
			next = next_token(param_value, " \0");
			// param_value = player.speed.y as double

			fsinfo->obj[nObj].speed.y = atof(param_value);

			param_value = next;
			next = next_token(param_value, " \0");
			// param_value = player.body_angle as double

			fsinfo->obj[nObj].body_angle = atof(param_value);

			param_value = next;
			next = next_token(param_value, " \0");
			// param_value = player.head_angle as double

			fsinfo->obj[nObj].head_angle = atof(param_value);

			if (*next != '(')
			{
				param_value = next;
				next = next_token(param_value, " \0");
				// param_value = player.pointto_dist as double

				fsinfo->obj[nObj].pointto_dist = atof(param_value);

				param_value = next;
				next = next_token(param_value, " \0");
				// param_value = player.pointto_dir as double

				fsinfo->obj[nObj].pointto_dir = atof(param_value);

				///////////// PMS: ATENTIE - Directia inspre care pointeaza bratul este  //////
				///////////// primita in radiani, si o transformam in grade              //////

				fsinfo->obj[nObj].pointto_dir = rad2deg(fsinfo->obj[nObj].pointto_dir);

				///////////////////////////////////////////////////////////////////////////////

			}
			else
			{
				fsinfo->obj[nObj].pointto_dist = 0.0;
				fsinfo->obj[nObj].pointto_dir = 0.0;
			}

			next++;

			param_name = next;
			next = next_token(param_name, " \0");
			// param_name = "stamina" as string name

			if (strcmp(param_name, "stamina") != 0) return false;

			param_value = next;
			next = next_token(param_value, ")\0");
			// param_value = (stamina, effort, recovery) as doubles

			if (sscanf(param_value, "%lf %lf %lf",
				&fsinfo->obj[nObj].stamina,
				&fsinfo->obj[nObj].effort,
				&fsinfo->obj[nObj].recovery) != 3) return false;

			next++;
			next++;

			nObj++;

			continue;
		}

		return false;
	}
	
	fsinfo->n_obj = nObj;
	if (fsinfo->n_obj < 2 || fsinfo->n_obj > MOVABLE_OBJECTS_MAX) return false;

	return true;
}


bool COxsyScanInfo::scan_score_info(char *buffer)
{
	COxsyScoreInfo *pScoreInfo = m_pClassPointers->GetScoreInfoPointer();

	int score_time, our_score, opp_score;
	ScoreInfo scoreInfo = pScoreInfo->get_score_info();
	
	sscanf(buffer, "(score %d %d %d", &score_time, &our_score, &opp_score);

	if (score_time < 0 || our_score < 0 || opp_score < 0) return false;

	scoreInfo.our_score_time = score_time;
	scoreInfo.our_score = our_score;

	scoreInfo.opp_score_time = score_time;
	scoreInfo.opp_score = opp_score;

	pScoreInfo->set_score_info(scoreInfo);

	return true;
}


bool COxsyScanInfo::scan_change_player_type_info(char *buffer)
{
	COxsyInfo *pInfo = m_pClassPointers->GetInfoPointer();
//	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
//	COxsyWorldModel *pWorldModel = m_pClassPointers->GetWorldModelPointer();

//	WorldModel *wm = pWorldModel->get_world_model();
	int unum = pInfo->get_unum();

	int player_number;
	int player_type;
	int nFieldsAssigned = sscanf(buffer, "(change_player_type %d %d)", &player_number, &player_type);

	if (player_number < 1 || player_number > TEAM_PLAYERS_MAX) return false;

	if (nFieldsAssigned == 2)
	{
		if (player_type < PT_0 || player_type > PT_6) return false;

		// sets new type for changed player
//		wm->tmate[player_number - 1].type_time = pTime->get_time();
//		wm->tmate[player_number - 1].type = (PlayerType)player_type;

		if (player_number == unum)
		{
			pInfo->set_player_type((PlayerType)player_type);
		}

		// only for tests purpose
//		printf("OUR : player_number = %d player_type = %d\n", player_number, player_type);
	}
	else
		if (nFieldsAssigned == 1)
		{
			// sets new type for changed player (in this case we don't know the opponent new type but we only know that this number was changed)
//			wm->opp[player_number - 1].type_time = pTime->get_time();
//			wm->opp[player_number - 1].type = PT_Unknown;

			// only for tests purpose
//			printf("OPP : player_number = %d\n", player_number);
		}

	return true;
}


SenderType COxsyScanInfo::GetSender(char *buffer)
{
	if (!strcmp(buffer, "our"))
	{
		return ST_Our_Player;
	}
	else
		if(!strcmp(buffer, "opp"))
		{
			return ST_Opp_Player;
		}
		else
			if (!strcmp(buffer, "self"))
			{
				return ST_Self;
			}
			else
				if (!strcmp(buffer, "referee"))
				{
					return ST_Referee;
				}
				else
					{
						return ST_Unknown;
					}
}
