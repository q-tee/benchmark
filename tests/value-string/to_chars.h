#pragma once
#include "base.h"

#include <charconv>

template <typename T>
class CToCharsToString : public CValueToString<T>
{
public:
	[[nodiscard]] const char* GetMethodName() const override
	{
		return "std::to_chars";
	}

	char* ToString(char* szBuffer, std::size_t nBufferSize, const T value) override
	{
		std::to_chars(szBuffer, szBuffer + nBufferSize, value);
		return szBuffer;
	}
};
