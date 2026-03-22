#pragma once
#include "base.h"

#define Q_CRT_STRING_CONVERT
#include <q-tee/crt/crt.h>

class CQTeeToValue : public CStringToValue<double>
{
public:
	[[nodiscard]] const char* GetName() const override
	{
		return "Q-TEE";
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "CRT::StringToReal";
	}

	double ToValue(const char* szSource) override
	{
		return CRT::StringToReal<double>(szSource);
	}
};