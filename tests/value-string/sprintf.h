#pragma once
#include "base.h"

#include <cinttypes>

template <typename T>
class CSprintfToString : public CValueToString<T>
{
public:
	CSprintfToString()
	{
		this->fnConvertToString = &ToString;
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "std::sprintf_s";
	}

private:
	static char* ToString(char* szBuffer, std::size_t nBufferSize, const T value)
	{
		if constexpr (std::is_floating_point_v<T>)
			::sprintf_s(szBuffer, nBufferSize, "%.17f", value);
		else if constexpr (sizeof(T) == sizeof(std::uint64_t))
		{
			if constexpr (std::is_signed_v<T>)
				::sprintf_s(szBuffer, nBufferSize, "%" PRId64, value);
			else
				::sprintf_s(szBuffer, nBufferSize, "%" PRIu64, value);
		}
		else if constexpr (std::is_signed_v<T>)
			::sprintf_s(szBuffer, nBufferSize, "%" PRId32, value);
		else
			::sprintf_s(szBuffer, nBufferSize, "%" PRIu32, value);

		return szBuffer;
	}
};
