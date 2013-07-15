BINARY=../bin/beetle
GCC=g++-4.7
CXX=$(GCC)
CXXFLAGS=-Wall -std=c++11 -g3 -O0 -I../include -I../parser
LINK=$(GCC)
LINKFLAGS=-lm 

SRCS = \
 parser/ASPCore2_0Lexer.cpp\
 parser/ASPCore2_0Parser.cpp\
 Atom.cpp\
 Body.cpp\
 Clonable.cpp\
 Component.cpp\
 Constraint.cpp\
 DependenciesGraph.cpp\
 Indices.cpp\
 Literal.cpp\
 NormalRule.cpp\
 Predicate.cpp\
 Program.cpp\
 Rule.cpp\
 StandardLiteral.cpp\
 StandardNegativeLiteral.cpp\
 StandardPositiveLiteral.cpp\
 StringTerm.cpp\
 Term.cpp\
 Variable.cpp\
 main.cpp\
 

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

all: $(BINARY) 
	
%.d: %.cpp
	$(CXX) $(CXXFLAGS) -M $< >$@
	
$(BINARY): $(OBJS)
	$(LINK) $(LINKFLAGS) $(LIBS) $(OBJS) -o $(BINARY)

static: $(OBJS)
	$(LINK) $(LINKFLAGS) $(LIBS) $(OBJS) -static -o $(BINARY)

########## Clean

clean:
	rm -f *.o a.out
	rm -f gmon.out

distclean: clean
	rm -f $(BINARY)
	rm -f *.d

-include $(DEPS)

