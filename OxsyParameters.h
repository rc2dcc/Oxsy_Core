#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__


class COxsyClassPointers;
class COxsyParameters
{

public:

	COxsyParameters(COxsyClassPointers *pClassPointers);
	virtual ~COxsyParameters();

//	memebers functions

	bool GetParameters();

//	server_param
//	double get_inertia_moment(void) { return inertia_moment; }
//	double get_stamina_inc_max(void) { return stamina_inc_max;}
	double get_stamina_max(void) { return stamina_max;}

	double get_recover_min(void) { return recover_min;}
	double get_recover_max(void) { return recover_init;}
	double get_recover_dec(void) { return recover_dec;}
	double get_recover_dec_thr(void) { return recover_dec_thr;}

//	double get_effort_max(void) { return effort_init;}
//	double get_effort_min(void) { return effort_min;}
	double get_effort_dec(void) { return effort_dec;}
	double get_effort_inc(void) { return effort_inc;}
	double get_effort_dec_thr(void) { return effort_dec_thr;}
	double get_effort_inc_thr(void) { return effort_inc_thr;}

//	double get_dash_power_rate(void) { return dash_power_rate; }
	double get_kick_power_rate(void) { return kick_power_rate; }
	double get_player_speed_max (void) { return player_speed_max; }
	double get_ball_speed_max (void) { return ball_speed_max; }
	double get_player_accel_max (void) { return player_accel_max; }
	double get_ball_accel_max (void) { return ball_accel_max; }
//	double get_player_decay (void) { return player_decay; }
	double get_ball_decay (void) { return ball_decay; }

	double get_player_size(void) { return player_size; }
	double get_ball_size(void) { return ball_size; }
//	double get_kickable_margin(void) { return kickable_margin; }
	double get_collision_area(void) { return collision_area; }
//	double get_middle_area(void) { return middle_area; }
//	double get_kickable_area(void) { return kickable_area; }
	double get_corner_kick_margin(void) { return ckick_margin; }

	int get_receive_step(void) { return recv_step; }
	int get_send_step(void) { return send_step; }
	int get_send_vi_step(void) { return send_vi_step; }
	int get_sensebody_step (void) { return sense_body_step; }
	int get_simulation_step(void) { return simulator_step; }
	int get_slow_down_factor(void) { return slow_down_factor; }

	int get_catch_ban_cycle(void) { return catch_ban_cycle; }
	int get_goalie_max_moves(void) { return goalie_max_moves; }
	double get_catchable_area_l(void) { return catchable_area_l; }
	double get_catchable_area_w(void) { return catchable_area_w; }
	double get_catchable_area(void) { return catchable_area; }

	double get_goal_width(void) { return goal_width; }
	int get_say_msg_size(void) { return say_msg_size; }

	double get_dist_qstep(void) {return quantize_step; }
	double get_land_qstep(void) {return quantize_step_l; }
	
	double get_visible_angle() { return visible_angle; }
	double get_visible_distance() { return visible_distance; }

	double get_tackle_dist(void) { return tackle_dist; }
	double get_tackle_back_dist(void) { return tackle_back_dist; }
	double get_tackle_width(void) { return tackle_width; }
	double get_tackle_exponent(void) { return tackle_exponent; }
	int get_tackle_cycles(void) { return tackle_cycles; }
	double get_tackle_power_rate(void) { return tackle_power_rate; }

	int get_point_to_ban(void) { return point_to_ban; }
	int get_point_to_duration(void) { return point_to_duration; }

	double get_max_moment(void) { return maxmoment; }
	double get_max_neck_ang(void) { return maxneckang; }
	double get_max_neck_moment(void) { return maxneckmoment; }
	double get_max_power(void) { return maxpower; }
	double get_min_moment(void) { return minmoment; }
	double get_min_neck_ang(void) { return minneckang; }
	double get_min_neck_moment(void) { return minneckmoment; }
	double get_min_power(void) { return minpower; }

	int get_nr_normal_halfs(void) { return nr_normal_halfs; }
	int get_nr_extra_halfs(void) { return nr_extra_halfs; }
	int get_half_time(void) { return half_time; }

	double get_audio_cut_dist(void) { return audio_cut_dist; }

//	player_param
	int get_player_types(void) { return player_types; }

//	player_types
	int get_h_id(int index) { return h_id[index]; }

    double get_h_dash_power_rate(int index) { return h_dash_power_rate[index]; }
    double get_h_effort_max(int index) { return h_effort_max[index]; }
    double get_h_effort_min(int index) { return h_effort_min[index]; }
    double get_h_extra_stamina(int index) { return h_extra_stamina[index]; }
    double get_h_inertia_moment(int index) { return h_inertia_moment[index]; }
    double get_h_kick_rand(int index) { return h_kick_rand[index]; }
    double get_h_kickable_margin(int index) { return h_kickable_margin[index]; }
    double get_h_player_decay(int index) { return h_player_decay[index]; }
    double get_h_player_size(int index) { return h_player_size[index]; }
	double get_h_player_speed_max(int index) { return h_player_speed_max[index]; }
    double get_h_stamina_inc_max(int index) { return h_stamina_inc_max[index]; }

	// additional functions
	double get_h_speed_dash_max(int index) { return h_speed_dash_max[index]; }
	double get_h_middle_area(int index) { return h_middle_area[index]; }
	double get_h_kickable_area(int index) { return h_kickable_area[index]; }

protected:

//	members functions

	int GetServerParameters(char *buffer);
	int GetPlayerParameters(char *buffer);
	int GetPlayerTypeParameters(char *buffer, int index);

	void SetDefaultParameters();

	void SetDefaultServerParameters();
	void SetDefaultPlayerParameters();
	void SetDefaultPlayerTypes();

//	members variables

	COxsyClassPointers *m_pClassPointers;

////////////////////////////////// server parameters /////////////////////////////////////

//	int variables
	int catch_ban_cycle;
	int clang_advice_win;
	int clang_define_win;
	int clang_del_win;
	int clang_info_win;
	int clang_mess_delay;
	int clang_mess_per_cycle;
	int clang_meta_win;
	int clang_rule_win;
	int clang_win_size;
	int coach_port;
	int connect_wait;
	int drop_ball_time;
	int freeform_send_period;
	int freeform_wait_period;
	int game_log_compression;
	int game_log_version;
	int game_over_wait;
	int goalie_max_moves;
	int half_time;
	int hear_decay;
	int hear_inc;
	int hear_max;
	int keepaway_start;
	int kick_off_wait;
	int max_goal_kicks;
	int nr_extra_halfs; // server version 9.3.2
	int nr_normal_halfs; // server version 9.3.2
	int olcoach_port;
	int pen_before_setup_wait; // server version 9.3.2
	int pen_max_extra_kicks; // server version 9.3.2
	int pen_nr_kicks; // server version 9.3.2
	int pen_ready_wait; // server version 9.3.2
    int pen_setup_wait; // server version 9.3.2
	int pen_taken_wait; // server version 9.3.2
	int point_to_ban; 
	int point_to_duration;
	int port;
	int recv_step;
	int say_coach_cnt_max;
	int say_coach_msg_size;
	int say_msg_size;
	int send_step;
	int send_vi_step;
	int sense_body_step;
	int simulator_step;
	int slow_down_factor;
	int start_goal_l;
	int start_goal_r;
	int synch_micro_sleep;
	int synch_offset;
	int tackle_cycles;
	int text_log_compression;

//	char variables
	char game_log_dir[FILE_PATH_LENGTH_MAX + 1];
	char game_log_fixed_name[BUFFER_SIZE_MAX / 128 + 1];
	char keepaway_log_dir[FILE_PATH_LENGTH_MAX + 1];
	char keepaway_log_fixed_name[BUFFER_SIZE_MAX / 128 + 1];
	char landmark_file[BUFFER_SIZE_MAX / 128 + 1];
	char log_date_format[BUFFER_SIZE_MAX / 128 + 1];
	char module_dir[FILE_PATH_LENGTH_MAX + 1];
	char team_l_start[BUFFER_SIZE_MAX / 128 + 1];
	char team_r_start[BUFFER_SIZE_MAX / 128 + 1];
	char text_log_dir[FILE_PATH_LENGTH_MAX + 1];
	char text_log_fixed_name[BUFFER_SIZE_MAX / 128 + 1];

//	bool variables
	bool coach;
	bool coach_w_referee;
	bool old_coach_hear;
	bool wind_none;
	bool wind_random;
	bool auto_mode;
	bool back_passes;
	bool forbid_kick_off_offside;
	bool free_kick_faults;
	bool fullstate_l;
	bool fullstate_r;
	bool game_log_dated;
	bool game_log_fixed;
	bool game_logging;
	bool keepaway;
	bool keepaway_log_dated;
	bool keepaway_log_fixed;
	bool keepaway_logging;
	bool log_times;
	bool pen_allow_mult_kicks; // server version 9.3.2
	bool pen_coach_moves_players;
	bool pen_random_winner; // server version 9.3.2
	bool pen_shoot_outs; // server version 9.3.2
	bool profile;
	bool proper_goal_kicks;
	bool record_messages;
	bool send_comms;
	bool synch_mode;
	bool team_actuator_noise;
	bool text_log_dated;
	bool text_log_fixed;
	bool text_logging;
	bool use_offside;
	bool verbose;

//	double variables
	double audio_cut_dist;
	double ball_accel_max;
	double ball_decay;
	double ball_rand;
	double ball_size;
	double ball_speed_max;
	double ball_weight;
	double catch_probability;
	double catchable_area_l;
	double catchable_area_w;
	double ckick_margin;
	double control_radius;
	double dash_power_rate;
	double effort_dec;
	double effort_dec_thr;
	double effort_inc;
	double effort_inc_thr;
	double effort_init; // pms
	double effort_min;
	double goal_width;
	double inertia_moment;
	double keepaway_length;
	double keepaway_width;
	double kick_power_rate;
	double kick_rand;
	double kick_rand_factor_l;
	double kick_rand_factor_r;
	double kickable_margin;
	double maxmoment;
	double maxneckang;
	double maxneckmoment;
	double maxpower;
	double minmoment;
	double minneckang;
	double minneckmoment;
	double minpower;
	double offside_active_area_size;
	double offside_kick_margin;
	double pen_dist_x; // server version 9.3.2
	double pen_max_goalie_dist_x; // server version 9.3.2
	double player_accel_max;
	double player_decay;
	double player_rand;
	double player_size;
	double player_speed_max;
	double player_weight;
	double prand_factor_l;
	double prand_factor_r;
	double quantize_step;
	double quantize_step_l;
	double recover_dec;
	double recover_dec_thr;
	double recover_init; // server version 9.3.2
	double recover_min;
	double slowness_on_top_for_left_team;
	double slowness_on_top_for_right_team;
	double stamina_inc_max;
	double stamina_max;
	double stopped_ball_vel;
	double tackle_back_dist;
	double tackle_dist;
	double tackle_exponent;
	double tackle_power_rate;
	double tackle_width;
	double visible_angle;
	double visible_distance;
	double wind_ang;
	double wind_dir;
	double wind_force;
	double wind_rand;

//	additional double variables
	double team_far_length; // pms
	double team_too_far_length; // pms
    double unum_far_length; // pms
	double unum_too_far_length; // pms

	double collision_area; // pms
	double middle_area; // pms
	double kickable_area; // pms
	double catchable_area; // pms

/////////////////////////////////// player parameters ////////////////////////////////////

//	int variables
	int player_types;
	int pt_max;
	int random_seed;
	int subs_max;
	
//	double variables
	double dash_power_rate_delta_max;
	double dash_power_rate_delta_min;
	double effort_max_delta_factor;
	double effort_min_delta_factor;
	double extra_stamina_delta_max;
	double extra_stamina_delta_min;
	double inertia_moment_delta_factor;
	double kick_rand_delta_factor;
	double kickable_margin_delta_max;
	double kickable_margin_delta_min;
	double new_dash_power_rate_delta_max;
	double new_dash_power_rate_delta_min;
	double new_stamina_inc_max_delta_factor;
	double player_decay_delta_max;
	double player_decay_delta_min;
	double player_size_delta_factor;
	double player_speed_max_delta_max;
	double player_speed_max_delta_min;
	double stamina_inc_max_delta_factor;
	
//////////////////////////////////// player types ////////////////////////////////////////

//	int variables
	int h_id[DEFAULT_PLAYER_TYPES + DEFAULT_ADDITIONAL_TYPES]; // pms

//	double variables
    double h_dash_power_rate[DEFAULT_PLAYER_TYPES + DEFAULT_ADDITIONAL_TYPES];
    double h_effort_max[DEFAULT_PLAYER_TYPES + DEFAULT_ADDITIONAL_TYPES];
    double h_effort_min[DEFAULT_PLAYER_TYPES + DEFAULT_ADDITIONAL_TYPES];
    double h_extra_stamina[DEFAULT_PLAYER_TYPES + DEFAULT_ADDITIONAL_TYPES];
    double h_inertia_moment[DEFAULT_PLAYER_TYPES + DEFAULT_ADDITIONAL_TYPES];
    double h_kick_rand[DEFAULT_PLAYER_TYPES + DEFAULT_ADDITIONAL_TYPES];
    double h_kickable_margin[DEFAULT_PLAYER_TYPES + DEFAULT_ADDITIONAL_TYPES];
    double h_player_decay[DEFAULT_PLAYER_TYPES + DEFAULT_ADDITIONAL_TYPES];
    double h_player_size[DEFAULT_PLAYER_TYPES + DEFAULT_ADDITIONAL_TYPES];
	double h_player_speed_max[DEFAULT_PLAYER_TYPES + DEFAULT_ADDITIONAL_TYPES];
    double h_stamina_inc_max[DEFAULT_PLAYER_TYPES + DEFAULT_ADDITIONAL_TYPES];

//	additional double variables
	double h_speed_dash_max[DEFAULT_PLAYER_TYPES + DEFAULT_ADDITIONAL_TYPES];
	double h_middle_area[DEFAULT_PLAYER_TYPES + DEFAULT_ADDITIONAL_TYPES];
	double h_kickable_area[DEFAULT_PLAYER_TYPES + DEFAULT_ADDITIONAL_TYPES];

//////////////////////////////////////////////////////////////////////////////////////////
};


#endif // __PARAMETERS_H__
