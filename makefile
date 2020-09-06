THIS_FILE := $(lastword $(MAKEFILE_LIST))

CC := g++ 
SRCDIR := src
BUILDDIR := build
INCLUDEDIR := include
EXEDIR := bin
 
SRCEXT := cpp
HEADEREXT := h
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
HEADERS := $(shell find $(INCLUDEDIR) -type f -name *.$(HEADEREXT))
CFLAGS := -g 
INC := -I include

TESTSRC := test/test.cpp
TESTOBJ := test/test.o

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(HEADERS)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

test: test/test.cpp $(HEADERS) $(OBJECTS)
	@mkdir -p $(EXEDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $(TESTOBJ) $(TESTSRC)";  $(CC) $(CFLAGS) $(INC) -c -o $(TESTOBJ) $(TESTSRC)
	@echo " $(CC) $(CFLAGS) $(INC) -o $(EXEDIR)/test $(TESTOBJ) $(OBJECTS)"; $(CC) $(CFLAGS) $(INC) -o $(EXEDIR)/test $(TESTOBJ) $(OBJECTS)

show: 
	@echo "headers: $(HEADERS)\n"
	@echo "src: $(SOURCES)\n"
	@echo "builds: $(OBJECTS)\n"

build: $(SOURCES) $(HEADERS)
	@for obj in $(OBJECTS); do \
		$(MAKE) -f $(THIS_FILE) $$obj; \
	done

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR)"; $(RM) -r $(BUILDDIR)
	@echo " $(RM) -r $(EXEDIR)"; $(RM) -r $(EXEDIR)

.PHONY: clean