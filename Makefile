CC := g++ # this is the main compiler
# CC := clang --analyze # and comment out the linker last line
SRCDIR := src
BUILDDIR := build
TARGETDIR := bin
TARGET := bin/CardEval

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -std=c++14 -Wall
LIBDIR := -L/usr/local/lib64/
LIB := -ltinyxml2
INC := -Iinclude/

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@mkdir -p $(TARGETDIR)
	@echo " $(CC) $^ -o $(TARGET) $(LIBDIR) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIBDIR) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo " Building..."
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $< $(CFLAGS) $(INC) -c -o $@"; $(CC) $< $(CFLAGS) $(INC) -c -o $@

clean:
	@echo " Cleaning..."
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
tester:
	@echo " $(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester"; $(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
ticket:
	@echo " $(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket"; $(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean
