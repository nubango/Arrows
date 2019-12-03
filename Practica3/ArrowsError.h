#ifndef _ARROWS_ERROR_H_
#define _ARROWS_ERROR_H_

#include "checkML.h"
#include <stdexcept>

class ArrowsError :
	public std::logic_error
{
public:
	ArrowsError(const std::string& msg) : logic_error(msg) { }

	virtual const char* what() { return logic_error::what(); }
};

#endif // !_ARROWS_ERROR_H_