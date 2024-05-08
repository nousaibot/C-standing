#include <stdio.h>
#include <string.h>

char *rem_sub(char *str, const char *sub)
{
    //Находим первое совпадение
    char *last_occur = strstr(str, sub);
    char *next_occur = strstr(last_occur + 1, sub);
        
    while (next_occur) {
    //Проверяем дополнительные совпадения в цикле, если совпадений нет вернется null
        last_occur = next_occur;
        next_occur = strstr(last_occur + 1, sub);
        }
    //Сдвигаемся на длинну подстроки с последнего совпадеиня   
    char *end_of_string = last_occur + strlen(sub);
    printf("---%s---\n", last_occur);
    //Заменяем последнее сопадение строки до конца на подстраку без последнего совпадения
    strcpy(last_occur, end_of_string);
    
    return str;
}

int main()
{
    char str[100];
    char sub[100];
    //Считываем строку
    fgets(str, sizeof(str), stdin);
    //Добавляем символ конца строки
    str[strlen(str) -1] = '\0';
    
    //Считываем субстроку
    fgets(sub, sizeof(sub), stdin);
    //Добавляем символ конца строки
     sub[strlen(sub) -1] = '\0';
    
    //Вызываем функцию удаления подстроки и печатаем результат
    printf("%s", rem_sub(str, sub));
    
    return 0;
}
