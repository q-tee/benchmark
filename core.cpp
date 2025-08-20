#include <q-tee/common/common.h>

#ifdef Q_OS_WINDOWS
#define _CRT_SECURE_NO_WARNINGS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

// used: [stl] ofstream
#include <fstream>

#include "tests/dtoa.h"
#include "tests/atod.h"
#include "tests/itoa.h"
#include "tests/ttoa.h"

int main()
{
#ifdef Q_OS_WINDOWS
	const HANDLE hOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOutput == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE;

	// enable virtual terminal to support ANSI escape-codes
	if (DWORD dwConsoleMode = 0UL; !::GetConsoleMode(hOutput, &dwConsoleMode) || !::SetConsoleMode(hOutput, dwConsoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING))
		return EXIT_FAILURE;

	::SetConsoleOutputCP(CP_UTF8);
#endif

	BENCH::ATOD::Test("results/atod/" Q_BENCH_BUILD "_" Q_BENCH_COMPILER "_" Q_BENCH_OS ".csv");
	BENCH::DTOA::Test("results/dtoa/" Q_BENCH_BUILD "_" Q_BENCH_COMPILER "_" Q_BENCH_OS ".csv");
	BENCH::ITOA::Test("results/itoa/" Q_BENCH_BUILD "_" Q_BENCH_COMPILER "_" Q_BENCH_OS ".csv");
	BENCH::TTOA::Test("results/ttoa/" Q_BENCH_BUILD "_" Q_BENCH_COMPILER "_" Q_BENCH_OS ".csv");

	return EXIT_SUCCESS;
}
