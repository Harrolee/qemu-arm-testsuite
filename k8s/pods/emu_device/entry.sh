#!/bin/bash
# Called on container startup

FRONTEND_IP='127.0.0.1:8000'

# we need to backslash in a second set of quotes
    # when we return a string in python, python returns the repr() value for the string object that we return. This encloses the characters in quotes
#if [ $filename == "\"no-file\"" ]; then
#    echo "they're equal"
#fi

# Curl FrontEnd until we get a "ready" response
filename=$(curl "$FRONTEND_IP/are-we-ready/")
until [ $filename != "\"no-file\"" ]; do
    echo "sleeping"
    sleep 5s
    filename=$(curl "$FRONTEND_IP/are-we-ready/")
done
# echo $filename
# when we get a response, wget or curl dl the .hex
# name the downloaded binary "code"
echo "$FRONTEND_IP/get-code/$filename"

# download the .hex that we will load on the emulated device
curl -o code.hex "$FRONTEND_IP/get-code/$filename"

# start the machine with recieved file

# we should be in the /var/qemu/ directory. In case we're not, we'll use the full path for the qemu command:
./var/qemu/qemu-system-arm -M mps2-an500 -m 16M -no-reboot -nographic -cpu cortex-m7 -device loader,file=/var/qemu/code.hex -monitor telnet:localhost:1234,server,nowait