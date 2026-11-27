
FROM ubuntu:24.04

# ARGUMENTS
ARG DRAKE_VERSION=1.55.0

WORKDIR /app

#
# APT INSTALLS
#

RUN apt-get update && apt-get install -y --no-install-recommends \
    wget \
    build-essential \
    cmake \
    git \
    ca-certificates \
    libeigen3-dev \
    python3 \
    python3-pip \
    python3-venv \
    python3-dev \
    pybind11-dev

#
# DRAKE INSTALL
#

RUN wget -O /tmp/drake.deb \
    https://github.com/RobotLocomotion/drake/releases/download/v${DRAKE_VERSION}/drake-dev_${DRAKE_VERSION}-1_amd64-noble.deb

RUN apt-get install -y --no-install-recommends /tmp/drake.deb

RUN rm /tmp/drake.deb && rm -rf /var/lib/apt/lists/*


ENV CMAKE_PREFIX_PATH=/opt/drake
ENV PATH="/opt/drake/bin:${PATH}"

#
# PYTHON ENVIRONMENT
#

RUN python3 -m venv --system-site-packages /opt/venv

ENV PATH="/opt/venv/bin:${PATH}"

#
# PYTHON DEPENDENCIES INSTALL
#

# COPY requirements.txt .
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

ENV CMAKE_PREFIX_PATH="/opt/drake:/opt/venv/lib/python3.12/site-packages/cmeel.prefix"

COPY . .

# CMD ["python", "main.py"]
