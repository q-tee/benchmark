#pragma once
#include "base.h"

#define Q_CRT_STRING_CONVERT
#include <q-tee/crt/crt.h>

class CQTeeTimeToString : public CTimeToString
{
public:
	CQTeeTimeToString()
	{
		this->fnConvertToString = &ToString;
	}

	[[nodiscard]] const char* GetName() const override
	{
		return "Q-TEE";
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "CRT::TimeToString";
	}

private:
	static std::size_t ToString(char* szBuffer, std::size_t nBufferSize, const char* szFormat, const tm* pTimePoint)
	{
		return CRT::TimeToString(szBuffer, nBufferSize, szFormat, pTimePoint);
	}
};
