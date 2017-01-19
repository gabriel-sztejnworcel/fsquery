
#include "FSQueryShell.h"

#include "StringInputStream.h"
#include "FSQueryLexer.h"
#include "FSQueryParser.h"
#include "QueryASTNode.h"
#include "TableHeader.h"
#include "ValueType.h"
#include "RowIterator.h"
#include "ColumnDescriptor.h"
#include "FSQueryInterpreter.h"
#include "Table.h"
#include "FSQueryException.h"

#include <iostream>
#include <algorithm>

FSQueryShell::FSQueryShell()
{
	
}

FSQueryShell::~FSQueryShell()
{
	
}

void FSQueryShell::Run()
{
	std::string line;
	std::cout << "fsquery> ";
	std::getline(std::cin, line);

	while (line != "quit")
	{
		try
		{
			if (line != "")
			{
				RunCommand(line);
			}
		}
		catch (const FSQueryException& e)
		{
			std::cout << e.GetMessage() << std::endl;
		}

		std::cout << "fsquery> ";
		std::getline(std::cin, line);
	}
}

void FSQueryShell::RunCommand(const std::string& cmd)
{
	StringInputStream inputStream(cmd);
	FSQueryLexer lexer(inputStream);
	FSQueryParser parser(lexer);
	std::unique_ptr<QueryASTNode> queryNode = parser.Query();
	FSQueryInterpreter interpreter;
	std::unique_ptr<Table> table = interpreter.Interpret(queryNode.get());
	PrintTable(table.get());
}

void FSQueryShell::PrintTable(Table* table)
{
	std::cout << std::endl;
	
	TableHeader* tableHeader = table->GetTableHeader();
	std::vector<size_t> columnSizes(tableHeader->GetNumColumns());
	
	for (size_t i = 0; i < tableHeader->GetNumColumns(); ++i)
	{
		ColumnDescriptor* columnDescriptor = tableHeader->GetColumnDescriptor(i);
		columnSizes[i] = columnDescriptor->GetColumnName().length();
	}
	
	std::unique_ptr<RowIterator> rowIterator = table->Iterator();
	for (rowIterator->Begin(); !rowIterator->End(); rowIterator->Next())
	{
		for (size_t i = 0; i < tableHeader->GetNumColumns(); ++i)
		{
			size_t columnSize = rowIterator->ConvertToString(i).length();
			
			if (columnSize > columnSizes[i])
			{
				columnSizes[i] = columnSize;
			}
		}
	}
	
	std::transform(columnSizes.begin(), columnSizes.end(), columnSizes.begin(), [](size_t columnSize)
	{
		return columnSize + 2;
	});
	
	PrintHeader(tableHeader, columnSizes);

	for (rowIterator->Begin(); !rowIterator->End(); rowIterator->Next())
	{
		PrintRow(rowIterator.get(), columnSizes);
	}
	
	PrintRowSeparator(columnSizes);
	std::cout << std::endl;
}

void FSQueryShell::PrintHeader(TableHeader* tableHeader, const std::vector<size_t>& columnSizes)
{
	PrintRowSeparator(columnSizes);
	
	for (size_t i = 0; i < columnSizes.size(); ++i)
	{
		ColumnDescriptor* columnDescriptor = tableHeader->GetColumnDescriptor(i);
		size_t spaces = columnSizes[i] - columnDescriptor->GetColumnName().length() - 1;
		std::cout << "| " << columnDescriptor->GetColumnName() << std::string(spaces, ' ');
	}
	
	std::cout << "|" << std::endl;
	
	PrintRowSeparator(columnSizes);
}

void FSQueryShell::PrintRowSeparator(const std::vector<size_t>& columnSizes)
{
	for (size_t i = 0; i < columnSizes.size(); ++i)
	{
		std::cout << "+";
		std::cout << std::string(columnSizes[i], '-');
	}
	
	std::cout << "+" << std::endl;
}

void FSQueryShell::PrintRow(RowIterator* rowIterator, const std::vector<size_t>& columnSizes)
{
	for (size_t i = 0; i < columnSizes.size(); ++i)
	{
		size_t spaces = columnSizes[i] - rowIterator->ConvertToString(i).length() - 1;
		std::cout << "| " << rowIterator->ConvertToString(i) << std::string(spaces, ' ');
	}
	
	std::cout << "|" << std::endl;
}
