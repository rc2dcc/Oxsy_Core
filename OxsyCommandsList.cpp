#include "OxsyLibrary.h"
#include "OxsyCommandsList.h"
#include "OxsyClassPointers.h"

#include "OxsyBasicCommands.h"
#include "OxsyInfo.h"
#include "OxsyParameters.h"
#include "OxsySocket.h"
#include "OxsyTime.h"
#include "OxsyUtility.h"

#include "OxsyLogger.h"
#include "OxsyTime.h"


COxsyCommandsList::COxsyCommandsList(COxsyClassPointers *pClassPointers)
{
	m_pClassPointers = pClassPointers;
	init_commands_list();
	init_commands_counter();
}


COxsyCommandsList::~COxsyCommandsList()
{

}


void COxsyCommandsList::init_commands_list(void) 
{	
	for (int i = 0; i < COMMANDS_LIST_SIZE; i++) 
	{
		m_Command[i].time = UNKNOWN_TIME;
	}

	m_nIndex = 0;
}


void COxsyCommandsList::init_commands_counter()
{
	m_CommandsCounter.catchCounter = 0;
	m_CommandsCounter.changeViewCounter = 0;
	m_CommandsCounter.dashCounter = 0;
	m_CommandsCounter.kickCounter = 0;
	m_CommandsCounter.moveCounter = 0;
	m_CommandsCounter.sayCounter = 0;
	m_CommandsCounter.turnCounter = 0;
	m_CommandsCounter.turnNeckCounter = 0;
	m_CommandsCounter.pointToCounter = 0;
	m_CommandsCounter.attentionToCounter = 0;
	m_CommandsCounter.tackleCounter = 0;
}


void COxsyCommandsList::add_command(int time, CommandName commandName, double p1, double p2)
{
  m_Command[m_nIndex].time = time;
  m_Command[m_nIndex].name = commandName;
  m_Command[m_nIndex].p1 = p1;
  m_Command[m_nIndex].p2 = p2;
  m_nIndex++;
  m_nIndex %= COMMANDS_LIST_SIZE;
}


int COxsyCommandsList::Catch(double dir) 
{
	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	COxsyUtility *pUtility = m_pClassPointers->GetUtilityPointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	#endif
	
	dir = pUtility->normalized_dir(dir);

	if (pBasicCommands->send_com_catch(pSocket->get_socket(), dir)) 
	{
		m_CommandsCounter.catchCounter++;

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_COMMANDS_COUNTER && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Catch counter = %d\n", pTime->get_time(), m_CommandsCounter.catchCounter);
		#endif

		add_command(pTime->get_time(), Com_Catch, dir, 0.0);

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Catch : dir = %lf\n", pTime->get_time(), dir);
		#endif

		return TRUE;
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Catch command not succeds!\n", pTime->get_time());
		#endif

		return FALSE;
	}
}


int COxsyCommandsList::Dash(double power)
{
	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	COxsyUtility *pUtility = m_pClassPointers->GetUtilityPointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	#endif

	power = pUtility->normalized_power(power);

	if (pBasicCommands->send_com_dash(pSocket->get_socket(), power))
	{
		m_CommandsCounter.dashCounter++;

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_COMMANDS_COUNTER && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Dash counter = %d\n", pTime->get_time(), m_CommandsCounter.dashCounter);
		#endif

		add_command(pTime->get_time(), Com_Dash, power, 0.0);

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Dash : power = %lf\n", pTime->get_time(), power);
		#endif

		return TRUE;
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Dash command not succeds!\n", pTime->get_time());
		#endif

		return FALSE;
	}
}


int COxsyCommandsList::Kick(double power, double dir) 
{
	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	COxsyUtility *pUtility = m_pClassPointers->GetUtilityPointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	#endif
	
	power = pUtility->normalized_power(power);
	dir = pUtility->normalized_dir(dir);

	if (pBasicCommands->send_com_kick(pSocket->get_socket(), power, dir))
	{
		m_CommandsCounter.kickCounter++;

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_COMMANDS_COUNTER && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Kick counter = %d\n", pTime->get_time(), m_CommandsCounter.kickCounter);
		#endif

		add_command(pTime->get_time(), Com_Kick, power, dir);

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Kick : power = %lf dir = %lf\n", pTime->get_time(), power, dir);
		#endif

		return TRUE;
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Kick command not succeds!\n", pTime->get_time());
		#endif

		return FALSE;
	}
}


int COxsyCommandsList::Move(double x, double y) 
{

	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	COxsyUtility *pUtility = m_pClassPointers->GetUtilityPointer();
	
	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	#endif
	
	x = pUtility->normalized_pos_x_inside_pitch(x);
	y = pUtility->normalized_pos_y_inside_pitch(y);

	if (pBasicCommands->send_com_move(pSocket->get_socket(), x, y))
	{
		m_CommandsCounter.moveCounter++;

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_COMMANDS_COUNTER && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Move counter = %d\n", pTime->get_time(), m_CommandsCounter.moveCounter);
		#endif

		add_command(pTime->get_time(), Com_Move, x, y);

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Move : x = %lf y = %lf\n", pTime->get_time(), x, y);
		#endif

		return TRUE;
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Move command not succeds!\n", pTime->get_time());
		#endif

		return FALSE;
	}
}


int COxsyCommandsList::Turn(double dir) 
{
	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
	COxsyInfo *pInfo = m_pClassPointers->GetInfoPointer();
	COxsyParameters *pParameters = m_pClassPointers->GetParametersPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	COxsyUtility *pUtility = m_pClassPointers->GetUtilityPointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	#endif

	dir *= (1.0 + pParameters->get_h_inertia_moment((int)pInfo->get_player_type()) * pInfo->get_speed_value());
	
	dir = pUtility->normalized_dir(dir);

	if (pBasicCommands->send_com_turn(pSocket->get_socket(), dir))
	{
		m_CommandsCounter.turnCounter++;

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_COMMANDS_COUNTER && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Turn counter = %d\n", pTime->get_time(), m_CommandsCounter.turnCounter);
		#endif

		add_command(pTime->get_time(), Com_Turn, dir, 0.0);

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Turn : dir = %lf\n", pTime->get_time(), dir);
		#endif

		return TRUE;
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Turn command not succeds!\n", pTime->get_time());
		#endif

		return FALSE;
	}
}


int COxsyCommandsList::Turn_Neck(double dir) 
{
	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	COxsyUtility *pUtility = m_pClassPointers->GetUtilityPointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	#endif

	dir = pUtility->normalized_turn_neck_dir(dir);

	if (pBasicCommands->send_com_turn_neck(pSocket->get_socket(), dir))
	{
		m_CommandsCounter.turnNeckCounter++;

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_COMMANDS_COUNTER && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Turn_Neck counter = %d\n", pTime->get_time(), m_CommandsCounter.turnNeckCounter);
		#endif

		add_command(pTime->get_time(), Com_Turn_Neck, dir, 0.0);

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Turn_Neck : dir = %lf\n", pTime->get_time(), dir);
		#endif

		return TRUE;
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Turn_neck command not succeds!\n", pTime->get_time());
		#endif

		return FALSE;
	}
}


int COxsyCommandsList::Change_View(ViewWidth width, ViewQuality quality)
{
	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	#endif

	if (pBasicCommands->send_com_change_view(pSocket->get_socket(), width, quality))
	{
		m_CommandsCounter.changeViewCounter++;

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_COMMANDS_COUNTER && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Change_View counter = %d\n", pTime->get_time(), m_CommandsCounter.changeViewCounter);
		#endif

		add_command(pTime->get_time(), Com_Change_View, width, quality);

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Change_View : width = %d  quality = %d\n", pTime->get_time(), width, quality);
		#endif

		return TRUE;
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Change_View command not succeds!\n", pTime->get_time());
		#endif

		return FALSE;
	}
}


int COxsyCommandsList::Eye(bool onp)
{
	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	#endif

	if (pBasicCommands->send_com_eye(pSocket->get_socket(), onp))
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Eye : onp = %d\n", pTime->get_time(), onp);
		#endif

		return TRUE;
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Eye command not succeds!\n", pTime->get_time());
		#endif

		return FALSE;
	}
}


int COxsyCommandsList::Look(void)
{
	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	#endif

	if (pBasicCommands->send_com_look(pSocket->get_socket()))
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Look\n", pTime->get_time());
		#endif

		return TRUE;
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Look command not succeds!\n", pTime->get_time());
		#endif

		return FALSE;
	}
}


// a-zA-Z0-9 +-*/.()<>?_
int COxsyCommandsList::Say(char *message) 
{
	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	#endif

	if (strlen(message) == 0)
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Say message is empty!\n", pTime->get_time());
		#endif

		return FALSE;
	}
	
	if (pBasicCommands->send_com_say(pSocket->get_socket(), message))
	{
		m_CommandsCounter.sayCounter++;
	
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_COMMANDS_COUNTER && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Say counter = %d\n", pTime->get_time(), m_CommandsCounter.sayCounter);
		#endif

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Say : %s\n", pTime->get_time(), message);
		#endif
		
		return TRUE;
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Say command not succeds!\n", pTime->get_time());
		#endif
		
		return FALSE;
	}
}


int COxsyCommandsList::Sense_Body(void)
{
	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	#endif

	if (pBasicCommands->send_com_sense_body(pSocket->get_socket()))
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Sense_Body\n", pTime->get_time());
		#endif

		return TRUE;
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Sense_Body command not succeds!\n", pTime->get_time());
		#endif

		return FALSE;
	}
}


int COxsyCommandsList::Score(void) 
{
	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	#endif

	if (pBasicCommands->send_com_score(pSocket->get_socket()))
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Score\n", pTime->get_time());
		#endif

		return TRUE;
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Score command not succeds!\n", pTime->get_time());
		#endif

		return FALSE;
	}
}


int COxsyCommandsList::Bye(void)
{
	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	#endif

	if (pBasicCommands->send_com_bye(pSocket->get_socket()))
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Bye\n", pTime->get_time());
		#endif

		return TRUE;
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Bye command not succeds!\n", pTime->get_time());
		#endif

		return FALSE;
	}
}


InitInfo COxsyCommandsList::Init(char *teamname, double version, bool goalie)
{
	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
//	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	#endif

	InitInfo info;

	info = pBasicCommands->send_com_init(teamname, version, goalie);

	if (info.side != S_Unknown && info.playMode != PM_Unknown && info.number != UNKNOWN_NUMBER && strcmp(info.strPlayMode, UNKNOWN_NAME))
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Init : team_name = %s version = %lf goalie = %d\n", pTime->get_time(), teamname, version, goalie);
		#endif
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Init command not succeds!\n", pTime->get_time());
		#endif
	}

	return info;
}


InitInfo COxsyCommandsList::Reconnect(char *teamname, int unum)
{
	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
//	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	#endif

	InitInfo info;

	info = pBasicCommands->send_com_reconnect(teamname, unum);

	if (info.side != S_Unknown && info.playMode != PM_Unknown && info.number != UNKNOWN_NUMBER && strcmp(info.strPlayMode, UNKNOWN_NAME))
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Reconnect : team_name = %s unum = %d\n", pTime->get_time(), teamname, unum);
		#endif
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Reconnect command not succeds!\n", pTime->get_time());
		#endif
	}

	return info;
}


// (pointto off)

int COxsyCommandsList::Point_To_Off()
{
	return Point_To(0.0, 0.0);
}


int COxsyCommandsList::Point_To(double dist, double dir)
{
	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
//	COxsyInfo *pInfo = m_pClassPointers->GetInfoPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();
	COxsyUtility *pUtility = m_pClassPointers->GetUtilityPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
//	COxsyWorldModel *pWorldModel = m_pClassPointers->GetWorldModelPointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	#endif

//	WorldModel *wm = pWorldModel->get_world_model();
//	int unum = pInfo->get_unum();

/*
	if (wm->tmate[unum - 1].body_angle_time != UNKNOWN_TIME && wm->tmate[unum - 1].head_angle_time != UNKNOWN_TIME)
	{
		dir = pUtility->sub_dir(dir, pUtility->add_dir(wm->tmate[unum - 1].body_angle, wm->tmate[unum - 1].head_angle));
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Point_To command unknown player angles!\n", pTime->get_time());
		#endif

		return FALSE;
	}
*/

	dir = pUtility->normalized_dir(dir);

	if (pBasicCommands->send_com_point_to(pSocket->get_socket(), dist, dir))
	{
		m_CommandsCounter.pointToCounter++;

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_COMMANDS_COUNTER && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Point_To counter = %d\n", pTime->get_time(), m_CommandsCounter.pointToCounter);
		#endif

		add_command(pTime->get_time(), Com_Point_To, dist, dir);

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Point_To : dist = %lf dir = %lf\n", pTime->get_time(), dist, dir);
		#endif

		return TRUE;
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Point_To command not succeds!\n", pTime->get_time());
		#endif

		return FALSE;
	}
}


// level = -1 indicate that zlib is not to be used (default) and 0 to 9 indicate 
// levels of compression as per the zlib library.

int COxsyCommandsList::Compression(int level)
{
	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	#endif

	if (pBasicCommands->send_com_compression(pSocket->get_socket(), level))
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Compression : level = %d\n", pTime->get_time(), level);
		#endif

		return TRUE;
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Compression command not succeds!\n", pTime->get_time());
		#endif

		return FALSE;
	}
}


// (attentionto off)

int COxsyCommandsList::Attention_To_Off()
{
	return Attention_To("\0", 0);
}


//  (attentionto <TEAM> <UNUM>) | (attentionto off)
//  Where <TEAM> is : opp | our | l | r | left | right | <TEAM_NAME>
//  and   <UNUM> is integer identifying a member of the team specified

int COxsyCommandsList::Attention_To(char *team, int unum)
{
	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
	COxsyInfo *pInfo = m_pClassPointers->GetInfoPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	#endif

	char side;

	if (strlen(team) == 0 && unum == 0)
	{
		side = '0';
	}
	else
	{
		if(strcmp(team, "our") == 0 || strcmp(team, pInfo->get_our_team_name()) == 0)
		{
			side = (pInfo->get_init_side() == S_Left) ? 'l' : 'r';
		}
		else
			if(strcmp(team, "opp") == 0 || strcmp(team, pInfo->get_opp_team_name()) == 0)
			{
				side = (pInfo->get_init_side() == S_Left) ? 'r' : 'l';
			}
			else
				if (strcmp(team, "l") == 0 || strcmp(team, "left") == 0)
				{
					side = 'l';
				}
				else
					if(strcmp(team, "r") == 0 || strcmp(team, "right") == 0)
					{
						side = 'r';
					}
					else
						{
							#ifdef CREATE_GAME_LOG_FILE
							if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Attention_To command has incorrect 'team' parameter!\n", pTime->get_time());
							#endif
				
							return FALSE;
						}

		if (unum < 1 || unum > TEAM_PLAYERS_MAX)
		{
			#ifdef CREATE_GAME_LOG_FILE
			if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Attention_To command has incorrect 'unum' parameter!\n", pTime->get_time());
			#endif
			
			return FALSE;
		}
	}

	if (pBasicCommands->send_com_attention_to(pSocket->get_socket(), team, unum))
	{
		m_CommandsCounter.attentionToCounter++;

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_COMMANDS_COUNTER && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Attention_To counter = %d\n", pTime->get_time(), m_CommandsCounter.attentionToCounter);
		#endif

		add_command(pTime->get_time(), Com_Attention_To, side, unum);

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Attention_To : team = %s unum = %d\n", pTime->get_time(), team, unum);
		#endif

		return TRUE;
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Attention_To command not succeds!\n", pTime->get_time());
		#endif

		return FALSE;
	}
}


int COxsyCommandsList::Tackle(double power) 
{
	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();
	COxsyUtility *pUtility = m_pClassPointers->GetUtilityPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	#endif

	power = pUtility->normalized_power(power);

	if (pBasicCommands->send_com_tackle(pSocket->get_socket(), power))
	{
		m_CommandsCounter.tackleCounter++;

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_COMMANDS_COUNTER && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Tackle counter = %d\n", pTime->get_time(), m_CommandsCounter.tackleCounter);
		#endif

		add_command(pTime->get_time(), Com_Tackle, power, 0.0);

		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Tackle : power = %lf\n", pTime->get_time(), power);
		#endif

		return TRUE;
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Tackle command not succeds!\n", pTime->get_time());
		#endif

		return FALSE;
	}
}


// (ear ({on|off} [TEAM] [TYPE]))
// TEAM is "our", "opp", "left", "l", "right", "r" or the team name of a team.
// If TEAM is omitted, the message will apply to messages from both teams.
// TYPE is used to specify the type of audio, where "complete" or "c" is used to
// specify messages which contain the audio data and "partial" or "p" is used to
// specify messages which do not contain audio data.  If TYPE is not specified,
// the message will apply to both types.

// For example:

// '(ear (on))' enables all audio.
// '(ear (off partial))' disables '(hear time TEAM [UNUM])' messages.
// '(ear (on our complete))' enables '(hear time TEAM [UNUM] "message")'
//  messages from the players team mates.
// '(ear (off opp))' disables all audio from opponent players.

int COxsyCommandsList::Ear(char *mode, char *team, char *type)
{
	COxsyBasicCommands *pBasicCommands = m_pClassPointers->GetBasicCommandsPointer();
	COxsyInfo *pInfo = m_pClassPointers->GetInfoPointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();

	#ifdef CREATE_GAME_LOG_FILE
	COxsyLogger *pLogger = m_pClassPointers->GetLoggerPointer();
	COxsyTime *pTime = m_pClassPointers->GetTimePointer();
	#endif

	if ((strcmp(mode, "on") != 0 && strcmp(mode, "off") != 0) ||
		(strcmp(team, "our") != 0 && strcmp(team, pInfo->get_our_team_name()) != 0 &&
		 strcmp(team, "l") != 0 && strcmp(team, "left") != 0 &&
		 strcmp(team, "opp") != 0 && strcmp(team, pInfo->get_opp_team_name()) != 0 &&
		 strcmp(team, "r") != 0 && strcmp(team, "right") != 0 &&
		 strcmp(team, "") != 0) ||
		(strcmp(type, "p") != 0 && strcmp(type, "partial") != 0 &&
		 strcmp(type, "c") != 0 && strcmp(type, "complete") != 0 &&
		 strcmp(type, "") != 0))
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Ear command has incorrect parameters!\n", pTime->get_time());
		#endif

		return FALSE;
	}

	if (pBasicCommands->send_com_ear(pSocket->get_socket(), mode, team, type))
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Ear : mode = %s team = %s type = %s\n", pTime->get_time(), mode, team, type);
		#endif
		
		return TRUE;
	}
	else
	{
		#ifdef CREATE_GAME_LOG_FILE
		if (LOG_OUT && pLogger->GetFileHandler()) fprintf(pLogger->GetFileHandler(), "%d Ear command not succeds!\n", pTime->get_time());
		#endif
		
		return FALSE;
	}
}
