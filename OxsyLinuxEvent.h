#ifndef _LINUX_EVENT_H
#define _LINUX_EVENT_H


// modified from original Tsinghuaeolus 'linux_syn.h'

#ifndef WIN32 // _LINUX

#include "pthread.h"


class OxsyLinuxEvent
{

private:

	pthread_mutex_t	m;
	pthread_cond_t	c;
	bool m_bManualReset;
	bool m_bSignalState;

public:

	OxsyLinuxEvent()
	{
	}

	void init(bool bManualReset, bool bInitialState)
	{
		m_bManualReset = bManualReset;
		m_bSignalState = bInitialState;
		pthread_mutex_init(&m, NULL);
		pthread_cond_init(&c, NULL);
	}

	void destroy()
	{
		pthread_cond_destroy(&c);
		pthread_mutex_destroy(&m);
	}

	void SetEvent()
	{
		pthread_mutex_lock(&m);
		m_bSignalState = true;
		pthread_mutex_unlock(&m);
		pthread_cond_signal(&c);
	}

	void ResetEvent()
	{
		pthread_mutex_lock(&m);
		m_bSignalState = false;
		pthread_mutex_unlock(&m);
	}

	int WaitEvent(const struct timespec *abstime = NULL)
	{
		int rt = 0;
		pthread_mutex_lock(&m);

		if(!m_bSignalState)
		{
			if(abstime == NULL)
			{
				rt = pthread_cond_wait(&c, &m);
			}
			else
			{
				rt = pthread_cond_timedwait(&c, &m, abstime);
			}

			if (!m_bManualReset) m_bSignalState = false;
		}

		pthread_mutex_unlock(&m);
		return rt;
	}
};

template<class T> void SetEvent(T& e)
{
	e.SetEvent();
}

template<class T> void ResetEvent(T& e)
{
	e.ResetEvent();
}

#endif


#endif //_LINUX_EVENT_H
