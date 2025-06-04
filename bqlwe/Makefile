# Makefile 변수 선언 (권장)
CXX = g++-13
CXXFLAGS = -Wall -g -O2 -MMD -MP -std=c++20
LDFLAGS = -lgmpxx -lgmp -pthread
TARGET = bqlwe

# 프로젝트의 모든 .cpp 파일을 자동으로 찾음
SOURCES = $(wildcard *.cpp)
# .cpp 목록으로부터 .o와 .d(의존성 파일) 목록을 생성
OBJS = $(SOURCES:.cpp=.o)
DEPS = $(SOURCES:.cpp=.d)

# 기본 타겟 (make만 입력했을 때 실행될 타겟)
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# .o 파일을 만드는 일반 규칙
# 컴파일 시 -MMD 플래그가 .d 의존성 파일을 자동으로 생성해줌
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	# .d 파일도 함께 삭제
	rm -f $(OBJS) $(DEPS) $(TARGET)

# 생성된 의존성 파일들을 Makefile에 포함시킴
# -include는 파일이 없어도 오류를 내지 않음
-include $(DEPS)