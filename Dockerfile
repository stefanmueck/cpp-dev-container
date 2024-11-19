FROM debian:12.6-slim
LABEL version="1.0"

ARG DEVUSER="vscode"

# Install required packages
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    bash bash-completion vim ccache \
    ca-certificates curl gnupg2 openssh-client \
    make cmake cmake-curses-gui ninja-build \
    gcc-12 g++-12 gdb gdbserver iwyu \
    clang-14 clang-tidy-14 clang-format-14 clangd-14 \
    cppcheck git tig catch2 \
    python3 python3-pip python3-venv \
    iputils-ping

# Install trompeloeil from source
ARG BUILD_DIR="/tmp/deps"
RUN mkdir -p $BUILD_DIR && \
    cd $BUILD_DIR && \
    git clone --depth 1 --branch v47 https://github.com/rollbear/trompeloeil.git &&\
    cd trompeloeil &&\
    mkdir build &&\
    cd build && \
    cmake .. && \
    cmake --build . --target install

# cleanup
RUN rm -rf $BUILD_DIR/*

# add a user
RUN useradd -ms /bin/bash $DEVUSER
RUN mkdir -p /home/$DEVUSER/.ssh

# basic ssh confiuration
RUN echo "Host *\n\tStrictHostKeyChecking no\n" >> /home/$DEVUSER/.ssh/config
RUN chown -R $DEVUSER:$DEVUSER /home/$DEVUSER/.ssh

# add links to clang-tidy and clang-format
RUN ln -s /usr/bin/clang-format-14 /usr/bin/clang-format
RUN ln -s /usr/bin/clang-tidy-14 /usr/bin/clang-tidy
RUN ln -s /usr/bin/clangd-14 /usr/bin/clangd

# Install Starship shell prompt
RUN curl -fsSL https://starship.rs/install.sh | sh -s -- -y
RUN echo 'eval "$(starship init bash)"' >> /home/$DEVUSER/.bashrc

# impersonate user
USER $DEVUSER

# Set the working directory
WORKDIR /home/$DEVUSER

# Install conan in virtual environment
RUN python3 -m venv venv
RUN . /home/$DEVUSER/venv/bin/activate && \
    pip install --upgrade pip && pip install conan
ENV PATH="/home/$DEVUSER/venv/bin:$PATH"
RUN conan --version

# Set the entry point to bash
CMD ["/bin/bash"]
