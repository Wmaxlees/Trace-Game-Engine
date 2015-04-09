/*
	AUTHOR: W. Max Lees
	FILE: ProcessManager.cpp
	DATE: March 23, 2014

	Definition of the ProcessManager class. See the header
	file for full details on class.
*/

#include "ProcessManager.h"

// Singleton instance
ProcessManager* ProcessManager::m_sInstance = nullptr;

// Get the instance of the class
ProcessManager* ProcessManager::getInstance( void )
{
	if( m_sInstance == nullptr )
		m_sInstance = new ProcessManager();

	return m_sInstance;
}

// Run the processes for one tick
unsigned int ProcessManager::updateProcesses( unsigned long deltaMS )
{
	unsigned short successCount = 0;
	unsigned short failCount = 0;

	// Run through all the processes in the list
	ProcessList::iterator it = this->m_ProcessList.begin();
	while( it != this->m_ProcessList.end() )
	{
		// Get the next process
		StrongProcessPtr pCurrProcess = *it;

		// Save the iterator in case we need to erase it
		ProcessList::iterator thisIt = it;
		++it;

		// Check if process needs to be initialized
		if( pCurrProcess->getState() == Process::UNINITIALIZED )
			pCurrProcess->vOnInit();

		// Update process if it's running
		if( pCurrProcess->getState() == Process::RUNNING )
			pCurrProcess->vOnUpdate( deltaMS );

		// Check if the process is dead
		if( pCurrProcess->isDead() )
		{
			// Run the exit function
			switch( pCurrProcess->getState() )
			{
				case Process::SUCCEEDED:
				{
					// Run succeeded function
					pCurrProcess->vOnSuccess();

					// Deal with child
					StrongProcessPtr pChild = pCurrProcess->peekChild();
					pCurrProcess->removeChild();
					if( pChild )
						this->attachProcess( pChild );

					// Chain finished successfully
					else
						++successCount;

					break;
				}

				case Process::FAILED:
				{
					// Run the failure function
					pCurrProcess->vOnFail();
					++failCount;

					break;
				}

				case Process::ABORTED:
				{
					// Run the aborted function
					pCurrProcess->vOnAbort();
					++failCount;
					break;
				}
			}

			// Remove the dead process
			m_ProcessList.erase( thisIt );
		}
	}

	// Return success and failure in one int
	return ( ( successCount << 16 ) || failCount );
}

// Add a process to be run during the next update cycle
WeakProcessPtr ProcessManager::attachProcess( StrongProcessPtr pProcess )
{
	this->m_ProcessList.push_back( pProcess );

	return pProcess;
}

// Destroy all processes
// TODO: MAKE THIS ACTUALLY DO SOMETHING
void ProcessManager::abortAllProcesses( bool immediate )
{
	if( immediate == true )
		return;

	return;
}