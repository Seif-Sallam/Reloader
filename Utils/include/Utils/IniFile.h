#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <fmt/core.h>
#include <algorithm>
#include <unordered_map>
#include <cassert>


namespace Util
{
	class IniFile
	{
	public:
		struct IniSection
		{
			IniSection(std::string name = "", IniSection* parent = nullptr)
				: name(name), parent(parent) {}

			IniSection& create(const char* name) {
				this->name = name;
				return *this;
			}

			IniSection& addProperty(const char* key, const char* value) {
				assert(properties.find(key) != properties.end());
				properties.insert(key, value);
				return *this;
			}

			IniSection& addSubSection(const char* name) {
				assert(subsections.find(name) != subsections.end());
				subsections[name] = IniSection{name, this};
				return subsections[name];
			};

			IniSection& getParent() {
				return *parent;
			}

			IniSection& getSubSection(const char* name) {
				assert(subsections.find(name) != subsections.end());
				return subsections[name];
			}

			std::string name;
			IniSection* parent = nullptr;
			std::unordered_map<std::string, std::string> properties;
			std::unordered_map<std::string, IniSection> subsections;
		};

		// Map from one parent to the children (one parent can have more htan one child)
		bool read(const char* file);
		bool write(const char* file);

		IniSection& createFile() { mGlobalSection.name = "Global"; return mGlobalSection; }
		IniSection& result() { return mGlobalSection; }
	private:
		IniSection mGlobalSection;
	};

}