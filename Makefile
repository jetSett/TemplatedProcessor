CXX = g++-4.9
CXXFLAGS = -Wall -fexceptions -ftemplate-depth=1000000000 -std=c++14
LDFLAGS=
EXEC=Processeur
PWD = $(shell pwd)
SRC= $(wildcard $(PWD)/*.cpp $(PWD)/Operands/*.cpp )
OBJ = $(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $< 

clean:
	@rm -rf $(OBJ)
