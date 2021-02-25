# docs: https://hub.docker.com/r/midnighter/fastapi-base
# FROM midnighter/fastapi-base:3.8-alpine3.12_2021-01-19_3ea5769
FROM midnighter/fastapi-base:3.8-slim-buster_2021-02-23_c13e0e7

# might not need to install this this:

RUN python3 -m pip install python-multipart 
#RUN python3 -m pip install gunicorn wheel
RUN python3 -m pip install uvloop
RUN python3 -m pip install httptools
RUN python3 -m pip install paho-mqtt

RUN mkdir /fastapi
WORKDIR /fastapi
COPY . .

EXPOSE 8000

RUN uvicorn web_server:app