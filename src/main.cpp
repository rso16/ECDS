#include "main.h"


int main(int argc, const char* argv[]) 
{
	
	//init server
	if(argc != 3)
	{
        	printf("Not enough arguments, please pass an IP and Port, example: ./server 127.0.0.1 80\n");
        	exit(1);
    	}
    
	char* ip_addr = (char *) argv[1];//(char *) "127.0.0.1";
	int port = atoi(argv[2]);
	server = Server(port, ip_addr);
	server.startup();

    	while (true)
	{
       		//wait for connection 
		server.connect();
		
		//get data
		char* data = server.getData(); 
		printf("recieved = %s\n",data);
		
		//get mac address
		uint64_t MAC_Addr = eHandler.getMAC(data);
		
		//get roomId
		int roomId = eHandler.getRoomId(MAC_Addr);
	
		if(roomId != NULL)
		{

			//get lesson info and send it
			server.sendData(cHandler.getLessonInfo(roomId));
		}
		else
		{
			//send error
			server.sendData("Error");
		}	
					
		
		//disconnnect 
		server.disconnect();
    	}
    	
	return 0;
}
