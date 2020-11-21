# Contributing to ms-client

### DOs

* **DO** create one pull request per improvement.
* **DO** follow the [Coding and Style](#code-formatting) guidelines, and keep code changes as small as possible.
* **DO** link the issue you are addressing in the pull request.
* **DO** write a good description for your pull request. More detail is better.

### DO NOTs

* **DO NOT** merge multiple changes into one PR unless they have the same root cause.
* **DO NOT** merge directly into the master branch.

## Code Formatting

***Run clang-format***

Use the following commands from the project's root directory to run clang-format (must be installed on the host system).

**Run the CMake target for `clang-format`:**
````bash
cmake --build build --target clang-format
````
