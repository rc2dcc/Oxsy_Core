#ifndef __LIBRARY_H__
#define __LIBRARY_H__


#ifdef WIN32
#include <winsock2.h>
#else // _LINUX
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#endif

#include <stdio.h>
#include <math.h>
#include <vector>


// --------------------------------- Default Parameters --------------------------------

#define USE_DEFAULT_PARAMETERS												true
// #define SERVER_PARAMETERS														152 // server version 9.2.4 ->
// #define SERVER_PARAMETERS														166 // server version 9.3.2 ->
// #define SERVER_PARAMETERS														168 // server version 9.4.5 ->
#define SERVER_PARAMETERS															167 // server version 10.0.4 ->
#define PLAYER_PARAMETERS															23
#define PLAYER_TYPE_PARAMETERS												12

// server parameters

// int
#define DEFAULT_CATCH_BAN_CYCLE						5
#define DEFAULT_CLANG_ADVICE_WIN					1
#define DEFAULT_CLANG_DEFINE_WIN					1
#define DEFAULT_CLANG_DEL_WIN						1
#define DEFAULT_CLANG_INFO_WIN						1
#define DEFAULT_CLANG_MESS_DELAY					50
#define DEFAULT_CLANG_MESS_PER_CYCLE				1
#define DEFAULT_CLANG_META_WIN						1
#define DEFAULT_CLANG_RULE_WIN						1
#define DEFAULT_CLANG_WIN_SIZE						300
#define DEFAULT_COACH_PORT							6001
#define DEFAULT_CONNECT_WAIT						300
#define DEFAULT_DROP_BALL_TIME						200
#define DEFAULT_FREEFORM_SEND_PERIOD				20
#define DEFAULT_FREEFORM_WAIT_PERIOD				600
#define DEFAULT_GAME_LOG_COMPRESSION				0
#define DEFAULT_GAME_LOG_VERSION					3
#define DEFAULT_GAME_OVER_WAIT						100
#define DEFAULT_GOALIE_MAX_MOVES					2
#define DEFAULT_HALF_TIME							3000
#define DEFAULT_HEAR_DECAY							1 // 2
#define DEFAULT_HEAR_INC							1
#define DEFAULT_HEAR_MAX							1 // 2
#define DEFAULT_KEEPAWAY_START					   -1
#define DEFAULT_KICK_OFF_WAIT						100
#define DEFAULT_MAX_GOAL_KICKS						3
#define DEFAULT_NR_EXTRA_HALFS						2 // server version 9.3.2
#define DEFAULT_NR_NORMAL_HALFS						2 // server version 9.3.2
#define DEFAULT_OLCOACH_PORT						6002
#define DEFAULT_PEN_BEFORE_SETUP_WAIT				30 // server version 9.3.2
#define DEFAULT_PEN_MAX_EXTRA_KICKS					10 // server version 9.3.2
#define DEFAULT_PEN_NR_KICKS						5 // server version 9.3.2
#define DEFAULT_PEN_READY_WAIT						5 // server version 9.3.2
#define DEFAULT_PEN_SETUP_WAIT						100 // server version 9.3.2
#define DEFAULT_PEN_TAKEN_WAIT						100 // server version 9.3.2
#define DEFAULT_POINT_TO_BAN						5
#define DEFAULT_POINT_TO_DURATION					20
#define DEFAULT_PORT								6000
#define DEFAULT_RECV_STEP							10
#define DEFAULT_SAY_COACH_CNT_MAX					128
#define DEFAULT_SAY_COACH_MSG_SIZE					128
#define DEFAULT_SAY_MSG_SIZE						10 // 512
#define DEFAULT_SEND_STEP							150
#define DEFAULT_SEND_VI_STEP						100
#define DEFAULT_SENSE_BODY_STEP						100
#define DEFAULT_SIMULATOR_STEP						100
#define DEFAULT_SLOW_DOWN_FACTOR					1
#define DEFAULT_START_GOAL_L						0
#define DEFAULT_START_GOAL_R						0
#define DEFAULT_SYNCH_MICRO_SLEEP					1
#define DEFAULT_SYNCH_OFFSET						60
#define DEFAULT_TACKLE_CYCLES						10
#define DEFAULT_TEXT_LOG_COMPRESSION				0

// char
#define DEFAULT_GAME_LOG_DIR						"./"
#define DEFAULT_GAME_LOG_FIXED_NAME					"rcssserver"
#define DEFAULT_KEEPAWAY_LOG_DIR					"./"
#define DEFAULT_KEEPAWAY_LOG_FIXED_NAME				"rcssserver"
#define DEFAULT_LANDMARK_FILE						"~/.rcssserver-landmark.xml"
#define DEFAULT_LOG_DATE_FORMAT						"%Y-%m-%d_%H:%M-"
#define DEFAULT_MODULE_DIR							"/usr/local/share/rcssserver/modules"
#define DEFAULT_TEAM_L_START						""
#define DEFAULT_TEAM_R_START						""
#define DEFAULT_TEXT_LOG_DIR						"./"
#define DEFAULT_TEXT_LOG_FIXED_NAME					"rcssserver"

// bool
#define DEFAULT_COACH								false
#define DEFAULT_COACH_W_REFEREE						false
#define DEFAULT_OLD_COACH_HEAR						false
#define DEFAULT_WIND_NONE							false
#define DEFAULT_WIND_RANDOM							false
#define DEFAULT_AUTO_MODE							false
#define DEFAULT_BACK_PASSES							true
#define DEFAULT_FORBID_KICK_OFF_OFFSIDE				true
#define DEFAULT_FREE_KICK_FAULTS					true
#define DEFAULT_FULLSTATE_L							false
#define DEFAULT_FULLSTATE_R							false
#define DEFAULT_GAME_LOG_DATED						false
#define DEFAULT_GAME_LOG_FIXED						false
#define DEFAULT_GAME_LOGGING						false
#define DEFAULT_KEEPAWAY							false
#define DEFAULT_KEEPAWAY_LOG_DATED					true
#define DEFAULT_KEEPAWAY_LOG_FIXED					false
#define DEFAULT_KEEPAWAY_LOGGING					true
#define DEFAULT_LOG_TIMES							false
#define DEFAULT_PEN_ALLOW_MULT_KICKS				false // server version 9.3.2
#define DEFAULT_PEN_COACH_MOVES_PLAYERS				true
#define DEFAULT_PEN_RANDOM_WINNER					false // server version 9.3.2
#define DEFAULT_PEN_SHOOT_OUTS						true // server version 9.3.2
#define DEFAULT_PROFILE								false
#define DEFAULT_PROPER_GOAL_KICKS					false
#define DEFAULT_RECORD_MESSAGES						false
#define DEFAULT_SEND_COMMS							false
#define DEFAULT_SYNCH_MODE							false
#define DEFAULT_TEAM_ACTUATOR_NOISE					false
#define DEFAULT_TEXT_LOG_DATED						false
#define DEFAULT_TEXT_LOG_FIXED						false
#define DEFAULT_TEXT_LOGGING						false
#define DEFAULT_USE_OFFSIDE							true
#define DEFAULT_VERBOSE								false

// double
#define DEFAULT_AUDIO_CUT_DIST						50.0
#define DEFAULT_BALL_ACCEL_MAX						2.7
#define DEFAULT_BALL_DECAY							0.94
#define DEFAULT_BALL_RAND							0.05
#define DEFAULT_BALL_SIZE							0.085
#define DEFAULT_BALL_SPEED_MAX						2.7
#define DEFAULT_BALL_WEIGHT							0.2
#define DEFAULT_CATCH_PROBABILITY					1.0
#define DEFAULT_CATCHABLE_AREA_L					2.0
#define DEFAULT_CATCHABLE_AREA_W					1.0
#define DEFAULT_CKICK_MARGIN						1.0
#define DEFAULT_CONTROL_RADIUS						2.0
#define DEFAULT_DASH_POWER_RATE						0.006
#define DEFAULT_EFFORT_DEC							0.005
#define DEFAULT_EFFORT_DEC_THR						0.3
#define DEFAULT_EFFORT_INC							0.01
#define DEFAULT_EFFORT_INC_THR						0.6
#define DEFAULT_EFFORT_INIT							1.0 // pms
#define DEFAULT_EFFORT_MAX							DEFAULT_EFFORT_INIT // pms
#define DEFAULT_EFFORT_MIN							0.6
#define DEFAULT_GOAL_WIDTH							14.02
#define DEFAULT_INERTIA_MOMENT						5.0
#define DEFAULT_KEEPAWAY_LENGTH						20.0
#define DEFAULT_KEEPAWAY_WIDTH						20.0
#define DEFAULT_KICK_POWER_RATE						0.027
#define DEFAULT_KICK_RAND							0.0
#define DEFAULT_KICK_RAND_FACTOR_L					1.0
#define DEFAULT_KICK_RAND_FACTOR_R					1.0
#define DEFAULT_KICKABLE_MARGIN						0.7
#define DEFAULT_MAXMOMENT							180.0
#define DEFAULT_MAXNECKANG							90.0
#define DEFAULT_MAXNECKMOMENT						180.0
#define DEFAULT_MAXPOWER							100.0
#define DEFAULT_MINMOMENT						   -180.0
#define DEFAULT_MINNECKANG						   -90.0
#define DEFAULT_MINNECKMOMENT					   -180.0
#define DEFAULT_MINPOWER						   -100.0
#define DEFAULT_OFFSIDE_ACTIVE_AREA_SIZE			5.0
#define DEFAULT_OFFSIDE_KICK_MARGIN					9.15
#define DEFAULT_PEN_DIST_X							11.0 // server version 9.3.2
#define DEFAULT_PEN_MAX_GOALIE_DIST_X				4.0 // server version 9.3.2
#define DEFAULT_PLAYER_ACCEL_MAX					1.0
#define DEFAULT_PLAYER_DECAY						0.4
#define DEFAULT_PLAYER_RAND							0.1
#define DEFAULT_PLAYER_SIZE							0.3
#define DEFAULT_PLAYER_SPEED_MAX					1.2 // 1.0
#define DEFAULT_PLAYER_WEIGHT						60.0
#define DEFAULT_PRAND_FACTOR_L						1.0
#define DEFAULT_PRAND_FACTOR_R						1.0
#define DEFAULT_QUANTIZE_STEP						0.1
#define DEFAULT_QUANTIZE_STEP_L						0.01
#define DEFAULT_RECOVER_DEC							0.002
#define DEFAULT_RECOVER_DEC_THR						0.3
#define DEFAULT_RECOVER_INIT						1.0 // server version 9.3.2
#define DEFAULT_RECOVER_MIN							0.5
#define DEFAULT_SLOWNESS_ON_TOP_FOR_LEFT_TEAM		1.0
#define DEFAULT_SLOWNESS_ON_TOP_FOR_RIGHT_TEAM		1.0
#define DEFAULT_STAMINA_INC_MAX						45.0
#define DEFAULT_STAMINA_MAX							4000.0
#define DEFAULT_STOPPED_BALL_VEL					0.01
#define DEFAULT_TACKLE_BACK_DIST					0.5
#define DEFAULT_TACKLE_DIST							2.0 // 2.5
#define DEFAULT_TACKLE_EXPONENT						6.0
#define DEFAULT_TACKLE_POWER_RATE					0.027
#define DEFAULT_TACKLE_WIDTH						1.0 // 1.25
#define DEFAULT_VISIBLE_ANGLE						90.0
#define DEFAULT_VISIBLE_DISTANCE					3.0
#define DEFAULT_WIND_ANG							0.0
#define DEFAULT_WIND_DIR							0.0
#define DEFAULT_WIND_FORCE							0.0
#define DEFAULT_WIND_RAND							0.0

// additional double
#define DEFAULT_COLLISION_AREA						(DEFAULT_PLAYER_SIZE + DEFAULT_BALL_SIZE)
#define DEFAULT_MIDDLE_AREA							(DEFAULT_PLAYER_SIZE + DEFAULT_BALL_SIZE + DEFAULT_KICKABLE_MARGIN / 2.0)
#define DEFAULT_KICKABLE_AREA						(DEFAULT_PLAYER_SIZE + DEFAULT_BALL_SIZE + DEFAULT_KICKABLE_MARGIN)
#define DEFAULT_CATCHABLE_AREA						(DEFAULT_BALL_SIZE + DEFAULT_CATCHABLE_AREA_L)
#define DEFAULT_TEAM_FAR_LENGHT						40.0 // pms
#define DEFAULT_TEAM_TOO_FAR_LENGHT					60.0 // pms
#define DEFAULT_UNUM_FAR_LENGHT						20.0 // pms
#define DEFAULT_UNUM_TOO_FAR_LENGHT					40.0 // pms

// player parameters

// int
#define DEFAULT_PLAYER_TYPES						7
#define DEFAULT_PT_MAX								3
#define DEFAULT_RANDOM_SEED						   -1 // negative means generate a new seed
#define DEFAULT_SUBS_MAX							3

// additional int
#define DEFAULT_ADDITIONAL_TYPES					2

// double
#define DEFAULT_DASH_POWER_RATE_DELTA_MAX			0.0
#define DEFAULT_DASH_POWER_RATE_DELTA_MIN			0.0
#define DEFAULT_EFFORT_MAX_DELTA_FACTOR			   -0.002
#define DEFAULT_EFFORT_MIN_DELTA_FACTOR			   -0.002
#define DEFAULT_EXTRA_STAMINA_DELTA_MAX				100.0
#define DEFAULT_EXTRA_STAMINA_DELTA_MIN				0.0
#define DEFAULT_INERTIA_MOMENT_DELTA_FACTOR			25.0
#define DEFAULT_KICK_RAND_DELTA_FACTOR				0.5
#define DEFAULT_KICKABLE_MARGIN_DELTA_MAX			0.2
#define DEFAULT_KICKABLE_MARGIN_DELTA_MIN			0.0
#define DEFAULT_NEW_DASH_POWER_RATE_DELTA_MAX		0.002
#define DEFAULT_NEW_DASH_POWER_RATE_DELTA_MIN		0.0
#define DEFAULT_NEW_STAMINA_INC_MAX_DELTA_FACTOR   -10000.0
#define DEFAULT_PLAYER_DECAY_DELTA_MAX				0.2
#define DEFAULT_PLAYER_DECAY_DELTA_MIN				0.0
#define DEFAULT_PLAYER_SIZE_DELTA_FACTOR		   -100.0
#define DEFAULT_PLAYER_SPEED_MAX_DELTA_MAX			0.0
#define DEFAULT_PLAYER_SPEED_MAX_DELTA_MIN			0.0
#define DEFAULT_STAMINA_INC_MAX_DELTA_FACTOR		0.0

// player type

// int
#define DEFAULT_H_ID								0 // pms
// #define DEFAULT_PLAYER_TYPE						0 // pms

// double
#define DEFAULT_H_DASH_POWER_RATE					0.006
#define DEFAULT_H_EFFORT_MAX						1.0
#define DEFAULT_H_EFFORT_MIN						0.6
#define DEFAULT_H_EXTRA_STAMINA						0.0
#define DEFAULT_H_INERTIA_MOMENT					5.0
#define DEFAULT_H_KICK_RAND							0.0
#define DEFAULT_H_KICKABLE_MARGIN					0.7
#define DEFAULT_H_PLAYER_DECAY						0.4
#define DEFAULT_H_PLAYER_SIZE						0.3
#define DEFAULT_H_PLAYER_SPEED_MAX					1.2
#define DEFAULT_H_STAMINA_INC_MAX					45.0

// additional double
#define DEFAULT_H_SPEED_DASH_MAX					DEFAULT_MAXPOWER * DEFAULT_H_DASH_POWER_RATE * DEFAULT_H_EFFORT_MAX
#define DEFAULT_H_MIDDLE_AREA						DEFAULT_PLAYER_SIZE + DEFAULT_BALL_SIZE + DEFAULT_H_KICKABLE_MARGIN / 2.0
#define DEFAULT_H_KICKABLE_AREA						DEFAULT_PLAYER_SIZE + DEFAULT_BALL_SIZE + DEFAULT_H_KICKABLE_MARGIN

// ---------------------------------- Logger parameters --------------------------------

#define CREATE_GAME_LOG_FILE

#define LOG_IN true
	#define LOG_IN_SEE false
	#define LOG_IN_HEAR false
		#define LOG_IN_HEAR_REFEREE false
		#define LOG_IN_HEAR_PLAYERS false
			#define LOG_IN_HEAR_PLAYERS_OUR false
			#define LOG_IN_HEAR_PLAYERS_OPP false
		#define LOG_IN_HEAR_SELF false
	#define LOG_IN_SENSE_BODY false
	#define LOG_IN_FULL_STATE false
	#define LOG_IN_SERVER false
#define LOG_OUT true
#define	LOG_COMMANDS_COUNTER true

#ifdef WIN32
	#define GAME_LOG_FILE_NAME								"\\player.gml"
#else // LINUX
	#define GAME_LOG_FILE_NAME								"/player.gml"
#endif

// -------------------------------------- Time -----------------------------------------

#define SLEEP_TIME									10	// milliseconds
#define CYCLES										30	// numbers of cycles after client
																			// exit if no information will be
																			// received.(Ex: server was stoped)

// --------------------------------- Structures size -----------------------------------

#define COMMANDS_PER_CYCLE_MAX						7
#define OPENED_FILES_MAX							4
#define TEAM_NAME_LENGTH_MAX						16
#define FILE_PATH_LENGTH_MAX						256
#define TEAM_PLAYERS_MAX							11
#define MOVABLE_OBJECTS_MAX							23
#define WORLD_MODEL_ARRAY_SIZE						10
#define COMMANDS_LIST_SIZE							10 
#define BUFFER_SIZE_MAX 							4096

// ------------------------------------ Names ------------------------------------------

#define GOALIE_NAME								   "goalie"
#define LEFT_SIDE_NAME							   "left"
#define RIGHT_SIDE_NAME							   "right"
#define UNKNOWN_NAME							    UNKNOWN_STRING_VALUE
#define QUOTES									   "\""

// --------------------------------- Connection settings -------------------------------

#define DEFAULT_TEAM_SIDE							LEFT_SIDE_NAME
#define DEFAULT_OUR_LEFT_TEAM_NAME				   "Oxsy_Left"
#define DEFAULT_OUR_RIGHT_TEAM_NAME				   "Oxsy_Right"
#define DEFAULT_OPPONENT_TEAM_NAME				   "Oxsy_Opponent"
#define DEFAULT_SERVER_IP						   "127.0.0.1"
#define DEFAULT_SERVER_PORT						   "6000"
#define DEFAULT_SERVER_VERSION					   "9.36"

// ---------------------------------- Objects parameters -------------------------------

#define N_PLAYERS_PER_TEAM 							11
#define N_PLAYERS									(N_PLAYERS_PER_TEAM * 2)
#define N_LINES										4
#define N_GOALS 									2
// corner, penalty, goal post, touchline, goalline, center mark 
#define N_FLAGS 									(6 + 6 + 4 + 22 + 14 + 1)
#define SEE_OBJECTS_MAX								(N_PLAYERS + N_LINES + N_GOALS + N_FLAGS)

// ----------------------------------- Pitch parameters --------------------------------

#define LAND_QSTEP_LIMIT							0.7 // limita maxima a erorii in observarea flagurilor si linilor
#define DIST_QSTEP_LIMIT							7.6 // limita maxima a erorii in observarea obiectelor(minge, jucatori)
#define DIST_MIN_STEP								0.1 // unitatea minima a distantelor receptionate in informatile vizuale
#define HALF_DIST_MIN_STEP							0.05 // unitatea de comparatie intre 2 distante

#define SECURE_DIST									2.0 // pms
#define SECURE_DIR									5.0 // pms

#define PITCH_MARGIN								5.0
#define PITCH_LENGTH					 			105.0
#define PITCH_WIDTH 	 							68.0
#define HALF_PITCH_LENGTH							(PITCH_LENGTH / 2.0)
#define HALF_PITCH_WIDTH							(PITCH_WIDTH / 2.0)
#define PITCH_DIST_MAX_INSIDE						(sqrt(square(PITCH_LENGTH) + square(PITCH_WIDTH)))
#define PITCH_LENGTH_WITH_MARK						(PITCH_LENGTH + PITCH_MARGIN * 2.0)
#define PITCH_WIDTH_WITH_MARK						(PITCH_WIDTH + PITCH_MARGIN * 2.0)
#define HALF_PITCH_LENGTH_WITH_MARK					(PITCH_LENGTH_WITH_MARK / 2.0)
#define HALF_PITCH_WIDTH_WITH_MARK					(PITCH_WIDTH_WITH_MARK / 2.0)
#define PITCH_DIST_MAX_WITH_MARK					(sqrt(square(PITCH_LENGTH_WITH_MARK) + square(PITCH_WIDTH_WITH_MARK)))
#define CIRCLE_ARC									7.1
#define CORNER_ARC_R								1.0
#define CENTER_CIRCLE_RADIUS						9.15
#define PENALTY_CIRCLE_RADIUS						9.15
#define PENALTY_AREA_LENGTH							16.5
#define PENALTY_AREA_WIDTH							40.32
#define PENALTY_CORNER_X							(HALF_PITCH_LENGTH - PENALTY_AREA_LENGTH)
#define PENALTY_CORNER_Y							(PENALTY_AREA_WIDTH / 2.0)
#define PENALTY_SPOT_DIST							11.0
#define GOAL_AREA_LENGTH							5.5
#define GOAL_AREA_WIDTH								18.32
#define GOAL_WIDTH									14.02
#define GOAL_DEPTH									4.0
#define PLAYER_SIZE									0.3
#define BALL_SIZE									0.085
#define FONT_SIZE									3.0	
#define KICKABLE_MARGIN								0.7

// ----------------------------------- Some useful defines -----------------------------

#ifndef NULL
#define NULL	0
#endif 

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif

#ifndef BOOL
#define BOOL	int
#endif

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

#define Bool	int

// ----------------------------------- Unknowns values ---------------------------------

#define MAX_INTEGER_VALUE							32767
#define MAX_DOUBLE_VALUE							32767.0
#define MIN_INTEGER_VALUE						   -32768
#define MIN_DOUBLE_VALUE						   -32768.0

#define UNKNOWN_INTEGER_VALUE						MIN_INTEGER_VALUE
#define UNKNOWN_DOUBLE_VALUE						MIN_DOUBLE_VALUE
#define UNKNOWN_CHAR_VALUE							'	'
#define UNKNOWN_STRING_VALUE						"Unknown"

// double values
#define UNKNOWN_DISTANCE							UNKNOWN_DOUBLE_VALUE
#define UNKNOWN_DIRECTION							UNKNOWN_DOUBLE_VALUE
#define UNKNOWN_DISTANCE_CHANGE						UNKNOWN_DOUBLE_VALUE
#define UNKNOWN_DIRECTION_CHANGE					UNKNOWN_DOUBLE_VALUE
#define UNKNOWN_BODY_DIRECTION						UNKNOWN_DOUBLE_VALUE
#define UNKNOWN_HEAD_DIRECTION						UNKNOWN_DOUBLE_VALUE
#define UNKNOWN_POINTTO_DIRECTION					UNKNOWN_DOUBLE_VALUE
#define UNKNOWN_ANGLE								UNKNOWN_DOUBLE_VALUE
#define UNKNOWN_X_POSITION							UNKNOWN_DOUBLE_VALUE
#define UNKNOWN_Y_POSITION							UNKNOWN_DOUBLE_VALUE
#define UNKNOWN_SPEED								UNKNOWN_DOUBLE_VALUE

// integer values
#define UNKNOWN_TIME								UNKNOWN_INTEGER_VALUE
#define UNKNOWN_CYCLE								UNKNOWN_INTEGER_VALUE
#define UNKNOWN_CYCLES								UNKNOWN_INTEGER_VALUE
#define UNKNOWN_NUMBER								UNKNOWN_INTEGER_VALUE
#define UNKNOWN_SCORE								UNKNOWN_INTEGER_VALUE
#define UNKNOWN_EXPIRES								UNKNOWN_INTEGER_VALUE
#define UNKNOWN_MOVABLE								UNKNOWN_INTEGER_VALUE
#define UNKNOWN_RANGE								UNKNOWN_INTEGER_VALUE
#define UNKNOWN_INDEX								UNKNOWN_INTEGER_VALUE
#define UNKNOWN_TEAM_SIDE							UNKNOWN_CHAR_VALUE

// ----------------------------------- Variables Types ---------------------------------

//#define Bool										int
//#define Fuzzy										float
#define Time										int
//#define Cycle										int

// -------------------------------------- Utilities ------------------------------------

#define F_E											2.7182818284590452353602874713527
#define F_INFINITY									1.0e+250
#define EPS											1.0e-10

#define RANDOMBASE									1000
#define IRANDOMBASE									31

#define drand(h, l)									((((h) - (l)) * ((double)(random() % RANDOMBASE) / (double)RANDOMBASE)) + (l))
#define	irand(x)									((random() / IRANDOMBASE) % (x))

#define PI											3.1415926535897932384626433832795

#define Min(a, b)									(((a) > (b)) ? (b) : (a))
#define Max(a, b)									(((a) > (b)) ? (a) : (b))

#define Sgn(x)										(((x) == 0.0) ? 0.0 : (((x) < 0.0) ? -1.0 : 1.0))
#define Abs(x)										(((x) > 0.0) ? (x) : -(x))
#define square(x)									((x) * (x))

#define deg2rad(d)									((double)(d) * PI / 180.0)
#define rad2deg(r)									((double)(r) * 180.0 / PI)
#define Sin(d)										sin(deg2rad(d))
#define Cos(d)										cos(deg2rad(d))

#define Tan(d)										tan(deg2rad(d))
#define Asin(d)										rad2deg(asin(d))
#define Acos(d)										rad2deg(acos(d))
#define Atan(d)										rad2deg(atan(d))

// -------------------------------------- Socket ---------------------------------------

typedef struct _Socket {
	int socketfd;
	struct sockaddr_in serv_addr;
} Socket;

// --------------------------- Say Message Characters, n = 74 --------------------------

typedef enum _SayCharacter {
	SC_0,
	SC_1,
	SC_2,
	SC_3,
	SC_4,
	SC_5,
	SC_6,
	SC_7,
	SC_8,
	SC_9,
	SC_10,
	SC_11,
	SC_12,
	SC_13,
	SC_14,
	SC_15,
	SC_16,
	SC_17,
	SC_18,
	SC_19,
	SC_20,
	SC_21,
	SC_22,
	SC_23,
	SC_24,
	SC_25,
	SC_26,
	SC_27,
	SC_28,
	SC_29,
	SC_30,
	SC_31,
	SC_32,
	SC_33,
	SC_34,
	SC_35,
	SC_36,
	SC_37,
	SC_38,
	SC_39,
	SC_40,
	SC_41,
	SC_42,
	SC_43,
	SC_44,
	SC_45,
	SC_46,
	SC_47,
	SC_48,
	SC_49,
	SC_50,
	SC_51,
	SC_52,
	SC_53,
	SC_54,
	SC_55,
	SC_56,
	SC_57,
	SC_58,
	SC_59,
	SC_60,
	SC_61,
	SC_62,
	SC_63,
	SC_64,
	SC_65,
	SC_66,
	SC_67,
	SC_68,
	SC_69,
	SC_70,
	SC_71,
	SC_72,
	SC_73,
	SC_Unknown,
	SC_Max
} SayCharacter;


#define SAY_CHARACTER_TABLE {\
	{'0',											SC_0},\
	{'1',											SC_1},\
	{'2',											SC_2},\
	{'3',											SC_3},\
	{'4',											SC_4},\
	{'5',											SC_5},\
	{'6',											SC_6},\
	{'7',											SC_7},\
	{'8',											SC_8},\
	{'9',											SC_9},\
	{'A',											SC_10},\
	{'B',											SC_11},\
	{'C',											SC_12},\
	{'D',											SC_13},\
	{'E',											SC_14},\
	{'F',											SC_15},\
	{'G',											SC_16},\
	{'H',											SC_17},\
	{'I',											SC_18},\
	{'J',											SC_19},\
	{'K',											SC_20},\
	{'L',											SC_21},\
	{'M',											SC_22},\
	{'N',											SC_23},\
	{'O',											SC_24},\
	{'P',											SC_25},\
	{'Q',											SC_26},\
	{'R',											SC_27},\
	{'S',											SC_28},\
	{'T',											SC_29},\
	{'U',											SC_30},\
	{'V',											SC_31},\
	{'W',											SC_32},\
	{'X',											SC_33},\
	{'Y',											SC_34},\
	{'Z',											SC_35},\
	{'a',											SC_36},\
	{'b',											SC_37},\
	{'c',											SC_38},\
	{'d',											SC_39},\
	{'e',											SC_40},\
	{'f',											SC_41},\
	{'g',											SC_42},\
	{'h',											SC_43},\
	{'i',											SC_44},\
	{'j',											SC_45},\
	{'k',											SC_46},\
	{'l',											SC_47},\
	{'m',											SC_48},\
	{'n',											SC_49},\
	{'o',											SC_50},\
	{'p',											SC_51},\
	{'q',											SC_52},\
	{'r',											SC_53},\
	{'s',											SC_54},\
	{'t',											SC_55},\
	{'u',											SC_56},\
	{'v',											SC_57},\
	{'w',											SC_58},\
	{'x',											SC_59},\
	{'y',											SC_60},\
	{'z',											SC_61},\
	{'(',											SC_62},\
	{')',											SC_63},\
	{'<',											SC_64},\
	{'>',											SC_65},\
	{'+',											SC_66},\
	{'-',											SC_67},\
	{'*',											SC_68},\
	{'/',											SC_69},\
	{'.',											SC_70},\
	{'?',											SC_71},\
	{'_',											SC_72},\
	{' ',											SC_73},\
	{UNKNOWN_CHAR_VALUE,							SC_Unknown},\
	{(char)NULL}}


typedef struct _SayCharacterTable {
	char sayCharacter;
	int sayCharacterValue;
} SayCharacterTable;

// ------------------------------------- Play mode -------------------------------------

typedef enum _PlayMode {
	PM_back_pass_l,
	PM_back_pass_r,
	PM_before_kick_off,
	PM_catch_fault_l,
	PM_catch_fault_r,
	PM_corner_kick_l,
	PM_corner_kick_r,
	PM_drop_ball,
	PM_first_half_over,
	PM_foul_charge_l,
	PM_foul_charge_r,
	PM_foul_push_l,
	PM_foul_push_r,
	PM_foul_multiple_attack_l,
	PM_foul_multiple_attack_r,
	PM_foul_ballout_l,
	PM_foul_ballout_r,
	PM_free_kick_fault_l,
	PM_free_kick_fault_r,
	PM_free_kick_l,
	PM_free_kick_r,
	PM_goal_kick_l,
	PM_goal_kick_r,
	PM_goal_l,
	PM_goal_r,
	PM_goalie_catch_ball_l,
	PM_goalie_catch_ball_r,
	PM_half_time,
	PM_human_judge,
	PM_indirect_free_kick_l,
	PM_indirect_free_kick_r,
	PM_kick_in_l,
	PM_kick_in_r,
	PM_kick_off_l,
	PM_kick_off_r,
	PM_offside_l,
	PM_offside_r,
	PM_pause,
	PM_penalty_kick_l,
	PM_penalty_kick_r,
	PM_penalty_miss_l,
	PM_penalty_miss_r,
	PM_penalty_ready_l,
	PM_penalty_ready_r,
	PM_penalty_score_l,
	PM_penalty_score_r,
	PM_penalty_setup_l,
	PM_penalty_setup_r,
	PM_penalty_taken_l,
	PM_penalty_taken_r,
	PM_play_on,
	PM_time_extended,
	PM_time_over,
	PM_time_up,
	PM_time_up_without_a_team,
	PM_Unknown,
	PM_Max
} PlayMode;


#define PLAY_MODE_TABLE	{\
	{"back_pass_l",									PM_back_pass_l},\
	{"back_pass_r",									PM_back_pass_r},\
	{"before_kick_off",								PM_before_kick_off},\
	{"catch_fault_l",								PM_catch_fault_l},\
	{"catch_fault_r",								PM_catch_fault_r},\
	{"corner_kick_l",								PM_corner_kick_l},\
	{"corner_kick_r",								PM_corner_kick_r},\
	{"drop_ball",									PM_drop_ball},\
	{"first_half_over",								PM_first_half_over},\
	{"foul_charge_l",								PM_foul_charge_l},\
	{"foul_charge_r",								PM_foul_charge_r},\
	{"foul_push_l",									PM_foul_push_l},\
	{"foul_push_r",									PM_foul_push_r},\
	{"foul_multiple_attack_l",						PM_foul_multiple_attack_l},\
	{"foul_multiple_attack_r",						PM_foul_multiple_attack_r},\
	{"foul_ballout_l",								PM_foul_ballout_l},\
	{"foul_ballout_r",								PM_foul_ballout_r},\
	{"free_kick_fault_l",							PM_free_kick_fault_l},\
	{"free_kick_fault_r",							PM_free_kick_fault_r},\
	{"free_kick_l",									PM_free_kick_l},\
	{"free_kick_r",									PM_free_kick_r},\
	{"goal_kick_l",									PM_goal_kick_l},\
	{"goal_kick_r",									PM_goal_kick_r},\
	{"goal_l",										PM_goal_l},\
	{"goal_r",										PM_goal_r},\
	{"goalie_catch_ball_l",							PM_goalie_catch_ball_l},\
	{"goalie_catch_ball_r",							PM_goalie_catch_ball_r},\
	{"half_time",									PM_half_time},\
	{"human_judge",									PM_human_judge},\
	{"indirect_free_kick_l",						PM_indirect_free_kick_l},\
	{"indirect_free_kick_r",						PM_indirect_free_kick_r},\
	{"kick_in_l",									PM_kick_in_l},\
	{"kick_in_r",									PM_kick_in_r},\
	{"kick_off_l",									PM_kick_off_l},\
	{"kick_off_r",									PM_kick_off_r},\
	{"offside_l",									PM_offside_l},\
	{"offside_r",									PM_offside_r},\
	{"pause",										PM_pause},\
	{"penalty_kick_l",								PM_penalty_kick_l},\
	{"penalty_kick_r",								PM_penalty_kick_r},\
	{"penalty_miss_l",								PM_penalty_miss_l},\
	{"penalty_miss_r",								PM_penalty_miss_r},\
	{"penalty_ready_l",								PM_penalty_ready_l},\
	{"penalty_ready_r",								PM_penalty_ready_r},\
	{"penalty_score_l",								PM_penalty_score_l},\
	{"penalty_score_r",								PM_penalty_score_r},\
	{"penalty_setup_l",								PM_penalty_setup_l},\
	{"penalty_setup_r",								PM_penalty_setup_r},\
	{"penalty_taken_l",								PM_penalty_taken_l},\
	{"penalty_taken_r",								PM_penalty_taken_r},\
	{"play_on",										PM_play_on},\
	{"time_extended",								PM_time_extended},\
	{"time_over",									PM_time_over},\
	{"time_up",										PM_time_up},\
	{"time_up_without_a_team",						PM_time_up_without_a_team},\
	{UNKNOWN_NAME,									PM_Unknown},\
	{NULL}}


typedef struct _PlayModeTable {
	char* strPlayMode;
	PlayMode playMode;
} PlayModeTable;

// --------------------------------------- Flags ---------------------------------------

typedef enum _FlagType {
	FT_c,
	FT_c_t,
	FT_c_b,
	FT_l_t,
	FT_l_b,
	FT_r_t,
	FT_r_b,
	FT_p_l_t,
	FT_p_l_c,
	FT_p_l_b,
	FT_p_r_t,
	FT_p_r_c,
	FT_p_r_b,
	FT_g_l_t,
	FT_g_l_b,
	FT_g_r_t,
	FT_g_r_b,
	FT_t_l_50,
	FT_t_l_40,
	FT_t_l_30,
	FT_t_l_20,
	FT_t_l_10,
	FT_t_0,
	FT_t_r_10,
	FT_t_r_20,
	FT_t_r_30,
	FT_t_r_40,
	FT_t_r_50,
	FT_b_l_50,
	FT_b_l_40,
	FT_b_l_30,
	FT_b_l_20,
	FT_b_l_10,
	FT_b_0,
	FT_b_r_10,
	FT_b_r_20,
	FT_b_r_30,
	FT_b_r_40,
	FT_b_r_50,
	FT_l_t_30,
	FT_l_t_20,
	FT_l_t_10,
	FT_l_0,
	FT_l_b_10,
	FT_l_b_20,
	FT_l_b_30,
	FT_r_t_30,
	FT_r_t_20,
	FT_r_t_10,
	FT_r_0,
	FT_r_b_10,
	FT_r_b_20,
	FT_r_b_30,
	FT_Unknown,
	FT_Max
} FlagType;


#define FLAG_TABLE {\
	{"c",			FT_c,		{ 0,								0}},\
	{"c t",			FT_c_t,		{ 0,							   -HALF_PITCH_WIDTH} },\
	{"c b",			FT_c_b,		{ 0,								HALF_PITCH_WIDTH} },\
	{"l t",			FT_l_t,		{-HALF_PITCH_LENGTH,			   -HALF_PITCH_WIDTH} },\
	{"l b",			FT_l_b,		{-HALF_PITCH_LENGTH,				HALF_PITCH_WIDTH} },\
	{"r t",			FT_r_t,		{ HALF_PITCH_LENGTH,			   -HALF_PITCH_WIDTH} },\
	{"r b",			FT_r_b,		{ HALF_PITCH_LENGTH,				HALF_PITCH_WIDTH} },\
	{"p l t",		FT_p_l_t,	{-PENALTY_CORNER_X,				   -PENALTY_CORNER_Y} },\
	{"p l c",		FT_p_l_c,	{-PENALTY_CORNER_X,					0} },\
	{"p l b",		FT_p_l_b,	{-PENALTY_CORNER_X,					PENALTY_CORNER_Y} },\
	{"p r t",		FT_p_r_t,	{ PENALTY_CORNER_X,				   -PENALTY_CORNER_Y} },\
	{"p r c",		FT_p_r_c,	{ PENALTY_CORNER_X,					0} },\
	{"p r b",		FT_p_r_b,	{ PENALTY_CORNER_X,					PENALTY_CORNER_Y} },\
	{"g l t",		FT_g_l_t,	{-HALF_PITCH_LENGTH,			   -GOAL_WIDTH / 2.0}},\
	{"g l b",		FT_g_l_b,	{-HALF_PITCH_LENGTH,				GOAL_WIDTH / 2.0}},\
	{"g r t",		FT_g_r_t,	{ HALF_PITCH_LENGTH,			   -GOAL_WIDTH / 2.0}},\
	{"g r b",		FT_g_r_b,	{ HALF_PITCH_LENGTH,				GOAL_WIDTH / 2.0}},\
	{"t l 50",		FT_t_l_50,	{-50,							   -HALF_PITCH_WIDTH_WITH_MARK}},\
	{"t l 40",		FT_t_l_40,	{-40,							   -HALF_PITCH_WIDTH_WITH_MARK}},\
	{"t l 30",		FT_t_l_30,	{-30,							   -HALF_PITCH_WIDTH_WITH_MARK}},\
	{"t l 20",		FT_t_l_20,	{-20,							   -HALF_PITCH_WIDTH_WITH_MARK}},\
	{"t l 10",		FT_t_l_10,	{-10,							   -HALF_PITCH_WIDTH_WITH_MARK}},\
	{"t 0",			FT_t_0,		{ 0,							   -HALF_PITCH_WIDTH_WITH_MARK}},\
	{"t r 10",		FT_t_r_10,	{ 10,							   -HALF_PITCH_WIDTH_WITH_MARK}},\
	{"t r 20",		FT_t_r_20,	{ 20,							   -HALF_PITCH_WIDTH_WITH_MARK}},\
	{"t r 30",		FT_t_r_30,	{ 30,							   -HALF_PITCH_WIDTH_WITH_MARK}},\
	{"t r 40",		FT_t_r_40,	{ 40,							   -HALF_PITCH_WIDTH_WITH_MARK}},\
	{"t r 50",		FT_t_r_50,	{ 50,							   -HALF_PITCH_WIDTH_WITH_MARK}},\
	{"b l 50",		FT_b_l_50,	{-50,								HALF_PITCH_WIDTH_WITH_MARK}},\
	{"b l 40",		FT_b_l_40,	{-40,								HALF_PITCH_WIDTH_WITH_MARK}},\
	{"b l 30",		FT_b_l_30,	{-30,								HALF_PITCH_WIDTH_WITH_MARK}},\
	{"b l 20",		FT_b_l_20,	{-20,								HALF_PITCH_WIDTH_WITH_MARK}},\
	{"b l 10",		FT_b_l_10,	{-10,								HALF_PITCH_WIDTH_WITH_MARK}},\
	{"b 0",			FT_b_0,		{ 0,								HALF_PITCH_WIDTH_WITH_MARK}},\
	{"b r 10",		FT_b_r_10,	{ 10,								HALF_PITCH_WIDTH_WITH_MARK}},\
	{"b r 20",		FT_b_r_20,	{ 20,								HALF_PITCH_WIDTH_WITH_MARK}},\
	{"b r 30",		FT_b_r_30,	{ 30,								HALF_PITCH_WIDTH_WITH_MARK}},\
	{"b r 40",		FT_b_r_40,	{ 40,								HALF_PITCH_WIDTH_WITH_MARK}},\
	{"b r 50",		FT_b_r_50,	{ 50,								HALF_PITCH_WIDTH_WITH_MARK}},\
	{"l t 30",		FT_l_t_30,	{-HALF_PITCH_LENGTH_WITH_MARK,	   -30}},\
	{"l t 20",		FT_l_t_20,	{-HALF_PITCH_LENGTH_WITH_MARK,	   -20}},\
	{"l t 10",		FT_l_t_10,	{-HALF_PITCH_LENGTH_WITH_MARK,	   -10}},\
	{"l 0",			FT_l_0,		{-HALF_PITCH_LENGTH_WITH_MARK,		0}},\
	{"l b 10",		FT_l_b_10,	{-HALF_PITCH_LENGTH_WITH_MARK,		10}},\
	{"l b 20",		FT_l_b_20,	{-HALF_PITCH_LENGTH_WITH_MARK,		20}},\
	{"l b 30",		FT_l_b_30,	{-HALF_PITCH_LENGTH_WITH_MARK,		30}},\
	{"r t 30",		FT_r_t_30,	{ HALF_PITCH_LENGTH_WITH_MARK,	   -30}},\
	{"r t 20",		FT_r_t_20,	{ HALF_PITCH_LENGTH_WITH_MARK,	   -20}},\
	{"r t 10",		FT_r_t_10,	{ HALF_PITCH_LENGTH_WITH_MARK,	   -10}},\
	{"r 0",			FT_r_0,		{ HALF_PITCH_LENGTH_WITH_MARK,		0}},\
	{"r b 10",		FT_r_b_10,	{ HALF_PITCH_LENGTH_WITH_MARK,		10}},\
	{"r b 20",		FT_r_b_20,	{ HALF_PITCH_LENGTH_WITH_MARK,		20}},\
	{"r b 30",		FT_r_b_30,	{ HALF_PITCH_LENGTH_WITH_MARK,		30}},\
	{UNKNOWN_NAME,	FT_Unknown,	{ UNKNOWN_X_POSITION,				UNKNOWN_Y_POSITION}},\
	{NULL}}


typedef struct _Pos {
	double x;
	double y;
} Pos;


typedef struct _FlagTable {
	char* strFlagType;
	FlagType flagType;
	Pos pos;
} FlagTable;

// -------------------------------------------- Lines ----------------------------------

typedef enum _LineType {
	LT_L,
	LT_T,
	LT_B,
	LT_R, 
	LT_Unknown,
} LineType;

// --------------------------------- Fullstate info ----------------------------------

// order in this enum must be like this PT_0 = 0 ... PT_6 = 6 and after this values the others defines can be in any order.
typedef enum _PlayerType {
	PT_0,
	PT_1,
	PT_2,
	PT_3,
	PT_4,
	PT_5,
	PT_6,
	PT_Goalie, // has the same characteristics like PT_0, the only differnece is that, this type can catch ball with 'Catch' command.
	PT_Unknown,
} PlayerType;


typedef enum _WhichTeam {
	WT_Our,
	WT_Opponent,
	WT_Unknown,
} WhichTeam;


typedef struct _PlayerInfo {
	WhichTeam team;
	int unum;
	PlayerType type;
} PlayerInfo;


typedef enum _ObjectType {
	OT_Ball,
	OT_Player,
	OT_Goal,
	OT_Flag,
	OT_Line,
	OT_Unknown,
} ObjectType;


typedef struct _FullStateObj {
	ObjectType type;
	PlayerInfo player_info;
	Pos pos;
	Pos speed;
	double body_angle;
	double head_angle;
	double pointto_dist;
	double pointto_dir;
	double stamina;
	double effort;
	double recovery;
} FullStateObj;


typedef struct _ArmInfo {
	int movable;
	int expires;
	double dist;
	double dir;
} ArmInfo;


typedef struct _CommandsCounter {
	int kickCounter;
	int dashCounter;
	int turnCounter;
	int sayCounter;
	int turnNeckCounter;
	int catchCounter;
	int moveCounter;
	int changeViewCounter;
	int tackleCounter;
	int pointToCounter;
	int attentionToCounter;
} CommandsCounter;


typedef enum _ViewWidth {
	VW_Narrow,
	VW_Normal,
	VW_Wide,
	VW_Unknown,
} ViewWidth;


typedef enum _ViewQuality {
	VQ_Low,
	VQ_High,
	VQ_Unknown,
} ViewQuality;


typedef struct _Score{
	int our_score;
	int opp_score;
} Score;


typedef struct _FullStateInfo {
	Time time;
	PlayMode play_mode;
	Score score;

	// self information
	ViewQuality view_quality;
	ViewWidth view_width;
	CommandsCounter commands_counter;
	ArmInfo arm_info;
	
	int n_obj;
	FullStateObj obj[MOVABLE_OBJECTS_MAX];
} FullStateInfo;

// --------------------------------- Sense Body Info -----------------------------------

typedef struct _FocusInfo {
	char team_side;
	int unum;
} FocusInfo;


typedef struct _TackleInfo {
	int expires;
} TackleInfo;


typedef struct _SenseBodyInfo {
	Time time;
	ViewQuality viewQuality;
	ViewWidth viewWidth;
	double stamina;
	double effort;
	double speed_value;
	double speed_dir; // PMS
	double head_angle;
	CommandsCounter commandsCounter;
	TackleInfo tackleInfo;
	ArmInfo armInfo;
	FocusInfo focusInfo;
} SenseBodyInfo;

// -------------------------------------- Hear Info ------------------------------------

typedef enum _SenderType {
	ST_Our_Player,
	ST_Opp_Player,
	ST_Self,
	ST_Referee,
	ST_Unknown,
} SenderType;


typedef struct _HearInfo {
	Time time;
	double direction;
	SenderType sender;
	int unum;
	char message[Max(BUFFER_SIZE_MAX / 128, DEFAULT_SAY_MSG_SIZE) + 1];
} HearInfo;

// ----------------------------------------- See Info ----------------------------------

typedef enum _Side {
    S_Left,
    S_Right,
	S_Unknown,
} Side;


typedef enum _ViewCone {
	VC_In,
	VC_Out,
	VC_Unknown,
} ViewCone;


typedef struct _Range {
	int begin;
	int end;
} Range;


typedef struct _SeenObj {
	ObjectType type;
	Range our_range;
	Range opp_range;
	ViewCone viewCone;
	Bool bIsTackling; // new
	union
	{
		PlayerInfo player;
		Side side;
		FlagType flagType;
		LineType lineType;
	} id;
	double dist;
	double dir;
	double dist_chng;
	double dir_chng;
	double body_dir;
	double head_dir;
	double pointto_dir; // new
} SeenObj;


typedef struct _SeeInfo {
	Time time;
	int n_obj;
	SeenObj obj[SEE_OBJECTS_MAX];
} SeeInfo;

// -------------------------------------- Sensor Info ----------------------------------

typedef enum _SensorInfoType {
	SIT_See,
	SIT_Hear,
	SIT_SenseBody,
	SIT_FullState,
	SIT_Server
} SensorInfoType;


typedef struct _SensorInfo {
	SensorInfoType type;
	union {
		SeeInfo see;
		HearInfo hear;
		SenseBodyInfo senseBody;
		FullStateInfo fullState;
	} info;
} SensorInfo;

// -------------------------------------- World Model ----------------------------------

typedef struct _ScoreInfo {
	Time our_score_time;
	int our_score;
	Time opp_score_time;
	int opp_score;
} ScoreInfo;


typedef struct _PlayModeInfo {
	Time play_mode_time;
	PlayMode play_mode;
} PlayModeInfo;


// ------------------------------------ Commands List ----------------------------------

typedef enum _CommandName {
///////////////////////////// only one of these per cycle = YES ///////////////////////////////
	Com_Catch,
	Com_Dash,
	Com_Kick,
	Com_Move,
	Com_Tackle,
	Com_Turn,
///////////////////////////// only one of these per cycle = NO ////////////////////////////////
	Com_Attention_To,
	Com_Attention_To_Off,
	Com_Change_View,
	Com_Ear, // this command can be used even by the trainer
	Com_Point_To,
	Com_Point_To_Off,
	Com_Say,
	Com_Score,
	Com_Sense_Body,
/////////////////////////////// only one turn_neck per cycle = YES ////////////////////////////
	Com_Turn_Neck,
///////////////////////// Connecting, Reconnecting & Disconnecting ////////////////////////////
	Com_Bye,
	Com_Compression,
	Com_Init,
	Com_Reconnect,
/////////////////// Commands that can be used by both trainer and online-coach ////////////////
	Com_Eye,
	Com_Look,
///////////////////////////////////////////////////////////////////////////////////////////////
	Com_Nothing, // empty command
	Com_Max // mark command
} CommandName;


typedef struct _Command {
	Time time;
	CommandName name;
	double p1;
	double p2;
} Command;

// --------------------------------------- Init ----------------------------------------

typedef struct _InitInfo {
	Side side;
	int number;
	char strPlayMode[BUFFER_SIZE_MAX / 128 + 1];
	PlayMode playMode;
} InitInfo;

// ----------------------------------- Match state -------------------------------------

typedef enum _MatchState {
	MS_First_Half,
	MS_Second_Half,
	MS_Unknown_Half
} MatchState;

// ---------------------------------- Log files information ----------------------------

typedef struct _FileInfo {
	FILE *fileHandler;
	char *strFilePath;
} FileInfo;


#endif // __LIBRARY_H__
