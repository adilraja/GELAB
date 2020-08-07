
# Makefile for the libGE intertwined spirals example using the GALib
# evolutionary library.
# If you are using this Makefile as a starting point for another
# libGE application, you may wish to check the settings below.


# General options.
OBJECTS           = main.o initfunc.o GEListGenome.o
#HEADERS           =

# General compiler options.
#CC                = gcc
#CXX               = g++
CFLAGS           += -Wall -O2
CXXFLAGS         += -Wall -O2
#LDFLAGS          +=

# GALib options.
#CXXFLAGS         += -IGALIB_INCLUDE_DIR
#LDFLAGS          += -LGALIB_LIB_DIR
LIBS             += -lga

# libGE options.
#CXXFLAGS         += -ILIBGE_INCLUDE_DIR
#LDFLAGS          += -LLIBGE_LIB_DIR
LIBS             += -lGE


# ---

# GEGCC options.
GEGCC_OBJECTS     = $(OBJECTS) spiral-gcc.o
GEGCC_EVAL_OBJECT = gcc_GEspiral.o
GEGCC_HEADERS     = $(HEADERS) $(GEGCC_EVAL_HDR)
GEGCC_CXXFLAGS    = $(CXXFLAGS)
GEGCC_LDFLAGS     = $(LDFLAGS)
GEGCC_LIBS        = $(LIBS)

# ---

# TCC options.
TCC               = tcc
TCC_CFLAGS       = $(CFLAGS)

# GETCC options.
GETCC_OBJECTS     = $(OBJECTS) spiral-tcc.o
GETCC_EVAL_OBJECT = tcc_GEspiral.o
GETCC_HEADERS     = $(HEADERS) $(GETCC_EVAL_HDR)
GETCC_CXXFLAGS    = $(CXXFLAGS) -DGESPIRAL_USE_TCC_COMP
GETCC_LDFLAGS     = $(LDFLAGS)
GETCC_LIBS        = $(LIBS)

# ---

# libTCC options.
#LIBTCC_CXXFLAGS   = -ILIBTCC_INCLUDE_DIR
#LIBTCC_LDFLAGS    = -LLIBTCC_LIB_DIR
LIBTCC_LIBS       = -ltcc -ldl

# GELIBTCC options.
GELIBTCC_OBJECTS  = $(OBJECTS) spiral-libtcc.o
GELIBTCC_HEADERS  = $(HEADERS) $(GELIBTCC_EVAL_HDR)
GELIBTCC_CXXFLAGS = $(CXXFLAGS) $(LIBTCC_CXXFLAGS)
GELIBTCC_LDFLAGS  = $(LDFLAGS) $(LIBTCC_LDFLAGS)
GELIBTCC_LIBS     = $(LIBS) $(LIBTCC_LIBS)

# ---

# S-Lang options.
#SLANG_CXXFLAGS    = -ISLANG_INCLUDE_DIR
#SLANG_LDFLAGS     = -LSLANG_LIB_DIR
SLANG_LIBS        = -lslang

# GESLANG options.
GESLANG_OBJECTS   = $(OBJECTS) spiral-slang.o
GESLANG_HEADERS   = $(HEADERS)
GESLANG_CXXFLAGS  = $(CXXFLAGS) $(SLANG_CXXFLAGS)
GESLANG_LDFLAGS   = $(LDFLAGS) $(SLANG_LDFLAGS)
GESLANG_LIBS      = $(LIBS) $(SLANG_LIBS)

# ---

# lua options.
#LUA_CXXFLAGS      = -ILUA_INCLUDE_DIR
#LUA_LDFLAGS       = -LLUA_LIBDIR_DIR
LUA_LIBS          = -llua -ldl

# GELUA options.
GELUA_OBJECTS     = $(OBJECTS) spiral-lua.o
GELUA_HEADERS     = $(HEADERS) $(GELUA_EVAL_HDR)
GELUA_CXXFLAGS    = $(CXXFLAGS) $(LUA_CXXFLAGS)
GELUA_LDFLAGS     = $(LDFLAGS) $(LUA_LDFLAGS)
GELUA_LIBS        = $(LIBS) $(LUA_LIBS)

# ---


default:all

all:    GEGCC GETCC GESLANG GELIBTCC GELUA

GEGCC:  $(GEGCC_OBJECTS) $(GEGCC_EVAL_OBJECT) $(GEGCC_HEADERS)
	$(CXX) $(GEGCC_LDFLAGS) -o $@ $(GEGCC_OBJECTS) $(GEGCC_LIBS)

GETCC:  $(GETCC_OBJECTS) $(GETCC_EVAL_OBJECT) $(GETCC_HEADERS)
	$(CXX) $(GETCC_LDFLAGS) -o $@ $(GETCC_OBJECTS) $(GETCC_LIBS)

GELIBTCC: $(GELIBTCC_OBJECTS) $(GELIBTCC_EVAL_OBJECT) $(GELIBTCC_HEADERS)
	$(CXX) $(GELIBTCC_LDFLAGS) -o $@ $(GELIBTCC_OBJECTS) $(GELIBTCC_LIBS)

GESLANG:$(GESLANG_OBJECTS) $(GESLANG_HEADERS)
	$(CXX) $(GESLANG_LDFLAGS) -o $@	$(GESLANG_OBJECTS) $(GESLANG_LIBS)

GELUA:  $(GELUA_OBJECTS) $(GELUA_HEADERS)
	$(CXX) $(GELUA_LDFLAGS) -o $@ $(GELUA_OBJECTS) $(GELUA_LIBS)

clean:
	rm -f *~ *.o a.out cc-output.dat stats\
	GEGCC GETCC GESLANG GELIBTCC GELUA

# ---


# GEGCC dependencies.

spiral-gcc.o: spiral-gcc.cpp
	$(CXX) -c $(GEGCC_CXXFLAGS) -o $@ $<

gcc_GEspiral.o: GEspiral.c
	$(CC) -c $(CFLAGS) -o $@ $<


# GETCC dependencies.

spiral-tcc.o: spiral-gcc.cpp
	$(CXX) -c $(GETCC_CXXFLAGS) -o $@ $<

tcc_GEspiral.o: GEspiral.c
	$(TCC) -c $(TCC_CFLAGS) -o $@ $<


# GELIBTCC dependencies.

spiral-libtcc.o: spiral-libtcc.cpp
	$(CXX) -c $(GELIBTCC_CXXFLAGS) -o $@ $<


# GESLANG dependencies.

spiral-slang.o: spiral-slang.cpp
	$(CXX) -c $(GESLANG_CXXFLAGS) -o $@ $<


# GELUA dependencies.

spiral-lua.o: spiral-lua.cpp
	$(CXX) -c $(GELUA_CXXFLAGS) -o $@ $<
