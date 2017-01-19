
#include "FSQueryTests.h"
#include "FSQueryShell.h"

void RunTests();
void RunShell();

int main()
{
	RunShell();
}

void RunTests()
{
	FSQueryTests tests;
	tests.TestLexer();
	tests.TestParser();
	tests.TestTableBuilder();
	tests.TestDirectoryReader();
	tests.TestFSQuery();
}

void RunShell()
{
	FSQueryShell shell;
	shell.Run();
}
