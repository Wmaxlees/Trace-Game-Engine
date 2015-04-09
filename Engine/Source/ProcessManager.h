/*
	AUTHOR: W. Max Lees
	FILE: ProcessManager.h
	DATE: March 23, 2014

	Class that handles all processes within the engine
*/

#ifndef	_H_PROCESSMANAGER
#define	_H_PROCESSMANAGER

#include "Process.h"

#include <list>

class ProcessManager
{
	typedef std::list<StrongProcessPtr> ProcessList;

	public:
		// Singleton Instance
		static ProcessManager* getInstance( void );

		// Destructor
		~ProcessManager( void );

		// Modification Member Functions
		unsigned int updateProcesses( unsigned long deltaMS );
		WeakProcessPtr attachProcess( StrongProcessPtr pProcess );
		void abortAllProcesses( bool immediate );

		// Constant Member Functions
		size_t getProcessCount( void ) const { return m_ProcessList.size(); }

	private:
		// Members
		ProcessList m_ProcessList;
		static ProcessManager* m_sInstance;

		// Helper Functions
		void clearAllProcesses( void );

		// Value Semantics
		ProcessManager( void ) {}
		ProcessManager( const ProcessManager& ) {}
		const ProcessManager& operator= ( const ProcessManager& ) {}
};

#endif
