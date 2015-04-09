


#ifndef _H_EVENT_WINDOWDESTROYED
#define	_H_EVENT_WINDOWDESTROYED

#include "../MessageHub.h"

#include <Windows.h>
#include <string>

// Event Type
#define		EVT_WINDOWDESTROYED		0x86b590d7

class Event_WindowDestroyed : public BaseEventData
{
	public:
		static const EventType ms_EventType;

		explicit Event_WindowDestroyed( char* windName )
			: m_WindowName( windName )
		{ }
		explicit Event_WindowDestroyed( std::istream& in )
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
			return "Event_WindowDestroyed";
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
