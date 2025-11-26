//Name: Ayden Dauenhauer
//Date: Mar 10, 2025
//Title: Lab9 - File Performance Measurement
//Description: To evaluate file system performance in the face of sequential I/O requests,
//             mainly disk reads and writes and to evaluate the impact of multiple
//             competing threads attempting to read/write simultaneously

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    char *file_name;
    int buffer_size;
    int thread_id;
} thread_arg_t;

void *copy_file(void *arg) {
    thread_arg_t *thread = (thread_arg_t *) arg;
    char copy_file_name[256];
    snprintf(copy_file_name, sizeof(copy_file_name), "copy_%d.out", thread->thread_id);

    FILE *fp = fopen(thread->file_name, "rb");
    FILE *out = fopen(copy_file_name, "wb");

    char *buffer = malloc(thread->buffer_size);
    size_t n;
    while ((n = fread(buffer, 1, thread->buffer_size, fp)) > 0) {
        fwrite(buffer, 1, n, out);
    }

    fclose(fp);
    fclose(out);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int thread_count = atoi(argv[3]);
    int buffer_size = atoi(argv[2]);

    pthread_t *threads = malloc(thread_count * sizeof(pthread_t));
    thread_arg_t *args = malloc(thread_count * sizeof(thread_arg_t));

    for (int i = 0; i < thread_count; i++) {
        args[i].file_name = argv[1];
        args[i].buffer_size = buffer_size;
        args[i].thread_id = i;
        pthread_create(&threads[i], NULL, copy_file, &args[i]);
    }

    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}