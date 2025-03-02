#include <stdio.h>
#include <windows.h>
#include <tchar.h>
void main()
{
    char s[20];
    int a, b, c, sum;
    CharToOem(_T("¬ведите "), s);
    printf("%s a: ", s);
    scanf_s("%d", &a);
    printf("%s b: ", s);
    scanf_s("%d", &b);
    printf("%s c: ", s);
    scanf_s("%d", &c);
    _asm
    {
        mov eax, a;
        mov ebx, b;
        mov ecx, 4;
    m: add edx, c
        loop m
        sub edx, ebx;
        inc edx;

        push edx;
        imul ebx, eax;

        mov ecx, 2;
        mov eax, c;
        cdq;
        idiv ecx; //т.к дл€ делени€ используетс€ edx:eax

        add eax, ebx;

        pop ebx;
        cdq;
        idiv ebx;
        mov sum, eax;
    }
    //(b*a+c/2)/(4*c-b+1)
    //printf("sum: %d", sum);
    printf("\n (%d * %d + %d/2)/(4 * %d - %d + 1)= %d", b, a, c, c, b, sum);
    getchar(); getchar();
}