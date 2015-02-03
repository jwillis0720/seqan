###it has to be libstdc++ because boost was compiled with gcc, if boost was compiled with something else, let it be someth libc++ I think
GXX = clang++ -stdlib=libstdc++
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.o)))
CC_FLAGS += -MMD -Wall
CC_FLAGS += -g
CC_FLAGS +=-I./include/
CC_FLAGS +=-I/Users/jordanwillis/Git_repos/boost/
CC_FLAGS +=-I/usr/local/include/
LD_FLAGS +=-L/Users/jordanwillis/Git_repos/boost/stage/lib/
LD_FLAGS += -lboost_filesystem -lboost_system -L/usr/local/lib
-include $(OBJ_FILES:.o=.d)

default: SeqIg
all: SeqIg

SeqIg: $(OBJ_FILES)
	$(GXX) $(LD_FLAGS) -o $@ $^

build/%.o: src/%.cpp
	$(GXX) $(CC_FLAGS) -c -o $@ $<

clean: 
	rm -rf build/*.o
	rm -rf build/*.d
	rm -rf SeqIg 
