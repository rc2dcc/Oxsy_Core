#include "OxsyMain.h"

#ifndef WIN32 // _LINUX
#include <unistd.h>
#endif

// #include <conio.h>

int main(int argc, char* argv[])
{
	COxsyMain::GetCommandLineParameters(argc, argv);
		
	COxsyMain::InitOxsyPlayerClasses();

	// only for some tests purpose
	COxsyMain::Test();

	COxsyMain::InitOxsyPlayerVariables();

	if (COxsyMain::StartOxsyPlayer())
	{
		while(	COxsyMain::m_bServerIsAlive ||
				COxsyMain::m_bSCCThreadIsAlive)
		{			
			#ifdef WIN32
				Sleep(2000);
			#else // _LINUX
				sleep(2);
			#endif
		}
	}
	
	COxsyMain::ExitOxsyPlayer();

//	getch();
	return 0;
}
