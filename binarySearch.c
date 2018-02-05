#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/*
In: User input string.
Out: converted string
Post: convert uppercase to lower case after first char for searching
*/
char * toLower(char * user);

/*
In: int array that stored index number, and length indicater.
Out: none.
Post: Read index binary file and store in array.
*/
void readBinary(int * array, int * length);

/*
In: array that stored index and length of array.
Out: Print infor to std out.
Post: Do the binary search.
*/
int binarySearch(int * array, int length, char * search);

/*
In: position in data binary file.
Out: return string of connected name.
Post: based on postion search in data file.
*/
char * returnName(char * name, int position);

/*
In: index array and location of founded record.
Out: None.
Post: print out the whole record based on the location.
*/
void printInfor(int * array, int location);

int main()
{
    char * user;
    char * key;
    key = malloc(10240);
    memset(key, 0, 10240);
    int array[30];
    int length;
    readBinary(array, &length);
    if (key == NULL)
    {
        printf("Failt to malloc.\n");
        return 1;
    }
    user = malloc(10240);
    if (user == NULL)
    {
        printf("Failt to malloc.\n");
        return 1;
    }
    printf("Please enter the key or Q for quit:");
    scanf(" %s", key);
    int found;
    found = -2;
    while (strcmp(key, "Q") != 0)
    {
        strcpy(user, toLower(key));
        found = binarySearch(array, length, user);
        if (found == -1)
        {
            printf("Not found Item in list.\n");
        }
        else
        {
            printInfor(array, found);
        }
        memset(user, 0, 10240);
        memset(key, 0, 10240);
        printf("Please enter another key or Q for quit:");
        scanf(" %s", key);
    }

    free(key);
    free(user);
    return 0;
 }

int binarySearch(int * array, int length, char * search)
{
    int first;
    int last;
    int middle;
    first = 0;
    last = length - 1;
    middle = (first+last)/2;
    char * name;
    name = malloc(10240);
    while (first <= last)
    {
        if (strcmp(toLower(returnName(name, array[middle])), toLower(search)) < 0) // change to coompare string in data binary
        {
            first = middle + 1;
        }
        else if (strcmp(toLower(returnName(name, array[middle])), toLower(search)) == 0)  // change to compare string in data file.
        {
             break;
        }
        else
        {
            last = middle - 1;
        }
          middle = (first + last)/2;
    }
    if (first > last)
    {
        middle = -2;
    }
    free(name);
    return middle + 1;
}

char * returnName(char * string, int position)
{
    int fp;
    fp = 0;
    int error;
    error = 1;
    fp = open("data.bin", O_RDONLY, 0751);
    int counter;
    counter = 0;
    if (fp < 0)
    {
        printf("Unable to read binary file.\n");
        exit(1);
    }
    int counterDeli;
    counterDeli = 0;
    lseek(fp, position-1, SEEK_SET);
    do
    {
        error = read(fp, string+counter, 1);
        if (string[counter] == '|')
        {
            counterDeli++;
            counter--;
        }
        if (counterDeli == 2)
        {
            break;
        }
        counter++;
    }while(error != 0);
    string[counter+1] = '\0';
    counterDeli = 0;
    counter = 0;
    close(fp);
    return string;
}

void readBinary(int * array, int * length)
{
    int fp;
    fp = open("index.bin", O_RDONLY, 0751);
    if (fp < 0)
    {
        printf("Unable to read binary file.\n");
        exit(1);
    }
    int error;
    error = 1;
    int counter;
    counter = 0;
    while(error != 0)
    {
        error = read(fp, &array[counter], 4);
        counter++;
    }
    *length = counter-1;
    close(fp);
    return;
}

 char * toLower(char * user)
{
    int i;
    for(i=0;i<=strlen(user);i++)
    {
        if(user[i]>=65 && user[i]<=92)
        {
            user[i]=user[i]+32;
        }
    }
    return user;
 }

 void printInfor(int * array, int location)
 {
    int fp;
    fp = open("data.bin", O_RDONLY, 0751);
    if (fp < 0)
    {
        printf("Unable to read binary file.\n");
        exit(1);
    }
    int length;
    length = array[location] - array[location-1];
    int counter;
    counter = 0;
    char * out;
    out = malloc(10240);
    memset(out, 0, 10240);
    lseek(fp, array[location-1]-1, SEEK_SET);
    while(counter < length-1)
    {
        read(fp, out+counter, 1);
        counter++;
    }
    out[counter+1] = '\0';
    char * token;
    token = strtok(out, "|");
    printf("\nLast Name: %s\n", token);
    token = strtok(NULL, "|");
    printf("First Name: %s\n", token);
    token = strtok(NULL, "|");
    printf("Street Address: %s\n", token);
    token = strtok(NULL, "|");
    printf("City Name: %s\n", token);
    token = strtok(NULL, "|");
    printf("Province: %s\n", token);
    token = strtok(NULL, "|");
    printf("Postal Code: %s\n\n", token);
    free(out);
    close(fp);
    return;
 }
