#ifndef __TIME_H__
#define __TIME_H__


class COxsyClassPointers;
class COxsyTime
{

public:

	COxsyTime(COxsyClassPointers *pClassPointers);
	virtual ~COxsyTime();

//	members functions

	void init_time(void);

	void set_time(int time) { m_time = time; }
	int get_time(void) { return m_time; }

protected:

//	memebers variables

	COxsyClassPointers *m_pClassPointers;

	int m_time;
};


#endif // __TIME_H__
