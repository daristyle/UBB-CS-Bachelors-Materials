#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int, char**){
    int a2b, b2a;
    a2b = open("8a2b", O_RDONLY);
    b2a = open("8b2a", O_WRONLY);
    (void)b2a;
    int n;
    read(a2b, &n, sizeof(int));
    for(int i = 1; i <= n; ++i){
        int len = 0;
        read(a2b, &len, sizeof(int));
        printf("%d",len);
        char* s = malloc((len + 1) * sizeof(char));
        read(a2b, s, len * sizeof(char));
        for(int j = 0; j < len; ++j){
            if('a' <= s[j] && s[j] <= 'z'){
                s[j] += 'A' - 'a';
            }
        }

        write(b2a, &len, sizeof(int));
        write(b2a, s, len * sizeof(char));
        printf("%s\n", s);

        free(s);
    }

    return 0;
}
