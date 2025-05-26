# Makefile 변수 선언 (권장)
CXX = g++
CXXFLAGS = -Wall -g -O2
LDFLAGS = -lgmpxx -lgmp -pthread
TARGET = bqlwe
OBJS = struct.o util.o calc.o main.o

# 기본 타겟 (make만 입력했을 때 실행될 타겟)
all: $(TARGET)

# bqlwe 실행 파일을 만드는 규칙
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

# struct.o 오브젝트 파일을 만드는 규칙
struct.o: struct.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

# util.o 오브젝트 파일을 만드는 규칙
util.o: util.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# main.o 오브젝트 파일을 만드는 규칙
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# clean 타겟 (컴파일된 파일들 삭제)
clean:
	rm -f $(OBJS) $(TARGET)