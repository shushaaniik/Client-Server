# Stage 1: Build stage
FROM gcc:latest AS builder

WORKDIR /app

COPY server ./server
COPY include ./include
COPY src ./src

RUN apt-get update && apt-get install -y cmake

RUN mkdir build && cd build && cmake ../server && make

# Stage 2: Final stage
FROM gcc:latest

WORKDIR /app/server

COPY --from=builder /app/build/server ./server

EXPOSE 8080

CMD ["./server", "1984"]

