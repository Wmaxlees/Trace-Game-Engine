


#ifndef _H_EVENT_WINDOWCREATED
#define	_H_EVENT_WINDOWCREATED

#include "../MessageHub.h"

#include <Windows.h>
#include <string>

// Event Type
#define		EVT_WINDOWCREATED		0x4d26c82

class Event_WindowCreated : public BaseEventData
{
	public:
		static const EventType ms_EventType;

		explicit Event_WindowCreated( char* windName )
			: m_WindowName( windName )
		{ }
		explicit Event_WindowCreated( std::istream& in )
			: m_WindowName( getString( in ) )
		{ }

		virtual const EventType& vGetEventType( void ) const
		{
			return this->ms_EventType;
		}

		virtual void vSerialize( std::ostream& out ) const
		{
			out << this->m_WindowName << ' ';

			return;
		}

		virtual const char* vGetName( void ) const
		{
			return "Event_WindowCreated";
		}

	private:
		const std::string m_WindowName;

		// Helper function
		std::string getString( std::istream& in )
		{
			std::string result;
			in >> result;

			return result;
		}
};

#endif // !_H_EVENT_WINDOWCREATED
