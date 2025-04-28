#pragma once
#include "common.h"
#include "print.h"
#define MAX 100

typedef struct _UIChar
{
    char c[MAX];
    int startId;
} UIchar;

typedef struct _UICharList
{
    UIchar *list[MAX];
    int size;
} UICharList;

/**
 * @brief 初始化UI字符列表
 *
 * @param list 指向UI字符列表的指针
 *
 * @return int 初始化成功返回1，否则返回0
 */
int initUICharList(UICharList *list)
{
    list->size = 0;
    return 1;
}

/**
 * @brief 向UICharList中添加一个字符
 *
 * @param list 指向UICharList的指针
 * @param c 要添加的字符
 * @param startId 字符的起始索引
 *
 * @return 如果添加成功，返回1；否则返回0
 */
int addUICharList(UICharList *list, char *c, int startId)
{
    if (list->size >= MAX)
    {
        return 0;
    }
    else
    {
        UIchar *temp = (UIchar *)malloc(sizeof(UIchar));
        strcpy(temp->c, c);
        temp->startId = startId;
        list->list[list->size] = temp;
        list->size++;
        return 1;
    }
}

/**
 * @brief 显示一个选项菜单并返回用户选择的选项索引
 *
 * @param title 菜单标题
 * @param option 选项列表
 * @param startId 选项列表中第一个选项的索引
 *
 * @return int 用户选择的选项索引
 */
int optionUI(char *title, UICharList *option, int startId)
{
    clearScreen();
    for (int a = startId;;)
    {
        moveCursor();
        printHead(title);
        for (int index = 0; index < option->size; index++)
        {
            char str[MAX];
            sprintf(str, "%d.%s\n", option->list[index]->startId, option->list[index]->c);
            printSelect(str, a == option->list[index]->startId);
        }
        printFoot();
        char c = _getch();
        switch (c)
        {
        // 上键
        case 72:
            a--;
            if (a < 0)
            {
                a = option->size - 1;
            }
            break;
        // 下键
        case 80:
            a++;
            if (a > option->size - 1)
            {
                a = 0;
            }
            break;
        // 回车键和空格
        case 13:
        case 32:
            return a;
            break;
        default:
            continue;
        }
    }
    return -1;
}