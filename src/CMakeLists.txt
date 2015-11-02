#add_library (LogicVerifier main.cpp)

add_executable(main main.cpp)

set_property(TARGET main PROPERTY CXX_STANDARD 11)
set_property(TARGET main PROPERTY CXX_EXTENSIONS OFF)


#find_library(libX11 Xaw Xmu Xt Xext png z m /usr/X11/lib)
#find_library(libXaw Xaw /usr/X11/lib)
#target_link_libraries(main ntl plotter ${libX11} ${libXaw})
