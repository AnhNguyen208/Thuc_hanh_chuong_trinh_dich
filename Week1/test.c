#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct DS {
    int line;
    char word[20];
    int SoLanXuatHien;
} List;
struct HienThi {
    char word[20];
    char stringLine[100];
};

struct DS ds[1000];
struct HienThi hThi[100];

void Sapxep(int n) {
    struct DS temp;
    for (int i = 0; i < n ; i++) {
        for (int j = 0; j < n; j++) {
            if (strcmp(ds[i].word, ds[j].word) < 0) {
                temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(ds[i].word, ds[j].word) == 0) {
                ds[i].SoLanXuatHien++;
                ds[j].SoLanXuatHien++;
            }
        }
    }
}

int KiemTra(char* a, char* b) {
    char* temp = (char*)malloc(20);
    strcpy(temp, a);
    strrev(temp);
    if ((strncmp(temp, ".", 1) == 0) && (isupper(b[0]) != 0)) {
        free(temp);
        return 1;
    }
    else if ((isupper(b[0]) == 0) && (isupper(a[0]) == 0)) {
        free(temp);
        return 2;
    }
    else if ((isupper(b[0]) == 0) && (isupper(a[0]) != 0)) {
        free(temp);
        return 2;
    }
    else {
        free(temp);
        return 0;
    }

}

int Stopw(char *p, char stop[20][10], int number1) {
    int number2 = 0;
    for (int i = 0; i < number1; i++) {
        if (strcmp(p, stop[i]) == 0) {
            return 1;
            break;
        }
        else {
            number2 = 0;
        }
    }
    if (number2 == 0) {
        return 0;
    }
}

int main() {
    FILE* file;
    FILE* file1;
    int m = 1, n = 0, number = 0, number1 = 0, number2 = 0;
    char *c = (char*)malloc(1000);
    char temp[10];
    char stop[20][10];
    file1 = fopen("stopw.txt", "r");
    while (feof(file1) == 0) {
        fscanf(file1, "%s", stop[number1]);
        // printf("%s\n", stop[number1]);
        number1++;
    }    
    fclose(file1);
    file = fopen("vanban.txt", "r");
    while (fgets(c, 1000, file) != NULL)
    {
        char* p = (char*)malloc(15);
        char* q = (char*)malloc(15);
        char* r = (char*)malloc(15);
        p = strtok(c, " '\n',()");
        strcpy(q, p);
        strlwr(p);
        number2 = Stopw(p, stop, number1);
        if (number2 == 0) {
            if (strncmp(p, "A", 1) >= 0) {
                ds[n].line = m;
                ds[n].SoLanXuatHien = 1;
                strcpy(ds[n].word, p);
                // printf("%s ", p);
                n++;
            }
        }
        while (p != NULL) {
            p = strtok(NULL, " '\n',()");
            if (p != NULL) {
                if (KiemTra(q, p) != 0) {
                    strcpy(r, p);
                    strlwr(p);
                    number2 = Stopw(p, stop, number1);
                    if (number2 == 0) {
                        if (strncmp(p, "A", 1) >= 0) {
                            if (strrchr(p, '.') != NULL) {
                                p[strlen(p) - 1] = '\0';
                            }
                            ds[n].line = m;
                            ds[n].SoLanXuatHien = 1;
                            strcpy(ds[n].word, p);
                            n++;
                        }
                    }
                    number2 = 0;
                    strcpy(q, r);
                }
            }
        }
        m++;
        free(p);
        free(q);
        free(r);
    }
    fclose(file);
    Sapxep(n);
    // for (int i = 0; i < 5; i++) {
    //     if (strcmp(ds[i].word, "\n") == 0)
    //         continue;
    //     else
    //         printf("Word: %20s \t Line: %d\t So lan xuat hien: %d\n", ds[i].word, ds[i].line, ds[i].SoLanXuatHien);
    // }
    
    strcpy(hThi[0].word, ds[0].word);
    sprintf(temp, "%d", ds[0].SoLanXuatHien);
    strcat(hThi[0].stringLine, temp);
    sprintf(temp, "%d", ds[0].line);
    strcat(hThi[0].stringLine, ", ");
    strcat(hThi[0].stringLine, temp);
    number++;
    // printf("%s \t %s", hThi[0].word, hThi[0].stringLine);
    for (int i = 1; i < n; i++) {
        int temp1;
        for (int j = 0; j < number; j++) {
            if (strcmp(ds[i].word, hThi[j].word) == 0) {
                sprintf(temp, "%d", ds[i].line);
                strcat(hThi[j].stringLine, ", ");
                strcat(hThi[j].stringLine, temp);
                temp1 = 1;
            }
            else {
                temp1 = 0;
            }
        }
        if (temp1 == 0) {
            strcpy(hThi[number].word, ds[i].word);
            sprintf(temp, "%d", ds[i].SoLanXuatHien);
            strcat(hThi[number].stringLine, temp);
            sprintf(temp, "%d", ds[i].line);
            strcat(hThi[number].stringLine, ", ");
            strcat(hThi[number].stringLine, temp);
            number++;
        }
    }
    
    for (int i = 0; i < number; i++) {
        printf("%-20s \t %s\n", hThi[i].word, hThi[i].stringLine);
    }
    free(c);
}