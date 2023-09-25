CXX = g++
CXXFLAGS = -g -Wall -O2
CXXPPFLAGS = -I ../../\
			 -I ./

MAIN_SOURCE = main.cpp
INTLIB_SOURCES = ../../bytearray.cpp  ../../tcpclient.cpp ../../interface.cpp

SOURCES = $(MAIN_SOURCE) $(INTLIB_SOURCES)
PROG = prog

all: $(PROG)

$(PROG): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(CXXPPFLAGS) $^ -o $@

clean:
	rm -f $(PROG)

