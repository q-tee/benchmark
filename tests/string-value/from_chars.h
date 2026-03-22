#pragma once
#include "base.h"

#include <cstring>
#include <charconv>

template <typename T>
class CFromCharsToValue : public CStringToValue<T>
{
public:
	[[nodiscard]] const char* GetMethodName() const override
	{
		return "std::from_chars";
	}

	T ToValue(const char* szSource) override
	{
		T value;
		std::from_chars(szSource, szSource + ::strlen(szSource), value);
		return value;
	}
};
