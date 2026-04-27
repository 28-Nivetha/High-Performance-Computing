#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define MAX_QUEUE 100
#define MAX_LINE 256

char* queue[MAX_QUEUE];
int front = 0, rear = 0;

int done_producers = 0;
int producer_count;

omp_lock_t lock;

// Insert into queue
void enqueue(char* line) {
    omp_set_lock(&lock);

    if ((rear + 1) % MAX_QUEUE != front) {
        queue[rear] = strdup(line);
        rear = (rear + 1) % MAX_QUEUE;
    }

    omp_unset_lock(&lock);
}

// Remove from queue
char* dequeue() {
    char* line = NULL;

    omp_set_lock(&lock);

    if (front != rear) {
        line = queue[front];
        front = (front + 1) % MAX_QUEUE;
    }

    omp_unset_lock(&lock);
    return line;
}

// Tokenize and print words
void process_line(char* line) {
    char* token = strtok(line, " \t\n");
    while (token != NULL) {

        #pragma omp critical
        {
            printf("%s\n", token);
        }

        token = strtok(NULL, " \t\n");
    }
}

int main() {
    int thread_count;
    int i;

    printf("Enter number of threads: ");
    scanf("%d", &thread_count);

    printf("Enter number of producer threads: ");
    scanf("%d", &producer_count);

    omp_init_lock(&lock);

    #pragma omp parallel num_threads(thread_count)
    {
        int id = omp_get_thread_num();

        // PRODUCER THREADS
        if (id < producer_count) {
            char filename[20];
            sprintf(filename, "file%d.txt", id);

            FILE* fp = fopen(filename, "r");
            if (fp == NULL) {
                printf("Cannot open %s\n", filename);
            } else {
                char line[MAX_LINE];

                while (fgets(line, MAX_LINE, fp)) {
                    enqueue(line);
                }

                fclose(fp);
            }

            // Update producer completion
            #pragma omp atomic
            done_producers++;
        }

        // CONSUMER THREADS
        else {
            while (1) {
                char* line = dequeue();

                if (line != NULL) {
                    process_line(line);
                    free(line);
                } else {
                    int finished;

                    #pragma omp atomic read
                    finished = done_producers;

                    if (finished == producer_count)
                        break;
                }
            }
        }
    }

    omp_destroy_lock(&lock);

    return 0;
}
