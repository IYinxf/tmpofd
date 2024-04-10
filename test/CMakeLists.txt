macro(MAKE_TEST name)
    find_package(Catch2 3 REQUIRED)
    add_executable(${name} ${name}.cc)
    target_link_libraries(${name} PRIVATE Catch2::Catch2WithMain)
    target_include_directories(${name} PRIVATE ${PROJECT_SOURCE_DIR})
    add_test(NAME ${name} COMMAND $<TARGET_FILE:${name}>)
endmacro(MAKE_TEST)

add_subdirectory(util)
