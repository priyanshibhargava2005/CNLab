#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define WINDOW_SIZE 4    // Size of the window
#define TOTAL_PACKETS 10 // Total packets to send

int main()
{
    int base = 0;
    int next_seq_num = 0;

    // Seed for random number generation
    srand(time(0));

    while (base < TOTAL_PACKETS)
    {
        // Send packets within the window
        while (next_seq_num < base + WINDOW_SIZE && next_seq_num < TOTAL_PACKETS)
        {
            printf("Sending packet %d\n", next_seq_num);
            next_seq_num++;
        }

        // Simulate acknowledgment or packet loss
        bool ack_received = rand() % 2; // Randomly decide if ACK is received (0 or 1)
        if (ack_received)
        {
            printf("Acknowledgment received for packet %d\n", base);
            base++; // Move the window
        }
        else
        {
            printf("Packet %d lost. Resending from packet %d\n", base, base);
            next_seq_num = base; // Resend all packets from the base
        }
    }

    printf("All packets sent successfully!\n");
    return 0;
}
