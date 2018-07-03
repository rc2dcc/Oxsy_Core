#include "OxsyLibrary.h"
#include "OxsyParameters.h"
#include "OxsyClassPointers.h"

#include "OxsyInfo.h"
#include "OxsyScanInfo.h"
#include "OxsySocket.h"
#include "OxsySocketCommands.h"

#include "OxsyLogger.h"

#ifndef WIN32 // _LINUX
#include <unistd.h>
#endif


COxsyParameters::COxsyParameters(COxsyClassPointers *pClassPointers)
{
	m_pClassPointers = pClassPointers;
	SetDefaultParameters();
}


COxsyParameters::~COxsyParameters()
{

}


bool COxsyParameters::GetParameters()
{
	COxsyInfo *pInfo = m_pClassPointers->GetInfoPointer();
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	#endif

	char com[BUFFER_SIZE_MAX / 256];
	char buf[BUFFER_SIZE_MAX];
	char str_server_param[BUFFER_SIZE_MAX];
	char str_backup_server_param[BUFFER_SIZE_MAX];
	char str_player_param[BUFFER_SIZE_MAX / 4];
	char str_backup_player_param[BUFFER_SIZE_MAX / 4];
	char str_player_type[DEFAULT_PLAYER_TYPES][BUFFER_SIZE_MAX / 8];
	char str_backup_player_type[BUFFER_SIZE_MAX / 8];

	BOOL bServerParam;
	BOOL bPlayerParam;
//	FILE *serverParamFile;
//	FILE *playerParamFile;
//	FILE *playerTypeFile;
	int i;
//	int nBufferLength;
//	int nFileLength;
	int nParameters;
	int nPlayerTypes;
	int nTry;
	int nTryMax;

	bServerParam = FALSE;
	bPlayerParam = FALSE;
	nPlayerTypes = 0;

//	buf[0] = 0; // delete ?
//	str_server_param[0] = 0; // delete ?
//	str_player_param[0] = 0; // delete ?
//	for(i = 0; i < DEFAULT_PLAYER_TYPES; i++) str_player_type[i][0] = 0; // delete ?

	nTry = 0;
	nTryMax = get_simulation_step() / SLEEP_TIME * CYCLES;

	while (TRUE)
	{
		nTry++;
		if (nTry > nTryMax || (bServerParam && bPlayerParam && nPlayerTypes == DEFAULT_PLAYER_TYPES)) break;

		 while (pSocketCommands->receive_message(pSocket->get_socket(), buf, BUFFER_SIZE_MAX))
		 {
			#ifdef CREATE_GAME_LOG_FILE
			if (LOG_IN && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%s\n\n", buf);
			#endif

			sscanf(buf, "(%s ", com);

			if (!strcmp(com, "server_param"))
			{
				strcpy(str_server_param, buf);
				bServerParam = TRUE;
				nTry = 0;
				break;
			}
			else
				if (!strcmp(com, "player_param"))
				{
					strcpy(str_player_param, buf);
					bPlayerParam = TRUE;
					nTry = 0;
					break;
				}
				else
					if (!strcmp(com, "player_type"))
					{
						strcpy(str_player_type[nPlayerTypes], buf);
						nPlayerTypes++;
						nTry = 0;
						break;
					}
		 }

		#ifdef WIN32
			Sleep(SLEEP_TIME);
		#else  // _LINUX
			usleep(SLEEP_TIME * 1000);
		#endif		
	}

	// server parameters
	if (bServerParam)
	{
		strcpy(str_backup_server_param, str_server_param);

		nParameters = GetServerParameters(str_server_param);

		if (nParameters == SERVER_PARAMETERS)
		{
//			serverParamFile = fopen(pInfo->get_server_param_path(), "w");
//			fprintf(serverParamFile, str_backup_server_param);
//			fclose(serverParamFile);
		}
		else
		{
			printf("Incorrect receiving <server_param> from server.Receiving %d from %d parameters\n", nParameters, SERVER_PARAMETERS);
			bServerParam = FALSE;
		}

//		printf("Reading server_param from server\n");
	}
	else
	{
/*
		serverParamFile = fopen(pInfo->get_server_param_path(), "r");

		if (serverParamFile)
		{
			fseek(serverParamFile, 0, SEEK_END);
			nFileLength = ftell(serverParamFile);
			fseek(serverParamFile, 0, SEEK_SET);
			nBufferLength = fread(str_server_param, 1, nFileLength, serverParamFile);
			str_server_param[nBufferLength] = '\0';
			fclose(serverParamFile);

			nParameters = GetServerParameters(str_server_param);

			if (nParameters == SERVER_PARAMETERS)
			{
				bServerParam = TRUE;
			}	
			else
			{
				printf("Incorrect reading <server_param> from file.Reading %d from %d parameters\n", nParameters, SERVER_PARAMETERS);
			}

//			printf("Reading server_param from file\n");
		}
		else
		{
			printf("Information for server_param missing\n");
		}
*/
		printf("Information for server_param missing\n");
	}


	// player parameters
	if (bPlayerParam)
	{
		strcpy(str_backup_player_param, str_player_param);

		nParameters = GetPlayerParameters(str_player_param);

		if (nParameters == PLAYER_PARAMETERS)
		{
//			playerParamFile = fopen(pInfo->get_player_param_path(), "w");
//			fprintf(playerParamFile, str_backup_player_param);
//			fclose(playerParamFile);
		}
		else
		{
			printf("Incorrect receiving <player_param> from server.Receiving %d from %d parameters\n", nParameters, PLAYER_PARAMETERS);
			bPlayerParam = FALSE;
		}

//		printf("Reading player_param from server");
	}
	else
	{
/*
		playerParamFile = fopen(pInfo->get_player_param_path(), "r");

		if (playerParamFile)
		{
			fseek(playerParamFile, 0, SEEK_END);
			nFileLength = ftell(playerParamFile);
			fseek(playerParamFile, 0, SEEK_SET);
			nBufferLength = fread(str_player_param, 1, nFileLength, playerParamFile);
			str_player_param[nBufferLength] = '\0';
			fclose(playerParamFile);

			nParameters = GetPlayerParameters(str_player_param);

			if (nParameters == PLAYER_PARAMETERS)
			{
				bPlayerParam = TRUE;
			}	
			else
			{
				printf("Incorrect reading <player_param> from file.Reading %d from %d parameters\n", nParameters, PLAYER_PARAMETERS);
			}

//			printf("Reading player_param from file\n");
		}
		else
		{
			printf("Information for player_param missing\n");
		}
*/
		printf("Information for player_param missing\n");
	}

	// player types
	if (nPlayerTypes == DEFAULT_PLAYER_TYPES)
	{
		for (i = 0; i < nPlayerTypes; i++)
		{
			strcpy(str_backup_player_type, str_player_type[i]);

			nParameters = GetPlayerTypeParameters(str_player_type[i], i);

			if (nParameters == PLAYER_TYPE_PARAMETERS)
			{
				if (i == DEFAULT_H_ID)
				{
//					playerTypeFile = fopen(pInfo->get_player_type_path(), "w");
//					fprintf(playerTypeFile, str_backup_player_type);
//					fclose(playerTypeFile);
				}
			}
			else
			{
				printf("Incorrect receiving <player_type %d> from server.Receiving %d from %d parameters\n", i, nParameters, PLAYER_TYPE_PARAMETERS);
				nPlayerTypes = 0;
			}

//			printf("Reading player_type from server\n");
		}
	}
	else
	{
/*
		playerTypeFile = fopen(pInfo->get_player_type_path(), "r");

		if (playerTypeFile)
		{
			fseek(playerTypeFile, 0, SEEK_END);
			nFileLength = ftell(playerTypeFile);
			fseek(playerTypeFile, 0, SEEK_SET);
			nBufferLength = fread(str_player_type[DEFAULT_H_ID], 1, nFileLength, playerTypeFile);
			str_player_type[DEFAULT_H_ID][nBufferLength] = '\0';
			fclose(playerTypeFile);

			nParameters = GetPlayerTypeParameters(str_player_type[DEFAULT_H_ID], DEFAULT_H_ID);

			if (nParameters == PLAYER_TYPE_PARAMETERS)
			{
				nPlayerTypes = DEFAULT_PLAYER_TYPES;

//				in cazul in care se citeste din fisier, celelalte 6 tipuri de jucatori
//				heterogenosi nu se cunosc, asa ca anuntam mprintr-un mesaj ca doar tipul
//				default sa citit din fisierul 'player_type.conf'.
				printf("Reading <player_type %d> from file\n", DEFAULT_H_ID);
			}	
			else
			{
				printf("Incorrect reading <player_type %d> from file.Reading %d from %d parameters\n", DEFAULT_H_ID, nParameters, PLAYER_TYPE_PARAMETERS);
			}

//			printf("Reading player_type from file\n");
		}
		else
		{
			printf("Information for player_type missing\n");
		}
*/
		printf("Information for player_type missing\n");
	}


	if (!bServerParam) SetDefaultServerParameters();
	if (!bPlayerParam) SetDefaultPlayerParameters();
	if (nPlayerTypes != DEFAULT_PLAYER_TYPES) SetDefaultPlayerTypes();

	// bugul care trimite "effort_init = 0.0" in severele mai vechi de 9.3.0
	if (bServerParam && pInfo->get_server_version() < 9.3) effort_init = DEFAULT_EFFORT_INIT; // pms

	if (!bServerParam || !bPlayerParam || nPlayerTypes != DEFAULT_PLAYER_TYPES) return FALSE;

	return TRUE;
}


void COxsyParameters::SetDefaultParameters()
{
	SetDefaultServerParameters();
	SetDefaultPlayerParameters();
	SetDefaultPlayerTypes();
}


void COxsyParameters::SetDefaultServerParameters()
{
	// int
	catch_ban_cycle = DEFAULT_CATCH_BAN_CYCLE;
	clang_advice_win = DEFAULT_CLANG_ADVICE_WIN;
	clang_define_win = DEFAULT_CLANG_DEFINE_WIN;
	clang_del_win = DEFAULT_CLANG_DEL_WIN;
	clang_info_win = DEFAULT_CLANG_INFO_WIN;
	clang_mess_delay = DEFAULT_CLANG_MESS_DELAY;
	clang_mess_per_cycle = DEFAULT_CLANG_MESS_PER_CYCLE;
	clang_meta_win = DEFAULT_CLANG_META_WIN;
	clang_rule_win = DEFAULT_CLANG_RULE_WIN;
	clang_win_size = DEFAULT_CLANG_WIN_SIZE;
	coach_port = DEFAULT_COACH_PORT;
	connect_wait = DEFAULT_CONNECT_WAIT; // new
	drop_ball_time = DEFAULT_DROP_BALL_TIME;
	freeform_send_period = DEFAULT_FREEFORM_SEND_PERIOD;
	freeform_wait_period = DEFAULT_FREEFORM_WAIT_PERIOD;
	game_log_compression = DEFAULT_GAME_LOG_COMPRESSION;
	game_log_version = DEFAULT_GAME_LOG_VERSION;
	game_over_wait = DEFAULT_GAME_OVER_WAIT; // new
	goalie_max_moves = DEFAULT_GOALIE_MAX_MOVES;
	half_time = DEFAULT_HALF_TIME;
	hear_decay = DEFAULT_HEAR_DECAY;
	hear_inc = DEFAULT_HEAR_INC;
	hear_max = DEFAULT_HEAR_MAX;
	keepaway_start = DEFAULT_KEEPAWAY_START; // new
	kick_off_wait = DEFAULT_KICK_OFF_WAIT; // new
	max_goal_kicks = DEFAULT_MAX_GOAL_KICKS;
	nr_extra_halfs = DEFAULT_NR_EXTRA_HALFS; // server version 9.3.2
	nr_normal_halfs = DEFAULT_NR_NORMAL_HALFS; // server version 9.3.2
	olcoach_port = DEFAULT_OLCOACH_PORT;
	pen_before_setup_wait = DEFAULT_PEN_BEFORE_SETUP_WAIT; // server version 9.3.2
	pen_max_extra_kicks = DEFAULT_PEN_MAX_EXTRA_KICKS; // server version 9.3.2
	pen_nr_kicks = DEFAULT_PEN_NR_KICKS; // server version 9.3.2
	pen_ready_wait = DEFAULT_PEN_READY_WAIT; // server version 9.3.2
    pen_setup_wait = DEFAULT_PEN_SETUP_WAIT; // server version 9.3.2
	pen_taken_wait = DEFAULT_PEN_TAKEN_WAIT; // server version 9.3.2
	point_to_ban = DEFAULT_POINT_TO_BAN;
	point_to_duration = DEFAULT_POINT_TO_DURATION;
	port = DEFAULT_PORT;
	recv_step = DEFAULT_RECV_STEP;
	say_coach_cnt_max = DEFAULT_SAY_COACH_CNT_MAX;
	say_coach_msg_size = DEFAULT_SAY_COACH_MSG_SIZE;
	say_msg_size = DEFAULT_SAY_MSG_SIZE;
	send_step = DEFAULT_SEND_STEP;
	send_vi_step = DEFAULT_SEND_VI_STEP;
	sense_body_step = DEFAULT_SENSE_BODY_STEP;
	simulator_step = DEFAULT_SIMULATOR_STEP;
	slow_down_factor = DEFAULT_SLOW_DOWN_FACTOR;
	start_goal_l = DEFAULT_START_GOAL_L;
	start_goal_r = DEFAULT_START_GOAL_R;
	synch_micro_sleep = DEFAULT_SYNCH_MICRO_SLEEP;
	synch_offset = DEFAULT_SYNCH_OFFSET;
	tackle_cycles = DEFAULT_TACKLE_CYCLES;
	text_log_compression = DEFAULT_TEXT_LOG_COMPRESSION;

	// char
	strcpy(game_log_dir, DEFAULT_GAME_LOG_DIR);
	strcpy(game_log_fixed_name, DEFAULT_GAME_LOG_FIXED_NAME);
	strcpy(keepaway_log_dir, DEFAULT_KEEPAWAY_LOG_DIR); // new
	strcpy(keepaway_log_fixed_name, DEFAULT_KEEPAWAY_LOG_FIXED_NAME); // new
	strcpy(landmark_file, DEFAULT_LANDMARK_FILE);
	strcpy(log_date_format, DEFAULT_LOG_DATE_FORMAT);
	strcpy(module_dir, DEFAULT_MODULE_DIR);
	strcpy(team_l_start, DEFAULT_TEAM_L_START); // new
	strcpy(team_r_start, DEFAULT_TEAM_R_START); // new
	strcpy(text_log_dir, DEFAULT_TEXT_LOG_DIR);
	strcpy(text_log_fixed_name, DEFAULT_TEXT_LOG_FIXED_NAME);

	// bool
	coach = DEFAULT_COACH;
	coach_w_referee = DEFAULT_COACH_W_REFEREE;
	old_coach_hear = DEFAULT_OLD_COACH_HEAR;
	wind_none = DEFAULT_WIND_NONE;
	wind_random = DEFAULT_WIND_RANDOM;
	auto_mode = DEFAULT_AUTO_MODE; // new
	back_passes = DEFAULT_BACK_PASSES;
	forbid_kick_off_offside = DEFAULT_FORBID_KICK_OFF_OFFSIDE;
	free_kick_faults = DEFAULT_FREE_KICK_FAULTS;
	fullstate_l = DEFAULT_FULLSTATE_L;
	fullstate_r = DEFAULT_FULLSTATE_R;
	game_log_dated = DEFAULT_GAME_LOG_DATED;
	game_log_fixed = DEFAULT_GAME_LOG_FIXED;
	game_logging = DEFAULT_GAME_LOGGING;
	keepaway = DEFAULT_KEEPAWAY; // new
	keepaway_log_dated = DEFAULT_KEEPAWAY_LOG_DATED; // new
	keepaway_log_fixed = DEFAULT_KEEPAWAY_LOG_FIXED; // new
	keepaway_logging = DEFAULT_KEEPAWAY_LOGGING; // new
	log_times = DEFAULT_LOG_TIMES;
	pen_allow_mult_kicks = DEFAULT_PEN_ALLOW_MULT_KICKS; // server version 9.3.2
	pen_coach_moves_players = DEFAULT_PEN_COACH_MOVES_PLAYERS;
	pen_random_winner = DEFAULT_PEN_RANDOM_WINNER; // server version 9.3.2
	pen_shoot_outs = DEFAULT_PEN_SHOOT_OUTS; // server version 9.3.2
	profile = DEFAULT_PROFILE;
	proper_goal_kicks = DEFAULT_PROPER_GOAL_KICKS;
	record_messages = DEFAULT_RECORD_MESSAGES;
	send_comms = DEFAULT_SEND_COMMS;
	synch_mode = DEFAULT_SYNCH_MODE;
	team_actuator_noise = DEFAULT_TEAM_ACTUATOR_NOISE;
	text_log_dated = DEFAULT_TEXT_LOG_DATED;
	text_log_fixed = DEFAULT_TEXT_LOG_FIXED;
	text_logging = DEFAULT_TEXT_LOGGING;
	use_offside = DEFAULT_USE_OFFSIDE;
	verbose = DEFAULT_VERBOSE;

	// double
	audio_cut_dist = DEFAULT_AUDIO_CUT_DIST;
	ball_accel_max = DEFAULT_BALL_ACCEL_MAX;
	ball_decay = DEFAULT_BALL_DECAY;
	ball_rand = DEFAULT_BALL_RAND;
	ball_size = DEFAULT_BALL_SIZE;
	ball_speed_max = DEFAULT_BALL_SPEED_MAX;
	ball_weight = DEFAULT_BALL_WEIGHT;
	catch_probability = DEFAULT_CATCH_PROBABILITY;
	catchable_area_l = DEFAULT_CATCHABLE_AREA_L;
	catchable_area_w = DEFAULT_CATCHABLE_AREA_W;
	ckick_margin = DEFAULT_CKICK_MARGIN;
	control_radius = DEFAULT_CONTROL_RADIUS;
	dash_power_rate = DEFAULT_DASH_POWER_RATE;
	effort_dec = DEFAULT_EFFORT_DEC;
	effort_dec_thr = DEFAULT_EFFORT_DEC_THR;
	effort_inc = DEFAULT_EFFORT_INC;
	effort_inc_thr = DEFAULT_EFFORT_INC_THR;
	effort_init = DEFAULT_EFFORT_INIT; // pms
	effort_min = DEFAULT_EFFORT_MIN;
	goal_width = DEFAULT_GOAL_WIDTH;
	inertia_moment = DEFAULT_INERTIA_MOMENT;
	keepaway_length = DEFAULT_KEEPAWAY_LENGTH; // new
	keepaway_width = DEFAULT_KEEPAWAY_WIDTH; // new
	kick_power_rate = DEFAULT_KICK_POWER_RATE;
	kick_rand = DEFAULT_KICK_RAND;
	kick_rand_factor_l = DEFAULT_KICK_RAND_FACTOR_L;
	kick_rand_factor_r = DEFAULT_KICK_RAND_FACTOR_R;
	kickable_margin = DEFAULT_KICKABLE_MARGIN;
	maxmoment = DEFAULT_MAXMOMENT;
	maxneckang = DEFAULT_MAXNECKANG;
	maxneckmoment = DEFAULT_MAXNECKMOMENT;
	maxpower = DEFAULT_MAXPOWER;
	minmoment = DEFAULT_MINMOMENT;
	minneckang = DEFAULT_MINNECKANG;
	minneckmoment = DEFAULT_MINNECKMOMENT;
	minpower = DEFAULT_MINPOWER;
	offside_active_area_size = DEFAULT_OFFSIDE_ACTIVE_AREA_SIZE;
	offside_kick_margin = DEFAULT_OFFSIDE_KICK_MARGIN;
	pen_dist_x = DEFAULT_PEN_DIST_X; // server version 9.3.2
	pen_max_goalie_dist_x = DEFAULT_PEN_MAX_GOALIE_DIST_X; // server version 9.3.2
	player_accel_max = DEFAULT_PLAYER_ACCEL_MAX;
	player_decay = DEFAULT_PLAYER_DECAY;
	player_rand = DEFAULT_PLAYER_RAND;
	player_size = DEFAULT_PLAYER_SIZE;
	player_speed_max = DEFAULT_PLAYER_SPEED_MAX;
	player_weight = DEFAULT_PLAYER_WEIGHT;
	prand_factor_l = DEFAULT_PRAND_FACTOR_L;
	prand_factor_r = DEFAULT_PRAND_FACTOR_R;
	quantize_step = DEFAULT_QUANTIZE_STEP;
	quantize_step_l = DEFAULT_QUANTIZE_STEP_L;
	recover_dec = DEFAULT_RECOVER_DEC;
	recover_dec_thr = DEFAULT_RECOVER_DEC_THR;
	recover_init = DEFAULT_RECOVER_INIT; // server version 9.3.2
	recover_min = DEFAULT_RECOVER_MIN;
	slowness_on_top_for_left_team = DEFAULT_SLOWNESS_ON_TOP_FOR_LEFT_TEAM;
	slowness_on_top_for_right_team = DEFAULT_SLOWNESS_ON_TOP_FOR_RIGHT_TEAM;
	stamina_inc_max = DEFAULT_STAMINA_INC_MAX;
	stamina_max = DEFAULT_STAMINA_MAX;
	stopped_ball_vel = DEFAULT_STOPPED_BALL_VEL;
	tackle_back_dist = DEFAULT_TACKLE_BACK_DIST;
	tackle_dist = DEFAULT_TACKLE_DIST;
	tackle_exponent = DEFAULT_TACKLE_EXPONENT;
	tackle_power_rate = DEFAULT_TACKLE_POWER_RATE;
	tackle_width = DEFAULT_TACKLE_WIDTH;
	visible_angle = DEFAULT_VISIBLE_ANGLE;
	visible_distance = DEFAULT_VISIBLE_DISTANCE;
	wind_ang = DEFAULT_WIND_ANG;
	wind_dir = DEFAULT_WIND_DIR;
	wind_force = DEFAULT_WIND_FORCE;
	wind_rand = DEFAULT_WIND_RAND;

	// additional double
	team_far_length = DEFAULT_TEAM_FAR_LENGHT; // pms
	team_too_far_length = DEFAULT_TEAM_TOO_FAR_LENGHT; // pms
	unum_far_length = DEFAULT_UNUM_FAR_LENGHT; // pms
	unum_too_far_length = DEFAULT_UNUM_TOO_FAR_LENGHT; // pms

	collision_area = DEFAULT_COLLISION_AREA;
	middle_area = DEFAULT_MIDDLE_AREA;
	kickable_area = DEFAULT_KICKABLE_AREA;
	catchable_area = DEFAULT_CATCHABLE_AREA;

	// set sends interval with regards to the slow_down_factor
	send_step *= DEFAULT_SLOW_DOWN_FACTOR;
	send_vi_step *= DEFAULT_SLOW_DOWN_FACTOR;
	sense_body_step *= DEFAULT_SLOW_DOWN_FACTOR;
	simulator_step *= DEFAULT_SLOW_DOWN_FACTOR;
}


void COxsyParameters::SetDefaultPlayerParameters()
{
	// int
	player_types = DEFAULT_PLAYER_TYPES;
	pt_max = DEFAULT_PT_MAX;
	random_seed = DEFAULT_RANDOM_SEED;
	subs_max = DEFAULT_SUBS_MAX;
    
	// double
	dash_power_rate_delta_max = DEFAULT_DASH_POWER_RATE_DELTA_MAX;
	dash_power_rate_delta_min = DEFAULT_DASH_POWER_RATE_DELTA_MIN;
	effort_max_delta_factor = DEFAULT_EFFORT_MAX_DELTA_FACTOR;
	effort_min_delta_factor = DEFAULT_EFFORT_MIN_DELTA_FACTOR;	
	extra_stamina_delta_max = DEFAULT_EXTRA_STAMINA_DELTA_MAX;
	extra_stamina_delta_min = DEFAULT_EXTRA_STAMINA_DELTA_MIN;
	inertia_moment_delta_factor = DEFAULT_INERTIA_MOMENT_DELTA_FACTOR;	
	kick_rand_delta_factor = DEFAULT_KICK_RAND_DELTA_FACTOR;	
	kickable_margin_delta_max = DEFAULT_KICKABLE_MARGIN_DELTA_MAX;
	kickable_margin_delta_min = DEFAULT_KICKABLE_MARGIN_DELTA_MIN;
	new_dash_power_rate_delta_max = DEFAULT_NEW_DASH_POWER_RATE_DELTA_MAX;
	new_dash_power_rate_delta_min = DEFAULT_NEW_DASH_POWER_RATE_DELTA_MIN;
	new_stamina_inc_max_delta_factor = DEFAULT_NEW_STAMINA_INC_MAX_DELTA_FACTOR;
	player_decay_delta_max = DEFAULT_PLAYER_DECAY_DELTA_MAX;
	player_decay_delta_min = DEFAULT_PLAYER_DECAY_DELTA_MIN;
	player_size_delta_factor = DEFAULT_PLAYER_SIZE_DELTA_FACTOR;	
	player_speed_max_delta_max = DEFAULT_PLAYER_SPEED_MAX_DELTA_MAX;
	player_speed_max_delta_min = DEFAULT_PLAYER_SPEED_MAX_DELTA_MIN;
	stamina_inc_max_delta_factor = DEFAULT_STAMINA_INC_MAX_DELTA_FACTOR;
}


void COxsyParameters::SetDefaultPlayerTypes()
{
	int i;

	for (i = 0; i < DEFAULT_PLAYER_TYPES + DEFAULT_ADDITIONAL_TYPES; i++)
	{
		// int
		h_id[i] = (i < DEFAULT_PLAYER_TYPES) ? i : DEFAULT_H_ID; // pms

		// double
		h_dash_power_rate[i] = DEFAULT_H_DASH_POWER_RATE;
		h_effort_max[i] = DEFAULT_H_EFFORT_MAX;
		h_effort_min[i] = DEFAULT_H_EFFORT_MIN;
		h_extra_stamina[i] = DEFAULT_H_EXTRA_STAMINA;
		h_inertia_moment[i] = DEFAULT_H_INERTIA_MOMENT;
		h_kick_rand[i] = DEFAULT_H_KICK_RAND;
		h_kickable_margin[i] = DEFAULT_H_KICKABLE_MARGIN;
		h_player_decay[i] = DEFAULT_H_PLAYER_DECAY;
		h_player_size[i] = DEFAULT_H_PLAYER_SIZE;
		h_player_speed_max[i] = DEFAULT_H_PLAYER_SPEED_MAX;
		h_stamina_inc_max[i] = DEFAULT_H_STAMINA_INC_MAX;

		// additional assignment
		h_speed_dash_max[i] = DEFAULT_H_SPEED_DASH_MAX;
		h_middle_area[i] = DEFAULT_H_MIDDLE_AREA;
		h_kickable_area[i] = DEFAULT_H_KICKABLE_AREA;
	}
}


int COxsyParameters::GetServerParameters(char *buffer)
{
	COxsyScanInfo *pScanInfo = m_pClassPointers->GetScanInfoPointer();

	char *param_name, *param_value, *next;
	int nParameters = 0;

	param_name = ++buffer;
	next = pScanInfo->next_token(param_name, " \0");
//	param = "server_param"
	
	while (*next == '(')
	{
		nParameters++;
		
		param_name = ++next;
		next = pScanInfo->next_token(param_name, " \0");

		param_value = next;
		next = pScanInfo->next_token(param_value, ")\0");

		// int
		if (strcmp(param_name, "catch_ban_cycle") == 0) { catch_ban_cycle = atoi(param_value); continue; }
		if (strcmp(param_name, "clang_advice_win") == 0) { clang_advice_win = atoi(param_value); continue; }
		if (strcmp(param_name, "clang_define_win") == 0) { clang_define_win = atoi(param_value); continue; }
		if (strcmp(param_name, "clang_del_win") == 0) { clang_del_win = atoi(param_value); continue; }
		if (strcmp(param_name, "clang_info_win") == 0) { clang_info_win = atoi(param_value); continue; }
		if (strcmp(param_name, "clang_mess_delay") == 0) { clang_mess_delay = atoi(param_value); continue; }
		if (strcmp(param_name, "clang_mess_per_cycle") == 0) { clang_mess_per_cycle = atoi(param_value); continue; }
		if (strcmp(param_name, "clang_meta_win") == 0) { clang_meta_win = atoi(param_value); continue; }
		if (strcmp(param_name, "clang_rule_win") == 0) { clang_rule_win = atoi(param_value); continue; }
		if (strcmp(param_name, "clang_win_size") == 0) { clang_win_size = atoi(param_value); continue; }
		if (strcmp(param_name, "coach_port") == 0) { coach_port = atoi(param_value); continue; }
		if (strcmp(param_name, "connect_wait") == 0) { connect_wait = atoi(param_value); continue; }
		if (strcmp(param_name, "drop_ball_time") == 0) { drop_ball_time = atoi(param_value); continue; }
		if (strcmp(param_name, "freeform_send_period") == 0) { freeform_send_period = atoi(param_value); continue; }
		if (strcmp(param_name, "freeform_wait_period") == 0) { freeform_wait_period = atoi(param_value); continue; }
		if (strcmp(param_name, "game_log_compression") == 0) { game_log_compression = atoi(param_value); continue; }
		if (strcmp(param_name, "game_log_version") == 0) { game_log_version = atoi(param_value); continue; }
		if (strcmp(param_name, "game_over_wait") == 0) { game_over_wait = atoi(param_value); continue; }
		if (strcmp(param_name, "goalie_max_moves") == 0) { goalie_max_moves = atoi(param_value); continue; }
		if (strcmp(param_name, "half_time") == 0) { half_time = atoi(param_value); continue; }
		if (strcmp(param_name, "hear_decay") == 0) { hear_decay = atoi(param_value); continue; }
		if (strcmp(param_name, "hear_inc") == 0) { hear_inc = atoi(param_value); continue; }
		if (strcmp(param_name, "hear_max") == 0) { hear_max = atoi(param_value); continue; }
		if (strcmp(param_name, "keepaway_start") == 0) { keepaway_start = atoi(param_value); continue; }
		if (strcmp(param_name, "kick_off_wait") == 0) { kick_off_wait = atoi(param_value); continue; }
		if (strcmp(param_name, "max_goal_kicks") == 0) { max_goal_kicks = atoi(param_value); continue; }
		if (strcmp(param_name, "nr_extra_halfs") == 0) { nr_extra_halfs = atoi(param_value); continue; }
		if (strcmp(param_name, "nr_normal_halfs") == 0) { nr_normal_halfs = atoi(param_value); continue; }
		if (strcmp(param_name, "olcoach_port") == 0) { olcoach_port = atoi(param_value); continue; }
		if (strcmp(param_name, "pen_before_setup_wait") == 0) { pen_before_setup_wait = atoi(param_value); continue; }
		if (strcmp(param_name, "pen_max_extra_kicks") == 0) { pen_max_extra_kicks = atoi(param_value); continue; }
		if (strcmp(param_name, "pen_nr_kicks") == 0) { pen_nr_kicks = atoi(param_value); continue; }
		if (strcmp(param_name, "pen_ready_wait") == 0) { pen_ready_wait = atoi(param_value); continue; }
		if (strcmp(param_name, "pen_setup_wait") == 0) { pen_setup_wait = atoi(param_value); continue; }
		if (strcmp(param_name, "pen_taken_wait") == 0) { pen_taken_wait = atoi(param_value); continue; }
		if (strcmp(param_name, "point_to_ban") == 0) { point_to_ban = atoi(param_value); continue; }
		if (strcmp(param_name, "point_to_duration") == 0) { point_to_duration = atoi(param_value); continue; }
		if (strcmp(param_name, "port") == 0) { port = atoi(param_value); continue; }
		if (strcmp(param_name, "recv_step") == 0) { recv_step = atoi(param_value); continue; }
		if (strcmp(param_name, "say_coach_cnt_max") == 0) { say_coach_cnt_max = atoi(param_value); continue; }
		if (strcmp(param_name, "say_coach_msg_size") == 0) { say_coach_msg_size = atoi(param_value); continue; }
		if (strcmp(param_name, "say_msg_size") == 0) { say_msg_size = atoi(param_value); continue; }
		if (strcmp(param_name, "send_step") == 0) { send_step = atoi(param_value); continue; }
		if (strcmp(param_name, "send_vi_step") == 0) { send_vi_step = atoi(param_value); continue; }
		if (strcmp(param_name, "sense_body_step") == 0) { sense_body_step = atoi(param_value); continue; }
		if (strcmp(param_name, "simulator_step") == 0) { simulator_step = atoi(param_value); continue; }
		if (strcmp(param_name, "slow_down_factor") == 0) { slow_down_factor = atoi(param_value); continue; }
		if (strcmp(param_name, "start_goal_l") == 0) { start_goal_l = atoi(param_value); continue; }
		if (strcmp(param_name, "start_goal_r") == 0) { start_goal_r = atoi(param_value); continue; }
		if (strcmp(param_name, "synch_micro_sleep") == 0) { synch_micro_sleep = atoi(param_value); continue; }
		if (strcmp(param_name, "synch_offset") == 0) { synch_offset = atoi(param_value); continue; }
		if (strcmp(param_name, "tackle_cycles") == 0) { tackle_cycles = atoi(param_value); continue; }
		if (strcmp(param_name, "text_log_compression") == 0) { text_log_compression = atoi(param_value); continue; }

		// char
		if (strcmp(param_name, "game_log_dir") == 0) { strncpy(game_log_dir, param_value + 1, strlen(param_value) - 2); game_log_dir[strlen(param_value) - 2] = '\0'; continue; }
		if (strcmp(param_name, "game_log_fixed_name") == 0) { strncpy(game_log_fixed_name, param_value + 1, strlen(param_value) - 2); game_log_fixed_name[strlen(param_value) - 2] = '\0'; continue; }
		if (strcmp(param_name, "keepaway_log_dir") == 0) { strncpy(keepaway_log_dir, param_value + 1, strlen(param_value) - 2); keepaway_log_dir[strlen(param_value) - 2] = '\0'; continue; }
		if (strcmp(param_name, "keepaway_log_fixed_name") == 0) { strncpy(keepaway_log_fixed_name, param_value + 1, strlen(param_value) - 2); keepaway_log_fixed_name[strlen(param_value) - 2] = '\0'; continue; }
		if (strcmp(param_name, "landmark_file") == 0) { strncpy(landmark_file, param_value + 1, strlen(param_value) - 2); landmark_file[strlen(param_value) - 2] = '\0'; continue; }
		if (strcmp(param_name, "log_date_format") == 0) { strncpy(log_date_format, param_value + 1, strlen(param_value) - 2); log_date_format[strlen(param_value) - 2] = '\0'; continue; }
		if (strcmp(param_name, "module_dir") == 0) { strncpy(module_dir, param_value + 1, strlen(param_value) - 2); module_dir[strlen(param_value) - 2] = '\0'; continue; }
		if (strcmp(param_name, "team_l_start") == 0) { strncpy(team_l_start, param_value + 1, strlen(param_value) - 2); team_l_start[strlen(param_value) - 2] = '\0'; continue; }
		if (strcmp(param_name, "team_r_start") == 0) { strncpy(team_r_start, param_value + 1, strlen(param_value) - 2); team_r_start[strlen(param_value) - 2] = '\0'; continue; }
		if (strcmp(param_name, "text_log_dir") == 0) { strncpy(text_log_dir, param_value + 1, strlen(param_value) - 2); text_log_dir[strlen(param_value) - 2] = '\0'; continue; }
		if (strcmp(param_name, "text_log_fixed_name") == 0) { strncpy(text_log_fixed_name, param_value + 1, strlen(param_value) - 2); text_log_fixed_name[strlen(param_value) - 2] = '\0'; continue; }

		// bool
		if (strcmp(param_name, "coach") == 0) { coach = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "coach_w_referee") == 0) { coach_w_referee = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "old_coach_hear") == 0) { old_coach_hear = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "wind_none") == 0) { wind_none = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "wind_random") == 0) { wind_random = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "auto_mode") == 0) { auto_mode = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "back_passes") == 0) { back_passes = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "forbid_kick_off_offside") == 0) { forbid_kick_off_offside = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "free_kick_faults") == 0) { free_kick_faults = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "fullstate_l") == 0) { fullstate_l = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "fullstate_r") == 0) { fullstate_r = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "game_log_dated") == 0) { game_log_dated = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "game_log_fixed") == 0) { game_log_fixed = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "game_logging") == 0) { game_logging = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "keepaway") == 0) { keepaway = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "keepaway_log_dated") == 0) { keepaway_log_dated = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "keepaway_log_fixed") == 0) { keepaway_log_fixed = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "keepaway_logging") == 0) { keepaway_logging = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "log_times") == 0) { log_times = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "pen_allow_mult_kicks") == 0) { pen_allow_mult_kicks = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "pen_coach_moves_players") == 0) { pen_coach_moves_players = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "pen_random_winner") == 0) { pen_random_winner = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "penalty_shoot_outs") == 0) { pen_shoot_outs = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "profile") == 0) { profile = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "proper_goal_kicks") == 0) { proper_goal_kicks = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "record_messages") == 0) { record_messages = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "send_comms") == 0) { send_comms = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "synch_mode") == 0) { synch_mode = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "team_actuator_noise") == 0) { team_actuator_noise = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "text_log_dated") == 0) { text_log_dated = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "text_log_fixed") == 0) { text_log_fixed = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "text_logging") == 0) { text_logging = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "use_offside") == 0) { use_offside = (atoi(param_value) != 0); continue; }
		if (strcmp(param_name, "verbose") == 0) { verbose = (atoi(param_value) != 0); continue; }

		// double
		if (strcmp(param_name, "audio_cut_dist") == 0) { audio_cut_dist = atof(param_value); continue; }
		if (strcmp(param_name, "ball_accel_max") == 0) { ball_accel_max = atof(param_value); continue; }
		if (strcmp(param_name, "ball_decay") == 0) { ball_decay = atof(param_value); continue; }
		if (strcmp(param_name, "ball_rand") == 0) { ball_rand = atof(param_value); continue; }
		if (strcmp(param_name, "ball_size") == 0) { ball_size = atof(param_value); continue; }
		if (strcmp(param_name, "ball_speed_max") == 0) { ball_speed_max = atof(param_value); continue; }
		if (strcmp(param_name, "ball_weight") == 0) { ball_weight = atof(param_value); continue; }
		if (strcmp(param_name, "catch_probability") == 0) { catch_probability = atof(param_value); continue; }
		if (strcmp(param_name, "catchable_area_l") == 0) { catchable_area_l = atof(param_value); continue; }
		if (strcmp(param_name, "catchable_area_w") == 0) { catchable_area_w = atof(param_value); continue; }
		if (strcmp(param_name, "ckick_margin") == 0) { ckick_margin = atof(param_value); continue; }
		if (strcmp(param_name, "control_radius") == 0) { control_radius = atof(param_value); continue; }
		if (strcmp(param_name, "dash_power_rate") == 0) { dash_power_rate = atof(param_value); continue; }
		if (strcmp(param_name, "effort_dec") == 0) { effort_dec = atof(param_value); continue; }
		if (strcmp(param_name, "effort_dec_thr") == 0) { effort_dec_thr = atof(param_value); continue; }
		if (strcmp(param_name, "effort_inc") == 0) { effort_inc = atof(param_value); continue; }
		if (strcmp(param_name, "effort_inc_thr") == 0) { effort_inc_thr = atof(param_value); continue; }
		if (strcmp(param_name, "effort_init") == 0) { effort_init = atof(param_value); continue; }
		if (strcmp(param_name, "effort_min") == 0) { effort_min = atof(param_value); continue; }
		if (strcmp(param_name, "goal_width") == 0) { goal_width = atof(param_value); continue; }
		if (strcmp(param_name, "inertia_moment") == 0) { inertia_moment = atof(param_value); continue; }
		if (strcmp(param_name, "keepaway_length") == 0) { keepaway_length = atof(param_value); continue; }
		if (strcmp(param_name, "keepaway_width") == 0) { keepaway_width = atof(param_value); continue; }
		if (strcmp(param_name, "kick_power_rate") == 0) { kick_power_rate = atof(param_value); continue; }
		if (strcmp(param_name, "kick_rand") == 0) { kick_rand = atof(param_value); continue; }
		if (strcmp(param_name, "kick_rand_factor_l") == 0) { kick_rand_factor_l = atof(param_value); continue; }
		if (strcmp(param_name, "kick_rand_factor_r") == 0) { kick_rand_factor_r = atof(param_value); continue; }
		if (strcmp(param_name, "kickable_margin") == 0) { kickable_margin = atof(param_value); continue; }
		if (strcmp(param_name, "maxmoment") == 0) { maxmoment = atof(param_value); continue; }
		if (strcmp(param_name, "maxneckang") == 0) { maxneckang = atof(param_value); continue; }
		if (strcmp(param_name, "maxneckmoment") == 0) { maxneckmoment = atof(param_value); continue; }
		if (strcmp(param_name, "maxpower") == 0) { maxpower = atof(param_value); continue; }
		if (strcmp(param_name, "minmoment") == 0) { minmoment = atof(param_value); continue; }
		if (strcmp(param_name, "minneckang") == 0) { minneckang = atof(param_value); continue; }
		if (strcmp(param_name, "minneckmoment") == 0) { minneckmoment = atof(param_value); continue; }
		if (strcmp(param_name, "minpower") == 0) { minpower = atof(param_value); continue; }
		if (strcmp(param_name, "offside_active_area_size") == 0) { offside_active_area_size = atof(param_value); continue; }
		if (strcmp(param_name, "offside_kick_margin") == 0) { offside_kick_margin = atof(param_value); continue; }
		if (strcmp(param_name, "pen_dist_x") == 0) { pen_dist_x = atof(param_value); continue; }
		if (strcmp(param_name, "pen_max_goalie_dist_x") == 0) { pen_max_goalie_dist_x = atof(param_value); continue; }
		if (strcmp(param_name, "player_accel_max") == 0) { player_accel_max = atof(param_value); continue; }
		if (strcmp(param_name, "player_decay") == 0) { player_decay = atof(param_value); continue; }
		if (strcmp(param_name, "player_rand") == 0) { player_rand = atof(param_value); continue; }
		if (strcmp(param_name, "player_size") == 0) { player_size = atof(param_value); continue; }
		if (strcmp(param_name, "player_speed_max") == 0) { player_speed_max = atof(param_value); continue; }
		if (strcmp(param_name, "player_weight") == 0) { player_weight = atof(param_value); continue; }
		if (strcmp(param_name, "prand_factor_l") == 0) { prand_factor_l = atof(param_value); continue; }
		if (strcmp(param_name, "prand_factor_r") == 0) { prand_factor_r = atof(param_value); continue; }
		if (strcmp(param_name, "quantize_step") == 0) { quantize_step = atof(param_value); continue; }
		if (strcmp(param_name, "quantize_step_l") == 0) { quantize_step_l = atof(param_value); continue; }
		if (strcmp(param_name, "recover_dec") == 0) { recover_dec = atof(param_value); continue; }
		if (strcmp(param_name, "recover_dec_thr") == 0) { recover_dec_thr = atof(param_value); continue; }
		if (strcmp(param_name, "recover_init") == 0) { recover_init = atof(param_value); continue; }
		if (strcmp(param_name, "recover_min") == 0) { recover_min = atof(param_value); continue; }
		if (strcmp(param_name, "slowness_on_top_for_left_team") == 0) { slowness_on_top_for_left_team = atof(param_value); continue; }
		if (strcmp(param_name, "slowness_on_top_for_right_team") == 0) { slowness_on_top_for_right_team = atof(param_value); continue; }
		if (strcmp(param_name, "stamina_inc_max") == 0) { stamina_inc_max = atof(param_value); continue; }
		if (strcmp(param_name, "stamina_max") == 0) { stamina_max = atof(param_value); continue; }
		if (strcmp(param_name, "stopped_ball_vel") == 0) { stopped_ball_vel = atof(param_value); continue; }
		if (strcmp(param_name, "tackle_back_dist") == 0) { tackle_back_dist = atof(param_value); continue; }
		if (strcmp(param_name, "tackle_dist") == 0) { tackle_dist = atof(param_value); continue; }
		if (strcmp(param_name, "tackle_exponent") == 0) { tackle_exponent = atof(param_value); continue; }
		if (strcmp(param_name, "tackle_power_rate") == 0) { tackle_power_rate = atof(param_value); continue; }
		if (strcmp(param_name, "tackle_width") == 0) { tackle_width = atof(param_value); continue; }
		if (strcmp(param_name, "visible_angle") == 0) { visible_angle = atof(param_value); continue; }
		if (strcmp(param_name, "visible_distance") == 0) { visible_distance = atof(param_value); continue; }
		if (strcmp(param_name, "wind_ang") == 0) { wind_ang = atof(param_value); continue; }
		if (strcmp(param_name, "wind_dir") == 0) { wind_dir = atof(param_value); continue; }
		if (strcmp(param_name, "wind_force") == 0) { wind_force = atof(param_value); continue; }
		if (strcmp(param_name, "wind_rand") == 0) { wind_rand = atof(param_value); continue; }

		nParameters--;	// parametrul nu a fost gasit deci il scadem din totalul de
						// parametrii gasitzi dupa care parasim functzia pentru a anuntza
						// indexul la care am gasit eroarea

		printf("server_param : parameter (%s %s) is new\n", param_name, param_value);

		break;
	}

	// additional double
	collision_area = player_size + ball_size;
	middle_area = player_size + ball_size + kickable_margin / 2.0;
	kickable_area = player_size + ball_size + kickable_margin;
	catchable_area = sqrt(square(catchable_area_l) + square(catchable_area_w / 2.0));

	// set sends interval with regards to the slow_down_factor
	send_step *= slow_down_factor;
	send_vi_step *= slow_down_factor;
	sense_body_step *= slow_down_factor;
	simulator_step *= slow_down_factor;

	return nParameters;
}


int COxsyParameters::GetPlayerParameters(char *buffer)
{
	COxsyScanInfo *pScanInfo = m_pClassPointers->GetScanInfoPointer();

	char *param_name, *param_value, *next;
	int nParameters = 0;

	param_name = ++buffer;
	next = pScanInfo->next_token(param_name, " \0");
//	param = "player_param"
	
	while (*next == '(')
	{
		nParameters++;

		param_name = ++next;
		next = pScanInfo->next_token(param_name, " \0");

		param_value = next;
		next = pScanInfo->next_token(param_value, ")\0");

		// int
		if (strcmp(param_name, "player_types") == 0) { player_types = atoi(param_value); continue; }
		if (strcmp(param_name, "pt_max") == 0) { pt_max = atoi(param_value); continue; }
		if (strcmp(param_name, "random_seed") == 0) { random_seed = atoi(param_value); continue; }
		if (strcmp(param_name, "subs_max") == 0) { subs_max = atoi(param_value); continue; }

		// double
		if (strcmp(param_name, "dash_power_rate_delta_max") == 0) { dash_power_rate_delta_max = atof(param_value); continue; }
		if (strcmp(param_name, "dash_power_rate_delta_min") == 0) { dash_power_rate_delta_min = atof(param_value); continue; }
		if (strcmp(param_name, "effort_max_delta_factor") == 0) { effort_max_delta_factor = atof(param_value); continue; }
		if (strcmp(param_name, "effort_min_delta_factor") == 0) { effort_min_delta_factor = atof(param_value); continue; }
		if (strcmp(param_name, "extra_stamina_delta_max") == 0) { extra_stamina_delta_max = atof(param_value); continue; }
		if (strcmp(param_name, "extra_stamina_delta_min") == 0) { extra_stamina_delta_min = atof(param_value); continue; }
		if (strcmp(param_name, "inertia_moment_delta_factor") == 0) { inertia_moment_delta_factor = atof(param_value); continue; }
		if (strcmp(param_name, "kick_rand_delta_factor") == 0) { kick_rand_delta_factor = atof(param_value); continue; }
		if (strcmp(param_name, "kickable_margin_delta_max") == 0) { kickable_margin_delta_max = atof(param_value); continue; }
		if (strcmp(param_name, "kickable_margin_delta_min") == 0) { kickable_margin_delta_min = atof(param_value); continue; }
		if (strcmp(param_name, "new_dash_power_rate_delta_max") == 0) { new_dash_power_rate_delta_max = atof(param_value); continue; }
		if (strcmp(param_name, "new_dash_power_rate_delta_min") == 0) { new_dash_power_rate_delta_min = atof(param_value); continue; }
		if (strcmp(param_name, "new_stamina_inc_max_delta_factor") == 0) { new_stamina_inc_max_delta_factor = atof(param_value); continue; }
		if (strcmp(param_name, "player_decay_delta_max") == 0) { player_decay_delta_max = atof(param_value); continue; }
		if (strcmp(param_name, "player_decay_delta_min") == 0) { player_decay_delta_min = atof(param_value); continue; }
		if (strcmp(param_name, "player_size_delta_factor") == 0) { player_size_delta_factor = atof(param_value); continue; }
		if (strcmp(param_name, "player_speed_max_delta_max") == 0) { player_speed_max_delta_max = atof(param_value); continue; }
		if (strcmp(param_name, "player_speed_max_delta_min") == 0) { player_speed_max_delta_min = atof(param_value); continue; }
		if (strcmp(param_name, "stamina_inc_max_delta_factor") == 0) { stamina_inc_max_delta_factor = atof(param_value); continue; }

		nParameters--;	// parametrul nu a fost gasit deci il scadem din totalul de
						// parametrii gasitzi dupa care parasim functzia pentru a anuntza
						// indexul la care am gasit eroarea

		printf("player_param : parameter (%s %s) is new\n", param_name, param_value);

		break;
	}

	return nParameters;
}


int COxsyParameters::GetPlayerTypeParameters(char *buffer, int index)
{
	COxsyScanInfo *pScanInfo = m_pClassPointers->GetScanInfoPointer();

	char *param_name, *param_value, *next;
	int nParameters = 0;

	param_name = ++buffer;
	next = pScanInfo->next_token(param_name, " \0");
//	param = "player_type"
	
	while (*next == '(')
	{
		nParameters++;

		param_name = ++next;
		next = pScanInfo->next_token(param_name, " \0");

		param_value = next;
		next = pScanInfo->next_token(param_value, ")\0");

		// int
		if (strcmp(param_name, "id") == 0) { h_id[index] = atoi(param_value); continue; }

		// double
		if (strcmp(param_name, "dash_power_rate") == 0) { h_dash_power_rate[index] = atof(param_value); continue; }
		if (strcmp(param_name, "effort_max") == 0) { h_effort_max[index] = atof(param_value); continue; }
		if (strcmp(param_name, "effort_min") == 0) { h_effort_min[index] = atof(param_value); continue; }
		if (strcmp(param_name, "extra_stamina") == 0) { h_extra_stamina[index] = atof(param_value); continue; }
		if (strcmp(param_name, "inertia_moment") == 0) { h_inertia_moment[index] = atof(param_value); continue; }
		if (strcmp(param_name, "kick_rand") == 0) { h_kick_rand[index] = atof(param_value); continue; }
		if (strcmp(param_name, "kickable_margin") == 0) { h_kickable_margin[index] = atof(param_value); continue; }
		if (strcmp(param_name, "player_decay") == 0) { h_player_decay[index] = atof(param_value); continue; }
		if (strcmp(param_name, "player_size") == 0) { h_player_size[index] = atof(param_value); continue; }
		if (strcmp(param_name, "player_speed_max") == 0) { h_player_speed_max[index] = atof(param_value); continue; }
		if (strcmp(param_name, "stamina_inc_max") == 0) { h_stamina_inc_max[index] = atof(param_value); continue; }

		nParameters--;	// parametrul nu a fost gasit deci il scadem din totalul de
						// parametrii gasitzi dupa care parasim functzia pentru a anuntza
						// indexul la care am gasit eroarea

		printf("player_type : parameter (%s %s) is new\n", param_name, param_value);

		break;
	}

	if (nParameters == PLAYER_TYPE_PARAMETERS)
	{
		// only for tests purpose
//		printf("kickable_margin[%d] = %lf\n", index, h_kickable_margin[index]);

		// ajustat kickable area pentru heterogenosi pentru a nu mai lovi pe langa minge
		// cele trei numere de mai jos sunt calculate din fisierul de quantificare al distantelor
		// astfel incat aceste numere sunt ultimele din serile quantificate care indeplinesc 
		// conditia de siguranta pentru kickable_margin(se poate verifica).

		double backup_h_kickable_margin = h_kickable_margin[index];
		h_kickable_margin[index] = floor((player_size + ball_size + h_kickable_margin[index]) * 10.0) / 10.0 - player_size - ball_size + EPS;
		if (backup_h_kickable_margin > 0.614999 && backup_h_kickable_margin < 0.666271) h_kickable_margin[index] -= get_dist_qstep();
		else
			if (backup_h_kickable_margin > 0.714999 && backup_h_kickable_margin < 0.776834) h_kickable_margin[index] -= get_dist_qstep();
			else
				if (backup_h_kickable_margin > 0.814999 && backup_h_kickable_margin < 0.899025) h_kickable_margin[index] -= get_dist_qstep();

		// only for tests purpose
//		printf("kickable_margin_worked[%d] = %lf\n", index, h_kickable_margin[index]);

		// additional assignment
		h_speed_dash_max[index] = maxpower * h_dash_power_rate[index] * h_effort_max[index];
		h_middle_area[index] = player_size + ball_size + h_kickable_margin[index] / 2.0;
		h_kickable_area[index] = player_size + ball_size + h_kickable_margin[index];

		// only for tests purpose
//		if (h_kickable_area[index] > 1.0) printf("---1---\n");
//		if (h_kickable_area[index] > 1.1) printf("---2---\n");
//		if (h_kickable_area[index] > 1.2) printf("---3---\n");
	}

	return nParameters;
}
