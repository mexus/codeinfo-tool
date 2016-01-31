SET(EXE_NAME "codeinfo-tool")

find_package(Boost COMPONENTS system program_options filesystem REQUIRED)

add_executable(${EXE_NAME}
               "main.cpp"
               "src/options.cpp"
)

target_link_libraries(${EXE_NAME} clangxx ${Boost_LIBRARIES})
