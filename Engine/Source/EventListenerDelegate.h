

#ifndef _H_EVENTLISTENERDELEGATE
#define	_H_EVENTLISTENERDELEGATE

#include "EventData.h"

#include <memory>

typedef std::shared_ptr<EventData> EventDataPtr;

class EventListenerDelegate
{
	private:
		typedef void ( *stub_type )( void* object_ptr, EventDataPtr );

	public:
		EventListenerDelegate( void )
			: m_ObjectPtr( 0 ), m_StubPtr( 0 )
		{ }

		template <class T, void( T::*TMethod )( EventDataPtr )>
		static EventListenerDelegate fromMethod( T* objectPtr )
		{
			EventListenerDelegate eLD;
			eLD.m_ObjectPtr = objectPtr;
			eLD.m_StubPtr = &method_stub<T, TMethod>;
			return eLD;
		}

		void operator()( EventDataPtr a1 ) const
		{
			return ( *m_StubPtr )( m_ObjectPtr, a1 );
		}

		bool operator== ( const EventListenerDelegate& target ) const
		{
			return ( this->m_ObjectPtr == target.m_ObjectPtr && this->m_StubPtr == target.m_StubPtr );
		}

	private:
		void*		m_ObjectPtr;
		stub_type	m_StubPtr;

		template <class T, void( T::*TMethod )( EventDataPtr )>
		static void method_stub( void* objectPtr, EventDataPtr a1 )
		{
			T* p = static_cast<T*>( objectPtr );
			return (p->*TMethod)(a1);
		}
};

#endif // !_H_EVENTDATALISTENER
