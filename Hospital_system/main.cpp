#include <iostream>
using namespace std;

void menu(int &choice);
void print(string name[][5],int status[][5],int siz);

int add(string name[][5],int status[][5],int siz);
int get(string name[][5],int status[][5],int siz);
int shift(string name[][5],int status[][5],int spec);    //removing function

int que[20] {0};

int main()
{
    string name[20][5];
    int status[20][5] ;

    for(int i=0;i<20;i++)
        for(int j=0;j<5;j++)        //To assign special value to status of (no patient)
          status[i][j]=-1;          //Help us later in printing and shifting(removing) functions

    int choice=1;
    while(choice)
    {
        menu(choice);
        if(choice==1)
            add(name,status,20);
        else if(choice==2)
            print(name,status,20);
        else if(choice==3)
            get(name,status,20);
        else
            break;
    }
    return 0;
}




//MENU//
void menu(int &choice)
{
    cout<<"ENTER YOUR CHOICE"<<"\n";
    cout<<"1) ADD NEW PATIENT"<< "\n";
    cout<<"2) PRINT ALL PATIENTS"<<"\n";
    cout<<"3) GET NEXT PATIENT"<<"\n";
    cout<<"4) EXIT"<<"\n";
    cin>>choice;
}



//ADDING//
int add(string name[][5],int status[][5],int siz)
{
    int spec,stat;
    string str;
    cout<<"specialization name status \n";
    cin>>spec>>str>>stat;
    if(spec>siz || spec <=0)
    {
        cout<<"wrong specialization"<<"\n";
        return 0;
    }
    --spec;
    if(que[spec]<5 && que[spec]>=0)                 // It means we can take one more patient.
    {
        name[spec][que[spec]]=str;
        status[spec][que[spec]]=stat;
    }
    else
    {
        cout<<"sorry,there are no space"<<"\n";
        return 0;
    }

    //SWAPPING PROCESS IF STATUS IS URGENT//
    if(stat==1 && que[spec] != 0)
    {
        int cnt=que[spec];

        while(cnt)
        {
           string tempname;
           int tempstat;

           tempname=name[spec][cnt];
           name[spec][cnt]= name[spec][cnt-1];
           name[spec][cnt-1]= tempname;
                                                                      //swapping process
           tempstat=status[spec][cnt];
           status[spec][cnt]=status[spec][cnt-1];
           status[spec][cnt-1]=tempstat;

           --cnt;
        }
    }
    que[spec]++;                                       //It means -->next queue in this specialization
    return 0;
}




    //PRINTING//
void print(string name[][5],int status[][5],int siz)
{
    for(int i=0;i<siz;i++)
    {
        if(status[i][0] == -1)                           //It means there is no patients any more as status=-1 means--> no patients any more in these spec.
            continue;

        cout<<"There are "<<que[i]<<" patients for specialization "<<i+1<<" are :\n";

        for(int j=0;j<5;j++)
        {
            if(status[i][j]==1)
                cout<<name[i][j]<<" "<<"urgent\n";
            else if(status[i][j]==0)
                cout<<name[i][j]<<" "<<"regular\n";
            else
                break;
        }
    }
    cout<<"There are no more patients\n";
    return;
}




       //GETTING A PATIENT//
int get(string name[][5],int status[][5],int siz)
{
    int spec;
    cin>>spec;
    --spec;                                             // because spec is zero based
    if(status[spec][0]==-1)
        cout<<"there is no patient\n";
    else
    {
        cout<<name[spec][0]<<" please go to DR. HMHM\n";
        shift(name,status,spec);
    }
}



        //SHIFTING(removing) PROCESS//
int shift(string name[][5],int status[][5],int spec)
{
    for(int i=0;i<que[spec];i++)
    {
        name[spec][i]==name[spec][i+1];         //name of last item will equal the carbage of next item.
        status[spec][i]=status[spec][i+1];      // but its status will be -1 so it wont be printed
    }
    que[spec]--;
}

