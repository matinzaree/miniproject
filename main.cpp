//


#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "product.h"
#include "customer.h"
#include "money.h"
using namespace std;



int main()
{
    string date;
    cout<<"enter date: ";
    cin>>date;
    int productid=add_id();
    int customerid=customer_id();

    bool loop = true;
    while (loop)
    {
        int choice;
        cout << "1. Search product" << endl;
        cout << "2. Add products" << endl;
        cout << "3. Edit product" << endl;
        cout << "4. Place an order" << endl;
        cout << "5. Show orders preview" << endl;
        cout << "6. Show order details" << endl;
        cout << "7. Financial report" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            searchproduct();
        }
        else if (choice == 2)
        {
            addproduct(productid);
            save_prid(productid);
        }
        else if (choice == 3)
        {
            editproduct();
        }
        else if (choice == 4)
        {
            customer_massage(customerid);
            save_csid(customerid);
        }
        else if (choice == 5)
        {
            opencustomer_showcustomer();
        }
        else if (choice == 6)
        {
            opencustomer_detailsorder();
        }
        else if (choice == 7)
        {
            money(date);
        }
        else if (choice == 0)
        {
            loop = false;
        }
    }

    return 0;
}


