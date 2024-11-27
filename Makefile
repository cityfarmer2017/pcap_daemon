APPNAME := pcapd

TOPDIR := $(shell pwd)
SRCDIR := $(TOPDIR)
INCDIR := $(TOPDIR)/inc

BINDIR := $(TOPDIR)/bin
BUILDDIR := $(TOPDIR)/build
OBJDIR := $(BUILDDIR)/obj
DEPDIR := $(BUILDDIR)/dep

TEMPDIRS := $(BINDIR) $(BUILDDIR) $(OBJDIR) $(DEPDIR)

SRCFILES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SRCFILES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPENDS := $(OBJECTS:$(OBJDIR)/%=$(DEPDIR)/%.d)

CC := g++
CCFLAGS := -g -Wall -ldbus-1 -libverbs -lpcap

.PHONY : all
all : $(TEMPDIRS) $(BINDIR)/$(APPNAME)

$(TEMPDIRS) :
	mkdir -p $@

$(BINDIR)/$(APPNAME) : $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(CCFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) -I$(INCDIR) -o $@ -c $< -MMD -MF $(patsubst $(OBJDIR)/%, $(DEPDIR)/%.d, $@)

-include $(DEPENDS)

.PHONY : clean
clean :
	rm $(OBJECTS) $(DEPENDS) $(BINDIR)/$(APPNAME)

.PHONY : dist-clean
dist-clean :
	rm -r $(BINDIR) $(BUILDDIR)