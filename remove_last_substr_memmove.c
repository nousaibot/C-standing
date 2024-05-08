#include <stdio.h>
#include <string.h>

void remove_last_occurrence(char *str, const char *sub) {
    char *ptr = strstr(str, sub);
    if (!ptr) {
        return;
    }
    
    char *next_ptr;
    while ((next_ptr = strstr(ptr + 1, sub)) != NULL) {
        ptr = next_ptr;
    }
    
    memmove(ptr, ptr + strlen(sub), strlen(ptr + strlen(sub)) + 1);
}

int main() {
    char str[100];
    char sub[100];
    
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0; // Remove the newline character
    
    fgets(sub, sizeof(sub), stdin);
    sub[strcspn(sub, "\n")] = 0; // Remove the newline character
    
    remove_last_occurrence(str, sub);
    
    printf("%s\n",str);
    
    return 0;
}
