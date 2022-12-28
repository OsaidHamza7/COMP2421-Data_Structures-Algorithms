//Project2_OSAIDHAMZA_1200875
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max_Size 500



typedef struct node1//structure for  node1 for topics in courses.
{
    char topic[50];//Array of characters (string) for topic.
    struct node1* next;//pointer of structure node1 named next.
} List;
typedef struct node//structure node for courses in this program.
{
    char Course [50];//Course name.
    int CreditHours;//Credit hours.
    char CourseCode[50];//Course code.
    char Department[50];//Department name.
    List* Topic;//pointer for structure node1(for topics in courses)
    struct node* Left;//pointer to structure node(Course).
    struct node* Right;//pointer to structure node(Course).
    int Height;//The height of the node(course).
} Course;
//----------------------------------------------------------------------------------------------------------------------------
//The insert routine : to insert topics in a linked list.
void InsertTopic(List* head,char topic[50])
{
    if(head!=NULL)//Check if the head is NULL,
    {//If not, start the insertion operation.
        List *temp;
        temp=(List*)malloc(sizeof(List));//Reserve a space for each node in the memory.
        strcpy(temp->topic,topic);//Give the topic in the node the passed value.
        List *p=head;//Create temporary node follow the nodes in linked list to insert the node (topic).
        while(p->next!=NULL)
        {
            p=p->next;
            if(p==NULL)
                break;
        }
        p->next=temp;//Insert the new node (topic).
        temp->next=NULL;//Make the next of the pointer points to NULL.
    }
}

//The print routine : print all the topics in the course (print linked list).
void PrintTopicsInCourse(List* head)
{
    if(head!=NULL)//Check if the head is NULL,
    {//If not, the operation of the printing will start.
        List *p=head->next;//Make the pointer to the next of head.
        printf("Course Topics:");
        while(p!=NULL)//Check that the node does not reach the end (points to NULL).
        {
            printf("%s ",p->topic);//Print the topic in each node.
            p=p->next;//Move the pointer.
        }
        printf("\n");
    }
}

//The make empty routine : to make sure that every node in the tree was empty first.
Course* MakeEmpty( Course* T )
{
    if( T != NULL )//Check if the root is NULL,
    {//If not,
        MakeEmpty( T->Left );//Free the left subtree.
        MakeEmpty( T->Right );//Free the right subtree.
        free( T );//Free the root.
    }
    return NULL;
}

//The hight routine : to get the hight of a node in the tree (course).
int Height( Course* P )
{
    if( P == NULL )//Check if the tree in NULL, the there's no height.
        return -1;
    else//Else, return the height of the node.
        return P->Height;
}

//The max method : get the maximum value between two values.
int Max( int Lhs, int Rhs )
{
    return Lhs > Rhs ? Lhs : Rhs;//Compare both values.
}

//The find Min routine : to find the minimum value in the tree.
Course* FindMin(Course* T )
{
    if( T == NULL )//Check if the root is null, then there's no tree.
        return NULL;
    else if( T->Left == NULL )//If the left subtree is null, then the root is the minimum value.
        return T;
    else
        return FindMin( T->Left );//While there is a left subtree for the tree, make recursive calls on it to find the minimum value.
}

//The find Max routine : to find the maximum value in the tree.
Course* FindMax( Course* T )
{
    if( T != NULL )//Check if the root is null, then there's no tree.
        while( T->Right != NULL )//While there is a right subtree for the tree, move the pointer to the right to find the maximum value.
            T = T->Right;//Move the pointer.
    return T;
}

//The single rotate left routine (on right side) : single rotate to left when balancing is breaking.
Course* SingleRotateWithLeft( Course* K2 )
{
    Course*  K1;
    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;
    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;//Update the height.
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;//Update the height for the new root.

    return K1;  /* New root */
}

//The single rotate right routine (on left side) : single rotate to right when balancing is breaking.
Course* SingleRotateWithRight( Course* K1 )
{
    Course* K2;
    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;
    K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;//Update the height.
    K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;//Update the height for the new root.

    return K2;  /* New root */
}


//The double rotate for left : when the unbalancing happen in different sides.
Course* DoubleRotateWithLeft( Course* K3 )
{
    K3->Left = SingleRotateWithRight( K3->Left );//First,rotate right,
    return SingleRotateWithLeft( K3 );//then, rotate left.
}

//The double rotate for right : when the unbalancing happen in different sides.
Course* DoubleRotateWithRight(Course* K1 )
{
    K1->Right = SingleRotateWithLeft( K1->Right );//First,rotate left,
    return SingleRotateWithRight( K1 );//then, rotate right.
}

//The insert routine : to insert a new node (course) in the tree.
Course* InsertCourse(Course* s,Course* T )
{
    if( T == NULL )//Check if the root is NULL,
    {
        T =(Course*)malloc( sizeof(Course) );//If is, then create a root.
        if( T == NULL )//if it still null, then the computer system fail to reserve a space for it in the memory.
            printf( "Out of space!!!" );//print this for user.
        else
        {
            T=s;//Make the new node (course) is the root.
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    }
    else if( strcmp(T->CourseCode,s->CourseCode)>0 )//Compare the course code of the root with the course code of the new node,
    {//If greater than (root greater than the new node) , insert the node in the left subtree.
        T->Left = InsertCourse(s, T->Left );
        if( Height( T->Left ) - Height( T->Right ) == 2 )//Get the height in order to make the needed rotation to save the balancing.
        {
            if( strcmp(T->Left->CourseCode,s->CourseCode)>0 )
                T = SingleRotateWithLeft( T );
            else
                T = DoubleRotateWithLeft( T );
        }
    }
    else if( strcmp(T->CourseCode,s->CourseCode)<0 )//Compare the course code of the root with the course code of the new node,
    {//If less than (root less than the new node) , insert the node in the right subtree.
        T->Right = InsertCourse( s, T->Right );
        if( Height( T->Right ) - Height( T->Left ) == 2 )//Get the height in order to make the needed rotation to save the balancing.
        {
            if( strcmp(T->Right->CourseCode,s->CourseCode)<0 )
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );
        }
    }

    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;//Update the height of the root.
    return T;//Return the new tree.
}

//The cut topics routine : divide topics into nodes for a linked list.
void CutTopics(char h[],List* head)
{
    char *token;
    token = strtok(h,",");//Divide it according to the following character ",".
    while( token != NULL )//While there is a node , continue inserting.
    {
        InsertTopic(head,token);//Call the insert function , to add new node to the linked list.
        token = strtok(NULL,",");
    }
}

//The find routine : find a specific course according to a given code.
Course* FindCourse(Course* T,char c[50])
{
    if( T == NULL )//Check if the root is null.
        return NULL;
    if( strcmp(c,T->CourseCode)<0 )//Compare the given code with the code of the root.
        return FindCourse(T->Left,c );//if less than , search in the left.
    else if( strcmp(c,T->CourseCode)>0 )
        return FindCourse(T->Right,c);//if greater than, search in the right.
    else
        return T;//Return a pointer to this node if founded (course).
}

//The find topic routine : to find a specific topic in the linked list.
List* FindTopic(char x[50],List*L)
{
    List* p;
    if(L!=NULL)//check that the list is not NULL.
    {
        p=L->next;
        while(p!=NULL && strcmp(p->topic,x)!=0  )//Compare the given topic with the topic that the pointer points to it.
        {
            p=p->next;//Move the pointer.
        }
    }
    return p;//return the pointer which points to the needed topic.
}

//The find previous topic routine : to find the previous topic for a given topic.
List* FindPreviousTopic(char c[],List *L)
{
    if(L!=NULL)//Check if the list is empty.
    {
        List* p;//Temporary pointers.
        List* temp=L;
        p=FindTopic(c,L);//check if the given course is exist.
        if(p==NULL)
        {
            return p;
        }
        while(temp->next!=p)
        {
            temp=temp->next;
        }
        return temp;
    }
    else
        return NULL;
}

//The get balance routine : to get the balance of the course.
int getBalance(Course* N)
{
    if (N == NULL)//Check if the course is NULL.
        return 0;
    return (Height(N->Left)- Height(N->Right));//If not, calculate the height of the node by this equation.
}

////////////////////////////////////////////////First Requirement/////////////////////////////////////////////////////////////////////////////////////////////
Course* LoadCoursesIntoAVL(Course* T)//creat a function to load all courses in file(courses.txt) to AVL_TREE for courses and return pointer of course
{
    if(T!=NULL)//check if T(course) not equal NULL
    {
        T = MakeEmpty( T );//make empty for this pointer to course.
        FILE *coursesFile;//Create pointer to the input file.
        coursesFile=fopen("courses.txt","r");//open a file named(courses) to read from it.
        if(coursesFile!=NULL)//Check if the pointer points to NULL.
        {
            while(!feof(coursesFile))
            {
                Course* r;
                r=(Course*)malloc(sizeof(Course));
                char temp[Max_Size];
                fscanf(coursesFile,"%[^:]:%d#%[^#]#%[^/]/%[^\n]",r->Course,&r->CreditHours,r->CourseCode,r->Department,temp);
                fgetc(coursesFile);
                r->Height=0;
                r->Topic=(List*)malloc(sizeof(List));
                r->Topic ->next=NULL;
                CutTopics(temp,r->Topic);
                T=InsertCourse(r,T);
            }
            printf("Load courses Into AVL Tree Is Done\n\n");//Print this for user to ensure that the reading operation is done.
            fclose(coursesFile);//Close the file.
        }
        else
        {
            printf("Not Found  courses File,please create a  courses file and try again\n");//print it when not found the file.
        }
    }
    else
    {
        printf("(Out Of Memory)\n");//Print this if the node still null.
    }
    return T;
}



///////////////////////////////////////////////////////Second Requirement////////////////////////////////////////////////////////////////////////////////////////////
//The inset course routine : to insert a new node (course) in the tree.
void InsertNewCourse(Course* T)
{
    if(T!=NULL)//Check if the root is null,
    {
        Course* New;
        New=(Course*)malloc(sizeof(Course));//If not,reserve a space for it in the memory.
        if(New==NULL)
            printf("Out of Memory");//If still null, then the memory is FULL.
        else
        {
            New->Left=New->Right=NULL;//If not, insert the node(course).
            New->Height=0;
            char temp[Max_Size];
            printf("Please Enter The Information Of Course:");//Print this the user to enter the information of the course.
            scanf("%[^:]:%d#%[^#]#%[^/]/%[^\n]",New->Course,&New->CreditHours,New->CourseCode,New->Department,temp);//Scan the info.
            New->Topic=(List*)malloc(sizeof(List));//Create new node (course).
            New->Topic->next=NULL;
            CutTopics(temp,New->Topic);//Call this function to make list of topics.
            T=InsertCourse(New,T);//Insert the new node into the tree.
            printf("The Inserting Course is done\n");
        }
    }
    else
        printf("NULL,No Inserting\n");//Print this if the root is NULL.
}
/////////////////////////////////////////////////////////Third Requirement//////////////////////////////////////////////////////////////////////////////////
//The Updating course routine : to update information about course.
void UpdatingCourse(Course* T)
{
    char YN[10];
    char c[50];
    Course* s;
    printf("Enter a Course Code:");//Print this for user to enter the code of course would to update its information.
    scanf("%s",c);//Scan the code.
    s=FindCourse(T,c);//Find if the course exist.
    if(s!=NULL)
    {
        printf("Found Course\n");
        printf("Do you want to update?");//Ask user if he/she would to update it.
        scanf("%s",YN);//Scan the result.
        if(strcmp(YN,"yes")==0 || strcmp(YN,"YES")==0 )
        {
            int h,k;
            char r[50],d[50],p[50],NewTopic[50];
            int choice;
            List* l,*m;
            while(choice!=5)//check that the user does not select option number 5.
            {
                printf("\n               MENU                             \n");//Print the menu.
                printf("1.update CreditHours.\n");
                printf("2.update Course Name.\n");
                printf("3.update Course Department.\n");
                printf("4.update Topics.\n");
                printf("5.Exit.\n");
                printf("Enter your choice:");//Print this to enter the choice.
                scanf("%d",&choice);//Scan the choice.
                switch(choice)//Make switch statements on the choice:
                {
                case 5:
                    break;
                default:
                    printf("Wrong Choice");//Print this for user if the choice was not from 1-5.
                    break;
                case 1://If choice 1 selected.
                    printf("Enter New CreditHours:");
                    scanf("%d",&h);
                    s->CreditHours=h;
                    printf("Update is done\n");
                    break;
                case 2://If choice 2 selected.
                    printf("Enter New Course Name:");
                    scanf("%s",r);
                    strcpy(s->Course,r);
                    printf("Update is done\n");
                    break;
                case 3://If choice 3 selected.
                    printf("Enter New Department:");
                    scanf("%s",d);
                    strcpy(s->Department,d);
                    printf("Update is done\n");
                    break;
                case 4://If choice 4 selected.
                    while(k!=4)
                    {
                        printf("\n               MENU                             \n");
                        printf("1.update specific topic.\n");
                        printf("2.Delete specific topic.\n");
                        printf("3.Add new topic.\n");
                        printf("4.Exit.\n");
                        printf("Enter your choice:");
                        scanf("%d",&k);
                        switch(k){
                       case 1:
                        {
                            printf("Enter a specific topic to Update:");
                            scanf("%s",p);
                            l=FindTopic(p,s->Topic);
                            if(l!=NULL)
                            {
                                printf("Found topic\n");
                                printf("Enter a new topic:");
                                scanf("%s",NewTopic);
                                strcpy(l->topic,NewTopic);
                                printf("After Updating:-\n");
                                PrintTopicsInCourse(s->Topic);
                                printf("\n");
                            }
                            else
                                printf("Not Found Topic");
                        }
                        case 2:
                        {
                            printf("Enter a specific topic you want to Delete:");
                            scanf("%s",p);
                            l=FindPreviousTopic(p,s->Topic);
                            if(l!=NULL)
                            {
                                printf("Found topic\n");
                                m=l->next;
                                l->next=m->next;
                                free(m);
                                printf("After Deleting:-\n");
                                PrintTopicsInCourse(s->Topic);
                                printf("\n");
                            }
                            else
                                printf("Not Found Topic");
                        }
                        case 3:
                        {
                            printf("Enter a new topic:");
                            scanf("%s",p);
                            InsertTopic(s->Topic,p);
                            printf("After Adding:-\n");
                            PrintTopicsInCourse(s->Topic);
                            printf("\n");
                        }
                        case 4:
                            break;

                    default:
                            printf("Wrong Choice");
                        break;
                        }
                    }
                }
            }
        }
    }
    else
        printf("Not Found Course\n");//Print this if the course does not exist.
}
/////////////////////////////////////////////////////////////////////Fourth Requirement///////////////////////////////////////////////////////////////////////////////
//The List courses in order routine : to print the courses in the in-order .
void  ListCoursesInLexicographic( Course* t)
{

    if( t != NULL)//Check if the root is NULL
    {
        ListCoursesInLexicographic( t->Left );//Make a recursive call for the print function on left subtree of the root.
        //Print the information of the root.
        printf("Course Name:%s       Credit Hours:%d     Course Code:%s      Course Department:%s\n",t->Course,t->CreditHours,t->CourseCode,t->Department);
        PrintTopicsInCourse(t->Topic);
        printf("----------------------------------------------------------------------------------------------------------------\n");
        ListCoursesInLexicographic(t->Right );//Make a recursive call for the print function on right subtree of the root.
    }
}
/////////////////////////////////////////////////////////////////////Fifth Requirement///////////////////////////////////////////////////////////////////////////////
//The list topic with a course routine : to print all courses in a specific course.
void ListAllTopicsWithGivenCourse(Course* T)
{
    char c[50];
    Course* s;
    s=(Course*)malloc(sizeof(Course));
    printf("Enter a Course Code:");//Print this to enter the code.
    scanf("%s",c);//Scan the code.
    s=FindCourse(T,c);//Call the find routine to check if the course exist.
    if(s!=NULL)//If its not null, then there's a course with this course .
    {
        printf("Found and this is all topics in this course:\n");
        PrintTopicsInCourse(s->Topic);//Call this print function , to print the topics in a linked list.
    }
    else
        printf("Not Found");//print this if the result was NULL, then the course does not exist.
}

/////////////////////////////////////////////////////////////////////Sixth Requirement///////////////////////////////////////////////////////////////////////
//The list courses with department routine : to list all courses belong to specific department.
void ListAllCoursesBelongDepartment( Course* t,char D[50])
{
    if( t != NULL)//Check if the tree is NULL,
    {
        ListAllCoursesBelongDepartment( t->Left,D );//If not, call the print function on the left subtree of the root.

        if( strcmp(t->Department,D)==0 )//Check if the department name in the root is the same as given one, then print it.
        {
            printf("Course Name:%s       Credit Hours:%d     Course Code:%s      Course Department:%s\n",t->Course,t->CreditHours,t->CourseCode,t->Department);
            PrintTopicsInCourse(t->Topic);//Print the topics.
        }
        printf("\n");

        ListAllCoursesBelongDepartment(t->Right,D);//call the print function on the right subtree of the root.
    }
}

////////////////////////////////////////////////////////////////////Seventh Requirement////////////////////////////////////////////////////////////////////////////
//The delete routine : to delete a specific course according to the code course.
Course* Delete(Course* T,char code[50])
{
    Course* temp;
    if(T==NULL)//Check if the root is NULL.
    {
        printf("element not found");
        return NULL;
    }
    else if (strcmp(T->CourseCode,code)>0 )//Compare the given code with the code in the root,
        T->Left=Delete(T->Left,code);//If greater (root->CODE > given code) than, call the delete function on the left subtree.
    else if ( strcmp(T->CourseCode,code)<0 )
        T->Right=Delete(T->Right,code);//If less (root->CODE < given code) than, call the delete function on the right subtree.
    else
    {//Check if the node it has children.
        if(T->Right && T->Left)//In case of has two children.
        {
            temp=FindMin(T->Right);
            strcpy(T->Course,temp->Course);
            T->CreditHours=temp->CreditHours;
            strcpy(T->CourseCode,temp->CourseCode);
            strcpy(T->Department,temp->Department);
            strcpy(T->CourseCode,temp->CourseCode);
            T->Topic = temp->Topic;
            T->Right=Delete(T->Right,temp->CourseCode);
        }
        else
        {//In case of it has zero or one child.
            temp=T;
            if(T->Left==NULL)
                T=T->Right;
            else if (T->Right==NULL)
                T=T->Left;
            free(temp);
        }
        if(T==NULL)
            return NULL;

        T->Height = 1 + Max(Height(T->Left),Height(T->Right));//Update the height after deletion.

        //The cases in which the balancing was broken, and different types of rotation were needed.
        if (getBalance(T) >1  && getBalance(T->Left) >= 0)
            return SingleRotateWithLeft(T);

        if (getBalance(T) > 1 && getBalance(T->Left) < 0)
        {
            T->Left = SingleRotateWithRight(T->Left);
            return SingleRotateWithLeft(T);
        }
        if (getBalance(T) < -1 && getBalance(T->Right) <= 0)
            return SingleRotateWithRight(T);

        if (getBalance(T) < -1 && getBalance(T->Right) > 0)
        {
            T->Right = SingleRotateWithLeft(T->Right);
            return SingleRotateWithRight(T);
        }
    }
    return T;//Return the tree after deletion .
}

/////////////////////////////////////////////////////////////////Eighth Requirement/////////////////////////////////////////////////////////////////////////////////
//The find course with letter routine : to find a course with specific character.
Course* FindCourseLetter( Course* t,char D)
{
    if( t != NULL)//Check if the root is NULL,
    {
        if( t->CourseCode[0]==D )//If not, compare the character with the first character in the course code.
        {
            return t;//In case of they are equal,
        }
        if(D < t -> CourseCode[0])//In case of less than,
        {
            return FindCourseLetter( t->Left, D);
        }
        return FindCourseLetter(t->Right,D);//The last case, which is greater than.
    }
    return NULL;
}

/////////////////////////////////////////////////////////////////ninth Requirement//////////////////////////////////////////////////////////////////////////////////////////
//The find course with department routine : to find specific course with a given department.
Course* FindCourseByGivenDepartment( Course* t,char D[50])
{
    if( t != NULL)//Check if the root is NULL,
    {
        if( strcmp(t->Department,D)==0 )// If not , compare the two values(the name of department in the root with the give departement)>
        {
            return t;
        }
        Course *s1 = FindCourseByGivenDepartment( t->Left, D);//Call the find function on the left subtree.
        if(s1 != NULL)
        {
            return s1;
        }
        return FindCourseByGivenDepartment(t->Right,D);//Call the find function on the right subtree.
    }
    return NULL;
}


/////////////////////////////////////////////////////////////////Tenth Requirement///////////////////////////////////////////////////////////////////////////////////////////////
//The save tree in file routine : to save all information in the output file after different operations.
void SaveTreeInFile(Course* t,FILE* fptr)
{
    if( t!= NULL && fptr!=NULL) //Check that neither the tree is null nor the pointer to file.
    {
        SaveTreeInFile( t->Left,fptr );//Call the function to print the contents of the left subtree in the output file.
        //Print the contents of the root in the output file.
        fprintf(fptr,"%s:%d#%s#%s/",t->Course,t->CreditHours,t->CourseCode,t->Department);
        if(t->Topic!=NULL)
        {
            List* c=t->Topic;
            List* p=c->next;
            while(p!=NULL)
            {
                if(p->next!=NULL)
                    fprintf(fptr,"%s, ",p->topic);
                else
                    fprintf(fptr,"%s",p->topic);

                p=p->next;
            }
            fprintf(fptr,"\n");
        }
        SaveTreeInFile( t->Right,fptr );//Call the function to print the contents of the right subtree in the output file.
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    Course* tree;//Create the main tree.
    tree=(Course*)malloc(sizeof(Course));//Reserve a space for it in the memory.
    tree->Left=tree->Right=NULL;
    int choice;
    FILE *fptr;
    char code[50];
    char department[50];
    char letter;
    Course *D;
    char buf;
    int i=0;
     while(i!=1)
    {//Print the menu for user.
        printf("\n             MENU                             \n");
        printf(" 1.Read the file courses.txt file and create the tree \n");
        printf(" 2.Insert a new course from the user with all its associated data.    \n");
        printf(" 3.Find a course and support updating of its information.   \n");
        printf(" 4.List courses in lexicographic order with their associated information (credit hours, IDs, and topics).\n");
        printf(" 5.List all topics associated with a given course.     \n");
        printf(" 6.List all courses in lexicographic order that belong to the same department.\n");
        printf(" 7.Delete a course.\n");
        printf(" 8.Delete all courses that start with a specific letter.   \n");
        printf(" 9.Delete all courses belong to a given department.      \n");
        printf(" 10.Save all words in file offered_courses.txt \n");
        printf(" 11.Exit the program. \n");
        printf("Enter your choice:");//Print this to enter the choice.
        scanf("%d",&choice);//Scan the choice.
        switch(choice)//Make switch statements on the choice.
        {
        case 1://If option 1 selected.
            tree=LoadCoursesIntoAVL(tree);
            printf("\n***************\n");
            ListCoursesInLexicographic(tree);
            printf("\n****************\n");
            i=1;
            break;

          default://Default case.
            printf("\nWrong Choice,please read the file and create the tree\n");
            break;

        }

    }

    while(1)//Still print the menu.
    {
        printf("\n\n               MENU                             \n");
        printf(" 1.Read the file courses.txt file and create the tree \n");
        printf(" 2.Insert a new course from the user with all its associated data.    \n");
        printf(" 3.Find a course and support updating of its information.   \n");
        printf(" 4.List courses in lexicographic order with their associated information (credit hours, IDs, and topics).\n");
        printf(" 5.List all topics associated with a given course.     \n");
        printf(" 6.List all courses in lexicographic order that belong to the same department.\n");
        printf(" 7.Delete a course.\n");
        printf(" 8.Delete all courses that start with a specific letter.   \n");
        printf(" 9.Delete all courses belong to a given department.      \n");
        printf(" 10.Save all words in file offered_courses.txt \n");
        printf(" 11.Exit the program. \n");
        printf("Enter your choice:");//Enter the choice again.
        scanf("%d",&choice);//Scan the choice.
        switch(choice)
        {
        case 2://If choice 2 selected.
            InsertNewCourse(tree);
            printf("AVL_TREE For Courses After Insertion:\n");
            printf("\n***************\n");
            ListCoursesInLexicographic(tree);
            printf("\n***************\n");
            break;
        case 3://If choice 3 selected.
            UpdatingCourse(tree);
            break;
        case 4://If choice 4 selected.
            if(tree==NULL)
                printf("Empty,No Courses yet");
            printf("\n***************\n");
            ListCoursesInLexicographic(tree);
            printf("\n***************\n");
            break;
        case 5://If choice 5 selected.
            ListAllTopicsWithGivenCourse(tree);
            break;
        case 6://If choice 6 selected.
            printf("Enter a Course Department:");
            gets(department);//buffer is used
            gets(department);
            printf("There is all courses in this deparmtent:\n");
            printf("\n***************\n");
            ListAllCoursesBelongDepartment(tree,department);
            printf("\n***************\n");
            break;
        case 7://If choice 7 selected.
            printf("Enter Course Code:");
            getchar();
            scanf("%s",code);
            tree=Delete(tree,code);
            break;
        case 8://If choice 8 selected.
            printf("Enter Letter:");
            getchar();
            scanf("%c",&letter);
            printf("%c",letter);
            D=FindCourseLetter(tree,letter);
            while(D != NULL)
            {
                tree=Delete(tree,D->CourseCode);
                D=FindCourseLetter(tree,letter);
            }
            break;
        case 9://If choice 9 selected.
            printf("Enter Department:");
            getchar();
            gets(department);
            D=FindCourseByGivenDepartment(tree,department);
            while(D != NULL)
            {
                tree=Delete(tree,D->CourseCode);
                D=FindCourseByGivenDepartment(tree,department);
            }
            break;
        case 10://If choice 10 selected.
            fptr = fopen("offered_courses.txt","w");
            if(fptr == NULL)
            {
                printf("Error!");
            }
            SaveTreeInFile(tree,fptr);
            printf("Save tree in new file is done,Thank You ^_^");
            fclose(fptr);
            break;
        case 11://If choice 11 selected.
            exit(0);
            break;
        default:
            printf("Wrong Choice,please try again");
            break;
        }
    }
    return 0;
}
//----------------------------------------------------------------------------------------------------------------------------
