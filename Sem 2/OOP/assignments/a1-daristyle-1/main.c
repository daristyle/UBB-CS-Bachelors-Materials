#include <stdio.h>
#include <stdlib.h>

void print_menu(){
    /*
     * Prints the menu
     */
    printf("====MAIN MENU====\n");
    printf("1.Generate primes\n");
    printf("2.Read an array\n");
    printf("3.Longest increasing substring such that the sum of any 2 consecutive elements is prime\n");
    printf("0.Exit\n");
}

int* generate_primes(int n, int *count){
    /*
     * Generates all the prime numbers less than n and modifies the memory address at count to contain the number of
     * primes less than n
     * Returns a pointer to the beginning of an array containing those primes
     */
    char* sieve = malloc(n * sizeof(char));
    sieve[0] = sieve[1] = 0;
    sieve[2] = 1;
    for(int i = 4; i < n; i += 2){
        sieve[i] = 0;
    }
    for(int i = 3; i < n; i += 2){
        sieve[i] = 1;
    }
    for(int i = 3; i * i < n; i += 2){
        if(sieve[i]){
            for(int j = i * i; j < n; j += i * 2){
                sieve[j] = 0;
            }
        }
    }

    int m = 0;
    for(int i = 0; i < n; ++i){
        m += sieve[i];
    }
    *count = m;

    int* primes = malloc(m * sizeof(int));
    m = 0;
    for(int i = 0; i < n; ++i){
        if(sieve[i]){
            primes[m++] = i;
        }
    }

    free(sieve);

    return primes;

}

void print_array(int* arr, int n){
    /*
     * Prints in the console the array arr, which has n elements
     */
    for(int i = 0; i < n; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int* read_array(int* n){
    /*
     * Reads from the keyboard an array of elements, modifies the memory location at n to contain the length of th array
     * Returns a pointer to the first element of the array read
     */
    printf("Enter the size of the array: ");
    scanf("%d", n);
    printf("Enter the elements of the array: ");
    int *arr = malloc(*n * sizeof(int));
    for(int i = 0; i < *n; ++i){
        scanf("%d", &arr[i]);
    }

    return arr;
}

int is_prime(int n){
    /*
     * Returns 0 if n is not prime and a value different from 0 if n is prime
     */
    if(n <= 3){
        return n >= 2;
    }
    if(n % 2 == 0 || n % 3 == 0){
        return 0;
    }

    for(int d = 5; d * d <= n; d += 6){
        if(n % d == 0 || n % (d + 2) == 0){
            return 0;
        }
    }

    return 1;
}

int* longest_substring(int *arr, int n, int *len){
    /*
     * Finds the longest increasing contiguous subsequence, such the sum of that any 2 consecutive elements is a prime number
     * Returns a pointer at the beginning of that substring and modifies the memory location at len to contain the length
     * of the substring found
     */
    int start = 0, end, *ans;
    *len = -1;
    for(int i = 1; i < n; ++i){
        if(arr[i] < arr[i - 1] || !is_prime(arr[i - 1] + arr[i])){
            end = i - 1;
            int length = end - start + 1;
            if(length > *len){
                *len = length;
                ans = (arr + start);
            }
            start = i;
        }
    }

    end = n - 1;
    int length = end - start + 1;
    if(length > *len){
        *len = length;
        ans = (arr + start);
    }

    return ans;
}

int main(){
    int n, m;
    int *arr;
    char exited = 0, command, array_read = 0;

    while(!exited){
        print_menu();
        printf("Enter your command: ");
        scanf(" %c", &command);
        if(command == '1'){
            printf("Enter the upperbound of primes: ");
            scanf("%d", &m);

            int num;
            int *primes = generate_primes(m, &num);
            print_array(primes, num);

            free(primes);
        }else if(command == '2'){
            arr = read_array(&n);
            array_read = 1;
        }else if(command == '3'){
            if(!array_read){
                printf("Array not read yet!\n");
            }else{
                int *substring = longest_substring(arr, n, &m);
                print_array(substring, m);
            }
        }else if(command == '0'){
            exited = 1;
        }else{
            printf("Invalid command!\n");
        }
    }


    return 0;
}