#--
# Step 1: Build QEMU
#--

FROM debian:stable-slim as qemu-builder
ARG QEMU_VERSION=5.2.0
ARG MACHINE=mps2-an500

RUN # update packages
RUN apt update

WORKDIR /var/qemu

RUN apt-get -y install wget
RUN # download QEMU: https://www.qemu.org/download/#source
RUN wget https://download.qemu.org/qemu-${QEMU_VERSION}.tar.xz

RUN # install QEMU dependencies

RUN apt-get -y install python build-essential libglib2.0-dev libpixman-1-dev

RUN apt-get -y install flex bison ninja-build

RUN #verify signature (copied key from Dockerpi. Will it work?)
RUN apt-get -y install gpg
RUN wget "https://download.qemu.org/qemu-${QEMU_VERSION}.tar.xz.sig"
RUN gpg --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys CEACC9E15534EBABB82D3FA03353C9CEF108B584
RUN gpg --verify "qemu-${QEMU_VERSION}.tar.xz.sig" "qemu-${QEMU_VERSION}.tar.xz"

RUN # untar, configure, and build QEMU
RUN tar xvJf qemu-${QEMU_VERSION}.tar.xz
# We only need to build arm-softmmu
RUN qemu-${QEMU_VERSION}/configure --static --target-list=arm-softmmu
# -j option with nproc lets us build QEMU with all of our processors
RUN make -j$(nproc)

RUN # Strip the binary to reduce size
RUN strip "arm-softmmu/qemu-system-arm"

#--
# Step 2: Load entryfile
#--

# For now, get hex file to run on the emulated mps-an500
COPY entry.sh .

# send output about machine startup to user's stdout

# expose the port for QEMU monitor so that the user can poke around their running machine
EXPOSE 7001

RUN # Launch listener

CMD ["bash", "entry.sh"]

# after this works, make the copy instruction from earlier copy an entire folder and then direct the file option in devices to the new folder
# RUN ./qemu-system-arm -M mps2-an500 -m 16M -no-reboot -nographic -cpu cortex-m7 -device loader,file=/var/qemu/Blinky.hex -monitor telnet:localhost:1234,server,nowait
