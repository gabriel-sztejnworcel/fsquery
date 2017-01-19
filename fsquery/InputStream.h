
#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H

class InputStream
{
public:
	virtual ~InputStream() {}
	virtual bool HasNext() const = 0;
	virtual char GetNext() = 0;
};

#endif // INPUTSTREAM_H
