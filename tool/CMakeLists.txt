SET(LIB_NAME "clang-wrapper")
SET(EXE_NAME "codeinfo-tool")

include_directories(".")

find_package(Boost COMPONENTS system program_options filesystem REQUIRED)

add_library(${LIB_NAME} SHARED
               "src/compilation_db.cpp"
               "src/cursor.cpp"
               "src/cx_string.cpp"
               "src/diagnostic.cpp"
               "src/file.cpp"
               "src/index.cpp"
               "src/options.cpp"
               "src/source_location.cpp"
               "src/temp_file.cpp"
               "src/translation-unit.cpp"
)
target_link_libraries(${LIB_NAME} clang ${Boost_LIBRARIES})

add_executable(${EXE_NAME}
               "main.cpp"
)

target_link_libraries(${EXE_NAME} ${LIB_NAME})
