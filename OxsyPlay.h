#ifndef __PLAY_H__
#define __PLAY_H__


class COxsyClassPointers;
class COxsyPlay
{

public:

	COxsyPlay(COxsyClassPointers *pClassPointers);
	virtual ~COxsyPlay();

//	members functions

	void ReceiveInformation(void);
	void SimulationCycleControler(void);
	void Play(void);

protected:

//	members variables

	COxsyClassPointers *m_pClassPointers;
};


#endif // __PLAY_H__
