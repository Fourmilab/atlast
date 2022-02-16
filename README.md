# ATLAST — Embedded Threaded Language Toolkit

Atlast is an attempt to make software component technology and open
architecture applications commonplace in the mainstream software
market. It is both a software component which can be readily integrated
into existing applications, providing them a ready-made macro language
and facilities for user extension and customisation and, at the same
time, a foundation upon which new applications can be built in an
open, component-oriented manner.

Atlast was developed at Autodesk, Inc.  Autodesk returned the rights to
me in 1991, and I subsequently placed the program in the public domain.
Autodesk's connection with this program is purely historical: it is
neither endorsed, used, nor supported by Autodesk, Inc.  This edition
of Atlast, including a native 64-bit implementation and a 32-bit
version which can be run either on a 32-bit system or cross-compiled
for a 64-bit system, is released under the Creative Commons CC-SA
license as described in the file LICENSE.md.

Atlast is based upon the FORTH-83 language, but has been extended in
many ways and modified to better serve its mission as an embedded
toolkit for open, programmable applications.  Atlast is implemented in
a single file, written in portable C; it has been ported to many
different machines and operating systems, including MS-DOS, OS/2, the
Macintosh, and a wide variety of Unix machines.  Atlast includes native
support for floating point, C-like strings, Unix-compatible file
access, and a wide variety of facilities for embedding within
applications.  Integers are 32 bits (64 bits in the 64-bit version of
Atlast) and identifiers can be up to 127 characters; extensive stack
and heap pointer checking is available to aid in debugging.  Atlast may
be configured at compilation time to include only the facilities needed
by a given application, thus saving memory and increasing execution
speed (when error checking is disabled).

## 32- and 64-bit Versions

Atlast is available in either the original 32-bit version, maintained
in the atlast-32 directory, or in a native 64-bit version, in the
atlast-64 directory.  Because Atlast, like all FORTH-like languages,
provides low-level access to system memory, these two versions are not
source code compatible: in particular, in the 64-bit version integers,
pointers, and floating point numbers are all 64 bits in length and may
be manipulated by the same stack commands, while in the 32 bit version
floating point numbers occupy two adjacent 32 bit words and a set of
double word operators are used with them.

If you are confident the code you're developing will always run on
64-bit platforms, the 64-bit version is generally faster, easier to
program, and directly compatible with system libraries.  The 32-bit
version may be used on 64-bit platforms as long as a compiler able to
cross-compile to 32-bit code and the necessary compatibility libraries
are installed on the systems used to develop and deploy applications.

## Documentation

Due to language differences between the 32- and 64-bit versions of
Atlast, each has its own documentation.

* [Atlast 32-bit](https://www.fourmilab.ch/atlast/atlast.html)
* [Atlast 64-bit](https://www.fourmilab.ch/atlast/atlast2.html)
