#
include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASSWORD "admin123"

void createFile() {
    FILE *fp = fopen("data.txt", "w");

    if(fp == NULL) {
        printf("File creation failed.\n");
        return;
    }

    printf("File created successfully.\n");
    fclose(fp);
}

void writeFile() {
    FILE *fp = fopen("data.txt", "a");

    char text[200];

    printf("Enter text: ");
    getchar();
    fgets(text, sizeof(text), stdin);

    fprintf(fp, "%s", text);

    fclose(fp);

    printf("Data written successfully.\n");
}

void readFile() {
    FILE *fp = fopen("data.txt", "r");

    char ch;

    if(fp == NULL) {
        printf("File not found.\n");
        return;
    }

    printf("\nFile Content:\n");

    while((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }

    fclose(fp);
}

void deleteFile() {
    if(remove("data.txt") == 0)
        printf("File deleted successfully.\n");
    else
        printf("Unable to delete file.\n");
}

int main() {

    char password[20];

    printf("Enter Password: ");
    scanf("%s", password);

    if(strcmp(password, PASSWORD) != 0) {
        printf("Authentication Failed!\n");
        return 0;
    }

    printf("Authentication Successful!\n");

    int choice;

    do {
        printf("\n===== FILE SECURITY SYSTEM =====\n");
        printf("1. Create File\n");
        printf("2. Write File\n");
        printf("3. Read File\n");
        printf("4. Delete File\n");
        printf("5. Exit\n");

        printf("Choose: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                createFile();
                break;

            case 2:
                writeFile();
                break;

            case 3:
                readFile();
                break;

            case 4:
                deleteFile();
                break;

            case 5:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid Choice\n");
        }

    } while(choice != 5);

    return 0;
}
