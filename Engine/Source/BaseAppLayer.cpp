/*
	AUTHOR: W. Max Lees
	FILE: MessageHub.h
	DATE: March 12, 2014

	Definition file for the BaseAppLayer class
*/

#include "BaseAppLayer.h"
#include "MessageHub.h"
#include "Messages\Event_WindowCreated.h"
#include "Messages\Event_WindowDestroyed.h"
#include "../../Graphics/Source/TraceGL.h"

#include <memory>
#include <iostream>

// Default Constructor
BaseAppLayer::BaseAppLayer( void )
{ }

// Windows message handler
LRESULT CALLBACK BaseAppLayer::WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	// Switch through the messages
	switch( uMsg )
	{
		case WM_CLOSE:								// Close message
		{
			PostQuitMessage( 0 );
			return 0;
		}

		case WM_KEYDOWN:							// Key Press
		{
			BaseAppLayer::keyPress( static_cast<char>( wParam ), true );
			return 0;
		}

		case WM_KEYUP:								// Key Release
		{
			BaseAppLayer::keyPress( static_cast<char>( wParam ), false );
			return 0;
		}


	}

	// Pass on unused messages
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

bool BaseAppLayer::vInit( void )
{
	// Print information
	std::cout << "Starting App Layer...\n";

	// Create the window
	if( !this->createWindow( "TraceWind", 640, 480, 16, false ) )
		return false;

	return true;
}

void BaseAppLayer::vRun( void )
{
	MSG msg;

	// Main game loop
	while( true )
	{
		// Run the message loop
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			if( msg.message == WM_QUIT || msg.message == WM_CLOSE )
			{
				// Exit the loop
				break;

			}
			else
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}

		// Run the game's message system
		MessageHub::getInstance()->update();

	}
}

// Shutdown the system
void BaseAppLayer::vShutdown( void )
{
	// Destroy the window
	this->killWindow();

	return;
}

// Handle key presses and releases
void BaseAppLayer::keyPress( char key, bool press )
{
	// Set the new value of the key
	BaseAppLayer::m_Keys[key] = press;

	std::cout << "|";

	return;
}

// Create the window
bool BaseAppLayer::createWindow( const char* const title, long width, long height, int depth, bool fullscreen )
{
	WNDCLASS	wc;
	DWORD		dwExStyle;
	DWORD		dwStyle;
	RECT		WindowRect;
	HWND		hWnd;
	WindowRect.left = 0L;
	WindowRect.right = width;
	WindowRect.top = 0L;
	WindowRect.bottom = height;

	// Display info
	std::cout << "Creating window...\n";

	// Set window class information
	HINSTANCE hInstance	= GetModuleHandle( NULL );
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= (WNDPROC) BaseAppLayer::WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= NULL;
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= "TraceWind";

	// Register the window class
	if( !RegisterClass( &wc ) )
		return false;
	
	/*
	if (fullscreen)
	{
		DEVMODE dmScreenSettings;
		memset( &dmScreenSettings, 0, sizeof( dmScreenSettings ) );
		dmScreenSettings.dmSize = sizeof( dmScreenSettings );
		dmScreenSettings.dmPelsWidth	= width;
		dmScreenSettings.dmPelsHeight	= height;
		dmScreenSettings.dmBitsPerPel	= depth;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if( ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
			fullscreen = false;
	}

	if( fullscreen )
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor( false );
	}
	else*/
	{
		// Set window style
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	// Setup the window
	AdjustWindowRectEx( &WindowRect, dwStyle, false, dwExStyle );

	// Create The Window
	if ( !( hWnd = CreateWindowEx(	dwExStyle,
									"TraceWind",
									title,
									dwStyle |
									WS_CLIPSIBLINGS |
									WS_CLIPCHILDREN,
									0, 0,
									WindowRect.right-WindowRect.left,
									WindowRect.bottom-WindowRect.top,
									NULL,
									NULL,
									hInstance,
									NULL ) ) )
	{
		this->killWindow();
		return false;
	}

	// Display update
	std::cout << "Window created successfully.\n";

	// Send the window created event to the message handler
	std::shared_ptr<Event_WindowCreated> pEvent( new Event_WindowCreated( "TraceWind" ) );
	MessageHub::getInstance()->queueEvent( pEvent );

	return true;
}

// Destroy the window
void BaseAppLayer::killWindow( void )
{
	std::cout << "Destroying the window\n";

	// Get the window handle
	HWND hWnd = FindWindow( "TraceWind", "TraceWind" );

	// Get the handle to the application instance
	HINSTANCE hInstance = GetModuleHandle( NULL );

	// Destroy the window
	if( hWnd && !DestroyWindow( hWnd ) )
		hWnd = NULL;

	// Release the application
	if( !UnregisterClass( "TraceWind", hInstance ) )
		hInstance = NULL;

	return;
}