cmake_minimum_required(VERSION 3.11)
project(lab)

set(CMAKE_CXX_STANDARD 11)
SET(COMPUTER_SOURCE
	mySimpleComputer.cpp mySimpleComputer.h
)
SET(TERMINAL_SOURCE
	myTerminal.cpp myTerminal.h
)

add_library(COMPUTER STATIC ${COMPUTER_SOURCE})
add_library(TERMINAL STATIC ${TERMINAL_SOURCE})

add_executable(main main.cpp SimpleComputerTest.cpp SimpleComputerTest.h TerminalTest.cpp TerminalTest.h)
target_link_libraries(main COMPUTER TERMINAL)
