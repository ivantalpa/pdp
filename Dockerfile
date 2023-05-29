# Use the latest Ubuntu image as the base
FROM ubuntu:latest

# Update the system and install MPICH and bash
RUN apt-get update && apt-get install -y \
    mpich \
    bash

# Set /bin/bash as the default shell
SHELL ["/bin/bash", "-c"]

# Ensure the working directory exists
RUN mkdir -p /exercises

# Set the working directory to /exercises
WORKDIR /exercises

# Keep the container running
CMD tail -f /dev/null
