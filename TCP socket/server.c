#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write


// create socket, bind,listen, accept, recv/send
int size;
float determinant(float matrix[size][size],int size);

int main(int argc, char *argv[])
{
	int socket_desc,client_sock,connection,portno;
	struct sockaddr_in server,client;
	int i , j; //counters
	float result;

	if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
    }
 	portno=atoi(argv[1]);

	// create the socket
	socket_desc=socket(AF_INET,SOCK_STREAM,0);
	if (socket_desc == -1) printf("Could not create socket\n");

	// prepare the socaddr_in structure for the server
	server.sin_family= AF_INET;
	server.sin_addr.s_addr= INADDR_ANY;
	server.sin_port=htons(portno);

	// bind
	if (bind(socket_desc,(struct sockaddr *)&server,sizeof(server))<0){
		printf("Could not bind\n");
		return 1;
	}
	printf("Bind Success!\n");

	// listen
	listen(socket_desc,5);

	// accept incoming connections
	connection=sizeof(struct sockaddr_in);
	client_sock=accept(socket_desc,(struct sockaddr*)&client,(socklen_t *)&connection);
	if(client_sock<0){
		printf("Could not connect to Client: Accept failed!\n");
		return 1;
	}
	printf("Connection accepted\n");

	// receive the order of the matrix
	if(recv(client_sock,&size,sizeof(size),0)<0){
		printf("Size not recieved\n");
		return 1;
	};

	float matrix[size][size]; 

	// receive the matrix
	if(recv(client_sock,&matrix,sizeof(matrix),0)<0){
		printf("Matrix not recieved\n");
		return 1;
	}
	printf("The matrix is\n");
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			printf("%f\t",matrix[i][j]);
		}
		printf("\n");
	}
	result=determinant(matrix,size);

	// send the results to the client
	if(send(client_sock,&result,sizeof(result),0)<0){
		printf("Sending results to the client failed \n");
		return 1;
	}
	printf("the determinant is %.2f\n",result);
	close(socket_desc);
	return 0;
}

// these code utilizez the upper triangular method
float determinant(float matrix[size][size],int x)
{
	int i,j,k;
	float ratio,det;
	if(x==1){
		det=0;
		det=matrix[0][0];
		return det;
	}
	if(x == 2){
		det=0;
		det=(matrix[0][0]*matrix[1][1])-(matrix[0][1]*matrix[1][0]);
		return det;
	}
	else{
		    /* Conversion of matrix to upper triangular */
		    for(i = 0; i < x; i++){
		        for(j = 0; j < x; j++){
		            if(j>i){
		                ratio = matrix[j][i]/matrix[i][i];
		                for(k = 0; k < x; k++){
		                    matrix[j][k] -= ratio * matrix[i][k];
		                }
		            }
		        }
		    }
		    det = 1;
		    for(i=0 ; i< x;i++){
		    	det*=matrix[i][i];
	}
    return det;
	}
}