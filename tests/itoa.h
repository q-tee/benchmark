#pragma once
#include <random>

#include "value-string/sprintf.h"
#include "value-string/to_string.h"
#include "value-string/oss.h"
#include "value-string/stb.h"
#include "value-string/qtee.h"

namespace BENCH::ITOA
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

		std::random_device randomDevice = { };
		const std::uint64_t ullSeed = ((static_cast<std::uint64_t>(randomDevice()) << 32ULL) | randomDevice());
		std::mt19937_64 randomEngine(ullSeed);
		std::printf("\033[94m[ITOA]\033[0m random engine seeded with: 0x%016" PRIX64 "\n", ullSeed);

		constexpr std::size_t nDataCount = 1024U;
		std::int64_t* pData = new std::int64_t[nDataCount];

		// generate random values data
		std::uniform_int_distribution<std::int64_t> distribution(std::numeric_limits<std::int64_t>::lowest(), (std::numeric_limits<std::int64_t>::max)());
		for (std::size_t i = 0U; i < nDataCount; i++)
			pData[i] = distribution(randomEngine);

		CBenchTest bench("ITOA/DEC", kIterationCount);
		bench.SetData(pData, nDataCount);
		// null
		bench.Add(new CValueToString<std::int64_t>());
		// standard
		bench.Add(new CSprintfToString<std::int64_t>());
		bench.Add(new CToCharsToString<std::int64_t>());
		bench.Add(new CToStringToString<std::int64_t>());
		bench.Add(new COStringStreamToString<std::int64_t>());
		// external
		bench.Add(new CStbToString<std::int64_t>());
		bench.Add(new CQTeeToString<std::int64_t>());
		bench.Report(ofsFile);

		delete[] pData;
	}
}
