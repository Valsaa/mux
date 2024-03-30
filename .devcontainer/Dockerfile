FROM mcr.microsoft.com/devcontainers/base:bullseye

# Install system utils and ninja
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3                     \
    python3-dev                 \
    python3-pyaudio             \
    python3-pip                 \
    wget                        \
    ca-certificates             \
    lsb-release                 \
    software-properties-common  \
    gnupg                       \
    doxygen

# Install clang++ and related tools
RUN set -ex && \
    echo "deb http://apt.llvm.org/bullseye/ llvm-toolchain-bullseye-18 main" > /etc/apt/sources.list.d/apt.llvm.org.list && \
    wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key |  tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc

RUN set -eux; \
    # Install clang/clang++
    apt-get update && apt-get install --no-install-recommends -y \
        clang-18    \
        llvm-18     \
        lld-18;     \
    # Ensure that clang/clang++ are callable directly
    ln --symbolic clang-18 /usr/bin/clang && ln --symbolic clang /usr/bin/clang++ && ln --symbolic lld-18 /usr/bin/ld.lld; \
    ln --symbolic clang-18 /usr/bin/clang-cl && ln --symbolic llvm-ar-18 /usr/bin/llvm-lib && ln --symbolic lld-link-18 /usr/bin/lld-link; \
    # Use clang instead of gcc when compiling and linking binaries targeting the host
    update-alternatives --install /usr/bin/cc cc /usr/bin/clang 100;        \
    update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 100;    \
    update-alternatives --install /usr/bin/ld ld /usr/bin/ld.lld 100;       \
    apt-get remove -y --auto-remove;                                        \
    rm -rf /var/lib/apt/lists/*;

RUN set -eux; \
    # Install xwin
    wget --quiet --output-document=- "https://github.com/Jake-Shadle/xwin/releases/download/0.5.0/xwin-0.5.0-x86_64-unknown-linux-musl.tar.gz" | \
    tar --strip-components=1 --extract --gzip --directory /usr/local/bin xwin-0.5.0-x86_64-unknown-linux-musl/xwin; \
    # Splat the CRT and SDK files to /xwin/crt and /xwin/sdk respectively
    xwin --accept-license splat --preserve-ms-arch-notation --output /xwin; \
    ln --symbolic /xwin/crt/lib/x64/msvcrt.lib /xwin/crt/lib/x64/msvcrtd.lib; \
    # Remove unneeded files to reduce image size
    rm -rf .xwin-cache /usr/local/bin/xwin;

RUN set -eux; \
    # Install Ninja
    wget --quiet --output-document=/tmp/ninja.zip "https://github.com/ninja-build/ninja/releases/download/v1.11.1/ninja-linux.zip"; \
    unzip -d /usr/local/bin /tmp/ninja.zip; \
    rm -f /tmp/ninja.zip

RUN set -eux; \
    # Install CMake
    wget --quiet --output-document=- "https://cmake.org/files/v3.20/cmake-3.20.6-linux-x86_64.tar.gz" | \
    tar --strip-components=1 --extract --gzip --directory /usr/local

# Install python utils
RUN pip install         \
    pre-commit          \
    pytest              \
    sphinx              \
    sphinx_rtd_theme    \
    sphinx-sitemap      \
    breathe
