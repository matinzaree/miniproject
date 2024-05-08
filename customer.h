//
// Created by matin on ۰۷/۰۵/۲۰۲۴.
//

#ifndef PRJ_CUSTOMER_H
#define PRJ_CUSTOMER_H
#include <string>

using namespace std;

class Customer
{
public:
    string name;
    int phone;
    int totall_price;
    int customer_id;
};

class Order
{
public:
    Product product;
    string date;
    int discount;
    int order_id;
};

void place_orderbyid(vector<Customer>& customers);
void place_order(int id);
void opencustomer();

int customer_id(){
    int i=0;
    ifstream addid("customerid.txt",ios::app);
    addid>>i;
    return i;
    addid.close();
}

void save_csid(int id){
    fstream saveid("customerid.txt");
    saveid<<id;
}

void savecustomer(vector<Customer> customer){
    fstream savecustomer("customer.csv",ios::out);
    if (!savecustomer.is_open()) {
        cerr << "Unable to save coustomer" << endl;
        return;
    }
    for (const Customer& customeri : customer) {
        savecustomer<<customeri.customer_id<<","<<customeri.name<<","<<customeri.phone<<","<<customeri.totall_price<<endl;
    }

    savecustomer.close();
}

void customer_massage(int &id){
    cout<<"if you have customer id enter '1' else enter '2': ";
    int i;
    cin>>i;
    if (i==1)
        opencustomer();
    else if (i==2)
        place_order(++id);
    else
        cout<<"wrong number.";
}

void save_order(Order order){
    ofstream save("order.csv", ios::app);
    save<<order.order_id<<","<<order.product.name<<","<<order.product.count<<","<<order.product.price<<","<<order.product.id_product<<endl;
    save.close();
}

void opencustomer() {
    vector<Customer> customers;
    fstream customeropen("customer.csv");
    string line;
    while (getline(customeropen, line)) {
        stringstream ss(line);
        string name, ph, totall, crid;
        getline(ss, crid, ',');
        getline(ss, name, ',');
        getline(ss, ph, ',');
        getline(ss, totall);

        int id = stoi(crid);
        int phone = stoi(ph);
        int totallprice = stoi(totall);

        Customer customer{name, phone, totallprice, id};
        customers.push_back(customer);
    }
    place_orderbyid(customers);
}

void place_orderbyid(vector<Customer>& customers) {
    int customerid;
    cout<<"enter your id: ";
    cin>>customerid;
    int i;
    bool loop= true;
    for(;i<sizeof(customers);i++){
        if (customers[i].customer_id==customerid) {
            loop= false;
            break;
        }
    }
    if (loop){
        cout<<"This ID is not registered.\n";
        return;
    }
    ifstream file("product.csv");
    vector<Product> products;

    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return;
    } else {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, priceStr, countStr, id;

            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, countStr, ',');
            getline(ss, priceStr);

            int price = stoi(priceStr);
            int count = stoi(countStr);
            int idpr = stoi(id);

            Product product{name, count, price, idpr};
            cout << "product id: " << product.id_product << endl;
            cout << "product name: " << product.name << endl;
            cout << "product count: " << product.count << endl;
            cout << "product price: " << product.price << endl;
            cout<<"--------------------------------------------\n";

            products.push_back(product);
        }
        file.close();
        string product_name;
        Order order;
        Product product;
        int count,price,discount;
        cout<<"enter product name: ";
        cin>>product_name;

        for(Product& producti : products){
            if(producti.name==product_name){
                cout<<"product name: "<<producti.name<<endl;
                cout<<"product count: "<<producti.count<<endl;
                cout<<"product price: "<<producti.price<<endl;
                cout<<"---------------------------------------\n";

                lable:
                cout<<"enter count to buy: ";
                cin>>count;
                if (count>producti.count) {
                    cout << "This number is more than assets.\n";
                    goto lable;
                }
                else{
                    cout<<"discount: ";
                    cin>>discount;
                    producti.count-=count;
                    order.product.name=producti.name;
                    order.product.count=count;
                    order.product.price=producti.price;
                    int h=(count*producti.price)-discount;
                    cout<<"totall price: "<<h<<endl;
                    customers[i].totall_price+=h;
                    order.product.price=h;
                    order.product.id_product=producti.id_product;
                    order.order_id=customerid;
                }
                break;
            }
        }
        savecustomer(customers);
        savevectorpr(products);
        save_order(order);
    }
}

void place_order(int id){
    Customer customer;
    cout<<"enter your name: ";
    cin>>customer.name;
    cout<<"enter your phone: ";
    cin>>customer.phone;
    customer.customer_id=id;
    cout<<"your id: "<<id<<endl;
    fstream savecustomer("customer.csv",ios::app);
    if (!savecustomer.is_open()) {
        cerr << "Unable to open file" << endl;
        return;
    }
    savecustomer<<customer.customer_id<<","<<customer.name<<","<<customer.phone<<","<<customer.totall_price<<endl;
    savecustomer.close();
    cout<<"press 0 to menu: ";
    string i;
    cin>>i;
}

#endif //PRJ_CUSTOMER_H
