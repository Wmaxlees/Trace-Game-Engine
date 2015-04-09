/*
	AUTHOR: W. Max Lees
	FILE: DelayProcess.h
	DATE: April 4th, 2014

*/

#ifndef	_H_DELAYPROCESS
#define	_H_DELAYPROCESS

#include "Process.h"

class DelayProcess : public Process
{
	public:
		// Constructors
		explicit DelayProcess( unsigned long timeToDelay );

	protected:
		// Modification Member Functions
		virtual void vOnUpdate( unsigned long deltaMs );

	private:
		// Members
		unsigned long m_DelayTime;
		unsigned long m_ElapsedTime;
};

#endif //_H_DELAYPROCESS
