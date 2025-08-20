#pragma once
#include <q-tee/common/common.h>

#if defined(Q_OS_WINDOWS)
#define WIN32_LEAN_AND_MEAN
// used: [win] QueryPerformanceCounter, QueryPerformanceFrequency
#include <windows.h>
#else
// used: [unix] clock_gettime
#include <time.h>
#endif
// used: [stl] filesystem
#include <filesystem>
// used: [stl] setprecision
#include <iomanip>
// used: [stl] vector
#include <vector>
// used: [stl] ranges
#include <ranges>
// used: [stl] transform
#include <algorithm>

#if !defined(_DEBUG) || defined(NDEBUG)
#define Q_BENCH_BUILD "release"
#else
#define Q_BENCH_BUILD "debug"
#endif
#if defined(Q_OS_WINDOWS)
#if defined(Q_ARCH_X64)
#define Q_BENCH_OS "win64"
#else
#define Q_BENCH_OS "win32"
#endif
#elif defined(__CYGWIN__)
#if defined(Q_ARCH_X64)
#define Q_BENCH_OS "cygwin64"
#else
#define Q_BENCH_OS "cygwin32"
#endif
#elif defined(Q_OS_LINUX)
#if defined(Q_ARCH_X64)
#define Q_BENCH_OS "linux64"
#else
#define Q_BENCH_OS "linux32"
#endif
#elif defined(Q_OS_MACOS)
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE
#if defined(Q_ARCH_X64)
#define Q_BENCH_OS "ios64"
#else
#define Q_BENCH_OS "ios32"
#endif
#elif TARGET_OS_MAC
#if defined(Q_ARCH_X64)
#define Q_BENCH_OS "mac64"
#else
#define Q_BENCH_OS "mac32"
#endif
#endif
#else
#if Q_ARCH_BIT == 64
#define Q_BENCH_OS "unknown64"
#elif Q_ARCH_BIT == 32
#define Q_BENCH_OS "unknown32"
#else
#define Q_BENCH_OS "unknown"
#endif
#endif

#if defined(Q_COMPILER_CLANG)
#define Q_BENCH_COMPILER "clang" Q_STRINGIFY(__clang_major__) "." Q_STRINGIFY(__clang_minor__)
#elif defined(Q_COMPILER_MSC)
#if _MSC_VER >= 1930
#define Q_BENCH_COMPILER "vc2022"
#elif _MSC_VER >= 1920
#define Q_BENCH_COMPILER "vc2019"
#elif _MSC_VER >= 1910
#define Q_BENCH_COMPILER "vc2017"
#elif _MSC_VER >= 1900
#define Q_BENCH_COMPILER "vc2015"
#elif _MSC_VER >= 1800
#define Q_BENCH_COMPILER "vc2013"
#elif _MSC_VER >= 1700
#define Q_BENCH_COMPILER "vc2012"
#elif _MSC_VER >= 1600
#define Q_BENCH_COMPILER "vc2010"
#elif _MSC_VER >= 1500
#define Q_BENCH_COMPILER "vc2008"
#elif _MSC_VER >= 1400
#define Q_BENCH_COMPILER "vc2005"
#else
#define Q_BENCH_COMPILER "vc"
#endif
#elif defined(Q_COMPILER_GCC)
#define Q_BENCH_COMPILER "gcc" Q_STRINGIFY(__GNUC__) "." Q_STRINGIFY(__GNUC_MINOR__)
#else
#define Q_BENCH_COMPILER "unknown"
#endif

#if defined(Q_COMPILER_CLANG)
#define Q_BENCH_COMPILER_PREFIX "CLANG"
#elif defined(Q_COMPILER_GCC)
#define Q_BENCH_COMPILER_PREFIX "GCC"
#elif defined(Q_COMPILER_MSC)
#define Q_BENCH_COMPILER_PREFIX "MSC"
#else
#define Q_BENCH_COMPILER_PREFIX "UNKNOWN"
#endif

class IBenchObject
{
public:
	virtual void Run(const void* pData, const std::size_t nDataCount) = 0;
	[[nodiscard]] virtual const char* GetName() const = 0;
	[[nodiscard]] virtual const char* GetMethodName() const = 0;
};

class CBenchTest
{
public:
	CBenchTest(const char* szName, const unsigned int nIterationCount, const unsigned int nTrialCount = 10U) :
		szName(szName), pData(nullptr), nDataCount(0U), nIterationCount(nIterationCount), nTrialCount(nTrialCount) { }

	void SetName(const char* szName)
	{
		this->szName = szName;
	}

	void SetData(const void* pData, const std::size_t nDataCount)
	{
		this->pData = pData;
		this->nDataCount = nDataCount;
	}

	void Add(IBenchObject* pBenchObject)
	{
		vecTestList.push_back(pBenchObject);
	}

	void Report(std::ofstream& ofsFile)
	{
		double dlDurationMin = (std::numeric_limits<double>::max)();
		double dlDurationMax = 0.0;

		for (IBenchObject* pBenchObject : this->vecTestList)
		{
			double dlCurrentMin = (std::numeric_limits<double>::max)();
			double dlCurrentMax = 0.0;
			double dlCurrentAvg = 0.0;

			// get best of N runs
			for (std::size_t nTrial = 0U; nTrial < this->nTrialCount; ++nTrial)
			{
				double dlElapsedTime;

				// start the timer
#if defined(Q_OS_WINDOWS)
				LARGE_INTEGER timeStart;
				LARGE_INTEGER timeEnd;
				::QueryPerformanceCounter(&timeStart);
#else
				timespec timeStart;
				timespec timeEnd;
				::clock_gettime(CLOCK_MONOTONIC_RAW, &timeStart);
#endif
				for (unsigned int nIteration = 0U; nIteration < this->nIterationCount; ++nIteration)
					pBenchObject->Run(this->pData, nDataCount);

				// stop the timer
#if defined(Q_OS_WINDOWS)
				::QueryPerformanceCounter(&timeEnd);

				LARGE_INTEGER timeFrequency;
				::QueryPerformanceFrequency(&timeFrequency);
				dlElapsedTime = (static_cast<double>(timeEnd.QuadPart - timeStart.QuadPart) * 1000.0) / static_cast<double>(timeFrequency.QuadPart);
#else
				::clock_gettime(CLOCK_MONOTONIC_RAW, &timeEnd);
				dlElapsedTime = static_cast<double>(timeEnd.tv_sec - timeStart.tv_sec) * 1000.0 + static_cast<double>(timeEnd.tv_nsec - timeStart.tv_nsec) / 1'000'000.0;
#endif

				dlCurrentMin = (std::min)(dlElapsedTime, dlCurrentMin);
				dlCurrentMax = (std::max)(dlElapsedTime, dlCurrentMax);
				dlCurrentAvg += dlElapsedTime;
			}

			// convert minimal elapsed time to nanoseconds per operation
			dlCurrentMin *= 1'000'000.0 / static_cast<double>(this->nIterationCount * this->nDataCount);

			std::string strTestNameLower = this->szName;
			if (const std::size_t nOffset = strTestNameLower.find('/'); nOffset != std::string::npos)
				strTestNameLower = strTestNameLower.substr(nOffset + 1U);
			std::ranges::transform(strTestNameLower, strTestNameLower.begin(), [](const char chCurrent) { return std::tolower(chCurrent); });
			ofsFile << strTestNameLower << ',' << pBenchObject->GetName() << ',' << pBenchObject->GetMethodName() << ',' << std::fixed << std::setprecision(3) << dlCurrentMin << '\n';
			std::printf("\033[94m[%s]\033[0m %s (%s): %.3fns\n", this->szName, pBenchObject->GetMethodName(), pBenchObject->GetName(), dlCurrentMin);

			dlDurationMin = (std::min)(dlCurrentMin, dlDurationMin);
			dlDurationMax = (std::max)(dlCurrentMin, dlDurationMax);
		}

		std::printf("\033[94m[%s]\033[0m min: %.3fns, max: %.3fns\n", this->szName, dlDurationMin, dlDurationMax);
	}

private:
	const char* szName;
	const void* pData;
	std::size_t nDataCount;
	unsigned int nIterationCount;
	unsigned int nTrialCount;
	std::vector<IBenchObject*> vecTestList;
};
