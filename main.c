#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {

    int randfile = open("/dev/random", O_RDONLY);
    if (randfile == -1) 
    {
        printf("errno: %d\terror: %s\n", errno, strerror(errno));
        return 0;
    }

    printf("Generating random numbers:\n");
    int randos[10]; 
    int i;
    for (i = 0; i < 10; i++) 
    {
        int n = read(randfile, &randos[i], sizeof(randos[i]));
        if (n == -1)
        {
            printf("errno: %d\terror: %s\n", errno, strerror(errno));
            return 0; 
        }
        printf("\trandom %d: %d\n", i, randos[i]);
    }
    printf("\n");
    
    printf("Writing numbers to file...\n\n");
    int randout = open("randout.out", O_CREAT | O_WRONLY, 0644);
    if (randout == -1)
    {
        printf("errno: %d\terror: %s\n", errno, strerror(errno));
        return 0;
    }

    int k = write(randout, randos, sizeof(randos));
    if (k == -1)
    {
        printf("errno: %d\terror: %s\n", errno, strerror(errno));
            return 0; 
    }

    printf("Reading numbers from file...\n\n");
    int randfile2 = open("randout.out", O_RDONLY);
    if (randfile2 == -1) 
    {
        printf("errno: %d\terror: %s\n", errno, strerror(errno));
        return 0;
    }

    printf("Verification that written values were the same:\n\n");
    
    int randos2[10]; 
    for (i = 0; i < 10; i++) 
    {
        int n = read(randfile2, &randos2[i], sizeof(randos2[i]));
        if (n == -1)
        {
            printf("errno: %d\terror: %s\n", errno, strerror(errno));
            return 0; 
        }
        printf("\trandom %d: %d\n", i, randos2[i]);
    }

    return 0;
}
