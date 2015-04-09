#pragma comment( lib, "../Engine/Lib/Enginex64Debug/Enginex64Debug.lib" )

#include "../../Engine/Source/TraceEngine.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	// =======================================
	// Initialize the Game
	// =======================================
	// Connect the console
	connectConsole();

	/*// Add the initialization of the three threads here
	StrongProcessPtr pBaseAppLayer( BaseAppLayer::getInstance() );
	ProcessManager::getInstance()->attachProcess( pBaseAppLayer );
	StrongProcessPtr pGameViewLayer( GameViewLayer::getInstance() );
	ProcessManager::getInstance()->attachProcess( pGameViewLayer );

	// =======================================
	// Run the Game
	// =======================================
	while( BaseAppLayer::getInstance()->isRunning() )
	{
		// TODO: Actually calculate the delta t for the argument
		ProcessManager::getInstance()->updateProcesses( 1 );
	}*/

	// =======================================
	// Shutdown the Game
	// =======================================

	// Wait for user to hit enter
	std::cout << "Press Return to Exit...";
	std::cin.get();

	return EXIT_SUCCESS;
}