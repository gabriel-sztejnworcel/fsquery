
#ifndef FSQUERYSHELL_H
#define FSQUERYSHELL_H

#include <string>
#include <vector>

class Table;
class TableHeader;
class RowIterator;

class FSQueryShell
{
public:
	FSQueryShell();
	~FSQueryShell();
	
	void Run();
	
private:
	void RunCommand(const std::string& cmd);
	void PrintTable(Table* table);
	void PrintHeader(TableHeader* tableHeader, const std::vector<size_t>& columnSizes);
	void PrintRowSeparator(const std::vector<size_t>& columnSizes);
	void PrintRow(RowIterator* rowIterator, const std::vector<size_t>& columnSizes);
};

#endif // FSQUERYSHELL_H
