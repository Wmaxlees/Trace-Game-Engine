/*
	AUTHOR: W. Max Lees
	FILE: DelayProcess.cpp
	DATE: April 4th, 2014

*/

#include "DelayProcess.h"

// Overloaded Constructor
DelayProcess::DelayProcess( unsigned long timeToDelay )
	: m_DelayTime( timeToDelay ), m_ElapsedTime( 0 )
{ }

// Update the delay one tick
void DelayProcess::vOnUpdate( unsigned long deltaMs )
{
	// Update the time
	this->m_ElapsedTime += deltaMs;

	// Check if time has run out
	if( this->m_ElapsedTime >= this->m_DelayTime )
		this->succeed();
}
