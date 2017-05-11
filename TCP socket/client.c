#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write

// create socket, connect, recv/send


int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in server;
	int size,i,j;
	float result;

	// create the socket
	sock=socket(AF_INET,SOCK_STREAM,0);
	if (sock == -1) printf("Could not create socket\n");
	printf("Client socket created \n");

	// set the sock_addr properties
	server.sin_family= AF_INET;
	server.sin_addr.s_addr= inet_addr("127.0.0.1");
	server.sin_port=htons(6760);

	// connect to a remote server
	if (connect(sock,(struct sockaddr *)&server,sizeof(server))<0){
		perror("Connecting to the sever failed\n");
		return 1;
	}	
	printf("Connection successful!\n");
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
			printf("%f\t",matrix[i][j]);
		}
		printf("\n");
	}

	// send the size of the matrix
	if (send(sock,&size,sizeof(size),0)<0){
		printf("Sending size to Server failed\n");
		return 1;
	} 	
	//send to the matrix to the server 
	if (send(sock,&matrix,sizeof(matrix),0)<0){
		printf("Sending matrix to Server failed\n");
		return 1;
	}
	// receive the determinant from the server side 
	if(recv(sock,&result,sizeof(result),0)<0){
		printf("Matrix not received\n");
		return 1;
	} 
	printf("The determinant of the matrix is : %.2f \n",result);
	close(sock);
	return 0;			
}
