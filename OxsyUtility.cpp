#include "OxsyLibrary.h"
#include "OxsyUtility.h"
#include "OxsyClassPointers.h"

#include "OxsyInfo.h"
#include "OxsyParameters.h"


COxsyUtility::COxsyUtility(COxsyClassPointers *pClassPointers)
{
	m_pClassPointers = pClassPointers;
}


COxsyUtility::~COxsyUtility()
{

}


double COxsyUtility::normalized_stamina(double s) 
{
	COxsyParameters *pParameters = m_pClassPointers->GetParametersPointer();

	return Max(Min(s, pParameters->get_stamina_max()), 0.0);
}


void COxsyUtility::normalized_dash_speed_and_dash_power(PlayerType player_type, double *player_dash_speed, double *player_dash_power)
{
	COxsyParameters *pParameters = m_pClassPointers->GetParametersPointer();
  
	if (*player_dash_speed > pParameters->get_h_player_speed_max((int)player_type))
	{
		*player_dash_power -= ((*player_dash_speed - pParameters->get_h_player_speed_max((int)player_type)) / (pParameters->get_h_dash_power_rate((int)player_type) * pParameters->get_h_effort_max((int)player_type)));
		*player_dash_speed = pParameters->get_h_player_speed_max((int)player_type);
	}
}


double COxsyUtility::normalized_dir(double dir) 
{
	COxsyParameters *pParameters = m_pClassPointers->GetParametersPointer();

//	return Max(Min(dir, pParameters->get_max_moment()), pParameters->get_min_moment());

	if (dir > pParameters->get_max_moment())
	{
		return pParameters->get_max_moment();
	}
	else
		if (dir < pParameters->get_min_moment())
		{
			return pParameters->get_min_moment();
		}

	return dir;
}


Pos COxsyUtility::normalized_pos_inside_pitch(Pos pos)
{
	pos.x = normalized_pos_x_inside_pitch(pos.x);
	pos.y = normalized_pos_y_inside_pitch(pos.y);

	return pos;
}


double COxsyUtility::normalized_pos_x_inside_pitch(double x) 
{
//	return Max(Min(x, HALF_PITCH_LENGTH), -HALF_PITCH_LENGTH);

	if(x > HALF_PITCH_LENGTH)
	{
		return HALF_PITCH_LENGTH;
	}
	else
		if (x < -HALF_PITCH_LENGTH) 
		{
			return -HALF_PITCH_LENGTH;
		}
	
	return x;
}


double COxsyUtility::normalized_pos_y_inside_pitch(double y) 
{
//	return Max(Min(y, HALF_PITCH_WIDTH), -HALF_PITCH_WIDTH);

	if(y > HALF_PITCH_WIDTH)
	{
		return HALF_PITCH_WIDTH;
	}
	else
		if (y < -HALF_PITCH_WIDTH)
		{
			return -HALF_PITCH_WIDTH;
		}

	return y;
}


double COxsyUtility::normalized_power(double power) 
{
	COxsyParameters *pParameters = m_pClassPointers->GetParametersPointer();

//	return Max(Min(power, pParameters->get_max_power()), pParameters->get_min_power());

	if (power > pParameters->get_max_power())
	{
		return pParameters->get_max_power();
	}
	else
		if (power < pParameters->get_min_power())
		{
			return pParameters->get_min_power();
		}

	return power;
}


double COxsyUtility::normalized_turn_neck_dir(double dir)
{
	COxsyInfo *pInfo = m_pClassPointers->GetInfoPointer();
	COxsyParameters *pParameters = m_pClassPointers->GetParametersPointer();

	if (pInfo->get_head_angle() + dir  > pParameters->get_max_neck_ang()) 
	{
		return sub_dir(pParameters->get_max_neck_ang(), pInfo->get_head_angle());
	}
	else
		if (pInfo->get_head_angle() + dir < pParameters->get_min_neck_ang())
		{
			return sub_dir(pParameters->get_min_neck_ang(), pInfo->get_head_angle());
		}

	return dir;
}


double COxsyUtility::add_dir(double d1, double d2) 
{
    d1 += d2;    
    return normalize_dir(d1);
}


double COxsyUtility::sub_dir(double d1, double d2) 
{
    d1 -= d2;
    return normalize_dir(d1);
}


double COxsyUtility::normalize_dir(double dir)
{
	COxsyParameters *pParameters = m_pClassPointers->GetParametersPointer();

    while (TRUE) 
	{
        if (dir > pParameters->get_max_moment()) 
		{
            dir -= (pParameters->get_max_moment() * 2.0);
        } 
		else 
			if (dir < pParameters->get_min_moment()) 
			{
				dir -= (pParameters->get_min_moment() * 2.0);
			} 
			else 
			{
				return dir;
			}
    }
}
