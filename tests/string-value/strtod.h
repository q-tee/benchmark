#pragma once
#include "base.h"

template <typename T> requires std::is_floating_point_v<T>
class CStrtodToValue : public CStringToValue<T>
{
public:
	CStrtodToValue()
	{
		this->fnConvertToValue = &ToValue;
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "std::strtod";
	}

private:
	static T ToValue(const char* szSource)
	{
		return std::strtod(szSource, nullptr);
	}
};
