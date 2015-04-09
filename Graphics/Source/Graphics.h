/*
	AUTHOR: W. Max Lees
	FILE: Graphics.h
	DATE: March 10th, 2014

	Graphics CLASS PROVIDED

	This class controls all of the graphics systems

	MODIFICATION MEMBER FUNCTIONS for the Graphics class
	static Graphics* getInstance()
		PRECONDITION: None
		POSTCONDITION: Returns a pointer to the singleton instance
			of the class
	bool initWindow( int width, int height )
		PRECONDITION: Window has been created
		POSTCONDITION: Creates an OpenGL context within the
			already created window
	void killWindow( void )
		PRECONDITION: None
		POSTCONDITION: Releases the OpenGL resources that are currently
			being used by the program

	CONSTANT MEMBER FUNCTIONS for the Graphics class
	void loadProgram( PROGRAM_ID program ) const
		PRECONDITION: None
		POSTCONDITION: Loads the compiles the specified program
			as the current openGL program
	void redrawGL( void ) const
		PRECONDITION: OpenGL has been initialized
		POSTCONDITION: Refreshes the OpenGL scene

	VALUE SEMANTICS
	The copy constructor and assignment operator will not work with
		the Graphics class
*/

// Macro Guard
#ifndef _H_GRAPHICS
#define _H_GRAPHICS

// Graphics libraries
#pragma comment( lib, "OpenGL32.lib" )
#pragma comment( lib, "./Glew32.lib" )
#pragma comment( lib, "glu32.lib" )

#include "TraceGL.h"

#include <Windows.h>
#include <GL\glew.h>
#include <GL\GL.h>

class TraceGL::Graphics
{
	public:
		// Modification Member Functions
		static Graphics* getInstance();
		void killWindow( void );
		bool initWindow( int width, int height );

		// Constant Member Functions
		void loadProgram( PROGRAM_ID program ) const;	
		void redrawGL( void ) const;

	private:
		// Singleton Instance
		static Graphics* m_pInstance;

		// Members
		HGLRC	m_HRC;
		HDC		m_HDC;

		// Constructors
		Graphics( void ) {};
		Graphics( const Graphics& ) {};
		Graphics& operator= ( const Graphics& ) {};

		// Helper Functions
		void printLog( GLuint obj ) const;
		bool initGL( void ) const;
		void resizeGLScene( GLsizei width, GLsizei height ) const;
		
};

#endif // !_H_GRAPHICS
