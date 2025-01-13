// CPP program to implement hashing with chaining
#include <iostream>
#include "hash.hpp"
#include <sstream>

using namespace std;

node* HashTable::createNode(string restaurantName, node* next)
{
    node *newNode = new node{restaurantName, 50, next};
    return newNode;
}

HashTable::HashTable(int bsize)
{
    numCollision = 0;
    tableSize = bsize;
    table = new node*[tableSize];
    for(int i = 0; i < tableSize; i++)
    {
        table[i] = nullptr;
    }
}

HashTable::~HashTable()
{
    node* temp;
    node* next;
    for(int i = 0; i < tableSize; i++)
    {
        if(table[i] != nullptr)
        {
            temp = table[i];
            while(temp != nullptr)
            {
                next = temp->next;
                delete temp;
                temp = next;
            }
            table[i] = nullptr;
        }
    }
    delete[] table;
}

void HashTable::displayTable()
{
    node* current = nullptr;
    for(int i = 0; i < tableSize; i++)
    {
        current = table[i];
        cout << i << "|";
        while(current != nullptr)
        {
            cout << current->restaurantName << "-->";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
}

unsigned int HashTable::hashFunction(string restaurantName)
{
    unsigned int sum = 0;
    for(int i = 0; i < restaurantName.length(); i++)
    {
        sum += restaurantName[i];
    }
    return sum % tableSize;
}

node* HashTable::searchItem(string restaurantName)
{
    int index = hashFunction(restaurantName);
    node *current = table[index];
    while(current != nullptr)
    {
        if(current->restaurantName == restaurantName)
        {
            return current;
        }
        current = current -> next;
    }
    return nullptr;
}

void HashTable::insertItem(ReviewInfo restaurant)
{
    node *newNode = searchItem(restaurant.restaurantName);
    if(newNode)
    {
        newNode->pq.insertElement(restaurant);
    }
    else
    {
        newNode = createNode(restaurant.restaurantName, nullptr);
        newNode->pq.insertElement(restaurant);
        int index = hashFunction(restaurant.restaurantName);
        if(table[index] == nullptr)
        {
            table[index] = newNode;
        }
        else
        {
            numCollision++;
            newNode->next = table[index];
            table[index] = newNode;
        }
    }
    
}


void HashTable::setup(string fname)
{
    ifstream myfile;
    myfile.open(fname);
    string line;
    string rName;
    string review;
    string customer;
    string time;
    while(getline(myfile, line))
    {
        stringstream ss(line);
        getline(ss, rName, ';');
        getline(ss, review, ';');
        getline(ss, customer, ';');
        getline(ss, time, ';');
        int militaryTime = stoi(time);

        ReviewInfo r;
        r.restaurantName = rName;
        r.review = review;
        r.customer = customer;
        r.time = militaryTime;    
        insertItem(r);
    }

    //stringstream
    //while loop
    //create instances
    //set attributes
    //insertitem(isntances)
}

//focus on hash.cpp
// then when you need to go to q, switch over