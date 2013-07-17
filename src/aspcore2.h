#ifndef ASPCORE2_H_
#define ASPCORE2_H_

#include "common.h"
#include <cassert>
#include <cstdio>

#include "Program.h"

class AspCore2 {
public:
    static AspCore2* getInstance();

    virtual int parse(int filesSize, const char **files);
    virtual int parse(const string& filename, FILE *file);
    virtual int parse();

    virtual void onNewLine() { line++; }
    virtual int onError(const char* msg);
    virtual int onWrap();

    virtual Variable* onVariableTerm();
    virtual Variable* onVariableTerm(const char* value);

    virtual Term* onTerm();
    virtual Term* onTerm(int value);
    virtual Term* onTerm(const char* value);
    virtual Term* onTerm(const char* functor, Terms* terms);
    virtual Term* onTerm(Term* left, Term* right);
    virtual Term* onTermDash(Term* term);

private:
    static AspCore2* instance;

    AspCore2();
    AspCore2(const AspCore2&) { assert(0); }
    virtual ~AspCore2() {}

    int line;
    int errors ;
    string file;
    Program* program;

    bool ParserStateInternal;

};

#endif
