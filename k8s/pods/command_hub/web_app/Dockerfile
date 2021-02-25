# docs: https://hub.docker.com/r/midnighter/fastapi-base

#--
# Step 1: Prepare Servers 
#--

# (1/2) FastAPI 
FROM midnighter/fastapi-base:3.8-slim-buster_2021-02-23_c13e0e7

RUN apt update -y && apt upgrade -y

RUN python3 -m pip install python-multipart 
RUN python3 -m pip install uvloop
RUN python3 -m pip install httptools
RUN python3 -m pip install paho-mqtt
RUN python3 -m pip install aiofiles
EXPOSE 8000

RUN mkdir -p /fastapi/code_to_emulate
RUN chmod 777 /fastapi/code_to_emulate/
RUN echo 'records' > /fastapi/code_to_emulate/apple.txt
WORKDIR /fastapi
COPY . .


#--
# Step 2: Start Servers
#--


CMD ["uvicorn", "web_server:app"]