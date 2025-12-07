CXXFLAGS= -Wall -Wextra -pedantic -std=c++23

laba5: laba5_utf8.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
