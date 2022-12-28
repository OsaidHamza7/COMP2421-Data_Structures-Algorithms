//P3_1200875_OSAIDHAMZA_1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max_size 23

typedef struct node//structure node for courses in this program.
{
    char Course [50];//Course name.
    int CreditHours;//Credit hours.
    char CourseCode[50];//Course code.
    char Department[50];//Department name.
    char Topic[100];//pointer for structure node1(for topics in courses)
}Course;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int hash(int num,int size)
{
    return (int)(num%size);//hash function (return an index)
}
int hash2(int num,int size)
{
    return (7-(num%7));//hash2 function (return an index)
}
int as(char *key,int size)//ascii function (return an index)
{
    int index=0;
    while(*key!='\0')//while string not equal zero(NULL)
        index+=*key++;
    return index;
}
int DoubleHash(Course array[],Course course,int size)//Double Hash function return index for course name
{
    int num=as(course.Course,size);//give the integer value of course name
    int i;
    int s=0;
    int collision=0;
    for(i=0; i<size; i++)
    {
        int index = (hash(num,size) + i * hash2(num,size)) %size;//found index of course name
        if(strcmp(array[index].Course,"") == 0)//check if there is space in array that represent double hashing table
        {
            strcpy(array[index].Course,course.Course);
            strcpy(array[index].CourseCode,course.CourseCode);
            strcpy(array[index].Department,course.Department);
            array[index].CreditHours=course.CreditHours;
            strcpy(array[index].Topic,course.Topic);
            printf("index=%d\n",index);
            s=1;
            break;
        }
        collision++;
    }
    printf("collision=%d\n",collision);
    if(s==0)
        printf("cant insert!\n");
    return collision;
}

int LinearHash(Course array[],Course course,int size)//Linear Hash function return index for course name
{
    int num=as(course.Course,size);//give the integer value of course name
    int i;
    int s=0;
    int collision=0;
    for(i=0; i<size; i++)
    {
        int index = (num+i)%size;//found index of course name
        if(strcmp(array[index].Course,"") == 0)//check if there is space in array that represent double hashing table
        {
            strcpy(array[index].Course,course.Course);
            strcpy(array[index].CourseCode,course.CourseCode);
            strcpy(array[index].Department,course.Department);
            array[index].CreditHours=course.CreditHours;
            strcpy(array[index].Topic,course.Topic);
            printf("index=%d\n",index);
            s=1;
            break;
        }
        collision++;
    }
    printf("collision=%d\n",collision);
    if(s==0){
        printf("cant insert!\n");}
return collision;
}
/*void insert(int array[],int num,int size)
{
    int h=hash(num,size);
    if(array[h]!=NULL)
        printf("Cant insert!!\n");
    else
        array[h]=num;
}
*/
/*int HASH(char *key,int size)
{
    int index=0;
    while(*key!='\0')
        index=(index<<5)+*key++;
    return index;
}*/

int* LoadCoursesIntoHashingTable(Course array1[Max_size], Course array2[Max_size])//function that load all courses in file(courses.txt) to hashing table (Linear and Double)
{
    static int array[1];
    int count=0;int count2=0;
        FILE *coursesFile;//Create pointer to the input file.
        coursesFile=fopen("courses.txt","r");//open a file named(courses) to read from it.
        if(coursesFile!=NULL)//Check if the pointer points to NULL.
        {
            while(!feof(coursesFile))//Check if there is courses in file(courses.txt)
            {
                Course r;//creat a struct node(Course) to insert into two hashing tables
                fscanf(coursesFile,"%[^:]:%d#%[^#]#%[^/]/%[^\n]",r.Course,&r.CreditHours,r.CourseCode,r.Department,r.Topic);//filling information in file to Course which defined
               fgetc(coursesFile);
             count+=LinearHash(array1, r,Max_size);//count that points to number of collisions in linear hashing table
               count2+=DoubleHash(array2,r,Max_size);//count2 that points to number of collisions in double hashing table
            }
            printf("Load courses Into Hashing Tables(Linear And Double) Is Done\n\n");//Print this for user to ensure that the reading operation is done.
            fclose(coursesFile);//Close the file.
        }
        else
        {
            printf("Not Found  courses File,please create a  courses file and try again\n");//print it when not found the file.
        }
  array[0]=count;
  array[1]=count2;
  return array;
}

int* insertCourse(Course array1[],Course array2[],int n[])//function that insert a new course entered from user int two hashing table
{
    static int s[1];
            Course r;
            printf("enter information of new course:");
            getchar();//to put buffer zero
            scanf("%[^:]:%d#%[^#]#%[^/]/%[^\n]",r.Course,&r.CreditHours,r.CourseCode,r.Department,r.Topic);//get information of new course from user
            n[0]+=LinearHash(array1, r,Max_size);//insert into Linear Hashing Table
            n[1]+=DoubleHash(array2,r,Max_size);//insert into Double Hashing Table
            s[0]=n[0];
            s[1]=n[1];
            return s;
}

void SearchCourse(Course array1[Max_size],Course array2[Max_size])//function that search a course name in one of two hashing tables
{
  char name[50];//course name from user
  int k;
    printf("enter a course do you want to search:\n");
    getchar();
    gets(name);
    printf("specify which table to search in:\n");
    printf("1.LinearHash\n");
    printf("2.DoubleHash\n");
    scanf("%d",&k);
    if(k==1)//insert into linear hashing table
    {
        int num=as(name,Max_size);//get value of course name in integer
        int i=0;
        int s=0;
        int collision=0;
        int index;
            for (i = 0; i < Max_size; i++) {
               index = (num+i)%Max_size;//get index of course name in linear hashing table
                if (strcmp(array1[index].Course, name) == 0) {//check if found course name in linear hashing table or not
                    printf("found at index=%d\n", index);
                    printf("course name:%s\tcourse code:%s\n",array1[index].Course,array1[index].CourseCode);
                    s = 1;
                    break;
                }
                collision++;
            }
            printf("collision=%d\n", collision);
            if (s == 0)
                printf("Not Found! at Linear Hashing Tabel\n");
    }
    else if (k==2)
    {
        int num=as(name,Max_size);//get value of course name in intege
        int i;
        int s=0;
        int collision=0;
        int index;
        for(i=0; i<Max_size; i++)
        {
            index = (hash(num,Max_size) + i * hash2(num,Max_size)) %Max_size;//get index of course name in double hashing table
            if(strcmp(array2[index].Course,name) == 0)//check if found course name in linear hashing table or not
            {
                printf("Found at index=%d\n",index);
                printf("course name:%s\tcourse code:%s\n",array2[index].Course,array2[index].CourseCode);
                s=1;
                break;
            }
            collision++;
        }
        printf("collision=%d\n",collision);
        if(s==0)
            printf("Not Found! at Double Hashing Table\n");
    }
}

void DeleteCourse(Course arrayL[],Course arrayD[])//function that delete a course in two hashing tables according a course name entered from user
{
   char name[50];//course name who want to delete
    printf("enter course that you want to delete:");
    getchar();
gets(name);
    int num=as(name,Max_size);
    int i=0;
    int s=0;
    int collision=0;
    int index;
    for (i = 0; i < Max_size; i++) {
        index = (num + i) % Max_size;//get index of course name in linear hashing table
            if (strcmp(arrayL[index].Course, name) == 0) {//check if found course name in linear hashing table or not
                printf("found in linear hash table at index=%d\n", index);
                strcpy(arrayL[index].Course, "");//make it empty(deleted)
                printf("The course has been deleted from linear hash table\n");
                s = 1;
                break;
            }
            collision++;
        }
        printf("collision=%d\n", collision);
        if (s == 0)
            printf("Not Found! at Linear Hashing Table\n");
printf("------------------------------------------------------------------------------\n");
   int num2=as(name,Max_size);
    int j=0;
    int c=0;
    int collision2=0;
    int index2;
    for (j= 0; j < Max_size; j++) {
        index2 = (hash(num2,Max_size) + j * hash2(num2,Max_size)) %Max_size;//get index of course name in double hashing table

            if (strcmp(arrayD[index2].Course, name) == 0) {//check if found course name in linear hashing table or not
                printf("found in double hash table at index=%d\n", index2);
                strcpy(arrayD[index2].Course, "");//make it empty(deleted)
                printf("The course has been deleted from Double hash table\n");
                c = 1;
                break;
            }

        collision2++;
    }
    printf("collision=%d\n", collision2);
    if (c== 0)
        printf("Not Found! at Double Hashing Table\n");
    printf("------------------------------------------------------------------------------\n");
}

void SaveHashTable(Course arrayD[])//save all courses in hashing tables into a new file named(saved_courses.txt)
{
    FILE *fptr;//pointer to file
    fptr=fopen("saved_courses.txt","w");//open a file that will write in
    if( fptr!=NULL) //Check that the pointer to file not equal NULL.
        {
        for(int i=0;i<Max_size;i++)
        {
            if(strcmp(arrayD[i].Course,"")!=0)
                //print information of courses into a new file(saved_courses.txt)
            fprintf(fptr,"index=%d\tcourse name:%s\tcourse code:%s\tCreditHours:%d\tcourse Department:%s\t course topics:%s\n",i,arrayD[i].Course,arrayD[i].CourseCode,arrayD[i].CreditHours,arrayD[i].Department,arrayD[i].Topic);
            else
                fprintf(fptr,"index=%d\tname:NULL\n",i);
        }
        }
printf("save courses into file done");
    fclose(fptr);
}

int NumberOfElementsD(Course arrayD[])
{
    int count=0;
   for(int i=0;i<Max_size;i++)
   {
       if(strcmp(arrayD[i].Course,"")!=0)
           count++;
   }
    return count;
}
int NumberOfElementsL(Course arrayL[])
{
    int count=0;
    for(int i=0;i<Max_size;i++)
    {
        if(strcmp(arrayL[i].Course,"")!=0)
            count++;
    }
    return count;
}

int main() {
    Course arrayD[Max_size] = {NULL};
    Course arrayL[Max_size] = {NULL};
    int choice;
    FILE *fptr;
    int *n;int *s;
    while (1) {//Print the menu for user.
        printf("\n             MENU                             \n");
        printf("1.Print hashed tables (including empty spots).  \n");
        printf("2.Print out table size and the load factor. \n");
        printf("3.Print out the used hash functions. \n");
        printf("4.Insert a new record to hash table (insertion will be done on both hash tables). \n");
        printf("5.Search for a specific word (specify which table to search in). \n");
        printf("6.Delete a specific record (from both tables).\n");
        printf("7.Compare between the two methods in terms of number of collisions occurred.\n");
        printf("8.Save hash table back to a file named saved_courses.txt (of the double hashing)\n");
        printf("9.Exit\n");
        printf("Enter your choice:\n");//Print this to enter the choice.
        scanf("%d", &choice);//Scan the choice.
        switch (choice)//Make switch statements on the choice.
        {
            case 1://If option 1 selected.
            printf("\n");

                n=LoadCoursesIntoHashingTable(arrayL, arrayD);
                s=n;
                printf("\n*********************************************************\n");
                printf("LinearHash Tabel:\n");
                printf("--------------------------------\n");
                for (int i = 0; i < Max_size; i++) {
                    if (strcmp(arrayL[i].Course, "") == 0)
                        printf("at index %d  Name=%s\n", i, "NULL");
                    else {
                        printf("at index %d  Name=%s\n", i, arrayL[i].Course);
                    }
                }
                printf("--------------------------------\n\n");
                printf("DoubleHash Tabel:\n");
                printf("--------------------------------\n");
                for (int i = 0; i < Max_size; i++) {
                    if (strcmp(arrayD[i].Course, "") == 0)
                        printf("at index %d  Name=%s\n", i, "NULL");
                    else
                        printf("at index %d  Name=%s\n", i, arrayD[i].Course);
                }
                printf("--------------------------------\n");
                printf("\n*********************************************************\n");
                break;

            case 2:
                printf("\n");
                int numD=NumberOfElementsD(arrayD);
                int numL=NumberOfElementsL(arrayL);
                printf("Linear Hash Table:\n");
                printf("size of linear hash table:%d\n",(int)(sizeof(arrayL) / sizeof(arrayL[0]) ));
                printf("Number of elements in linear hash table:%d\n",numL);
                printf("Load Factor of linear hash table:%d%\n",numL*100/(int)(sizeof(arrayL) / sizeof(arrayL[0]) ));
                printf("----------------------------------------------------------------------------------------------\n");
                printf("Double Hash Table:\n");
                printf("size of Double hash table:%d\n",(int)(sizeof(arrayD) / sizeof(arrayD[0]) ));
                printf("Number of elements in Double hash table:%d\n",numD);
                printf("Load Factor of double hash table:%d%\n",numD*100/(int)(sizeof(arrayL) / sizeof(arrayL[0]) ));
                printf("----------------------------------------------------------------------------------------------\n");
                break;

            case 3:
                printf("I USED Hashing String First Type (ASCII) By Linear Hashing\n");
                break;

            case 4:
                printf("\n");
                s=insertCourse(arrayL, arrayD,n);
               printf("\n***************\n");
                printf("LinarHash Tabel:\n");
                printf("--------------------------------\n");
                for (int i = 0; i < Max_size; i++) {
                    if (strcmp(arrayL[i].Course, "") == 0)
                        printf("at index %d  Name=%s\n", i, "NULL");
                    else {
                        printf("at index %d  Name=%s\n", i, arrayL[i].Course);
                    }
                }
                printf("--------------------------------\n\n");

                printf("DoubleHash Tabel:\n");
                printf("--------------------------------\n");
                for (int i = 0; i < Max_size; i++) {
                    if (strcmp(arrayD[i].Course, "") == 0)
                        printf("at index %d  Name=%s\n", i, "NULL");
                    else
                        printf("at index %d  Name=%s\n", i, arrayD[i].Course);
                }
                printf("--------------------------------\n");
                printf("\n****************\n");
                break;
            case 5:
                SearchCourse(arrayL, arrayD);
                break;
            case 6:
                DeleteCourse(arrayL,arrayD);
                break;
            case 7:
                printf("number of collisions at linearHashing=%d\n",s[0]);
                printf("number of collisions at DoubleHashing=%d\n",s[1]);
                if(s[0]>s[1])
                    printf("number of collisions at Linear Hashing Table > number of collisions at Double Hashing Table \n");
           else if(s[0]<s[1])
                    printf("number of collisions at Double Hashing Table > number of collisions at Linear Hashing Table \n");
           else
                    printf("number of collisions at Linear Hashing Table = number of collisions at Double Hashing Table \n");


                break;

            case 8:
                SaveHashTable(arrayD);
                break;
            case 9:
                exit(0);
            default://Default case.
                printf("\nWrong Choice,please read the file and create the tree\n");
                break;
        }
    }
    return 0;
}
//END prject3