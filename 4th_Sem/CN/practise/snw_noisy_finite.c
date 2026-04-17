#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PKT_SIZE 100
#define LOSS_PROBABILITY 30 // 30% chance frame lost

typedef struct {
    char data[MAX_PKT_SIZE];
} Packet;

typedef struct {
    Packet payload;
    int seq;
    bool ack;
} Frame;

typedef enum { frame_arrival, no_event } event_type;

Frame shared_channel;
bool frame_available = false;

void sender(void);
void receiver(void);

void WaitForEvent(event_type *event);
void GetData(Packet *p);
Frame MakeDataFrame(Packet p, int seq);
Frame MakeAckFrame(int seq);
void SendFrame(Frame f);
void ReceiveFrame(Frame *f);
Packet ExtractData(Frame f);
void DeliverData(Packet p);

int sender_seq = 0;

int main()
{
    srand(time(NULL));

    printf("\n--- Stop-and-Wait Protocol (Noisy Channel) ---\n\n");

    sender();
    receiver();
    sender();

    return 0;
}

void sender(void)
{
    static int state = 0;
    Packet buffer;
    Frame s, r;
    event_type event;

    if (state == 0)
    {
        GetData(&buffer);
        s = MakeDataFrame(buffer, sender_seq);
        SendFrame(s);
        state = 1;
    }
    else
    {
        WaitForEvent(&event);

        if (event == frame_arrival)
        {
            ReceiveFrame(&r);

            if (r.ack && r.seq == sender_seq)
            {
                printf("[Sender] ACK %d received\n", r.seq);
                sender_seq = 1 - sender_seq;
                state = 0;
            }
        }
        else
        {
            printf("[Sender] Timeout! Retransmitting frame %d\n", sender_seq);
            state = 0;
        }
    }
}

Frame MakeDataFrame(Packet p, int seq)
{
    Frame f;
    f.payload = p;
    f.seq = seq;
    f.ack = false;

    printf("[Sender] Data Frame %d created\n", seq);
    return f;
}

Frame MakeAckFrame(int seq)
{
    Frame f;
    f.seq = seq;
    f.ack = true;

    printf("[Receiver] ACK Frame %d created\n", seq);
    return f;
}

void GetData(Packet *p)
{
    printf("Enter message: ");
    fgets(p->data, MAX_PKT_SIZE, stdin);
    p->data[strcspn(p->data, "\n")] = 0;
}

void SendFrame(Frame f)
{
    int r = rand() % 100;

    if (r < LOSS_PROBABILITY)
    {
        printf("*** Frame LOST in channel ***\n");
        frame_available = false;
        return;
    }

    shared_channel = f;
    frame_available = true;

    if (f.ack)
        printf("ACK %d sent to channel\n", f.seq);
    else
        printf("Data Frame %d sent to channel\n", f.seq);
}

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

            expected_seq = 1 - expected_seq;
        }
    }
}

void ReceiveFrame(Frame *f)
{
    *f = shared_channel;
    printf("Frame received from channel\n");
}

Packet ExtractData(Frame f)
{
    printf("Extracting packet from frame %d\n", f.seq);
    return f.payload;
}

void DeliverData(Packet p)
{
    printf("DATA DELIVERED: %s\n", p.data);
}

void WaitForEvent(event_type *event)
{
    if (frame_available)
        *event = frame_arrival;
    else
        *event = no_event;
}
