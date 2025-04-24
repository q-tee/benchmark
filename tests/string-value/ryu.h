#pragma once
#include "base.h"

#include <ryu/ryu_parse.h>

template <typename T> requires std::is_floating_point_v<T>
class CRyuToValue : public CStringToValue<T>
{
public:
	CRyuToValue()
	{
		this->fnConvertToValue = &ToValue;
	}

	[[nodiscard]] const char* GetName() const override
	{
		return "RYU";
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "s2d";
	}

private:
	static T ToValue(const char* szSource)
	{
		T result = 0;

		if constexpr (std::is_same_v<T, float>)
			s2f(szSource, &result);
		else
			s2d(szSource, &result);

		return result;
	}
};
