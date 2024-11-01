#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    // Шаг 1: Создание каталогов
    if (mkdir("proj_1", 0755) == -1) handle_error("Failed to create proj_1");
    if (mkdir("proj_2", 0755) == -1) handle_error("Failed to create proj_2");
    if (mkdir("proj_3", 0755) == -1) handle_error("Failed to create proj_3");

    // Шаг 2: Создание файла name.txt и запись в него данных
    int fd_name = open("proj_1/name.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_name == -1) handle_error("Failed to open name.txt");

    const char *data = "Имя_Фамилия_группа\n";
    if (write(fd_name, data, strlen(data)) == -1) handle_error("Failed to write to name.txt");

    if (close(fd_name) == -1) handle_error("Failed to close name.txt");

    // Шаг 3: Создание пустого файла clear.txt
    int fd_clear = open("proj_2/clear.txt", O_CREAT | O_WRONLY, 0644);
    if (fd_clear == -1) handle_error("Failed to open clear.txt");

    if (close(fd_clear) == -1) handle_error("Failed to close clear.txt");

    // Шаг 4: Генерация и запись случайных данных в rand.bin
    int fd_rand = open("proj_3/rand.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_rand == -1) handle_error("Failed to open rand.bin");

    unsigned char random_data[500];
    srand(time(NULL)); // Инициализация генератора случайных чисел

    for (int i = 0; i < 500; i++) {
        random_data[i] = rand() % 256; // Генерация случайного байта
    }

    if (write(fd_rand, random_data, sizeof(random_data)) != sizeof(random_data)) {
        handle_error("Failed to write random data to rand.bin");
    }

    if (close(fd_rand) == -1) handle_error("Failed to close rand.bin");

    // Шаг 5: Создание файла head.bin размером 35 байт
    int fd_head = open("proj_3/head.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_head == -1) handle_error("Failed to open head.bin");

    if (ftruncate(fd_head, 35) == -1) handle_error("Failed to set size of head.bin");

    if (close(fd_head) == -1) handle_error("Failed to close head.bin");

    // Шаг 6: Создание жесткой ссылки namelink.txt на файл name.txt
    if (link("proj_1/name.txt", "proj_3/namelink.txt") == -1) {
        handle_error("Failed to create hard link namelink.txt");
    }

    // Шаг 7: Создание символической ссылки proj_2_link на каталог proj_2
    if (symlink("proj_2", "proj_2_link") == -1) {
        handle_error("Failed to create symbolic link proj_2_link");
    }

    printf("Все операции выполнены успешно.\n");
    
    return EXIT_SUCCESS;
}