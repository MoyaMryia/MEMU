cmake_minimum_required(VERSION 3.5)
project( MEMU )
find_library(READLINE_LIBRARY NAMES readline)
find_path(READLINE_INCLUDE_DIR NAMES readline/readline.h)
find_library(NCURSES_LIBRARY NAMES ncurses curses tinfo termcap)
if(READLINE_LIBRARY AND READLINE_INCLUDE_DIR AND NCURSES_LIBRARY)
    set(READLINE_FOUND TRUE)
    message(STATUS "Found Readline Library: ${READLINE_LIBRARY}")
    message(STATUS "Readline Include Path: ${READLINE_INCLUDE_DIR}")
    message(STATUS "Found Ncurses/Termcap: ${NCURSES_LIBRARY}")
else()
    set(READLINE_FOUND FALSE)
    message(WARNING "Readline library, headers, or required dependency (Ncurses/Termcap) NOT found.")
endif()
include_directories(include/ ${READLINE_INCLUDE_DIR})
file(GLOB SOURCES_TOOLS "tools/*.cpp")
file(GLOB SOURCES_SRC "src/*.cpp")

add_executable( MEMU main.cpp ${SOURCES_SRC} ${SOURCES_TOOLS} )
target_link_libraries(MEMU 
    PRIVATE 
        ${READLINE_LIBRARY}
        ${NCURSES_LIBRARY} # Readline 通常需要依赖 Ncurses/Termcap
)
target_link_libraries( MEMU PRIVATE )