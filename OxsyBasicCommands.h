#ifndef __BASICCOMMANDS_H__
#define __BASICCOMMANDS_H__


class COxsyClassPointers;
class COxsyBasicCommands
{

public:

	COxsyBasicCommands(COxsyClassPointers *pClassPointers);
	virtual ~COxsyBasicCommands();

//	members functions

	int send_com_catch(Socket *sock, double dir);
	int send_com_dash(Socket *sock, double power);
	int send_com_kick(Socket *sock, double power, double dir);
	int send_com_move(Socket *sock, double x, double y);
	int send_com_tackle(Socket *sock, double power);
	int send_com_turn(Socket *sock, double moment);

	int send_com_attention_to(Socket *sock, char *team, int unum);
	int send_com_change_view(Socket *sock, ViewWidth width, ViewQuality quality);
	int send_com_ear(Socket *sock, char *mode, char *team, char *type);
	int send_com_point_to(Socket *sock, double dist, double dir);
	int send_com_say(Socket *sock, char *message);
	int send_com_score(Socket *sock);
	int send_com_sense_body(Socket *sock);
	int send_com_turn_neck(Socket *sock, double dir);

	int send_com_bye(Socket *sock);
	int send_com_compression(Socket *sock, int level);
	InitInfo send_com_init(char *teamname, double version, bool goalie);
	InitInfo send_com_reconnect(char *teamname, int unum);

	int send_com_eye(Socket *sock, bool onp);
	int send_com_look(Socket *sock);


protected:

//	members variables

	COxsyClassPointers *m_pClassPointers;


};


#endif // __BASICCOMMANDS_H__
