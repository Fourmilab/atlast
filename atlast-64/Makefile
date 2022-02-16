
#	Unix makefile for ATLAST

VERSION = 2.0

COPTIONS = -g -Wall
#COPTIONS = -O3 -Wall
CC = gcc

LIBRARIES = -lm

INCLUDE =

ATLCONFIG = -DMEMSTAT -DEXPORT -DREADONLYSTRINGS

CFLAGS = $(COPTIONS) $(INCLUDE) $(ATLCONFIG)

ATLOBJ = atlast.o atlmain.o

APPS = atlast primdeftest

all:	$(APPS)

atlast: $(ATLOBJ)
	$(CC) $(CFLAGS) $(ATLOBJ) -o atlast $(LIBRARIES)

atlast.o:   atlast.c atldef.h
atldef.h:   atlast.h
atlmain.o:  atlmain.c atlast.h

primdeftest: primdeftest.c atldef.h
	$(CC) $(CFLAGS) primdeftest.c atlast.c -o primdeftest $(LIBRARIES)

#	Run the Atlast regression test

check:
	echo testcons >/tmp/regin.tmp
	echo Test 1234 >>/tmp/regin.tmp
	echo ls atlast.c >>/tmp/regin.tmp
	echo  >>/tmp/regin.tmp
	echo  >>/tmp/regin.tmp
	./atlast -iregression/regress.atl </tmp/regin.tmp >/tmp/regout.tmp
	diff regression/regout.txt /tmp/regout.tmp

clean:
	rm -f $(APPS)
	rm -f *.bak *.o *.dvi *.aux *.log
	rm -f core core.* cscope.out *.tar.gz
	rm -rf dist
	( cd benchmark ; make clean )
	
dist:	clean
	rm -rf dist
	mkdir dist
	mkdir dist/atlast-$(VERSION)
	mkdir dist/atlast-$(VERSION)/benchmark
	mkdir dist/atlast-$(VERSION)/examples
	mkdir dist/atlast-$(VERSION)/regression
	cp -p benchmark/* dist/atlast-$(VERSION)/benchmark
	cp -p examples/* dist/atlast-$(VERSION)/examples
	cp -p regression/* dist/atlast-$(VERSION)/regression
	cp -p atlast.c atlast.h atldef.h \
		atlast2.html \
		atlmain.c log.txt Makefile MANIFEST \
		primdeftest.c \
	      dist/atlast-$(VERSION)
	find dist -type f -exec chmod 644 {} \;
	( cd dist ; tar cfvz ../atlast-$(VERSION).tar.gz atlast-$(VERSION) )
	rm -rf dist
