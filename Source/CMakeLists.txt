get_filename_component(BUILD_PARENT_DIR ${CMAKE_BINARY_DIR} PATH)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_INSTALL_PREFIX "${BUILD_PARENT_DIR}" CACHE PATH "Install path prefix, prepended onto install directories." FORCE)

find_package( Curses REQUIRED )

set (NCURSESTEST_SOURCE
    NCursesTest.cc
    )

add_executable (NCursesTest ${NCURSESTEST_SOURCE})

target_link_libraries (NCursesTest LINK_PUBLIC ${CURSES_LIBRARIES})

set (NCURSESCOLORTEST_SOURCE
    NCursesColorTest.cc
    )

add_executable (NCursesColorTest ${NCURSESCOLORTEST_SOURCE})

target_link_libraries (NCursesColorTest LINK_PUBLIC ${CURSES_LIBRARIES})

set (THREADTEST_SOURCE
    ThreadTest.cc
    )

add_executable (ThreadTest ${THREADTEST_SOURCE})

target_link_libraries (ThreadTest LINK_PUBLIC ${CURSES_LIBRARIES})

set (KNIGHTSTOUR_SOURCE
    KTTypeDefs.cc
    Random.cc
    KTKnightGraph.cc
    KTNeuralNetwork.cc
    KTDisplay.cc
    KnightsTour.cc
)

add_executable (KnightsTour ${KNIGHTSTOUR_SOURCE})

target_link_libraries (KnightsTour LINK_PUBLIC ${CURSES_LIBRARIES})

install (TARGETS NCursesTest NCursesColorTest ThreadTest KnightsTour DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
