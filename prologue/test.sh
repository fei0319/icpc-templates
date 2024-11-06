#!/bin/bash

g++ -o main "$1"
g++ -o brute "$2"
g++ -o gen "$3"

while true; do
  ./gen > in.txt
  ./main < in.txt > out.txt
  ./brute < in.txt > out_bf.txt

  if diff out.txt out_bf.txt > /dev/null; then
    echo "AC"
  else
    echo "WA"
    exit 1
  fi
done
