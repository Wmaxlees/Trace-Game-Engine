/*
	AUTHOR: W. Max Lees
	FILE: TraceGL.h
	DATE: March 10th, 2014

	TraceGL CLASS PROVIDED

	Contains the static functions to call all necessary
	actions for the TraceGL graphics engine

*/

#ifndef _H_TRACEGL
#define _H_TRACEGL

#include <Windows.h>

class TraceGL
{
	public:
		static void initializeWindow( int width, int height );
		// PRECONDITION: None
		// POSTCONDITION: Calls freeglut functions to create a
		//		window and load openGL

		enum PROGRAM_ID { PROG_PASSTHROUGH_SHADER };
		static void loadProgram( PROGRAM_ID program );
		// PRECONDITION: initializeWindow() has been called
		// POSTCONDITION: The specified shader program will be
		//		loaded

		static void drawScene( void );
		// PRECONDITION: OpenGL has been initialized
		// POSTCONDITION: Swaps the buffers and draws everything
		//		to the screen

		static void shutdownWindow( void );
		// PRECONDITION: None
		// POSTCONDITION: If a GL window exists, the resources
		//		for GL will be released

	private:
		// Classes
		class Graphics;
		class Model;

};

#endif // !_H_TRACEGL
