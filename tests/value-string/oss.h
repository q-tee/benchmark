#pragma once
#include "base.h"

#include <sstream>
#include <iomanip>

template <typename T>
class COStringStreamToString : public CValueToString<T>
{
public:
	COStringStreamToString()
	{
		this->fnConvertToString = &ToString;
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "std::ostringstream";
	}

private:
	static char* ToString(char* szBuffer, std::size_t nBufferSize, const T value)
	{
		std::ostringstream ossNumber;
		if constexpr (std::is_floating_point_v<T>)
			ossNumber << std::fixed << std::setprecision(17) << value;
		else
			ossNumber << value;
		::strcpy_s(szBuffer, nBufferSize, ossNumber.str().c_str());
		return szBuffer;
	}
};
