/*
	AUTHOR: W. Max Lees
	FILE: Model.h
	DATE: March 9th, 2014

	Model CLASS PROVIDED

	Class that contains data to access and load model
	data within the GPU via OpenGL

	CONSTRUCTORS for the Model class
	Model( void )
		PRECONDITION: None
		POSTCONDITION: Creates an empty model instance
	explicit Model( char* file )
		PRECONDITION: file exists
		POSTCONDITION: Loads the model based on the data within
			the file

	MODIFICATION MEMBER FUNCTIONS for the Model class
	void loadModel( char* file )
		PRECONDITION: file exists
		POSTCONDITION: Loads the model based on the data within
			the file
	void destroy( void )
		PRECONDITION: None
		POSTCONDITION: Releases the model data within the GPU

	CONSTANT MEMBER FUNCTIONS for the Model class
	void draw( void ) const
		PRECONDITION: Model data has been loaded
		POSTCONDITION: Pushes the model data into the buffer

	VALUE SEMANTICS
	The copy constructor and the assignment operator will not work
		with the Model class
*/

// Macro Guard
#ifndef _H_MODEL
#define	_H_MODEL

#pragma comment( lib, "OpenGL32.lib" )

#include "TraceGL.h"

#include <Windows.h>
#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

class TraceGL::Model
{
	private:
		// Enumerations
		enum VAO_IDs { Triangles, NumVAOs };
		enum Buffer_IDs { ElementBuffer, ArrayBuffer, NumBuffers };

	public:
		// Constructors
		Model( void );
		explicit Model( char* file );
		// explicit Model( unsigned int offset );

		// Modification Member Functions
		void loadModel( char* file );
		void destroy( void );

		// Constant Member Functions
		void draw( void ) const;

	private:
		// Members
		//unsigned char	m_Priority;
		GLuint			m_VAOs[NumVAOs];
		GLuint			m_Buffers[NumBuffers];
		GLushort		m_numIndices;
		GLuint			m_numVertices;

		// Value Semantics
		Model( const Model& );
		Model& operator= ( const Model& );
};

#endif // !_H_MODEL
