#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string>
#include <string.h>
#include <math.h>
#include<iostream>
#include <time.h> 
#include <sys/time.h>
#include <inttypes.h>

// TCP/IP Comm stuff
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT 18002 
#define MAXLINE 1024 
#define _POSIX_C_SOURCE 200809L

// http://192.168.2.1/ is the router ip address
// 192.168.2.3	NAVID-SUPER-SERVER

using namespace std; 
typedef struct
{
  //The 6 double values to be sent represent the following signals:
  double q1; 
  double q2; 
  double q3; 
  double q4; 
  double q5; 
  double q6; 
 
} KinovaMsgData_rec;

typedef struct
{
  //The 6 double values to be sent represent the following signals:
  double q1 = -10*(M_PI/180); 
  double q2 = -154*(M_PI/180);
  double q3 = -193*(M_PI/180);
  double q4 = -170*(M_PI/180);
  double q5 = 86*(M_PI/180);
  double q6 = -95*(M_PI/180);
 
} KinovaMsgData_send;

long current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}

int receive_robot_packet(int udp_socket, KinovaMsgData_rec* data_rec, struct sockaddr_in* cliaddr)
{

  socklen_t sock_addr_size_rec = sizeof(struct sockaddr_in);
  return recvfrom(udp_socket, (char *) data_rec, sizeof(KinovaMsgData_rec), 0, (struct sockaddr *) cliaddr, &sock_addr_size_rec);
}

int send_robot_packet(int udp_socket, KinovaMsgData_send* data_send, struct sockaddr_in* cliaddr)
{

  socklen_t sock_addr_size_snd = sizeof(struct sockaddr_in);
  return sendto(udp_socket, (const char *) data_send, sizeof(KinovaMsgData_send), 0, (const struct sockaddr *) cliaddr, sock_addr_size_snd); 
}

int main() { 
    int udp_socket; 
    struct sockaddr_in servaddr, cliaddr; 
    std::string kinova_ip_address = "192.168.2.2";
    long milliseconds;
   
    cout << "Creating socket..." << endl; 
    // Creating socket 
    if ( (udp_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { // change SOCK_DGRAM to SOCK_STREAM for TCP
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    cout << "socket creation successfull..." << endl; 

    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
          
    // server information 
    servaddr.sin_family = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 

    // Setup remote address
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_addr.s_addr = inet_addr(kinova_ip_address.c_str());
    cliaddr.sin_port = htons(PORT);
          // close(udp_socket);

    // Bind the socket 
    if ( bind(udp_socket, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) 
    { 
        close(udp_socket);
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    int received = -1;
    int sent = -1;
    int counter = 0;
    KinovaMsgData_rec kinova_data_rec;
    KinovaMsgData_send kinova_data_sent;
    memset((void*)(& kinova_data_rec),0x0,sizeof(kinova_data_rec));

    while (1)
    {
      // cout << "Please enter an angle: ";
      // cin >> kinova_data_sent.q1;
      printf("Time: %ld ", current_timestamp());
      kinova_data_sent.q1 = current_timestamp();
      sent =  send_robot_packet(udp_socket, &kinova_data_sent, &cliaddr);
      // cout << "sent= " << kinova_data_sent.q1 << " ";
      if (received =  receive_robot_packet(udp_socket, &kinova_data_rec, &cliaddr) > 0)
      {
        cout << "q1= " << kinova_data_rec.q1 << " ";
        cout << "q2= " << kinova_data_rec.q2 << " ";
        cout << "q3= " << kinova_data_rec.q3 << " ";
        cout << "q4= " << kinova_data_rec.q4 << " ";
        cout << "q5= " << kinova_data_rec.q5 << " ";
        cout << "q6= " << kinova_data_rec.q6 << endl;
      } 
      else
      {
        printf("Failed recieving..!\n");
        printf("Stream ended\n");
        close(udp_socket);
        exit(0); 
      }   
    }
    
    close(udp_socket);
    return 0; 
} 