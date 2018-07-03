#ifndef __SCOREINFO_H__
#define __SCOREINFO_H__


class COxsyClassPointers;
class COxsyScoreInfo
{

public:

	COxsyScoreInfo(COxsyClassPointers *pClassPointers);
	virtual ~COxsyScoreInfo();

//	members functions

	void init_score_info(void);

	void set_our_score_info(int our_score, int our_score_time) { m_score_info.our_score = our_score; m_score_info.our_score_time = our_score_time; }
	void set_opp_score_info(int opp_score, int opp_score_time) { m_score_info.opp_score = opp_score; m_score_info.opp_score_time = opp_score_time; }
	void set_score_info(ScoreInfo score_info) { m_score_info = score_info; }
	ScoreInfo get_score_info(void) { return m_score_info; }

protected:

//	members variables

	COxsyClassPointers *m_pClassPointers;
	ScoreInfo m_score_info;
};


#endif // __SCOREINFO_H__
