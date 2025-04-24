#pragma once
#include <random>

#include "value-string/sprintf.h"
#include "value-string/to_chars.h"
#include "value-string/to_string.h"
#include "value-string/oss.h"
#include "value-string/stb.h"
#include "value-string/double_conversion.h"
#include "value-string/milo.h"
#include "value-string/ryu.h"
#include "value-string/fpconv.h"
#include "value-string/qtee.h"

namespace BENCH::DTOA
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
		std::printf("\033[94m[DTOA]\033[0m random engine seeded with: 0x%016" PRIX64 "\n", ullSeed);

		constexpr std::size_t nDataCount = 1024U;
		double* pData = new double[nDataCount];

		// generate small values data
		std::uniform_real_distribution<double> smallDistribution(-1.0, 1.0);
		for (std::size_t i = 0U; i < nDataCount; i++)
			pData[i] = smallDistribution(randomEngine);

		CBenchTest bench("DTOA/SMALL", kIterationCount);
		bench.SetData(pData, nDataCount);

		// null
		bench.Add(new CValueToString<double>());
		// standard
		bench.Add(new CSprintfToString<double>());
		bench.Add(new CToCharsToString<double>());
		bench.Add(new CToStringToString<double>());
		bench.Add(new COStringStreamToString<double>());
		// external
		bench.Add(new CStbToString<double>());
		bench.Add(new CDoubleConversionToString()); // @note: doesn't support fixed output for values larger than 1e60
		bench.Add(new CMiloToString());
		bench.Add(new CRyuToString());
		bench.Add(new CFpconvToString());
		bench.Add(new CQTeeToString<double>());

		bench.Report(ofsFile);

		// generate medium values data
		std::uniform_real_distribution<double> mediumDistribution(1.0, 1e15);
		for (std::size_t i = 0U; i < nDataCount; i++)
			pData[i] = mediumDistribution(randomEngine);

		bench.SetName("DTOA/MEDIUM");
		bench.SetData(pData, nDataCount);
		bench.Report(ofsFile);

		// generate large values data
		std::uniform_real_distribution<double> largeDistribution(1e53, (std::numeric_limits<double>::max)());
		for (std::size_t i = 0U; i < nDataCount; i++)
			pData[i] = largeDistribution(randomEngine);
		
		bench.SetName("DTOA/LARGE");
		bench.SetData(pData, nDataCount);
		bench.Report(ofsFile);

		delete[] pData;
	}
}
