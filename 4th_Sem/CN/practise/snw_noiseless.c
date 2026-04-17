
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PKT_SIZE 100

typedef struct
{
    char data[MAX_PKT_SIZE];
} Packet;

typedef struct
{
    Packet payload;
    int seq;  // sequence number (0 or 1)
    bool ack; // true if ACK frame
} Frame;

typedef enum
{
    frame_arrival,
    no_event
} event_type;

// Global variable to simulate the physical medium/channel
Frame shared_channel;

// --- Functional Prototypes ---
void sender(void);
void receiver(void);

// Helper functions
void WaitForEvent(event_type *event);
void GetData(Packet *p);
Frame MakeDataFrame(Packet p, int seq);
Frame MakeAckFrame(int seq);
void SendFrame(Frame f);
void ReceiveFrame(Frame *f);
Packet ExtractData(Frame f);
void DeliverData(Packet p);

// --- Main Execution ---
int main()
{
    int n = 0;
    printf("\n--- Stop-and-Wait Protocol (Noiseless Channel) ---\n\n");
    while (n != 5)
    {
        sender();   // Sender sends frame
        receiver(); // Receiver receives and sends ACK
        sender();   // Sender receives ACK
        n++;
    }
    return 0;
}

int sender_seq = 0; // sequence number (0 or 1)

// --- Sender Implementation ---
void sender(void)
{
    static int state = 0; // 0 = send data, 1 = wait for ACK
    Packet buffer;
    Frame s, r;
    event_type event;

    if (state == 0) // SEND DATA
    {
        GetData(&buffer);
        s = MakeDataFrame(buffer, sender_seq);
        SendFrame(s);
        state = 1; // now wait for ACK
    }
    else // WAIT FOR ACK
    {
        WaitForEvent(&event);
        if (event == frame_arrival)
        {
            ReceiveFrame(&r);
            if (r.ack && r.seq == sender_seq)
            {
                printf("[Sender] ACK %d received.\n", r.seq);
                sender_seq++; // toggle 0 ↔ 1
                state = 0;    // ready to send next data
            }
        }
    }
}

Frame MakeDataFrame(Packet p, int seq)
{
    Frame f;
    f.payload = p;
    f.seq = seq;
    f.ack = false;
    printf("[Sender] Data Frame %d created.\n", seq);
    return f;
}

Frame MakeAckFrame(int seq)
{
    Frame f;
    f.seq = seq;
    f.ack = true;
    printf("[Receiver] ACK Frame %d created.\n", seq);
    return f;
}

void GetData(Packet *p)
{
    printf("Enter message to send: ");
    fgets(p->data, MAX_PKT_SIZE, stdin);
    p->data[strcspn(p->data, "\n")] = 0;
}

void SendFrame(Frame f)
{
    shared_channel = f;
    if (f.ack)
        printf("ACK %d sent to channel.\n", f.seq);
    else
        printf("Data Frame %d sent to channel.\n", f.seq);
}

// --- Receiver Implementation ---
void receiver(void)
{
    Frame r, ack_frame;
    Packet buffer;
    event_type event;
    static int expected_seq = 0;

    WaitForEvent(&event);

    if (event == frame_arrival)
    {
        ReceiveFrame(&r);

        if (!r.ack && r.seq == expected_seq)
        {
            buffer = ExtractData(r);
            DeliverData(buffer);

            ack_frame = MakeAckFrame(expected_seq);
            SendFrame(ack_frame);

            expected_seq++; // toggle
        }
    }
}

void ReceiveFrame(Frame *f)
{
    *f = shared_channel;
    printf("Frame received from channel.\n");
}

Packet ExtractData(Frame f)
{
    printf("Extracting packet from Frame %d...\n", f.seq);
    return f.payload;
}

void DeliverData(Packet p)
{
    printf("DATA DELIVERED TO NETWORK LAYER: %s\n", p.data);
}

void WaitForEvent(event_type *event)
{
    *event = frame_arrival; // always arrives (noiseless)
}
