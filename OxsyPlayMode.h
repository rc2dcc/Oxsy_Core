#ifndef __PLAYMODE_H__
#define __PLAYMODE_H__


using namespace std;

class COxsyClassPointers;
class COxsyPlayMode
{

public:

	COxsyPlayMode(COxsyClassPointers *pClassPointers);
	virtual ~COxsyPlayMode();

//	memebers functions

	void analyze_play_mode(char *strRefereeMessage, int nRefereeMessageTime);
	PlayMode get_play_mode(char *strPlayMode);

	void set_play_mode_info(PlayMode play_mode, int play_mode_time) { m_PlayModeInfo.play_mode = play_mode; m_PlayModeInfo.play_mode_time = play_mode_time; }
	void set_play_mode_info(PlayModeInfo playModeInfo) { m_PlayModeInfo = playModeInfo; }
	PlayModeInfo get_play_mode_info(void) { return m_PlayModeInfo; }
	vector<PlayModeInfo> *get_play_mode_info_array(void) { return &m_PlayModeInfoArray; }

protected:

//	members variables

	COxsyClassPointers *m_pClassPointers;

	PlayModeInfo m_PlayModeInfo;
	vector<PlayModeInfo> m_PlayModeInfoArray;
};


#endif // __PLAYMODE_H__
