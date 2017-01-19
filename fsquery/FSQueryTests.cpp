
#include "FSQueryTests.h"
#include "StringInputStream.h"
#include "FSQueryLexer.h"
#include "FSQueryParser.h"
#include "FSQueryTokenType.h"
#include "FSQueryException.h"
#include "QueryASTNode.h"
#include "TableBuilder.h"
#include "TableImpl.h"
#include "TableHeader.h"
#include "ValueType.h"
#include "RowIterator.h"
#include "ColumnDescriptor.h"
#include "DirectoryReader.h"
#include "FSQueryInterpreter.h"

#include <iostream>
#include <vector>

void FSQueryTests::TestLexer()
{
	try
	{
		StringInputStream inputStream("select H.size from '/home/gabriel' recursive H where H.name like '%test%' and extension = 'xls' order by H.size");
		FSQueryLexer lexer(inputStream);
		
		Token token = lexer.GetNext();
		
		while (token != Token::EndOfInput())
		{
			std::cout << TokenTypeToString(token.GetType()) << " - " << token.GetVal() << std::endl;
			token = lexer.GetNext();
		}
	}
	catch (FSQueryException& e)
	{
		std::cout << e.GetMessage() << std::endl;
	}
}

void FSQueryTests::TestParser()
{
	try
	{
		StringInputStream inputStream("select H.size from '/home/gabriel' recursive H where H.name like '%test%' and extension = 'xls' order by H.size");
		FSQueryLexer lexer(inputStream);
		FSQueryParser parser(lexer);
		auto query = parser.Query();
		std::cout << 10 << std::endl;
	}
	catch (FSQueryException& e)
	{
		std::cout << e.GetMessage() << std::endl;
	}
}

void FSQueryTests::TestTableBuilder()
{
	try
	{
		/*TableBuilder tableBuilder;
		
		tableBuilder.SetTableName("people");
		tableBuilder.AddColumn("name", ValueType::STRING);
		tableBuilder.AddColumn("age", ValueType::NUMBER);
		tableBuilder.SealColumns();
		
		tableBuilder.SetString(0, "A");
		tableBuilder.SetNumber(1, 10);
		tableBuilder.SealRow();

		tableBuilder.SetString(0, "B");
		tableBuilder.SetNumber(1, 20);
		tableBuilder.SealRow();

		tableBuilder.SetString(0, "C");
		tableBuilder.SetNumber(1, 30);
		
		std::unique_ptr<Table> table = tableBuilder.Construct();
		PrintTable(table.get());
		
		std::unique_ptr<Table> product = table->CartesianProduct(table.get(), nullptr);
		PrintTable(product.get());
		
		auto projected = product->Project({"name"}, "projected");
		PrintTable(projected.get());
		
		auto selected = product->Select([](RowIterator* rowIterator){ return true; }, "selected");
		PrintTable(selected.get());*/
	}
	catch (FSQueryException& e)
	{
		std::cout << e.GetMessage() << std::endl;
	}
}

void FSQueryTests::TestDirectoryReader()
{
	try
	{
		std::unique_ptr<DirectoryReader> dirReader = DirectoryReader::Create();
		std::unique_ptr<Table> test = dirReader->ReadDirectory("/home/gabriel/tmp", "test", true);
		PrintTable(test.get());
	}
	catch (FSQueryException& e)
	{
		std::cout << e.GetMessage() << std::endl;
	}
}

void FSQueryTests::PrintTable(Table* table)
{
	TableHeader* tableHeader = table->GetTableHeader();
	
	std::cout << table->GetTableName() << ":" << std::endl;
	std::unique_ptr<RowIterator> rowIterator = table->Iterator();

	for (rowIterator->Begin(); !rowIterator->End(); rowIterator->Next())
	{
		for (size_t i = 0; i < tableHeader->GetNumColumns(); ++i)
		{
			ColumnDescriptor* cd = tableHeader->GetColumnDescriptor(i);

			switch (cd->GetDataType())
			{
			case ValueType::STRING:
				std::cout << rowIterator->GetString(i) << "\t";
				break;
				
			case ValueType::NUMBER:
				std::cout << rowIterator->GetNumber(i) << "\t";
				break;
				
			default:
				throw FSQueryException("TableImpl: Invalid data type");
			}
		}
		
		std::cout << std::endl;
	}
	
	std::cout << std::endl;
}

void FSQueryTests::TestFSQuery()
{
	try
	{
		while (true)
		{
			std::string line;
			std::getline(std::cin, line);
			StringInputStream inputStream(line);
			FSQueryLexer lexer(inputStream);
			FSQueryParser parser(lexer);
			std::unique_ptr<QueryASTNode> queryNode = parser.Query();
			FSQueryInterpreter interpreter;
			std::unique_ptr<Table> table = interpreter.Interpret(queryNode.get());
			PrintTable(table.get());
		}
	}
	catch (FSQueryException& e)
	{
		std::cout << e.GetMessage() << std::endl;
	}
}
