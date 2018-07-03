#include "OxsyLibrary.h"
#include "OxsyBasicCommands.h"
#include "OxsyClassPointers.h"

#include "OxsyInfo.h"
#include "OxsyParameters.h"
#include "OxsyPlayMode.h"
#include "OxsySocket.h"
#include "OxsySocketCommands.h"

#ifndef WIN32 // _LINUX
#include <unistd.h>
#endif

COxsyBasicCommands::COxsyBasicCommands(COxsyClassPointers *pClassPointers)
{
	m_pClassPointers = pClassPointers;
}


COxsyBasicCommands::~COxsyBasicCommands()
{

}


InitInfo COxsyBasicCommands::send_com_init(char *teamname, double version, bool goalie)
{
	COxsyInfo *pInfo = m_pClassPointers->GetInfoPointer();
	COxsyParameters *pParameters = m_pClassPointers->GetParametersPointer();
	COxsyPlayMode *pPlayMode = m_pClassPointers->GetPlayModePointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();

	InitInfo info;
	Socket sock;
	char msg_buf[BUFFER_SIZE_MAX / 64], command[BUFFER_SIZE_MAX / 256], side;
	int nTry;
	int nTryMax;
	
	sock = pSocketCommands->init_connection(pInfo->get_server_ip(), pInfo->get_server_port());

	if (sock.socketfd == SOCKET_ERROR)
	{
		info.side = S_Unknown;
		info.number = UNKNOWN_NUMBER;
		info.playMode = PM_Unknown;
		strcpy(info.strPlayMode, UNKNOWN_NAME);
		return info;
	}
	else
	{
		pSocket->set_socket(sock);
	}

    if(goalie)
	{
		sprintf(msg_buf, "(init %s (version %3.2f) (goalie))", teamname, version);
	} 
	else 
	{
		sprintf(msg_buf, "(init %s (version %3.2f))", teamname, version);
	}

	if (!pSocketCommands->send_message(pSocket->get_socket(), msg_buf)) 
	{
		info.side = S_Unknown;
		info.number = UNKNOWN_NUMBER;
		info.playMode = PM_Unknown;
		strcpy(info.strPlayMode, UNKNOWN_NAME);
		return info;
	}
	
	/* wait for reply */
	nTry = 0;
	nTryMax = pParameters->get_simulation_step() / SLEEP_TIME * CYCLES;

	while(!pSocketCommands->receive_message(pSocket->get_socket(), msg_buf, BUFFER_SIZE_MAX / 64))
	{
		nTry++;

		if (nTry > nTryMax)
		{
			info.side = S_Unknown;
			info.number = UNKNOWN_NUMBER;
			info.playMode = PM_Unknown;
			strcpy(info.strPlayMode, UNKNOWN_NAME);
			return info;
		}

		#ifdef WIN32
			Sleep(SLEEP_TIME);
		#else // _LINUX
			usleep(SLEEP_TIME * 1000);
		#endif
	}
		
	sscanf(msg_buf, "(%s ", command);

	if (!strcmp(command, "init")) 
	{
		sscanf(msg_buf, "(init %c %d %s)", &side, &info.number, info.strPlayMode); 
		if (side == 'l')
		{
			info.side = S_Left;
		}
		else
			if (side == 'r')
			{
				info.side = S_Right;
			}

		info.strPlayMode[strlen(info.strPlayMode) - 1] = '\0';
		info.playMode = pPlayMode->get_play_mode(info.strPlayMode);
	}
	else 
	{
		info.side = S_Unknown;
		info.number = UNKNOWN_NUMBER;
		info.playMode = PM_Unknown;
		strcpy(info.strPlayMode, UNKNOWN_NAME);
	}
	
	return info;
}


InitInfo COxsyBasicCommands::send_com_reconnect(char *teamname, int unum)
{
	COxsyPlayMode *pPlayMode = m_pClassPointers->GetPlayModePointer();
	COxsySocket *pSocket = m_pClassPointers->GetSocketPointer();
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();
	COxsyInfo *pInfo = m_pClassPointers->GetInfoPointer();
	COxsyParameters *pParameters = m_pClassPointers->GetParametersPointer();
	
	InitInfo info;
	Socket sock;
	char msg_buf[BUFFER_SIZE_MAX / 128], command[BUFFER_SIZE_MAX / 256], side;
	int i;
	int nTry;
	int nTryMax;
	
	sock = pSocketCommands->init_connection(pInfo->get_server_ip(), pInfo->get_server_port());

	if (sock.socketfd == SOCKET_ERROR)
	{
		info.side = S_Unknown;
		info.number = UNKNOWN_NUMBER;
		info.playMode = PM_Unknown;
		strcpy(info.strPlayMode, UNKNOWN_NAME);
		return info;
	}
	else
	{
		pSocket->set_socket(sock);
	}

	sprintf(msg_buf, "(reconnect %s %d)", teamname, unum);

	if (!pSocketCommands->send_message(pSocket->get_socket(), msg_buf)) 
	{
		info.side = S_Unknown;
		info.number = UNKNOWN_NUMBER;
		info.playMode = PM_Unknown;
		strcpy(info.strPlayMode, UNKNOWN_NAME);
		return info;
	}
	
	/* wait for reply */
	nTry = 0;
	nTryMax = pParameters->get_simulation_step() / SLEEP_TIME * CYCLES;

	while(!pSocketCommands->receive_message(pSocket->get_socket(), msg_buf, BUFFER_SIZE_MAX / 128))
	{
		nTry++;

		if (nTry > nTryMax)
		{
			info.side = S_Unknown;
			info.number = UNKNOWN_NUMBER;
			info.playMode = PM_Unknown;
			strcpy(info.strPlayMode, UNKNOWN_NAME);
			return info;
		}

		#ifdef WIN32
			Sleep(SLEEP_TIME);
		#else // _LINUX
			usleep(SLEEP_TIME * 1000);
		#endif
	}

	sscanf(msg_buf, "(%s ", command);

	if (!strcmp(command, "reconnect")) 
	{
		sscanf(msg_buf, "(reconnect %c %s)", &side, info.strPlayMode); 
		if (side == 'l')
		{
			info.side = S_Left;
		}
		else 
			if (side == 'r')
			{
				info.side = S_Right;
			}

		for(i = 0; info.strPlayMode[i] != ')'; i++);

		info.strPlayMode[i] = '\0';
		info.playMode = pPlayMode->get_play_mode(info.strPlayMode);
		info.number = pInfo->get_unum();
	}
	else
	{
		info.side = S_Unknown;
		info.number = UNKNOWN_NUMBER;
		info.playMode = PM_Unknown;
		strcpy(info.strPlayMode, UNKNOWN_NAME);
	}
	
	return info;
}


int COxsyBasicCommands::send_com_move(Socket *sock, double x, double y)
{
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();

	char msg_buf[BUFFER_SIZE_MAX / 128] ;
	
	sprintf(msg_buf, "(move %.1f %.1f)", x, y);
	if (!pSocketCommands->send_message(sock, msg_buf))
	{
		return FALSE;
	}
	
	return TRUE;
}


int COxsyBasicCommands::send_com_turn(Socket *sock, double moment)
{
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();

	char msg_buf[BUFFER_SIZE_MAX / 256];
	
	sprintf(msg_buf, "(turn %.1f)", moment);
	if (!pSocketCommands->send_message(sock, msg_buf))
	{
		return FALSE;
	}
	
	return TRUE;
}


int COxsyBasicCommands::send_com_dash(Socket *sock, double power)
{
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();

	char msg_buf[BUFFER_SIZE_MAX / 256];

	sprintf(msg_buf, "(dash %.1f)", power);
	if (!pSocketCommands->send_message(sock, msg_buf))
	{
		return FALSE;
	}

	return TRUE;
}


int COxsyBasicCommands::send_com_kick(Socket *sock, double power, double dir)
{
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();

	char msg_buf[BUFFER_SIZE_MAX / 128];

	sprintf(msg_buf, "(kick %.1f %.1f)", power, dir);
	if (!pSocketCommands->send_message(sock, msg_buf))
	{
		return FALSE;
	}

	return TRUE;
}


int COxsyBasicCommands::send_com_score(Socket *sock)
{
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();

	char msg_buf[BUFFER_SIZE_MAX / 256];

	sprintf(msg_buf, "(score)");
	if (!pSocketCommands->send_message(sock, msg_buf))
	{
		return FALSE;
	}

	return TRUE;
}


int COxsyBasicCommands::send_com_say(Socket *sock, char *message)
{
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();

	char msg_buf[BUFFER_SIZE_MAX / 4];

	sprintf(msg_buf, "(say %s)", message);
	if (!pSocketCommands->send_message(sock, msg_buf))
	{
		return FALSE;
	}

	return TRUE;
}


int COxsyBasicCommands::send_com_change_view(Socket *sock, ViewWidth width, ViewQuality quality)
{
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();

	char msg_buf[BUFFER_SIZE_MAX / 128], w_str[8], q_str[8];

	switch (width) 
	{
		case VW_Narrow:
			strcpy(w_str, "narrow");
			break;
		case VW_Normal:
			strcpy(w_str, "normal");
			break;
		case VW_Wide:
			strcpy(w_str, "wide");
			break;
		default:
			return FALSE;
	}

	switch (quality) 
	{
		case VQ_High:
			strcpy(q_str, "high");
			break;
		case VQ_Low:
			strcpy(q_str, "low");
			break;
		default:
			return FALSE;
	}

	sprintf(msg_buf, "(change_view %s %s)", w_str, q_str);
	if (!pSocketCommands->send_message(sock, msg_buf))
	{
		return FALSE;
	}

	return TRUE;
}


int COxsyBasicCommands::send_com_sense_body(Socket *sock)
{
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();

	char msg_buf[BUFFER_SIZE_MAX / 256];

	sprintf(msg_buf, "(sense_body)");
	if (!pSocketCommands->send_message(sock, msg_buf))
	{
		return FALSE;
	}

	return TRUE;
}


int COxsyBasicCommands::send_com_catch(Socket *sock, double dir)
{
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();

	char msg_buf[BUFFER_SIZE_MAX / 256];

	sprintf(msg_buf, "(catch %.1f)", dir);
	if (!pSocketCommands->send_message(sock, msg_buf))
	{
		return FALSE;
	}

	return TRUE;
}


int COxsyBasicCommands::send_com_bye(Socket *sock)
{
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();

	char msg_buf[BUFFER_SIZE_MAX / 512];

	sprintf(msg_buf, "(bye)");
	if (!pSocketCommands->send_message(sock, msg_buf))
	{
		return FALSE;
	}

	return TRUE;
}


int COxsyBasicCommands::send_com_turn_neck(Socket *sock, double dir)
{
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();

	char msg_buf[BUFFER_SIZE_MAX / 128];

	sprintf(msg_buf, "(turn_neck %.1f)", dir);
	if (!pSocketCommands->send_message(sock, msg_buf))
	{
		return FALSE;
	}

	return TRUE;
}


int COxsyBasicCommands::send_com_look(Socket *sock)
{ 
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();
	char msg_buf[BUFFER_SIZE_MAX / 512];

	sprintf(msg_buf, "(look)");
	if (!pSocketCommands->send_message(sock, msg_buf))
	{
		return FALSE;
	}

	return TRUE;
}


int COxsyBasicCommands::send_com_eye(Socket *sock, bool onp)
{
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();
	char msg_buf[BUFFER_SIZE_MAX / 256];

	if (onp) 
	{
		sprintf(msg_buf, "(eye on)");
		if (!pSocketCommands->send_message(sock, msg_buf))
		{
			return FALSE;
		}
	} 
	else 
	{
		sprintf(msg_buf, "(eye off)");
		if (!pSocketCommands->send_message(sock, msg_buf))
		{
			return FALSE;
		}
	}

	return TRUE;
}


int COxsyBasicCommands::send_com_point_to(Socket *sock, double dist, double dir)
{
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();
	char msg_buf[BUFFER_SIZE_MAX / 128];

	if (dist == 0.0 && dir == 0.0)
	{
		sprintf(msg_buf, "(pointto off)");
	}
	else
	{
		sprintf(msg_buf, "(pointto %.1f %.1f)", dist, dir);
	}

	if (!pSocketCommands->send_message(sock, msg_buf))
	{
		return FALSE;
	}

	return TRUE;
}


// level = -1 ndicate that zlib is not to be used (default) and 0 to 9 indicate 
// levels of compression as per the zlib library.

int COxsyBasicCommands::send_com_compression(Socket *sock, int level)
{
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();

	char msg_buf[BUFFER_SIZE_MAX / 128];

	sprintf(msg_buf, "(compression %d)", level);
	if (!pSocketCommands->send_message(sock, msg_buf))
	{
		return FALSE;
	}

	return TRUE;
}


//  (attentionto <TEAM> <UNUM>) | (attentionto off)
//  Where <TEAM> is : opp | our | l | r | left | right | <TEAM_NAME>
//  and   <UNUM> is integer identifying a member of the team specified

int COxsyBasicCommands::send_com_attention_to(Socket *sock, char *team, int unum)
{
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();
	char msg_buf[BUFFER_SIZE_MAX / 64];

	if (strlen(team) == 0 && unum == 0)
	{
		sprintf(msg_buf, "(attentionto off)");
	}
	else
	{
		sprintf(msg_buf, "(attentionto %s %d)", team, unum);
	}

	if (!pSocketCommands->send_message(sock, msg_buf))
	{
		return FALSE;
	}

	return TRUE;
}


int COxsyBasicCommands::send_com_tackle(Socket *sock, double power)
{
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();

	char msg_buf[BUFFER_SIZE_MAX / 256];

	sprintf(msg_buf, "(tackle %.1f)", power);
	if (!pSocketCommands->send_message(sock, msg_buf))
	{
		return FALSE;
	}

	return TRUE;
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

int COxsyBasicCommands::send_com_ear(Socket *sock, char *mode, char *team, char *type)
{
	COxsySocketCommands *pSocketCommands = m_pClassPointers->GetSocketCommandsPointer();

	char msg_buf[BUFFER_SIZE_MAX / 64];

	if (strlen(mode) > 0)
	{
		strcpy(msg_buf, "(ear (");
		strcat(msg_buf, mode);
	}
	else
	{
		return FALSE;
	}

	if (strlen(team) > 0)
	{
		strcat(msg_buf, " ");
		strcat(msg_buf, team);
	}

	if (strlen(type) > 0)
	{
		strcat(msg_buf, " ");
		strcat(msg_buf, type);
	}

	strcat(msg_buf, "))");

	if (!pSocketCommands->send_message(sock, msg_buf))
	{
		return FALSE;
	}

	return TRUE;
}
