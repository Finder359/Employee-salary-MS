
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100  //员工数量上限
#define MAX_LOGIN_ATTEMPTS 3  //用户在登录时最大的尝试次数
#define USERNAME "admin"
#define PASSWORD "password"

typedef struct {
    char name[50];
    int id;
    float salary;
} Employee;

// Function prototypes
void login();
void displayMenu();
void addEmployee(Employee* employees, int* numEmployees);
void displayEmployees(Employee* employees, int numEmployees);
void searchEmployee(Employee* employees, int numEmployees);
void deleteEmployee(Employee* employees, int* numEmployees);
void modifyEmployee(Employee* employees, int numEmployees);
void calculateTotalSalary(Employee* employees, int numEmployees);//old name
void saveToFile(Employee* employees, int numEmployees);
void readFromFile(Employee* employees, int* numEmployees);
void sortEmployeesBySalaryDescending(Employee* employees, int numEmployees);    //排序

void clearScreen() {

    system("cls");

}
int main() {
    Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;
    int loginAttempts = 0;

    // 从文件中读取员工信息
    readFromFile(employees, &numEmployees);

    login();

    int choice;
    do {
        clearScreen();
        displayMenu();
        printf("请输入您的选择: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addEmployee(employees, &numEmployees);
            break;
        case 2:
            displayEmployees(employees, numEmployees);
            break;
        case 3:
            searchEmployee(employees, numEmployees);
            break;
        case 4:
            deleteEmployee(employees, &numEmployees);
            saveToFile(employees, numEmployees);  // 保存到文件
            break;
        case 5:
            modifyEmployee(employees, numEmployees);
            saveToFile(employees, numEmployees);  // 保存到文件
            break;
        case 6:
            calculateTotalSalary(employees, numEmployees);
            break;
        case 7:
            saveToFile(employees, numEmployees);
            break;
        case 8:
            printf("正在退出系统。再见！\n");
            break;
        default:
            printf("无效的选择。请键入有效选项。\n");
        }
        printf("按回车键继续...");
        getchar();  // 暂停，等待用户按任意键
        getchar();  // 捕捉用户的实际按键
    } while (choice != 8);

    return 0;
}

void login() {
    char username[50];
    char password[50];
    int attempts = 0;

    do {
        printf("请输入用户名: ");
        scanf("%s", username);
        printf("请输入密码: ");
        scanf("%s", password);

        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            printf("登录成功！\n");
            break;
        }
        else {
            attempts++;
            printf("登录失败。请重试。\n");
        }

        if (attempts >= MAX_LOGIN_ATTEMPTS) {
            printf("登录尝试次数过多。正在退出。\n");
            exit(0);
        }
    } while (1);
}

void displayMenu() {
    printf("员工工资管理系统\n");
    printf("*********选择菜单***********\n");
    printf("1. 添加员工\n");
    printf("2. 显示员工\n");
    printf("3. 查找员工\n");
    printf("4. 删除员工\n");
    printf("5. 修改员工\n");
    printf("6. 按工资从高到低排序员工信息\n");
    printf("7. 保存到文件\n");
    printf("8. 退出\n");
    printf("文件存储在程序根目录下的employee_data.txt内\n");
    printf("****************************\n");
}

void addEmployee(Employee* employees, int* numEmployees) {
    if (*numEmployees < MAX_EMPLOYEES) {
        printf("请输入员工姓名: ");
        scanf("%s", employees[*numEmployees].name);
        printf("请输入员工ID: ");
        scanf("%d", &employees[*numEmployees].id);
        printf("请输入员工工资: ");
        scanf("%f", &employees[*numEmployees].salary);

        (*numEmployees)++;
        printf("员工添加成功！\n");
        // 立即保存到文件
        saveToFile(employees, *numEmployees);
    }
    else {
        printf("员工数量已达到上限，无法添加更多员工。\n");
    }
}

void displayEmployees(Employee* employees, int numEmployees) {
    if (numEmployees > 0) {
        printf("\n员工列表:\n");
        printf("姓名\tID\t工资\n");
        for (int i = 0; i < numEmployees; i++) {
            printf("%s\t%d\t%.2f\n", employees[i].name, employees[i].id, employees[i].salary);
        }
    }
    else {
        printf("没有员工记录。\n");
    }
}

void searchEmployee(Employee* employees, int numEmployees) {
    if (numEmployees > 0) {
        int searchId;
        printf("请输入要查找的员工ID: ");
        scanf("%d", &searchId);

        int found = 0;
        for (int i = 0; i < numEmployees; i++) {
            if (employees[i].id == searchId) {
                printf("员工信息:\n");
                printf("姓名\tID\t工资\n");
                printf("%s\t%d\t%.2f\n", employees[i].name, employees[i].id, employees[i].salary);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("未找到匹配的员工。\n");
        }
    }
    else {
        printf("没有员工记录。\n");
    }
}

void deleteEmployee(Employee* employees, int* numEmployees) {
    if (*numEmployees > 0) {
        int deleteId;
        printf("请输入要删除的员工ID: ");
        scanf("%d", &deleteId);

        int found = 0;
        for (int i = 0; i < *numEmployees; i++) {
            if (employees[i].id == deleteId) {
                // 将最后一个员工的信息覆盖到要删除的位置
                employees[i] = employees[*numEmployees - 1];
                (*numEmployees)--;
                found = 1;
                printf("员工删除成功！\n");
                break;
            }
        }

        if (!found) {
            printf("未找到匹配的员工。\n");
        }
    }
    else {
        printf("没有员工记录。\n");
    }
}

void modifyEmployee(Employee* employees, int numEmployees) {
    if (numEmployees > 0) {
        int modifyId;
        printf("请输入要修改的员工ID: ");
        scanf("%d", &modifyId);

        int found = 0;
        for (int i = 0; i < numEmployees; i++) {
            if (employees[i].id == modifyId) {
                printf("请输入修改后的员工姓名: ");
                scanf("%s", employees[i].name);
                printf("请输入修改后的员工工资: ");
                scanf("%f", &employees[i].salary);
                found = 1;
                printf("员工信息修改成功！\n");
                break;
            }
        }

        if (!found) {
            printf("未找到匹配的员工。\n");
        }
    }
}

void calculateTotalSalary(Employee* employees, int numEmployees) {  //原功能为统计工资总量，已弃用
    //if (numEmployees > 0) {
    //    float totalSalary = 0;
    //    for (int i = 0; i < numEmployees; i++) {
    //        totalSalary += employees[i].salary;
    //    }
    //    printf("总工资为: %.2f\n", totalSalary);
    //}
    //else {
    //    printf("没有员工记录。\n");
    //}
    sortEmployeesBySalaryDescending(employees, numEmployees);
    displayEmployees(employees, numEmployees);
}

void saveToFile(Employee* employees, int numEmployees) {
    FILE* file = fopen("employee_data.txt", "w");

    if (file == NULL) {
        printf("无法打开文件进行保存。\n");
        return;
    }

    for (int i = 0; i < numEmployees; i++) {
        fprintf(file, "%s %d %.2f\n", employees[i].name, employees[i].id, employees[i].salary);
    }

    fclose(file);

    printf("员工信息已保存到文件。\n");
}

void readFromFile(Employee* employees, int* numEmployees) {
    FILE* file = fopen("employee_data.txt", "r");

    if (file == NULL) {
        printf("无法打开文件进行读取。\n");
        return;
    }

    while (fscanf(file, "%s %d %f", employees[*numEmployees].name, &employees[*numEmployees].id, &employees[*numEmployees].salary) == 3) {
        (*numEmployees)++;
        if (*numEmployees >= MAX_EMPLOYEES) {
            printf("文件中的员工数量超过程序支持的上限。\n");
            break;
        }
    }

    fclose(file);

    printf("从文件中读取了 %d 条员工信息。\n", *numEmployees);
}

void sortEmployeesBySalaryDescending(Employee* employees, int numEmployees) {
    // 使用冒泡排序按工资从高到低排序
    for (int i = 0; i < numEmployees - 1; i++) {
        for (int j = 0; j < numEmployees - i - 1; j++) {
            if (employees[j].salary < employees[j + 1].salary) {
                // 交换元素
                Employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
    printf("员工信息已按工资从高到低排序。\n");
}
