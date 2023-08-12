cmake_minimum_required(VERSION 3.11)
project(lab)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_SOURCE_DIR src)
set(EXECUTABLE_OUTPUT_PATH ../bin)
set(LIBRARY_OUTPUT_PATH lib)


SET(SIMPLE_COMPUTER_SOURCE
	lib/SimpleComputer/mySimpleComputer.cpp lib/SimpleComputer/mySimpleComputer.h
)
SET(TERMINAL_SOURCE
	lib/Terminal/myTerminal.cpp lib/Terminal/myTerminal.h
)
SET(BIGCHARS_SOURCE
	lib/BigChars/myBigChars.cpp lib/BigChars/myBigChars.h
)
SET(READKEYS_SOURCE
	lib/ReadKeys/myReadKeys.cpp lib/ReadKeys/myReadKeys.h
)
SET(COMPUTER_SOURCE
	lib/Computer/DisplayInterface.cpp lib/Computer/DisplayInterface.h
	lib/CellChange/SetVariables.cpp lib/CellChange/SetVariables.h
	lib/CU/CU.cpp lib/CU/CU.h
	lib/SignalHandler/signals.cpp lib/SignalHandler/signals.h
)
SET(SIMPLE_ASSEMBLER_SOURCE
  lib/SA/SimpleAssembler.cpp lib/SA/SimpleAssembler.h
)
SET(SIMPLE_BASIC_SOURCE
  lib/SB/SimpleBasic.cpp lib/SB/SimpleBasic.h
)


add_library(SIMPLECOMPUTER STATIC ${SIMPLE_COMPUTER_SOURCE})
add_library(TERMINAL STATIC ${TERMINAL_SOURCE})
add_library(BIGCHARS STATIC ${BIGCHARS_SOURCE})
add_library(READKEYS STATIC ${READKEYS_SOURCE})
add_library(COMPUTER STATIC ${COMPUTER_SOURCE})
add_library(SIMPLEASSEMBLER STATIC ${SIMPLE_ASSEMBLER_SOURCE})
add_library(SIMPLEBASIC STATIC ${SIMPLE_BASIC_SOURCE})

#add_executable(main src/EVM/main.cpp src/lab2/SimpleComputerTest.cpp src/lab2/SimpleComputerTest.h src/lab3/TerminalTest.cpp src/lab3/TerminalTest.h)
add_executable(main src/EVM/main.cpp)
target_link_libraries(main COMPUTER READKEYS BIGCHARS TERMINAL SIMPLECOMPUTER)

add_executable(sat src/SAT/sat.cpp)
target_link_libraries(sat SIMPLEASSEMBLER SIMPLECOMPUTER)

add_executable(sbt src/SBT/sbt.cpp)
target_link_libraries(sbt SIMPLEBASIC)
