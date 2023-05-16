FROM gcc:latest

WORKDIR /app

COPY server ./server
COPY include ./include
COPY src ./src

RUN apt-get update && apt-get install -y cmake

RUN mkdir build && cd build && cmake ../server && make

WORKDIR /app/server

EXPOSE 8080

CMD ["./server", "1984"]

