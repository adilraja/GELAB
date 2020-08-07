## Process this file with automake to produce Makefile.in

###############################################################################
# ALL DIRS TO BUILD MAKEFILE AND COMPILE
###############################################################################
SUBDIRS = .

AM_CPPFLAGS = -Wall -pg

###############################################################################
# SOURCE FILES
###############################################################################

lib_LIBRARIES = libGE.a
GEdir = $(includedir)/GE

GE_HEADERS = src/libGEdefs.h src/ge.h src/Genotype.h src/Phenotype.h src/Symbol.h src/Production.h src/Rule.h src/Mapper.h src/Grammar.h src/Tree.h src/CFGrammar.h src/GEGrammar.h src/Initialiser.h src/GEGrammarSI.h
libGE_a_SOURCES = $(GE_HEADERS) src/Genotype.cpp src/Phenotype.cpp src/Symbol.cpp src/Production.cpp src/Rule.cpp src/Mapper.cpp src/Grammar.cpp src/CFGrammar.cpp src/GEGrammar.cpp src/Initialiser.cpp src/GEGrammarSI.cpp

###############################################################################
# DOCUMENTATION FILES
###############################################################################
info_TEXINFOS = doc/libGE.texi
libGE_TEXINFOS = doc/fdl.texi doc/readme.texi doc/install.texi
EXTRA_DIST = doc/*.texi doc/*.pdf doc/*.eps doc/*.txt
EXTRA_DIST += WRAPPERS/ILLIGAL/README WRAPPERS/MIT/README

###############################################################################
# EXAMPLE FILES
###############################################################################
EXTRA_DIST += EXAMPLES/SantaFeAntTrail/GE_EO/Makefile
EXTRA_DIST += EXAMPLES/SantaFeAntTrail/GE_EO/*.*
EXTRA_DIST += EXAMPLES/SantaFeAntTrail/GE_ILLIGALSGA/Makefile
EXTRA_DIST += EXAMPLES/SantaFeAntTrail/GE_ILLIGALSGA/*.*
EXTRA_DIST += EXAMPLES/SantaFeAntTrail/GE_MITGALIB/Makefile
EXTRA_DIST += EXAMPLES/SantaFeAntTrail/GE_MITGALIB/*.*
EXTRA_DIST += EXAMPLES/CartCentering/GE_EO/Makefile
EXTRA_DIST += EXAMPLES/CartCentering/GE_EO/*.*
EXTRA_DIST += EXAMPLES/CartCentering/GE_ILLIGALSGA/Makefile
EXTRA_DIST += EXAMPLES/CartCentering/GE_ILLIGALSGA/*.*
EXTRA_DIST += EXAMPLES/CartCentering/GE_MITGALIB/Makefile
EXTRA_DIST += EXAMPLES/CartCentering/GE_MITGALIB/*.*
EXTRA_DIST += EXAMPLES/CartCentering/grammars/*.*
EXTRA_DIST += EXAMPLES/IntertwinedSpirals/GE_EO/Makefile
EXTRA_DIST += EXAMPLES/IntertwinedSpirals/GE_EO/*.*
EXTRA_DIST += EXAMPLES/IntertwinedSpirals/GE_MITGALIB/Makefile
EXTRA_DIST += EXAMPLES/IntertwinedSpirals/GE_MITGALIB/*.*

###############################################################################
# CONFIGURE SCRIPT OPTIONS
###############################################################################
if ILLIGALSGA_WRAPPER
libGE_a_SOURCES += src/GE_ILLIGALSGA.cpp
GE_HEADERS += src/GE_ILLIGALSGA.h
endif
#if MITGALIB_WRAPPER
#libGE_a_SOURCES += src/GE_MITGALIB.cpp
#GE_HEADERS += src/GE_MITGALIB.h
#endif

