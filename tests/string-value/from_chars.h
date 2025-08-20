#pragma once
#include "base.h"

#include <cstring>
#include <charconv>

template <typename T>
class CFromCharsToValue : public CStringToValue<T>
{
public:
	CFromCharsToValue()
	{
		this->fnConvertToValue = &ToValue;
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "std::from_chars";
	}

private:
	static T ToValue(const char* szSource)
	{
		T value;
		std::from_chars(szSource, szSource + ::strlen(szSource), value);
		return value;
	}
};
