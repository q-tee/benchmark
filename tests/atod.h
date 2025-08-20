#pragma once
#include <cinttypes>
#include <random>

#include "string-value/strtod.h"
#include "string-value/from_chars.h"
#include "string-value/ryu.h"
#include "string-value/qtee.h"

namespace BENCH::ATOD
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
		std::printf("\033[94m[ATOD]\033[0m random engine seeded with: 0x%016" PRIX64 "\n", ullSeed);

		constexpr std::size_t nDataCount = 1024U;
		char** pData = new char*[nDataCount];

		// generate small values data
		std::uniform_real_distribution<double> smallDistribution(-1.0, 1.0);
		for (std::size_t i = 0U; i < nDataCount; i++)
		{
			pData[i] = new char[512];
			::sprintf(pData[i], "%.17f", smallDistribution(randomEngine));
		}

		CBenchTest bench("ATOD/SMALL", kIterationCount);
		bench.SetData(pData, nDataCount);

		// null
		bench.Add(new CStringToValue<double>());
		// standard
		bench.Add(new CStrtodToValue<double>());
		bench.Add(new CFromCharsToValue<double>());
		// external
		bench.Add(new CRyuToValue<double>()); // @note: doesn't support more than 17 digits
		bench.Add(new CQTeeToValue());

		bench.Report(ofsFile);

		// generate medium values data
		std::uniform_real_distribution<double> mediumDistribution(1.0, 1e15);
		for (std::size_t i = 0U; i < nDataCount; i++)
			::sprintf(pData[i], "%.17f", mediumDistribution(randomEngine));

		bench.SetName("ATOD/MEDIUM");
		bench.SetData(pData, nDataCount);
		bench.Report(ofsFile);

		// generate large values data
		std::uniform_real_distribution<double> largeDistribution(1e53, (std::numeric_limits<double>::max)());
		for (std::size_t i = 0U; i < nDataCount; i++)
			::sprintf(pData[i], "%.17f", largeDistribution(randomEngine));

		bench.SetName("ATOD/LARGE");
		bench.SetData(pData, nDataCount);
		bench.Report(ofsFile);

		for (std::size_t i = 0U; i < nDataCount; ++i)
			delete pData[i];
		delete[] pData;
	}
}
