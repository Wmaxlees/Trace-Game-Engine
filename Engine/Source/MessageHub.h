/*
	AUTHOR: W. Max Lees
	FILE: MessageHub.h
	DATE: March 12, 2014

*/

#ifndef _H_MESSAGEHUB
#define	_H_MESSAGEHUB

#include "EventData.h"
#include "EventListenerDelegate.h"

#include <list>
#include <map>
#include <mutex>

#define		EVENTMANAGER_NUM_QUEUES		2
#define		kINFINITE					0xFFFFFFFF

class MessageHub
{
	private:
		struct EventListenerList
		{
			// So we don't get a weird error message
			EventListenerList( void ) { }
			EventListenerList( const EventListenerList& ) { }

			std::list<EventListenerDelegate>	m_List;
			std::mutex							m_Mutex;
		};
		typedef std::map<EventType, EventListenerList> EventListenerMap;
		typedef std::list<EventDataPtr> EventQueue;

	public:
		static MessageHub* getInstance( void );

		// Modification Member Functions
		void addListener( const EventListenerDelegate& eventDelegate, const EventType& type );
		void removeListener( const EventListenerDelegate& eventDelegate, const EventType& type );
		void queueEvent( const EventDataPtr& pEvent );
		void abortEvent( const EventType& type, bool allOfType = false );
		void update( unsigned long maxTime = kINFINITE );
		
		// Constant Member Functions
		void triggerEvent( const EventDataPtr& pEvent ) const;

	private:
		

		// Singleton Instance
		static MessageHub* m_sInstance;

		EventListenerMap	m_EventListeners;

		EventQueue			m_Queues[EVENTMANAGER_NUM_QUEUES];
		std::mutex			m_QueueMutex[EVENTMANAGER_NUM_QUEUES];

		unsigned short		m_ActiveQueue;
		std::mutex			m_ActiveMutex;

		// Constructors
		MessageHub( void ) : m_ActiveQueue( 0 ) { }
		MessageHub( const MessageHub& ) { }
		MessageHub& operator= ( const MessageHub& ) { }
};

#endif // !_H_MESSAGEHUB