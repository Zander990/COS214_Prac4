FROM ubuntu:22.04

# Non-interactive so apt does not stop on tzdata prompts
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
        g++ \
        make \
        gdb \
        valgrind \
        doxygen \
        graphviz \
        git \
        ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /taskforge

# Source is normally bind-mounted at run time, but COPY keeps the image
# self-contained if the marker builds without mounting.
COPY . /taskforge

CMD ["/bin/bash"]
