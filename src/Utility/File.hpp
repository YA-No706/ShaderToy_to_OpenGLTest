#pragma once

#include <string>
#include <fstream>


class File
{
public:
	static std::string GetFileContents(const std::string& filename)
	{
		std::ifstream stream(filename, std::ios::binary);
		if (!stream)
			throw(errno);

		std::string contents;
		stream.seekg(0, std::ios::end);
		contents.resize(stream.tellg());
		stream.seekg(0, std::ios::beg);
		stream.read(&contents[0], contents.size());
		stream.close();
		return contents;
	}
};