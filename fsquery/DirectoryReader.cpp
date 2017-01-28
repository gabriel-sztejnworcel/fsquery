
#include "DirectoryReader.h"
#include "PosixDirectoryReader.h"

DirectoryReader::~DirectoryReader()
{
	
}

/* static */ std::unique_ptr<DirectoryReader> DirectoryReader::Create()
{
	return std::make_unique<PosixDirectoryReader>();
}

void DirectoryReader::SeparateFileNameFromExtension(const std::string& fileNamePlusExtension, std::string& fileName, std::string& extension)
{
	size_t dotPosition = fileNamePlusExtension.find_last_of(".");
	
	if (dotPosition == std::string::npos)
	{
		fileName = fileNamePlusExtension;
		extension = "";
	}
	else
	{
		fileName = fileNamePlusExtension.substr(0, dotPosition);
		extension = fileNamePlusExtension.substr(dotPosition + 1);
	}
}
