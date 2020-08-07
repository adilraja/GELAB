
# Makefile for the libGE Cart Centering example using the EO
# evolutionary library.
# If you are using this Makefile as a starting point for another
# libGE application, you may wish to check the settings below.


# General options.
HEADERS           = eoGE.h eoGEInit.h eoGEMutation.h eoGEQuadCrossover.h
GEGCC_EVAL_HDR    = eoGEEvalFunc-gcc_tcc.h
GETCC_EVAL_HDR    = eoGEEvalFunc-gcc_tcc.h
GESLANG_EVAL_HDR  = eoGEEvalFunc-slang.h
GELIBTCC_EVAL_HDR = eoGEEvalFunc-libtcc.h
GELUA_EVAL_HDR    = eoGEEvalFunc-lua.h

# General compiler options.
#CC                = gcc
#CXX               = g++
CFLAGS          += -Wall -O2
CXXFLAGS         += -Wall -O2
#LDFLAGS          +=

# EO options.
#CXXFLAGS         += -IEO_INCLUDE_DIR
#LDFLAGS          += -LEO_LIB_DIR
LIBS             += -leoutils -leo

# libGE options.
#CXXFLAGS         += -ILIBGE_INCLUDE_DIR
#LDFLAGS          += -LLIBGE_LIB_DIR
LIBS             += -lGE

# ---

# GEGCC options.
GEGCC_OBJECTS     = gegcc_main.o
GEGCC_EVAL_OBJECTS= gcc_GEspiral.o
GEGCC_HEADERS     = $(HEADERS) $(GEGCC_EVAL_HDR)
GEGCC_CXXFLAGS    = $(CXXFLAGS) -include $(GEGCC_EVAL_HDR)
GEGCC_LDFLAGS     = $(LDFLAGS)
GEGCC_LIBS        = $(LIBS)

# ---

# TCC options.
TCC               = tcc
TCC_CFLAGS       = $(CFLAGS)

# GETCC options.
GETCC_OBJECTS     = getcc_main.o 
GETCC_EVAL_OBJECTS= tcc_GEspiral.o
GETCC_HEADERS     = $(HEADERS) $(GETCC_EVAL_HDR)
GETCC_CXXFLAGS    = $(CXXFLAGS) -include $(GETCC_EVAL_HDR) -DGESPIRAL_USE_TCC_COMP
GETCC_LDFLAGS     = $(LDFLAGS)
GETCC_LIBS        = $(LIBS)

# ---

# libTCC options.
#LIBTCC_CXXFLAGS   = -ILIBTCC_INCLUDE_DIR
#LIBTCC_LDFLAGS    = -LLIBTCC_LIB_DIR
LIBTCC_LIBS       = -ltcc -ldl

# GELIBTCC options.
GELIBTCC_OBJECTS  = gelibtcc_main.o
GELIBTCC_EVAL_OBJECTS= tcc_GEspiral.o
GELIBTCC_HEADERS  = $(HEADERS) $(GELIBTCC_EVAL_HDR)
GELIBTCC_CXXFLAGS = $(CXXFLAGS) $(LIBTCC_CXXFLAGS) -include $(GELIBTCC_EVAL_HDR)
GELIBTCC_LDFLAGS  = $(LDFLAGS) $(LIBTCC_LDFLAGS)
GELIBTCC_LIBS     = $(LIBS) $(LIBTCC_LIBS)

# ---

# S-Lang options.
#SLANG_CXXFLAGS    = -ISLANG_INCLUDE_DIR
#SLANG_LDFLAGS     = -LSLANG_LIB_DIR
SLANG_LIBS        = -lslang

# GESLANG options.
GESLANG_OBJECTS   = geslang_main.o
GESLANG_HEADERS   = $(HEADERS) $(GESLANG_EVAL_HDR)
GESLANG_CXXFLAGS  = $(CXXFLAGS) $(SLANG_CXXFLAGS) -include $(GESLANG_EVAL_HDR)
GESLANG_LDFLAGS   = $(LDFLAGS) $(SLANG_LDFLAGS)
GESLANG_LIBS      = $(LIBS) $(SLANG_LIBS)

# ---

# lua options.
#LUA_CXXFLAGS      = -ILUA_INCLUDE_DIR
#LUA_LDFLAGS       = -LLUA_LIB_DIR
LUA_LIBS          = -llua -ldl

# GELUA options.
GELUA_OBJECTS     = gelua_main.o
GELUA_HEADERS     = $(HEADERS) $(GELUA_EVAL_HDR)
GELUA_CXXFLAGS    = $(CXXFLAGS) $(LUA_CXXFLAGS) -include $(GELUA_EVAL_HDR)
GELUA_LDFLAGS     = $(LDFLAGS) $(LUA_LDFLAGS)
GELUA_LIBS        = $(LIBS) $(LUA_LIBS)

# ---


default:all

all:    GEGCC GETCC GESLANG GELIBTCC GELUA

GEGCC:  $(GEGCC_OBJECTS) $(GEGCC_EVAL_OBJECTS) $(GEGCC_HEADERS)
	$(CXX) $(GEGCC_LDFLAGS) -o $@ $(GEGCC_OBJECTS) $(GEGCC_LIBS)

GETCC:  $(GETCC_OBJECTS) $(GETCC_EVAL_OBJECTS) $(GETCC_HEADERS)
	$(CXX) $(GETCC_LDFLAGS) -o $@ $(GETCC_OBJECTS) $(GETCC_LIBS)

GESLANG:$(GESLANG_OBJECTS) $(GESLANG_HEADERS)
	$(CXX) $(GESLANG_LDFLAGS) -o $@ $(GESLANG_OBJECTS) $(GESLANG_LIBS)

GELIBTCC: $(GELIBTCC_OBJECTS) $(GELIBTCC_EVAL_OBJECTS) $(GELIBTCC_HEADERS)
	$(CXX) $(GELIBTCC_LDFLAGS) -o $@ $(GELIBTCC_OBJECTS) $(GELIBTCC_LIBS)

GELUA:  $(GELUA_OBJECTS) $(GELUA_HEADERS)
	$(CXX) $(GELUA_LDFLAGS) -o $@ $(GELUA_OBJECTS) $(GELUA_LIBS)

clean:
	rm -f *.o *~ *.sav *.xg *.status gmon.out\
	GEGCC GETCC GESLANG GELIBTCC GELUA

# ---


# GEGCC dependencies.

$(GEGCC_OBJECTS): $(GEGCC_HEADERS)

gegcc_main.o: GEEA.cpp
	$(CXX) -c $(GEGCC_CXXFLAGS) -o $@ $<

gcc_GEspiral.o: GEspiral.c
	$(CC) -c $(CFLAGS) -o $@ $<


# GETCC dependencies.

$(GETCC_OBJECTS): $(GETCC_HEADERS)

getcc_main.o: GEEA.cpp
	$(CXX) -c $(GETCC_CXXFLAGS) -o $@ $<

tcc_GEspiral.o: GEspiral.c
	$(TCC) -c $(TCC_CFLAGS) -o $@ $<


# GESLANG dependencies.

$(GESLANG_OBJECTS): $(GESLANG_HEADERS)

geslang_main.o: GEEA.cpp
	$(CXX) -c $(GESLANG_CXXFLAGS) -o $@ $<


# GELIBTCC dependencies.

$(GELIBTCC_OBJECTS): $(GELIBTCC_HEADERS)

gelibtcc_main.o: GEEA.cpp
	$(CXX) -c $(GELIBTCC_CXXFLAGS) -o $@ $<


# GELUA dependencies.

$(GELUA_OBJECTS): $(GELUA_HEADERS)

gelua_main.o: GEEA.cpp
	$(CXX) -c $(GELUA_CXXFLAGS) -o $@ $<
