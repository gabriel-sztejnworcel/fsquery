
#include "PosixDirectoryReader.h"
#include "TableBuilder.h"
#include "ValueType.h"
#include "FSQueryException.h"
#include "Table.h"

#include <dirent.h>
#include <sys/stat.h>

PosixDirectoryReader::PosixDirectoryReader()
{
	
}

PosixDirectoryReader::~PosixDirectoryReader()
{
	
}

std::unique_ptr<Table> PosixDirectoryReader::ReadDirectory(const std::string& path, const std::string& tableName, bool recursive) /* override */
{
	std::string dirpath = path;
	
	if (dirpath == "" || dirpath[dirpath.length() - 1] != '/')
	{
		dirpath += "/";
	}
	
	TableBuilder tableBuilder;
	tableBuilder.SetTableName(tableName);

	tableBuilder.AddColumn("fullpath", ValueType::STRING);
	tableBuilder.AddColumn("name", ValueType::STRING);
    tableBuilder.AddColumn("extension", ValueType::STRING);
	tableBuilder.AddColumn("size", ValueType::NUMBER);
	tableBuilder.SealColumns();

	ReadDirectoryInner(dirpath, recursive, tableBuilder);
	
	return tableBuilder.Construct();
}

void PosixDirectoryReader::ReadDirectoryInner(const std::string& path, bool recursive, TableBuilder& tableBuilder)
{
	DIR* dir = nullptr;
	
	try
	{
		dir = opendir(path.c_str());
		
		if (dir == nullptr)
		{
			throw FSQueryException("PosixDirectoryReader: Could not open directory '" + path + "'");
		}
		
		dirent* dirEntry = readdir(dir);
		struct stat fileStat;
		
		while (dirEntry != nullptr)
		{
			std::string fileName(dirEntry->d_name);
			
			if (fileName != "." && fileName != "..")
			{
				std::string fullPath = path + fileName;
				
				int statResult = stat(fullPath.c_str(), &fileStat);
				
				if (statResult < 0)
				{
					throw FSQueryException("PosixDirectoryReader: stat() failed");
				}
				
				if (recursive && S_ISDIR(fileStat.st_mode))
				{
					fullPath += "/";
					ReadDirectoryInner(fullPath, recursive, tableBuilder);
				}
				else
				{
					tableBuilder.SetString(0, fullPath);
					tableBuilder.SetString(1, fileName);
                    tableBuilder.SetString(2, GetFileExtension(fileName));
					tableBuilder.SetNumber(3, fileStat.st_size);
					tableBuilder.SealRow();
				}
			}
			
			dirEntry = readdir(dir);
		}
		
		closedir(dir);
	}
	catch (...)
	{
		if (dir != nullptr)
		{
			closedir(dir);
		}
		
		throw;
	}
}
