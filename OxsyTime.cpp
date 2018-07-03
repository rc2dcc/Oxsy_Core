#include "OxsyLibrary.h"
#include "OxsyTime.h"
#include "OxsyClassPointers.h"


COxsyTime::COxsyTime(COxsyClassPointers *pClassPointers)
{
	m_pClassPointers = pClassPointers;
	init_time();
}


COxsyTime::~COxsyTime()
{

}


void COxsyTime::init_time()
{
	m_time = 0;
}
