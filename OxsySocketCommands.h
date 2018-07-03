#ifndef __SOCKETCOMMANDS_H__
#define __SOCKETCOMMANDS_H__


class COxsyClassPointers;
class COxsySocketCommands
{

public:

	COxsySocketCommands(COxsyClassPointers *pClassPointers);
	virtual ~COxsySocketCommands();

//	members functions

	Socket init_connection(char *host, int port);
	void close_connection(Socket *sock);
	bool receive_message(Socket *sock, char *buf, int size);
	bool send_message(Socket *sock, char *buf);
	bool wait_message(Socket *sock, char *buf, int size);

protected:

//	members variables

	COxsyClassPointers *m_pClassPointers;
};


#endif // __SOCKETCOMMANDS_H__
