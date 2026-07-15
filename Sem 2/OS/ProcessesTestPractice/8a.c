#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv){
    int a2b, b2a;
    a2b = open("8a2b", O_WRONLY);
    b2a = open("8b2a", O_RDONLY);
    (void)b2a;

    int n = argc - 1, length = 0;
    write(a2b, &n, sizeof(int));
    for(int i = 1; i <= n; ++i){
        int len = strlen(argv[i]);
        write(a2b, &len, sizeof(int));
        write(a2b, argv[i], len * sizeof(char));

        length += len;
    }

    char* s = malloc((length + 1) * sizeof(char));
    s[0] = '\0';
    for(int i = 1; i <= n; ++i){
        int len;
        read(b2a, &len, sizeof(int));
        char* t = malloc((len + 1) * sizeof(char));
        read(b2a, t, len * sizeof(char));

        strcat(s, t);
        free(t);
    }

    printf("%s\n", s);
    free(s);

    return 0;
}
