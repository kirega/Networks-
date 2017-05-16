#include <stdio.h>
#include <string.h>    
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <unistd.h>    
#include <string.h>
// create socket, connect, recvfrom/sendto


int main(int argc, char *argv[])
{
	int sock,server_size,size,i=0,j=0,portno;
	struct sockaddr_in server;
	float result;
	char temp[20];

	server_size=sizeof(server);
	if (argc < 2) {
       fprintf(stderr,"usage %s port\n", argv[0]);
       exit(0);
    }
	portno=atoi(argv[1]);
	
	// create the socket
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if (sock == -1) printf("Could not create socket\n");
	printf("Client socket created \n");

	// set the sock_addr properties
	server.sin_family= AF_INET;
	server.sin_addr.s_addr= inet_addr("127.0.0.1");
	server.sin_port=htons(portno);

	
	// accept the user data for the matrix	
	printf("Enter the order of the matrix\n");
	scanf("%d",&size);	
	// initialize the size of the matrix
	float matrix[size][size];

	printf("Enter the matrix\n");
	for(i=0;i<size ;i++){
		for(j=0;j<size;j++){
			printf("matrix[%d][%d] : ",i,j);
			scanf("%f",&matrix[i][j]);
		}
	}
	//print out the matrix
	printf("The matrix is \n");
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			printf("%.2f\t",matrix[i][j]);
		}
		printf("\n");
	}

	// send the size of the matrix
	if (sendto(sock,&size,sizeof(size),0,(struct sockaddr *)&server,server_size)<0){
		printf("Sending size to Server failed\n");
		return 1;
	} 	
	//send to the matrix to the server 
	if (sendto(sock,&matrix,sizeof(matrix),0,(struct sockaddr *)&server,server_size)<0){
		printf("Sending matrix to Server failed\n");
		return 1;
	}
	// receive the determinant from the server side 
	if(recvfrom(sock,&result,sizeof(result),0,(struct sockaddr *)&server,&server_size)<0){
		printf("Matrix not received\n");
		return 1;
	} 
	printf("The determinant of the matrix is : %.2f \n",result);
	close(sock);
	return 0;			
}
