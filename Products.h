#include <iostream>
using namespace std;
#include <fstream>
class Products
{
public:
    string line;
    int productID;
    string productName;
    string productType;
    string productSpecification;
    string productMaker;
    string tempLine;
    void setProduct();
    void setID();
    void addProduct();
    void pack();
    void unpack();
    void display();
    bool searchProducts(string n);
    void displayAll();
    void deleteProduct(string n);
    void updateProduct();
    void productStart();
};

