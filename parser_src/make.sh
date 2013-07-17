#!/bin/bash

DIRNAME=`dirname $0`

flex -o $DIRNAME/aspcore2_lexer.hpp $DIRNAME/aspcore2.l
bison -y -d -o $DIRNAME/aspcore2_parser.c $DIRNAME/aspcore2.y
bison -y -o $DIRNAME/aspcore2_parser.hpp $DIRNAME/aspcore2.y

cp $DIRNAME/aspcore2_lexer.hpp $DIRNAME/aspcore2_parser.h $DIRNAME/aspcore2_parser.hpp $DIRNAME/../src/
