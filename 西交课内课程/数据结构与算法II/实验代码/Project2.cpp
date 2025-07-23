#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STR_LEN 1024

typedef struct
{
    char* str;
    int len;
} HString;

//定义一个结构体存放字符串，str指向字符串中的各个元素，len代表字符串长度



void StrAssign(HString* S, const char* chars) {
    if (S->str)
    {
        free(S->str);
    }
    S->str = NULL;
    S->len = 0;
    S->len = strlen(chars);
    if (S->len==0)  //如果是空字符串
    {
        S->str = NULL;
    }
    else  //如果字符串非空，分配内存
    {

        S->str = (char*)malloc((S->len + 1) * sizeof(char));
        if (!S->str)
            exit(0);  //分配失败，退出程序
        int i = 0;
        for (i = 0; i < S->len; i++)
        {
            S->str[i] = chars[i];
        }
        S->str[i] = '\0';

    }
}

void ClearString(HString* S) {//清空字符串
    if (S->str)
        free(S->str);
    S->str = NULL; // 避免悬空指针
    S->len = 0;
}

int min_len(HString* S, HString* T)//获得较短的字符串
{
    if (S->len > T->len)
        return T->len;
    else
        return S->len;
}

int StrCompare(HString* S, HString* T) {//得到返回值j，返回匹配不相等位置——>进入next数组求解
    int i = 0;//循环因子
    int j = 0;//返回不相等位置,若全部不相等，返回-1
    int h = 0;//检查是否含有模式串
    for (i = 0; i < S->len && i < T->len; i++)//遍历原字符串与模式串，逐个比较
    {
        if (S->str[i] == T->str[i])
        {
            j++;
        }
        else
        {
            break;
        }
    }
    if (j == 0)//如果第一个即不相等——>判断是否全部不相等
    {
        int k = 0;
        for (k = 0; k < S->len && k < T->len; k++)//遍历原字符串与模式串，逐个比较
        {
            if (S->str[k] != T->str[k])
                h++;
        }
        if (h == (min_len(S, T) - 1))//没有匹配的模式串
            return -1;
        else
            return j;//模式串中存在相等的，返回j
    }
    else
        return j;//查找到模式串
}

// 计算模式串的 next 数组
void get_next(HString* T, int* next) {
    int i = 0;  // 模式串当前位置
    int j = -1; // 前缀位置
    next[0] = -1;

    while (i < T->len - 1) {
        if (j == -1 || T->str[i] == T->str[j]) {
            ++i;
            ++j;
            next[i] = j;
        }
        else {
            j = next[j];
        }
    }
}

// KMP 算法实现
int KMP_Index(HString* S, HString* T) {
    // 如果模式串长度为0或者主串长度小于模式串，直接返回-1
    if (T->len == 0 || S->len < T->len) {
        return -1;
    }

    int* next = (int*)malloc(sizeof(int) * T->len);
    if (!next) {
        printf("ERROR_01\n");
        exit(0);
    }

    get_next(T, next);

    int i = 0; // 主串指针
    int j = 0; // 模式串指针

    while (i < S->len && j < T->len) {
        if (j == -1 || S->str[i] == T->str[j]) {
            i++;
            j++;
        }
        else {
            j = next[j]; // 模式串右移
        }
    }

    free(next);

    if (j >= T->len) { // 找到匹配
        return i - T->len + 1; // 返回匹配位置（从1开始计数）
    }
    else {
        return -1; // 未找到匹配
    }
}

int main() {
    char S_str[STR_LEN] = "";
    char T_str[STR_LEN] = "";

    // 读取原字符串和模式串
    if (!fgets(S_str, sizeof(S_str), stdin) ||
        !fgets(T_str, sizeof(T_str), stdin)) {
        printf("ERROR_01\n");
        return 0;
    }

    // 去除换行符
    S_str[strcspn(S_str, "\n")] = '\0';
    T_str[strcspn(T_str, "\n")] = '\0';

    //分配空间
    HString S = { NULL,0 };
    HString T = { NULL,0 };
    StrAssign(&S, S_str);
    StrAssign(&T, T_str);

    // 使用KMP算法查找模式串
    int pos = KMP_Index(&S, &T);
    printf("%d\n", pos);

    ClearString(&S);
    ClearString(&T);
    return 0;
}