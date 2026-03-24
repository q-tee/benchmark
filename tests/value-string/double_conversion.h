#pragma once
#include "base.h"

#include <double-conversion/double-conversion.h>

class CDoubleConversionToString : public CValueToString<double>
{
public:
	CDoubleConversionToString() :
		converter(double_conversion::DoubleToStringConverter::EMIT_POSITIVE_EXPONENT_SIGN | double_conversion::DoubleToStringConverter::EMIT_TRAILING_DECIMAL_POINT | double_conversion::DoubleToStringConverter::EMIT_TRAILING_ZERO_AFTER_POINT, "inf", "nan", 'e', 0, 0, 0, 0) { }

	[[nodiscard]] const char* GetName() const override
	{
		return "GOOGLE";
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "double_conversion::ToFixed";
	}

	char* ToString(char* szBuffer, std::size_t nBufferSize, const double dlValue) override
	{
		double_conversion::StringBuilder stringBuilder(szBuffer, static_cast<int>(nBufferSize));
		converter.ToFixed(dlValue, 17, &stringBuilder); // @note: doesn't support values greater than 1e60
		return szBuffer;
	}

private:
	double_conversion::DoubleToStringConverter converter;
};
