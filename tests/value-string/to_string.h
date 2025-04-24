#pragma once
#include "base.h"

#include <string>

template <typename T>
class CToStringToString : public CValueToString<T>
{
public:
	CToStringToString()
	{
		this->fnConvertToString = &ToString;
	}

	[[nodiscard]] const char* GetMethodName() const override
	{
		return "std::to_string";
	}

private:
	static char* ToString(char* szBuffer, std::size_t nBufferSize, const T value)
	{
		const std::string strResult = std::to_string(value);
		::strcpy_s(szBuffer, nBufferSize, strResult.c_str());
		return szBuffer;
	}
};
