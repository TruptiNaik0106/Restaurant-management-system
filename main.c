
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node//node structure 
{
    char foodname[50];
    int quantity;
    float price;
    int data;
    struct node *prev;
    struct node *next;//stores address of next node
};
//global vaiables declaration
struct node *headc = NULL,*newnode,*tailc = NULL;// head and tail pointers of customer linked list
struct node *heada = NULL, *taila = NULL;//head and tail pointers for admin lnked list
struct node *head_s;//which stores total sails in the day

void adminmenu()//this prints all the options available for the admin
{
    printf("\n\t\t\t\t\t\t\t1. View total sales\n");
    printf("\t\t\t\t\t\t\t2. Add new items in the order menu\n");
    printf("\t\t\t\t\t\t\t3. Delete items from the order menu\n");
    printf("\t\t\t\t\t\t\t4. Display order menu\n");
    printf("\t\t\t\t\t\t\t5. Back To Main Menu \n\n");
    printf("\t\t\t\t\t\t\t   Enter Your Choice --->");
}

void customermenu()//this prints all the options available for the customer to choose
{
    printf("\n\t\t\t\t\t\t\t1. Place your order\n");
    printf("\t\t\t\t\t\t\t2. View your ordered items\n");
    printf("\t\t\t\t\t\t\t3. Delete an item from order\n");
    printf("\t\t\t\t\t\t\t4. Display final bill\n");
    printf("\t\t\t\t\t\t\t5. Back To Main Menu \n\n");
    printf("\t\t\t\t\t\t\t   Enter Your Choice --->");
}

struct node* createadmin(struct node *head,int data, char foodname[25], float price)//creates node for admin's linked list
{
    newnode = (struct node*)malloc(sizeof(struct node));//memory allocation

    newnode->data = data;
    newnode->price = price;
    newnode-> quantity = 0;// we set quantity as zero as we are not restricting the quantity
    strcpy(newnode->foodname,foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head;
    //empty condition
    if(temp==NULL)
        heada = taila = newnode;
        //if linked list is not empty
    else
    {
        while(temp->next!=NULL)//traverse till the end
            temp=temp->next;

        temp->next=newnode;//add newnode to the last
        newnode->prev = taila;
        taila = newnode;
    }

    return heada;
}

struct node* createcustomer(struct node *head,int data,int quantity)//creates node for customer linked list
{
    newnode = (struct node*)malloc(sizeof(struct node));

    struct node *temp1 = heada;
    int flag = 0;//initialization of flag
    while(temp1!=NULL)//traverse and check if the data entered by customer exists or not
    {
        if(temp1->data==data)
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }

    if(flag==1)//if the order placed is correct then node is created
    {
        newnode->data = data;
        newnode->price = quantity*(temp1->price);
        newnode-> quantity = quantity;
        strcpy(newnode->foodname,temp1->foodname);
        newnode->next = NULL;
        newnode->prev = NULL;

        struct node *temp = head;

        if(temp==NULL)
            headc = tailc = newnode;
        else
        {
            while(temp->next!=NULL)
                temp=temp->next;

            temp->next=newnode;
            newnode->prev = tailc;
            tailc = newnode;
        }


    }
    else//print not present in menu
    {
        printf("\n\t\t\t\t\t\t\tThis item is not present in the menu!\n");
    }
    return headc;
}

void displayList(struct node *head)//display function of linked list which takes head pointer as the argument
{
    struct node *temp1 = head;
    if(temp1==NULL)//if list is empty
    {
        printf("\n\t\t\t\t\t\t\t\tList is empty!!\n\n");
    }
    else
    {
        printf("\n");
        while(temp1!=NULL)//traverse till last node
        {
            if(temp1->quantity==0)
                printf("\t\t\t\t\t\t\t%d\t%s\t%0.2f\n",temp1->data,temp1->foodname,temp1->price);
            else
            {
                printf("\t\t\t\t\t\t\t%d\t%s\t%d\t%0.2f\n",temp1->data,temp1->foodname,temp1->quantity,temp1->price);
            }

            temp1 = temp1->next;
        }
        printf("\n");
    }

}

struct node* totalsales(int data,int quantity)//utility function to calculate total sales of the day
{
    newnode = (struct node*)malloc(sizeof(struct node));
    int flag = 0;

    struct node *temp1 = heada;//temp1 is assigned with head of admin's linked list
    while(temp1->data!=data)//we traverse until the data is not equal to the data given in the parameter
    {
        temp1 = temp1->next;
    }
    // assign the given parameters to newnode data and quantity
    newnode->data = data;
    newnode->price = quantity*(temp1->price);//calculate price by multiplying quantity with cost
    newnode-> quantity = quantity;
    strcpy(newnode->foodname,temp1->foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head_s;
    // now we check if the linked list that stores total sales of the day is empty or not
    if(temp==NULL)
        head_s = newnode;//assign new node to head pointer
    else
    {
        while(temp->next!=NULL)//traverse 
        {
            if(temp->data==data)//check if the data already exists or not
            {
                flag = 1;//assign flag as 1 and break the loop
                break;
            }
            temp=temp->next;
        }

        if(flag==1)//if flag is 1
        {
            temp->quantity += newnode-> quantity;//we increase its quantity and price
            temp->price += newnode->price;
        }
        else//if data does not exist
        {
            temp->next=newnode;// add new node at the end
        }
    }

    return head_s;
}

void calculatetotsales()//linked list for total sales in the day
{
    struct node *temp = headc;
    while(temp!=NULL)//traverse
    {
        head_s = totalsales(temp->data, temp->quantity);//call total sales function 
        temp=temp->next;
    }
}

struct node* delete(int data,struct node *head, struct node* tail)//utility function to delete node from customers or admin lsit
{
    if(head==NULL)//empty condition
    {
        printf("\n\t\t\t\t\t\t\tList is empty\n");
    }
    else
    {
        struct node* temp;//temporary pointer
        if(data==head->data)//check if data is equal to the head data
        {
            temp = head;//assign head to temp
            head = head->next;// shift head to next node
            if (head != NULL)
                head->prev = NULL;
            free(temp);//free memory
        }
        else if(data==tail->data)//data to be deleted is tail node
        {
            temp = tail;//assign tail to temp
            tail = tail->prev;//shift tail to previous node
            tail->next = NULL;
            free(temp);//free temp
        }
        else
        {
            temp = head;//assign head to temp
            while(data!=temp->data)//traverse till data is not equal
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            free(temp);
        }
    }
    return head;
}

int deleteadmin()//delete a node from admin's linked list
{
    printf("\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ");
    int num;
    scanf("%d",&num);

    struct node* temp=heada;
    while(temp!=NULL)// traverse 
    {
        if (temp->data == num)//if data is equal to num
        {
            heada = delete(num, heada, taila);//call delete function
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

int deletecustomer()//delete from customer linked list
{
    printf("\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ");
    int num;
    scanf("%d",&num);

    struct node* temp=headc;
    while(temp!=NULL)//traverse
    {
        if (temp->data == num)
        {
            headc = delete(num, headc, tailc);//call delete function
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

void displaybill()//display total bill function
{
    displayList(headc);//display the ordered list
    struct node *temp = headc;
    float total_price = 0;//initially total price is zero
    while (temp!=NULL)//traverse the customer linked list
    {
        total_price +=temp->price;//add the total price of all ordered menu
        temp = temp->next;
    }

    printf("\t\t\t\t\t\t\tTotal price: %0.02f\n",total_price);//display the bill

}

struct node* deleteList(struct node* head)//entire linked list is deleted
{
    if(head==NULL)
    {
        return NULL;
    }
    else
    {
        struct node* temp = head;
        while(temp->next!=0)
        {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }

    return head;
}

void admin()//admin's functonalities
{
    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    ADMIN SECTION\n");
    printf("\t\t\t\t\t   ----------------------------------------------\n");
    while(1)
    {
        adminmenu();//displays  the admin's functionalities

        int opt;
        scanf("%d",&opt);

        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
                displayList(head_s);//displaying total sales
                break;
            case 2:

                printf("\n\t\t\t\t\t\t\tEnter serial no. of the food item: ");// adding food item and also checks if it already exists
                int num,flag = 0;
                char name[50];
                float price;
                scanf("%d",&num);

                struct node *temp = heada;

                while(temp!=NULL)
                {
                    if(temp->data==num)
                    {
                        printf("\n\t\t\t\t\t\tFood item with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if(flag==1)
                    break;

                printf("\t\t\t\t\t\t\tEnter food item name: ");
                scanf("%s",name);
                printf("\t\t\t\t\t\t\tEnter price: ");
                scanf("%f",&price);
                heada = createadmin(heada, num, name, price);
                printf("\n\t\t\t\t\t\t\tNew food item added to the list!!\n\n");
                break;
            case 3:
                if(deleteadmin())//delete from the menu
                {
                    printf("\n\t\t\t\t\t\t### Updated list of food items menu ###\n");
                    displayList(heada);
                }
                else
                    printf("\n\t\t\t\t\t\tFood item with given serial number doesn't exist!\n\n");

                break;
            case 4:
                printf("\n\t\t\t\t\t\t\t   ### Order menu ###\n");
                displayList(heada);// display the admin's linked lsit
                break;

            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
                break;
        }
    }
}

void customer()//customer's functionalities
{
    int flag=0,j=1;
    char ch;
    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    CUSTOMER SECTION\n");
    printf("\t\t\t\t\t   ----------------------------------------------\n");
    while(1)
    {
        customermenu();//prints customer functionality

        int opt;
        scanf("%d",&opt);

        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
                displayList(heada);//displays admin's linked list that is the menu
                printf("\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ");
                int n;
                scanf("%d",&n);
                printf("\t\t\t\t\t\tEnter quantity: ");
                int quantity;
                scanf("%d",&quantity);
                headc = createcustomer(headc, n, quantity);
                break;
            case 2:
                printf("\n\t\t\t\t\t\t\t  ### List of ordered items ###\n");
                displayList(headc);//displays ordered items
                break;
            case 3:
                if(deletecustomer())//delete from ordered menu
                {
                    printf("\n\t\t\t\t\t\t### Updated list of your ordered food items ###\n");
                    displayList(headc);
                }
                else
                    printf("\n\t\t\t\t\t\tFood item with given serial number doesn't exist!!\n");
                break;
            case 4:
                calculatetotsales();
                printf("\n\t\t\t\t\t\t\t  ### Final Bill ###\n");
                displaybill();
                headc = deleteList(headc);
                printf("\n\t\t\t\t\t\tPress any key to return to main menu:\n\t\t\t\t\t\t");
                fflush(stdin);
                ch=fgetc(stdin);
                flag=1;
                break;

            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
                break;
        }
        if(flag==1)
            break;
    }
}

void mainnenu()
{
    printf("\n                                 **************************************************************************\n");
    printf("                                                     WELCOME TO RESTAURANT MANAGEMENT SYSTEM\n");
    printf("                                 **************************************************************************\n\n\n");
    printf("\t\t\t\t\t\t\t1. ADMIN SECTION--> \n");
    printf("\t\t\t\t\t\t\t2. CUSTOMER SECTION--> \n");
    printf("\t\t\t\t\t\t\t3. Exit--> \n\n");
    printf("\t\t\t\t\t\t\tEnter Your Choice --->");
}

int main()
{
    heada = createadmin(heada,1,"Hot and Sour Soup", 100);
    heada = createadmin(heada,2,"Manchow Soup\t",      200);
    heada = createadmin(heada,3,"Manchurian Noodles",150);
    heada = createadmin(heada,4,"Fried Rice\t",        180);
    heada = createadmin(heada,5,"Hakka Noodles\t",      80);

    while(1)
    {
        mainnenu();
        int choice;
        scanf("%d",&choice);

        if(choice==3)
        {
            printf("\n\n\t\t\t\t\t\t\t**********Thank you!!**********\n");
            break;
        }

        switch (choice)
        {
            case 1:
                admin();
                break;
            case 2:
                customer();
                break;
            case 3:
                break;

            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
                break;
        }
    }
}







