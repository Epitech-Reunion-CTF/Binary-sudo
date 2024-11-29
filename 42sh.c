#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>

void print_usage(const char *prog_name) {
    printf("Usage: %s [-a] [-b] [-c] [-d] [-e] [-f] [-g] [-h] [-i] [-j] [-p] [-x] [-y] [-z]\n", prog_name);
    printf("  -a  Enable advanced mode\n");
    printf("  -b  Enable background mode\n");
    printf("  -c  Launch the shell with color\n");
    printf("  -d  Enable debug mode\n");
    printf("  -e  Enable extended features\n");
    printf("  -f  Enable fast mode\n");
    printf("  -g  Enable graphical mode\n");
    printf("  -h  Display help\n");
    printf("  -i  Enable interactive mode\n");
    printf("  -j  Enable JSON output\n");
    printf("  -p  Launch the shell as the owner\n");
    printf("  -x  Enable experimental features\n");
    printf("  -y  Enable YAML output\n");
    printf("  -z  Enable zipping of output\n");
}

int main(int argc, char *argv[]) {
    int opt;
    int p_flag = 0;

    while ((opt = getopt(argc, argv, "abcdefghijpxyz")) != -1) {
        switch (opt) {
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'x':
            case 'y':
            case 'z':
                // These flags do nothing
                break;
            case 'p':
                p_flag = 1;
                break;
            default:
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    struct passwd *pw;
    if (p_flag) {
        pw = getpwnam("manu");
    } else {
        pw = getpwnam("www-data");
    }

    if (pw == NULL) {
        perror("getpwnam");
        exit(EXIT_FAILURE);
    }

    printf("Becoming user: %s\n", pw->pw_name);
    if (setuid(pw->pw_uid) != 0) {
        perror("setuid");
        exit(EXIT_FAILURE);
    }

    printf("Launching shell...\n");
    execl("/bin/sh", "sh", NULL);

    perror("execl");
    return EXIT_FAILURE;
}