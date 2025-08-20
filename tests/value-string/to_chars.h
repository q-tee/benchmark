#pragma once
#include "base.h"

#include <charconv>

template <typename T>
class CToCharsToString : public CValueToString<T>
{
public:
	CToCharsToString()
	{
		this->fnConvertToString = &ToString;
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "std::to_chars";
	}

private:
	static char* ToString(char* szBuffer, std::size_t nBufferSize, const T value)
	{
		std::to_chars(szBuffer, szBuffer + nBufferSize, value);
		return szBuffer;
	}
};
