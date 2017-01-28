
#include "PosixDirectoryReader.h"
#include "TableBuilder.h"
#include "ValueType.h"
#include "FSQueryException.h"
#include "Table.h"

#include <dirent.h>
#include <sys/stat.h>
#include <ctime>

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
	tableBuilder.AddColumn("modtime", ValueType::TIME);
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
			std::string fileNamePlusExtension(dirEntry->d_name);
			
			if (fileNamePlusExtension != "." && fileNamePlusExtension != "..")
			{
				std::string fullPath = path + fileNamePlusExtension;
				
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
					std::string fileName;
					std::string extension;
					SeparateFileNameFromExtension(fileNamePlusExtension, fileName, extension);
					
					tableBuilder.SetString(0, fullPath);
					tableBuilder.SetString(1, fileName);
					tableBuilder.SetString(2, extension);
					tableBuilder.SetNumber(3, fileStat.st_size);
                    tableBuilder.SetTimeValue(4, GetTimeValue(fileStat));
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

TimeValue PosixDirectoryReader::GetTimeValue(struct stat& fileStat)
{
	struct tm* timeinfo = localtime(&fileStat.st_mtime);
	
	return TimeValue(
		timeinfo->tm_year + 1900,
		timeinfo->tm_mon + 1,
		timeinfo->tm_mday,
		timeinfo->tm_hour,
		timeinfo->tm_min,
		timeinfo->tm_sec
		);
}
