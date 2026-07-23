#!/bin/sh

cat input.txt\
  | perl -ne '/(\d+)/;$g=$1;while(/(\d+) red/g){$g=0 if($1>12)};while(/(\d+) green/g){$g=0 if($1>13)};while(/(\d+) blue/g){$g=0 if($1>14)};$s+=$g;print"$s\n"'\
  | tail -n 1

cat input.txt\
  | perl -ne '$r=0;$g=0;$b=0;while(/(\d+) red/g){$r=$1 if($1>$r)};while(/(\d+) green/g){$g=$1 if($1>$g)};while(/(\d+) blue/g){$b=$1 if($1>$b)};$s+=$r*$g*$b;print"$s\n"'\
  | tail -n 1
