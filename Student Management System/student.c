#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Data Structure Definition ---
typedef struct Student {
    int id;
    char name[50];
    float gpa;
    struct Student* next;
    struct Student* prev;
} Student;

// Global head pointer
Student* head = NULL;

// --- Function Prototypes ---
void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();
void updateStudent();
void sortStudents();
void clearBuffer();

// --- Helper Function to clear input buffer ---
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- 1. Add Student (Insert at End) ---
void addStudent() {
    Student* newNode = (Student*)malloc(sizeof(Student));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d", &newNode->id);
    clearBuffer();

    // Check for duplicate ID
    Student* temp = head;
    while (temp != NULL) {
        if (temp->id == newNode->id) {
            printf("Error: Student ID %d already exists!\n", newNode->id);
            free(newNode);
            return;
        }
        temp = temp->next;
    }

    printf("Enter Name: ");
    fgets(newNode->name, sizeof(newNode->name), stdin);
    // Remove newline character from fgets
    newNode->name[strcspn(newNode->name, "\n")] = 0; 

    printf("Enter GPA: ");
    scanf("%f", &newNode->gpa);
    clearBuffer();

    newNode->next = NULL;
    newNode->prev = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        Student* last = head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newNode;
        newNode->prev = last;
    }
    printf("Student added successfully!\n");
}

// --- 2. Display All Students ---
void displayStudents() {
    if (head == NULL) {
        printf("No records found.\n");
        return;
    }

    Student* temp = head;
    printf("\n%-5s %-20s %-5s\n", "ID", "Name", "GPA");
    printf("------------------------------------------\n");
    while (temp != NULL) {
        printf("%-5d %-20s %-5.2f\n", temp->id, temp->name, temp->gpa);
        temp = temp->next;
    }
    printf("------------------------------------------\n");
}

// --- 3. Search Student ---
void searchStudent() {
    int searchId;
    printf("Enter ID to search: ");
    scanf("%d", &searchId);
    clearBuffer();

    Student* temp = head;
    while (temp != NULL) {
        if (temp->id == searchId) {
            printf("Found: ID: %d, Name: %s, GPA: %.2f\n", temp->id, temp->name, temp->gpa);
            return;
        }
        temp = temp->next;
    }
    printf("Student with ID %d not found.\n", searchId);
}

// --- 4. Delete Student ---
void deleteStudent() {
    int delId;
    printf("Enter ID to delete: ");
    scanf("%d", &delId);
    clearBuffer();

    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Student* temp = head;

    // Case 1: Delete Head
    if (head->id == delId) {
        head = head->next;
        if (head != NULL) head->prev = NULL;
        free(temp);
        printf("Student deleted.\n");
        return;
    }

    // Case 2: Delete Middle or Tail
    while (temp != NULL && temp->id != delId) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student not found.\n");
    } else {
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }
        if (temp->prev != NULL) {
            temp->prev->next = temp->next;
        }
        free(temp);
        printf("Student deleted.\n");
    }
}

// --- 5. Update Student ---
void updateStudent() {
    int updateId;
    printf("Enter ID to update: ");
    scanf("%d", &updateId);
    clearBuffer();

    Student* temp = head;
    while (temp != NULL) {
        if (temp->id == updateId) {
            printf("Enter new Name: ");
            fgets(temp->name, sizeof(temp->name), stdin);
            temp->name[strcspn(temp->name, "\n")] = 0;

            printf("Enter new GPA: ");
            scanf("%f", &temp->gpa);
            clearBuffer();
            
            printf("Record updated successfully!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Student not found.\n");
}

// --- 6. Sort Students (Bubble Sort on Linked List) ---
void sortStudents() {
    if (head == NULL) return;

    int swapped;
    Student* ptr1;
    Student* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->gpa < ptr1->next->gpa) { // Sort Descending by GPA
                // Swap data
                int tId = ptr1->id;
                ptr1->id = ptr1->next->id;
                ptr1->next->id = tId;

                float tGpa = ptr1->gpa;
                ptr1->gpa = ptr1->next->gpa;
                ptr1->next->gpa = tGpa;

                char tName[50];
                strcpy(tName, ptr1->name);
                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->next->name, tName);

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    printf("List sorted by GPA (High to Low).\n");
}

// --- Main Menu ---
int main() {
    int choice;

    while (1) {
        printf("\n=== Student Management System (Doubly Linked List) ===\n");
        printf("1. Add Student\n");
        printf("2. Display All\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Update Student\n");
        printf("6. Sort by GPA\n");
        printf("7. Exit\n");
        printf("Enter Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            clearBuffer(); // Handle non-integer input
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: sortStudents(); break;
            case 7: 
                // Free memory before exit
                while(head != NULL) {
                    Student* temp = head;
                    head = head->next;
                    free(temp);
                }
                printf("Exiting...\n");
                return 0;
            default: printf("Invalid choice!\n");
        }
    }
}