libminigxx: A minimalistic C++ library for gcc -fno-exceptions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
libminigxx is a minimalistic C++ library which can be used as a replacement
for libstdc++ or libc++ when `gcc -fno-exceptions' is used as a compiler.
The goal of libminigxx is to give the user the power of the C++ programming
language (rather than C, but without the C++ standard library) without
making the output executables large and bloated, especially those created by
gcc -static. The functionality provided is intentionally very limited, it's
mostly new, delete and dynamic_cast. Exceptions, STL templates (e.g.
std::vector, std::map) and stream IO (e.g. std::cout) are not supported. The
user is expected to use the C library (e.g. printf) for I/O.

Usage:

* Don't run g++, it would link against libstdc++, defying the purpose of
  libbminigxx.

* If you don't need RTTI (e.g. dynamic_cast), the easiest way to try
  libminigxx is using minigxx_nortti.c:

  $ gcc -fno-exceptions -no-rtti  ... PROG.cc minigxx_nortti.cc

  minigxx_nortti.cc works on any architecture.

* Alternatively, if you are targeting i386, run this:

  $ gcc -m32 -fno-exceptions ... PROG.cc -L. -lminigxx_i386

  Examples:

  $ gcc -m32 -s -O2 -W -Wall -Wextra -fno-exceptions examples/rtti.cc -L. -lminigxx_i386.a && ./a.out
  $ gcc -m32 -s -O2 -W -Wall -Wextra -fno-exceptions -fno-rtti examples/nortti.cc -L. -linigxx_i386.a && ./a.out

  Specifying -fno-rtti is optional. dynamic_cast needs RTTI, so don't
  specify -fno-rtti in that case.

* Alternatively, if you are targeting amd64, run this:

  $ gcc -m64 -fno-exceptions ... PROG.cc -L. -lminigxx_amd64

  Examples:

  $ gcc -m64 -s -O2 -W -Wall -Wextra -fno-exceptions examples/rtti.cc -L. -lminigxx_amd64 && ./a.out
  $ gcc -m64 -s -O2 -W -Wall -Wextra -fno-exceptions -fno-rtti examples/nortti.cc -L. -lminigxx_amd64 && ./a.out

  Specifying -fno-rtti is optional. dynamic_cast needs RTTI, so don't
  specify -fno-rtti in that case.

Features:

* new and delete: Works.
* exceptions: Not implemented and will never be implemented.
* dynamic_cast: Works if RTTI works.
* RTTI: Works on i386 and amd64 only. (Don't specify -fno-rtti for gcc.)
  RTTI support .o files were copied from the file libstdc++.a in Ubuntu
  Lucid's libstdc++6-4.4-dev package.
* std::vector, std::map, std::pair and other STL templates: Not implemented
  and will never be implemented.
* std::cout and other stream I/O: Not implemented and will never be
  implemented. Use the C library (e.g. printf) instead.
* C++98, C++11, C++17, C++20: All of these should work by passing the
  relevant flags to gcc. libminigxx is angostic to this.
* typeid: Currently not supported. To make it work, we'd need a working
  <typeinfo> header from gcc-4.4. Maybe it's possible to it.

Troubleshooting:

* If you are getting the error
  ``: undefined reference to `__gxx_personality_v0' '', then specify
  -fno-exceptions. (libminigxx doesn't support exceptions.)
* If you are getting the error
  ``: undefined reference to `__dynamic_cast' '', then use a compilation
  method which doesn't need minigxx_nortti.cc .

TODOs:

* Copy more RTTI support .o files from other Ubuntu Lucid architectures.
  Now we need to cross-compile.
* Add typeid support.

__END__
