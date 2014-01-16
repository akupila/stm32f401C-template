#!/bin/bash
# This is a ghetto hack for XCode that can't properly set paths..
# $1 = clean when cleaning, empty when building
eval `/usr/libexec/path_helper -s`
case $1 in
  clean)
    make clean
    ;;
  *)
    make
    ;;
esac