GTEST_DIR = thirdparty/gtest-1.7.0
GMP_DIR = /usr/local/lib
AES_DIR = src/aes

# the compiler: gcc for C program, define as g++ for C++
CXX = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CXXFLAGS  = -O3 -g -Wall -Isrc -I$(GTEST_DIR)/include
LDFLAGS = -L$(GMP_DIR) -L$(AES_DIR) -L$(GTEST_DIR) -lgmp -lgmpxx -laes -lgtest

# the build target executable:
TARGET_TEST = bin/test
OBJ_TEST = src/tests.o \
           src/fte/ranker.o \
           src/ffx/key.o \
           src/ffx/ffx.o \
           src/fte/fte.o \
           src/tests/dfas.o \
           src/tests/test_errors.o \
           src/tests/test_fte.o \
           src/tests/test_ffx.o \
           src/tests/test_ranker.o

TARGET_MAIN = bin/main
OBJ_MAIN = src/main.o \
           src/fte/ranker.o \
           src/ffx/key.o \
           src/ffx/ffx.o \
           src/fte/fte.o \
           src/tests/dfas.o

OBJ_AES = src/aes/aes_modes.o \
          src/aes/aescrypt.o \
          src/aes/aeskey.o \
          src/aes/aestab.o

LIBAES = src/aes/libaes.a

all: $(GTEST_DIR)/libgtest.a $(LIBAES) $(TARGET_TEST) $(TARGET_MAIN)

$(GTEST_DIR)/libgtest.a:
	cd $(GTEST_DIR) && cmake . && $(MAKE)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TARGET_TEST): $(OBJ_TEST)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

$(TARGET_MAIN): $(OBJ_MAIN)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

$(LIBAES): $(OBJ_AES)
	ar rsc $(LIBAES) $(OBJ_AES)

test:
	@./$(TARGET_TEST)

clean:
	$(RM) $(TARGET_TEST)
	$(RM) $(OBJ_TEST)
	$(RM) $(TARGET_MAIN)
	$(RM) $(OBJ_MAIN)
	$(RM) $(LIBAES)
	$(RM) $(OBJ_AES)
