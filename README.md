LibAleph <img src="doc/logo.png?raw=true" alt="LibAleph" height="100px" /> 
=============
[![Build Status](https://img.shields.io/travis/ZigWap/LibAleph.svg)](https://travis-ci.org/ZigWap/LibAleph) [![Coverage Status](https://img.shields.io/coveralls/ZigWap/LibAleph/master.svg)](https://coveralls.io/r/ZigWap/LibAleph?branch=master)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](http://opensource.org/licenses/MIT)

A complete, portable, Unicode library for C.

LibAleph was primarily designed to provide functionality for a higher level scripting language that needed extensive string manipulation support. However, it has since expended to become a generic string library with extensive features. 

LibAleph can be easily incorporated into any project. LibAleph consists of just 2 files: `aleph.h` and `aleph.c` (an amalgamation of the entire project), has no dependencies, and is namespaced with it's own a_ prefix. Aleph strings are easy to work with and can be passed to any other API that expects a regular `const char *` null-terminate strings.

Just drop the two files `aleph.h` and `aleph.c` into your project and compile! That's it, it should literally just work!
