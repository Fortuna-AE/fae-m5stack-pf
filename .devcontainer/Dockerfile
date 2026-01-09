FROM espressif/idf:release-v4.4

# Set default shell
SHELL ["/bin/bash", "-c"]

# Setting time zone
ENV TZ=Asia/Tokyo
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Install apt packages(non-interractive)
RUN apt -y update \
    && apt install -y --no-install-recommends \
        curl  \
        locales \
        build-essential  \
        usbutils  \
        socat  \
        git  \
        vim  \
        tig  \
    && apt clean \
    && rm -rf /var/lib/apt/lists/*

# Configure locale
RUN locale-gen en_US.UTF-8
ENV LANG=en_US.UTF-8
ENV LANGUAGE=en_US:en
ENV LC_ALL=en_US.UTF-8

# Manage pip packages
COPY requirements.txt .
RUN pip install --upgrade pip \
    && pip install --no-cache-dir -r requirements.txt

# Set environment variable
RUN echo '. ${IDF_PATH}/export.sh' >> ~/.bashrc

WORKDIR /workspaces
CMD ["/bin/bash"]