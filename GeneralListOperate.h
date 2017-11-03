//
// Created by antonio on 17-11-1.
//

#ifndef GENERALLIST_GENERALLISTOPERATE_H
#define GENERALLIST_GENERALLISTOPERATE_H

#include <string.h>
#include <stdlib.h>
typedef char DataType ;

typedef struct GListNode{
    int tag ;
    //struct GListNode *tail ;
    union {
        DataType atom ;//原子域
        struct {
            struct GListNode *head ;//头链
            struct GListNode *tail ;//尾链
        }subList;//子表域

    }val;

}GLNode;

void DecomposeStr(char str[], char hstr[]){
    //把表示广义表的字符串str分解成表头字符串hstr和表尾字符串str
    int i, j, tag, n = strlen(str) ;
    char ch ;
    ch = str[0], tag = 0 ;
    for (i = 0; i <= n - 1; ++i) {
        if(str[i] == ',' && tag == 1){//搜索最外层的第一个逗号
            break ;
        }
        ch = str[i] ;
        if (ch == '(')
            tag++ ;
        if (ch == ')')
            tag-- ;

    }
    if (i <= n - 1 && str[i] == ','){//广义表表尾部分非空
        for (j = 0; j < i-1; ++j) {//取表头字符串
            hstr[j] = str[j + 1] ;
        }
        hstr[j] = '\0' ;//添加结束符
        if (str[i] == ',')
            i++ ;
        str[0] = '(' ;//添加左括号
        for (j = 1; i <= n-2; ++j, i++) {//取表尾字符串
            str[j] = str[i] ;
        }
        str[j] = ')' ;//取右括号
        str[++j] = '\0' ;//添加结束符
    } else{//广义表表尾部分空
        str++ ;//跳过最左边的左括号
        strncpy(hstr, str, n-2) ;//不复制最右边的右括号
        hstr[n-2] = '\0' ;//添加结束符
        str -- ;//恢复字符串指针的位置
        strcpy(str, "()") ;//表尾部分为空

    }
}

GLNode* CreateGList(char str[]){
    //按照广义表字符串str创建广义表，返回锁创建的广义表的头指针
    //str为表示广义表的字符串
    GLNode *h ;
    char hstr[200] ;
    int len = strlen(str) ;
    if (strcmp(str, "()") == 0)
        h = NULL ;
    else if (len == 1){
        h = (GLNode *)malloc(sizeof(GLNode)) ;
        h->tag = 0 ;
        h->val.atom = str[0] ;
    }
    else{
        h = (GLNode *)malloc(sizeof(GLNode)) ;
        h->tag = 1 ;
        //把字符串str分解成表头hstr和表尾str
        DecomposeStr(str, hstr) ;
        h->val.subList.head = CreateGList(hstr) ;//创建表头的广义表
        if (strcmp(str, "()") != 0)//表尾非空
            h->val.subList.tail = CreateGList(str) ;//创建表尾的广义表
        else//如果表尾为空
            h->val.subList.tail = NULL ;//赋值空指针
    }
    return h ;//返回所创的广义表的头指针
}

//求广义表的深度：括号的重数
int GListDepth(GLNode *h){
    //返回所求广义表h的深度，h为广义表的头指针
    int max, dep ;
    GLNode *pre ;

    if (h == NULL) return 1 ;
    if (h->tag == 0) return 0 ;

    //递归求广义表的深度
    pre = h ;
    //广义表可以分成表头和表尾，对表尾循环
    for(max = 0; pre != NULL; pre = pre->val.subList.tail){
        dep = GListDepth(pre->val.subList.head) ;//递归求表头的深度
        if(dep > max)//寻求最大值
            max = dep ;

    }
    return max+1 ;//当前层深度为上一层深度+1
}

//求广义表的长度:广义表中数据源素或者子表的个数
int GListLength(GLNode *h){
    int number = 0 ;
    GLNode *p ;
    for (p = h; p != NULL; p = p->val.subList.tail)
        number++ ;
    return number ;
}

//广义表中原子的个数
int GListAtomNum(GLNode *h){
    if(h == NULL) return 0 ;
    else{
        if(h->tag == 0) return 1 ;
        else{
            return GListAtomNum(h->val.subList.head) + GListAtomNum(h->val.subList.tail) ;
        }
    }
}

//查找原子
GLNode* GListSearch(GLNode *h, DataType x){
    GLNode *p ;
    if(h == NULL) return NULL ;
    if(h->tag == 0 && h->val.atom == x) return h ;
    if(h->tag == 1 && h->val.subList.head != NULL){
        p = GListSearch(h->val.subList.tail, x) ;//在头链中查找
        if(p != NULL) return p ;

    }
    if(h->tag == 1 && h->val.subList.tail != NULL){
        p = GListSearch(h->val.subList.tail, x) ;//在尾链中查找
        if(p != NULL) return NULL ;
    }
    return NULL ;
}
//撤销广义表
void DestroyGList(GLNode *h){
    if(h == NULL) return;
    if(h->tag == 1 && h->val.subList.head != NULL)//撤销head所指
        DestroyGList(h->val.subList.head) ;
    if(h->tag == 1 && h->val.subList.tail != NULL)//撤销tail所指
        DestroyGList(h->val.subList.tail) ;
    free(h) ;//删除当前
}
#endif //GENERALLIST_GENERALLISTOPERATE_H
