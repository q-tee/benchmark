#pragma once
#include "base.h"

#include <cinttypes>

#define STB_SPRINTF_IMPLEMENTATION
#include <stb/stb_sprintf.h>

template <typename T>
class CStbToString : public CValueToString<T>
{
public:
	CStbToString()
	{
		this->fnConvertToString = &ToString;
	}

	[[nodiscard]] const char* GetName() const override
	{
		return "STB";
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "stbsp_snprintf";
	}

private:
	static char* ToString(char* szBuffer, std::size_t nBufferSize, const T value)
	{
		if constexpr (std::is_floating_point_v<T>)
			stbsp_snprintf(szBuffer, static_cast<int>(nBufferSize), "%.17f", value);
		else if constexpr (sizeof(T) == sizeof(std::uint64_t))
		{
			if constexpr (std::is_signed_v<T>)
				stbsp_snprintf(szBuffer, static_cast<int>(nBufferSize), "%" PRId64, value);
			else
				stbsp_snprintf(szBuffer, static_cast<int>(nBufferSize), "%" PRIu64, value);
		}
		else if constexpr (std::is_signed_v<T>)
			stbsp_snprintf(szBuffer, static_cast<int>(nBufferSize), "%" PRId32, value);
		else
			stbsp_snprintf(szBuffer, static_cast<int>(nBufferSize), "%" PRIu32, value);

		return szBuffer;
	}
};
