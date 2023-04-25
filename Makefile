# Makefile of all project
CC=gcc

# ANSI color codes
GREEN=\033[0;32m
BROWN=\033[0;33m
PURPLE=\033[0;35m
RED=\033[0;31m
NC=\033[0m # No Color

# Basic paths
APPSRC=./app/main.c
LIBSPATH=/home/f7kso/hello/lab1/libs

# Static Dynamic libraries path
SPATH=$(LIBSPATH)/static/
DPATH=$(LIBSPATH)/dynamic/

# Static flags
INCPNG=-I$(SPATH)libpng/include
INCZLIB=-I$(SPATH)libzlib/include
F=-I$(SPATH)libftype/include/freetype2/freetype
T=-I$(SPATH)libftype/include/freetype2/
Y=-I$(SPATH)libftype/include/freetype2/freetype/config
INCSTATIC=$(F) $(T) $(Y) $(INCPNG) $(INCZLIB)
SFLAG=-D_STATIC_
STBUILD=./build/app-static.bin

# Dynamic flags
DINCPNG=-I$(DPATH)libpng/include
DINCZLIB=-I$(DPATH)libzlib/include
FD=-I$(DPATH)libftype/include/freetype2/freetype
TD=-I$(DPATH)libftype/include/freetype2/
YD=-I$(DPATH)libftype/include/freetype2/freetype/config
INCDYN=$(FD) $(TD) $(YD) $(DINCPNG) $(DINCZLIB)
DBUILD=./build/app-dynamic.bin
SOBJECT=*.so
DFLAG=-D_DYNAMIC_

# Blob flags
BFLAG=-D_BLOB_
	


.PHONY: static dynamic libdynamic libstatic clean all clean-lib blob

all: 
	@echo "$(GREEN)[*] Building project...$(NC)"
	@$(MAKE) static
	@$(MAKE) dynamic
	@$(MAKE) blob
	@echo "$(GREEN)[+] Damn, that's works.$(NC)"
	
libdynamic:
	@echo "\033[1;33m[*] Libs dynamic: Compiling...$(NC)"
	cd ./freetype && pwd && ./configure --prefix=$(DPATH)libftype --enable-shared && $(MAKE)
	$(MAKE) -C ./freetype install 
	cd ./libpng && pwd && ./configure --prefix=$(DPATH)libpng --enable-shared && $(MAKE)
	$(MAKE) -C ./libpng install
	cd ./zlib && pwd && ./configure --shared && $(MAKE)
	@echo "$(GREEN)[+] Libs dynamic: Done.$(NC)"
	
libstatic:
	@echo "$(BROWN)[*] Libs static: Compiling...$(NC)"
	cd ./freetype && pwd && ./configure --prefix=$(SPATH)libftype --enable-static && $(MAKE)
	$(MAKE) -C ./freetype install 
	cd ./libpng && pwd && ./configure --prefix=$(SPATH)libpng --enable-static && $(MAKE)
	$(MAKE) -C ./libpng install
	cd ./libpng && $(MAKE)
	cd ./zlib  && pwd && $(MAKE)
	
	@echo "$(PURPLE)[*] Check directories...$(NC)"
	cd ./zlib && ls 
	cd $(SPATH)libftype && ls
	cd $(SPATH)libpng && ls
	@echo "$(GREEN)[+] Libs static: Done.$(NC)"

static:
	@echo "$(BROWN)[*] Static app: Compiling...$(NC)"
	cp ./zlib/*.a $(SPATH)
	cp ./libpng/*.a $(SPATH)
	cp $(SPATH)/libftype/lib/*.a $(SPATH)
	$(CC) $(SFLAG) $(APPSRC) $(INCSTATIC) $(SPATH)*.a -o $(STBUILD) -lz -lm
	@echo "$(GREEN)[+] Static: Done.$(NC)"
	
dynamic:
	@echo "$(BROWN)[*] Dynamic app: Compiling...$(NC)"
	cp ./zlib/*.so $(DPATH)
	cp $(DPATH)/libftype/lib/*.so $(DPATH)
	cp $(DPATH)/libpng/lib/*.so $(DPATH)
	$(CC) $(DFLAG) $(APPSRC) $(INCDYN) -L$(DPATH)/*.so -o $(DBUILD) -Wl,-rpath=$(DPATH)
	@echo "$(GREEN)[+] Dynamic: Done.$(NC)"

blob:
	@echo "$(BROWN)[*] Blob app: Compiling...$(NC)"
	$(CC) $(BFLAG) $(APPSRC) $(INCSTATIC) $(SPATH)*.a -fPIE -pie -o ./build/app-blob.bin -lm
	
	@echo "$(GREEN)[+] Blob app: Done.$(NC)"
		
clean:
	@echo "$(RED)[*] Cleaning...$(NC)"
	rm -f ./build/*.bin
	rm -f $(SPATH)*.a
	rm -f $(DPATH)*.so
	@echo "$(GREEN)[+] Cleaned successfully.$(NC)"

clean-lib:
	@echo "$(RED)[*] Cleaning...$(NC)"
	$(MAKE) -C ./freetype clean
	$(MAKE) -C ./libpng clean
	$(MAKE) -C ./zlib clean
	@echo "$(GREEN)[+] Cleaned successfully.$(NC)"	

