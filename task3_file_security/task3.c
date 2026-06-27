#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#define PASSWORD "admin123"
#define FILE_NAME "data.txt"
#define LOG_FILE "audit.log"
#define KEY 123

void auditLog(char action[]) {
    FILE *log = fopen(LOG_FILE, "a");
    time_t now = time(NULL);

    if (log != NULL) {
        fprintf(log, "%s - %s", action, ctime(&now));
        fclose(log);
    }
}

int authenticate() {
    char password[30];

    printf("Enter Password: ");
    scanf("%s", password);

    if (strcmp(password, PASSWORD) == 0) {
        printf("Authentication Successful!\n");
        auditLog("User logged in successfully");
        return 1;
    } else {
        printf("Authentication Failed!\n");
        auditLog("Failed login attempt");
        return 0;
    }
}

void createFile() {
    FILE *fp = fopen(FILE_NAME, "w");

    if (fp == NULL) {
        printf("File creation failed.\n");
        auditLog("File creation failed");
        return;
    }

    printf("File created successfully.\n");
    auditLog("File created");
    fclose(fp);
}

void writeFile() {
    FILE *fp = fopen(FILE_NAME, "a");
    char text[300];

    if (fp == NULL) {
        printf("Unable to open file.\n");
        auditLog("File write failed");
        return;
    }

    getchar();
    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);

    fprintf(fp, "%s", text);
    fclose(fp);

    printf("Data written successfully.\n");
    auditLog("Data written to file");
}

void readFile() {
    FILE *fp = fopen(FILE_NAME, "r");
    char ch;

    if (fp == NULL) {
        printf("File not found.\n");
        auditLog("File read failed");
        return;
    }

    printf("\nFile Content:\n");

    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }

    fclose(fp);
    auditLog("File read");
}

void deleteFile() {
    if (remove(FILE_NAME) == 0) {
        printf("File deleted successfully.\n");
        auditLog("File deleted");
    } else {
        printf("Unable to delete file.\n");
        auditLog("File deletion failed");
    }
}

void encryptDecryptFile(char action[]) {
    FILE *fp = fopen(FILE_NAME, "rb+");
    char ch;
    long pos;

    if (fp == NULL) {
        printf("File not found.\n");
        auditLog("Encryption/Decryption failed");
        return;
    }

    while ((ch = fgetc(fp)) != EOF) {
        pos = ftell(fp) - 1;
        fseek(fp, pos, SEEK_SET);
        fputc(ch ^ KEY, fp);
        fseek(fp, pos + 1, SEEK_SET);
    }

    fclose(fp);

    printf("File %s successfully.\n", action);
    auditLog(action);
}

void setPermissions() {
    int choice;

    printf("\nPermission Options:\n");
    printf("1. Owner read/write only\n");
    printf("2. Owner read/write, group read, others read\n");
    printf("3. Full permission for all users\n");
    printf("Choose permission: ");
    scanf("%d", &choice);

    if (choice == 1) {
        chmod(FILE_NAME, 0600);
        printf("Permission set to 0600.\n");
        auditLog("Permission changed to 0600");
    } else if (choice == 2) {
        chmod(FILE_NAME, 0644);
        printf("Permission set to 0644.\n");
        auditLog("Permission changed to 0644");
    } else if (choice == 3) {
        chmod(FILE_NAME, 0777);
        printf("Permission set to 0777.\n");
        auditLog("Permission changed to 0777");
    } else {
        printf("Invalid permission choice.\n");
        auditLog("Invalid permission choice");
    }
}

void viewAuditLog() {
    FILE *fp = fopen(LOG_FILE, "r");
    char ch;

    if (fp == NULL) {
        printf("Audit log not found.\n");
        return;
    }

    printf("\nAudit Log:\n");

    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }

    fclose(fp);
}

int main() {
    int choice;

    if (!authenticate()) {
        return 0;
    }

    do {
        printf("\n===== SECURE FILE MANAGEMENT SYSTEM =====\n");
        printf("1. Create File\n");
        printf("2. Write File\n");
        printf("3. Read File\n");
        printf("4. Delete File\n");
        printf("5. Encrypt File\n");
        printf("6. Decrypt File\n");
        printf("7. Set File Permissions\n");
        printf("8. View Audit Log\n");
        printf("9. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
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
                encryptDecryptFile("Encrypted");
                break;
            case 6:
                encryptDecryptFile("Decrypted");
                break;
            case 7:
                setPermissions();
                break;
            case 8:
                viewAuditLog();
                break;
            case 9:
                printf("Exiting system...\n");
                auditLog("User exited system");
                break;
            default:
                printf("Invalid choice.\n");
                auditLog("Invalid menu choice");
        }

    } while (choice != 9);

    return 0;
}
