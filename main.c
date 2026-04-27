#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

// Structure for Student
struct Student {
    char name[50];
    int id;
    float grade;
};

// Global storage
struct Student students[MAX_STUDENTS];
int count = 0;

// Function Prototypes
void addStudent();
void updateStudent();
void deleteStudent();
void searchStudent();
void generateReport();
void saveToFile();
void loadFromFile();
void adminMenu();
void studentMenu();

// ---------------- MAIN PROGRAM ----------------
int main() {
    int choice;

    loadFromFile();

    while (1) {
        printf("\n==========================================\n");
        printf("===== Student Data Management System =====\n");
        printf("==========================================\n");
        printf("1. Admin Login\n");
        printf("2. Student Login\n");
        printf("3. Exit\n");
        printf("==========================================\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adminMenu();
                break;

            case 2:
                studentMenu();
                break;

            case 3:
                saveToFile();
                printf("Data saved successfully.\n");
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid option.\n");
        }
    }

    return 0;
}

// ---------------- FILE HANDLING ----------------
void saveToFile() {
    FILE *fp = fopen("students.txt", "w");

    if (fp == NULL) {
        printf("Error saving file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s %d %.2f\n",
                students[i].name,
                students[i].id,
                students[i].grade);
    }

    fclose(fp);
}

void loadFromFile() {
    FILE *fp = fopen("students.txt", "r");

    if (fp == NULL) {
        return;
    }

    while (fscanf(fp, "%s %d %f",
                  students[count].name,
                  &students[count].id,
                  &students[count].grade) != EOF) {

        count++;

        if (count >= MAX_STUDENTS) {
            break;
        }
    }

    fclose(fp);
}

// ---------------- ADD STUDENT ----------------
void addStudent() {

    if (count >= MAX_STUDENTS) {
        printf("Database full.\n");
        return;
    }

    printf("Enter student name: ");
    scanf("%s", students[count].name);

    printf("Enter student ID: ");
    scanf("%d", &students[count].id);

    printf("Enter student grade (0-100): ");
    scanf("%f", &students[count].grade);

    if (students[count].grade < 0 || students[count].grade > 100) {
        printf("Invalid grade.\n");
        return;
    }

    count++;

    printf("Student added successfully.\n");
}

// ---------------- UPDATE STUDENT ----------------
void updateStudent() {
    int id;

    printf("Enter student ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {

        if (students[i].id == id) {

            printf("Enter new name: ");
            scanf("%s", students[i].name);

            printf("Enter new grade (0-100): ");
            scanf("%f", &students[i].grade);

            if (students[i].grade < 0 || students[i].grade > 100) {
                printf("Invalid grade.\n");
                return;
            }

            printf("Student record updated successfully.\n");
            return;
        }
    }

    printf("Student not found.\n");
}

// ---------------- DELETE STUDENT ----------------
void deleteStudent() {
    int id;

    printf("Enter student ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {

        if (students[i].id == id) {

            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }

            count--;

            printf("Student record deleted successfully.\n");
            return;
        }
    }

    printf("Student not found.\n");
}

// ---------------- SEARCH STUDENT ----------------
void searchStudent() {

    int option;
    int id;
    char name[50];

    printf("\nSearch By:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("Enter choice: ");
    scanf("%d", &option);

    if (option == 1) {

        printf("Enter ID: ");
        scanf("%d", &id);

        for (int i = 0; i < count; i++) {

            if (students[i].id == id) {

                printf("\nStudent Found:\n");
                printf("Name  : %s\n", students[i].name);
                printf("ID    : %d\n", students[i].id);
                printf("Grade : %.2f\n", students[i].grade);

                return;
            }
        }

        printf("Student not found.\n");
    }

    else if (option == 2) {

        printf("Enter Name: ");
        scanf("%s", name);

        for (int i = 0; i < count; i++) {

            if (strcmp(students[i].name, name) == 0) {

                printf("\nStudent Found:\n");
                printf("Name  : %s\n", students[i].name);
                printf("ID    : %d\n", students[i].id);
                printf("Grade : %.2f\n", students[i].grade);

                return;
            }
        }

        printf("Student not found.\n");
    }

    else {
        printf("Invalid choice.\n");
    }
}

// ---------------- GENERATE REPORT ----------------
void generateReport() {

    if (count == 0) {
        printf("No student records available.\n");
        return;
    }

    printf("\n========== Student Report ==========\n");

    for (int i = 0; i < count; i++) {

        printf("%d. Name: %s | ID: %d | Grade: %.2f\n",
               i + 1,
               students[i].name,
               students[i].id,
               students[i].grade);
    }
}

// ---------------- ADMIN MENU ----------------
void adminMenu() {

    int choice;

    while (1) {

        printf("\n========== Admin Menu ==========\n");
        printf("1. Add Student\n");
        printf("2. Update Student\n");
        printf("3. Delete Student\n");
        printf("4. Search Student\n");
        printf("5. Generate Report\n");
        printf("6. Logout\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                updateStudent();
                break;

            case 3:
                deleteStudent();
                break;

            case 4:
                searchStudent();
                break;

            case 5:
                generateReport();
                break;

            case 6:
                printf("Logging out...\n");
                return;

            default:
                printf("Invalid option.\n");
        }
    }
}

// ---------------- STUDENT MENU ----------------
void studentMenu() {

    int id;

    printf("Enter your student ID: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {

        if (students[i].id == id) {

            printf("\n===== Student Details =====\n");
            printf("Name  : %s\n", students[i].name);
            printf("Grade : %.2f\n", students[i].grade);

            return;
        }
    }

    printf("Record not found.\n");
}
