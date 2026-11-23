
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
    && cmake -S /tmp/eigen -B /tmp/eigen-build \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/usr/local \
        -DEIGEN_BUILD_TESTING=OFF \
        -DEIGEN_BUILD_DOC=OFF \
    && cmake --install /tmp/eigen-build \
    && rm -rf /tmp/eigen /tmp/eigen-build

# Install Python dependencies
# COPY requirements.txt .
# RUN pip install --no-cache-dir -r requirements.txt

COPY . .

CMD ["python", "main.py"]
