file(GLOB_RECURSE LibHeaders "./*.h")
file(GLOB_RECURSE LibSources "./*.c")
add_library(list SHARED ${LibSources} ${LibHeaders})

target_include_directories(
    list PRIVATE
    "${CoreDir}/include"
    "${CoreDir}/source"
)
