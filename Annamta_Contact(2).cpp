#include<iostream>
#include<fstream>
#include<cstdlib>
using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;
class contact_query
{
private:
    char firstName[20];
    char lastName[20];
    char number [10];
public:
    void read_contact();
    void show_contact();
    void write_contact();
    void search_contact();
    void edit_contact();
    void delete_contact();
    void read_contact_file();
};
void contact_query::read_contact()
{
    cout<<"\nEnter First Name: ";
    cin>>firstName;
    cout<<"\nEnter Last Name: ";
    cin>>lastName;
    cout<<"\nEnter Number: ";
    cin>>number;
    cout<<endl;
}
void contact_query::show_contact()
{
    cout<<"Contact Number: "<<number<<endl;
    cout<<"First Name: "<<firstName<<endl;
    cout<<"Last Name: "<<lastName<<endl;
    cout<<"Current Number: Rs.  "<<number<<endl;
    cout<<"-------------------------------"<<endl;
}
void contact_query::write_contact()
{
    ofstream outfile;
    outfile.open("record.contact", ios::binary|ios::app);
    read_contact();
    outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
    outfile.close();
}
void contact_query::read_contact_file()
{
    ifstream infile;
    infile.open("record.contact", ios::binary);
    if(!infile)
    {
        cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
    }
    cout<<"\n****Data from file****"<<endl;
    while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))>0)
        {
            show_contact();
        }
    }
    infile.close();
}
void contact_query::search_contact()
{
    int n;
    ifstream infile;
    infile.open("record.contact", ios::binary);
    if(!infile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" contact(s) in the file";
    cout<<"\n Enter Contact Number to Search: ";
    cin>>n;
    infile.seekg((n-1)*sizeof(*this));
    infile.read(reinterpret_cast<char*>(this), sizeof(*this));
    show_contact();
}
void contact_query::edit_contact()
{
    int n;
    fstream iofile;
    iofile.open("record.contact", ios::in|ios::binary);
    if(!iofile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    iofile.seekg(0, ios::end);
    int count = iofile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" contact(s) in the file";
    cout<<"\n Enter Contact Number to edit: ";
    cin>>n;
    iofile.seekg((n-1)*sizeof(*this));
    iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
    cout<<"Contact "<<n<<" has following data"<<endl;
    show_contact();
    iofile.close();
    iofile.open("record.contact", ios::out|ios::in|ios::binary);
    iofile.seekp((n-1)*sizeof(*this));
    cout<<"\nEnter data to Modify "<<endl;
    read_contact();
    iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
}
void contact_query::delete_contact()
{
    int n;
    ifstream infile;
    infile.open("record.contact", ios::binary);
    if(!infile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" contact(s) in the file";
    cout<<"\n Enter Contact Number to Delete: ";
    cin>>n;
    fstream tmpfile;
    tmpfile.open("tmpfile.contact", ios::out|ios::binary);
    infile.seekg(0);
    for(int i=0; i<count; i++)
    {
        infile.read(reinterpret_cast<char*>(this),sizeof(*this));
        if(i==(n-1))
            continue;
        tmpfile.write(reinterpret_cast<char*>(this), sizeof(*this));
    }
    infile.close();
    tmpfile.close();
    remove("record.contact");
    rename("tmpfile.contact", "record.contact");
}
int main()
{
    contact_query A;
    int choice;
    cout<<"***Contact Information System***"<<endl;
    while(true)
    {
        cout<<"Select one option below ";
        cout<<"\n\t1-->Add contact";
        cout<<"\n\t2-->Show saved contacts";
        cout<<"\n\t3-->Search contact from file";
        cout<<"\n\t4-->Update contact";
        cout<<"\n\t5-->Delete contact";
        cout<<"\n\t6-->Quit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            A.write_contact();
            break;
        case 2:
            A.read_contact_file();
            break;
        case 3:
            A.search_contact();
            break;
        case 4:
            A.edit_contact();
            break;
        case 5:
            A.delete_contact();
            break;
        case 6:
            exit(0);
            break;
        default:
            cout<<"\nEnter correct choice";
            exit(0);
        }
    }
    system("pause");
    return 0;
}
