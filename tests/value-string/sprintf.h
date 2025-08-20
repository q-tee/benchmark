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
		return "std::sprintf";
	}

private:
	static char* ToString(char* szBuffer, std::size_t nBufferSize, const T value)
	{
		if constexpr (std::is_floating_point_v<T>)
			::sprintf(szBuffer, "%.17f", value);
		else if constexpr (sizeof(T) == sizeof(std::uint64_t))
		{
			if constexpr (std::is_signed_v<T>)
				::sprintf(szBuffer, "%" PRId64, value);
			else
				::sprintf(szBuffer, "%" PRIu64, value);
		}
		else if constexpr (std::is_signed_v<T>)
			::sprintf(szBuffer, "%" PRId32, value);
		else
			::sprintf(szBuffer, "%" PRIu32, value);

		return szBuffer;
	}
};
