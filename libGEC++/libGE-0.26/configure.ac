# Process this file with autoconf to produce a configure script.

AC_INIT(libGE, 0.26, miguel.nicolau@gmail.com,libGE)
AC_PREREQ(2.59)
AC_CONFIG_HEADERS([src/libGEdefs.h])
AC_CONFIG_SRCDIR([src/Genotype.cpp])
AC_CONFIG_AUX_DIR(config)
AM_INIT_AUTOMAKE
AC_ARG_ENABLE([GE_ILLIGALSGA],
	AC_HELP_STRING([--enable-[GE_ILLIGALSGA]=yes/no],
		[include GE_ILLIGALSGA wrapper (default is yes)]),
	[case "${enableval}" in
		yes) GE_ILLIGALSGA=true ;;
		no)  GE_ILLIGALSGA=false ;;
		*)   AC_MSG_ERROR(bad value ${enableval} for --enable-GE_ILLIGALSGA) ;;
	esac],
	[GE_ILLIGALSGA=true]
)
AC_ARG_ENABLE([GE_MITGALIB],
	AC_HELP_STRING([--enable-[GE_MITGALIB]=yes/no],
		[include GE_MITGALIB wrapper (default is yes)]),
	[case "${enableval}" in
		yes) GE_MITGALIB=true ;;
		no)  GE_MITGALIB=false ;;
		*)   AC_MSG_ERROR(bad value ${enableval} for --enable-GE_MITGALIB) ;;
	esac],
	[GE_MITGALIB=true]
)
AC_ARG_WITH(MITGALIBINCLUDES,
	AC_HELP_STRING([--with-[MITGALIBINCLUDES]=path],
		       [set full path to MITGALIB includes base directory]),
	[GALIB_INCLUDE="${withval}"],
	[GALIB_INCLUDE="DEFAULT"]
)
AC_ARG_WITH(MITGALIBLIBS,
	AC_HELP_STRING([--with-[MITGALIBLIBS]=path],
		       [set full path to MITGALIB library (default is to use linker flag -lga)]),
	[GALIBS="${withval}"],
	[GALIBS="-lga"]
)

AC_PROG_CC
AC_PROG_CXX
if test x"$GE_ILLIGALSGA" = xtrue ; then
	AC_C_CONST
	AC_FUNC_MALLOC
	AC_DEFINE(GE_ILLIGALSGA,[],[Install Illigal SGA wrapper])
fi
if test x"$GE_MITGALIB" = xtrue ; then
	if test x"$GE_ILLIGALSGA" != xtrue ; then
		AC_FUNC_MALLOC
	fi
	AC_LANG(C++)
	
	if test x"$GALIB_INCLUDE" = xDEFAULT ; then
		AC_CHECK_HEADER(ga/ga.h,[AC_DEFINE(GALIB_INCLUDEPATH,<ga/ga.h>,Path for GALib headers)],[AC_MSG_WARN([could not find the GALib headers on <ga/ga.h>.]) && GE_MITGALIB=false])
	else
		AC_CHECK_FILE([$GALIB_INCLUDE/ga.h],
			      [GALIB=$GALIB_INCLUDE],
			      [AC_CHECK_FILE([$GALIB_INCLUDE/ga/ga.h],
					    [GALIB=$GALIB_INCLUDE/ga],
					    [AC_MSG_WARN([Could not find the GALib \
headers on "$GALIB_INCLUDE/ga.h" or "$GALIB_INCLUDE/ga/ga.h".]) && GE_MITGALIB=false])])
		AC_SUBST(CPPFLAGS,["$CPPFLAGS -I$GALIB/.."])
		AC_DEFINE_UNQUOTED(GALIB_INCLUDEPATH,["$GALIB/ga.h"],[Path for GALib headers])
		AC_MSG_CHECKING([whether GALib includes are compilable])
		AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <ga/ga.h>],[GAGenome g; GASteadyStateGA ga(g);])],AC_MSG_RESULT([yes]),
AC_MSG_RESULT([no]) && AC_MSG_WARN([could not use the GALib headers defined.]) && GE_MITGALIB=false)
	fi

	AC_SUBST(LIBS,["$LIBS $GALIBS"])
	AC_MSG_CHECKING([whether GALib library is installed])
	AC_LINK_IFELSE([AC_LANG_PROGRAM([#include <ga/ga.h>],[GAGenome g; GASteadyStateGA ga(g);])],AC_MSG_RESULT([yes]),
AC_MSG_RESULT([no]) && AC_MSG_WARN([Could not use the GALib library "$GALIBS".]) && GE_MITGALIB=false)
fi

AM_CONDITIONAL(ILLIGALSGA_WRAPPER,test x$GE_ILLIGALSGA = xtrue)
AM_CONDITIONAL(MITGALIB_WRAPPER,test x$GE_MITGALIB = xtrue)

AC_HEADER_STDBOOL
AC_PROG_RANLIB
AC_CONFIG_FILES([Makefile])
AH_TOP([// ge.h -*- C++ -*-
#ifndef _LIBGEDEFS_H_
#define _LIBGEDEFS_H_])
AH_TOP([#define libGEVersion] "AC_PACKAGE_VERSION")
AH_BOTTOM([
#endif])
AC_OUTPUT

AC_MSG_NOTICE([************************************************************])
AC_MSG_NOTICE([* Now run `make` and `make install`. The following options *])
AC_MSG_NOTICE([* were set:                                                *])
if test x"$GE_ILLIGALSGA" = xtrue ; then
AC_MSG_NOTICE([* - IlliGAL sga support was installed;                     *])
else
AC_MSG_NOTICE([* - IlliGAL sga support was NOT installed;                 *])
fi
if test x"$GE_MITGALIB" = xtrue ; then
AC_MSG_NOTICE([* - GALib support was installed;                           *])
else
AC_MSG_NOTICE([* - GALib support was NOT installed;                       *])
fi
AC_MSG_NOTICE([* - EO support is implicit.                                *])
AC_MSG_NOTICE([************************************************************])

