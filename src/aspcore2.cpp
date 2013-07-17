#include "aspcore2.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Helper functions as expected by LEX/FLEX

extern "C" int yywrap()    // End-of-file handler for LEX
    {
    return AspCore2::getInstance()->onWrap();
    }

extern "C" FILE* yyin;     // Where LEX reads its input from

//////////////////////////////////////////////////////////////////////////////
// Helper functions as expected by YACC/BISON

int yyerror(const char* s) // Error handler for YACC
{
    return AspCore2::getInstance()->onError(s);
}

#include "aspcore2_lexer.hpp"
#include "aspcore2_parser.hpp"


/////////////////////////////////////////////////////////////////////////////
// Class

AspCore2* AspCore2::instance = NULL;

AspCore2*
AspCore2::getInstance() {
    if(instance == NULL)
        instance = new AspCore2();
    return instance;
}

AspCore2::AspCore2()
: line(0),
  errors(0),
  program(NULL) {

}

int
AspCore2::onError(
        const char* msg) {
    errors++;

    if( !ParserStateInternal )
        {
        if(file.length() > 0 )
            cerr << file << ": ";
        cerr << "line " << line;

        cerr << ": ";
        }
    else
        cerr << "Internal parser invocation: ";

    cerr << msg << "." << endl;

    return 0;
}

int
AspCore2::onWrap() {
    return 1;
}

int
AspCore2::parse(
    int filesSize,
    const char **files) {
    for(int i = 1; i < filesSize; i++) {
        FILE *file = fopen(files[i], "r");
        if(file) {
            int res = this->parse(files[i], file);
            fclose(file);
            if(res != 0)
                return res;
        }
        else {
            this->onError("Can't open input");
            return -1;
        }
    }
    return 0;
}

int
AspCore2::parse(
    const string& filename,
    FILE *file) {
    yyin = file;
    this->file = filename;
    this->line = 1;
    yyparse();

    if(this->errors > 0) {
        cerr << "Aborting due to parser errors." << endl;
        return -1;
    }
    return 0;
}

int
AspCore2::parse() {
    assert(program == NULL);
    this->program = new Program();

    yyin = stdin;
    this->file = "STDIN";
    this->line = 1;
    yyparse();

    if(this->errors > 0) {
        cerr << "Aborting due to parser errors." << endl;
        return -1;
    }
    return 0;
}

Variable*
AspCore2::onVariableTerm() {
    return new Variable("ricca");
}

Variable*
AspCore2::onVariableTerm(
        const char* value) {
    Variable* res = new Variable(value);
    delete[] value;
    return res;
}

Term*
AspCore2::onTerm() {
    // FIXME
    return NULL;
}

Term*
AspCore2::onTerm(
        int value) {
    // FIXME
    return NULL;
}

Term*
AspCore2::onTerm(
        const char* value) {
    assert(value != NULL);
    assert(strlen(value) > 0);
    Term* res = NULL;
    if('A' <= value[0] && value[0] <= 'Z')
        res = new Variable(value);
    else
        res = new StringTerm(program->createStringTerm(value));
    delete[] value;
    return res;
}

Term*
AspCore2::onTerm(
        const char* functor,
        Terms* terms) {
    // FIXME
    return NULL;
}

Term*
AspCore2::onTerm(
        Term* left,
        Term* right) {
    // FIXME
    return NULL;
}

Term*
AspCore2::onTermDash(
        Term* term) {
    // FIXME
    return NULL;
}
