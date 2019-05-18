cmake_minimum_required(VERSION 2.8)

project(GameofLife)
add_executable(GameofLife "main.cpp"
                               "Board.cpp"
                               "Board.h"
#                               "button.cpp"
#                               "button.h"
#                               "widget.h"
#                               "widget.cpp"
#                               "label.h"
#                               "label.cpp"
#                               "textbutton.h"
#                               "textbutton.cpp"
#                               "container.h"
#                               "container.cpp"
#                               "frame.h"
#                               "frame.cpp"
#                               "action.h"
#                               "action.cpp"
#                               "actiontarget.h"
#                               "actiontarget.cpp"
                               )

set (CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED COMPONENTS
                                    network
                                    audio
                                    graphics
                                    window
                                    system)
target_link_libraries(GameofLife ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(GameofLife ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.65.1 COMPONENTS date_time filesystem system)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(GameofLife ${Boost_LIBRARIES})
endif()
