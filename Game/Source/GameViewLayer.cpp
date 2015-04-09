
#include "GameViewLayer.h"

void GameViewLayer::windowCreatedEvent( EventDataPtr anEvent )
{
	// Respond to event
	this->m_WindowGood = true;
	if( !this->m_WindowInitialized )
	{
		TraceGL::initializeWindow( 640, 480 );
		this->m_WindowInitialized = true;
	}
	
	// Unregister the listener
	EventListenerDelegate d =
		EventListenerDelegate::fromMethod<GameViewLayer, &GameViewLayer::windowCreatedEvent>(GameViewLayer::getInstance());
	MessageHub::getInstance()->removeListener( d, EVT_WINDOWCREATED );

	return;
}

void GameViewLayer::windowDestroyedEvent( EventDataPtr anEvent )
{
	// Respond to event
	this->m_WindowGood = false;
	this->succeed();

	// Unregister the listener
	EventListenerDelegate d =
		EventListenerDelegate::fromMethod<GameViewLayer, &BaseGameViewLayer::windowDestroyedEvent>(GameViewLayer::getInstance());
	MessageHub::getInstance()->removeListener( d, EVT_WINDOWDESTROYED );

	return;
}