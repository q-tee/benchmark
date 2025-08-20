# about
benchmark of performance-critical methods provided by **q-tee** library against standard and external implementations.

# results
table of the already measured results can be found in the [results](./results) directory.
note that it doesn't verify the correctness or compliance of the algorithms used. to verify correctness of the **q-tee** library methods, follow the [test](https://github.com/q-tee/test/) project.

here is a chart visualization of the results measured @ *4.21GHz*, compiled with *MSVC 2022*, run on *Windows 11 64-bit*:
### double to string conversion
measurements were made on **1024** values, which were generated randomly in the range \[-1.0 .. 1.0\] (small), \[1.0 .. 1e15\] (medium), \[1e53 .. 1e308\] (large) and run **16** times. the minimum time duration is measured over **10** trials.

implementation             | note
-------------------------- | ----
std::sprintf (MSC)         | :white_check_mark: (reference)
std::to_string (MSC)       | doesn't support exact number of precision digits, fixed to 6. may perform heap allocations. so *small*, *medium* and *large* measurements are biased
std::to_chars (MSC)        | rounding doesn't match to reference results (e.g. `-0.91942582403655604` being printed as `-0.91942582403655688`)
std::ostringstream         | :white_check_mark:
stbsp_snprintf             | rounding doesn't match to reference results (e.g. `0.50597744914400899` being printed as `0.50597744914400900`)
double_conversion::ToFixed | doesn't support fixed output for values greater than 1e60, so *large* measurements are wrong
dtoa_milo                  | doesn't handle special cases (inf, nan). rounding doesn't match to reference results (e.g. `0.36405244231922773` being printed as `0.36405244231922775`). precision digits doesn't always match to reference results (e.g. `0.42825863483271798` being printed as `0.428258634832718`)
d2fixed_buffered           | :white_check_mark:
fpconv_dtoa                | precision digits doesn't always match to reference results (e.g. `0.43394907957111351` being printed as `0.4339490795711135`)
CRT::RealToString          | :white_check_mark:

![visualization](./results/dtoa/visualization-dark-release-vc2022-win64.svg#gh-dark-mode-only)
![visualization](./results/dtoa/visualization-light-release-vc2022-win64.svg#gh-light-mode-only)

### string to double conversion
measurements were made on **1024** strings converted from randomly generated values in the range \[-1.0 .. 1.0\] (small), \[1.0 .. 1e15\] (medium), \[1e53 .. 1e308\] (large) and run **16** times. the minimum time duration is measured over **10** trials.

implementation             | note
-------------------------- | ----
std::strtod (MSC)          | :white_check_mark: (reference)
std::from_chars (MSC)      | :white_check_mark: conditionally uses Ryu algorithm internally
s2d                        | doesn't support values with more than 17 digits, so *medium* and *large* measurements are wrong
CRT::StringToReal          | :white_check_mark:

![visualization](./results/atod/visualization-dark-release-vc2022-win64.svg#gh-dark-mode-only)
![visualization](./results/atod/visualization-light-release-vc2022-win64.svg#gh-light-mode-only)

# build
- build with Visual Studio:
1. open the solution in repository root directory
2. select target architecture and build type
3. build the solution
4. output files will be written to the `build` directory
- build with CMake:
1. open terminal in repository root directory
2. create the project and build
```console
user@machine:~/benchmark$ mkdir intermediate
user@machine:~/benchmark$ cd intermediate
user@machine:~/benchmark/intermediate$ cmake .. -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Release
user@machine:~/benchmark/intermediate$ make
```
3. output files will be written to the `build` directory

# usage
to add your own algorithm into the benchmark, follow these steps:
1. add your implementation files into `dependencies` directory
2. create header file in the appropriate tests directory (e.g. `atod`, `dtoa`, `itoa`, etc)
3. create a class declaring your implementation based on one of the available interfaces (e.g. `CValueToString`, `CStringToValue`, etc)
4. override `GetName()` and `GetMethodName()` methods with your library name and the name of the used function, respectively
5. create a static method that matches the prototype and set it via the constructor
6. add a instance to appropriate bench object in the appropriate test file

# further information
you can read about installation of particular libraries, contributing and look for other general information on the [q-tee](https://github.com/q-tee/) main page.