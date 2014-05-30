clasp
=====

A Lisp interpreter written in C.

Wrote it inspired by [this post about writing an interpreter in Python](http://www.michaelnielsen.org/ddi/lisp-as-the-maxwells-equations-of-software/).  As I explain [here](http://faehnri.ch/all-but-finished-with-clasp/), didn't feel I learned all I could blindly following the tutorial, failed horribly trying it in C#, so finally tried in C after reading The C Programming Language.

Why the name "clasp"?  Because the name "[clisp](http://www.clisp.org/)" was already taken.

##Commands

I implement the same commands they have in that post.

* +,-,*,/
* >, <
* eq?
* atom?
* null?
* car
* cdr
* cond
* cons
* quote
* define
* set!
* begin
* if
* lambda