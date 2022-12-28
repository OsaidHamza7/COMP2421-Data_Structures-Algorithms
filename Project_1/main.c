#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Student Name:Osaid Hamza
// Student ID:1200875
// Section:1

typedef struct node1  //creat a struct type of passenger
{
    int id;
    int date1;
    char time1[50];
    char from1 [50];
    char to1[50];
    struct node1* next;

} passenger;
//----------------------------------
typedef struct node2  //creat a struct type of busses
{
    int num;
    int date2;
    char time2[50];
    char from2 [50];
    char to2[50];
    int price;
    int capacity;
    struct node2* nextBus;
    struct node1* nextPass;
} busses;

//---------------------------------------------------------------
void InsertBegin(struct node2*L,struct node2*temp);
void InsertBegin2(struct node1*L,struct node1*temp);
void InsertBegin3(struct node2*L,struct node1*temp);
void PrintList(struct node2* L);
void PrintList2(struct node1* L);
void PrintList5(struct node2* L);
void Printt(struct node2* L);
struct node2* FindPrevious(int x,struct node2*L);
struct node2* Find(int x,struct node2*L);
struct node1* FindPrevious2(struct node1*L,struct node1*s);
//------------------------------------------------------------------------
void LoadBusses(struct node2* b);
void LoadPassengers(struct node1* p);
void AssignPassengers(struct node2*b,struct node1*p,struct node1* um);
void PrintSpecificBus(struct node2*b);
void AddPassenger(struct node2* b,struct node1* um);
void DeleteBusNumber(struct node2*b,struct node1* um);
void DeletePassenger(struct node2*b);

//-------------------------------------------------------------------------
int main()

{
    passenger* LinkedPassengers;//define a Head linked list for passengers
    LinkedPassengers=(passenger*) malloc(sizeof(passenger));//define it in memory as malloc
    LinkedPassengers->next=NULL;//make linked list for passengers is empty
    busses* LinkedBusses;//define a Head linked list for busses
    LinkedBusses=(busses*) malloc(sizeof(busses));//define it in memory as malloc
    LinkedBusses->nextPass=NULL;//next passenger of Head is NULL
    LinkedBusses->nextBus=NULL;//make a linked list for busses is empty (next bus of Head is NULL)
    passenger* LinkedUnMatchedPassengers;//define a Head of linked list for passengers who unmatched with anybusses
    LinkedUnMatchedPassengers=(passenger*) malloc(sizeof(passenger));//define it in memory as malloc
    LinkedUnMatchedPassengers->next=NULL;//make a linked list for unmatched passengers is empty

    int i,f=2;//define a variable i that mean yout choice,and define a variable f equal two
    while(f>0)
    {
        printf("\n                MENU                             \n");
        printf(" 1.Load the bus information file    \n");
        printf(" 2.Load the passenger information file    \n");
        printf("Enter your choice:");
        scanf("%d",&i);
        switch(i)
        {
        case 1:
            LoadBusses(LinkedBusses);//call function named LoadBusses,it load all busses into a linked list named LinkedBusses
            PrintList(LinkedBusses);//print informations of all busses that load to linked list named LinkedBusses
            f--;

            break;
        case 2:
            LoadPassengers(LinkedPassengers);//call function named LoadPassengers,it load all passengers into a linked list named LinkedPassengers
            PrintList2(LinkedPassengers);//print informations of all Passengers that load to linked list named LinkedPassengers
            f--;
            break;

        default:
            printf("Wrong Choice,please try again");//print it when you enter anynumber except 1 and 2
            break;
        }
    }
//------------------------------------------------------------------------------------------------------------------
    int choice;
    while(1)
    {
        printf("\n                MENU                             \n");
        // printf(" 1.Load the bus information file    \n");
        //printf(" 2.Load the passenger information file    \n");
        printf(" 3.Assign passengers and print assignment information of all busses    \n");
        printf(" 4.Print a specific bus information along with its passengers information (names and IDs)   \n");
        printf(" 5.Print unmatched passengers    \n");
        printf(" 6.Add new passenger\n");
        printf(" 7.Delete passenger   \n");
        printf(" 8.Delete bus number   \n");
        printf(" 9.Exit       \n");
        printf("Enter your choice:");
        scanf("%d",&choice);

        switch(choice)
        {
        /*case 1:
            LoadBusses(LinkedBusses);
            PrintList(LinkedBusses);
            break;
        case 2:
            LoadPassengers(LinkedPassengers);
            PrintList2(LinkedPassengers);
            break;*/
        case 3:
            AssignPassengers(LinkedBusses,LinkedPassengers,LinkedUnMatchedPassengers);//call function named AssignPassengers
            PrintList5(LinkedBusses);//print all busses with all passengers in them
            break;
        case 4:
            PrintSpecificBus(LinkedBusses);//call a function named PrintSpecificBus and it print the informations of specific bus in LinkedBusses that you want
            break;
        case 5:
            printf("\nThe UnMatched Passengers Informations:\n");
            PrintList2(LinkedUnMatchedPassengers);//print all passengers informations that not found a bus agreed with
            break;
        case 6:
            AddPassenger(LinkedBusses,LinkedUnMatchedPassengers);//call function named AddPassenger,it can add any passenger do you want whether in busses or in linked list of unmatched passenger
            break;
        case 7:
            DeletePassenger(LinkedBusses);//call function named DeletePasssenger,it delete a passenger where that found whether in busses or in linked list of unmatched passenger
            break;
        case 8:
            DeleteBusNumber(LinkedBusses,LinkedUnMatchedPassengers);//call function named DeleteBusNumber ,it delete a bus according to number of bus
            break;
        case 9:
            exit(0);
            break;

        default:
            printf("Wrong Choice,please try again");
            break;
        }

    }

    return 0;
}

//----------------------------------------------------------------------------------------------
void LoadBusses(struct node2* L)//function named LoadBusses,it inserts all busses in file(busses.txt) into a linked list for busses
{
    if(L!=NULL)//check if the head for linked list is not NULL (in memory)
    {
        FILE *BussesFile;
        BussesFile=fopen("busses.txt","r");//open a file named busses.txt and it have all busses informations
        if(BussesFile!=NULL)//check if the file of busses is created
        {
            while(!feof(BussesFile))//check if the file of busses still have a busses
            {
                busses* b;//define a pointer of busses that have a informations of every line in file (line by line)
                b=(busses*)malloc(sizeof(busses));//define it in memory
                fscanf(BussesFile,"%d#%d#%[^#]#%[^#]#%[^#]#%d#%d",&b->num,&b->date2,b->time2,b->from2,b->to2,&b->price,&b->capacity);
                b->nextPass=NULL;//make a next passenger is NULL
                b->nextBus=NULL;//make a next bus is NULL
                InsertBegin(L,b);//insert the bus(this pointer) into a Linked list for busses from begin
            }
            printf("Load Busses Into a Linked List Is Done,And The Informations Of All Busses below:\n\n");
            fclose(BussesFile);//close a file named busses.txt and it have all busses informations
        }
        else
        {
            printf("Not Found Busses File,please creat a busses file and try again\n");//print it when not found the file
        }
    }
    else
    {
        printf("No Head to Busses its(Out Of Memory)\n");
    }
}
//------------------------------------------------------------------------------------------

void LoadPassengers(struct node1* L)//function named LoadPassengers,it inserts all Passengers in file(passengers.txt) into a linked list for passengers
{
    if(L!=NULL)//check if the head for linked list is not NULL (in memory)
    {
        FILE *PassengersFile;
        PassengersFile=fopen("passengers.txt","r");//open a file named passengers.txt and it have all passengers informations
        if(PassengersFile!=NULL)//check if the file of passengers is created
        {
            while(!feof(PassengersFile))//check if the file of busses still have a busses
            {
                passenger* p;//define a pointer of passengers that have a informations of every line in file (line by line)
                p=(passenger*)malloc(sizeof(passenger));//define it in memory
                fscanf(PassengersFile,"%d#%d#%[^#]#%[^#]#%[^\n]",&p->id,&p->date1,p->time1,p->from1,p->to1);
                p->next=NULL;//make next of passenger is NULL
                InsertBegin2(L,p);//insert the passenger(this pointer) into a Linked list for passenger from begin
            }
            printf("Load Passengers Into a Linked List Is Done,And The Informations Of All Passengers below:\n\n");
            fclose(PassengersFile);//close a file named passengers.txt and it have all passengers informations
        }
        else
        {
            printf("Not Found Passengers File,please creat a passengers file and try again\n");//print it when not found the file
        }
    }
    else
    {
        printf("No Head To passengers its(Out Of Memory)\n");
    }

}
//-----------------------------------------------------------------------------------------------

void  AssignPassengers(struct node2*b,struct node1*p,struct node1* um)
{
    int count =0;
    printf("\n");
    if(b!=NULL && p!=NULL && um!=NULL)//check if headers of linked list of busses and passengers and unmatched passengers is not NULL(in memory)
    {
        struct node2* b1;//define pointer b1
        struct node1* p1=p->next,*temp;//define pointer p1 it's pointer to first passenger,and define pointer temp
        if(p1!=NULL && b->nextBus!=NULL)//check if first passenger and first bus is not NULL(not empty linked list of busses and linked list of passengers)
        {
            while(p1!=NULL)//enter a wile loop until p1 equal a NULL (finish a linked list for passengers)
            {
                temp = p1->next;//make temp pointer to next passenger of p1, because don't lose a (next passenger) to pass all linked list for passengers
                int t=0;//define t equal zero
                b1=b->nextBus;//make b1 pointer to first bus in linked list for busses
                while(b1!=NULL)//enter a wile loop until b1 equal a NULL (finish a linked list for busses)
                {
                    //check if the passenger and the bus that have the same date,time,from travel and to where (destination) and check if the bus have a space for the passenger
                    if(p1->date1==b1->date2 && strcmp(p1->time1,b1->time2)==0 &&  strcmp(p1->from1,b1->from2)==0 &&  strcmp(p1->to1,b1->to2)==0 && b1->capacity!=0)
                    {
                        InsertBegin3(b1,p1);//insert the passenger to the bus when agreed with him
                        b1->capacity--;//reduse a capacity of the bus by one
                        t=1;//change t to one
                    }
                    b1=b1->nextBus;//pass into the next bus
                }
                if(t==0) //check if t don't change,that mean passenger not insert to any bus,so it insert to unmatched passengers
                {
                    InsertBegin2(um,p1);
                    count++;
                }//insert to unmatched passengers
                p1=temp;//pass into the next passenger
            }
            printf("Assign Passengers In Busses is Completed^-^\n");

        }
        else
        {
            printf("please load passengers and Busses\n");//print it when didn't load passengers and busses
        }
    }
    else
    {
        printf("NULL");
    }
    //printf("\n%d\n",count);
}
//-----------------------------------------------------------------------------------------------------
void PrintSpecificBus(struct node2*b)
{
    if(b!=NULL)//check if a header of linked list for busses is not NULL
    {
        busses* b1=b->nextBus,*b2;//define a pointer b1 type busses that pointer to first bus
        if(b1!=NULL)//check if b1 is not NULL,not empty busses
        {
            int num,date,price,capacity;
            char  time[50],from[50],to[50];
            printf("Please Enter Information Of Bus With (#):");
            scanf("%d#%d#%[^#]#%[^#]#%[^#]#%d#%d",&num,&date,time,from,to,&price,&capacity);//enter Informations Of Bus you want to print
            int y=0;//define y equal zero
            while(b1!=NULL)//check if a first bus not NULL(not empty linked)
            {
                b2=b1->nextBus;
                if(num==b1->num && date==b1->date2 &&  (strcmp(time,b1->time2)==0) && (strcmp(from,b1->from2)==0) && (strcmp(to,b1->to2)==0) && price==b1->price && capacity==b1->capacity )
                {
                    printf("     Number\tDATE\t\tTIME\t\tFROM\t\tTO\t\tPRICE\t    CAPACITY\n");
                    printf("Bus: %d\t\t%d\t%s\t\t%s   \t%s   \t%d\t    %d\n",b1->num,b1->date2,b1->time2,b1->from2,b1->to2,b1->price,b1->capacity);//print all informations of the bus
                    Printt(b1);//print all passengers in this bus
                    printf("---------------------------------------------------------------------------------------------------------\n");
                    y=1;//change y to 1
                    break;
                }
                b1=b2;//pass into a next bus in a linked list for busses
            }
            if(y==0)//check if y not change,that mean the bus is not found in a linked list for busses
            {
                printf("THE BUS IS NOT FOUND");
            }
        }
        else//b1 is NULL that mean Empty (linked list for busses),no busses loaded
        {
            printf("NO Busses");
        }
    }
    else
    {
        printf("NULL");
    }

}

//-----------------------------------------------------------------------------------------------------

void AddPassenger(struct node2* b,struct node1* um)
{
    if(b!=NULL && um !=NULL)//check if a header to busses and unmatched passengers linked list are not NULL
    {
        int id,date1;
        char from1[50],to1[50],time1[50];
        printf("Please Enter The Information Of Passenger with (#):");
        scanf("%d#%d#%[^#]#%[^#]#%[^\n]",&id,&date1,time1,from1,to1);//enter a informations of pasenger you want to add
        passenger* New;//define pointer type passenger named New (this passenger will add)
        New=(passenger*)malloc(sizeof(passenger));//define it in memory
        New->id=id;
        New->date1=date1;
        strcpy(New->from1,from1);
        strcpy(New->to1,to1);
        strcpy(New->time1,time1);
        New->next=NULL;
        busses* b1;//define pointer b1 type busses
        b1=b->nextBus;//make b1 pointer to first bus
        int t=0;//define t equal zero
        busses* temp;//define pointer temp type busses
        if(b1!=NULL)//check if b1 not NULL(that mean found busses in linked list for busses)
        {
            while(b1!=NULL)
            {
                temp=b1->nextBus;//make temp pointer to next bus of b1

                if(date1==b1->date2 && strcmp(time1,b1->time2)==0  &&  strcmp(from1,b1->from2)==0 && strcmp(to1,b1->to2)==0 && b1->capacity!=0 )
                {
                    InsertBegin3(b1,New);//insert the new passenger into the bus who's agreed with
                    b1->capacity--;//reduce the capacity of bus by one
                    t=1;//change t to one
                    printf("New passenger:%d  %d  %s  %s   %s\nInsert To Bus Number:%d\n", New->id, New->date1, New->time1, New->from1, New->to1,b1->num);//print all informations of passenger who added
                }
                b1=temp;//pass into a next bus
            }
        }
        else//b1 is NULL (theres no busses)
        {
            printf("No Busses");
        }
        if(t==0)//check if t don't change that mean (the passenger not found in busses)
        {
            InsertBegin2(um,New);//insert the new passenger into  a linked list for unmatched passengers
            printf("New passenger:%d  %d  %s  %s   %s \nInsert To UnMatched Passengers\n", New->id, New->date1, New->time1, New->from1, New->to1);
        }
    }
    else
    {
        printf("NULL");
    }

}

//----------------------------------------------------------------------------------------------------------------------------

void DeletePassenger(struct node2*b)
{
    if(b!=NULL)
    {
        int id,num;
        printf("Please Enter An Id Of Passenger You Want To Delete:");
        scanf("%d",&id);
        printf("Please Enter The Bus Number Containing This Passenger:");
        scanf("%d",&num);

        passenger* temp;
        passenger* temp2;
        int t=0;
        busses* b1=b->nextBus,*p,*Bus,*Bus2;
        //passenger* d;



        p=FindPrevious(num,b);

        if(p==NULL)
        {
            printf("Not Found Bus Number\n");
        }
        else
        {
            Bus=p->nextBus;
            printf("The Bus Is found\n");
        }


        while(b1!=NULL)
        {
            passenger* s=b1->nextPass;
            while(s!=NULL)
            {
                if(id==s->id)
                {
                    Bus2=b1;
                    temp=s;
                    t=1;
                }
                s=s->next;
            }
            b1=b1->nextBus;
        }
        if(t==1)
            printf("The Passenger Is Found\n");
        else
            printf("The Passenger Is Not Found\n");

        if(Bus2->num==Bus->num)
        {
            printf("Correct,The Passenger In This Bus\n");

            if(Bus->nextPass==temp)
            {
                Bus->nextPass=temp->next;
                Bus->capacity++;
                free(temp);
                printf("Done Delte Passenger");

            }
            else
            {
                temp2=FindPrevious2(Bus->nextPass,temp);
                temp2->next=temp->next;
                Bus->capacity++;
                free(temp);
                printf("Done Delte Passenger");

            }


        }
        else
            printf("Incorrect,The Bus dosen't containing The Passenger");

    }
    else
    {
        printf("NULL");
    }


}
//---------------------------------------------------------------------------------------------------------------------------
void DeletePassenger2(struct node2*b,struct node1*um)
{
    if(b!=NULL && um!=NULL)
    {
        int id;
        printf("Please Enter Id Passenger:");
        scanf("%d",&id);
        passenger* temp=um;
        passenger* temp2;
        int t=0;
        busses* b1=b->nextBus;
        passenger* d;
        while(temp->next!=NULL)
        {
            if(id==temp->next->id)
            {
                temp2=temp->next;
                temp->next=temp2->next;
                free(temp2);
                t=1;
            }
            temp=temp->next;
        }

        if(t==0)
        {

            while(b1!=NULL)
            {

                passenger* s=b1->nextPass;
                while(s!=NULL)
                {

                    if(id==s->id)
                    {
                        t=1;
                        if(b1->nextPass==s)
                        {
                            temp2=s;
                            b1->nextPass=temp2->next;
                            b1->capacity++;
                            free(temp2);
                            break;
                        }
                        else
                        {
                            temp2=s;
                            d=FindPrevious2(b1->nextPass,s);
                            d->next=temp2->next;
                            b1->capacity++;
                            free(temp2);
                            break;
                        }
                        t=1;
                    }
                    s=s->next;
                }
                b1=b1->nextBus;
            }
            if(t==0)
            {
                printf("Not Found Passenger");
            }
        }
    }
    else
    {
        printf("NULL");
    }
}
//----------------------------------------------------------------------------------------------------------------------------
void DeleteBusNumber(struct node2*b,struct node1* um)
{
    if(b!=NULL && um !=NULL)
    {
        int num;//define a variable named num,this number of bus you want to delete
        printf("Please Enter A Number Of Bus Do You Want To Delete:");
        scanf("%d",&num);//store the number you enter in variable num
        if(b->nextBus!=NULL)//check if first bus not NULL (not empty linked list for busses)
        {
            struct node2* p,*temp;
            struct node1* pass,*pass2;
            p=FindPrevious(num,b);//find previous of bus (have this number that you enter)
            if(p!=NULL)//check if previous of this bus not NULL (mean it found in a linked list)
            {
                temp = p->nextBus;//make temp pointer to next of the previous bus(it mean that pointer to the bus with number entered)
                p->nextBus = temp->nextBus;
                pass=temp->nextPass;
                if(pass==NULL)
                {
                    printf("No Passengers In This Bus\n");
                }
                else
                {
                    while(pass!=NULL)
                    {
                        pass2=pass->next;
                        InsertBegin2(um,pass);//insert all passengers in this bus to (linked list for unmatched passengers)
                        pass=pass2;
                    }
                    printf("All Passengers In This Bus Inserted To UnMatched Linked\n");
                }
                free(temp);//do free to bus(that you want to delete)
                printf("The Bus Has Been Deleted ^-^\n");
            }
            else//the previous of this bus is NULL ,that mean not found the bus in (linked list for busses)
            {
                printf("Not Found The Bus Number");
            }
        }
        else//first bus is NULL that mean no busses in (linked list for busses)
        {
            printf("No Busses");
        }
    }
    else
    {
        printf("NULL");
    }
}
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
struct node1* FindPrevious2(struct node1*L,struct node1*s)
{
    if(L!=NULL && s!=NULL)
    {
        while(L->next!=s)
        {
            L=L->next;
            if(L==NULL)
            {
                return L;
            }
        }
    }
    return L;
}
struct node2* FindPrevious(int x,struct node2*L)
{

    if(L->nextBus!=NULL)
    {
        struct node2* p;
        struct node2* temp=L;
        p=Find(x,L);
        if(p==NULL)
        {
            return p;
        }

        while(temp->nextBus!=p)
        {
            temp=temp->nextBus;
        }
        return temp;
    }
    else
        return NULL;

}
struct node2* Find(int x,struct node2*L)
{
    struct node2* p;
    if(L->nextBus!=NULL)
    {
        p=L->nextBus;
        while(p!=NULL && p->num!=x)
        {
            p=p->nextBus;
        }
    }
    return p;
}
//----------------------------------------------------------------------------------------------------------------------------
void PrintList5(struct node2* L)
{
    if(L!=NULL)
    {
        if(L->nextBus==NULL)
        {
            printf("Empty Busses\n");
        }
        else
        {
            while(L->nextBus!=NULL)
            {
                printf("     Number\tDATE\t\tTIME\t\tFROM\t\tTO\t\tPRICE\t    CAPACITY\n");
                printf("Bus: %d\t\t%d\t%s\t\t%s   \t%s   \t%d\t    %d\n",L->nextBus->num,L->nextBus->date2,L->nextBus->time2,L->nextBus->from2,L->nextBus->to2,L->nextBus->price,L->nextBus->capacity);
                Printt(L->nextBus);
                L=L->nextBus;
                printf("--------------------------------------------------------------------------------------------------------\n");
            }
        }
    }
    else
    {
        printf("NULL");

    }
}
void Printt(struct node2* L)
{
    if(L!=NULL)
    {
        if(L->nextPass==NULL)
        {
            printf("Empty Bus theres no passengers\n");
        }
        else
        {
            struct node1* p=L->nextPass;
            printf("Passengers Informations In This Bus:\n\t   ID\t\tDATE\t\tTIME\t\tFROM\t\tTO\n");
            while(p!=NULL)
            {
                printf("Passenger: %d \t%d\t%s   \t%s   \t%s\n",p->id,p->date1,p->time1,p->from1,p->to1);
                p=p->next;
            }
        }
    }
    else
    {
        printf("NULL");
    }
}
void PrintList(struct node2* L)
{
    if(L->nextBus==NULL)
    {
        printf("Empty Busses\n");
    }
    else
    {
        printf("--------------------------------------------------------------------------------------------------------\n");
        struct node2* p=L->nextBus;//gived me a linked list of passengers
        printf("      Number\t  DATE\t\t  TIME\t\tFROM\t\t  TO     \t PRICE\t    CAPACITY\n");
        while(p!=NULL)
        {
            printf("Bus:%4d%17d%14s%18s%16s%10d%13d\n",p->num,p->date2,p->time2,p->from2,p->to2,p->price,p->capacity);
            if(p->nextBus==NULL)
            {
                break;
            }
            else
            {
                p=p->nextBus;
            }
        }
        printf("--------------------------------------------------------------------------------------------------------\n");
    }
}
void PrintList2(struct node1* L)
{
    if(L->next==NULL)
    {
        printf("No Passengers\n");
    }
    else
    {
        printf("--------------------------------------------------------------------------------------------------------\n");
        struct node1* p=L->next;//gived me a linked list of passengers
        printf("\t   ID\t\tDATE\t\t  TIME\t\tFROM\t\tTO\n");
        while(p!=NULL)
        {
            printf("Passenger: %d \t%d\t%15s   \t%s   \t%s\n",p->id,p->date1,p->time1,p->from1,p->to1);
            if(p->next==NULL)
            {
                break;
            }
            else
            {
                p=p->next;
            }
        }
        printf("--------------------------------------------------------------------------------------------------------\n");
    }
}
//-------------------------------------------------------------------------------------------------------
void InsertBegin(struct node2*L,struct node2*temp)
{
    if(L!=NULL && temp!=NULL)
    {
        temp->nextBus= L->nextBus;
        L->nextBus=temp;
    }
    else
    {
        printf("NULL,can't Insert ");
    }
}
void InsertBegin2(struct node1*L,struct node1*temp)
{
    if(L!=NULL && temp!=NULL)
    {
        temp->next= L->next;
        L->next=temp;
    }
    else
    {
        printf("NULL,can't Insert");
    }
}
void InsertBegin3(struct node2*L,struct node1*temp)
{
    if(L!=NULL && temp!=NULL)
    {
        temp->next= L->nextPass;
        L->nextPass=temp;
    }
    else
    {
        printf("NULL,can't Insert");
    }
}

