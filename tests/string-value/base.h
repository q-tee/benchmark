#pragma once
#include "../test.h"

template <typename T> requires (std::is_floating_point_v<T> || std::is_integral_v<T>)
class CStringToValue : public IBenchObject
{
public:
	CStringToValue()
	{
		this->fnConvertToValue = &ToValue;
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
		for (std::size_t i = 0U; i < nDataSize; ++i)
			fnConvertToValue(static_cast<const char* const*>(pData)[i]);
	}

protected:
	T(*fnConvertToValue)(const char* szSource);
private:
	static T ToValue(const char* szSource)
	{
		return static_cast<T>(0);
	}
};
