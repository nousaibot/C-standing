#include <stdio.h>
#include <string.h>

char *remove_last_occurrence(char *str, const char *sub)
{
    char *last_occurrence = strstr(str, sub);
    
    if (last_occurrence) {
        char *next_occurrence = strstr(last_occurrence + 1, sub);
        
        while (next_occurrence) {
            last_occurrence = next_occurrence;
            next_occurrence = strstr(last_occurrence + 1, sub);
        }
        
        char *end_of_string = last_occurrence + strlen(sub);
        strcpy(last_occurrence, end_of_string);
    }
    
    return str;
}

int main()
{
    char str[100];
    char sub[100];
    
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0; // Remove the newline character
    
    printf("Enter the substring to remove: ");
    fgets(sub, sizeof(sub), stdin);
    sub[strcspn(sub, "\n")] = 0; // Remove the newline character
    
    char *result = remove_last_occurrence(str, sub);
    
    printf("String after removing last occurrence of '%s': %s\n", sub, result);
    
    return 0;
}
