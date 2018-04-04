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
OPT1=-L/usr/lib/python2.7/config-x86_64-linux-gnu -L/usr/lib -lpython2.7 -lpthread -ldl  -lutil -lm  -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions
OPT2=-I/usr/include/python2.7 -I/usr/include/x86_64-linux-gnu/python2.7  -fno-strict-aliasing -Wdate-time -D_FORTIFY_SOURCE=2 -g -fstack-protector-strong -Wformat -Werror=format-security  -DNDEBUG -g -fwrapv -O2 -Wall

test:	$(ODIR)/test.o $(ODIR)/clt.o $(ODIR)/utils.o
		$(CC) -std=c++11 -o test -g $(ODIR)/test.o $(ODIR)/clt.o $(ODIR)/utils.o $(CPPFLAGS) $(OPT1) $(OPT2)

$(ODIR)/test.o:	test.cpp
	$(CC) -std=c++11 -w -o $(ODIR)/test.o -c test.cpp $(CPPFLAGS) $(OPT1) $(OPT2)

$(ODIR)/clt.o:	$(SRCDIR)/clt.cpp $(IDIR)/clt.h
	$(CC) -std=c++11 -w -o $(ODIR)/clt.o -c $(SRCDIR)/clt.cpp $(CPPFLAGS) $(OPT1) $(OPT2)

$(ODIR)/utils.o:	$(SRCDIR)/utils.cpp $(IDIR)/utils.h
	$(CC) -std=c++11 -w -o $(ODIR)/utils.o -c $(SRCDIR)/utils.cpp $(OPT1) $(OPT2)

clean:
	rm -f $(ODIR)/*.o
	rm test
# test:	$(ODIR)/test.o $(ODIR)/clt.o $(ODIR)/utils.o
# 		$(CC) -std=c++11 -o test -g $(ODIR)/test.o $(ODIR)/clt.o $(ODIR)/utils.o $(CPPFLAGS) `python2-config --cflags --ldflags`

# $(ODIR)/test.o:	test.cpp
# 	$(CC) -std=c++11 -w -o $(ODIR)/test.o -c test.cpp $(CPPFLAGS) `python2-config --cflags --ldflags`

# $(ODIR)/clt.o:	$(SRCDIR)/clt.cpp $(IDIR)/clt.h
# 	$(CC) -std=c++11 -w -o $(ODIR)/clt.o -c $(SRCDIR)/clt.cpp $(CPPFLAGS) `python2-config --cflags --ldflags`

# $(ODIR)/utils.o:	$(SRCDIR)/utils.cpp $(IDIR)/utils.h
# 	$(CC) -std=c++11 -w -o $(ODIR)/utils.o -c $(SRCDIR)/utils.cpp `python2-config --cflags --ldflags`

# clean:
# 	rm -f $(ODIR)/*.o
# 	rm test
