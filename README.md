# TCP client-server

## Requirements
Write two programs - the client and the server.
Server program should open and listen a TCP port N that is given via command-line arguments.
On every connection that server receives, the server should receive a 4-byte integer M as an input from the client.
After the input number is received from the client, the server should asynchronously handle the client connection as follows:
- compute M-th prime number,
- send calculated number to the client as an 8-byte number.
The server should not block other connections while processing one (every connection should be handled asynchronously).
- Option 1: use a separate thread to handle each connection (bad solution),
- Option 2: use thread pool to handle every incoming connection with queueing (not ideal, but preferred).
----
The client program should be able to connect to the IP and PORT of the server given with command-line arguments.
The client program is an infinite loop that waits the user to input number M, open a connection once number is entered, send to the server and print the result that server responded.
Once number is entered in the client program, the communication with server should also happen asynchronously and client should not wait while data is sent or result is retreived and should continue.
As in case of the server, client program should do the operations asynchronously (preferrably with thread pooling).
For the thread pool you can use one from previous homeworks or use any other library (including C++ standard library).
Every program should be in a separate folder, have its own Makefile.
Extra: For the highest score, you must write a Dockerfile and a docker-compose.yml file to run the server (only server) in a container. The Dockerfile should also take care of building the server automatically (google two-stage build in docker).


## Usage:

**From first terminal**
```
cd server
cmake -S . -B ./build
cd build
make
../server <port>
```

**From second terminal**
```
cd client
cmake -S . -B ./build
cd build
make
../client <ip> <port>
```

**The number of clients can be any**


## Dockerfile usage:
```
docker build -t server-container .
docker run -p 8080:8080 --name server server-container
```

**these command may require _sudo_ permission**

```
docker stop server
```


