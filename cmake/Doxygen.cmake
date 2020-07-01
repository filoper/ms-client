if(${PROJECT_NAME}_ENABLE_DOXYGEN)
    set(DOXYGEN_CALLER_GRAPH YES)
    set(DOXYGEN_CALL_GRAPH YES)
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_GENERATE_HTML YES)
    set(
        DOXYGEN_EXCLUDE_PATTERNS
        */thirdparty/*)
    find_package(Doxygen REQUIRED dot)
    doxygen_add_docs(
        doxygen
        ${PROJECT_SOURCE_DIR}/Audio
        ${PROJECT_SOURCE_DIR}/Character
        ${PROJECT_SOURCE_DIR}/Data
        ${PROJECT_SOURCE_DIR}/Gameplay
        ${PROJECT_SOURCE_DIR}/Graphics
        ${PROJECT_SOURCE_DIR}/IO
        ${PROJECT_SOURCE_DIR}/Net
        ${PROJECT_SOURCE_DIR}/Template
        ${PROJECT_SOURCE_DIR}/Util
        ${PROJECT_SOURCE_DIR}/Configuration.h
        ${PROJECT_SOURCE_DIR}/Constants.h
        ${PROJECT_SOURCE_DIR}/Error.h
        ${PROJECT_SOURCE_DIR}/MapleStory.h
        ${PROJECT_SOURCE_DIR}/resource.h
        ${PROJECT_SOURCE_DIR}/Timer.h
        ${PROJECT_SOURCE_DIR}/MapleStory.cpp)
endif()
