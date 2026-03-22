#pragma once
#include "base.h"

#include <cstring>
#include <string>

template <typename T>
class CToStringToString : public CValueToString<T>
{
public:
	[[nodiscard]] const char* GetMethodName() const override
	{
		return "std::to_string";
	}

	char* ToString(char* szBuffer, std::size_t nBufferSize, const T value) override
	{
		const std::string strResult = std::to_string(value);
		::strcpy(szBuffer, strResult.c_str());
		return szBuffer;
	}
};
