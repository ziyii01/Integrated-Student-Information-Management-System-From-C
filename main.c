#include ".h/common.h"
#include ".h/classes.h"
#include ".h/student.h"
#include ".h/print.h"
#include ".h/auth.h"
#include ".h/optionUI.h"
#define MAX_ID 100

/**
 * @brief 添加学生信息
 *
 * @param list 学生链表
 */
void addStudent(StudentList *list)
{
    clearScreen();
    Student *newStudent = (Student *)malloc(sizeof(Student));
    printHead("添加学生信息");
    int flag;
    StudentNode *temp = list->head;
    do
    {
        printf("-> 请输入学生学  号：");
        scanf("%s", newStudent->id);
        if (findPersonById(list, newStudent->id) != NULL)
        {
            printError("学号重复，请重新输入！\n");
            flag = 1;
        }
        else
        {
            flag = 0;
        }
    } while (flag);
    do
    {
        printf("-> 请输入学生姓  名：");
        scanf("%s", newStudent->name);
        if (findPersonByName(list, newStudent->name) != NULL)
        {
            printError("姓名重复，请重新输入！\n");
            flag = 1;
        }
        else
        {
            flag = 0;
        }
    } while (flag);
    printf("-> 请输入学生性  别：");
    scanf("%s", newStudent->sex);
    printf("-> 请输入学生生  日：");
    scanf("%s", newStudent->age);
    printf("-> 请输入学生手机号：");
    scanf("%s", newStudent->mobile);
    printf("-> 请输入学生寝室号：");
    scanf("%s", newStudent->dormitory);
    printf("-> 请输入学生邮  箱：");
    scanf("%s", newStudent->email);
    printLine();
    newStudent->del = 1;
    printf("-> 请输入课程信息，输入0退出：\n");
    int a = 0;
    while (1)
    {
        Classes newClass;
        printf("-> 请输入课程名称：");
        scanf("%s", &newClass.name);
        if (strcmp(newClass.name, "0") == 0)
        {
            break;
        }
        int flag = 0;
        for (int i = 0; i < a; i++)
        {
            if (strcmp(newClass.name, newStudent->classes[i].name) == 0)
            {
                printf("\n");
                printError("课程名称重复，请重新输入！\n\n");
                flag = 1;
                continue;
            }
        }
        if (flag)
        {
            continue;
        }
        printf("-> 请输入课程成绩：");
        scanf("%d", &newClass.score);
        newStudent->classes[a] = newClass;
        printf("\n");
        a++;
    }
    Classes newClass;
    newClass.score = -1;
    newStudent->classes[a] = newClass;
    int b = appendPerson(list, newStudent);
    clearScreen();
    printHead("添加学生信息");
    printStudent(newStudent);
    printLine();
    if (b == 1)
    {
        printSuccess("添加成功！\n");
    }
    else
    {
        printError("添加失败！\n");
    }
    printFoot();
    waitForAnyKey();
}

/**
 * @brief 查询学生信息
 *
 * @param list 学生链表
 */
void findStudent(StudentList *list)
{
    char id[MAX_ID];
    int a;
    while (1)
    {
        clearScreen();
        printHead("查询学生信息");
        printf("-> 请输入学生学号/姓名，输入0退出：");
        scanf("%s", id);
        if (strcmp(id, "0") == 0)
        {
            break;
        }
        Student *result = findPersonByIdAndName(list, id);
        if (result == NULL)
        {
            printLine();
            printError("没有找到该学生信息！\n");
        }
        else
        {
            clearScreen();
            printHead("查询到学生信息：");
            printStudent(result);
        }
        printFoot();
        waitForAnyKey();
    }
}

/**
 * @brief 修改学生信息
 *
 * @param list 学生链表
 */
void modifyStudent(StudentList *list)
{
    while (1)
    {
        clearScreen();
        printHead("修改学生信息");
        printf("-> 请输入学生学号，输入0退出：");
        char id[MAX_ID];
        scanf("%s", id);
        if (strcmp(id, "0") == 0)
        {
            break;
        }
        Student *result = findPersonByIdAndName(list, id);
        if (result == NULL)
        {
            printLine();
            printError("没有找到该学生信息！\n");
            printFoot();
            waitForAnyKey();
        }
        else
        {
            while (1)
            {
                clearScreen();
                printHead("修改学生信息");
                printf("-> 请输入学生学号，输入0退出：%s\n", id);
                printLine();
                printStudent(result);
                printLine();
                printf("-> 请输入要修改的信息，输入0退出：");
                char info[20];
                scanf("%s", info);
                if (strcmp(info, "0") == 0)
                {
                    break;
                }
                else if (strcmp(info, "姓名") == 0)
                {
                    printf("-> 请输入新的姓名：");
                    scanf("%s", result->name);
                }
                else if (strcmp(info, "性别") == 0)
                {
                    printf("-> 请输入新的性别：");
                    scanf("%s", result->sex);
                }
                else if (strcmp(info, "生日") == 0)
                {
                    printf("-> 请输入新的生日：");
                    scanf("%s", result->age);
                }
                else if (strcmp(info, "手机号") == 0)
                {
                    printf("-> 请输入新的手机号：");
                    scanf("%s", result->mobile);
                }
                else if (strcmp(info, "邮箱") == 0)
                {
                    printf("-> 请输入新的邮箱：");
                    scanf("%s", result->email);
                }
                else if (strcmp(info, "课程") == 0)
                {
                    printf("-> 请输入要修改的课程名称：");
                    char className[20];
                    scanf("%s", className);
                    printf("-> 请输入要修改的课程成绩：");
                    int score;
                    scanf("%d", &score);
                    for (int i = 0; i < MAX_CLASS; i++)
                    {
                        if (strcmp(result->classes[i].name, className) == 0)
                        {
                            result->classes[i].score = score;
                            break;
                        }
                    }
                }
                else
                {
                    printError("无效的修改信息！\n");
                }
            }
        }
    }
}

/**
 * @brief 删除学生信息
 *
 * @param list 学生链表
 */
void deleteStudent(StudentList *list)
{
    while (1)
    {
        clearScreen();
        printHead("删除学生信息");
        printf("-> 请输入学生学号/姓名，输入0退出：");
        char id[MAX_ID];
        scanf("%s", id);
        if (strcmp(id, "0") == 0)
        {
            break;
        }
        if (deletePersonByIdAndName(list, id) == 0)
        {
            printLine();
            printError("没有找到该学生信息！\n");
        }
        else
        {
            printLine();
            printSuccess("删除成功！\n");
        }
        printFoot();
        waitForAnyKey();
    }
}

/**
 * @brief 退出系统
 */
void exitSystem()
{
    clearScreen();
    printHead("退出系统");
    printSuccess("感谢使用，再见！\n");
    printFoot();
    waitForAnyKey();
    exit(0);
}

/**
 * @brief 课程统计分析
 *
 * @param list 学生链表
 */
void analyzeCourses(StudentList *list)
{
    clearScreen();
    printHead("课程统计分析");
    char courseNames[MAX_CLASS][MAX_CLASS_NAME];
    int courseCount = 0;
    int maxScores[MAX_CLASS] = {0};
    int minScores[MAX_CLASS] = {100};
    float avgScores[MAX_CLASS] = {0};
    int studentCounts[MAX_CLASS] = {0};
    StudentNode *temp = ifStudent(list->head);
    while (temp != NULL)
    {
        for (int i = 0; i < MAX_CLASS; i++)
        {
            if (temp->data.classes[i].score == -1)
            {
                break;
            }
            int found = 0;
            for (int j = 0; j < courseCount; j++)
            {
                if (strcmp(temp->data.classes[i].name, courseNames[j]) == 0)
                {
                    found = 1;
                    if (temp->data.classes[i].score > maxScores[j])
                    {
                        maxScores[j] = temp->data.classes[i].score;
                    }
                    if (temp->data.classes[i].score < minScores[j])
                    {
                        minScores[j] = temp->data.classes[i].score;
                    }
                    avgScores[j] += temp->data.classes[i].score;
                    studentCounts[j]++;
                    break;
                }
            }
            if (!found && courseCount < MAX_CLASS)
            {
                strcpy(courseNames[courseCount], temp->data.classes[i].name);
                maxScores[courseCount] = temp->data.classes[i].score;
                minScores[courseCount] = temp->data.classes[i].score;
                avgScores[courseCount] = temp->data.classes[i].score;
                studentCounts[courseCount] = 1;
                courseCount++;
            }
        }
        temp = ifStudent(temp->next);
    }
    for (int i = 0; i < courseCount; i++)
    {
        avgScores[i] /= studentCounts[i];
    }
    printf("课程名称\t最高分\t最低分\t平均分\n");
    for (int i = 0; i < courseCount; i++)
    {
        printf("%-15s\t%d\t%d\t%.2f\n", courseNames[i], maxScores[i], minScores[i], avgScores[i]);
    }
    waitForAnyKey();
}

/**
 * @brief 比较两个学生节点的总分
 *
 * @param a 第一个学生节点指针
 * @param b 第二个学生节点指针
 * @return int 如果第一个学生节点的总分小于第二个学生节点的总分，返回负数；如果相等，返回0；否则返回正数
 */
int compareStudentsByTotal(const void *a, const void *b)
{
    StudentNode *nodeA = *(StudentNode **)a;
    StudentNode *nodeB = *(StudentNode **)b;
    int totalA = 0, totalB = 0;
    for (int i = 0; i < MAX_CLASS; i++)
    {
        if (nodeA->data.classes[i].score == -1)
            break;
        totalA += nodeA->data.classes[i].score;
    }
    for (int i = 0; i < MAX_CLASS; i++)
    {
        if (nodeB->data.classes[i].score == -1)
            break;
        totalB += nodeB->data.classes[i].score;
    }
    return totalB - totalA;
}

/**
 * @brief 比较两个学生的平均成绩
 *
 * @param a 第一个学生的指针
 * @param b 第二个学生的指针
 * @return int 如果第一个学生的平均成绩大于第二个学生的平均成绩，返回1；如果第一个学生的平均成绩小于第二个学生的平均成绩，返回-1；如果两个学生的平均成绩相等，返回0
 */
int compareStudentsByAverage(const void *a, const void *b)
{
    StudentNode *nodeA = *(StudentNode **)a;
    StudentNode *nodeB = *(StudentNode **)b;
    int totalA = 0, totalB = 0;
    int countA = 0, countB = 0;
    for (int i = 0; i < MAX_CLASS; i++)
    {
        if (nodeA->data.classes[i].score == -1)
            break;
        totalA += nodeA->data.classes[i].score;
        countA++;
    }
    for (int i = 0; i < MAX_CLASS; i++)
    {
        if (nodeB->data.classes[i].score == -1)
            break;
        totalB += nodeB->data.classes[i].score;
        countB++;
    }
    float avgA = countA > 0 ? (float)totalA / countA : 0;
    float avgB = countB > 0 ? (float)totalB / countB : 0;
    if (avgB > avgA)
        return 1;
    if (avgB < avgA)
        return -1;
    return 0;
}

/**
 * @brief 学生排名
 *
 * @param list 学生列表
 * @param byAverage 是否按平均分排名
 */
void rankStudents(StudentList *list, int byAverage)
{
    clearScreen();
    printHead("学生排名");
    StudentNode **nodes = malloc(list->count * sizeof(StudentNode *));
    StudentNode *temp = ifStudent(list->head);
    int i = 0;
    while (temp != NULL)
    {
        nodes[i++] = temp;
        temp = ifStudent(temp->next);
    }
    if (byAverage)
    {
        qsort(nodes, list->count, sizeof(StudentNode *), compareStudentsByAverage);
        printf("排名\t学号    \t姓名\t平均分\n");
    }
    else
    {
        qsort(nodes, list->count, sizeof(StudentNode *), compareStudentsByTotal);
        printf("排名\t学号    \t姓名\t总分\n");
    }
    for (i = 0; i < list->count; i++)
    {
        int total = 0;
        int count = 0;
        for (int j = 0; j < MAX_CLASS; j++)
        {
            if (nodes[i]->data.classes[j].score == -1)
                break;
            total += nodes[i]->data.classes[j].score;
            count++;
        }
        if (byAverage)
        {
            float avg = count > 0 ? (float)total / count : 0;
            printf("%d\t%s\t%s\t%.2f\n", i + 1, nodes[i]->data.id, nodes[i]->data.name, avg);
        }
        else
        {
            printf("%d\t%s\t%s\t%d\n", i + 1, nodes[i]->data.id, nodes[i]->data.name, total);
        }
    }
    free(nodes);
    waitForAnyKey();
}

/**
 * @brief 分析系统
 *
 * @param list 学生列表
 */
void analysisSystem(StudentList *list)
{
    for (int choice = 0; choice != -1;)
    {
        UICharList uiCharList;
        initUICharList(&uiCharList);
        addUICharList(&uiCharList, "学生成绩统计", 1);
        addUICharList(&uiCharList, "课程统计分析", 2);
        addUICharList(&uiCharList, "按总分排名", 3);
        addUICharList(&uiCharList, "按平均分排名", 4);
        addUICharList(&uiCharList, "返回", 0);
        choice = optionUI("分析系统", &uiCharList, choice);
        switch (choice)
        {
        case 1:
            clearScreen();
            printHead("学生成绩统计");
            printf("正在加载……");
            Sleep(2500);
            clearScreen();
            printHead("学生成绩统计");
            printf("正在分析……\n");
            Sleep(1000);
            printf("正在分析……\n");
            Sleep(1000);
            printf("正在分析……\n");
            Sleep(1000);
            clearScreen();
            printHead("学生成绩统计");
            printf("%-12s%-8s%s\n", "学号", "总分", "平均分");
            StudentNode *temp = ifStudent(list->head);
            while (temp != NULL)
            {
                int totalScore = 0;
                float averageScore = 0;
                int courseCount = 0;
                for (int i = 0; i < MAX_CLASS; i++)
                {
                    if (temp->data.classes[i].score == -1)
                    {
                        break;
                    }
                    totalScore += temp->data.classes[i].score;
                    courseCount++;
                }
                if (courseCount > 0)
                {
                    averageScore = (float)totalScore / courseCount;
                }
                printf("%-10s%-6d%.2f\n", temp->data.id, totalScore, averageScore);
                temp = ifStudent(temp->next);
            }
            waitForAnyKey();
            break;
        case 2:
            analyzeCourses(list);
            break;
        case 3:
            rankStudents(list, 0);
            break;
        case 4:
            rankStudents(list, 1);
            break;
        case 0:
            choice = -1;
            break;
        default:
            printf("无效选择!\n");
            waitForAnyKey();
        }
    }
}

/**
 * 从CSV文件批量导入学生信息
 * @param list 学生链表
 * @param filename CSV文件名
 * @return 成功导入的学生数量
 */
int batchImportFromCSV(StudentList *list, const char *filename)
{
    FILE *file = fopen(filename, "r");
    // FILE *file = fopen("C:\\ziyii\\c\\students.csv", "r");
    if (file == NULL)
    {
        printError("无法打开文件！\n");
        return 0;
    }
    char line[1024];
    int importedCount = 0;
    int lineNumber = 0;
    fgets(line, sizeof(line), file);
    lineNumber++;
    while (fgets(line, sizeof(line), file))
    {
        lineNumber++;
        line[strcspn(line, "\n")] = 0;
        Student *newStudent = (Student *)malloc(sizeof(Student));
        if (newStudent == NULL)
        {
            printError("内存分配失败！\n");
            continue;
        }
        char *token = strtok(line, ",");
        int fieldIndex = 0;
        int classIndex = 0;
        while (token != NULL && fieldIndex <= 10)
        {
            switch (fieldIndex)
            {
            case 0:
                strncpy(newStudent->id, token, sizeof(newStudent->id));
                break;
            case 1:
                strncpy(newStudent->name, token, sizeof(newStudent->name));
                break;
            case 2:
                strncpy(newStudent->sex, token, sizeof(newStudent->sex));
                break;
            case 3:
                strncpy(newStudent->age, token, sizeof(newStudent->age));
                break;
            case 4:
                strncpy(newStudent->mobile, token, sizeof(newStudent->mobile));
                break;
            case 5:
                strncpy(newStudent->dormitory, token, sizeof(newStudent->dormitory));
                break;
            case 6:
                strncpy(newStudent->email, token, sizeof(newStudent->email));
                break;
            case 7:
                strncpy(newStudent->classes[classIndex].name, "C语言程序设计", sizeof(newStudent->classes[classIndex].name));
                newStudent->classes[classIndex].score = atoi(token);
                classIndex++;
                break;
            case 8:
                strncpy(newStudent->classes[classIndex].name, "高数", sizeof(newStudent->classes[classIndex].name));
                newStudent->classes[classIndex].score = atoi(token);
                classIndex++;
                break;
            case 9:
                strncpy(newStudent->classes[classIndex].name, "英语", sizeof(newStudent->classes[classIndex].name));
                newStudent->classes[classIndex].score = atoi(token);
                classIndex++;
                break;
            }
            token = strtok(NULL, ",");
            fieldIndex++;
        }
        newStudent->classes[classIndex].score = -1;
        newStudent->del = 1;
        if (findPersonById(list, newStudent->id) != NULL)
        {
            printf("警告：第%d行学号%s已存在，跳过导入\n", lineNumber, newStudent->id);
            free(newStudent);
            continue;
        }
        if (appendPerson(list, newStudent))
        {
            importedCount++;
        }
        else
        {
            free(newStudent);
        }
    }
    fclose(file);
    return importedCount;
}

/**
 * @brief 批量导入学生信息
 *
 * @param list 学生链表
 */
void importStudent(StudentList *list)
{
    char filename[256];
    clearScreen();
    printHead("批量导入学生信息");
    printf("请输入要导入的CSV文件路径：");
    scanf("%s", filename);
    printLine();
    int importedCount = batchImportFromCSV(list, filename);
    if (importedCount == 0)
    {
    }
    else
    {
        char c[100];
        sprintf(c, "成功导入%d条记录\n", importedCount);
        printSuccess(c);
    }
    printFoot();
    waitForAnyKey();
}

/**
 * @brief 管理员密码验证
 *
 * @return 验证成功返回1，失败返回0
 */
int auth()
{
    clearScreen();
    printHead("欢迎使用学生信息管理系统");
    printf("请输入8位管理员密码：");
    char password[21];
    for (char c = _getch(); c != 13; c = _getch())
    {
        // 删除键
        if (c == 8)
        {
            if (strlen(password) > 0)
            {
                password[strlen(password) - 1] = '\0';
                printf("\b \b");
            }
        }
        else
        {
            if (strlen(password) < 20)
            {
                password[strlen(password)] = c;
                printf("*");
            }
        }
    }
    password[strlen(password)] = '\0';
    char output[65];
    sha256_hash(password, output);
    printf("\n");
    printLine();
    if (strcmp(output, "1ffb9e69fd37154d0e0fede61dd23c60fcb81943cf5260c84a0881832b298dd0") == 0)
    {
        printSuccess("密码正确\n");
        printFoot();
        return 1;
    }
    else
    {
        printError("密码错误\n");
        printFoot();
        return 0;
    }
}

/**
 * 主函数（
 */
int main()
{
    // 适配垃圾win终端的编码
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    // 登录验证
    if (!auth())
    {
        Sleep(1000);
        exit(0);
    }
    Sleep(1000);
    int choice = -1;
    StudentList StudentList;
    initPersonList(&StudentList);
    int a = 0;
    for (int choice = 0;;)
    {
        UICharList list;
        initUICharList(&list);
        addUICharList(&list, "添加学生信息", 1);
        addUICharList(&list, "删除学生信息", 2);
        addUICharList(&list, "修改学生信息", 3);
        addUICharList(&list, "查询学生信息", 4);
        addUICharList(&list, "进入分析系统", 5);
        addUICharList(&list, "批量导入信息", 6);
        addUICharList(&list, "退出管理系统", 0);
        choice = optionUI("欢迎使用学生信息管理系统", &list, choice);
        switch (choice)
        {
        case 1:
            addStudent(&StudentList);
            break;
        case 2:
            deleteStudent(&StudentList);
            break;
        case 3:
            modifyStudent(&StudentList);
            break;
        case 4:
            findStudent(&StudentList);
            break;
        case 5:
            analysisSystem(&StudentList);
            break;
        case 6:
            importStudent(&StudentList);
            break;
        case 0:
            exitSystem();
        }
    }
    return 0;
}
