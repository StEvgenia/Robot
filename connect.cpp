#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

void link_with_serv(char**argv)
{
	int fd, r;
	char name[]="MRBOT\n";
	char buf[1024];
	struct sockaddr_in addr;
	fd=socket(AF_INET, SOCK_STREAM,0);
	if(fd==-1){
		perror("Socket:");
		exit(1);
	}
	addr.sin_family=AF_INET;
	if(!inet_aton(argv[1], &(addr.sin_addr))){
		cout<<"Invalid IP\n";
		exit(1);
	}
	addr.sin_port=htons(atoi(argv[2]));
	if(-1==connect(fd, (struct sockaddr*)&addr, sizeof(addr))){
		perror("Error with connect:");
		exit(1);
	}
	write(fd, name, strlen(name));
	write(fd, "Prefectly!\n", 11);
	r=read(fd, buf, 1024);
	write(1, buf, r);
}
	
int main(int argc, char **argv)
{
	link_with_serv(argv);
	sleep(5);
	cout<<"Perfectly!";
	return 0;
}
