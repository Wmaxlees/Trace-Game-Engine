/*
	AUTHOR: W. Max Lees
	FILE: BaseAppLayer.h
	DATE: March 3rd, 2014

	BaseAppLayer CLASS PROVIDED

	Controls the Application Layer of the game engine

	STATIC MEMBER FUNCTIONS for the BaseAppLayer class
	static BaseAppLayer* getInstance( void )
		PRECONDITION: None
		POSTCONDITION: Returns a pointer to the singleton instance
			of the class
	static LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
		PRECONDITION: None
		POSTCONDITION: Handles the windows message sent via uMsg

	MODIFICATION MEMBER FUNCTIONS for the BaseAppLayer class
	int main( void )
		PRECONDITION: None
		POSTCONDITION: Function that runs the Application Layer
			for the engine

	VALUE SEMANTICS
	Copy Constructor and assignment operator will not work for 
	the BaseAppLayer class 
*/

#ifndef _H_APPLAYER
#define	_H_APPLAYER

#include "Process.h"

#include <Windows.h>

class BaseAppLayer
{
	public:
		// Constructors
		BaseAppLayer( void );

		// Static Member Functions
		static LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

		// Modification Member Functions
		virtual bool vInit( void );
		virtual void vRun( void );
		virtual void vShutdown( void );

		// Constant Member Functions
		virtual char* vGetGameTitle( void ) const = 0;
		virtual char* vGetGameDir( void ) const = 0;

	protected:
		virtual void vCreateGameAndView( void );
		virtual void vRegisterGameEvents( void ) {}
		// TODO: ADD NETWORKING CAPABILITIES
		// virtual void vCreateNeworkEventForwarder( void );
		// virtual void vDestroyNetworkEventForwarder( void );

	private:
		// Members
		static char m_Keys[256];

		// Helper Functions
		static void keyPress( char key, bool press );
		bool createWindow( const char* const title, long width, long height, int depth, bool fullscreen );
		void killWindow( void );

		// Value Semantics
		BaseAppLayer( const BaseAppLayer& ) { }
		BaseAppLayer& operator= ( const BaseAppLayer& ) { return *this; }
};

#endif // !_H_APPLAYER