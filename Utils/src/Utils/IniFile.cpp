#include "Utils/IniFile.h"

#include <fmt/core.h>

namespace Util
{
	bool IniFile::read(const char* file)
	{
		// read the damn file
		return false;
	}

	bool IniFile::writeSection(std::ofstream& file, IniFile::IniSection& section)
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
	};
}