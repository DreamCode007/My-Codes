#include <stdio.h>

void tow(int a, char s, char h, char d)
{
    
    if (a == 0 ) return;
    tow(a-1, s, d, h); // s is source ,h is hel prod , d is destination 
    printf("%c to %c\n", s, d);
    
    
    tow(a-1, h, s, d);
    
    return ;
}

int main() {
    int a;
    
    scanf("%d", &a);
    tow(a, 'A', 'B', 'C');
