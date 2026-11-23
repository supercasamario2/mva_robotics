
FROM python:3.12-slim

WORKDIR /app

# Install system dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Install Eigen 5.0.1
ARG EIGEN_VERSION=5.0.1

RUN git clone --depth 1 \
    --branch ${EIGEN_VERSION} \
    https://gitlab.com/libeigen/eigen.git /tmp/eigen \
    && mkdir -p /usr/local/include/eigen3 \
    && cp -r /tmp/eigen/Eigen /usr/local/include/eigen3/ \
    && cp -r /tmp/eigen/unsupported /usr/local/include/eigen3/ \
    && rm -rf /tmp/eigen# Install Python dependencies

# COPY requirements.txt .
COPY . .

RUN pip install --no-cache-dir -r requirements.txt

# CMD ["python", "main.py"]
