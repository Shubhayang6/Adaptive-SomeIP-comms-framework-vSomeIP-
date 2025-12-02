FROM ubuntu:22.04

# Avoiding interactive prompts
RUN apt update && apt install -y \
    git cmake build-essential \
    libboost-all-dev libtool pkg-config \
    autoconf automake \
    && rm -rf /var/lib/apt/lists/*

# Build and install vsomeip
WORKDIR /opt
RUN git clone https://github.com/Shubhayang6/Adaptive-SomeIP-comms-framework-vSomeIP-.git
WORKDIR /opt/vsomeip
RUN mkdir build && cd build && cmake .. && make -j4 && make install

# Copy project into container
WORKDIR /app
COPY . .

# Build the client and service
RUN mkdir build && cd build && cmake .. && make -j4

# Set default directory on container run
WORKDIR /app/build