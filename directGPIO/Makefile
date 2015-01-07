
CXX=g++

TARGET=mmapGpioTest
TARGET2=writeATR

INCLUDEDIR = ./  mmapGpioLib
LIBSOURCEDIR = mmapGpioLib
INCDIR  = $(patsubst %,-I%,$(INCLUDEDIR))

OPT = -O3
DEBUG = -g
WARN= -Wall

CXXFLAGS= $(OPT) $(DEBUG) $(WARN) $(INCDIR)

SRCMAIN =   mmapGpioTest.cpp
SRCMAIN2 =  writeATR.cpp
SRCLIB = $(LIBSOURCEDIR)/mmapGpio.cpp

OBJMAIN = $(SRCMAIN:.cpp=.o)
OBJMAIN2 = $(SRCMAIN2:.cpp=.o)
OBJLIB = $(SRCLIB:.cpp=.o)

all: $(OBJLIB) $(OBJMAIN) $(OBJMAIN2)
	    $(CXX)  $(OBJLIB) $(OBJMAIN) -o $(TARGET)
	    $(CXX)  $(OBJLIB) $(OBJMAIN2) -o $(TARGET2)

%$.o:%.cpp
	    $(CXX) $(CXXFLAGS)  -c $<  
		 
clean:
	    -rm *.o
		-rm $(LIBSOURCEDIR)/*.o
		-rm $(TARGET)
