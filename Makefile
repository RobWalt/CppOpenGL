ifeq ($(OS), Windows_NT)
	RM=rmdir /Q /S
else
	RM=sudo rm -r
endif

help:
	@echo "Some available commands:"
	@echo " * prepare - Remove old build dir, create new build dir, install conan deps"

prepare:
	@$(RM) build
	@mkdir build
	@cd build && conan install .. --build missing -s compiler=gcc -s compiler.version=10 -s compiler.libcxx=libstdc++11 && cd ..
