# See INSTALL.md for usage.

#-------------------------------------------------------------------------------
# Configuration
# Variables defined in make.inc, or use make's defaults:
#   CXX, CXXFLAGS   -- C compiler and flags
#   LD, LDFLAGS, LIBS -- Linker, options, library paths, and libraries
#   AR, RANLIB      -- Archiver, ranlib updates library TOC
#   prefix          -- where to install BLAS++
#   build_dir       -- where to build objects, library, and tester; default "."

build_dir ?= .

ifeq ($(MAKECMDGOALS),config)
    # For `make config`, don't include make.inc with previous config;
    # force re-creating make.inc.
    .PHONY: config
    config: $(build_dir)/make.inc

    $(build_dir)/make.inc: force

else ifneq ($(findstring clean,$(MAKECMDGOALS)),clean)
    # For `make clean` or `make distclean`, don't include make.inc,
    # which could generate it. Otherwise, include make.inc.
    include $(build_dir)/make.inc
endif

python ?= python3

force: ;

$(build_dir)/make.inc:
	$(python) configure.py
	-mv make.inc $(build_dir)/make.inc

# Defaults if not given in make.inc. GNU make doesn't have defaults for these.
RANLIB   ?= ranlib
prefix   ?= /opt/slate

# Default LD=ld won't work; use CXX. Can override in make.inc or environment.
ifeq ($(origin LD),default)
    LD = $(CXX)
endif

# auto-detect OS
# $OSTYPE may not be exported from the shell, so echo it
ostype := $(shell echo $${OSTYPE})
ifneq ($(findstring darwin, $(ostype)),)
    # MacOS is darwin
    macos = 1
endif

#-------------------------------------------------------------------------------
# if shared
ifneq ($(static),1)
    CXXFLAGS += -fPIC
    LDFLAGS  += -fPIC
    lib_ext = so
else
    lib_ext = a
endif

#-------------------------------------------------------------------------------
# MacOS needs shared library's path set
ifeq ($(macos),1)
    install_name = -install_name @rpath/$(notdir $@)
else
    install_name =
endif

#-------------------------------------------------------------------------------
# Files

lib_src  = $(wildcard src/*.cc)
lib_obj  = $(addprefix $(build_dir)/, $(addsuffix .o, $(basename $(lib_src))))
dep     += $(addprefix $(build_dir)/, $(addsuffix .d, $(basename $(lib_src))))

tester_src = $(wildcard test/*.cc)
tester_obj = $(addprefix $(build_dir)/, $(addsuffix .o, $(basename $(tester_src))))
dep       += $(addprefix $(build_dir)/, $(addsuffix .d, $(basename $(tester_src))))

tester     = $(build_dir)/test/tester

#-------------------------------------------------------------------------------
# TestSweeper

testsweeper_dir = $(wildcard ../testsweeper)
ifeq ($(testsweeper_dir),)
    testsweeper_dir = $(wildcard ./testsweeper)
endif
ifeq ($(testsweeper_dir),)
    $(tester_obj):
		$(error Tester requires TestSweeper, which was not found. Run 'make config' \
		        or download manually from https://github.com/icl-utk-edu/testsweeper)
endif

testsweeper_src = $(wildcard $(testsweeper_dir)/testsweeper.cc $(testsweeper_dir)/testsweeper.hh)

testsweeper = $(testsweeper_dir)/libtestsweeper.$(lib_ext)

testsweeper: $(testsweeper)

#-------------------------------------------------------------------------------
# Get Mercurial id, and make version.o depend on it via .id file.

ifneq ($(wildcard .git),)
    id := $(shell git rev-parse --short HEAD)
    $(build_dir)/src/version.o: CXXFLAGS += -DBLASPP_ID='"$(id)"'
endif

last_id := $(shell [ -e .id ] && cat .id || echo 'NA')
ifneq ($(id),$(last_id))
    .id: force
endif

.id:
	echo $(id) > .id

$(build_dir)/src/version.o: .id

#-------------------------------------------------------------------------------
# BLAS++ specific flags and libraries
CXXFLAGS += -I./include

# additional flags and libraries for testers
$(tester_obj): CXXFLAGS += -I$(testsweeper_dir)

TEST_LDFLAGS += -L$(build_dir)/lib -Wl,-rpath,$(abspath $(build_dir)/lib)
TEST_LDFLAGS += -L$(testsweeper_dir) -Wl,-rpath,$(abspath $(testsweeper_dir))
TEST_LIBS    += -lblaspp -ltestsweeper

#-------------------------------------------------------------------------------
# Rules
.DELETE_ON_ERROR:
.SUFFIXES:
.PHONY: all lib src test tester headers include docs clean distclean
.DEFAULT_GOAL = all

all: lib tester

pkg = lib/pkgconfig/blaspp.pc

install: lib $(pkg)
	mkdir -p $(DESTDIR)$(prefix)/include/blas
	mkdir -p $(DESTDIR)$(prefix)/lib$(LIB_SUFFIX)
	mkdir -p $(DESTDIR)$(prefix)/lib$(LIB_SUFFIX)/pkgconfig
	cp include/*.hh $(DESTDIR)$(prefix)/include/
	cp include/blas/*.h  $(DESTDIR)$(prefix)/include/blas/
	cp include/blas/*.hh $(DESTDIR)$(prefix)/include/blas/
	cp -R $(build_dir)/lib/lib* $(DESTDIR)$(prefix)/lib$(LIB_SUFFIX)/
	cp $(pkg) $(DESTDIR)$(prefix)/lib$(LIB_SUFFIX)/pkgconfig/

uninstall:
	$(RM)    $(DESTDIR)$(prefix)/include/blas.hh
	$(RM) -r $(DESTDIR)$(prefix)/include/blas
	$(RM) $(DESTDIR)$(prefix)/lib$(LIB_SUFFIX)/libblaspp.*
	$(RM) $(DESTDIR)$(prefix)/lib$(LIB_SUFFIX)/pkgconfig/blaspp.pc

#-------------------------------------------------------------------------------
# If re-configured, recompile everything. Create build directories.
$(lib_obj) $(tester_obj): $(build_dir)/make.inc | $(build_dir)/src $(build_dir)/test

$(build_dir)/src $(build_dir)/test:
	mkdir $@

#-------------------------------------------------------------------------------
# BLAS++ library
lib_a  = $(build_dir)/lib/libblaspp.a
lib_so = $(build_dir)/lib/libblaspp.so
lib    = $(build_dir)/lib/libblaspp.$(lib_ext)

$(lib_so): $(lib_obj)
	mkdir -p $(build_dir)/lib
	$(LD) $(LDFLAGS) -shared $(install_name) $(lib_obj) $(LIBS) -o $@

$(lib_a): $(lib_obj)
	mkdir -p $(build_dir)/lib
	$(RM) $@
	$(AR) cr $@ $(lib_obj)
	$(RANLIB) $@

# sub-directory rules
lib src: $(lib)

lib/clean src/clean:
	$(RM) $(build_dir)/lib/*.a $(build_dir)/lib/*.so $(build_dir)/src/*.o

#-------------------------------------------------------------------------------
# TestSweeper library
ifneq ($(testsweeper_dir),)
    $(testsweeper): $(testsweeper_src)
		cd $(testsweeper_dir) && $(MAKE) lib CXX=$(CXX)
endif

#-------------------------------------------------------------------------------
# tester
$(tester): $(tester_obj) $(lib) $(testsweeper)
	$(LD) $(TEST_LDFLAGS) $(LDFLAGS) $(tester_obj) \
		$(TEST_LIBS) $(LIBS) -o $@

# sub-directory rules
# Note 'test' is sub-directory rule; 'tester' is CMake-compatible rule.
test: $(tester)
tester: $(tester)

test/clean:
	$(RM) $(tester) $(build_dir)/test/*.o

test/check: check

check: tester
	cd test; $(python) run_tests.py --quick

#-------------------------------------------------------------------------------
# headers
# precompile headers to verify self-sufficiency
headers     = $(wildcard include/blas.hh include/blas/*.h include/blas/*.hh test/*.hh)
headers_gch = $(addsuffix .gch, $(basename $(headers)))

headers: $(headers_gch)

headers/clean:
	$(RM) $(headers_gch)

# sub-directory rules
include: headers

include/clean: headers/clean

#-------------------------------------------------------------------------------
# pkgconfig
# Keep -std=c++11 in CXXFLAGS. Keep -fopenmp in LDFLAGS.
CXXFLAGS_clean = $(filter-out -O% -W% -pedantic -D% -I./include -MMD -fPIC -fopenmp, $(CXXFLAGS))
CPPFLAGS_clean = $(filter-out -O% -W% -pedantic -D% -I./include -MMD -fPIC -fopenmp, $(CPPFLAGS))
LDFLAGS_clean  = $(filter-out -fPIC, $(LDFLAGS))

.PHONY: $(pkg)
$(pkg):
	perl -pe "s'#VERSION'2021.04.01'; \
	          s'#PREFIX'${prefix}'; \
	          s'#CXX\b'${CXX}'; \
	          s'#CXXFLAGS'${CXXFLAGS_clean}'; \
	          s'#CPPFLAGS'${CPPFLAGS_clean}'; \
	          s'#LDFLAGS'${LDFLAGS_clean}'; \
	          s'#LIBS'${LIBS}';" \
	          $@.in > $@

#-------------------------------------------------------------------------------
# documentation
docs: docs/html/index.html

doc_files = \
	docs/doxygen/DoxygenLayout.xml \
	docs/doxygen/doxyfile.conf \
	docs/doxygen/groups.dox \
	README.md \
	INSTALL.md \

docs/html/index.html: $(headers) $(lib_src) $(tester_src) $(doc_files)
	doxygen docs/doxygen/doxyfile.conf
	@echo ========================================
	cat docs/doxygen/errors.txt
	@echo ========================================
	@echo "Documentation available in docs/html/index.html"
	@echo ========================================

# sub-directory redirects
src/docs: docs
test/docs: docs

#-------------------------------------------------------------------------------
# general rules
clean: lib/clean test/clean headers/clean
	$(RM) $(dep)

distclean: clean
	$(RM) $(build_dir)/make.inc $(build_dir)/include/blas/defines.h
	$(RM) $(dep)
	$(RM) config/*.[od]
	find config -perm +0100 -type f -delete

h$(build_dir)/%.o: %.cc
	$(CXX) $(CXXFLAGS) -MF $(build_dir)/$*.d -c $< -o $@

# preprocess source
$(build_dir)/%.i: %.cc
	$(CXX) $(CXXFLAGS) -I$(testsweeper_dir) -E $< -o $@

# preprocess source
$(build_dir)/%.i: %.h
	$(CXX) $(CXXFLAGS) -I$(testsweeper_dir) -E $< -o $@

# preprocess source
$(build_dir)/%.i: %.hh
	$(CXX) $(CXXFLAGS) -I$(testsweeper_dir) -E $< -o $@

# precompile header to check for errors
$(build_dir)/%.gch: %.h
	$(CXX) $(CXXFLAGS) -I$(testsweeper_dir) -c $< -o $@

$(build_dir)/%.gch: %.hh
	$(CXX) $(CXXFLAGS) -I$(testsweeper_dir) -c $< -o $@

-include $(dep)

#-------------------------------------------------------------------------------
# debugging
echo:
	@echo "static        = '$(static)'"
	@echo "id            = '$(id)'"
	@echo "last_id       = '$(last_id)'"
	@echo
	@echo "lib_a         = $(lib_a)"
	@echo "lib_so        = $(lib_so)"
	@echo "lib           = $(lib)"
	@echo
	@echo "lib_src       = $(lib_src)"
	@echo
	@echo "lib_obj       = $(lib_obj)"
	@echo
	@echo "tester_src    = $(tester_src)"
	@echo
	@echo "tester_obj    = $(tester_obj)"
	@echo
	@echo "tester        = $(tester)"
	@echo
	@echo "dep           = $(dep)"
	@echo
	@echo "testsweeper_dir   = $(testsweeper_dir)"
	@echo "testsweeper_src   = $(testsweeper_src)"
	@echo "testsweeper       = $(testsweeper)"
	@echo
	@echo "CXX           = $(CXX)"
	@echo "CXXFLAGS      = $(CXXFLAGS)"
	@echo
	@echo "LD            = $(LD)"
	@echo "LDFLAGS       = $(LDFLAGS)"
	@echo "LIBS          = $(LIBS)"
	@echo
	@echo "TEST_LDFLAGS  = $(TEST_LDFLAGS)"
	@echo "TEST_LIBS     = $(TEST_LIBS)"
