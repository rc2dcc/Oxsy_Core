#include "OxsyLibrary.h"
#include "OxsySensorInfo.h"
#include "OxsyClassPointers.h"


COxsySensorInfo::COxsySensorInfo(COxsyClassPointers *pClassPointers)
{
	m_pClassPointers = pClassPointers;
	init_sensor_info();
}


COxsySensorInfo::~COxsySensorInfo()
{

}


void COxsySensorInfo::init_sensor_info()
{
	m_hear.time = UNKNOWN_TIME;
	m_sensebody.time = UNKNOWN_TIME;
	m_see.time = UNKNOWN_TIME;
	m_fullstate.time = UNKNOWN_TIME;

	m_bReceivedHearInfo = false;
	m_bReceivedSenseBodyInfo = false;
	m_bReceivedSeeInfo = false;
	m_bReceivedFullStateInfo = false;
}
