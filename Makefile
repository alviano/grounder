BINARY=bin/beetle
GCC=g++-4.7
CXX=$(GCC)
CXXFLAGS=-Wall -std=c++11 -g3 -O0 -Iinclude
LINK=$(GCC)
LINKFLAGS=-lm 

SRCS = \
 src/aspcore2.cpp\
 src/Atom.cpp\
 src/Body.cpp\
 src/Clonable.cpp\
 src/Component.cpp\
 src/Constraint.cpp\
 src/DependenciesGraph.cpp\
 src/Indices.cpp\
 src/Literal.cpp\
 src/NormalRule.cpp\
 src/Predicate.cpp\
 src/Program.cpp\
 src/Rule.cpp\
 src/StandardLiteral.cpp\
 src/StandardNegativeLiteral.cpp\
 src/StandardPositiveLiteral.cpp\
 src/StringTerm.cpp\
 src/Term.cpp\
 src/Variable.cpp\
 src/main.cpp\
 

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

all: bin $(BINARY)

bin:
	mkdir -p bin
	
%.d: %.cpp
	$(CXX) $(CXXFLAGS) -M $< >$@
	
$(BINARY): $(OBJS)
	$(LINK) $(LINKFLAGS) $(LIBS) $(OBJS) -o $(BINARY)

static: $(OBJS)
	$(LINK) $(LINKFLAGS) $(LIBS) $(OBJS) -static -o $(BINARY)


########## Parser

parser:
	./parser_src/make.sh
	touch src/aspcore2.cpp

########## Clean

clean:
	rm -f $(OBJS)
	rm -f bin/gmon.out

distclean: clean
	rm -f $(BINARY) $(DEPS)

-include $(DEPS)

