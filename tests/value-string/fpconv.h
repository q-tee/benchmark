#pragma once
#include "base.h"

#include <fpconv/fpconv.h>

class CFpconvToString : public CValueToString<double>
{
public:
	[[nodiscard]] const char* GetName() const override
	{
		return "FPCONV";
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "fpconv_dtoa";
	}

	char* ToString(char* szBuffer, std::size_t nBufferSize, double dlValue) override
	{
		szBuffer[fpconv_dtoa(dlValue, szBuffer)] = '\0';
		return szBuffer;
	}
};

