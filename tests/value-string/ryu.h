#pragma once
#include "base.h"

#include <ryu/ryu.h>

class CRyuToString : public CValueToString<double>
{
public:
	[[nodiscard]] const char* GetName() const override
	{
		return "RYU";
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "d2fixed_buffered";
	}

	char* ToString(char* szBuffer, std::size_t nBufferSize, double dlValue) override
	{
		d2fixed_buffered(dlValue, 17, szBuffer);
		return szBuffer;
	}
};

