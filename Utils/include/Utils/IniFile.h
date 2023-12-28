#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <fmt/core.h>
#include <algorithm>
#include <map>
#include <cassert>

namespace Util
{
	class IniFile
	{
	public:
		struct IniSection
		{
		public:
			IniSection(std::string name = "", IniSection* parent = nullptr)
				: name(name), parentSection(parent) {}

			IniSection& property(const char* key, const char* value) {
				assert(properties.find(key) == properties.end());
				properties[key] = value;
				return *this;
			}

			IniSection& section(const char* name) {
				assert(indicies.find(name) == indicies.end());
				indicies[name] = subsections.size();

				subsections.push_back(new IniSection{name, this});
				return *subsections.back();
			};

			IniSection& parent() {
				return *parentSection;
			}

			IniSection& getSection(const char* name) {
				assert(indicies.find(name) == indicies.end());
				return *subsections[indicies[name]];
			}

			bool hasParent() { return parentSection != nullptr; }

			~IniSection() {
				for (auto& section : subsections)
					delete section;
			}

		private:
			std::string name;
			IniSection* parentSection = nullptr;
			std::map<std::string, std::string> properties;
			std::map<std::string, int> indicies;
			std::vector<IniSection*> subsections;

		friend class IniFile;
		};

		// Map from one parent to the children (one parent can have more htan one child)
		bool read(const char* file);
		bool write(const char* file);

		void append(IniFile& other);

		IniSection& createFile() { mGlobalSection.name = "Global"; return mGlobalSection; }
		IniSection& result() { return mGlobalSection; }

	private:
		bool writeSection(std::ofstream& file, IniFile::IniSection& section);

	private:
		IniSection mGlobalSection;
	};

}