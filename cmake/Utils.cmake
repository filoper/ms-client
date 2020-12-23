# Add a target for formating the project using `clang-format` (i.e: cmake --build build --target clang-format)
function(add_clang_format_target)
    if(NOT ${PROJECT_NAME}_CLANG_FORMAT_BINARY)
    find_program(${PROJECT_NAME}_CLANG_FORMAT_BINARY clang-format)
    endif()
    if(${PROJECT_NAME}_CLANG_FORMAT_BINARY)
    add_custom_target(clang-format
        COMMAND ${${PROJECT_NAME}_CLANG_FORMAT_BINARY}
        -i 
        --style=file --verbose 
        ${CMAKE_CURRENT_LIST_DIR}/*.h
        ${CMAKE_CURRENT_LIST_DIR}/*.cpp 
        ${CMAKE_CURRENT_LIST_DIR}/Audio/*.cpp 
        ${CMAKE_CURRENT_LIST_DIR}/Audio/*.h
        ${CMAKE_CURRENT_LIST_DIR}/Character/*.cpp 
        ${CMAKE_CURRENT_LIST_DIR}/Character/*.h
        ${CMAKE_CURRENT_LIST_DIR}/Character/*/*.cpp 
        ${CMAKE_CURRENT_LIST_DIR}/Character/*/*.h
        ${CMAKE_CURRENT_LIST_DIR}/Data/*.cpp 
        ${CMAKE_CURRENT_LIST_DIR}/Data/*.h
        ${CMAKE_CURRENT_LIST_DIR}/Gameplay/*.cpp 
        ${CMAKE_CURRENT_LIST_DIR}/Gameplay/*.h
        ${CMAKE_CURRENT_LIST_DIR}/Gameplay/*/*.cpp 
        ${CMAKE_CURRENT_LIST_DIR}/Gameplay/*/*.h
        ${CMAKE_CURRENT_LIST_DIR}/Graphics/*.cpp 
        ${CMAKE_CURRENT_LIST_DIR}/Graphics/*.h
        ${CMAKE_CURRENT_LIST_DIR}/IO/*.cpp 
        ${CMAKE_CURRENT_LIST_DIR}/IO/*.h
        ${CMAKE_CURRENT_LIST_DIR}/IO/*/*.cpp 
        ${CMAKE_CURRENT_LIST_DIR}/IO/*/*.h
        ${CMAKE_CURRENT_LIST_DIR}/IO/*/*/*.cpp 
        ${CMAKE_CURRENT_LIST_DIR}/IO/*/*/*.h
        ${CMAKE_CURRENT_LIST_DIR}/Net/*.cpp 
        ${CMAKE_CURRENT_LIST_DIR}/Net/*.h
        ${CMAKE_CURRENT_LIST_DIR}/Net/*/*.cpp 
        ${CMAKE_CURRENT_LIST_DIR}/Net/*/*.h
        ${CMAKE_CURRENT_LIST_DIR}/Net/*/*/*.cpp 
        ${CMAKE_CURRENT_LIST_DIR}/Net/*/*/*.h
        ${CMAKE_CURRENT_LIST_DIR}/Template/*.h
        ${CMAKE_CURRENT_LIST_DIR}/Util/*.cpp 
        ${CMAKE_CURRENT_LIST_DIR}/Util/*.h)
    message("Format the project using the `clang-format` target (i.e: cmake --build build --target clang-format).\n")
    endif()
endfunction()
