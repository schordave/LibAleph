LibAleph <img src="doc/logo.png?raw=true" alt="LibAleph" height="100px" />
=============

A complete, portable, Unicode dynamic string library for C.

LibAleph was primarily designed to provide functionality for a higher level scripting language that needed extensive string manipulation support. However, it has since expended to become a generic string library. Aleph string can, at any time, be safely passed to any other API that expects a regular `const char *` null-terminate string.

LibAleph can be easily incorporated into any C project. LibAleph release consists of just 2 files: `aleph.h` and `aleph.c` (an amalgamation of the entire project). The makefile can be used to generate this file as well.
