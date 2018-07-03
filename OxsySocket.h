#ifndef __SOCKET_H__
#define __SOCKET_H__


class COxsyClassPointers;
class COxsySocket
{

public:

	COxsySocket(COxsyClassPointers *pClassPointers);
	virtual ~COxsySocket();

//	members functions

	Socket *get_socket(void) { return &sock; }
	void   set_socket(Socket s) { sock = s; }

protected:

//	memebers variables

	COxsyClassPointers *m_pClassPointers;
	Socket sock;


};


#endif // __SOCKET_H__
