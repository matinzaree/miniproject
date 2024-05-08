//
// Created by matin on ۰۸/۰۵/۲۰۲۴.
//

#ifndef PRJ_MONEY_H
#define PRJ_MONEY_H
class Money{
public:
    int totallorice;
    int discount;
};

void totallmoney(){
    Money money;
    vector<Order> orders;
    Order order;
    ifstream orderopen("order.csv");
    if (!orderopen.is_open()){
        cerr<<"unable to open\n";
        return;
    }else {
        string line1;
        while (getline(orderopen, line1)) {
            stringstream ss(line1);
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
        for(const Order&orderi : orders){
                money.totallorice += orderi.product.price;
                money.discount += orderi.discount;
        }
        cout<<"all income:"<<money.totallorice<<endl;
        cout<<"all discount:"<<money.discount<<endl;
    }

}


#endif //PRJ_MONEY_H
