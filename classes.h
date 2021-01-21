
#include<iostream>
#include<string.h>

using namespace std;

//----------------------------NODE---------------------------
template<class t>
class node
{
public:
    t data;
    node<t> * next;
};
//----------------------------LINKED LIST--------------------
template<class t>
class linked_list
{
public:
    node<t> *head, *tail;
    int size;
    linked_list()                           //Default Constructor
    {
        head = tail = nullptr;
        size = 0;
    }
    linked_list(const linked_list<t> &obj)       //Copy Constructor
    {
        tail = nullptr;
        head = nullptr;
        this->size = 0;
        node<t> * current = obj.head;
        while(current != nullptr)
        {
            this->insert_at_end(current->data);
            current = current->next;
        }
    }
    void insert_at_end(const t & data)
    {
        node<t> * new_node = new node<t>;
        new_node->data = data;                      //assignment operator invoked
        if(head != nullptr)
        {
            tail->next = new_node;
            new_node->next = nullptr;
            tail = new_node;
        }
        else
        {
            new_node->next = nullptr;
            head = tail = new_node;
        }
        size++;    
            
    }
    void delete_from_start()
    {
        if(head != nullptr)
        {
            node<t> * current = head;
            head = head->next;
            delete current;
        }
        size--;
    }
    void delete_from_end()
    {
        if(head != nullptr)
        {
            if(head == tail)
            {
                delete tail;
                head = tail = nullptr;
                size--;
            }
            else
            {
                node<t> * current = head;
                while(current->next != tail)
                {
                    current = current->next;
                }
                delete(current->next);              //verify... deletes pointer ?? or next node ??
                tail = current;
                tail->next = nullptr;
                size--;
            }   
        }
    }
    void delete_from_middle(node<t> * ptr)      //ptr is the address to be deleted
    {
        if(head != nullptr)
        {
            if(head != tail)
            {
                node<t> * current = head;
                while (current->next != ptr && current != nullptr)
                {
                    current = current->next;
                }
                if(current->next == ptr)
                {
                    node<t> * temp = ptr->next;
                    delete ptr;
                    current->next = temp;
                }
                else
                {
                    cout << "Address not Found...\n";
                }
            }
            else
            {
                delete head;
                head = tail = nullptr;
            }
        }
        size--;
    }

    linked_list<t> operator=(const linked_list<t> & obj)
    {
        node<t> * current = obj.head;
        this->size = obj.size;
        while(current != nullptr)
        {
            node<t> * temp;
            this->insert_at_end(current->data);
            current = current->next;
        }
        return *this;
    }
    void print()
    {
        cout << "Linked List Size : " << this->size << endl;
        node<t> * current = this->head;
        while(current != nullptr)
        {
            cout << current->data << endl;
            current = current->next;
        }
    }
    void swap(node<t> * ptr1, node<t> * ptr2)
    {
        t temp = ptr1->data;
        ptr1->data = ptr2->data;
        ptr2->data = temp;
    }
    void sort()
    {
        node<t> * temp;
        node<t> * current_1 = head;
        node<t> * current_2 = current_1->next;
        while(current_1->next != nullptr)
        {
            current_2 = current_1->next;
            while(current_2 != nullptr)
            {
                if(current_1->data > current_2->data)
                {
                    swap(current_1,current_2);
                }
                current_2 = current_2->next;
            }
            current_1 = current_1->next;
        }
    }
};
//--------------------------------BLOCK----------------------------
class block
{
public:
    int start_id;
    int total_sectors;
    block()
    {
        start_id = 0;
        total_sectors = 0;
    }
    block(const block & obj)
    {
        this->total_sectors = obj.total_sectors;
        this->start_id = obj.start_id;
    }
    block(int index, int size)
    {
        start_id = index;
        total_sectors = size;
    }
    bool operator>(const block & obj)
    {
        if(this->start_id > obj.start_id)
        {
            return true;
        }
        return false;
    }
    block operator=(const block & obj)
    {
        this->total_sectors = obj.total_sectors;
        this->start_id = obj.start_id;
        return *this;
    }
    friend ostream &operator<<(ostream &output, const block & obj)
    {
        output << "Starting Index : " << obj.start_id << endl;
        output << "Total Sectors : " << obj.total_sectors << endl;
        return output;
    }

};
//-------------------------------FILE----------------------------
class file
{
public:
    string name;
    int size;
    linked_list<block> * blocks = new linked_list<block>;
    file()
    {
        this->name = "";
        this->size = 0;
        this->blocks = nullptr;
    }
    file(const file & obj)
    {
        this->name = obj.name;
        this->size = obj.size;
        this->blocks = obj.blocks;
    }
    file(string name, int size, linked_list<block> & block_list)
    {
        this->name = name;
        this->size = size;
        this->blocks->head = block_list.head;
    }
    friend ostream &operator<<(ostream &output, const file & obj)
    {
        output << "File Name : " << obj.name << endl;
        output << "File Size : " << obj.size << endl;
        node<block> * current = obj.blocks->head;
        while(current != nullptr)
        {
            output << current->data;
            current = current->next;
        }
        return output;
    }
    file operator=(const file & obj)
    {
        this->name = obj.name;
        this->size = obj.size;
        this->blocks = obj.blocks;
        return *this;
    }
};
//-------------------------------FILESYSTEM-------------------------
class file_system
{
public:
    linked_list<block> * pool = new linked_list<block>;
    linked_list<file> * files = new linked_list<file>;
    char * disk = new char[100];
    int num_of_sectors = 100;
    int num_of_sectors_in_pool = 100;               //free sectors
    int size_of_sector = 1;
    int current_index = 0;
    
    file_system()
    {
        //cout << "Here\n";
    }
    ~file_system()
    {
        //cout << "Here";
        delete[] disk;
    }
    void save_file(string name, int size, string content)
    {
        if(num_of_sectors_in_pool > size)
        {
            linked_list<block> blocks_of_file;
            block new_block(current_index,size);
            blocks_of_file.insert_at_end(new_block);
            for(int i = current_index, j = 0; j < size; i++, j++)
            {
                disk[i] = content[j];
                num_of_sectors_in_pool--;
                current_index++;
            }
            block block_of_pool(current_index,num_of_sectors_in_pool);
            pool->insert_at_end(block_of_pool);
            file new_file(name,size,blocks_of_file);
            files->insert_at_end(new_file);
            pool->sort();
        }
    }
    void read_data(string name)
    {
        bool found = false;
        node<file> * current = this->files->head;
        //cout << current;
        while(current != nullptr && found == false)
        {
            if(current->data.name == name)
            {
                node<block> * temp = current->data.blocks->head;
                cout << current->data;
                cout << "Content : ";   
                while(temp != nullptr)
                {
                    //prints character by character
                    for(int i = temp->data.start_id; i < (temp->data.start_id + temp->data.total_sectors); i++)
                    {
                        cout << disk[i];
                    }
                    temp = temp->next;
                }
                found = true;
                cout << endl;
            }
            else
            { 
                current = current->next;
            }
        }
        if(found == false)
        {
            cout << "File not found...\n";
        }
    }
    void delete_file(string name)
    {
        bool found = false;
        node<file> * current = this->files->head;
        //cout << current;
        while(current != nullptr && found == false)
        {
            if(current->data.name == name)
            {
                
                pool->insert_at_end(current->data.blocks->head->data);
                cout << endl << current->data.name << " File is ";
                found = true;
                files->delete_from_start();
                //this->files->size--;
            }
            current = current->next;
            pool->sort();
        }
    }
};


/*
        NOTE : Sorry for the Inconvenience

This program doesn't handle the pool properly i.e. it can sort the pool and make blocks in it
but this program can't update the spaces/gaps between. It will delete the file, read the file, and save it
but it will not save file when there are gaps. 
Secondly, in this program I have used sector of 1 byte.
We can change that by using "string" array instead of character array and we can determine the size of file
with strlen() function. String will be a substitute for 2D-Character Array.

Because it can not save file with gaps, the following two features are commented...

MERGING 2 BLOCKS:

if(block_1.sector_id + total_sectors == block_2.start_id)  //means that block 2 is after block 1
{
    block new_block(block_1.start_id, block_2.start_id + block_2.total_ectors) //block-2 start+total = size
    pool->delete_from_middle(block_1);      //address of block-1 as arguement
    pool->delete_from_middle(block_2);      //address of block-2 as arguement
    pool->insert_at_end(new_block);
    pool->sort();
}

DELETING FILES when there's GAP Between THEM:

we'll modify the function delete_file() by adding this loop.
Before, the program was deleting only one element/block. In the assignment, however, we have multiple blocks.
To delete blocks, we will add this loop in the delete_file() funtion.

bool found = false;
node<file> * current = this->files->head;
while(current != nullptr && found == false)
{
    if(current->data.name == name)          //if name matches with file
    {
        node<block> * temp = current->data.blocks->head;
        while(temp != nullptr)
        {
            pool->insert_at_end(temp->data);        //will assign block in pool
            temp = temp->next;                      //next block
        }
        found = true;
        files->delete_from_start();
    }
    current = current->next;
}
pool->sort();

*/