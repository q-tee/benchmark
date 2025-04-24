#pragma once
#include "../test.h"

struct TimeToStringData_t
{
	const tm* pTimePoint;
	const char* const* arrFormat;
};

class CTimeToString : public IBenchObject
{
public:
	CTimeToString()
	{
		this->fnConvertToString = &ConvertToString;
	}

	[[nodiscard]] const char* GetName() const override
	{
		return Q_BENCH_COMPILER_PREFIX;
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "null";
	}

	void Run(const void* pData, const std::size_t nDataSize) override
	{
		const auto pTimeData = static_cast<const TimeToStringData_t*>(pData);

		char szBuffer[512];
		for (std::size_t i = 0U; i < nDataSize; ++i)
			fnConvertToString(szBuffer, sizeof(szBuffer), pTimeData->arrFormat[i], pTimeData->pTimePoint);
	}

protected:
	std::size_t(*fnConvertToString)(char* szBuffer, std::size_t nBufferSize, const char* szFormat, const tm* pTimePoint);
private:
	static std::size_t ConvertToString(char* szBuffer, std::size_t nBufferSize, const char* szFormat, const tm* pTimePoint)
	{
		return 0U;
	}
};
