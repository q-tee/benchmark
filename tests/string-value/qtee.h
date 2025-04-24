#pragma once
#include "base.h"

#define Q_CRT_STRING_CONVERT
#include <q-tee/crt/crt.h>

class CQTeeToValue : public CStringToValue<double>
{
public:
	CQTeeToValue()
	{
		this->fnConvertToValue = &ToValue;
	}

	[[nodiscard]] const char* GetName() const override
	{
		return "Q-TEE";
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "CRT::StringToReal";
	}

private:
	static double ToValue(const char* szSource)
	{
		return CRT::StringToReal<double>(szSource);
	}
};