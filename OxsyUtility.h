#ifndef __UTILITY_H__
#define __UTILITY_H__


class COxsyClassPointers;
class COxsyUtility
{

public:

	COxsyUtility(COxsyClassPointers *pClassPointers);
	virtual ~COxsyUtility();

//	members functions

	double	normalized_dir(double dir);
	Pos		normalized_pos_inside_pitch(Pos pos);
	double	normalized_pos_x_inside_pitch(double x);
	double	normalized_pos_y_inside_pitch(double y);
	double	normalized_power(double power);
	double	normalized_stamina(double s);
	double	normalized_turn_neck_dir(double dir);
	void	normalized_dash_speed_and_dash_power(PlayerType player_type, double *player_dash_speed, double *player_dash_power);

	double	normalize_dir(double dir);

	double	add_dir(double d1, double d2);
	double	sub_dir(double d1, double d2);

protected:

//	members variables

	COxsyClassPointers *m_pClassPointers;

};


#endif // __UTILITY_H__
