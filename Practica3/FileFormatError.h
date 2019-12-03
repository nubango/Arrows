#ifndef _FILEFORMAT_ERROR_H_
#define _FILEFORMAT_ERROR_H_

#include "checkML.h"
#include "ArrowsError.h"

class FileFormatError : 
	public ArrowsError
{
public:
	FileFormatError(const std::string& msg) : ArrowsError(msg) {}
};

#endif // !_FILEFORMAT_ERROR_H_