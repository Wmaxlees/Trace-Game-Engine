/*
	AUTHOR: W. Max Lees
	FILE: Process.h
	DATE: March 23, 2014

	Fully virtual Process class for the process manager
*/

#ifndef	_H_PROCESS
#define	_H_PROCESS

#include <memory>

// Typedefs
class Process;
typedef std::shared_ptr<Process> StrongProcessPtr;
typedef std::weak_ptr<Process> WeakProcessPtr;

#include "ProcessManager.h"

class Process
{
	friend class ProcessManager;

	public:
		enum State { UNINITIALIZED, REMOVED,
					 RUNNING, PAUSED,
					 SUCCEEDED, FAILED, ABORTED };

		// Constructors
		Process( void ) : m_State( UNINITIALIZED ) { };
		
		// Destructors
		virtual ~Process( void ) {};

		// Modification Member Functions
		inline void succeed( void ) { this->m_State = SUCCEEDED; }
		inline void fail( void ) { this->m_State = FAILED; }
		inline void pause( void ) { this->m_State = PAUSED; }
		inline void unpause( void ) { this->m_State = RUNNING; }
		inline void attachChild( StrongProcessPtr pChild ) { this->m_pChild = pChild; }
		void removeChild( void ) { this->m_pChild = nullptr; }
		StrongProcessPtr peekChild( void ) { return m_pChild; }

		// Constant Member Functions
		State getState( void ) const { return this->m_State; }
		bool isAlive( void ) const { return ( this->m_State == RUNNING || this->m_State == PAUSED ); }
		bool isDead( void ) const { return ( this->m_State > PAUSED ); }
		bool isRemoved( void ) const { return ( this->m_State == REMOVED ); }
		bool isPaused( void ) const { return ( this->m_State == PAUSED ); }

	protected:
		// Redefine as needed in derived classes
		virtual void vOnInit( void ) { this->m_State = RUNNING; }
		virtual void vOnUpdate( unsigned long deltaMS ) = 0;
		virtual void vOnSuccess( void ) { }
		virtual void vOnFail( void ) { }
		virtual void vOnAbort( void ) { }

	private:
		State m_State;
		StrongProcessPtr m_pChild;

		// Helper Functions
		void setState( State newState ) { this->m_State = newState; }
};

#endif //_H_PROCESS
