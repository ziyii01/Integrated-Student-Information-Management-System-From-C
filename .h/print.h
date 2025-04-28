#pragma once
#include "common.h"
#include "student.h"

typedef enum
{
    MY_COLOR_BLACK = 0, // 黑色
    MY_COLOR_RED,       // 红色
    MY_COLOR_GREEN,     // 绿色
    MY_COLOR_YELLOW,    // 黄色
    MY_COLOR_BLUE,      // 蓝色
    MY_COLOR_MAGENTA,   // 洋红
    MY_COLOR_CYAN,      // 青色
    MY_COLOR_WHITE,     // 白色
    MY_COLOR_DEFAULT    // 默认颜色
} TextColor;

/**
 * 清除屏幕上的所有内容，并将光标移动到屏幕左上角。
 */
void clearScreen()
{
    printf("\033[2J"); // 清除整个屏幕
    printf("\033[H");  // 将光标移动到屏幕左上角
}

/**
 * 单纯移动光标到屏幕左上角
 */
void moveCursor()
{
    printf("\033[H"); // 将光标移动到屏幕左上角
}

/**
 * 等待用户按下任意键继续执行
 *
 * 该函数会提示用户按下任意键继续，然后等待用户按下任意键后继续执行。
 *
 * @return void
 */
void waitForAnyKey()
{
    printf("按任意键继续...\n");
    _getch();
    printf("\n");
}

/**
 * @brief 打印彩色文本
 *
 * 根据指定的颜色打印文本。
 *
 * @param text 要打印的文本
 * @param color 文本颜色，取值范围为0到7，分别对应黑色、红色、绿色、黄色、蓝色、洋红、青色和白色
 */
void printColor(const char *text, TextColor color)
{
    const char *color_codes[] = {
        "\033[0;30m", // 黑色
        "\033[0;31m", // 红色
        "\033[0;32m", // 绿色
        "\033[0;33m", // 黄色
        "\033[0;34m", // 蓝色
        "\033[0;35m", // 洋红
        "\033[0;36m", // 青色
        "\033[0;37m", // 白色
        "\033[0m"};   // 默认颜色
    if (color < MY_COLOR_BLACK || color > MY_COLOR_DEFAULT)
    {
        color = MY_COLOR_DEFAULT;
    }
    printf("%s%s%s", color_codes[color], text, color_codes[MY_COLOR_DEFAULT]);
}

/**
 * 打印分割线
 *
 */
void printLine()
{
    printf("----------------------\n");
}

/**
 * @brief 打印带有样式分隔线的文本基类
 *
 * @param msg 要打印的文本内容
 */
void printBash(const char *msg)
{
    printLine();
    printf("%s\n", msg);
    printLine();
}

/**
 * @brief 打印标题
 *
 * @param title 标题字符串
 */
void printHead(const char *title)
{
    printBash(title);
}

/**
 * 打印脚注
 *
 * 该函数用于打印脚注信息。
 */
void printFoot()
{
    printBash("              by.ziyii");
}

/**
 * @brief 打印带有颜色的文本基类
 *
 * @param title 标题字符串
 * @param msg 消息字符串
 * @param color 文本颜色
 */
void printColorBash(const char *title, const char *msg, TextColor color)
{
    printColor(title, color);
    printf(" ");
    printColor(msg, color);
}

/**
 * @brief 打印错误信息
 *
 * @param msg 错误信息字符串
 */
void printError(const char *msg)
{
    printColorBash("[!]", msg, MY_COLOR_RED);
}

/**
 * @brief 打印成功消息
 *
 * @param msg 要打印的消息
 */
void printSuccess(const char *msg)
{
    printColorBash("[*]", msg, MY_COLOR_GREEN);
}

/**
 * @brief 打印学生信息
 *
 * 打印学生的学号、姓名、性别、生日、手机号、寝室号和邮箱。
 *
 * @param p 指向要打印的学生信息的指针
 */
void printStudent(const Student *p)
{
    int a = 0;
    printf(">> 学  号：%s\n", p->id);
    printf(">> 姓  名：%s\n", p->name);
    printf(">> 性  别：%s\n", p->sex);
    printf(">> 生  日：%s\n", p->age);
    printf(">> 手机号：%s\n", p->mobile);
    printf(">> 寝室号：%s\n", p->dormitory);
    printf(">> 邮  箱：%s\n", p->email);
    printHead("课程信息：");
    while (p->classes[a].score != -1)
    {
        printf(">> 课程名称：%-10s\n", p->classes[a].name);
        printf(">>           ↳课程成绩：%-10d\n\n", p->classes[a].score);
        a++;
    }
}

/**
 * @brief 打印是否选中消息
 *
 * 根据传入的布尔值打印是否选中消息。
 *
 * @param msg 要打印的消息
 * @param isSelect 是否选中，如果为1则打印选中消息，否则打印未选中消息
 */
void printSelect(const char *msg, int isSelect)
{
    if (isSelect)
    {
        printColorBash(">>", msg, MY_COLOR_YELLOW);
    }
    else
    {
        printColorBash(">>", msg, MY_COLOR_DEFAULT);
    }
}