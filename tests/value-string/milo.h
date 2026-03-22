#pragma once
#include "base.h"

#include <milo/dtoa.h>

class CMiloToString : public CValueToString<double>
{
public:
	[[nodiscard]] const char* GetName() const override
	{
		return "MILO";
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "dtoa_milo";
	}

	char* ToString(char* szBuffer, std::size_t nBufferSize, double dlValue) override
	{
		dtoa_milo(dlValue, szBuffer);
		return szBuffer;
	}
};

