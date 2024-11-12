#include <stdio.h>

#define BUCKET_SIZE 10 // Maximum capacity of the bucket
#define OUTPUT_RATE 4  // Rate at which packets are sent out of the bucket

// Function to simulate the leaky bucket algorithm
void leaky_bucket(int packets[], int n)
{
    int bucket_content = 0; // Tracks the current amount of data in the bucket

    // Loop through each incoming packet
    for (int i = 0; i < n; i++)
    {
        printf("Packet %d arrived with %d packets\n", i + 1, packets[i]);

        // Check if the bucket can accommodate the incoming packet without overflow
        if (packets[i] + bucket_content > BUCKET_SIZE)
        {
            // If overflow occurs, calculate and report the dropped packets
            printf("Bucket overflow! %d packets dropped\n", (packets[i] + bucket_content) - BUCKET_SIZE);
            bucket_content = BUCKET_SIZE; // Fill the bucket to maximum capacity
        }
        else
        {
            // If no overflow, add the incoming packet size to the bucket
            bucket_content += packets[i];
        }

        // Transmit packets at the defined output rate
        printf("Transmitting %d packets\n", (bucket_content < OUTPUT_RATE) ? bucket_content : OUTPUT_RATE);
        bucket_content -= (bucket_content < OUTPUT_RATE) ? bucket_content : OUTPUT_RATE;

        // Display the remaining packets in the bucket after transmission
        printf("Packets remaining in bucket: %d\n\n", bucket_content);
    }

    // After processing all packets, drain any remaining packets in the bucket
    while (bucket_content > 0)
    {
        // Transmit the remaining packets at the output rate or less if fewer packets remain
        printf("Transmitting %d packets\n", (bucket_content < OUTPUT_RATE) ? bucket_content : OUTPUT_RATE);
        bucket_content -= (bucket_content < OUTPUT_RATE) ? bucket_content : OUTPUT_RATE;

        // Display the remaining packets in the bucket
        printf("Packets remaining in bucket: %d\n", bucket_content);
    }

    // Print a message indicating all packets have been transmitted
    printf("All packets transmitted successfully!\n");
}

int main()
{
    int packets[] = {5, 3, 8, 2, 6};              // Array representing incoming packet sizes at each interval
    int n = sizeof(packets) / sizeof(packets[0]); // Calculate the number of packets

    // Run the leaky bucket algorithm on the array of packets
    leaky_bucket(packets, n);

    return 0;
}
