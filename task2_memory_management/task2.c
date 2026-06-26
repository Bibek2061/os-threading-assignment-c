#include <stdio.h>

#define MAX_FRAMES 10

// This function displays the current pages stored in memory frames
void showFrames(int frames[], int frameCount)
{
    printf("Memory Frames: ");

    for (int i = 0; i < frameCount; i++)
    {
        if (frames[i] == -1)
        {
            printf("[empty] ");
        }
        else
        {
            printf("[%d] ", frames[i]);
        }
    }

    printf("\n");
}

// This function checks whether a page is already available in memory or not
int searchPage(int frames[], int frameCount, int page)
{
    for (int i = 0; i < frameCount; i++)
    {
        if (frames[i] == page)
        {
            return i;
        }
    }

    return -1;
}

// FIFO page replacement algorithm
void fifoAlgorithm(int pages[], int totalPages, int frameCount)
{
    int frames[MAX_FRAMES];
    int pageFaults = 0;
    int pageHits = 0;
    int nextFrame = 0;

    for (int i = 0; i < frameCount; i++)
    {
        frames[i] = -1;
    }

    printf("\n========== FIFO PAGE REPLACEMENT ==========\n");

    for (int i = 0; i < totalPages; i++)
    {
        int currentPage = pages[i];

        printf("\nRequested Page: %d\n", currentPage);

        if (searchPage(frames, frameCount, currentPage) != -1)
        {
            pageHits++;
            printf("Status: Page Hit\n");
        }
        else
        {
            pageFaults++;
            printf("Status: Page Fault\n");

            frames[nextFrame] = currentPage;
            nextFrame++;

            if (nextFrame == frameCount)
            {
                nextFrame = 0;
            }
        }

        showFrames(frames, frameCount);
    }

    printf("\nFIFO Result Summary\n");
    printf("Total Page Hits: %d\n", pageHits);
    printf("Total Page Faults: %d\n", pageFaults);
    printf("Hit Ratio: %.2f\n", (float)pageHits / totalPages);
    printf("Miss Ratio: %.2f\n", (float)pageFaults / totalPages);
}

// LRU page replacement algorithm
void lruAlgorithm(int pages[], int totalPages, int frameCount)
{
    int frames[MAX_FRAMES];
    int lastUsed[MAX_FRAMES];

    int pageFaults = 0;
    int pageHits = 0;
    int time = 0;

    for (int i = 0; i < frameCount; i++)
    {
        frames[i] = -1;
        lastUsed[i] = 0;
    }

    printf("\n========== LRU PAGE REPLACEMENT ==========\n");

    for (int i = 0; i < totalPages; i++)
    {
        int currentPage = pages[i];
        time++;

        printf("\nRequested Page: %d\n", currentPage);

        int foundIndex = searchPage(frames, frameCount, currentPage);

        if (foundIndex != -1)
        {
            pageHits++;
            lastUsed[foundIndex] = time;
            printf("Status: Page Hit\n");
        }
        else
        {
            pageFaults++;
            printf("Status: Page Fault\n");

            int replaceIndex = 0;

            for (int j = 0; j < frameCount; j++)
            {
                if (frames[j] == -1)
                {
                    replaceIndex = j;
                    break;
                }

                if (lastUsed[j] < lastUsed[replaceIndex])
                {
                    replaceIndex = j;
                }
            }

            frames[replaceIndex] = currentPage;
            lastUsed[replaceIndex] = time;
        }

        showFrames(frames, frameCount);
    }

    printf("\nLRU Result Summary\n");
    printf("Total Page Hits: %d\n", pageHits);
    printf("Total Page Faults: %d\n", pageFaults);
    printf("Hit Ratio: %.2f\n", (float)pageHits / totalPages);
    printf("Miss Ratio: %.2f\n", (float)pageFaults / totalPages);
}

int main()
{
    int pageSize = 4;      // page size in KB
    int frameCount = 3;    // number of available memory frames

    int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int totalPages = 12;

    printf("Task 2: Memory Management Simulation\n");
    printf("Page Size: %d KB\n", pageSize);
    printf("Number of Memory Frames: %d\n", frameCount);

    printf("\nPage Reference String: ");
    for (int i = 0; i < totalPages; i++)
    {
        printf("%d ", pages[i]);
    }
    printf("\n");


    fifoAlgorithm(pages, totalPages, frameCount);
    lruAlgorithm(pages, totalPages, frameCount);

    return 0;
}


