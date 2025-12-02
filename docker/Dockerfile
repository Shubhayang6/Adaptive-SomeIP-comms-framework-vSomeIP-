FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt update && apt install -y \
    git cmake build-essential \
    libboost-all-dev libtool pkg-config \
    autoconf automake \
    && rm -rf /var/lib/apt/lists/*

# Clone and build VSOMEIP
WORKDIR /opt
RUN git clone https://github.com/GENIVI/vsomeip.git

WORKDIR /opt/vsomeip
RUN mkdir build && cd build && cmake .. && make -j4 && make install

# Copy project into /app
WORKDIR /app
COPY . .

# Build the client and service
RUN mkdir build
WORKDIR /app/build
RUN cmake .. && make -j4 || cat /app/build/CMakeFiles/CMakeError.log || true

# Default directory
WORKDIR /app/build
