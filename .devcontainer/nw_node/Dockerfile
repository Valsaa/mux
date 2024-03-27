FROM debian:bullseye

# Install utils
RUN apt update && \
    apt install --yes \
        net-tools \
        socat

# Add a user
RUN useradd -d /home/user -s /bin/bash -G sudo user
RUN echo 'user:user' | chpasswd
USER user

WORKDIR /home/user
