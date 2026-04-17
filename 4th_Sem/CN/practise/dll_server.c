#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_PKT_SIZE 100

typedef struct {
    char data[MAX_PKT_SIZE];
} Packet;

typedef struct {
    Packet payload;
} Frame;

typedef enum { frame_arrival, no_event } event_type;

int new_socket; // Global client socket

// -------- Function Prototypes --------
void receiver(void);
void WaitForEvent(event_type *event);
void ReceiveFrame(Frame *f);
Packet ExtractData(Frame f);
void DeliverData(Packet p);

// -------- Main --------
int main() {

    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    listen(server_fd, 3);
    printf("Server waiting for connection...\n");

    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Client connected.\n\n");

    receiver();

    close(new_socket);
    close(server_fd);

    return 0;
}

// -------- Receiver Implementation --------
void receiver(void) {
    Packet buffer;
    Frame r;
    event_type event;

    WaitForEvent(&event);

    if (event == frame_arrival) {
        ReceiveFrame(&r);
        buffer = ExtractData(r);
        DeliverData(buffer);
    }
}

void ReceiveFrame(Frame *f) {
    read(new_socket, f, sizeof(Frame));
    printf("Frame received from client.\n");
}

Packet ExtractData(Frame f) {
    printf("Extracting packet from frame...\n");
    return f.payload;
}

void DeliverData(Packet p) {
    printf("DATA DELIVERED: %s\n", p.data);
}

void WaitForEvent(event_type *event) {
    *event = frame_arrival;
}
