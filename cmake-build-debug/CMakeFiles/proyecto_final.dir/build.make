# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/proyecto_final.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/proyecto_final.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/proyecto_final.dir/flags.make

CMakeFiles/proyecto_final.dir/main.cpp.o: CMakeFiles/proyecto_final.dir/flags.make
CMakeFiles/proyecto_final.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/proyecto_final.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proyecto_final.dir/main.cpp.o -c /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/main.cpp

CMakeFiles/proyecto_final.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proyecto_final.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/main.cpp > CMakeFiles/proyecto_final.dir/main.cpp.i

CMakeFiles/proyecto_final.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proyecto_final.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/main.cpp -o CMakeFiles/proyecto_final.dir/main.cpp.s

CMakeFiles/proyecto_final.dir/igvInterfaz.cpp.o: CMakeFiles/proyecto_final.dir/flags.make
CMakeFiles/proyecto_final.dir/igvInterfaz.cpp.o: ../igvInterfaz.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/proyecto_final.dir/igvInterfaz.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proyecto_final.dir/igvInterfaz.cpp.o -c /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/igvInterfaz.cpp

CMakeFiles/proyecto_final.dir/igvInterfaz.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proyecto_final.dir/igvInterfaz.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/igvInterfaz.cpp > CMakeFiles/proyecto_final.dir/igvInterfaz.cpp.i

CMakeFiles/proyecto_final.dir/igvInterfaz.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proyecto_final.dir/igvInterfaz.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/igvInterfaz.cpp -o CMakeFiles/proyecto_final.dir/igvInterfaz.cpp.s

CMakeFiles/proyecto_final.dir/igvEscena3D.cpp.o: CMakeFiles/proyecto_final.dir/flags.make
CMakeFiles/proyecto_final.dir/igvEscena3D.cpp.o: ../igvEscena3D.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/proyecto_final.dir/igvEscena3D.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proyecto_final.dir/igvEscena3D.cpp.o -c /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/igvEscena3D.cpp

CMakeFiles/proyecto_final.dir/igvEscena3D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proyecto_final.dir/igvEscena3D.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/igvEscena3D.cpp > CMakeFiles/proyecto_final.dir/igvEscena3D.cpp.i

CMakeFiles/proyecto_final.dir/igvEscena3D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proyecto_final.dir/igvEscena3D.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/igvEscena3D.cpp -o CMakeFiles/proyecto_final.dir/igvEscena3D.cpp.s

CMakeFiles/proyecto_final.dir/igvCamara.cpp.o: CMakeFiles/proyecto_final.dir/flags.make
CMakeFiles/proyecto_final.dir/igvCamara.cpp.o: ../igvCamara.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/proyecto_final.dir/igvCamara.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proyecto_final.dir/igvCamara.cpp.o -c /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/igvCamara.cpp

CMakeFiles/proyecto_final.dir/igvCamara.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proyecto_final.dir/igvCamara.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/igvCamara.cpp > CMakeFiles/proyecto_final.dir/igvCamara.cpp.i

CMakeFiles/proyecto_final.dir/igvCamara.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proyecto_final.dir/igvCamara.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/igvCamara.cpp -o CMakeFiles/proyecto_final.dir/igvCamara.cpp.s

CMakeFiles/proyecto_final.dir/igvPunto3D.cpp.o: CMakeFiles/proyecto_final.dir/flags.make
CMakeFiles/proyecto_final.dir/igvPunto3D.cpp.o: ../igvPunto3D.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/proyecto_final.dir/igvPunto3D.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proyecto_final.dir/igvPunto3D.cpp.o -c /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/igvPunto3D.cpp

CMakeFiles/proyecto_final.dir/igvPunto3D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proyecto_final.dir/igvPunto3D.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/igvPunto3D.cpp > CMakeFiles/proyecto_final.dir/igvPunto3D.cpp.i

CMakeFiles/proyecto_final.dir/igvPunto3D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proyecto_final.dir/igvPunto3D.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/igvPunto3D.cpp -o CMakeFiles/proyecto_final.dir/igvPunto3D.cpp.s

CMakeFiles/proyecto_final.dir/utils.cpp.o: CMakeFiles/proyecto_final.dir/flags.make
CMakeFiles/proyecto_final.dir/utils.cpp.o: ../utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/proyecto_final.dir/utils.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proyecto_final.dir/utils.cpp.o -c /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/utils.cpp

CMakeFiles/proyecto_final.dir/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proyecto_final.dir/utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/utils.cpp > CMakeFiles/proyecto_final.dir/utils.cpp.i

CMakeFiles/proyecto_final.dir/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proyecto_final.dir/utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/utils.cpp -o CMakeFiles/proyecto_final.dir/utils.cpp.s

# Object files for target proyecto_final
proyecto_final_OBJECTS = \
"CMakeFiles/proyecto_final.dir/main.cpp.o" \
"CMakeFiles/proyecto_final.dir/igvInterfaz.cpp.o" \
"CMakeFiles/proyecto_final.dir/igvEscena3D.cpp.o" \
"CMakeFiles/proyecto_final.dir/igvCamara.cpp.o" \
"CMakeFiles/proyecto_final.dir/igvPunto3D.cpp.o" \
"CMakeFiles/proyecto_final.dir/utils.cpp.o"

# External object files for target proyecto_final
proyecto_final_EXTERNAL_OBJECTS =

proyecto_final: CMakeFiles/proyecto_final.dir/main.cpp.o
proyecto_final: CMakeFiles/proyecto_final.dir/igvInterfaz.cpp.o
proyecto_final: CMakeFiles/proyecto_final.dir/igvEscena3D.cpp.o
proyecto_final: CMakeFiles/proyecto_final.dir/igvCamara.cpp.o
proyecto_final: CMakeFiles/proyecto_final.dir/igvPunto3D.cpp.o
proyecto_final: CMakeFiles/proyecto_final.dir/utils.cpp.o
proyecto_final: CMakeFiles/proyecto_final.dir/build.make
proyecto_final: CMakeFiles/proyecto_final.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable proyecto_final"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/proyecto_final.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/proyecto_final.dir/build: proyecto_final

.PHONY : CMakeFiles/proyecto_final.dir/build

CMakeFiles/proyecto_final.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/proyecto_final.dir/cmake_clean.cmake
.PHONY : CMakeFiles/proyecto_final.dir/clean

CMakeFiles/proyecto_final.dir/depend:
	cd /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/cmake-build-debug /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/cmake-build-debug /mnt/c/Users/cojou/CLionProjects/proyecto_final_IGV/cmake-build-debug/CMakeFiles/proyecto_final.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/proyecto_final.dir/depend

