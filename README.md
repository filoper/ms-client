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

* **CMake v3.14+** - found at [https://cmake.org/](https://cmake.org/)

* **Ninja v1.9.0+**

* **C++ Compiler** - needs to support at least the **C++20** standard, i.e. *MSVC*,
*GCC*, *Clang*

* **Homebrew (Mac OS ONLY)** - found at [https://brew.sh/](https://brew.sh/)

* **Visual Studio 2019 (Windows ONLY)**

### Setup the project

```bash
git clone https://github.com/filoper/ms-client.git
```

### Dependencies
Download the required NX files from here [https://github.com/HeavenClient/HeavenClient/tree/master#required-files](https://github.com/HeavenClient/HeavenClient/tree/master#required-files)

See install instructions for your platform below.

#### Windows

```bash
Download BASS from https://www.un4seen.com/download.php?bass24 and place inside `ms-client/thirdparty`.
```

#### Mac
```bash
Download BASS from https://www.un4seen.com and place inside `ms-client/thirdparty`.
```

```bash
brew install lz4
```

```bash
brew install glfw
```

#### Linux
```bash
Download BASS from https://www.un4seen.com and place inside `ms-client/thirdparty`.
```

```bash
sudo apt-get install liblz4-dev
```

```bash
sudo apt-get install libglfw3-dev
```

```bash
sudo apt-get install libfreetype-dev
```

## Build

### Windows
Start Visual Studio 2019 x64 developer terminal.

```bash
cmake -Bbuild -GNinja -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=c:\msclient-install
cmake --build build --config Debug
cmake --build build --target install --config Debug
```

### Mac or Linux
```bash
cmake -Bbuild -GNinja -DCMAKE_INSTALL_PREFIX=./msclient-install
cmake --build build --config Debug
cmake --build build --target install --config Debug
```

## Run
Place all the Nx files in the install location of msclient.

Start your server, probably HeavenMS, then run

```bash
./msclient
```

## Acknowledgements
Contributors to

https://github.com/SYJourney/JourneyClient

https://github.com/HeavenClient/HeavenClient
