THREADS_COUNT_MAX=4

ifeq ($(shell uname -s),Darwin)
    THREADS_COUNT_MAX=$(shell sysctl -n hw.logicalcpu)
endif

ifeq ($(shell uname -s),Linux)
	THREADS_COUNT_MAX=&(shell nproc)
endif

define build_target
	mkdir $(1)
	cd $(1) && cmake ..
	cmake --build ./$(1) --target $(1)View -j $(THREADS_COUNT_MAX)
endef

define run_target
	./$(1)/$(1)View
endef

all: ant gauss winograd

ant:
	$(call build_target,Ant)

run_ant:
	$(call run_target,Ant)

gauss:
	$(call build_target,Gauss)

run_gauss:
	$(call run_target,Gauss)

winograd:
	$(call build_target,Winograd)

run_winograd:
	$(call run_target,Winograd)

clean: clean_ant clean_gauss clean_winograd
	rm .clang-format

clean_ant:
	rm -rf Ant

clean_gauss:
	rm -rf Gauss

clean_winograd:
	rm -rf Winograd

style:
	@cp materials/linters/.clang-format .clang-format
	@clang-format -n src/Controller/*.h src/Controller/*.cc
	@clang-format -n src/Extern/FileManager/include/*.h src/Extern/FileManager/internal/*.tpp
	@clang-format -n src/Extern/Graph/include/*.h src/Extern/Graph/internal/*.tpp
	@clang-format -n src/Extern/Matrix/include/*.h src/Extern/Matrix/internal/*.tpp
	@clang-format -n src/Model/*.h src/Model/*.cc
	@clang-format -n src/Model/AntColony/*.cc src/Model/AntColony/*.h
	@clang-format -n src/Model/AntColony/ant/*.cc src/Model/AntColony/ant/*.h
	@clang-format -n src/Model/Gauss/*.cc src/Model/Gauss/*.h
	@clang-format -n src/Model/Winograd/*.cc src/Model/Winograd/*.h
	@clang-format -n src/View/*.cc src/View/*.h
	@clang-format -n src/View/base/*.cc src/View/base/*.h
	@clang-format -n src/main.cc
