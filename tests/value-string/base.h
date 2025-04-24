#pragma once
#include "../test.h"

template <typename T> requires (std::is_floating_point_v<T> || std::is_integral_v<T>)
class CValueToString : public IBenchObject
{
public:
	CValueToString()
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
		char szBuffer[512];
		for (std::size_t i = 0U; i < nDataSize; ++i)
			fnConvertToString(szBuffer, sizeof(szBuffer), static_cast<const T*>(pData)[i]);
	}

protected:
	char*(*fnConvertToString)(char* szBuffer, std::size_t nBufferSize, const T value);
private:
	static char* ConvertToString(char* szBuffer, std::size_t nBufferSize, const T value)
	{
		return szBuffer;
	}
};
