#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <iostream>

using namespace std;

void main()
{
    char s[20];
    int a, b, c, sum;
    int error_zero = 0, error_over = 0;
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
    m: add edx, c //<edx>=4*c
        loop m
        sub edx, ebx; //<edx> = 4*<edx>-<ebx> = 4*c-b
        inc edx; //<edx> = 4*c-b+1

        push edx; //в стеке 4*с-b+1
        imul ebx, eax; //<ebx> = b * a
        jo error_of;

        mov ecx, 2; //<ecx> = 2
        mov eax, c; //<eax> = c
        cdq;
        idiv ecx; //<eax> = c/2

        add eax, ebx; //<eax> = c/2 + b*a
        jo error_of;

        pop ebx; //достаем из стека 4*c-b+1
        test ebx, ebx;
        jz error_zf;
        cdq;
        idiv ebx; //<aex> = (c/2 + b*a)/(4*c-b+1)

        mov sum, eax;
        jmp end_asm;

    error_of:
        mov sum, 0; //обнул€ем результат
        mov error_over, -1;
        jmp end_asm;

    error_zf:
        mov sum, 0; //обнул€ем результат
        mov error_zero, -1;
        jmp end_asm;

    end_asm:
        ;
    }
    //(b*a+c/2)/(4*c-b+1)
    //printf("sum: %d", sum);
    if (error_zero != 0) {
        cout << "Division by zero" << endl;
    }
    else if (error_over != 0) {
        cout << "Overflow" << endl;
    }
    else {
        printf("\n (%d * %d + %d/2)/(4 * %d - %d + 1)= %d", b, a, c, c, b, sum);
    }
    getchar(); getchar();
}