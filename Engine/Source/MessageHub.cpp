

#include "MessageHub.h"

#include <Windows.h>

MessageHub* MessageHub::m_sInstance = nullptr;

// Return the singleton instance
MessageHub* MessageHub::getInstance( void )
{
	// Check if the instance already exists
	if( m_sInstance == nullptr )
		m_sInstance = new MessageHub;

	// Return the instance
	return m_sInstance;
}

// Add an event listener
void MessageHub::addListener( const EventListenerDelegate& eventDelegate, const EventType& type )
{
	// Get the correct event spot
	EventListenerList& eventListenerList = this->m_EventListeners[type];
	std::unique_lock<std::mutex> listenerLock( eventListenerList.m_Mutex );
	for( auto it = eventListenerList.m_List.begin(); it != eventListenerList.m_List.end(); ++it )
	{
		// Check if the listener is already registered
		if( eventDelegate == ( *it ) )
		{
			// Maybe display error message?
			return;
		}
	}

	// If there is not instance add the new delegate
	eventListenerList.m_List.push_back( eventDelegate );

	// Release the lock
	listenerLock.unlock();

	return;
}

// Remove an event listener
// TODO: Make this actually do something
void MessageHub::removeListener( const EventListenerDelegate& eventDelegate, const EventType& type )
{
	
	return;
}

void MessageHub::queueEvent( const EventDataPtr& pEvent )
{
	// Make sure correct queue is being used
	if( this->m_ActiveQueue < 0 || this->m_ActiveQueue > EVENTMANAGER_NUM_QUEUES )
	{
		// Set new value
		std::unique_lock<std::mutex> activeLock( this->m_ActiveMutex );
		this->m_ActiveQueue = 0;
		activeLock.unlock();
	}

	// Make sure event is needed
	auto findIt = m_EventListeners.find( pEvent->vGetEventType() );
	if( findIt != m_EventListeners.end() )
	{
		// Queue event
		std::unique_lock<std::mutex> queueMutex( this->m_QueueMutex[m_ActiveQueue] );
		m_Queues[m_ActiveQueue].push_back(pEvent);
		queueMutex.unlock();

		return;
	}

	return;
}

// TODO: Make this actually do something
void MessageHub::abortEvent( const EventType& type, bool allOfType )
{


	return;
}

void MessageHub::update( unsigned long maxTime )
{
	unsigned long currMs = GetTickCount();
	unsigned long maxMs = ( ( maxTime == kINFINITE ) ? kINFINITE : ( currMs + maxTime ) );

	// Update active queue number
	std::unique_lock<std::mutex> activeMutex( this->m_ActiveMutex );
	unsigned short queueToUse = this->m_ActiveQueue;
	this->m_ActiveQueue = ( this->m_ActiveQueue + 1 ) % EVENTMANAGER_NUM_QUEUES;
	activeMutex.unlock();

	// Clear the queue
	std::unique_lock<std::mutex> queueMutex( this->m_QueueMutex[this->m_ActiveQueue] );
	this->m_Queues[this->m_ActiveQueue].clear();
	queueMutex.unlock();

	// Process the queue
	queueMutex = std::unique_lock<std::mutex>( this->m_QueueMutex[queueToUse] );
	std::unique_lock<std::mutex> listenerMutex;
	while( !this->m_Queues[queueToUse].empty() )
	{
		// Get first item
		EventDataPtr pEvent = this->m_Queues[queueToUse].front();
		this->m_Queues[queueToUse].pop_front();

		// Get the type
		const EventType& eventType = pEvent->vGetEventType();

		// Find delegate functions for this event type
		auto findIt = this->m_EventListeners.find(eventType);
		if( findIt != this->m_EventListeners.end() )
		{
			EventListenerList& eventListeners = findIt->second;

			// Call each listener
			listenerMutex = std::unique_lock<std::mutex>( eventListeners.m_Mutex );
			for( auto it = eventListeners.m_List.begin(); it != eventListeners.m_List.end(); ++it )
			{
				EventListenerDelegate listener = (*it);
				listener( pEvent );
			}
			listenerMutex.unlock();
		}

		// Make sure there is still time
		currMs = GetTickCount();
		if( maxTime != kINFINITE && currMs >= maxMs )
			break;
	}

	// Add any remaining items to the next queue
	std::unique_lock<std::mutex> activeQueueMutex( this->m_QueueMutex[this->m_ActiveQueue] );
	while( !this->m_Queues[queueToUse].empty() )
	{
		EventDataPtr pEvent = this->m_Queues[queueToUse].back();
		this->m_Queues[queueToUse].pop_back();
		this->m_Queues[this->m_ActiveQueue].push_front( pEvent );
	}
	activeQueueMutex.unlock();
	queueMutex.unlock();

	return;
}
		
// Constant Member Functions
// TODO: Make this do something
void MessageHub::triggerEvent( const EventDataPtr& pEvent ) const
{


	return;
}