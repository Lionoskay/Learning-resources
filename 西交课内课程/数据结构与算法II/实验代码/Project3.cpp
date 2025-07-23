#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 1024

// 存储字符及其权值的结构体
typedef struct {
    char character;  // 字符（空格或a-z）
    int weight;      // 权值
} CharWeight;

typedef struct {
    int weight;         // 霍夫曼树结点权值
    int parent, lch, rch;  // 父节点、左右孩子
} HTNode, * HuffmanTree;

typedef char** HuffmanCode;  // 哈夫曼编码表

// 选择两个权值最小的结点（C89兼容修改：变量声明移至循环外）
void Select(HuffmanTree HT, int n, int* s1, int* s2) {
    int i;
    *s1 = *s2 = -1;
    for (i = 1; i <= n; i++) {
        if (HT[i].parent == 0) {
            if (*s1 == -1 || HT[i].weight < HT[*s1].weight) *s1 = i;
        }
    }
    for (i = 1; i <= n; i++) {
        if (HT[i].parent == 0 && i != *s1) {
            if (*s2 == -1 || HT[i].weight < HT[*s2].weight) *s2 = i;
        }
    }
    if (*s1 == -1 || *s2 == -1) {
        printf("ERROR_02");
        exit(0);
    }
}

// 构建哈夫曼树及编码表（C89兼容修改：变量声明移至循环外）
void HuffmanCoding(HuffmanTree* HT, HuffmanCode* HC, CharWeight* charWeights, int n) {
    int i, m, start, c, f;  // C89要求变量声明在代码块开头
    if (n <= 1) {
        printf("ERROR_02");
        exit(0);
    }
    m = 2 * n - 1;
    *HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
    if (*HT == NULL) {
        printf("ERROR_02");
        exit(0);
    }
    // 初始化叶子结点
    for (i = 1; i <= n; i++) {
        (*HT)[i].weight = charWeights[i - 1].weight;
        (*HT)[i].parent = (*HT)[i].lch = (*HT)[i].rch = 0;
    }
    // 初始化非叶子结点
    for (i = n + 1; i <= m; i++) {
        (*HT)[i].weight = (*HT)[i].parent = (*HT)[i].lch = (*HT)[i].rch = 0;
    }
    // 构建哈夫曼树
    for (i = n + 1; i <= m; i++) {
        int s1, s2;
        Select(*HT, i - 1, &s1, &s2);
        (*HT)[s1].parent = (*HT)[s2].parent = i;
        (*HT)[i].lch = s1;
        (*HT)[i].rch = s2;
        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
        // 确保左孩子权值≤右孩子（权值相同则序号小的在左）
        if ((*HT)[s1].weight > (*HT)[s2].weight ||
            ((*HT)[s1].weight == (*HT)[s2].weight && s1 > s2)) {
            (*HT)[i].lch = s2;
            (*HT)[i].rch = s1;
        }
    }
    // 生成哈夫曼编码
    *HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
    if (*HC == NULL) {
        printf("ERROR_02");
        free(*HT);
        exit(0);
    }
    char* cd = (char*)malloc(n * sizeof(char));  // 临时存储编码
    cd[n - 1] = '\0';
    for (i = 1; i <= n; i++) {
        start = n - 1;
        c = i;
        f = (*HT)[i].parent;
        while (f != 0) {
            if ((*HT)[f].lch == c) cd[--start] = '0';
            else cd[--start] = '1';
            c = f;
            f = (*HT)[f].parent;
        }
        (*HC)[i] = (char*)malloc((n - start) * sizeof(char));
        strcpy((*HC)[i], &cd[start]);  // 替换为标准strcpy
    }
    free(cd);
}

// 统计字符权值（C89兼容修改：变量声明移至循环外）
void initWeights(char* str, int length, CharWeight* charWeights, int* n) {
    int i;  // C89要求变量声明在代码块开头
    int weight[27] = { 0 };  // 0:空格，1-26:a-z
    for (i = 0; i < length; i++) {
        char c = str[i];
        if (c == ' ') weight[0]++;
        else if (c >= 'a' && c <= 'z') weight[c - 'a' + 1]++;
    }
    *n = 0;
    // 收集非零权值的字符
    if (weight[0] > 0) {
        charWeights[*n].character = ' ';
        charWeights[*n].weight = weight[0];
        (*n)++;
    }
    for (i = 1; i < 27; i++) {
        if (weight[i] > 0) {
            charWeights[*n].character = 'a' + (i - 1);  // i=1→a, i=2→b...
            charWeights[*n].weight = weight[i];
            (*n)++;
        }
    }
}

// 哈夫曼译码（C89兼容修改：变量声明移至循环外）
void HuffmanDecoding(HuffmanTree HT, CharWeight* charWeights, int n, char* ma, char* putout) {
    int i, m, idx, f;  // C89要求变量声明在代码块开头
    m = 2 * n - 1;  // 根节点位置
    idx = 0;
    f = m;  // f初始化为根节点
    for (i = 0; i < strlen(ma); i++) {
        char bit = ma[i];
        if (bit == '0') f = HT[f].lch;
        else if (bit == '1') f = HT[f].rch;
        else {  // 无效码字
            printf("ERROR_03");
            exit(0);
        }
        // 到达叶子节点（左右孩子均为0）
        if (HT[f].lch == 0 && HT[f].rch == 0) {
            putout[idx++] = charWeights[f - 1].character;  // 叶子节点f对应charWeights[f-1]
            f = m;  // 重置根节点
        }
    }
    if (f != m) {  // 码字未完全译码
        printf("ERROR_03");
        exit(0);
    }
    putout[idx] = '\0';  // 字符串结束符
}

int main() {
    char str[MAX_INPUT_LEN], ma[MAX_INPUT_LEN];
    int strLen, i, j;  // C89要求变量声明在代码块开头
    fgets(str, MAX_INPUT_LEN, stdin);
    str[strcspn(str, "\n")] = '\0';  // 去除换行符
    fgets(ma, MAX_INPUT_LEN, stdin);
    ma[strcspn(ma, "\n")] = '\0';

    // 检查输入长度
    strLen = strlen(str);
    if (strLen < 20) {
        printf("ERROR_02");
        return 0;
    }
    if (str && !ma) {
        printf("ERROR_01");
        return 0;
    }
    // 统计字符权值
    CharWeight* charWeights = (CharWeight*)malloc(27 * sizeof(CharWeight));  // 最多27个字符
    int n = 0;
    initWeights(str, strLen, charWeights, &n);
    if (n == 0) {  // 无有效字符
        printf("ERROR_02");
        free(charWeights);
        return 0;
    }

    // 构建哈夫曼树和编码表
    HuffmanTree HT = NULL;
    HuffmanCode HC = NULL;
    HuffmanCoding(&HT, &HC, charWeights, n);

    // 生成编码结果
    char* encodeResult = (char*)malloc(MAX_INPUT_LEN * sizeof(char));
    encodeResult[0] = '\0';
    for (i = 0; i < strLen; i++) {
        char c = str[i];
        int found = 0;
        for (j = 0; j < n; j++) {  // 查找字符对应的编码
            if (charWeights[j].character == c) {
                strcat(encodeResult, HC[j + 1]);  // 替换为标准strcat
                found = 1;
                break;
            }
        }
        if (!found) {  // 字符未在权值表中（如大写字母、特殊符号）
            printf("ERROR_02");
            free(charWeights);
            free(encodeResult);
            for (i = 1; i <= n; i++) free(HC[i]);
            free(HC);
            free(HT);
            return 0;
        }
    }

    // 生成译码结果
    char* decodeResult = (char*)malloc(MAX_INPUT_LEN * sizeof(char));
    HuffmanDecoding(HT, charWeights, n, ma, decodeResult);

    // 输出结果
    printf("%s %s", encodeResult, decodeResult);

    // 释放内存
    free(charWeights);
    free(encodeResult);
    free(decodeResult);
    for (i = 1; i <= n; i++) free(HC[i]);
    free(HC);
    free(HT);
    return 0;
}
