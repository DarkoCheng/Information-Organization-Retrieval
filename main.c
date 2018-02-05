#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/*
In: none.
Out: none.
Post: read information file, create 2 disk files, data.bin and index.bin.
*/
void createBinary();

int main()
{
    createBinary();
    return 0;
}

void createBinary()
{
    FILE * fp;
    fp = fopen("infor.txt", "r");
    if (fp == NULL)
    {
        printf("Failt to open file1.\n");
        exit(1);
    }
    char * infor;
    infor = malloc(10240);
    if (infor == NULL)
    {
        printf("Fail to malloc!\n");
        exit(1);
    }
    else
    {
        memset(infor, 0, 10240);
    }
    char * token;
    int counter;
    counter = 0;
    int binaryIndex;
    binaryIndex = open("index.bin", O_WRONLY | O_APPEND | O_CREAT, 0751);
    if (binaryIndex < 0)
    {
        printf("Unable to create binary file2.\n");
        free(infor);
        fclose(fp);
        exit(1);
    }
    int binary;
    binary = open("data.bin", O_WRONLY | O_CREAT, 0751);
    if (binary < 0)
    {
        printf("Unable to create binary file3.\n");
        free(infor);
        exit(1);
    }

    fgets(infor, 10240, fp);
    memset(infor, 0, 10240);
    write(binary, "index.bin", strlen("index.bin"));
    write(binary, "|",  sizeof(char));
    lseek(binary, 2, SEEK_CUR);
    write(binary, "|", sizeof(char));
    int a = 6;
    char b[10];
    sprintf(b, "%d", a);
    write(binary, b, 1);
    write(binary, "|", sizeof(char));
    write(binary, "Last_Name", strlen("Last_Name"));
    write(binary, "|", sizeof(char));
    write(binary, "First_Name",  strlen("First_Name"));
    write(binary, "|",  sizeof(char));
    write(binary, "Street_Address", strlen("Street_Address"));
    write(binary, "|",  sizeof(char));
    write(binary, "City_Name", strlen("City_Name"));
    write(binary, "|", sizeof(char));
    write(binary, "Province", strlen("Province"));
    write(binary, "|", sizeof(char));
    write(binary, "Postal_Code", strlen("Postal_Code"));
    write(binary, "|", sizeof(char));
    int length;
    length = lseek(binary, 1, 1);
    lseek(binary, -1, 1);
    write(binaryIndex, &length, sizeof(length));
    int lengthTotal;
    lengthTotal = length;
    counter = 1;
    while (fgets(infor, 10240, fp) != NULL)
    {
        token = strtok(infor, ":");
        token = strtok(NULL, ":");
        write(binary, token, strlen(token)-2);
        write(binary, "|", sizeof(char));
        lengthTotal = lengthTotal + strlen(token) - 2;
        lengthTotal++;
        if (counter%6 == 0 && counter != 0)
        {
            write(binaryIndex, &lengthTotal, sizeof(int));
        }
        counter++;
        memset(infor, 0, 10240);
    }
    counter = counter/6;
    lseek(binary, strlen("index.bin|"), SEEK_SET);
    char string[10];
    sprintf(string, "%d", counter);
    write(binary, string, 2);

    free(infor);
    close(binary);
    close(binaryIndex);
    fclose(fp);

    return;
}
