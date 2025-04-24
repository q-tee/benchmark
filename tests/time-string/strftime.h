#pragma once
#include "base.h"

class CStrftimeTimeToString : public CTimeToString
{
public:
	CStrftimeTimeToString()
	{
		this->fnConvertToString = &ToString;
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "std::strftime";
	}

private:
	static std::size_t ToString(char* szBuffer, std::size_t nBufferSize, const char* szFormat, const tm* pTimePoint)
	{
		return ::strftime(szBuffer, nBufferSize, szFormat, pTimePoint);
	}
};
