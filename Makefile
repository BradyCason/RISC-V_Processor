CXX = g++
CXX_FLAGS = -std=c++23 -I ./components

CMP_SRCS = $(wildcard components/*.cpp)
CMP_OBJS = $(patsubst %.cpp,lib/%.o,$(CMP_SRCS))

PRC_SRCS = $(wildcard processors/*.cpp)
PRC_OBJS = $(patsubst %.cpp,lib/%.o,$(PRC_SRCS))

all: lib main
main: $(CMP_OBJS) $(PRC_OBJS)
	${CXX} ${CXX_FLAGS} main.cpp -o main $(CMP_OBJS) $(PRC_OBJS)
lib/%.o: %.cpp | lib/components lib/processors
	$(CXX) $(CXX_FLAGS) -c $< -o $@
lib:
	@if not exist lib mkdir lib
lib/components:
	@if not exist lib\components mkdir lib\components
lib/processors:
	@if not exist lib\processors mkdir lib\processors
clean:
	@if exist lib rd /s /q lib
	@if exist main del main
