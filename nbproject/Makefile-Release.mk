#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/lib/API_Leitura.o \
	${OBJECTDIR}/lib/API_Utils.o \
	${OBJECTDIR}/lib/FuncoesGerais.o \
	${OBJECTDIR}/lib/GestaoEncomendas.o \
	${OBJECTDIR}/lib/GestaoTabelaPrecos.o \
	${OBJECTDIR}/lib/GestaoUtilizadores.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbean-lei_lp_19.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbean-lei_lp_19.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbean-lei_lp_19 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/lib/API_Leitura.o: lib/API_Leitura.c
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/API_Leitura.o lib/API_Leitura.c

${OBJECTDIR}/lib/API_Utils.o: lib/API_Utils.c
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/API_Utils.o lib/API_Utils.c

${OBJECTDIR}/lib/FuncoesGerais.o: lib/FuncoesGerais.c
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/FuncoesGerais.o lib/FuncoesGerais.c

${OBJECTDIR}/lib/GestaoEncomendas.o: lib/GestaoEncomendas.c
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/GestaoEncomendas.o lib/GestaoEncomendas.c

${OBJECTDIR}/lib/GestaoTabelaPrecos.o: lib/GestaoTabelaPrecos.c
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/GestaoTabelaPrecos.o lib/GestaoTabelaPrecos.c

${OBJECTDIR}/lib/GestaoUtilizadores.o: lib/GestaoUtilizadores.c
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/GestaoUtilizadores.o lib/GestaoUtilizadores.c

${OBJECTDIR}/main.o: main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
