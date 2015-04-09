
#ifndef _H_EVENTDATA
#define	_H_EVENTDATA

#include <ostream>

typedef unsigned long EventType;

class EventData
{
	public:
		virtual const EventType& vGetEventType( void ) const = 0;
		virtual float vGetTimeStamp( void ) const = 0;
		virtual void vSerialize( std::ostream& out ) const = 0;
		// virtual EventDataPtr vCopy( void ) const = 0;
		virtual const char* vGetName( void ) const = 0;

	private:

};

class BaseEventData : public EventData
{
	public:
		explicit BaseEventData( const float timeStamp = 0.0f )
			: m_TimeStamp( timeStamp )
		{ }

		virtual ~BaseEventData( void ) { }

		virtual const EventType& vGetEventType( void ) const = 0;

		float vGetTimeStamp( void ) const { return this->m_TimeStamp; }

		virtual void vSerialize( std::ostream& out ) const { }

	private:
		const float m_TimeStamp;
};

#endif // !_H_EVENTDATA