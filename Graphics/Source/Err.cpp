/*
	AUTHOR: W. Max Lees
	FILE: Err.cpp
	DATE: March 9th, 2014

	Definition of Err class
*/

#include "Err.h"

namespace Trace
{

	// Default Constructor
	Err::Err( void )
		: m_Message( "" )
	{ }

	// Overloaded Constructor
	Err::Err( const char* msg )
		: m_Message( msg )
	{ }

	// Overloaded constructor
	Err::Err( const std::string& msg )
		: m_Message( msg )
	{ }

}