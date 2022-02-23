#include <iostream>
#include <fstream>
using namespace std;

struct stacklist
{
    int CId;
    struct stacklist *next;
};
struct serialC
{
    int priority;
    int CId;
};
struct Node
{
    int CId;
    string name;
    int milage;
    int year;
    int serial;
    int priority;
    struct Node *next;
};

struct Node *head1;
struct Node *tail1;

struct stacklist *head2;
struct stacklist *tail2;


void list_input(int CId,string name,int milage,int year,int serial ,int priority)
{
    struct Node *newnode;
    newnode=new Node();
    newnode->next=NULL;
    newnode->CId=CId;
    newnode->name=name;
    newnode->milage=milage;
    newnode->year=year;
    newnode->serial=serial;
    newnode->priority=priority;

    if(head1==NULL)
    {
        head1=newnode;
        tail1=newnode;

    }
    else
    {
        tail1->next=newnode;
        tail1=newnode;
    }

}
void inputin_stack(int id)
{
    struct stacklist *node;
    node=new stacklist();
    node->CId=id;
    node->next=NULL;
    if(head2==NULL)
    {
        head2=node;
        tail2=node;
    }
    else
    {
        node->next=head2;
        head2=node;
    }

}
int fun_priority(int milage, int years,int seq)
{
    int prio=0;
    prio=(milage/1000)+years-seq;
    return prio;
}
void displaycust_fun()
{
    struct Node *temp;
    temp=head1;
    int i=1;

    while(temp !=NULL)
    {
        cout<<i<<" "<<temp->name<<"    \t"<<temp->milage<<"\t"<<temp->year<<"\t"<<temp->serial<<"  "<<temp->priority<<"\n";
        i++;
        temp=temp->next;
    }
}
void fundata_swapping(struct serialC data[],int p,int parent)
{
    int tempprio=0;
    int custid=0;
    int parentdata=data[parent].priority;
    int posdata=data[p].priority;;
    tempprio=data[p].priority;
    data[p].priority=data[parent].priority;
    data[parent].priority=tempprio;
    int parentcustid=data[parent].CId;
    int poscustid=data[p].CId;
    custid=data[p].CId;
    data[p].CId=data[parent].CId;
    data[parent].CId=custid;
}
void fun_reheapup(struct serialC data[],int p)
{
    if(p!=1)
    {
        int parent=0;
        parent=p/2;
        int p1=data[p].priority;
        int p2=data[parent].priority;
        if(data[p].priority>data[parent].priority)
        {
            fundata_swapping(data,p,parent);
            fun_reheapup(data,parent);
        }
    }
}
void fun_reheapdown(struct serialC data[],int p,int n)
{
    if(p <=n)
    {
        int child1=0;
        int child2=0;
        int l=child1;
       int  r=child2;
        l=2*p;
        r=2*p+1;
        int ldata=data[l].priority;
        int rdata=data[r].priority;
        if(l <=n && r<=n)
        {
            if(data[l].priority>data[r].priority)
            {
                fundata_swapping(data,l,p);
                fun_reheapdown(data,l,n);
            }
            else
            {
                fundata_swapping(data,r,p);
                fun_reheapdown(data,r,n);
            }
        }
        else if(l<=n && r>n)
        {

            fundata_swapping(data,l,p);
            fun_reheapdown(data,l,n);

        }
        else if(l>n && r<=n)
        {

            fundata_swapping(data,r,p);
            fun_reheapdown(data,r,n);

        }

    }
}


int heaplist_create(struct serialC data[])
{
    int i=1;
    struct Node*temp;
    temp=head1;
    while(temp !=NULL)
    {
        data[i].priority=temp->priority;
        data[i].CId=temp->CId;
        fun_reheapup(data,i);
        i++;
        temp=temp->next;

    }
    return i;
}
void fundisplay_serially(int CId,int i)
{
    struct Node *temp;
    temp=head1;

    while(temp !=NULL)
    {
        if(temp->CId==CId)
        {
            cout<<i<<" "<<temp->name<<"    \t"<<temp->milage<<"\t"<<temp->year<<"\t"<<temp->serial<<"  "<<temp->priority<<"\n";
            i++;

        }
        temp=temp->next;

    }
}
void display_namelist(int CId)
{
    struct Node *temp;
    temp=head1;

    while(temp !=NULL)
    {
        if(temp->CId==CId)
        {
            cout<<" "<<temp->name<<"\n";


        }
        temp=temp->next;

    }
}
void fundisplay_seriallystack()
{
    struct stacklist *temp;
    temp=head2;
    int i=1;

    while(temp !=NULL)
    {
        fundisplay_serially(temp->CId,i);
        temp=temp->next;
        i++;

    }
}
int manu()
{
    cout<<"\n";
    cout<<"1.Display with Priority ->\n";
    cout<<"2.Give Ticket to Priority First Customer ->\n";
    cout<<"3.Display All Waiting and Served Customer ->\n";
    int k =0;
    cin>>k;
    return k;
}
int main()
{
    ifstream getProduct("data.txt");

    int i=0;
    int custId;
    string name;
    int milage;
    int year;
    int serial;
    while(getProduct>>custId>>name>>milage>>year>>serial)
    {
        int prio=fun_priority(milage,year,serial);
        list_input(custId,name,milage,year,serial,prio);
        i++;
    }
    struct serialC data[100];
    int n=0;
    n=heaplist_create(data)-1;
    while(1)
    {
        int k=manu();

        if(k==1)
        {
            for(i=1; i<=n; i++)
            {
                fundisplay_serially (data[i].CId,i);
            }
        }
        if(k==2)
        {
            while(1)
            {
                cout<<" Are You want to take ticket ? 0/1--> ";
                int k=0;
                if(n!=0)
                {
                    cin>>k;
                }
                else
                {
                    cout<<"\n There is No Customer Waiting on Queue ";
                    break;
                }

                if(k==1)
                {
                    cout<<"Ticket taken for Customer : ";
                    display_namelist(data[1].CId);
                    inputin_stack(data[1].CId);
                    data[1].CId=data[n].CId;
                    data[1].priority=data[n].priority;
                    fun_reheapdown(data,1,n);
                    n--;
                }
                else
                {
                    break;
                }
            }
        }
        if(k==3)
        {
            cout<<"Ticket taken customer \n";
            fundisplay_seriallystack();
            cout<<"\n Ticket Remaining Customer \n";
            for(i=1; i<=n; i++)
            {
                fundisplay_serially(data[i].CId,i);
            }
        }
    }
}


