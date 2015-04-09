/*
	AUTHOR: W. Max Lees
	FILE: Model.cpp
	DATE: March 9th, 2014

	Definition of Graphics class
*/

#include "Graphics.h"
#include "Err.h"
#include "Shaders.h"

#include <iostream>

// Singleton instance definition
TraceGL::Graphics* TraceGL::Graphics::m_pInstance = nullptr;

// Get the singleton instance of the class
TraceGL::Graphics* TraceGL::Graphics::getInstance( void )
{
	// Create an instance if it doesn't already exist
	if( !m_pInstance )
		m_pInstance = new Graphics;

	// Return the current instance
	return m_pInstance;
}

// Initialize the GL portion of the window
bool TraceGL::Graphics::initWindow( int width, int height )
{
	// Get the window handle
	HWND hWnd = FindWindow( "TraceWind", "TraceWind" );

	// Define the pixel format data
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof( PIXELFORMATDESCRIPTOR ),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		16,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};		
	
	// Get the Device Context handle
	if( !( this->m_HDC = GetDC( hWnd ) ) )
	{
		TRACE_ERROR( "Could not get handle to the device context." );
		this->killWindow();
		return false;
	}

	// Create the pixel format
	int	PixelFormat;
	if( !( PixelFormat = ChoosePixelFormat( this->m_HDC, &pfd ) ) )
	{
		TRACE_ERROR( "Could not create the pixel format." );
		this->killWindow();
		return false;
	}

	// Set the Pixel Format
	if( !SetPixelFormat( this->m_HDC, PixelFormat, &pfd ) )
	{
		TRACE_ERROR( "Could not set the pixel format" );
		this->killWindow();
		return false;
	}

	// Create the device context
	if ( !( this->m_HRC = wglCreateContext( this->m_HDC ) ) )
	{
		TRACE_ERROR( "Could not create the device context" );
		this->killWindow();
		return false;
	}

	// Attach everything to the window
	if( !wglMakeCurrent( this->m_HDC, this->m_HRC ) )
	{
		TRACE_ERROR( "Could not make HDC and HRC current" );
		this->killWindow();
		return false;
	}

	// Show the window
	ShowWindow( hWnd, SW_SHOW );
	SetForegroundWindow( hWnd );
	SetFocus( hWnd );
	this->resizeGLScene( width, height );

	// Initialize OpenGL settings
	if( !this->initGL() )
	{
		TRACE_ERROR( "Could not initialize OpenGL" );
		this->killWindow();
		return false;
	}

	// Intialize glew
	if( GLEW_OK != glewInit() )
		throw Trace::Err( "ERROR: Failed initializing GLEW.\n" );

	return true;
}

// Compile and load the specified program into GL
void TraceGL::Graphics::loadProgram( PROGRAM_ID program ) const
{
	// Create pointers to shader programs
	const GLchar* vShaderProg = nullptr;
	const GLchar* fShaderProg = nullptr;

	// Load correct shader file pointer
	switch( program )
	{
		case PROG_PASSTHROUGH_SHADER:
		default:
			vShaderProg = VERT_SHADER;
			fShaderProg = FRAG_SHADER;
			break;
	}

	GLuint vShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vShader, 1, &vShaderProg, NULL );
	glCompileShader( vShader );
	this->printLog( vShader );

	GLuint fShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fShader, 1, &fShaderProg, NULL );
	glCompileShader( fShader );
	this->printLog( fShader );

	GLuint myProg = glCreateProgram();
	glAttachShader( myProg, vShader );
	glAttachShader( myProg, fShader );
	glLinkProgram( myProg );
	glUseProgram( myProg );
	this->printLog( myProg );

	return;
}

// Print the gl shader compiler logs if there are errors
void TraceGL::Graphics::printLog( GLuint obj ) const
{
	int infologLength = 0;
	int maxLength;
 
	// Get the length
	if( glIsShader( obj ) )
		glGetShaderiv( obj, GL_INFO_LOG_LENGTH, &maxLength );
	else
		glGetProgramiv( obj, GL_INFO_LOG_LENGTH, &maxLength );
 
	// Create the char* for a log
	char* infoLog = new char[maxLength];
 
	// Get the log message
	if( glIsShader( obj ) )
		glGetShaderInfoLog( obj, maxLength, &infologLength, infoLog );
	else
		glGetProgramInfoLog( obj, maxLength, &infologLength, infoLog );
 
	// Print the log to the console
	if( infologLength > 0 )
		std::cerr << infoLog;

	// Delete the char*
	delete [] infoLog;
	infoLog = NULL;
}

// Initialize the GL variables
bool TraceGL::Graphics::initGL( void ) const
{
	// Set Shader type
	glShadeModel( GL_SMOOTH );

	// Set clear color (default now but could change later)
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	// Set clear depth (default now but could change later)
	glClearDepth( 1.0f );

	// Set up depth testing
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );

	// Set up perspective hint
	// TODO: Slows down performance, should be able to choose
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	return true;
}

// Resize the gl scene
void TraceGL::Graphics::resizeGLScene( GLsizei width, GLsizei height ) const
{
	// Make sure we don't divide by zero
	if( height == 0 )
		height = 1;

	// Set the viewport
	glViewport( 0, 0, width, height );

	// Load the projection matrix
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	// Calculate The Aspect Ratio Of The Window
	gluPerspective( 45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f );

	// Load the modelview matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	return;
}

// Release gl window stuff
void TraceGL::Graphics::killWindow( void )
{
	/*if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}*/

	// Get the window handle
	HWND hWnd = FindWindow( "TraceWind", "TraceWind" );

	// Releases the HRC
	if( this->m_HRC )
	{
		wglMakeCurrent( NULL, NULL );

		wglDeleteContext( this->m_HRC );
		this->m_HRC = NULL;
	}

	// Release the device context
	if( this->m_HDC && !ReleaseDC( hWnd, this->m_HDC ) )
		this->m_HDC = NULL;

}

void TraceGL::Graphics::redrawGL( void ) const
{
	// Clear the buffers
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();


	// Swap the buffers
	SwapBuffers( this->m_HDC );
}