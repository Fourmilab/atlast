
#	Unix makefile for ATLAST

VERSION = 1.2

#	Use -m32 to build 32-bit version on 64-bit platform
COPTIONS = -g -Wall -m32
CC = gcc

LIBRARIES = -lm

INCLUDE =

ATLCONFIG = -DMEMSTAT -DALIGNMENT -DEXPORT -DREADONLYSTRINGS

CFLAGS = $(COPTIONS) $(INCLUDE) $(ATLCONFIG)

ATLOBJ = atlast.o atlmain.o

APPS = atlast primdeftest

all:	$(APPS)

atlast: $(ATLOBJ)
	$(CC) $(CFLAGS) $(ATLOBJ) -o atlast $(LIBRARIES)

atlast.o:   atlast.c atldef.h
atldef.h:   atlast.h
atlmain.o:  atlmain.c atlast.h

primdeftest:
	$(CC) $(CFLAGS) primdeftest.c atlast.c -o primdeftest $(LIBRARIES)

#	Run the Atlast regression test

check:
	echo testcons >/tmp/regin.tmp
	echo Test 1234 >>/tmp/regin.tmp
	echo ls atlast.c >>/tmp/regin.tmp
	echo  >>/tmp/regin.tmp
	echo  >>/tmp/regin.tmp
	./atlast -iregress </tmp/regin.tmp >/tmp/regout.tmp
	diff regout.txt /tmp/regout.tmp

clean:
	rm -f $(APPS)
	rm -f *.bak *.o *.dvi *.aux *.log
	rm -f core core.* cscope.out *.tar.gz
	rm -rf dist
	
dist:
	rm -rf dist
	mkdir dist
	mkdir dist/atlast-$(VERSION)
	cp -p atlast.c atlast.h atldef.h \
		atlast.html \
		atlmain.c log.txt Makefile MANIFEST \
		primdeftest.c \
		regout.txt regress.atl dist/atlast-$(VERSION)
	find dist -type f -exec chmod 644 {} \;
	( cd dist ; tar cfvz ../atlast-$(VERSION).tar.gz atlast-$(VERSION) )
	rm -rf dist

lint:	lintatlast

lintatlast:
	lint atlast.c atlmain.c $(LIBRARIES) $(ATLCONFIG)
