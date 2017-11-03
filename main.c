#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "GeneralListOperate.h"

int main() {
    printf("Hello, World!\n");
    char str1[] = "(((a,b,c),(d)),e)" ;
    char str2[] = "(((a,b,c),(d)),e)" ;
    char hstr[100] ;
    GLNode *h, *p ;
    int depth, number, length ;
    h = CreateGList(str1) ;
    printf("广义表 str1 = %s", str2) ;
    DecomposeStr(str2, hstr) ;
    printf("\n表头 = %s", hstr) ;
    printf("\n表尾 = %s", str2) ;
    depth = GListAtomNum(h) ;
    printf("\n深度 = %d", depth) ;
    length = GListLength(h) ;
    printf("\n长度 = %d", length) ;
    number = GListAtomNum(h) ;
    printf("\n原子个数 = %d", number) ;
    p = GListSearch(h, 'd') ;
    if (p != NULL)
        printf("\n数据元素%c在广义表中\n", p->val.atom);
    else
        printf("\n数据元素不在广义表中") ;
    DestroyGList(h) ;
    return 0;
}