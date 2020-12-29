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
        ${PROJECT_SOURCE_DIR}/src/Audio
        ${PROJECT_SOURCE_DIR}/src/Character
        ${PROJECT_SOURCE_DIR}/src/Data
        ${PROJECT_SOURCE_DIR}/src/Gameplay
        ${PROJECT_SOURCE_DIR}/src/Graphics
        ${PROJECT_SOURCE_DIR}/src/IO
        ${PROJECT_SOURCE_DIR}/src/Net
        ${PROJECT_SOURCE_DIR}/src/Template
        ${PROJECT_SOURCE_DIR}/src/Util
        ${PROJECT_SOURCE_DIR}/src/Configuration.h
        ${PROJECT_SOURCE_DIR}/src/Constants.h
        ${PROJECT_SOURCE_DIR}/src/Error.h
        ${PROJECT_SOURCE_DIR}/src/MSClient.h
        ${PROJECT_SOURCE_DIR}/src/resource.h
        ${PROJECT_SOURCE_DIR}/src/Timer.h
        ${PROJECT_SOURCE_DIR}/src/MSClient.cpp
        ${PROJECT_SOURCE_DIR}/src/Game.cpp
        ${PROJECT_SOURCE_DIR}/src/Game.h)
endif()
