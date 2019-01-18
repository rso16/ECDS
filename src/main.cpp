#include "main.h"


int main(int argc, const char* argv[]) {
    if(argc != 3){
        printf("Not enough arguments, please pass an IP and Port, example: ./server 127.0.0.1 80\n");
        exit(1);
    }
    char* ip_addr = (char *) argv[1];//(char *) "127.0.0.1";
    int port = atoi(argv[2]);
    server = Server(port, ip_addr);
    server.startup();

    while (true){
        server.connect();

        char* data = server.getData(); 

	printf("recieved = %s\n",data);
	char *MAC_Addr = eHandler.getMAC(data);
	printf("MAC address  = %s\n",MAC_Addr);
	char *roomIdStr = (char*) malloc(sizeof(char) * 10);
	roomIdStr = eHandler.getRoomId(MAC_Addr);
	//printf("Room Id   = %s\n", roomId); 	 
	int roomId = sscanf(roomIdStr, "%d", &roomId);	
	//server.sendData(cHandler.getLessonInfo(roomId));
	server.sendData(cHandler.getLessonInfo(roomId));

        server.disconnect();
    }
    return 0;
}
