
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100  //Ա����������
#define MAX_LOGIN_ATTEMPTS 3  //�û��ڵ�¼ʱ���ĳ��Դ���
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
void sortEmployeesBySalaryDescending(Employee* employees, int numEmployees);    //����

void clearScreen() {

    system("cls");

}
int main() {
    Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;
    int loginAttempts = 0;

    // ���ļ��ж�ȡԱ����Ϣ
    readFromFile(employees, &numEmployees);

    login();

    int choice;
    do {
        clearScreen();
        displayMenu();
        printf("����������ѡ��: ");
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
            saveToFile(employees, numEmployees);  // ���浽�ļ�
            break;
        case 5:
            modifyEmployee(employees, numEmployees);
            saveToFile(employees, numEmployees);  // ���浽�ļ�
            break;
        case 6:
            calculateTotalSalary(employees, numEmployees);
            break;
        case 7:
            saveToFile(employees, numEmployees);
            break;
        case 8:
            printf("�����˳�ϵͳ���ټ���\n");
            break;
        default:
            printf("��Ч��ѡ���������Чѡ�\n");
        }
        printf("���س�������...");
        getchar();  // ��ͣ���ȴ��û��������
        getchar();  // ��׽�û���ʵ�ʰ���
    } while (choice != 8);

    return 0;
}

void login() {
    char username[50];
    char password[50];
    int attempts = 0;

    do {
        printf("�������û���: ");
        scanf("%s", username);
        printf("����������: ");
        scanf("%s", password);

        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            printf("��¼�ɹ���\n");
            break;
        }
        else {
            attempts++;
            printf("��¼ʧ�ܡ������ԡ�\n");
        }

        if (attempts >= MAX_LOGIN_ATTEMPTS) {
            printf("��¼���Դ������ࡣ�����˳���\n");
            exit(0);
        }
    } while (1);
}

void displayMenu() {
    printf("Ա�����ʹ���ϵͳ\n");
    printf("*********ѡ��˵�***********\n");
    printf("1. ���Ա��\n");
    printf("2. ��ʾԱ��\n");
    printf("3. ����Ա��\n");
    printf("4. ɾ��Ա��\n");
    printf("5. �޸�Ա��\n");
    printf("6. �����ʴӸߵ�������Ա����Ϣ\n");
    printf("7. ���浽�ļ�\n");
    printf("8. �˳�\n");
    printf("�ļ��洢�ڳ����Ŀ¼�µ�employee_data.txt��\n");
    printf("****************************\n");
}

void addEmployee(Employee* employees, int* numEmployees) {
    if (*numEmployees < MAX_EMPLOYEES) {
        printf("������Ա������: ");
        scanf("%s", employees[*numEmployees].name);
        printf("������Ա��ID: ");
        scanf("%d", &employees[*numEmployees].id);
        printf("������Ա������: ");
        scanf("%f", &employees[*numEmployees].salary);

        (*numEmployees)++;
        printf("Ա����ӳɹ���\n");
        // �������浽�ļ�
        saveToFile(employees, *numEmployees);
    }
    else {
        printf("Ա�������Ѵﵽ���ޣ��޷���Ӹ���Ա����\n");
    }
}

void displayEmployees(Employee* employees, int numEmployees) {
    if (numEmployees > 0) {
        printf("\nԱ���б�:\n");
        printf("����\tID\t����\n");
        for (int i = 0; i < numEmployees; i++) {
            printf("%s\t%d\t%.2f\n", employees[i].name, employees[i].id, employees[i].salary);
        }
    }
    else {
        printf("û��Ա����¼��\n");
    }
}

void searchEmployee(Employee* employees, int numEmployees) {
    if (numEmployees > 0) {
        int searchId;
        printf("������Ҫ���ҵ�Ա��ID: ");
        scanf("%d", &searchId);

        int found = 0;
        for (int i = 0; i < numEmployees; i++) {
            if (employees[i].id == searchId) {
                printf("Ա����Ϣ:\n");
                printf("����\tID\t����\n");
                printf("%s\t%d\t%.2f\n", employees[i].name, employees[i].id, employees[i].salary);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("δ�ҵ�ƥ���Ա����\n");
        }
    }
    else {
        printf("û��Ա����¼��\n");
    }
}

void deleteEmployee(Employee* employees, int* numEmployees) {
    if (*numEmployees > 0) {
        int deleteId;
        printf("������Ҫɾ����Ա��ID: ");
        scanf("%d", &deleteId);

        int found = 0;
        for (int i = 0; i < *numEmployees; i++) {
            if (employees[i].id == deleteId) {
                // �����һ��Ա������Ϣ���ǵ�Ҫɾ����λ��
                employees[i] = employees[*numEmployees - 1];
                (*numEmployees)--;
                found = 1;
                printf("Ա��ɾ���ɹ���\n");
                break;
            }
        }

        if (!found) {
            printf("δ�ҵ�ƥ���Ա����\n");
        }
    }
    else {
        printf("û��Ա����¼��\n");
    }
}

void modifyEmployee(Employee* employees, int numEmployees) {
    if (numEmployees > 0) {
        int modifyId;
        printf("������Ҫ�޸ĵ�Ա��ID: ");
        scanf("%d", &modifyId);

        int found = 0;
        for (int i = 0; i < numEmployees; i++) {
            if (employees[i].id == modifyId) {
                printf("�������޸ĺ��Ա������: ");
                scanf("%s", employees[i].name);
                printf("�������޸ĺ��Ա������: ");
                scanf("%f", &employees[i].salary);
                found = 1;
                printf("Ա����Ϣ�޸ĳɹ���\n");
                break;
            }
        }

        if (!found) {
            printf("δ�ҵ�ƥ���Ա����\n");
        }
    }
}

void calculateTotalSalary(Employee* employees, int numEmployees) {  //ԭ����Ϊͳ�ƹ���������������
    //if (numEmployees > 0) {
    //    float totalSalary = 0;
    //    for (int i = 0; i < numEmployees; i++) {
    //        totalSalary += employees[i].salary;
    //    }
    //    printf("�ܹ���Ϊ: %.2f\n", totalSalary);
    //}
    //else {
    //    printf("û��Ա����¼��\n");
    //}
    sortEmployeesBySalaryDescending(employees, numEmployees);
    displayEmployees(employees, numEmployees);
}

void saveToFile(Employee* employees, int numEmployees) {
    FILE* file = fopen("employee_data.txt", "w");

    if (file == NULL) {
        printf("�޷����ļ����б��档\n");
        return;
    }

    for (int i = 0; i < numEmployees; i++) {
        fprintf(file, "%s %d %.2f\n", employees[i].name, employees[i].id, employees[i].salary);
    }

    fclose(file);

    printf("Ա����Ϣ�ѱ��浽�ļ���\n");
}

void readFromFile(Employee* employees, int* numEmployees) {
    FILE* file = fopen("employee_data.txt", "r");

    if (file == NULL) {
        printf("�޷����ļ����ж�ȡ��\n");
        return;
    }

    while (fscanf(file, "%s %d %f", employees[*numEmployees].name, &employees[*numEmployees].id, &employees[*numEmployees].salary) == 3) {
        (*numEmployees)++;
        if (*numEmployees >= MAX_EMPLOYEES) {
            printf("�ļ��е�Ա��������������֧�ֵ����ޡ�\n");
            break;
        }
    }

    fclose(file);

    printf("���ļ��ж�ȡ�� %d ��Ա����Ϣ��\n", *numEmployees);
}

void sortEmployeesBySalaryDescending(Employee* employees, int numEmployees) {
    // ʹ��ð�����򰴹��ʴӸߵ�������
    for (int i = 0; i < numEmployees - 1; i++) {
        for (int j = 0; j < numEmployees - i - 1; j++) {
            if (employees[j].salary < employees[j + 1].salary) {
                // ����Ԫ��
                Employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
    printf("Ա����Ϣ�Ѱ����ʴӸߵ�������\n");
}
