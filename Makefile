CC=gcc
CFLAGS=-Wall -O2 -g
LDFLAGS=-lglfw -lGLU -lGL -lm

BINDIR=bin
SRCDIR=src
OBJDIR=obj

GLOB_OBJ=$(OBJDIR)/3D_tools.o
OBJ_FILES=$(GLOB_OBJ) $(OBJDIR)/main.o
EXEC_CORRIDOR=corridor

all : corridor

corridor : $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(BINDIR)/$(EXEC_CORRIDOR) $(LDFLAGS)

clean :
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)/*
    
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p `dirname $@`
	$(CC) -o $@ -c $< $(CFLAGS)