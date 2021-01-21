
#include"classes.h"


void menu()
{
    cout << endl << endl;
    cout << " Press 1 to Create & Save File" << endl;
    cout << " Press 2 to Read File" << endl;
    cout << " Press 3 to Delete File" << endl;
    cout << " Press 0 to Exit" << endl;
    cout << " Enter your choice : ";
}

void driver_function()
{
    int choice;
    cout << "Press 1 to create a File system : ";
    cin >> choice;
    if (choice == 1)
    {
        file_system s1;
        menu();
        cin >> choice;
        while(choice != 0)
        {
            if(choice == 1)
            {
                string name;
                int size;
                string content;
                cout << endl << "Enter Name of File : ";
                cin >> name;
                cout << endl << "Enter the Content : ";
                cin >> content;
                cout << endl << "Enter the Size : ";
                cin >> size;
                s1.save_file(name,size,content);
            }
            else if(choice == 2)
            {
                string name;
                cout << "\nEnter the name of file : ";
                cin >> name;
                s1.read_data(name);
            }
            else if(choice == 3)
            {
                string name;
                cout << "\nEnter the name of file : ";
                cin >> name;
                s1.delete_file(name);
            }
            else
            {
                cout << "Invalid Choice...\n";
            }
            menu();
            cin >> choice;
        }        
    }
    else
    {
        cout << "Invalid selection... Run the program again...\n";
    }
    

}


//Uncomment the driver function.
int main()
{
/*
    linked_list<int> l1;
    l1.insert_at_end(9);
    l1.insert_at_end(19);
    l1.insert_at_end(3);
    l1.insert_at_end(21);
    l1.sort();
    l1.print();
    block a(1,1);
    block b(2,1);
    block c(1,2);
    block d(2,2);
    linked_list<block> b1;
    b1.insert_at_end(a);
    b1.insert_at_end(b);
    b1.insert_at_end(c);
    b1.insert_at_end(d);
    linked_list<block> b2(b1);
    //b2.print();
    file f1("Sample",10,b1);
    file f2;
    f2 = f1;
    cout << f2;
*/
    //driver_function();
    file_system system_1;
    string content = "HAHAHAHA";
    system_1.save_file("Sample-file-1",8,content);
    content = "LLLL";
    system_1.save_file("Sample-file-2",4,content);
    system_1.read_data("Sample-file-2");
    system_1.delete_file("Sample-file-1");
    cout << "Content on disk (not deleted) : " << system_1.disk << endl;
    cout << endl;




}