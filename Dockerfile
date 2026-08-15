FROM ubuntu:24.04

# Предотвращаем интерактивные запросы пакетов
ENV DEBIAN_FRONTEND=noninteractive \
    LANG=en_US.UTF-8 \
    LANGUAGE=en_US:en \
    LC_ALL=en_US.UTF-8

# Устанавливаем зависимости для сборки LLVM
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    ccache \
    ninja-build \
    git \
    python3 \
    python3-pip \
    python3-dev \
    zlib1g-dev \
    libxml2-dev \
    libedit-dev \
    libncurses-dev \
    swig \
    binutils-dev \
    wget \
    curl \
    locales \
    ca-certificates \
    && locale-gen en_US.UTF-8 \
    && rm -rf /var/lib/apt/lists/*

# Каталог для build-артефактов
RUN mkdir -p /build /src /install

# Копируем скрипт сборки
COPY build.sh /usr/local/bin/build.sh
RUN chmod +x /usr/local/bin/build.sh

WORKDIR /build

ENTRYPOINT ["/usr/local/bin/build.sh"]