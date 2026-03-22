#pragma once
#include "../test.h"

template <typename T> requires (std::is_floating_point_v<T> || std::is_integral_v<T>)
class CStringToValue : public IBenchObject
{
public:
	[[nodiscard]] const char* GetName() const override
	{
		return Q_BENCH_COMPILER_PREFIX;
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "null";
	}

	virtual T ToValue(const char*)
	{
		return static_cast<T>(0);
	}

	void Run(const void* pData, const std::size_t nDataSize) override
	{
		for (std::size_t i = 0U; i < nDataSize; ++i)
			this->ToValue(static_cast<const char* const*>(pData)[i]);
	}
};
