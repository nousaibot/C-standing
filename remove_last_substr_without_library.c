#include <stdio.h>

void rem_occur(char str[], const char sub[]) {
   int str_len = 0, sub_len = 0;
   
   while (str[str_len] != '\0') {
      str_len++;
   }
   
   while (sub[sub_len] != '\0') {
      sub_len++;
   }

int found_index = -1;
for (int i = 0; i <= str_len - sub_len; i++) {
   int j;
   for (j = 0; j < sub_len; j++) {
      if (str[i + j] != sub[j]) {
        break;
      }
    }
    if (j == sub_len) {
        found_index = i;
     }
}

if (found_index != -1) {
   for (int i = found_index; i < str_len - sub_len; i++) {
   str[i] = str[i + sub_len];
   }
   str[str_len - sub_len] = '\0';
   }
}

int main() {
char str[100];
char sub[100];
int str_index = 0, sub_index = 0;
char ch, ch2;


while(scanf("%c", &ch) ==1 && ch != '\n'){
    if(ch == '\n') str[str_index] == '\0';
    str[str_index] = ch;
    str_index++;
    
}

while(scanf("%c", &ch2) ==1 && ch2 != '\n'){
    if(ch2 == '\n') sub[sub_index] == '\0';
    sub[sub_index] = ch2;
    sub_index++;
    
}

rem_occur(str, sub);

printf("%s\n", str);

return 0;
}
