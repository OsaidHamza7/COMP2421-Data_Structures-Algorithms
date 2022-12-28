#include <string.h>
#include <stdio.h>
#include <malloc.h>
#define INF 1000
int MAX;
typedef struct City
{
    char name[50];
    struct node* next;
} city;
//////////////////////
int Dijkstra2(int graph[][MAX], int n, int t,char cities [][50],int D);
int PrintShortPath(int a[],char cities[][50],int d);
int CHECK(struct City *L,char name[50]);
void PrintDistances(int dist[],char cities[5][50],int src);
struct City* Find(char name[50],struct City*L);
void InsertBegin2(struct City *L,struct City *temp);
void PrintGraph(int graph[][MAX],char cities[][50]);
int name(char a[][50],char name[]);
int column(char a[][50],char name[]);
int row(char s[][50],char name[]);
void DijkstraAlgo(int Graph[][MAX], int n, int start,char cities [][50]);
////////////////////////////////////////////////////////////////
int main()
{
    city* cy;
    cy=(city*)malloc(sizeof(struct City));
    cy->next=NULL;
    int i=0,d,size=0,n,u;
    char name1[50], name2[50],c[30][50], r[30][50];
    FILE *CitiesFile;
    CitiesFile = fopen("cities.txt", "r");
    while (!feof(CitiesFile))
    {
        fscanf(CitiesFile, "%[^\t]\t%[^\t]\t%dkm", name1, name2, &d);
        fgetc(CitiesFile);
        int s = CHECK(cy, name1);
        if (!s)
        {
            strcpy(c[i], name1);
            strcpy(r[i], name1);
            i++;
            size++;
        }
        int s2 = CHECK(cy, name2);
        if (!s2)
        {
            strcpy(c[i], name2);
            strcpy(r[i], name2);
            i++;
            size++;
        }
    }
    n=size+1;
    MAX=size;
    int graph[size][size];
    for(int x=0; x<size; x++)
    {
        for(int y=0; y<size; y++)
            graph[x][y]=0;
    }
    int choice;
    int s;
    while(1) {
        printf("\n                MENU                             \n");
        printf(" 1. Load cities: \n");
        printf(" 2. Enter source city:  \n");
        printf(" 3. Enter destination city:\n");
        printf(" 4.Exit       \n");
        printf("Enter your choice:");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                CitiesFile = fopen("cities.txt", "r");
                while (!feof(CitiesFile))
                {
                    fscanf(CitiesFile, "%[^\t]\t%[^\t]\t%dkm", name1, name2, &d);
                    fgetc(CitiesFile);
                    int col = column(c, name1);
                    int ro = row(r, name2);
                    if (ro != -1 && col != -1)
                        graph[col][ro] = d;
                }
                printf("Loaded cities was done.\nAnd Their graph is:\n");
                printf("----------------------------------------------------------------------------------------------------------\n");
                PrintGraph(graph,c);
                break;
            case 2:
                printf("Enter Source City:");
                int ver;
                char city[50];
                scanf("%s",city);
                int found=name(c,city);
                if(!found)
                {
                    printf("Not found City,please try again\n");
                    break;
                }
                else
                {
                    ver = column(c, city);
                }
                printf("The single source shortest path:\n");
                printf("----------------------------------------------------------------------------------------------------------\n");
                DijkstraAlgo(graph, n, ver,c);
                printf("----------------------------------------------------------------------------------------------------------\n");
                break;
            case 3:
                printf("Enter Destination City:");
                int D;
                char city2[50];
                scanf("%s",city2);
                int found2=name(c,city2);
                if(!found2)
                {
                    printf("Not found City,please try again\n");
                    return 0;
                }
                else
                {
                    D = column(c, city2);
                }
                 s= Dijkstra2(graph,n,ver,c,D);
                break;
            case 4:
                printf("\n");
                FILE *fptr;
                fptr = fopen("shortest_path.txt","w");
                fprintf(fptr,"Shortest Path from Source City\n");
               fprintf(fptr,"\t%d",s);
                printf("Save Information in a new file is done,Thank You ^_^\n");
                fclose(fptr);
                exit(0);
        }
    }

    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintGraph(int graph[MAX][MAX],char cities[][50])//function that print the graph in this project which it 2-d array
{
    for (int g = 0; g < MAX; g++)
    {
        for (int h = 0; h < MAX; h++)
        {
            printf("%d\t ", graph[g][h]);
        }
        printf("\n");
    }
    printf("----------------------------------------------------------------------------------------------------------\n");
}
struct City* Find(char name[50],struct City*L)//function find city in linked list
{
    struct City* p=NULL;
    if(L->next!=NULL)
    {
        p=L->next;
        while(p!=NULL && strcmp(p->name,name)!=0)//while not found city
        {
            p=p->next;
        }
    }
    return p;
}
void InsertBegin2(struct City*L,struct City*temp)//function that add city into linked list of cities
{
    if(L!=NULL && temp!=NULL)//check if not equal NULL
    {
        temp->next= L->next;//to insert in begin of linked list
        L->next=temp;
    }
    else
    {
        printf("NULL,can't Insert ");
    }
}
int CHECK(struct City *L,char name[50])//function that check if city is found in linked list(for cities)
{
    if(L!=NULL)
    {
        city* p;//node of city
        p=(city*)malloc(sizeof(struct City));
        p=Find(name,L);//find this node of city
        if(p!=NULL)
            return 1;//if the city is exist then return 1 and don't do anything because the city is already in linked list for cities
        else
        {
            city* temp;
            temp=(city*)malloc(sizeof(struct City));
            temp->next=NULL;
            strcpy(temp->name,name);//copy name of city to new node to add in linked list
            InsertBegin2(L,temp);
            return 0;
        }
    }
    else
    {
        printf("NULL");
    }

}

int name(char a[][50],char name[])//check if name of city found in cities or not
{
    for(int i=0; i<MAX; i++)
    {
        if(strcmp(a[i],name)==0)//check if found name of city
            return 1;//return 1 if found city
    }
    return 0;//return zero if the city is not exist
}
int column(char a[][50],char name[])//function that check if the name of city is found in cities in column of graph
{
    for(int i=0; i<MAX; i++)
    {
        if(strcmp(a[i],name)==0)//check if name of city who enter have the same name of cities in array s that represent cities
            return i;//return index of name of city if found
    }
    return -1;//return -1 if not found city in array of cities

}
int row(char s[][50],char name[])//function that check if the name of city is found in cities in row of graph
{
    for(int i=0; i<MAX; i++)
    {
        if(strcmp(s[i],name)==0)//check if name of city who enter have the same name of cities in array s that represent cities
            return i;//return index of name of city if found
    }
    return -1;//return -1 if not found city in array of cities
}
void DijkstraAlgo(int graph[][MAX], int n, int t,char cities [][50])
{
    int c[MAX][MAX], d[MAX], e[MAX];//declare variables
    int v[MAX], y, min, x, i, j;//declare variables
    for (i = 0; i < n; i++) {//loop to put every distances betweem cities in new array named
                                   // c (2-d)and if there is empty distance put it to invenity
        for (j = 0; j < n; j++) {
            if (graph[i][j] == 0) {
                c[i][j] = INF;//make distance invenity
            }
            else {
                c[i][j] = graph[i][j];//make distance like distance in the graph
            }
        }
    }
    for (i = 0; i < n; i++)//
    {
        d[i] = c[t][i];
        e[i] = t;
        v[i] = 0;
    }
    d[t] = 0;
    v[t] = 1;
    y = 1;
    while (y < n - 1)
    {
        min = INF;
        for (i = 0; i < n; i++)
            if (d[i] < min && !v[i])
            {
                min = d[i];
                x = i;
            }
        v[x] = 1;
        for (i = 0; i < n; i++)
            if (!v[i])
                if (min + c[x][i] < d[i])
                {
                    d[i] = min + c[x][i];
                    e[i] = x;
                }
        y++;
    }
    PrintDistances(d,cities,t);//function that print short paths between source city and every another city
}
char* GetCity(char s[][50],int  index)
{
    return s[index];//return name of city have the same index
}
void PrintDistances(int a[],char cities[][50],int f)
{
    char* c;
    printf("Destination \t\t Distance from Source\n");
    for (int i = 0; i < MAX; i++)
    {
        c= GetCity(cities,i);//get name of city have same index
        if(strcmp(c,GetCity(cities,f))!=0)//check if the city who got by function is equal to source city
        {
            printf("%s    \t\t %d\n", c, a[i]);
        }
    }
}
int PrintShortPath(int a[],char cities[][50],int d)
{
    char* D;
    printf("Destination \t\t Distance from Source\n");
   D =GetCity(cities,d);
            printf("%s    \t\t %d\n",D, a[d]);
return a[d];
}
int Dijkstra2(int graph[][MAX], int n, int t,char cities [][50],int D)
{
    int c[MAX][MAX], d[MAX], e[MAX];//declare variables
    int v[MAX], y, min, x, i, j;//declare variables
    for (i = 0; i < n; i++) {//loop to put every distances betweem cities in new array named
        // c (2-d)and if there is empty distance put it to invenity
        for (j = 0; j < n; j++) {
            if (graph[i][j] == 0) {
                c[i][j] = INF;//make distance invenity
            }
            else {
                c[i][j] = graph[i][j];//make distance like distance in the graph
            }
        }
    }
    for (i = 0; i < n; i++)//
    {
        d[i] = c[t][i];
        e[i] = t;
        v[i] = 0;
    }
    d[t] = 0;
    v[t] = 1;
    y = 1;
    while (y < n - 1)
    {
        min = INF;
        for (i = 0; i < n; i++)
            if (d[i] < min && !v[i])
            {
                min = d[i];
                x = i;
            }
        v[x] = 1;
        for (i = 0; i < n; i++)
            if (!v[i])
                if (min + c[x][i] < d[i])
                {
                    d[i] = min + c[x][i];
                    e[i] = x;
                }
        y++;
    }
  int ss=  PrintShortPath(d,cities,D);//function that print short paths between source city and every another city
  return ss;
}




