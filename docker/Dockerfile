# Use Ubuntu 22.04 as base
FROM ubuntu:22.04

# Set non-interactive for apt
ENV DEBIAN_FRONTEND=noninteractive

# Install basic build tools and dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    build-essential \
    libboost-all-dev \
    libasio-dev \
    libtinyxml2-dev \
    pkg-config \
    git \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy your project files into the container
COPY . /app

# Build vsomeip3 from source
RUN git clone https://github.com/COVESA/vsomeip.git /tmp/vsomeip && \
    cd /tmp/vsomeip && \
    mkdir build && cd build && \
    cmake .. && make -j$(nproc) && make install

# Build your service
RUN mkdir -p build && cd build && \
    cmake .. && make -j$(nproc)

# Set the default command
CMD ["./build/service"]
