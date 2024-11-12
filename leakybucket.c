#include <stdio.h>

#define BUCKET_SIZE 10 // Maximum capacity of the bucket
#define OUTPUT_RATE 4  // Rate at which packets are sent out of the bucket

void leaky_bucket(int packets[], int n)
{
    int bucket_content = 0;

    for (int i = 0; i < n; i++)
    {
        printf("Packet %d arrived with %d packets\n", i + 1, packets[i]);

        // Check if there is enough space in the bucket
        if (packets[i] + bucket_content > BUCKET_SIZE)
        {
            printf("Bucket overflow! %d packets dropped\n", (packets[i] + bucket_content) - BUCKET_SIZE);
            bucket_content = BUCKET_SIZE; // Fill bucket to maximum capacity
        }
        else
        {
            bucket_content += packets[i];
        }

        // Send packets at the output rate
        printf("Transmitting %d packets\n", (bucket_content < OUTPUT_RATE) ? bucket_content : OUTPUT_RATE);
        bucket_content -= (bucket_content < OUTPUT_RATE) ? bucket_content : OUTPUT_RATE;

        printf("Packets remaining in bucket: %d\n\n", bucket_content);
    }

    // Drain the remaining packets in the bucket after all packets have arrived
    while (bucket_content > 0)
    {
        printf("Transmitting %d packets\n", (bucket_content < OUTPUT_RATE) ? bucket_content : OUTPUT_RATE);
        bucket_content -= (bucket_content < OUTPUT_RATE) ? bucket_content : OUTPUT_RATE;
        printf("Packets remaining in bucket: %d\n", bucket_content);
    }

    printf("All packets transmitted successfully!\n");
}

int main()
{
    int packets[] = {5, 3, 8, 2, 6}; // Array representing incoming packet sizes
    int n = sizeof(packets) / sizeof(packets[0]);

    leaky_bucket(packets, n);

    return 0;
}
