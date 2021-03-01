#--
# Step 1: Build QEMU
#--

FROM debian:stable-slim as qemu-builder
ARG QEMU_VERSION=5.2.0
ARG MACHINE=mps2-an500

RUN # update packages
RUN apt update

WORKDIR /var/qemu

RUN apt -y install wget
RUN # download QEMU: https://www.qemu.org/download/#source
RUN wget https://download.qemu.org/qemu-${QEMU_VERSION}.tar.xz

RUN # install dependencies

RUN apt -y install python build-essential libglib2.0-dev libpixman-1-dev

RUN apt -y install flex bison ninja-build

# verify signature (what does this mean? how does it work?)
#RUN apt-get -y install gpg
#RUN wget "https://download.qemu.org/${QEMU_TARBALL}.sig"
#RUN gpg --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys CEACC9E15534EBABB82D3FA03353C9CEF108B584
#RUN gpg --verify "${QEMU_TARBALL}.sig" "${QEMU_TARBALL}"

RUN # untar, configure, and build QEMU
RUN tar xvJf qemu-${QEMU_VERSION}.tar.xz
# We only need to build arm-softmmu
RUN qemu-${QEMU_VERSION}/configure --static --target-list=arm-softmmu
# -j option with nproc lets us build QEMU with all of our processors
RUN make -j$(nproc)

RUN # Strip the binary to reduce size
RUN strip "arm-softmmu/qemu-system-arm"



#--
# Step 3: Load kernel for board and emulate board
#--

# For now, get hex file to run on the emulated mps-an500
COPY hex/* .
# maybe later, write a shell script that prompts the user for an image or a kernel or device file


# send output about machine startup to user's stdout

# expose QEMU monitor so that the user can poke around their running machine
EXPOSE 7001

RUN ls

RUN # launch machine
# after this works, make the copy instruction from earlier copy an entire folder and then direct the file option in devices to the new folder
RUN ./qemu-system-arm -M mps2-an500 -m 16M -no-reboot -nographic -cpu cortex-m7 -device loader,file=/var/qemu/Blinky.hex -monitor telnet:localhost:1234,server,nowait
