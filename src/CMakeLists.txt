#add_library (LogicVerifier main.cpp)


#add_subdirectory(logic)
#add_subdirectory(parser)
#add_subdirectory(config)

include_directories(parser)
find_package(Boost 1.58.0)
#find_library(BoostLib boost)

if(Boost_FOUND)
	# SYSTEM surpress boost header warning
	if(XCODE)
		# see https://public.kitware.com/Bug/view.php?id=15687
  		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem ${Boost_INCLUDE_DIRS}")
	else(XCODE)
		include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
	endif(XCODE)
endif(Boost_FOUND)

add_executable(main
  main.cpp
  parser/cfg_parser.cpp
  parser/cfg_parser.hpp
  logic/symbol/symbol.cpp
  logic/symbol/symbol.hpp
)

set_property(TARGET main PROPERTY CXX_STANDARD 11)
set_property(TARGET main PROPERTY CXX_EXTENSIONS OFF)


configure_file(input/pl1.json input/pl1.json COPYONLY)

#find_library(libX11 Xaw Xmu Xt Xext png z m /usr/X11/lib)
#find_library(libXaw Xaw /usr/X11/lib)
#target_link_libraries(main ntl plotter ${libX11} ${libXaw})
