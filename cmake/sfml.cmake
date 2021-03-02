message("-- External Project: sfml")
include(FetchContent)
FetchContent_Declare(
    sfml
    URL https://github.com/SFML/SFML/archive/2.5.1.zip)

set(SFML_BUILD_AUDIO OFF CACHE BOOL "TRUE to build SFML's Audio module." FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "TRUE to build SFML libs ass DLL's" FORCE)

FetchContent_MakeAvailable(sfml)

set(sfml_libraries "sfml-graphics" "sfml-network" "sfml-system" "sfml-window")

if (WIN32)
    list(APPEND sfml_libraries "sfml-main")
endif(WIN32)

foreach(library ${sfml_libraries})
    set_target_properties(${library} PROPERTIES FOLDER "third_party/sfml")
endforeach(library)