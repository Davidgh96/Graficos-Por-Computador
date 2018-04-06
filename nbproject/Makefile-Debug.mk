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
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/prueba2.o \
	${OBJECTDIR}/sesion1.o \
	${OBJECTDIR}/sesion2.o \
	${OBJECTDIR}/sesion3.o \
	${OBJECTDIR}/sesion4.o \
	${OBJECTDIR}/sesion5.o \
	${OBJECTDIR}/sesion6.o


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
LDLIBSOPTIONS=-L/D/Mis\ documentos/Ingenieria\ Computadores/Cuarto\ Computadores/Segundo\ Cuatrimestre/Graficos\ por\ Computador/libs/ogl/lib -L/D/Mis\ documentos/Ingenieria\ Computadores/Cuarto\ Computadores/Segundo\ Cuatrimestre/Graficos\ por\ Computador/libs/soil/lib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sesion.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sesion.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sesion ${OBJECTFILES} ${LDLIBSOPTIONS} -lSOIL -lopengl32 -lglu32 -lglew32 -lfreeglut

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/D/Mis\ documentos/Ingenieria\ Computadores/Cuarto\ Computadores/Segundo\ Cuatrimestre/Graficos\ por\ Computador/libs/ogl/include -I/D/Mis\ documentos/Ingenieria\ Computadores/Cuarto\ Computadores/Segundo\ Cuatrimestre/Graficos\ por\ Computador/libs/soil/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/prueba2.o: prueba2.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/D/Mis\ documentos/Ingenieria\ Computadores/Cuarto\ Computadores/Segundo\ Cuatrimestre/Graficos\ por\ Computador/libs/ogl/include -I/D/Mis\ documentos/Ingenieria\ Computadores/Cuarto\ Computadores/Segundo\ Cuatrimestre/Graficos\ por\ Computador/libs/soil/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/prueba2.o prueba2.cpp

${OBJECTDIR}/sesion1.o: sesion1.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/D/Mis\ documentos/Ingenieria\ Computadores/Cuarto\ Computadores/Segundo\ Cuatrimestre/Graficos\ por\ Computador/libs/ogl/include -I/D/Mis\ documentos/Ingenieria\ Computadores/Cuarto\ Computadores/Segundo\ Cuatrimestre/Graficos\ por\ Computador/libs/soil/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sesion1.o sesion1.cpp

${OBJECTDIR}/sesion2.o: sesion2.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/D/Mis\ documentos/Ingenieria\ Computadores/Cuarto\ Computadores/Segundo\ Cuatrimestre/Graficos\ por\ Computador/libs/ogl/include -I/D/Mis\ documentos/Ingenieria\ Computadores/Cuarto\ Computadores/Segundo\ Cuatrimestre/Graficos\ por\ Computador/libs/soil/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sesion2.o sesion2.cpp

${OBJECTDIR}/sesion3.o: sesion3.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/D/Mis\ documentos/Ingenieria\ Computadores/Cuarto\ Computadores/Segundo\ Cuatrimestre/Graficos\ por\ Computador/libs/ogl/include -I/D/Mis\ documentos/Ingenieria\ Computadores/Cuarto\ Computadores/Segundo\ Cuatrimestre/Graficos\ por\ Computador/libs/soil/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sesion3.o sesion3.cpp

${OBJECTDIR}/sesion4.o: sesion4.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/D/Mis\ documentos/Ingenieria\ Computadores/Cuarto\ Computadores/Segundo\ Cuatrimestre/Graficos\ por\ Computador/libs/ogl/include -I/D/Mis\ documentos/Ingenieria\ Computadores/Cuarto\ Computadores/Segundo\ Cuatrimestre/Graficos\ por\ Computador/libs/soil/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sesion4.o sesion4.cpp

${OBJECTDIR}/sesion5.o: sesion5.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/D/Mis\ documentos/Ingenieria\ Computadores/Cuarto\ Computadores/Segundo\ Cuatrimestre/Graficos\ por\ Computador/libs/ogl/include -I/D/Mis\ documentos/Ingenieria\ Computadores/Cuarto\ Computadores/Segundo\ Cuatrimestre/Graficos\ por\ Computador/libs/soil/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sesion5.o sesion5.cpp

${OBJECTDIR}/sesion6.o: sesion6.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/D/Mis\ documentos/Ingenieria\ Computadores/Cuarto\ Computadores/Segundo\ Cuatrimestre/Graficos\ por\ Computador/libs/ogl/include -I/D/Mis\ documentos/Ingenieria\ Computadores/Cuarto\ Computadores/Segundo\ Cuatrimestre/Graficos\ por\ Computador/libs/soil/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sesion6.o sesion6.cpp

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
