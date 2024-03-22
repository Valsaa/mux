FROM mcr.microsoft.com/devcontainers/base:bullseye

# Install some utils
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    python3-pip \
    wget \
    ca-certificates \
    lsb-release \
    software-properties-common \
    gnupg

# Install pre-commit
RUN pip install pre-commit

# Install clang++ and related tools
RUN set -ex && \
    echo "deb http://apt.llvm.org/bullseye/ llvm-toolchain-bullseye-18 main" > /etc/apt/sources.list.d/apt.llvm.org.list && \
    wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key |  tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc && \
    apt update && \
    apt-get install -y clang-18 lldb-18 clang-format-18 clang-tidy-18

# Install CMake
RUN wget -qO- "https://cmake.org/files/v3.20/cmake-3.20.6-linux-x86_64.tar.gz" | tar --strip-components=1 -xz -C /usr/local

# Persitent bash history
#ARG USERNAME="vscode"
#RUN SNIPPET="export PROMPT_COMMAND='history -a' && export HISTFILE=/commandhistory/.bash_history" \
#    && mkdir /commandhistory \
#    && touch /commandhistory/.bash_history \
#    && chown -R $USERNAME /commandhistory \
#    && echo "$SNIPPET" >> "/home/$USERNAME/.bashrc"
