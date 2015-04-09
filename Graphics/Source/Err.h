/*
	AUTHOR: W. Max Lees
	FILE: Err.h
	DATE: March 9th, 2014

	Err CLASS PROVIDED in the TraceGL namespace.

	Err class is used to pass error data through
	throws in error handling.

	CONSTRUCTORS for the Err class
	Err( void )
		PRECONDITION: None
		POSTCONDITION: Creates a blank error
	explicit Err( const char* msg )
		PRECONDITION: None
		POSTCONDITION: Creates an error with the specified
			message
	explicit Err( const std::string& msg )
		PRECONDITION: None
		POSTCONDITION: Creates an error with the specified
			message

	MODIFICATION MEMBER FUNCTIONS for the Err class
	void setMessage( const char* msg )
		PRECONDITION: None
		POSTCONDITION: Sets the error message

	CONSTANT MEMBER FUNCTIONS for the Err class
	const char* getMessage( void )
		PRECONDITION: None
		POSTCONDITION: Returns the error message

	VALUE SEMANTICS
	The copy constructor and the assignment operator will both
		work with the Err class
*/

// Macro Guard
#ifndef _H_ERR
#define	_H_ERR

#include <string>
#include <iostream>

// Error Macro
#define TRACE_ERROR( a ) { std::cerr << "ERROR: " << ( a ) << '\n'; }

namespace Trace
{
	class Err
	{
		public:
			// Constructors
			Err( void );
			explicit Err( const char* msg );
			explicit Err( const std::string& msg );

			// Modification Member functions
			void setMessage( const char* msg ) { this->m_Message = msg; }

			// Constant Member Functions
			const char* getMessage( void ) { return this->m_Message.c_str(); }

		private:
			std::string		m_Message;
	};
}

#endif // !_H_ERR
