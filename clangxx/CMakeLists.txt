SET(LIB_NAME "clangxx")

add_library(${LIB_NAME} SHARED
               "src/compilation_db.cpp"
               "src/cursor.cpp"
               "src/cx_string.cpp"
               "src/diagnostic.cpp"
               "src/file.cpp"
               "src/index.cpp"
               "src/source_location.cpp"
               "src/translation-unit.cpp"
               "src/type.cpp"
)
target_link_libraries(${LIB_NAME} clang)
