#pragma once
#include <string>

inline static size_t ID = 0;

inline static std::string generateID()
{
	return std::to_string(ID++);
}