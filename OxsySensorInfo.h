#ifndef __SENSORINFO_H__
#define __SENSORINFO_H__


class COxsyClassPointers;
class COxsySensorInfo
{

public:

	COxsySensorInfo(COxsyClassPointers *pClassPointers);
	virtual ~COxsySensorInfo();

//	members functions

	void init_sensor_info(void);

	void set_hear_info(HearInfo hear) { m_hear = hear; }
	void set_sense_body_info(SenseBodyInfo sensebody) { m_sensebody = sensebody; }
	void set_see_info(SeeInfo see) { m_see = see; }
	void set_fullstate_info(FullStateInfo fullstate) { m_fullstate = fullstate; }

	HearInfo *get_hear_info(void) { return &m_hear; }
	SenseBodyInfo *get_sensebody_info(void) { return &m_sensebody; }
	SeeInfo *get_see_info(void) { return &m_see; }
	FullStateInfo *get_fullstate_info(void) { return &m_fullstate; }

	void reset_hear_info_time(void) { m_hear.time = UNKNOWN_TIME; }
	void reset_sensebody_info_time(void) { m_sensebody.time = UNKNOWN_TIME; }
	void reset_see_info_time(void) { m_see.time = UNKNOWN_TIME; }
	void reset_fullstate_info_time(void) { m_fullstate.time = UNKNOWN_TIME; }

	int get_hear_info_time(void) { return m_hear.time; }
	int get_sensebody_info_time(void) { return m_sensebody.time; }
	int get_see_info_time(void) { return m_see.time; }
	int get_fullstate_info_time(void) { return m_fullstate.time; }

	void set_received_hear_info_this_cycle(bool bState) { m_bReceivedHearInfo = bState; }
	void set_received_sensebody_info_this_cycle(bool bState) { m_bReceivedSenseBodyInfo = bState; }
	void set_received_see_info_this_cycle(bool bState) { m_bReceivedSeeInfo = bState; }
	void set_received_fullstate_info_this_cycle(bool bState) { m_bReceivedFullStateInfo = bState; }

	bool is_received_hear_info_this_cycle(void) { return m_bReceivedHearInfo; }
	bool is_received_sensebody_info_this_cycle(void) { return m_bReceivedSenseBodyInfo; }
	bool is_received_see_info_this_cycle(void) { return m_bReceivedSeeInfo; }
	bool is_received_fullstate_info_this_cycle(void) { return m_bReceivedFullStateInfo; }

protected:

//	members variables

	COxsyClassPointers *m_pClassPointers;

	HearInfo m_hear;
	SenseBodyInfo m_sensebody;
	SeeInfo m_see;
	FullStateInfo m_fullstate;

	bool m_bReceivedHearInfo;
	bool m_bReceivedSenseBodyInfo;
	bool m_bReceivedSeeInfo;
	bool m_bReceivedFullStateInfo;
};


#endif // __SENSORINFO_H__
