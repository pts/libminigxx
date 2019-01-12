#! /bin/bash --
# by pts@fazekas.hu at Sat Jan 12 17:33:04 CET 2019

set -ex

# Tested with gcc-4.8 in Ubuntu Trusty (14.04).
for ARCH in i386 amd64; do
  if test "$ARCH" = i386; then
    CC="gcc -m32"
  elif test "$ARCH" = amd64; then
    CC="gcc -m64"
  else
    echo "fatal: bad arch: $ARCH" >&2 
    exit 2
  fi
  rm -rf lib.tmp
  mkdir lib.tmp
  cp lib.src/*.c lib.tmp/
  cp lib."$ARCH"/*.o lib.tmp/ ||:
  (rm -f libminigxx_"$ARCH".a && cd lib.tmp && $CC -c -O2 -W -Wall -Wextra *.c && ar cr ../libminigxx_"$ARCH".a *.o) || exit "$?"
  rm -rf lib.tmp
done

: compile.sh OK
