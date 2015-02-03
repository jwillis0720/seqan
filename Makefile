CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.o)))
CC_FLAGS += -MMD -Wall
CC_FLAGS +=-I./include/
LD_FLAGS += -lboost_filesystem -lboost_system
-include $(OBJ_FILES:.o=.d)

default: SeqIg
all: clean SeqIg

SeqIg: $(OBJ_FILES)
	g++ $(LD_FLAGS) -o $@ $^

build/%.o: src/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<

clean: 
	rm -rf build/*.o
	rm -rf build/*.d
	rm -rf SeqIg 