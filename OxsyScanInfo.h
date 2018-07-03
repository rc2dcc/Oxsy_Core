#ifndef __SCANINFO_H__
#define __SCANINFO_H__


class COxsyClassPointers;
class COxsyScanInfo
{

public:

	COxsyScanInfo(COxsyClassPointers *pClassPointers);
	virtual ~COxsyScanInfo();

//	members functions

	bool scan_info(char *buffer, SensorInfo *sinfo, char *teamname);
	bool scan_visual_info(char *buffer, SeeInfo *sinfo, char *teamname);
	void rescan_visual_info(SeeInfo *sinfo);
	bool scan_auditorial_info(char *buffer, HearInfo *hinfo);
	bool scan_sensebody_info(char *buffer, SenseBodyInfo *sbinfo);
	bool scan_fullstate_info(char *buffer, FullStateInfo *fsinfo);
	bool scan_score_info(char *buffer);
	bool scan_change_player_type_info(char *buffer);

	char *next_token(char *buf);
	char *next_token(char *buf, char *separators);
	SenderType GetSender(char *buffer);

protected:

//	members variables

	COxsyClassPointers *m_pClassPointers;

};


#endif // __SCANINFO_H__
