



#ifndef _H_BASEGAMEVIEWLAYER
#define _H_BASEGAMEVIEWLAYER

#pragma comment( lib, "../Graphics/Lib/TraceGLx64Debug/TraceGLx64Debug.lib" )

#include "EventListenerDelegate.h"
#include "Process.h"

class BaseGameViewLayer : public Process
{
	public:
		// Constructors
		BaseGameViewLayer( void );

		// Process Functions
		virtual void vOnUpdate( unsigned long deltaMs );
		virtual void vOnSuccess( void );

	private:
		// Members
		bool m_WindowInitialized;
		bool m_WindowGood;

		// Constructors
		BaseGameViewLayer( const BaseGameViewLayer& ) { }
		BaseGameViewLayer& operator= ( const BaseGameViewLayer& ) { }
};

#endif // !_H_BASEGAMEVIEWLAYER
