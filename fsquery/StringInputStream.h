
#ifndef STRINGINPUTSTREAM_H
#define STRINGINPUTSTREAM_H

#include "InputStream.h"

#include <string>

class StringInputStream : public InputStream
{
public:
	StringInputStream(const std::string& str);

	virtual bool HasNext() const override;
	virtual char GetNext() override;
	
private:
	std::string m_str;
	size_t m_currentPosition;
	bool m_beforeStart;
};

#endif // STRINGINPUTSTREAM_H
