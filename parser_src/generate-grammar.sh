#!/bin/sh

DIRNAME=`dirname $0`

java -jar $DIRNAME/../tools/antlr-3.5-complete.jar ${1+"$@"} -o $DIRNAME/../src
