set(target_name "engine-lib")

set(src_precompiled
    "src/precompiled/pch.h")

set(src_include
	"include/engine.h")

set(src_engine
    "src/game.h"
    "src/window.h"
	"src/sprite.h"
	"src/text.h"
	"src/mouse.h"
    "src/dummy.cpp")

set(all_sources
    ${src_precompiled}
    ${src_include}
    ${src_engine})

add_library(${target_name} STATIC ${all_sources})

source_group("engine\\include" FILES ${src_include})
source_group("engine\\src" FILES ${src_engine})
source_group("engine\\pch" FILES ${src_precompiled})

target_include_directories(${target_name} PUBLIC ${sfml_include_dirs})
target_link_libraries(${target_name} "compiler-warnings")
target_link_libraries(${target_name} ${sfml_libraries})
target_compile_features(${target_name} INTERFACE cxx_std_17)
target_precompile_headers(${target_name} PUBLIC ${src_precompiled})

set_target_properties(${target_name} PROPERTIES FOLDER "worksample")
set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)