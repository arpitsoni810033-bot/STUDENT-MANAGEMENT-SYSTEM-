#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

void addStudent(void) {
    struct Student s;
    FILE *fp = fopen("students.dat", "ab");

    if (fp == NULL) {
        printf("File cannot be opened!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Student Name: ");
    scanf(" %49[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("\nStudent Added Successfully!\n");
}

void displayStudents(void) {
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No student records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");
    while (fread(&s, sizeof(s), 1, fp) == 1) {
        printf("\nRoll Number: %d\n", s.roll);
        printf("Name: %s\n", s.name);
        printf("Marks: %.2f\n", s.marks);
    }

    fclose(fp);
}

void searchStudent(void) {
    struct Student s;
    int roll, found = 0;
    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Roll Number to Search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.roll == roll) {
            printf("\nStudent Found!\n");
            printf("Name: %s\n", s.name);
            printf("Marks: %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student Not Found!\n");
    }

    fclose(fp);
}

void updateStudent(void) {
    struct Student s;
    int roll, found = 0;
    FILE *fp = fopen("students.dat", "rb+");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Roll Number to Update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.roll == roll) {
            printf("Enter New Name: ");
            scanf(" %49[^\n]", s.name);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -(long)sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            found = 1;
            printf("Record Updated Successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Student Not Found!\n");
    }

    fclose(fp);
}

void deleteStudent(void) {
    struct Student s;
    int roll, found = 0;
    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        fclose(fp);
        printf("Temporary file cannot be created!\n");
        return;
    }

    printf("Enter Roll Number to Delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.roll == roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("students.dat");
        rename("temp.dat", "students.dat");
        printf("Record Deleted Successfully!\n");
    } else {
        remove("temp.dat");
        printf("Student Not Found!\n");
    }
}

int main(void) {
    int choice;

    do {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("\nEnter Your Choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("Thank You!\n");
                break;
            default:
                printf("Invalid Choice! Try Again.\n");
        }
    } while (choice != 6);

    return 0;
}
