#include "AspCore2.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>

#include "Atom.h"
#include "StandardPositiveLiteral.h"
#include "StandardNegativeLiteral.h"
#include "NormalRule.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Helper functions as expected by LEX/FLEX

extern "C" int yywrap()    // End-of-file handler for LEX
    {
    return AspCore2::getInstance().onWrap();
    }

extern "C" FILE* yyin;     // Where LEX reads its input from

//////////////////////////////////////////////////////////////////////////////
// Helper functions as expected by YACC/BISON

int yyerror(const char* s) // Error handler for YACC
{
    return AspCore2::getInstance().onError(s);
}

#include "aspcore2_lexer.hpp"
#include "aspcore2_parser.hpp"

/////////////////////////////////////////////////////////////////////////////
// Class

AspCore2* AspCore2::instance = NULL;

AspCore2&
AspCore2::getInstance() {
    if(instance == NULL)
        instance = new AspCore2();
    return *instance;
}

void
AspCore2::free() {
    if(instance != NULL) {
        assert(instance->program == NULL);
        delete instance;
        instance = NULL;
        yylex_destroy();
    }
}

AspCore2::AspCore2()
: line(0),
  errors(0),
  program(NULL) {

}

AspCore2::~AspCore2() {
    assert(program == NULL);
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

/*
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
    fclose(yyin);

    if(this->errors > 0) {
        cerr << "Aborting due to parser errors." << endl;
        return -1;
    }
    return 0;
}
*/

int
AspCore2::parse(
        Program& program) {
    assert(this->program == NULL);
    this->program = &program;

    yyin = stdin;
    //this->file = "STDIN";
    this->line = 1;
    yyparse();
    this->program = NULL;

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
    return onVariableTerm();
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
    if('A' <= value[0] && value[0] <= 'Z')
        return onVariableTerm(value);

    Term* res = new StringTerm(program->createStringTerm(value));
    delete[] value;
    return res;
}

Term*
AspCore2::onTerm(
        const char* functor,
        Terms* terms) {
    // FIXME
    delete[] functor;
    delete terms;
    return NULL;
}

Term*
AspCore2::onTerm(
        Term* left,
        Term* right) {
    // FIXME
    delete left;
    delete right;
    return NULL;
}

Term*
AspCore2::onTermDash(
        Term* term) {
    // FIXME
    delete term;
    return NULL;
}

Terms*
AspCore2::onTerms(
        Term* term) {
    Terms* res = new Terms();
    res->push_back(term);
    return res;
}

Terms*
AspCore2::onTerms(
        Terms* terms,
        Term* term) {
    terms->push_back(term);
    return terms;
}

Atom*
AspCore2::onAtom(
        const char* value) {
    Atom* res = new Atom(program->createPredicate(value), Terms());
    delete[] value;
    return res;
}

Atom*
AspCore2::onAtom(
        const char* value,
        Terms* terms) {
    Atom* res = new Atom(program->createPredicate(value), *terms);
    delete[] value;
    delete terms;
    return res;
}

Literal*
AspCore2::onNafLiteral(
        Atom* atom,
        bool positive) {
    Literal* res = NULL;
    if(positive)
        res = new StandardPositiveLiteral(*atom);
    else
        res = new StandardNegativeLiteral(*atom);
    delete atom;
    return res;
}

Literals*
AspCore2::onNafLiterals(
        Literal* literal) {
    Literals* res = new Literals();
    res->push_back(literal);
    return res;
}

Literals*
AspCore2::onNafLiterals(
        Literals* literals,
        Literal* literal) {
    literals->push_back(literal);
    return literals;
}

Rule*
AspCore2::onRule(
        Atom* head) {
    Rule* res = new NormalRule(*head, Body());
    delete head;
    return res;
}

Rule*
AspCore2::onRule(
        Atom* head,
        Literals* body) {
    Rule* res = new NormalRule(*head, *body);
    delete head;
    delete body;
    return res;
}

Rule*
AspCore2::onRule(
        Literals* body) {
    Rule* res = new NormalRule(Atom(program->getFalsePredicate()), *body);
    delete body;
    return res;
}

void
AspCore2::addRule(
        Rule* rule) {
    program->addRule(rule);
}
