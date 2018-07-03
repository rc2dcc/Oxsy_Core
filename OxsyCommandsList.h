#ifndef __COMMANDSLIST_H__
#define __COMMANDSLIST_H__


class COxsyClassPointers;
class COxsyCommandsList
{

public:

	COxsyCommandsList(COxsyClassPointers *pClassPointers);
	virtual ~COxsyCommandsList();

//	members functions

	void init_commands_counter(void);
	void init_commands_list(void);
	void add_command(int time, CommandName commandName, double p1, double p2);

	int Catch(double dir);
	int Dash(double power); 
	int Kick(double power, double dir); 
	int Move(double x, double y); 
	int Tackle(double power);
	int Turn(double dir); 

	int Attention_To_Off(void);
	int Attention_To(char *team, int unum);
	int Change_View(ViewWidth width, ViewQuality quality);
	int Ear(char *mode, char *team = "", char *type = "");
	int Point_To_Off(void);
	int Point_To(double dist, double dir);
	int Say(char *message); 
	int Sense_Body(void);
	int Score(void);
	int Turn_Neck(double dir);

	int Bye(void);
	int Compression(int level);
	InitInfo Init(char *teamname, double version, bool goalie);
	InitInfo Reconnect(char *teamname, int unum);

	int Eye(bool onp);
	int Look(void);

protected:

//	members variables

	COxsyClassPointers *m_pClassPointers;
	Command m_Command[COMMANDS_LIST_SIZE];
	CommandsCounter m_CommandsCounter;
	int m_nIndex;
};


#endif // __COMMANDSLIST_H__
