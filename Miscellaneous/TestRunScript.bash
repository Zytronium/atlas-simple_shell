#!/bin/env bash
gcc -ggdb3 *.c -o OpenShellGates -Wall -Wextra -pedantic -std=gnu89
if ! test -f ./OpenShellGates
then
  echo "Couldn't compile."
  exit
fi
echo
./OpenShellGates || rm OpenShellGates
echo
if test -f ./OpenShellGates
then
  rm OpenShellGates
  exit
fi
