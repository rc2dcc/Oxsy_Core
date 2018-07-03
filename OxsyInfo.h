#ifndef __INFO_H__
#define __INFO_H__


class COxsyClassPointers;
class COxsyInfo
{

public:

	COxsyInfo(COxsyClassPointers *pClassPointers);
	virtual ~COxsyInfo();

//  members functions

	void init_info(void);

	void set_our_team_name(char *our_team_name) { strncpy(m_our_team_name, our_team_name, TEAM_NAME_LENGTH_MAX); m_our_team_name[TEAM_NAME_LENGTH_MAX] = '\0'; }
	char *get_our_team_name(void) { return m_our_team_name; }

	void set_our_team_name_with_quotes(char *our_team_name_with_quotes) { strcpy(m_our_team_name_with_quotes, QUOTES); strncat(m_our_team_name_with_quotes, our_team_name_with_quotes, TEAM_NAME_LENGTH_MAX); strcat(m_our_team_name_with_quotes, QUOTES); }
	char *get_our_team_name_with_quotes(void) { return m_our_team_name_with_quotes; }

	void set_opp_team_name(char *opp_team_name) { strncpy(m_opp_team_name, opp_team_name, TEAM_NAME_LENGTH_MAX); m_opp_team_name[TEAM_NAME_LENGTH_MAX] = '\0'; }
	char *get_opp_team_name(void) { return m_opp_team_name; }

	void set_server_ip(char *server_ip) { strncpy(m_server_ip, server_ip, BUFFER_SIZE_MAX / 256); m_server_ip[BUFFER_SIZE_MAX / 256] = '\0';}
	char *get_server_ip(void) { return m_server_ip; }

	void set_server_port(int sp) { m_server_port = sp; }
	int get_server_port(void) { return m_server_port; }

	void set_game_log_file_path(char *game_log_file_path) { strncpy(m_game_log_file_path, game_log_file_path, FILE_PATH_LENGTH_MAX); m_game_log_file_path[FILE_PATH_LENGTH_MAX] = '\0'; }
	char *get_game_log_file_path(void) { return m_game_log_file_path; }

	void set_server_version(double server_version) { m_server_version = server_version; }
	double get_server_version(void) { return m_server_version; }

	void set_init_side(Side init_side) { m_init_side = init_side; }
	Side get_init_side(void) { return m_init_side; }

	void set_unum(int self_number) { m_self_number = self_number; }
	int get_unum(void) { return m_self_number; }

	void set_player_type(PlayerType player_type) { m_player_type = player_type; }
	PlayerType get_player_type(void) { return m_player_type; }

	void init_player_state(void);

	void init_match_state(void) { m_match_state = MS_First_Half; }
	void inc_match_state(void) { ++m_match_state %= 2; }
	int get_match_state(void) { return m_match_state; }

	void set_stamina(double stamina) { m_stamina = stamina; }
	double get_stamina(void) { return m_stamina; }

	void set_effort(double effort) { m_effort = effort; }
	double get_effort(void) { return m_effort; }

	void set_recovery(double recovery) { m_recovery = recovery; }
	double get_recovery(void) { return m_recovery; }

	void set_head_angle(double head_angle) { m_head_angle = head_angle; }
	double get_head_angle(void) { return m_head_angle; }

	void set_speed_value(double speed_value) { m_speed_value = speed_value; }
	double get_speed_value(void) { return m_speed_value; }

protected:

//  members variables

	COxsyClassPointers *m_pClassPointers;

	int m_match_state;

	double m_effort;
	double m_recovery;
	double m_stamina;
	double m_server_version;

	double m_head_angle;
	double m_speed_value;

	int m_server_port;

	char m_game_log_file_path[FILE_PATH_LENGTH_MAX + 1];
	char m_our_team_name[TEAM_NAME_LENGTH_MAX + 1];
	char m_our_team_name_with_quotes[TEAM_NAME_LENGTH_MAX + 2 + 1];
	char m_opp_team_name[TEAM_NAME_LENGTH_MAX + 1];
	char m_server_ip[BUFFER_SIZE_MAX / 256 + 1];

	Side m_init_side;
	int m_self_number;
	PlayerType m_player_type;
};


#endif // __INFO_H__
