#!/bin/sh

java -jar ../tools/antlr-3.5-complete.jar *.g ${1+"$@"} -o ../src/parser

