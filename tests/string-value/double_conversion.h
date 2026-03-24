#pragma once
#include "base.h"

#include <double-conversion/double-conversion.h>

template <typename T> requires std::is_floating_point_v<T>
class CDoubleConversionToValue : public CStringToValue<T>
{
public:
	CDoubleConversionToValue() :
		converter(double_conversion::StringToDoubleConverter::ALLOW_TRAILING_JUNK | double_conversion::StringToDoubleConverter::ALLOW_LEADING_SPACES | double_conversion::StringToDoubleConverter::ALLOW_TRAILING_SPACES, 0.0, 0.0, "inf", "nan") { }

	[[nodiscard]] const char* GetName() const override
	{
		return "GOOGLE";
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "double_conversion::StringToDouble";
	}
	
	T ToValue(const char* szSource) override
	{
		T result = 0;
		int nProcessedCount;
		if constexpr (std::is_same_v<T, float>)
			return converter.StringToFloat(szSource, ::strlen(szSource), &nProcessedCount);
		else
			return converter.StringToDouble(szSource, ::strlen(szSource), &nProcessedCount);
	}

private:
	double_conversion::StringToDoubleConverter converter;
};
