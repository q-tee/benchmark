#pragma once
#include "time-string/strftime.h"
#include "time-string/qtee.h"

namespace BENCH::TTOA
{
	/*
	 * times to repeat operation per capture, used to deal on more stable time delta for small operations
	 * @note: if used, final duration may depend on branch prediction, cache and other factors
	 */
	constexpr unsigned int kIterationCount = 16U;

	inline void Test(const char* szFileName)
	{
		const std::filesystem::path fsFilePath(szFileName);
		if (const std::filesystem::path fsDirectoryPath = fsFilePath.parent_path(); !fsDirectoryPath.empty() && !std::filesystem::exists(fsDirectoryPath))
			std::filesystem::create_directories(fsDirectoryPath);

		std::ofstream ofsFile(fsFilePath);
		ofsFile << "type,name,function,time(ns)\n";

		constexpr const char* arrTimeFormat[] =
		{
			// single
			"%a",
			"%A",
			"%b",
			"%B",
			"%c",
			"%C",
			"%d",
			"%D",
			"%e",
			"%F",
			"%g",
			"%G",
			"%h",
			"%H",
			"%I",
			"%j",
			"%m",
			"%M",
			"%n",
			"%p",
			"%r",
			"%R",
			"%S",
			"%t",
			"%T",
			"%u",
			"%U",
			"%V",
			"%w",
			"%W",
			"%x",
			"%X",
			"%y",
			"%Y",
			//"%z",	// @note: implementation-defined
			//"%Z",	// @note: implementation-defined
			"%%",
			// custom
			"%A, %B %d, %Y",
			"Today at %I:%M %p",
		};

		time_t time;
		::time(&time);
		const tm* pTimePoint = ::localtime(&time);

		const TimeToStringData_t timeToStringData =
		{
			pTimePoint,
			arrTimeFormat
		};
		constexpr std::size_t nDataCount = Q_ARRAYSIZE(arrTimeFormat);

		CBenchTest bench("TTOA", kIterationCount);
		bench.SetData(&timeToStringData, nDataCount);
		// null
		bench.Add(new CTimeToString());
		// standard
		bench.Add(new CStrftimeTimeToString());
		// external
		bench.Add(new CQTeeTimeToString());
		bench.Report(ofsFile);
	}
}
