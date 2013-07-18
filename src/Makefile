BINARY=../bin/beetle
GCC=g++-4.7
CXX=$(GCC)
CXXFLAGS=-Wall -std=c++11 -g3 -O0 -Iinclude
LINK=$(GCC)
LINKFLAGS=-lm 

SRCS = \
 AspCore2.cpp\
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
 Output.cpp\
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

all: ../bin $(BINARY)

../bin:
	mkdir -p ../bin
	
%.d: %.cpp
	$(CXX) $(CXXFLAGS) -M $< >$@
	
$(BINARY): $(OBJS)
	$(LINK) $(LINKFLAGS) $(LIBS) $(OBJS) -o $(BINARY)

static: $(OBJS)
	$(LINK) $(LINKFLAGS) $(LIBS) $(OBJS) -static -o $(BINARY)


########## Parser

parser:
	../parser_src/make.sh

########## Clean

clean:
	rm -f $(OBJS)
	rm -f ../bin/gmon.out

distclean: clean
	rm -f $(BINARY) $(DEPS)

-include $(DEPS)

