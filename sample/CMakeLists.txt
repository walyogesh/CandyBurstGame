set(target_name "sample-app")

set(src_precompiled
    "src/precompiled/pch.h")

file(GLOB_RECURSE src_sample "src/*.*")

set(all_sources
    ${src_precompiled}
    ${src_sample})

add_executable(${target_name} WIN32 MACOSX_BUNDLE ${all_sources})

source_group("sample\\src" FILES ${src_sample})
source_group("sample\\pch" FILES ${src_precompiled})

target_compile_definitions(${target_name} PRIVATE SAMPLE_ASSETS_DIR="${PROJECT_SOURCE_DIR}/assets/")

target_link_libraries(${target_name} "engine-lib")
target_compile_features(${target_name} INTERFACE cxx_std_17)
target_include_directories(${target_name} PRIVATE "../engine/include")
target_precompile_headers(${target_name} PUBLIC ${src_precompiled})

set_target_properties(${target_name} PROPERTIES FOLDER "worksample")
set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)
