

#include "BaseGameViewLayer.h"
#include "MessageHub.h"
#include "EventListenerDelegate.h"
#include "Messages\Event_WindowCreated.h"
#include "Messages\Event_WindowDestroyed.h"
#include "../../Graphics/Source/TraceGL.h"

#include <cstdlib>
#include <iostream>

// Default Constructor
BaseGameViewLayer::BaseGameViewLayer( void )
	: m_WindowGood( false ), m_WindowInitialized( false )
{
	std::cout << "Starting Game View Layer...\n";
}

// Run the process
void BaseGameViewLayer::vOnUpdate( unsigned long deltaMs )
{
	if( this->m_WindowInitialized )
		// Draw the scene
		TraceGL::drawScene();

}

// Shutdown the process
void BaseGameViewLayer::vOnSuccess( void )
{
	std::cout << "Destroying GL interface.\n";

	if( this->m_WindowInitialized )
		// Destroy the window
		TraceGL::shutdownWindow();

	return;
}