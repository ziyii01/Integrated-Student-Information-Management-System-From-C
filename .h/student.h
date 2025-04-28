#pragma once
#include "common.h"
#include "classes.h"
#define MAX_ID 100
#define MAX_NAME 100
#define MAX_SEX 100
#define MAX_AGE 100
#define MAX_MOBILE 100
#define MAX_DORMITORY 100
#define MAX_EMAIL 100
#define MAX_CLASS 100

typedef struct _student
{
    char id[MAX_ID];               // 学号
    char name[MAX_NAME];           // 姓名
    char sex[MAX_SEX];             // 性别
    char age[MAX_AGE];             // 出生日期
    char mobile[MAX_MOBILE];       // 手机号
    char dormitory[MAX_DORMITORY]; // 寝室号
    char email[MAX_EMAIL];         // 邮箱
    unsigned short del;            // 是否删除，1表示删除，0表示未删除
    Classes classes[MAX_CLASS];    // 课程信息
} Student;

typedef struct _studentNode
{
    Student data;
    struct _studentNode *next;
} StudentNode;

typedef struct _studentList
{
    StudentNode *head;
    StudentNode *tail;
    int count;
} StudentList;

/**
 * 初始化学生列表
 *
 * @param list 指向学生列表的指针
 */
void initPersonList(StudentList *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
}

/**
 * @brief 向学生链表中添加一个学生节点
 *
 * @param list 指向学生链表结构的指针
 * @param p 指向要添加的学生数据的指针
 * @return int 添加成功返回1，否则返回0
 */
int appendPerson(StudentList *list, const Student *p)
{
    StudentNode *newNode = (StudentNode *)malloc(sizeof(StudentNode));
    if (!newNode)
    {
        return 0;
    }
    newNode->data = *p;
    newNode->next = NULL;
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->count++;
    return 1;
}

/**
 * @brief 根据学号查找学生信息
 *
 * 在给定的学生列表中，根据学号查找学生信息。如果找到匹配的学生且该学生未被删除，则返回该学生的指针；否则返回NULL。
 *
 * @param list 指向学生列表的指针
 * @param id 要查找的学号
 * @return student* 如果找到匹配的学生且该学生未被删除，则返回该学生的指针；否则返回NULL
 */
Student *findPersonById(const StudentList *list, const char *id)
{
    StudentNode *current = list->head;
    while (current != NULL)
    {
        if (strcmp(current->data.id, id) == 0 && current->data.del == 1)
        {
            return &current->data;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * @brief 根据姓名查找学生信息
 *
 * 在给定的学生列表中，根据姓名查找学生信息。如果找到匹配的学生且该学生未被删除，则返回该学生的指针；否则返回NULL。
 *
 * @param list 指向学生列表的指针
 * @param name 要查找的学生姓名
 * @return student* 指向找到的学生信息的指针，如果未找到则返回NULL
 */
Student *findPersonByName(const StudentList *list, const char *name)
{
    StudentNode *current = list->head;
    while (current != NULL)
    {
        if (strcmp(current->data.name, name) == 0 && current->data.del == 1)
        {
            return &current->data;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * 根据ID或姓名查找学生
 *
 * @param list 学生列表
 * @param key 查找关键字（ID或姓名）
 * @return 查找到的学生，如果未找到则返回NULL
 */
Student *findPersonByIdAndName(const StudentList *list, const char *key)
{
    Student *result = findPersonById(list, key);
    Student *result2 = findPersonByName(list, key);
    Student *finalResult = result ? result : result2;
    return finalResult;
}

/**
 * @brief 根据ID和姓名删除学生节点
 *
 * @param list 指向学生列表的指针
 * @param key 包含ID或姓名的键值
 * @return int 如果删除成功返回1，否则返回0
 */
int deletePersonByIdAndName(StudentList *list, const char *key)
{
    Student *student = findPersonByIdAndName(list, key);
    if (student != NULL)
    {
        student->del = 0;
        list->count--;
        return 1;
    }
    return 0;
}

/**
 * @brief 销毁学生链表
 *
 * @param list 指向学生链表的指针
 */
void destroyPersonList(StudentList *list)
{
    StudentNode *current = list->head;
    while (current != NULL)
    {
        StudentNode *temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
}

/**
 * @brief 判断传入的节点是否为有效学生节点
 *
 * @param Node 当前节点
 * @return StudentNode* 如果当前节点为有效学生节点，则返回该节点；否则返回下一个节点/NULL
 */
StudentNode *ifStudent(StudentNode *Node)
{
    if (Node == NULL)
        return NULL;
    if (Node->data.del == 0)
        return ifStudent(Node->next);
    else
        return Node;
}
