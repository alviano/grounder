#ifndef ASPCORE2_H_
#define ASPCORE2_H_

#include "common.h"
#include <cassert>
#include <cstdio>

#include "Program.h"
#include "Literal.h"

class AspCore2 {
public:
    static AspCore2& getInstance();
    static void free();

    Program* getProgram() { return program; }

    //virtual int parse(int filesSize, const char **files, Program& program);
    //virtual int parse(const string& filename, FILE *file);
    virtual int parse(Program& program);

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

    virtual Terms* onTerms(Term* term);
    virtual Terms* onTerms(Terms* terms, Term* term);

    virtual Atom* onAtom(const char* value);
    virtual Atom* onAtom(const char* value, Terms* terms);

    virtual Literal* onNafLiteral(Atom* atom, bool positive);

    virtual Literals* onNafLiterals(Literal* literal);
    virtual Literals* onNafLiterals(Literals* literals, Literal* literal);

    virtual Rule* onRule(Atom* head);
    virtual Rule* onRule(Atom* head, Literals* body);
    virtual Rule* onRule(Literals* body);

    virtual void addRule(Rule* rule);

private:
    static AspCore2* instance;

    AspCore2();
    AspCore2(const AspCore2&) { assert(0); }
    virtual ~AspCore2();

    int line;
    int errors ;
    string file;
    Program* program;

    bool ParserStateInternal;

};

#endif
