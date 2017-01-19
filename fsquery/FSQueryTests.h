
#ifndef FSQUERYTESTS_H
#define FSQUERYTESTS_H

class Table;

class FSQueryTests
{
public:
	void TestLexer();
	void TestParser();
	void TestTableBuilder();
	void TestDirectoryReader();
	void TestFSQuery();
	
private:
	void PrintTable(Table* table);
};

#endif // FSQUERYTESTS_H
