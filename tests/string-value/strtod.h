#pragma once
#include "base.h"

template <typename T> requires std::is_floating_point_v<T>
class CStrtodToValue : public CStringToValue<T>
{
public:
	[[nodiscard]] const char* GetMethodName() const override
	{
		return "std::strtod";
	}

	T ToValue(const char* szSource) override
	{
		return std::strtod(szSource, nullptr);
	}
};
