<meta property="og:image" content="https://hobywan.github.io/trinity/figures/logo.png"/>

<a href="https://github.com/hobywan/wrappi">
<img src="figures/logo_inverted.png" alt="logo" width="150">
</a>

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

###### Share

<style>
.social-button-container {
  /*background-color: red;*/
  /**
  * This is a nice CSS trick that allows you to clear an element
  * without having to add extra elements to your HTML. This helps
  * seperate content from design, which should always be an architectural
  * goal.
  */
  overflow: hidden;
  float: left:
}
.social-button {
  float: left;
  min-width: 90px;
  min-height: 20px;
  padding-right: 4px;
}
</style>

<div class="social-button-container" style="position: relative; z-index: 999;">
  <div class="social-button" style="margin-top: -2px; margin-right: -25px;">
    <script src="https://platform.linkedin.com/in.js" type="text/javascript">lang: en_US</script><script type="in/share" data-url="https://hobywan.github.io/trinity" height="20"></script>
  </div>
  
  <div class="social-button">
    <iframe src="https://www.facebook.com/plugins/like.php?href=http%3A%2F%2Fhobywan.github.io%2Ftrinity&width=121&layout=standard&action=like&size=small&show_faces=true&share=true&height=65&appId" width="121" height="20" style="border:none;overflow:hidden" scrolling="no" frameborder="0" allowTransparency="true" allow="encrypted-media">
</iframe>
    <a href="https://hobywan.github.io/trinity" class="twitter-share-button" data-show-count="false">Tweet</a><script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>
  </div>
</div>  

<br>

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
using namespace wrappi;
int const nb = 4;
// enable cache profiling on all cores for each kernel.
Manager profile(Mode::Cache, nb);   

for (int i = 0; i < nb; ++i) {                       
  profile.start(i);                               
  kernel[i].run();                                
  profile.stop(i);                               
}

profile.dump();
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

###### Share

<div class="social-button-container" style="position: relative; z-index: 999;">
  <div class="social-button" style="margin-top: -2px; margin-right: -25px;">
    <script src="https://platform.linkedin.com/in.js" type="text/javascript">lang: en_US</script><script type="in/share" data-url="https://hobywan.github.io/trinity" height="20"></script>
  </div>
  
  <div class="social-button">
    <iframe src="https://www.facebook.com/plugins/like.php?href=http%3A%2F%2Fhobywan.github.io%2Ftrinity&width=121&layout=standard&action=like&size=small&show_faces=true&share=true&height=65&appId" width="121" height="20" style="border:none;overflow:hidden" scrolling="no" frameborder="0" allowTransparency="true" allow="encrypted-media">
</iframe>
    <a href="https://hobywan.github.io/trinity" class="twitter-share-button" data-show-count="false">Tweet</a><script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>
  </div>
</div>