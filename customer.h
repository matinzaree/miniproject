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
    int totall_price=0;
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
void showcustomer(vector<Customer>& customers);

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
    ofstream savecustomer("customer.csv",ios::out);
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
    save<<order.order_id<<","<<order.product.name<<","<<order.product.count<<","<<order.product.price<<","<<order.discount<<","<<order.date<<","<<order.product.id_product<<endl;
    save.close();
}

void opencustomer() {
    vector<Customer> customers;
    ifstream customeropen("customer.csv");
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
        string product_name,date;
        Order order;
        Product product;
        int count,price,discount;
        cout<<"enter product name: ";
        cin>>product_name;
        cout<<"enter date(2024-05-08): ";
        cin>>date;

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
                    order.discount=discount;
                    order.date=date;
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
    ofstream savecustomer("customer.csv",ios::app);
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

void opencustomer_showcustomer() {
    vector<Customer> customers;
    ifstream customeropen("customer.csv");
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
    showcustomer(customers);
}

void showcustomer(vector<Customer>& customers){
    cout<<setw(10)<<"customer id"<<setw(10)<<"name"<<setw(10)<<"phone"<<setw(10)<<"totall price"<<endl;
    for(const Customer& customeri : customers){
        cout<<setw(10)<<customeri.customer_id<<setw(10)<<customeri.name<<setw(10)<<customeri.phone<<setw(10)<<customeri.totall_price<<endl;
    }
}

void showorder_dtails(vector<Customer>& customers,vector<Order>& orders){

    for(const Customer&customeri : customers){
        int i=0;
        cout<<setw(10)<<"customer id"<<setw(10)<<"name"<<setw(10)<<"phone"<<setw(10)<<"totall price"<<endl;
        cout<<setw(10)<<customeri.customer_id<<setw(10)<<customeri.name<<setw(10)<<customeri.phone<<endl;
        cout<<"\n"<<"product number"<<"name"<<setw(10)<<"count"<<setw(10)<<"price"<<setw(10)<<"discount"<<setw(10)<<"product id"<<setw(10)<<"date"<<endl;
        for(const Order&orderi : orders){
            if(customeri.customer_id==orderi.order_id){
                ++i;
                cout<<"product "<<i<<":"<<setw(10)<<orderi.product.name<<setw(10)<<orderi.product.count<<setw(10)<<orderi.product.price<<setw(10)<<orderi.discount<<setw(10)<<orderi.product.id_product<<setw(10)<<orderi.date<<endl;
                cout<<setw(60)<<setfill('-')<<endl;
            }
        }
    }

}

void opencustomer_detailsorder() {
    vector<Customer> customers;
    ifstream customeropen("customer.csv");
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
    vector<Order> orders;
    Order order;
    ifstream orderopen("order.csv");
    if (!orderopen.is_open()){
        cerr<<"unable to open\n";
        return;
    }else {
        string line1;
        while (getline(orderopen, line1)) {
            stringstream ss(line);
            string prname, prdcount, prdprice, prdid, ordate, orddiscount, ordid;
            getline(ss, ordid, ',');
            getline(ss, prname, ',');
            getline(ss, prdcount, ',');
            getline(ss, prdprice, ',');
            getline(ss, orddiscount, ',');
            getline(ss, ordate, ',');
            getline(ss, prdid);


            order.product.name = prname;
            order.date = ordate;
            order.order_id = stoi(ordid);
            order.product.count = stoi(prdcount);
            order.product.price = stoi(prdprice);
            order.product.id_product = stoi(prdid);
            order.discount = stoi(orddiscount);


            orders.push_back(order);
        }
    }
    showorder_dtails(customers,orders);
}

#endif //PRJ_CUSTOMER_H
