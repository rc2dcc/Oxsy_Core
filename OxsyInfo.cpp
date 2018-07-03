#include "OxsyLibrary.h"
#include "OxsyInfo.h"
#include "OxsyClassPointers.h"


COxsyInfo::COxsyInfo(COxsyClassPointers *pClassPointers)
{
	m_pClassPointers = pClassPointers;

	init_info();
}


COxsyInfo::~COxsyInfo()
{

}


void COxsyInfo::init_info()
{
	m_stamina = DEFAULT_STAMINA_MAX;
	m_effort = DEFAULT_EFFORT_MAX;
	m_recovery = DEFAULT_RECOVER_INIT;

	m_match_state = MS_First_Half;

	m_init_side = S_Unknown;
	m_self_number = UNKNOWN_NUMBER;
	m_player_type = PT_Unknown;

	m_head_angle = 0.0;
	m_speed_value = 0.0;
}


void COxsyInfo::init_player_state()
{
	m_stamina = DEFAULT_STAMINA_MAX;
	m_effort = DEFAULT_EFFORT_MAX;
	m_recovery = DEFAULT_RECOVER_INIT;
}
