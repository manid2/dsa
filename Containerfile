FROM debian:testing-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    python3 \
    python3-pip \
    python3-venv \
    clang-format \
    git \
    vim \
    && rm -rf /var/lib/apt-get/lists/*

RUN pip3 install --no-cache-dir --break-system-packages pre-commit

WORKDIR /dsa

CMD ["sleep", "infinity"]