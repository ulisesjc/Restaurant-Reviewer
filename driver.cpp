#include <iostream>
#include "hash.hpp"
#include "PriorityQueue.hpp"
#include <vector> 
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void displayMenu() // do not modify
{
    cout << "------------------" << endl;
    cout << "1: Build the data structure (execute this option one time)" << endl;
    cout << "2: Add a review" << endl;
    cout << "3: Retrieve most recent review for a restaurant" << endl;
    cout << "4: Pop most recent review for a restaurant" << endl;
    cout << "5: Print reviews for a restaurant" << endl;
    cout << "6: Display number of collisions" << endl;
    cout << "7: Display table results" << endl;
    cout << "8: Exit" << endl;
    cout << "------------------" << endl;
}

int main(int argc, char* argv[])
{
    if (argc <3)
    {
        cout<<"need correct number of arguments"<<endl;
    }
	
    string fname = argv[1];
    int tableSize = stoi(argv[2]);
    int ch = 0;
    string chs;
    HashTable ht(5);
    bool flag = true;
	
    while(ch!=8)
    {
        displayMenu();
        cout << "Enter your choice >>";
        getline(cin, chs);
        ch = stoi(chs);
        switch (ch)
        {
            case 1:
			{
                if(flag)
                {
                    ht.setup(argv[1]);
                    flag = false;
                }
                else
                {
                    cout << "ONLY CLICK ONCE" << endl;
                }
				break;
            }
            case 2:
			{
                string rName;
                string customer;
                string review;
                string time;
                cout << "Restaurant Name: " << endl;
                getline(cin, rName);
                cout << "Review: " << endl;
                getline(cin, review);
                cout << "Customer: " << endl;
                getline(cin, customer);
                cout << "Time: " << endl;
                getline(cin, time);
                int newT = stoi(time);

                ReviewInfo r = {rName, review, customer, newT};
                node *restaurant = ht.searchItem(r.restaurantName);
                if(restaurant)
                {
                    restaurant->pq.insertElement(r);
                    cout << "Review Added Successfully!" << endl;
                }
                else
                {
                    ht.insertItem(r);
                    cout << "New Restaurant Added to Review List!" << endl;
                }
                
				break;
            }
            case 3:
			{
                string rName;
                cout << "Restaurant Name:";
                getline(cin , rName);
                cout << "Retrieved result" << endl;
                node* gummyBearNode = ht.searchItem(rName);
                if(gummyBearNode)
                {
                    gummyBearNode->pq.peek();
                }
                else
                {
                    cout << "no record found" << endl;
                }
				break;
            }
            case 4:
			{
                string rName = "";
                cout << "Restaurant Name:" << endl;
                getline(cin, rName);

                node* restaurant = ht.searchItem(rName);
                if(restaurant)
                {
                    restaurant->pq.pop();
                    cout << "Successful pop!" << endl;
                }
                else
                {
                    cout << "Restaurant not found" << endl;
                }
				break;
            }
            case 5:
			{
                string rName;
                cout << "Restaurant Name:" << endl;
                getline(cin, rName);
				node *kodiakNode = ht.searchItem(rName);
                if(kodiakNode)
                {
                    kodiakNode->pq.print();
                }
                else
                {
                    cout << "no record found" << endl;
                }
				break;
			}
            case 6:
            {
                int collisions = ht.getNumCollision();
                cout << "Number of Collisions: " << collisions << endl;
                break;
            }
            case 7:
                ht.displayTable();
                break;
            case 8:
				break;
            default:
                cout << "Enter a valid option." << endl;
                break;
        }
    }
}
