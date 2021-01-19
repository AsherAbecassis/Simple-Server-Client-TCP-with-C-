

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <iostream>


#define PORT 8080 

int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buf[1024] = {0}; 
    
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)))
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    
    if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0)                           
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0) 
                        
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 

   

    
    
    while (true)
    {
        memset(buf,0,1024);
        int tobyte=recv(new_socket,buf,1024,0);
        if(tobyte==-1)
        {
            std::cout<<"could not send to Client"<<std::endl;
            break;
        }
        if(tobyte==0)
        {
            std::cout<<"0 msg"<<std::endl;
            break;
        }


        std::string ans= std::string(buf,0,tobyte);
        if(ans=="ok")
        {
            
            
            std::cout<< "Recive frome Client: "<<std::string(buf,0,tobyte)<<std::endl;
            send(new_socket,buf,tobyte+1,0);

        }
        const char * err="Your syntax is invalid please type agen! (plese type ok..) ";

        send(new_socket,err,strlen(err),0);
        

        




    }
    close(new_socket);
    
    

    
    return 0; 
} 
