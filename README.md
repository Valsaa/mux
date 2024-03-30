# Mux

## Configure

| Tool               | Action                                            |
| ------------------ | ------------------------------------------------- |
| Visual Studio Code | Press ```F1``` then select ```CMake: Configure``` |
| Bash               | ```cmake -S . -B ./build```                       |

## Build

| Tool               | Action                      |
| ------------------ | --------------------------- |
| Visual Studio Code | Press ```F7```              |
| Bash               | ```cmake --build ./build``` |

# Clang-cl cross compile

```
#!/usr/bin/env sh

exec /usr/bin/clang-cl --target=x86_64-pc-windows-msvc -vctoolsdir /xwin/crt -winsdkdir /xwin/sdk -fuse-ld=lld "$@"
```
