#ifndef _FILENOTFOUND_ERROR_H_
#define _FILENOTFOUND_ERROR_H_

#include "checkML.h"
#include "ArrowsError.h"

class FileNotFoundError : 
	public ArrowsError
{
public:
	FileNotFoundError(const std::string& msg) : ArrowsError(msg) {}
};

#endif // !_FILENOTFOUND_ERROR_H_