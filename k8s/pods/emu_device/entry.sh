#!/bin/bash
# Called on container startup

# point to the name of the NodePort service in cluster
FRONTEND_IP='cmdhub_np'

# Curl FrontEnd until it is ready. It will respond with a a real filename when it is ready.
filename=$(wget -q -O - "$FRONTEND_IP/are-we-ready/")
until [ $filename != "\"no-file\"" ]; do
    echo "sleeping"
    sleep 5s
    filename=$(wget -q -O - "$FRONTEND_IP/are-we-ready/")
done

# download the .hex that we will load on the emulated device. Name it code.hex
wget -o code.hex "$FRONTEND_IP/get-code/$filename"

# start the machine with recieved file

# we should be in the /var/qemu/ directory. In case we're not, we'll use the full path for the qemu command:
# ./var/qemu/qemu-system-arm -M mps2-an500 -m 16M -no-reboot -nographic -cpu cortex-m7 -device loader,file=/var/qemu/code.hex -monitor telnet:localhost:1234,server,nowait
