
<img src="docs/figures/logo.png" alt="logo" width="150">

**wrappi** is a C++ library for core events profiling based on [PAPI](http://icl.utk.edu/papi/) hardware counters.  
It is targetted for multicore and [manycore](https://en.wikipedia.org/wiki/Manycore_processor) compute nodes endowed with a Linux kernel.  
It provides a simple and clean interface to retrieve:

* core cycles,
* cache hits/misses ratios,
* branch prediction,
* [translation lookaside buffer](https://en.wikipedia.org/wiki/Translation_lookaside_buffer) misses,
* instructions load/store.

on a given **section** of the code, or for a **set** of compute kernels.  

[![Build Status](https://travis-ci.com/hobywan/wrappi.svg?branch=master)](https://travis-ci.com/hobywan/wrappi)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/97ca452a233a4ca8b0b6ba82f56fd040)](https://www.codacy.com?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=hobywan/wrappi&amp;utm_campaign=Badge_Grade)
[![license](https://img.shields.io/badge/license-MIT-green.svg)](https://opensource.org/licenses/MIT)

### Build and use
###### Build

**wrappi** is almost standalone.  
It requires a [C++14](https://isocpp.org/wiki/faq/cpp14-language) compiler endowed with [OpenMP](https://www.openmp.org).  
It can be built on any Linux distribution with [PAPI](http://icl.utk.edu/papi/) installed, using [CMake](https://cmake.org):  

``` bash
mkdir build                                      # out-of-source build recommended
cd build                                         #
cmake ..                                         # CMAKE_BUILD_TYPE=[Debug|Release]
make -j4                                         # use multiple jobs for compilation
make install                                     # optional, can use a prefix
```

###### Linking to your project
**wrappi** is exported as a package.  
To enable it, please update your CMakeLists.txt with:

``` cmake
find_package(wrappi)                             # works for both build/install trees
target_link_libraries(target PRIVATE wrappi)     # replace 'target' with your library/binary
```
And then include `wrappi.h` in your application.  

###### Setting thread-core affinity

In a multicore context, you have to explicitly set [thread-core affinity](https://eli.thegreenplace.net/2016/c11-threads-affinity-and-hyperthreading/) before profiling.  
Indeed, threads should be bind to physical cores to prevent the OS from migrating them.  
Besides, [simultaneous multithreading](https://en.wikipedia.org/wiki/Simultaneous_multithreading) (or hyperthreading on Intel) should be disabled in this case.  
It can be done by setting some environment variables:

```bash
export OMP_PLACES=core OMP_PROC_BIND=close       # with GNU or clang compiler
export KMP_AFFINITY=[granularity=core,compact]   # with Intel compiler  
```

###### Basic usage

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/97ca452a233a4ca8b0b6ba82f56fd040)](https://www.codacy.com?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=hobywan/wrappi&amp;utm_campaign=Badge_Grade)

**wrappi** was designed with simplicity and ease of use in mind.  
It can retrieve stats on each invidual core as well as for all cores.  
Here is a basic usage:

``` c++
int const nb = 4;
// set cache counters for each core and each kernel.
wrappi::Manager profile(wrappi::Mode::Cache, nb);   

for (int i = 0; i < nb; ++i) {                       
  profile.start(i);                               
  kernel[i].run();                                
  profile.stop(i);                               
}

profile.report();
```
>💡 You can profile cycles, caches, instructions, [TLB](https://en.wikipedia.org/wiki/Translation_lookaside_buffer), or any event supported by [PAPI](http://icl.utk.edu/papi/) as well.

### License
###### Copyright (c) 2018 Hoby Rakotoarivelo

[![license](https://img.shields.io/badge/license-MIT-green.svg)](https://opensource.org/licenses/MIT)

**wrappi** is free and released under the [MIT](https://opensource.org/licenses/MIT) license.  
It extends the initial work of [Sean Chester](https://github.com/sean-chester/papi-wrapper), but improvements are still welcome 😊.  
To get involved, you can:

-    report bugs or request features by submitting an [issue](https://github.com/hobywan/trinity/issues).
-    submit code contributions using feature branches and [pull requests](https://github.com/hobywan/trinity/pulls).

Enjoy! 😉
