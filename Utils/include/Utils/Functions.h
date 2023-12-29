#pragma once
#include <string>
#include <algorithm>
#include <fstream>
#include <imgui.h>
#include <inttypes.h>

namespace Util
{
	inline static void SanitizeFilePath(std::string& filePath)
	{
		for (int i = 0; i < filePath.size() - 1; i++)
		{
			if (filePath[i] == '\\')
				filePath[i] = '/';
		}
		return;
	}

	inline static std::string RemovePrefix(const std::string& prefix, const std::string& str)
	{
		std::string copy = str;
		size_t index = copy.find(prefix);
		if(index == std::string::npos)
			return str;
		copy.erase(copy.begin() + index, copy.begin() + prefix.size() + index);
		return copy;
	}

	void BeginGroupPanel(const char* name, const ImVec2& size = ImVec2(0.0f, 0.0f));
	void EndGroupPanel();

	bool IsInteger(const char *value);
	uint32_t GetInteger(const char *imm, uint32_t size);

	inline static std::string GetFileContent(const char* fileName) {
		std::ifstream inputFile(fileName);
		std::string content;
		while(inputFile.eof() == false)
		{
			std::string line;
			std::getline(inputFile, line);
			if (line == "")
				break;
			content += line + '\n';
		}
		inputFile.close();
		return content;
	}
}