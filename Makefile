#===============================================================================
#
#     Filename: Makefile
#  Description: Makefile do TP de OC1
#
#        Usage: make              (generate executable                      )
#               make clean        (remove objects, executable, prerequisits )
#               make tarball      (generate compressed archive              )
#
#       Author: Leonardo vilela Teixeira
#        Email: vilela@dcc.ufmg.br
#
#        Notes: This is a GNU make (gmake) makefile.
#
#========================================== makefile template version 1.8 ======

# DEBUG can be set to YES to include debugging info, or NO otherwise
DEBUG          := YES

# PROFILE can be set to YES to include profiling info, or NO otherwise
PROFILE        := NO

# LANGUAGE: C or CPP
LANGUAGE	   := C

# ------------  name of the executable and folders  ----------------------------
EXECUTABLE      := bin/uRISC
PARAMS			:= 
OBJDIR			:= bin/obj
SRCDIR			:= src

# ------------  tarball info  --------------------------------------------------
TARNAME      	:= tp_grupo4
TARCONTENT		:= src/ bin/ Makefile

# ------------ list of modules -------------------------------------------------
MODULES			:= main registradores memoria alu controle constantes

# ------------  compiler  ------------------------------------------------------
CC				:= gcc

# ------------  Libraries ------------------------------------------------------
LIBS			:= 

# ------------  compiler flags  ------------------------------------------------
DEBUG_CFLAGS    := -Wall -g
RELEASE_CFLAGS  := -Wall -O3

# ------------  linker flags  --------------------------------------------------
DEBUG_LDFLAGS    := -g
RELEASE_LDFLAGS  :=

ifeq (YES, ${DEBUG})
  CFLAGS       := ${DEBUG_CFLAGS}
  LDFLAGS      := ${DEBUG_LDFLAGS}
else
  CFLAGS       := ${RELEASE_CFLAGS}
  LDFLAGS      := ${RELEASE_LDFLAGS}
endif

ifeq (YES, ${PROFILE})
  CFLAGS       := ${CFLAGS}   -pg -O3
  LDFLAGS      := ${LDFLAGS}  -pg
endif

CFLAGS_FINAL := ${CFLAGS}
C_FINAL		 := ${CC}


# ------------  generate the names of the object files  ------------------------
OBJECTS         = $(addprefix ${OBJDIR}/, $(addsuffix .o,$(MODULES)))

#===============================================================================
# TARGETS
#===============================================================================

.PHONY: all run check mrproper clean tarball zip

# ==============================================================================

all: ${EXECUTABLE}

# ------------  make the executable (the default goal)  ------------------------
$(EXECUTABLE): ${OBJECTS}

	@echo "Criando ${EXECUTABLE}"
	@$(C_FINAL) $(LFLAGS) $(LIBS) -o $(EXECUTABLE) $(OBJECTS)

# ------------ make and execute ------------------------------------------------
run: all
	@echo "Executando:"
	@echo "========================="
	@./${EXECUTABLE} ${PARAMS}
	@echo "========================="

# ------------ make and execute ------------------------------------------------
check: all
	@echo "Rodando VALGRIND:"
	@echo "========================="
	@valgrind ./${EXECUTABLE} ${PARAMS}
	@echo "========================="

# ==============================================================================
# ------------  make the objects  ----------------------------------------------

${OBJDIR}/main.o:	${SRCDIR}/main.c
			@echo "Compilando Modulo Principal"
			@${C_FINAL} $(CFLAGS_FINAL) -c $< -o $@

${OBJDIR}/registradores.o:	${SRCDIR}/registradores.c ${SRCDIR}/registradores.h
		@echo "Compilando Módulo Registradores"
		@${C_FINAL} $(CFLAGS_FINAL) -c $< -o $@

${OBJDIR}/memoria.o:	${SRCDIR}/memoria.c ${SRCDIR}/memoria.h
		@echo "Compilando Módulo Memória"
		@${C_FINAL} $(CFLAGS_FINAL) -c $< -o $@

${OBJDIR}/alu.o:	${SRCDIR}/alu.c ${SRCDIR}/alu.h
		@echo "Compilando Módulo ALU"
		@${C_FINAL} $(CFLAGS_FINAL) -c $< -o $@

${OBJDIR}/controle.o:	${SRCDIR}/controle.c ${SRCDIR}/controle.h
		@echo "Compilando Módulo Controle"
		@${C_FINAL} $(CFLAGS_FINAL) -c $< -o $@

${OBJDIR}/constantes.o:	${SRCDIR}/constantes.c ${SRCDIR}/constantes.h
		@echo "Compilando Módulo Constantes"
		@${C_FINAL} $(CFLAGS_FINAL) -c $< -o $@

#${OBJDIR}/modulo.o:	${SRCDIR}/modulo.c ${SRCDIR}/modulo.h
#		@echo "Compilando Modulo <NOME>"
#		@${C_FINAL} $(CFLAGS_FINAL) -c $< -o $@

# ==============================================================================
# ------------  remove generated files  ----------------------------------------
# ------------  remove hidden backup files  ------------------------------------
clean:
			@rm  --force $(OBJECTS) *~

# ------------  remove all (clean + exec.) -------------------------------------
mrproper: clean
			@rm  --force  $(EXECUTABLE)

# ------------ tarball generation ----------------------------------------------
tarball: all
			@echo "Limpando..."
			@rm --force $(OBJECTS) *~
			@echo "Compactando..."
			@rm --force ${TARNAME}.tar.gz
			@tar -czf ${TARNAME}.tar.gz ${TARCONTENT}
			@echo "Pronto. Arquivo Compactado: ${TARNAME}.tar.gz"

# ==============================================================================

