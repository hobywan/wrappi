<img src="docs/figures/logo.png" alt="logo" width="100">

[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

**wrappi** is a [C++14](https://isocpp.org/wiki/faq/cpp14-language) library for core events profiling based on [PAPI](http://icl.utk.edu/papi/) hardware counters.  
It is targetted for multicore and [manycore](https://en.wikipedia.org/wiki/Manycore_processor) compute nodes endowed with a Linux kernel.  
It provides a simple and clean interface to retrieve:

* core cycles,
* cache hits/misses ratios,
* branch prediction,
* [translation lookaside buffer](https://en.wikipedia.org/wiki/Translation_lookaside_buffer) misses,
* instructions load/store.

on a given **section** of the code, or for a **set** of compute kernels.  

### Build and use
###### Build

**wrappi** is almost standalone.  
It requires a [C++14](https://isocpp.org/wiki/faq/cpp14-language) compiler endowed with [OpenMP](https://www.openmp.org).  
It can be built on any Linux distribution with [PAPI](http://icl.utk.edu/papi/) installed, using [CMake](https://cmake.org):  

``` bash
mkdir build                                  # out-of-source build recommended
cd build                                     #
cmake ..                                     # CMAKE_BUILD_TYPE=[Debug|Release]
make -j4                                     # use multiple jobs for compilation
make install                                 # optional, can use a prefix
```

###### Linking to your project
**wrappi** is exported as a package.  
To enable it, please update your CMakeLists.txt with:

``` cmake
find_package(wrappi)                         # works for both build/install trees
target_link_libraries(target PRIVATE wrappi) # replace 'target' with your library/binary
```
And then include `wrappi.h` in your application.  

###### Basic usage
**wrappi** was designed with simplicity and ease of use in mind.  
It can retrieve stats on each invidual core as well as for all cores.  
Here is a basic usage:

``` c++
int const nb_kernels = 4;
// set CPU cache counters for each core and each kernel.
wrappi::Manager profile(wrappi::Mode::Cache, nb_kernels);   

for (int i = 0; i < nb_kernels; ++i) {                       
  profile.start(i);                               
  kernel[i].run();                                
  profile.stop(i);                               
}

profiler.report();
```
>💡 You can profile cycles, caches, instructions, [TLB](https://en.wikipedia.org/wiki/Translation_lookaside_buffer), or any event supported by [PAPI](http://icl.utk.edu/papi/) as well.

### License and contributions
###### Copyright (c) 2018 Hoby Rakotoarivelo

[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

**wrappi** is free and released under the [MIT](https://opensource.org/licenses/MIT) license.  
It extends the initial work of [Sean Chester](https://github.com/sean-chester/papi-wrapper), but improvements are welcome 😊.  
To get involved, you can:

-    report bugs or request features by submitting an [issue](https://github.com/hobywan/trinity/issues).
-    submit code contributions using feature branches and [pull requests](https://github.com/hobywan/trinity/pulls).

Enjoy! 😉
