file(GLOB_RECURSE LibHeaders "./*.h")
file(GLOB_RECURSE LibSources "./*.c")
add_library(adv_ds SHARED ${LibSources} ${LibHeaders})

target_include_directories(
    adv_ds PRIVATE
    "${CoreDir}/include"
    "${CoreDir}/source"
)
