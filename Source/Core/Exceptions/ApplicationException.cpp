#include "ApplicationException.h"


//------------------------------------------------------------------------------
/**
*/
//---
ApplicationException::ApplicationException(std::string_view message, std::source_location location)
	: std::runtime_error(std::string(message))
	, m_sourceLocation(location)
{
}
