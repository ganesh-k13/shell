CHECK := $(shell which clang++)

ifeq ($(CHECK),)
$(warning No clang++ found, consider apt-get install clang, using g++ now)
CC = g++
else
$(info using clang++ over g++)
CC = clang++
endif

IDIR=include
ODIR=obj
SRCDIR=src
LDIR=lib
CPPFLAGS=-lreadline

test:	$(ODIR)/test.o $(ODIR)/clt.o $(ODIR)/utils.o
		$(CC) -std=c++11 -o test -g $(ODIR)/test.o $(ODIR)/clt.o $(ODIR)/utils.o $(CPPFLAGS) `python2-config --cflags --ldflags`

$(ODIR)/test.o:	test.cpp
	$(CC) -std=c++11 -w -o $(ODIR)/test.o -c test.cpp $(CPPFLAGS) `python2-config --cflags --ldflags`

$(ODIR)/clt.o:	$(SRCDIR)/clt.cpp $(IDIR)/clt.h
	$(CC) -std=c++11 -w -o $(ODIR)/clt.o -c $(SRCDIR)/clt.cpp $(CPPFLAGS) `python2-config --cflags --ldflags`

$(ODIR)/utils.o:	$(SRCDIR)/utils.cpp $(IDIR)/utils.h
	$(CC) -std=c++11 -w -o $(ODIR)/utils.o -c $(SRCDIR)/utils.cpp `python2-config --cflags --ldflags`

clean:
	rm -f $(ODIR)/*.o
	rm test
