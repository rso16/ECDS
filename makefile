OBJS = bin/main.o bin/Server.o bin/MysqlHandler.o bin/node.o bin/ECDH.o bin/CurlHandler.o
CC = gcc
CFLAGS = -std=c++11 -Wall -c -I/usr/include/mysql -I/src/
LFLAGS = -Wall -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -lrt -latomic -ldl -lcurl -ljsoncpp -lstdc++
NAME = bin/server


all: $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LFLAGS)  
run: all
	sudo $(NAME) "localhost" "666"
clean : 
	\rm bin/*.o $(NAME)
bin/main.o : src/main.cpp src/main.h src/Server/Server.h src/MysqlHandler/MysqlHandler.h src/ECDH/ECDH.h src/CurlHandler/CurlHandler.h
	$(CC) $(CFLAGS) src/main.cpp -o bin/main.o
bin/Server.o : src/Server/Server.cpp src/Server/Server.h   
	$(CC) $(CFLAGS) src/Server/Server.cpp -o bin/Server.o
bin/MysqlHandler.o : src/MysqlHandler/MysqlHandler.cpp src/MysqlHandler/MysqlHandler.h src/node/node.h
	$(CC) $(CFLAGS) src/MysqlHandler/MysqlHandler.cpp -o bin/MysqlHandler.o
bin/node.o : src/node/node.c src/node/node.h  
	$(CC) $(CFLAGS) src/node/node.c -o bin/node.o
bin/ECDH.o : src/ECDH/ECDH.cpp src/ECDH/ECDH.h src/node/node.h src/MysqlHandler/MysqlHandler.h  
	$(CC) $(CFLAGS) src/ECDH/ECDH.cpp -o bin/ECDH.o
bin/CurlHandler.o : src/CurlHandler/CurlHandler.cpp src/CurlHandler/CurlHandler.h 
	$(CC) $(CFLAGS) src/CurlHandler/CurlHandler.cpp -o bin/CurlHandler.o

