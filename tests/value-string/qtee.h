#pragma once
#include "base.h"

#define Q_CRT_STRING_CONVERT
#include <q-tee/crt/crt.h>

template <typename T>
class CQTeeToString : public CValueToString<T>
{
public:
	CQTeeToString()
	{
		this->fnConvertToString = &ToString;
	}

	[[nodiscard]] const char* GetName() const override
	{
		return "Q-TEE";
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		if constexpr (std::is_floating_point_v<T>)
			return "CRT::RealToString";
		else
			return "CRT::IntegerToString";
	}

private:
	static char* ToString(char* szBuffer, std::size_t nBufferSize, const T value)
	{
		if constexpr (std::is_floating_point_v<T>)
			return CRT::RealToString<T>(value, szBuffer, nBufferSize, 17);
		else
			return CRT::IntegerToString<T>(value, szBuffer, nBufferSize);
	}
};
