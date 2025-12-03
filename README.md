# Adaptive SOME/IP Communication Framework (vSomeIP)

This project demonstrates SOME/IP communication between a client and server using the vSomeIP framework in Docker containers.

## Overview

- **Service (someip-service)**: Offers a SOME/IP service that responds to client requests
- **Client (someip-client)**: Discovers and sends requests to the service

## Project Structure

```
.
├── CMakeLists.txt          # Build configuration
├── docker-compose.yml      # Docker compose configuration  
├── docker/
│   └── Dockerfile          # Container image definition
├── config/
│   ├── service.json        # vSomeIP service configuration
│   └── client.json         # vSomeIP client configuration
└── src/
    ├── service.cpp         # Service implementation
    └── client.cpp          # Client implementation
```

## Building and Running

### Using Docker Compose

1. Build the containers:
   ```bash
   docker compose build
   ```

2. Run the containers:
   ```bash
   docker compose up
   ```

3. Stop the containers:
   ```bash
   docker compose down
   ```

## Service Configuration

- **Service ID**: 0x1234
- **Instance ID**: 0x5678
- **Method ID**: 0x0421
- **Port**: 30509 (TCP)
- **Service IP**: 172.20.0.10
- **Client IP**: 172.20.0.11

## Current Status

The containers are configured to communicate over a Docker bridge network with static IP addresses:
- Service listens on 172.20.0.10:30509
- Client connects from 172.20.0.11

### Implementation Details

- Uses vSomeIP 3.5.11 from GitHub (COVESA/vsomeip)
- C++ code updated for vsomeIP v3 API compatibility
- Client uses availability handler to wait for service discovery
- Docker containers have proper network configuration with specific IPs

### Known Limitations

Service Discovery via multicast does not work reliably across Docker bridge networks. The current configuration uses static service endpoints. For production use cases requiring service discovery, consider:

1. Using `host` network mode in Docker (removes network isolation)
2. Running on the same machine without containers  
3. Using a proper multicast-capable network setup

## Development

### Building Locally

Requirements:
- CMake 3.10+
- C++14 compiler
- vsomeip3 library
- Boost libraries

```bash
mkdir build && cd build
cmake ..
make
```

### Configuration

Edit `config/service.json` and `config/client.json` to modify:
- IP addresses
- Ports  
- Logging levels
- Service discovery settings

## License

See LICENSE file for details.