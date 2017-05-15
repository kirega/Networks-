#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <sys/types.h>

// create socket, bind,recvfrom/sendto

int size;
float determinant(float matrix[size][size],int size);

int main(int argc, char *argv[])
{
	int socket_desc,client_size;
	struct sockaddr_in server,client;
	int i , j; //counters	
	float result;

	client_size= sizeof(client);
	// create the udp socket
	socket_desc=socket(AF_INET,SOCK_DGRAM,0);
	if (socket_desc == -1) printf("Could not create socket\n");

	// prepare the socaddr_in structure for the server
	server.sin_family= AF_INET;
	server.sin_addr.s_addr= INADDR_ANY;
	server.sin_port=htons(6760);

	// bind
	if (bind(socket_desc,(struct sockaddr *)&server,sizeof(server))<0){
		printf("Could not bind\n");
		return 1;
	}
	printf("Bind Success!\n");

	// receive the order of the matrix
	if(recvfrom(socket_desc,&size,sizeof(size),0,(struct sockaddr*)&client,&client_size)<0){
		printf("Size not recieved\n");
		return 1;
	};
	printf("The order of the matrix received : %d\n",size);
	
	// allocate the size of the matrix based on what the client chooses
	float matrix[size][size]; 
	// receive the matrix
	if(recvfrom(socket_desc,&matrix,sizeof(matrix),0,(struct sockaddr *)&client,&client_size)<0){
		printf("Matrix not received\n");
		return 1;
	}
	printf("The matrix is\n");
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			printf("%.2f\t",matrix[i][j]);
		}
		printf("\n");
	}
	result=determinant(matrix,size);

	// send the results to the client
	if(sendto(socket_desc,&result,sizeof(result),0,(struct sockaddr*)&client,client_size)<0){
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