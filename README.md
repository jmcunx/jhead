## jhead - clone of head(1)

jhead is a clone of head(1) for systems that
does not have a full featured head(1).
But it may have a couple of options not
found in head(1).

If head(1) exists on your system, you should use that instead.
It will be much faster.

To build, execute build.sh to generate a Makefile from
Makefile.template on most BSD/Linux systems and IBM AIX.
For MS-DOS, it should be rather easy to create a Makefile.

This requires [j\_lib2](https://github.com/jmcunx/j_lib2) to build.

[GNU automake](https://en.wikipedia.org/wiki/Automake)
only confuses me, so I came up with my own method which
is a real hack.  But works for me.
