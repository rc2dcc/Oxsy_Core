#include "OxsyLibrary.h"
#include "OxsyScoreInfo.h"
#include "OxsyClassPointers.h"


COxsyScoreInfo::COxsyScoreInfo(COxsyClassPointers *pClassPointers)
{
	m_pClassPointers  = pClassPointers;
	init_score_info();
}


COxsyScoreInfo::~COxsyScoreInfo()
{

}


void COxsyScoreInfo::init_score_info()
{
	// our score
	m_score_info.our_score_time = 0;
	m_score_info.our_score = 0;

	// opp score
	m_score_info.opp_score_time = 0;
	m_score_info.opp_score = 0;
}
