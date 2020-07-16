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

* **C++ Compiler** - needs to support at least the **C++17** standard, i.e. *MSVC*,
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
Download https://github.com/lz4/lz4/releases/download/v1.9.2/lz4_win64_v1_9_2.zip
```

```bash
Download https://www.un4seen.com/download.php?bass24
```

```bash
mkdir NoLifeNx
cd NoLifeNx
git clone https://github.com/lain3d/NoLifeNx nlnx
cd nlnx
$content = Get-Content -Path 'CMakeLists.txt'
$content = $content.replace('/../../lz4/lib)', '/../../lz4/include)')
$content = $content.replace('/../../lz4/lib/liblz4.a)', '/../../lz4/dll/liblz4.lib)')
$content | Set-Content -Path 'CMakeLists.txt'
$content_check = Get-Content -Path 'CMakeLists.txt'
echo $content_check
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
brew install openal-soft
```

```bash
git clone https://github.com/kcat/alure
cd alure
cmake -Bbuild -GNinja -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
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
git clone https://github.com/lain3d/NoLifeNx nlnx
cd nlnx
sed -i '' '$d' CMakeLists.txt
sed -i '' '$d' CMakeLists.txt
echo "include_directories(/usr/local/Cellar/lz4/1.9.2/include)" >> CMakeLists.txt
echo "target_link_libraries(NoLifeNx /usr/local/Cellar/lz4/1.9.2/lib/liblz4.a)" >> CMakeLists.txt
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
sudo apt-get update
sudo apt-get install libopenal-dev
```

```bash
git clone https://github.com/kcat/alure
cd alure
cmake -Bbuild -GNinja 
cmake --build build --config Release
```

```bash
sudo apt-get install liblz4-dev
```
```bash
mkdir NoLifeNx
cd NoLifeNx
git clone https://github.com/lain3d/NoLifeNx nlnx
cd nlnx
sed -i '$d' CMakeLists.txt
sed -i '$d' CMakeLists.txt
echo "include_directories(/usr/lz4/1.9.2/include)" >> CMakeLists.txt
echo "target_link_libraries(NoLifeNx /usr/lz4/1.9.2/lib/liblz4.a)" >> CMakeLists.txt
cmake -Bbuild -GNinja -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

```bash
sudo apt-get install libglfw3-dev
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
