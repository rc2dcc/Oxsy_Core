#include "OxsyLibrary.h"
#include "OxsySocket.h"
#include "OxsyClassPointers.h"


COxsySocket::COxsySocket(COxsyClassPointers *pClassPointers)
{
	m_pClassPointers = pClassPointers;

	sock.socketfd = SOCKET_ERROR;
}


COxsySocket::~COxsySocket()
{

}
