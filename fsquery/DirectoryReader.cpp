
#include "DirectoryReader.h"
#include "PosixDirectoryReader.h"

DirectoryReader::~DirectoryReader()
{
	
}

/* static */ std::unique_ptr<DirectoryReader> DirectoryReader::Create()
{
	return std::make_unique<PosixDirectoryReader>();
}

std::string DirectoryReader::GetFileExtension(const std::string& fileName)
{
	std::string extension = "";
	
	size_t dotPosition = fileName.find_last_of(".");
	
	if (dotPosition != std::string::npos)
	{
		extension = fileName.substr(dotPosition + 1);
	}
	
	return extension;
}
