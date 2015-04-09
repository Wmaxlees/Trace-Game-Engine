/*
	AUTHOR: W. Max Lees
	FILE: Model.cpp
	DATE: March 9th, 2014

	Model class definition file
*/

#include "Model.h"
#include "Err.h"

#include <fstream>
#include <iostream>

// Default Constructor
TraceGL::Model::Model( void )
	: m_numIndices( 0 ), m_numVertices( 0 )
{ }

// Overloaded Constructor
TraceGL::Model::Model( char* file )
{
	this->loadModel( file );
}

// Load the model from the fileS
void TraceGL::Model::loadModel( char* file )
{
	// Try to open the file
	std::ifstream mdlFile( file );
	if( mdlFile.bad() )
	{
		std::string error( "Could not load model file: " );
		error.append( file );
		throw Trace::Err( error );
	}

	// Try to read in numbers
	mdlFile >> this->m_numIndices;
	mdlFile >> this->m_numVertices;
	if( mdlFile.bad() )
	{
		std::string error( "Could not read indices or vertices in model file: " );
		error.append( file );
		throw Trace::Err( error );
	}

	// Create the vertex and element buffer
	// TODO: Set some way to edit GL_DYNAMIC_DRAW to other options
	// based on appropriate usage
	glGenVertexArrays( NumVAOs, this->m_VAOs );
	glBindVertexArray( this->m_VAOs[Triangles] );

	// Bind and fill the element buffer
	glGenBuffers( NumBuffers, this->m_Buffers );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->m_Buffers[ElementBuffer] );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, this->m_numIndices*sizeof( GLushort ), nullptr, GL_DYNAMIC_DRAW );
	GLushort* indices = (GLushort*)glMapBuffer( GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY );
	if( indices != NULL )
	{
		for( unsigned int i = 0; i < this->m_numIndices; ++i )
			mdlFile >> indices[i];
		glUnmapBuffer( GL_ELEMENT_ARRAY_BUFFER );
		indices = nullptr;
	}
	else
		throw Trace::Err( "Could not map Element Array Buffer.\n" );

	// Bind and fill the vertex buffer
	glBindBuffer( GL_ARRAY_BUFFER, this->m_Buffers[ArrayBuffer] );
	glBufferData( GL_ARRAY_BUFFER, this->m_numVertices*sizeof( GLfloat )*3, nullptr, GL_DYNAMIC_DRAW );
	GLfloat* vertices = (GLfloat*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );
	if( vertices != NULL )
	{
		for( unsigned int i = 0; i < this->m_numVertices*3; ++i )
			mdlFile >> vertices[i];
		glUnmapBuffer( GL_ARRAY_BUFFER );
		vertices = nullptr;
	}
	else
		throw Trace::Err( "Could not map Array Buffer.\n" );

	// Create the vertex attribute pointer
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_TRUE, NULL, (GLvoid*)0 );
	glEnableVertexAttribArray( 0 );

	// Unbind the vertex array
	glBindVertexArray( 0 );

	// Close the file
	mdlFile.close();

	return;
}

// Load the model into the OpenGL pipeline
void TraceGL::Model::draw( void ) const
{
	// Load the vertex array
	glBindVertexArray( this->m_VAOs[Triangles] );

	// Render the object
	glDrawElements( GL_TRIANGLES, this->m_numIndices, GL_UNSIGNED_SHORT, (void*)0 );

	return;
}

// Release all the resources
void TraceGL::Model::destroy( void )
{
	// Delete the openGL stuff
	glDeleteBuffers( NumBuffers, this->m_Buffers );
	glDeleteVertexArrays( NumVAOs, this->m_VAOs );

	return;
}
