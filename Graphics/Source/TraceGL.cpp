/*
	AUTHOR: W. Max Lees
	FILE: Model.cpp
	DATE: March 9th, 2014
*/

#include "TraceGL.h"
#include "Graphics.h"

// Initialize the window
void TraceGL::initializeWindow( int width, int height )
{
	Graphics::getInstance()->initWindow( width, height );
	return;
}

// Load the passthrough shader program
void TraceGL::loadProgram( PROGRAM_ID program )
{
	Graphics::getInstance()->loadProgram( program );
	return;
}

// Redraw the scene
void TraceGL::drawScene( void )
{
	Graphics::getInstance()->redrawGL();
	return;
}

// Shutdown the window
void TraceGL::shutdownWindow( void )
{
	Graphics::getInstance()->killWindow();
	return;
}