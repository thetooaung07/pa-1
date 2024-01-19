#include <stdio.h>
#include <stdlib.h>

int rec(int x) {
    if (x == 0) { return 0; }
    return rec(x < 0 ? x + 1 : x - 1) - 1;

}


int main() {

    int count = 0;
    for (int i = 1; i <= 4454; i += i) {
        for (int j = 0; j < i; ++j) {
            count++;
        }
    }
    printf("count %d", count);
    printf("%d", rec(133));

    return 0;
}