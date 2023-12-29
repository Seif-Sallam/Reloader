#include "Utils/IniFile.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <fmt/core.h>

namespace Util
{
	bool IniFile::read(const char* file)
	{
		// read the damn file
		std::ifstream inFile(file);
		if (!inFile.is_open())
			return false;
		this->createFile();
		IniSection* foundSection = &this->mGlobalSection;
		while (inFile.eof() == false)
		{
			std::string line = "";
			std::getline(inFile, line);
			if (line.empty())
				break;
			if (line[0] == '[')
			{
				// section
				std::string sectionName = line.substr(1, line.size() - 2);

				std::vector<std::string> sectionTree;
				std::string currentSection = "";
				for (auto& c : sectionName)
				{
					if (c == '.')
					{
						sectionTree.push_back(currentSection);
						currentSection = "";
					}
					else
					{
						currentSection += c;
					}
				}
				sectionTree.push_back(currentSection);
				if (sectionTree.size() > 1)
				{
					// Find parent section
					IniSection* parentSection = &this->mGlobalSection;
					for (int i = 0; i < sectionTree.size() - 1; ++i)
						parentSection = &(parentSection->getSection(sectionTree[i].c_str()));
					foundSection = &(parentSection->section(sectionTree.back().c_str()));
				}
				else
				{
					foundSection = &this->mGlobalSection.section(sectionTree.back().c_str());
				}
			}
			else {
				// Read property
				std::string key = "";
				std::string value = "";
				bool readingKey = true;
				for (auto& c : line)
				{
					if (c == '=')
					{
						readingKey = false;
						continue;
					}
					if (readingKey)
						key += c;
					else
						value += c;
				}
				// Remove spaces
				key.erase(std::remove_if(key.begin(), key.end(), isspace), key.end());
				value.erase(std::remove_if(value.begin(), value.end(), isspace), value.end());
				// Add property
				foundSection->property(key.c_str(), value.c_str());
			}
		}
		return false;
	}

	bool IniFile::writeSection(std::ostream& file, IniFile::IniSection& section)
	{
		std::vector<std::string> sectionTree;
		IniFile::IniSection* currentSection = &section;
		sectionTree.push_back(currentSection->name);
		while(currentSection) {
			if (currentSection->hasParent())
			{
				currentSection = currentSection->parentSection;
				if (currentSection->name == "Global")
					continue;
				sectionTree.push_back(currentSection->name);
			}
			else
			{
				break;
			}
		}
		std::string sectionName = "[" + sectionTree.back();
		for (int i = sectionTree.size() - 2; i >= 0; --i)
		{
			sectionName += "." + sectionTree[i];
		}
		sectionName += "]";

		file << sectionName << '\n';
		for (auto& [key, value] : section.properties)
			file << key << " = " << value << '\n';

		for (auto& subsection : section.subsections)
			writeSection(file, *subsection);

		return true;
	}

	bool IniFile::write(const char* file)
	{
		std::ofstream outFile(file);
		for (auto& section : this->mGlobalSection.subsections)
			writeSection(outFile, *section);
		outFile.close();
		return true;
	}

	std::string IniFile::getFileContent()
	{
		std::stringstream stream;
		for (auto& section : this->mGlobalSection.subsections)
			writeSection(stream, *section);
		return stream.str();
	}

	void IniFile::append(IniFile& other)
	{
		for (auto& section : other.mGlobalSection.subsections)
		{
			auto sec = this->mGlobalSection.section(section->name.c_str());
			for (auto property : section->properties)
				sec.property(property.first.c_str(), property.second.c_str());
		}
	}
}