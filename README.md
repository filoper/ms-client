| Branch         | Status           |
| :-------------:|:----------------:|
| master         | [![Windows](https://github.com/filoper/ms-client/workflows/Windows/badge.svg?branch=master)](https://github.com/filoper/ms-client/actions?query=workflow%3AWindows+branch%3Amaster)    [![Ubuntu](https://github.com/filoper/ms-client/workflows/Ubuntu/badge.svg?branch=master)](https://github.com/filoper/ms-client/actions?query=workflow%3AUbuntu+branch%3Amaster)    [![MacOS](https://github.com/filoper/ms-client/workflows/MacOS/badge.svg?branch=master)](https://github.com/filoper/ms-client/actions?query=workflow%3AMacOS+branch%3Amaster)     |
| dev            | [![Windows](https://github.com/filoper/ms-client/workflows/Windows/badge.svg?branch=dev)](https://github.com/filoper/ms-client/actions?query=workflow%3AWindows+branch%3Adev)    [![Ubuntu](https://github.com/filoper/ms-client/workflows/Ubuntu/badge.svg?branch=dev)](https://github.com/filoper/ms-client/actions?query=workflow%3AUbuntu+branch%3Adev)    [![MacOS](https://github.com/filoper/ms-client/workflows/MacOS/badge.svg?branch=dev)](https://github.com/filoper/ms-client/actions?query=workflow%3AMacOS+branch%3Adev)            |

# ms-client
An ms game client.

## Getting started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites
Download and install the following:

* **Git**

* **CMake v3.15+** - found at [https://cmake.org/](https://cmake.org/)

* **Ninja v1.9.0+**

* **C++ Compiler** - needs to support at least the **C++20** standard, i.e. *MSVC*,
*GCC*, *Clang*

* **Homebrew (Mac OS ONLY)** - found at [https://brew.sh/](https://brew.sh/)

* **Visual Studio 2019 (Windows ONLY)**

### Setup the project

```bash
git clone https://github.com/filoper/ms-client.git
```

Finally, create a new folder called `thirdparty` inside `ms-client` folder.

### Dependencies
Download the required NX files from here [https://github.com/HeavenClient/HeavenClient/tree/master#required-files](https://github.com/HeavenClient/HeavenClient/tree/master#required-files)

See install instructions below for your platform.
> ***Note:*** *Place all folders created through `git clone` inside the `thirdparty` folder.*

#### Windows
Start Visual Studio 2019 x64 developer terminal.

```bash
Download and compile lz4 static library https://github.com/lz4/lz4/archive/v1.9.2.zip
Navigate to `visual/VS2017/liblz4` open the project and retarget it to VS2019 before compiling.

Copy the content of `lz4-1.9.2/lib` to `thirdparty/lz4/include`.
Copy the compiled library to `thirdparty/lz4/dll`.

In msclient CMakeLists.txt change
TARGET_LINK_LIBRARIES(msclient ${PROJECT_SOURCE_DIR}/thirdparty/lz4/dll/liblz4.dll.a) 
to
TARGET_LINK_LIBRARIES(msclient ${PROJECT_SOURCE_DIR}/thirdparty/lz4/dll/lz4.lib)
```

```bash
Download BASS from https://www.un4seen.com/download.php?bass24 and place inside `thirdparty`.
```

```bash
mkdir NoLifeNx
cd NoLifeNx
git clone https://github.com/filoper/NoLifeNx.git nlnx
cd nlnx
cmake -Bbuild -GNinja -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

```bash
Download https://github.com/ubawurinna/freetype-windows-binaries/archive/v2.10.2.zip 
```

```bash
git clone https://github.com/Dav1dde/glad.git
cd glad
cmake -Bbuild -GNinja -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

```bash
git clone https://github.com/glfw/glfw 
cd glfw
cmake -Bbuild -GNinja -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

```bash
git clone https://github.com/chriskohlhoff/asio.git
```

```bash
git clone https://github.com/nothings/stb.git
```

#### Mac
```bash
Download BASS from https://www.un4seen.com and place inside `thirdparty`.
```

```bash
git clone https://github.com/Dav1dde/glad.git
cd glad
cmake -Bbuild -GNinja -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

```bash
brew install lz4
```

```bash
mkdir NoLifeNx
cd NoLifeNx
git clone https://github.com/filoper/NoLifeNx.git nlnx
cd nlnx
cmake -Bbuild -GNinja -DCMAKE_BUILD_TYPE=Release
```

```bash
brew install glfw
```

```bash
git clone https://github.com/chriskohlhoff/asio.git
```

```bash
git clone https://github.com/nothings/stb.git
```

#### Linux
```bash
Download BASS from https://www.un4seen.com and place inside `thirdparty`.
```

```bash
sudo apt-get install liblz4-dev
```
```bash
mkdir NoLifeNx
cd NoLifeNx
git clone https://github.com/filoper/NoLifeNx.git nlnx
cd nlnx
cmake -Bbuild -GNinja -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

```bash
sudo apt-get install libglfw3-dev
```

```bash
sudo apt-get install libfreetype-dev
```

```bash
git clone https://github.com/chriskohlhoff/asio.git
```

```bash
git clone https://github.com/nothings/stb.git
```

## Build

### Windows
Start Visual Studio 2019 x64 developer terminal.

```bash
cmake -Bbuild -GNinja -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=c:\msclient-install
cmake --build build --config Release
cmake --build build --target install --config Release
```

### Mac or Linux
```bash
cmake -Bbuild -GNinja -DCMAKE_INSTALL_PREFIX=./msclient-install
cmake --build build --config Release
cmake --build build --target install --config Release
```

## Run
Place all the Nx files in the install location of msclient.

Start your server, probably HeavenMS, and then run

```bash
./msclient
```

## Acknowledgements
Contributors to

https://github.com/SYJourney/JourneyClient

https://github.com/HeavenClient/HeavenClient
