include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

FetchContent_Declare(
  glad
  GIT_REPOSITORY    https://github.com/Dav1dde/glad.git
  GIT_TAG           b5d260b65b3edbbd9e75f5a6c9924fe0ff4f04dd
  PREFIX            "${PROJECT_SOURCE_DIR}/thirdparty"
  SOURCE_DIR        "${PROJECT_SOURCE_DIR}/thirdparty/glad"
  BINARY_DIR        "${PROJECT_SOURCE_DIR}/thirdparty/glad-build"
)

FetchContent_Declare(
  nlnx
  GIT_REPOSITORY    https://github.com/filoper/NoLifeNx.git
  GIT_TAG           aee212e7b0995ee4aaee58393f83c592f4a718a6
  PREFIX            "${PROJECT_SOURCE_DIR}/thirdparty"
  SOURCE_DIR        "${PROJECT_SOURCE_DIR}/thirdparty/nlnx"
  BINARY_DIR        "${PROJECT_SOURCE_DIR}/thirdparty/nlnx-build"
)

FetchContent_Declare(
  stb
  GIT_REPOSITORY    https://github.com/nothings/stb.git
  GIT_TAG           b42009b3b9d4ca35bc703f5310eedc74f584be58
  PREFIX            "${PROJECT_SOURCE_DIR}/thirdparty"
  SOURCE_DIR        "${PROJECT_SOURCE_DIR}/thirdparty/stb"
  BINARY_DIR        "${PROJECT_SOURCE_DIR}/thirdparty/stb-build"
)

FetchContent_Declare(
  asio
  GIT_REPOSITORY    https://github.com/chriskohlhoff/asio.git
  GIT_TAG           5fb2ea03ac6df7d65fc0101745e01ecff0bbd5fe
  PREFIX            "${PROJECT_SOURCE_DIR}/thirdparty"
  SOURCE_DIR        "${PROJECT_SOURCE_DIR}/thirdparty/asio"
  BINARY_DIR        "${PROJECT_SOURCE_DIR}/thirdparty/asio-build"
)

IF (WIN32)
    FetchContent_Declare(
      glfw
      GIT_REPOSITORY    https://github.com/glfw/glfw.git
      GIT_TAG           3327050ca66ad34426a82c217c2d60ced61526b7
      PREFIX            "${PROJECT_SOURCE_DIR}/thirdparty"
      SOURCE_DIR        "${PROJECT_SOURCE_DIR}/thirdparty/glfw"
      BINARY_DIR        "${PROJECT_SOURCE_DIR}/thirdparty/glfw-build"
    )

    FetchContent_MakeAvailable(glfw)
ENDIF()

FetchContent_MakeAvailable(glad nlnx asio stb)

