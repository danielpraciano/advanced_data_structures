file(GLOB_RECURSE TestHeaders "include/*.h")
file(GLOB_RECURSE TestSources "suites/*.c")

foreach(FileName ${TestSources})
    get_filename_component(TestName ${FileName} NAME_WE)
    add_executable(${TestName} ${FileName} ${TestHeaders})
    target_link_libraries(${TestName} adv_ds)

    target_include_directories(
        ${TestName} PRIVATE
        "${CoreDir}/include"
        "include"
    )
endforeach()
