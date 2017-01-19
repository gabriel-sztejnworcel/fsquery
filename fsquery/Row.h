
#ifndef ROW_H
#define ROW_H

#include <vector>
#include <memory>

class Value;

class Row
{
public:
	Row(std::vector<std::unique_ptr<Value>>&& values);
	~Row();
	
	Value* GetValue(size_t i);

private:
	std::vector<std::unique_ptr<Value>> m_values;
};

#endif // ROW_H
