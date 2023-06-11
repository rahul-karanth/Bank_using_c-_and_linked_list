#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int acc1=100000;    //acc1 is a global variable

//Structure template for date
struct date1
{
    int day;
    int month;
    int year;
};

//Structure template for storing account details
struct account
{
    float trans[20];
    int transcount;
    float balance;
    char name[25];
    char aadharno[13];
    struct date1 dob;
    char mob_no[11];
    int accno;
    char chequeflag;
    char atmpin[5];
    struct account *next;
};

//Delay function to give a time stall
void delay(int i)
{
    int j;
    for(j=0;j<(i*100000000);j++);
}

//Function to go to a particular account
struct account *traversing(struct account **lst,int i)
{
    int j;
    struct account *trv;
    trv=*lst;
    for(j=0;j<i;j++)
        trv=trv->next;
    return trv;
}

//Function to display date of birth
void displaydate(struct account a)
{
    printf("%d/%d/%d\n",a.dob.day,a.dob.month,a.dob.year);
}

//Function to check whether the read date is valid
char validate(int d,int m,int y)
{
    if(d>31)
        return 0;
    if(d>30&&(m==2||m==4||m==6||m==9||m==11))
        return 0;
    if(y>2022)
        return 0;
    if(d>29&&m==2)
        return 0;
    if(y%4!=0&&m==2&&d>28)
        return 0;
    if(m>12)
        return 0;
    return 1;
}

//Function to read the date from user
void readdate(struct account *a)
{
    while(1)
    {
        printf("Enter the day:\n");
        scanf("%d",&(a->dob.day));
        printf("Enter the month:\n");
        scanf("%d",&(a->dob.month));
        printf("Enter the year:\n");
        scanf("%d",&(a->dob.year));
        if(validate(a->dob.day,a->dob.month,a->dob.year))
            break;
        else
        {
            delay(5);
            printf("Invalid date!!Please re input the date\n");
        }
    }
}
char stringcmp(char *c,char*s)
{
    int i;
    for(i=0;c[i]!='\0';i++)
        if(c[i]!=s[i])
            return 0;
    return 1;

}
void pingen(char *ca)
{
    char pword[13],c=' ';
    int i=0;
    while(1)
    {
        printf("please enter your new atm pin\n");
        while(i<4)
        {
            c=getch();
            if(c>='0'&&c<='9')
            {
                pword[i]=c;
                printf("*");
                i++;
            }
        }
        pword[i]='\0';
        printf("\n");
        printf("please re-enter your atm pin\n");
        i=0;
        while(i<4)
        {
            c=getch();
            if(c>='0'&&c<='9')
            {
                ca[i]=c;
                printf("*");
                i++;
            }
        }
        ca[i]='\0';
        if(stringcmp(pword,ca))
        {
            printf("\npin generated successfully\n");
            delay(5);
            break;
        }
        else
            printf("\nthe re-entered pin does not match!!\n");
        i=0;
    }
}

//Function to create a new account
struct account *assign1(struct account *a)
{
    char c;
    int i;
    float balance;
    a->transcount=0;
    printf("Enter your name:\n");
    scanf("%s",a->name);
    printf("Enter your Aadhaar number:\n");
    for(i=0;i<=12;i++)
    {
        scanf("%c",&a->aadharno[i]);
    }
    a->aadharno[i]='\0';
    printf("Enter your date of birth:\n");
    readdate(a);
    printf("Enter your mobile number:\n");
    for(i=0;i<=10;i++)
        scanf("%c",&a->mob_no[i]);
    a->mob_no[i]='\0';
    a->accno=acc1++;
    while(1)
    {
        printf("do you want cheque?(y/n)\n");
        scanf(" %c",&c);
        if(c=='y')
        {
            a->chequeflag=1;
            break;
        }
        else if(c=='n')
        {
            a->chequeflag=0;
            break;
        }
        else
            printf("wrong input!!please re-enter the input\n");
    }
    while(1)
    {
        printf("enter the first deposit amount\n");
        scanf("%f",&balance);
        if((a->chequeflag==1&&balance<1000)||(a->chequeflag==0&&balance<500))
            printf("minimum balance should be 1000!!please re-enter the deposit(amount was not deposited and deducted)\n");
        else
        {
            printf("amount has been deposited\n");
            a->balance=balance;
            a->trans[a->transcount++]=balance;
            break;
        }
    }
    pingen(a->atmpin);
    printf("Account created!!\n");
    a->next=NULL;
    delay(5);
    return a;
}

//Function to store the new account details in the database
struct account *create(struct account *list)
{
    struct account *tmp,*trv;
    tmp=(struct account *)malloc(sizeof(struct account));
    tmp=assign1(tmp);
    if(list==NULL)
    {
        list=tmp;
    }
   else
   {
       trv=list;
       while(trv->next!=NULL)
       {
           trv=trv->next;
       }
       trv->next=tmp;
   }
   return (list);
}

//Function to display the account details
void displayaccdet(struct account a)
{
    printf("Balance=>%f\nName=>%s\nAadhaar no=>%s\nMobile no=>%s\nAccount no=>%d\n",a.balance,a.name,a.aadharno,a.mob_no,a.accno);
    printf("Date of birth:");
    displaydate(a);
    delay(10);
}

//Function to display customer details
void displaycust(struct account *a,int i)
{
    int j;
    for(j=0;j<i;j++)
    {

        printf("(%d).%s(account no:%d)\n",j+1,a->name,a->accno);
        a=a->next;
    }
}

//Function to traverse for a particular account
struct account *traverse(struct account *lst,int i,int *f)
{
    struct account *trv;
    trv=lst;
    *f=1;
    while(trv!=NULL)
    {
        if(trv->accno==i)
            break;
        trv=trv->next;
    }
    if(trv==NULL)
        *f=0;
    return trv;
}

//Function to implement withdrawal of amount
struct account *withdraw(struct account *a)
{
    float w;
    printf("Enter the withdrawal amount:\n");
    scanf("%f",&w);
    delay(5);
    if(a->balance>=w)
    {
        a->balance-=w;
        a->trans[a->transcount++]=(w*-1.0);
        printf("successful withdrawal\n");
    }
    else
    {
                printf("!!Insufficient balance!!\nSorry!!withdrawal not possible\n");
    }
    return a;
}

//Function to implement deposition of money
struct account *deposit(struct account *a)
{
    float d;
    printf("Enter the amount:\n");
    scanf("%f",&d);
    a->balance=a->balance+d;
    a->trans[a->transcount++]=d;
    printf("successful deposit\n");
     delay(5);
    return a;
}

//Function to list all the transactions
void transactions(struct account *a)
{
    int i;
    printf("Transactions:\n");
    if(a->transcount==0)
        printf("No transactions have happened till now\n");
    for(i=0;i<a->transcount;i++)
    {
        printf("%d.%f\n",i+1,a->trans[i]);
    }
}

//Function to modify the account,if needed
struct account *modify(struct account *a)
{
        int choice,k=0,flag=1;
        char pword[14],c;
        printf("1.Name\n2.Aadhaar number\n3.Date of birth\n4.Mobile no\n5.atm pin\nenter your choice:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:printf("Enter the new name:\n");
                    scanf("%s",a->name);
                    break;
            case 2:printf("Enter the new aadhaar no:\n");
                    scanf("%s",a->aadharno);
                    break;
            case 3:printf("Enter the modified date of birth:\n");
                    readdate(a);
                    break;
            case 4:printf("Enter the new mobile number:\n");
                    scanf("%s",a->mob_no);
                    break;
            case 5:printf("please enter the old atm pin:\n");
                    while(k<4)
                    {
                        c=getch();
                        if(c>='0'&&c<='9')
                        {
                            pword[k]=c;
                            printf("*");
                            k++;
                        }
                    }
                    pword[k]='\0';
                    if(stringcmp(pword,a->atmpin))
                    {
                        printf("\npin authentication successful\n");
                        pingen(a->atmpin);
                    }
                    else
                    {
                        printf("\nwrong pin!!\n");
                        flag=0;
                    }
                    break;
            default:printf("Invalid choice\n");
                    flag=0;
        }
        delay(5);
        if(flag)
            printf("Account updated\n");
        else
            printf("Account not updated\n");
        return a;
}

//Function to delete any account
struct account *deleteacc(struct account *a,int j)
{
    struct account *del,*trv,*tmp;
    int i;
    del=a;
    if(a->next==NULL)
    {
        a=NULL;
    }
    else
    {
        tmp=traverse(a,j,&i);
        if(tmp==a)
        {
            a=tmp->next;
        }
        else
        {
            trv=a;
            while(trv->next!=tmp)
            {
                trv=trv->next;
            }
            del=trv->next;
            trv->next=tmp->next;
        }
    }
    free(del);
    printf("!!Account deleted!!\n");
    delay(5);
    return a;
}

//Function to check account balance
void checkbalance(struct account *tmp)
{
    printf("Balance=%f\n",tmp->balance);
}

//Function to perform various operations
struct account *atm(struct account *a,int j,int *i)
{
    int choice,k=0,l;
    struct account *tmp;
    char c,pword[13];
    tmp=traverse(a,j,&l);
    if(l==0)
    {
        printf("invalid account number!!\n");
        return a;
    }
    printf("please enter the atm pin:\n");
    while(k<4)
    {
       c=getch();
            if(c>='0'&&c<='9')
            {
                pword[k]=c;
                printf("*");
                k++;
            }
    }
    pword[k]='\0';
     if(stringcmp(pword,tmp->atmpin))
     {
        printf("\npin authentication successful\n");
       do
        {
            printf("1.Withdraw\n2.Deposit\n3.Check balance\n4.Transactions\n5.Display account info\n6.Modify/update account info\n7.Exit\nEnter your choice:\n");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1:tmp=withdraw(tmp);
                    break;
                case 2:tmp=deposit(tmp);
                    break;
                case 3:checkbalance(tmp);
                    break;
                case 4:transactions(tmp);
                    delay(5);
                    break;
                case 5:displayaccdet(*tmp);
                    break;
                case 6:tmp=modify(tmp);
                    break;
                case 7:break;
                default:printf("!!Invalid choice!!\n");
            }
            delay(5);
        }while(choice!=7);
     }
     else
     {
         printf("\nwrong pin!!\n");
     }
    return a;
}
struct account *travandaut(struct account *a,int j,int *l)
{
    int choice,k=0;
    struct account *tmp;
    char c,pword[13];
    tmp=traverse(a,j,l);
    if(*l==0)
    {
        printf("invalid account number!!\n");
        return a;
    }
    printf("please enter the atm pin:\n");
    while(k<4)
    {
       c=getch();
            if(c>='0'&&c<='9')
            {
                pword[k]=c;
                printf("*");
                k++;
            }
    }
    pword[k]='\0';
     if(stringcmp(pword,tmp->atmpin))
     {
        printf("\npin authentication successful\n");
     }
     else
     {
        printf("\nwrong pin!!\n");
        *l=0;
     }

     return tmp;
}
//Driver code to test all the above functions
int main()
{
    struct account *lst,*tmp;
    int choice,i=0,acc,flag;
    char c1[2];
    lst=NULL;
    system("COLOR 0a");
    do
    {
        printf("Welcome to One Nation Bank Corp.\nHow can we help you?\n");
        printf("1.Create account\n2.ATM\n3.Customer list\n4.Update information\n5.Delete existing account\n6.Exit\nEnter your choice:\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:lst=create(lst);
                    i++;
                    break;
            case 2:if(i!=0)
                    {
                        displaycust(lst,i);
                        printf("Enter the account no:\n");
                        scanf("%d",&acc);
                        if(acc<=acc1&&acc>=100000)
                            lst=atm(lst,acc,&i);
                        else
                            printf("!!Invalid account number!!\n");
                    }
                    else
                        printf("No accounts exist\n");
                   break;
            case 3:if(i!=0)
                        displaycust(lst,i);
                    else
                        printf("No accounts exist\n");
                    break;
            case 4:if(i!=0)
                    {
                        displaycust(lst,i);
                        printf("Enter the account no:\n");
                        scanf("%d",&acc);
                        if(acc<=acc1&&acc>=100000)
                        {
                            tmp=travandaut(lst,acc,&flag);
                            if(flag==0)
                                break;
                            tmp=modify(tmp);
                        }
                        else
                            printf("!!Invalid account number!!\n");
                    }
                    else
                        printf("No accounts exist\n");
                    break;
            case 5:if(i!=0)
                    {
                        displaycust(lst,i);
                        printf("Enter the account no:\n");
                        scanf("%d",&acc);
                        while(1)
                        {
                            if(acc<=acc1&&acc>=100000)
                            {
                                tmp=travandaut(lst,acc,&flag);
                                if(flag==0)
                                    break;
                                if(tmp->balance==0)
                                {
                                    lst=deleteacc(tmp,acc);
                                    i--;
                                    break;
                                }
                                else
                                {
                                    printf("please withdraw all your amount to delete\n");
                                    printf("do you want to withdraw?balance=>%f(type y-if yes)\n",tmp->balance);
                                    scanf("%s",c1);
                                    if(c1[0]=='y')
                                    {
                                        tmp=withdraw(tmp);
                                        if(tmp->balance==0)
                                        {
                                            lst=deleteacc(tmp,acc);
                                            i--;
                                            break;
                                        }
                                        else
                                        {
                                            printf("still amount is left in your balance!!\naccount not deleted!!\n");
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        printf("account not deleted!!\n");
                                        break;
                                    }
                                }
                            }
                            else
                                printf("!!Invalid account number!!\n");
                                break;
                        }
                    }
                    else
                        printf("No accounts exist\n");
                    break;
            case 6:break;
            default:printf("!!INVALID CHOICE!!\n");
        }
         delay(5);
    }while(choice!=6);
    printf("Thank you for using our service!\n");
}
