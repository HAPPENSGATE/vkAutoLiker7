
MF=	Makefile

CC=	g++

CFLAGS=-I$(HOME)/local_software/include
LFLAGS=-L$(HOME)/local_software/lib -lquickfix
PREPROC=

EXE=	prog
SRC=	Application.cpp \
		Market.cpp \
		ordermatch.cpp

OBJ=	$(SRC:.cpp=.o)

INC=	IDGenerator.h \
		Order.h \
		OrderMatcher.h \


.SUFFIXES:
.SUFFI