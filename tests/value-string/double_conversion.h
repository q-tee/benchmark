#pragma once
#include "base.h"

#include <double-conversion/double-conversion.h>

class CDoubleConversionToString : public CValueToString<double>
{
public:
	CDoubleConversionToString()
	{
		this->fnConvertToString = &ToString;
	}
	
	[[nodiscard]] const char* GetName() const override
	{
		return "GOOGLE";
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "double_conversion::ToFixed";
	}

private:
	static char* ToString(char* szBuffer, std::size_t nBufferSize, const double dlValue)
	{
		double_conversion::StringBuilder stringBuilder(szBuffer, static_cast<int>(nBufferSize));
		double_conversion::DoubleToStringConverter::EcmaScriptConverter().ToFixed(dlValue, 17, &stringBuilder);
		return szBuffer;
	}
};
