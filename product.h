#ifndef PRJ_PRODUCT_H
#define PRJ_PRODUCT_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

class Product
{
public:
    string name;
    int count;
    int price;
    int id_product;
};

void savevectorpr(vector<Product> products);

int add_id(){
    ifstream addid("productid.txt",ios::app);
    int i=0;
    addid>>i;
    addid.close();
    return i;
}

void save_prid(int id){
    fstream saveid("productid.txt");
    saveid<<id;
}

void searchproduct()
{
    string name_search;
    cout << "enter your name for search:";
    cin >> name_search;
    fstream file("product.csv");
    if (!file.is_open()){
            cerr << "Unable to open file" << endl;
    }
    else{
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
            // product.price = price;
            if (name_search == product.name) {
                cout << "Product id: " << product.id_product << endl;
                cout << "name: " << product.name << endl;
                cout << "Quantity: " << product.count << endl;
                cout << "Price: " << product.price << endl;
                cout << endl;
                break;
            }
        }
    }
}

void saveproduct(Product products)
{
    fstream save_product;
    save_product.open("product.csv", ios::app);
    save_product <<products.id_product<<","<< products.name << "," << products.count << "," << products.price << endl;
    save_product.close();
}

void addproduct(int &id)
{
    cout << "add your product:\n";
    Product product;
    cout << "product name:";
    string name;
    cin >> name;
    product.name = name;
    cout << "product count:";
    cin >> product.count;
    cout << "product price:";
    cin >> product.price;
    product.id_product=++id;
    cout<< "product id: "<< product.id_product<<endl;
    saveproduct(product);
}

void editproduct(){
    string name_search;
    cout << "enter your name for edit:";
    cin >> name_search;
    vector<Product> products;
    fstream file("product.csv");
    if (!file.is_open()){
        cerr << "Unable to open file" << endl;
        return;
    } else{
        string line;
        while (getline(file, line)){
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
            products.push_back(product);
        }
        file.close();
        bool loop=true;
        for (int i = 0; i < sizeof(products); i++){
            if(name_search==products[i].name){
                cout<<"product id: "<<products[i].id_product<<endl;
                cout<<"product name: "<<products[i].name<<endl;
                cout<<"product count: "<<products[i].count<<endl;
                cout<<"product price: "<<products[i].price<<endl;
                cout<< "------------------------\n";
                cout<<"enter new count: ";
                cin>>products[i].count;
                cout<<"enter new price: ";
                cin>>products[i].price;
                loop=false;
                break;

            }
        }
        if (loop){
            cout<<"we dont find your product";
        }
        else{

            savevectorpr(products);
            }

        }
    }

void savevectorpr(vector<Product> products){
    fstream save("product.csv", ios::out);
    for(const Product& producti : products){
        save<<producti.id_product<<","<<producti.name<<","<<producti.count<<","<<producti.price<<endl;
    }
    save.close();
}

#endif //PRJ_PRODUCT_H
