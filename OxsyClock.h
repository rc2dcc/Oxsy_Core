#ifndef __CLOCK_H__
#define __CLOCK_H__


#ifdef WIN32
#define TIME_DIF_TO_MS(begin, end, frequency) \
	((double)(end.QuadPart - begin.QuadPart) / (double)frequency.QuadPart * 1000.0)
// #define INTEGER64 _int64
#else // _LINUX
#include <sys/time.h>
#define TIME_DIF_TO_MS(begin, end) \
	((end.tv_sec - begin.tv_sec) * 1000.0 + (end.tv_usec - begin.tv_usec) * 0.001)
// #define INTEGER64 long long
#endif


#ifdef WIN32
typedef LARGE_INTEGER TIME_T;
#else // _LINUX
typedef struct timeval TIME_T;
#endif


//	union UniformTime {
//		struct timeval tv;
//		INTEGER64 QuadPart;
//	};


class COxsyClassPointers;
class COxsyClock
{

public:

	COxsyClock(COxsyClassPointers *pClassPointers);
	virtual ~COxsyClock();

//	members functions

	void start_clock(void);
	void stop_clock(void);
	TIME_T get_start_clock(void) { return m_nClockStartValue; }
	TIME_T get_stop_clock(void) { return m_nClockStopValue; }
	double get_elapsed_time(void);

protected:

//	memebers variables

	COxsyClassPointers *m_pClassPointers;

//	double m_dCorrectionFactor;
	double m_dElapsedTime;

	TIME_T m_nClockFrequency;
	TIME_T m_nClockStartValue;
	TIME_T m_nClockStopValue;
};


#endif // __CLOCK_H__
