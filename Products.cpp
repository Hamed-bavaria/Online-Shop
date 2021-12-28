#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include "Products.h"
void Products::setProduct()
{
	cout << "Enter the product name: "; cin >> productName;
	cout << "Enter the product type: "; cin >> productType;
	cout << "Enter the product specifications: "; cin >> productSpecification;
	cout << "Enter the product maker name: "; cin >> productMaker;
}
void Products::setID() {
	int counter = 0;
	fstream table;
	table.open("Products.txt", ios::in);
	while (!table.eof()) {
		getline(table, line);
		if (line == "") {
			productID = counter;
			break;
		}
		unpack();
		if (productID == counter) {
			counter++;
			continue;
		}
	}
	table.close();
}
void Products::pack() {
	line = productName + "|"
		+ productType + "|"
		+ productSpecification + '|'
		+ productMaker + '|'
		+ to_string(productID) + '|'
		+ "\n";
}
void Products::unpack()
{
	string values[5];
	string temp = "";
	int counter = 0;
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == '|')
		{
			values[counter] = temp;
			temp = "";
			counter++;
		}
		else if (i == line.length() - 1)
		{
			values[counter] = temp;
		}
		else
		{
			temp += line[i];
		}
	}
	productName = values[0];
	productType = values[1];
	productSpecification = values[2];
	productMaker = values[3];
	productID = stoi(values[4]);
}
void Products::addProduct()
{
	setID();
	setProduct();
	pack();
	fstream table;
	table.open("Products.txt", ios::app);
	table << line;
	table.close();
}
void Products::display()
{
	cout << "Product Name: " << productName << endl
		<< "Product ID: " << productID << endl
		<< "Product Type: " << productType << endl
		<< "Product Specifications: " << productSpecification << endl
		<< "Product Maker: " << productMaker << endl;
}
bool Products::searchProducts(string n)
{
	string key;
	key = n;
	fstream table;
	table.open("Products.txt", ios::in);
	while (!table.eof())
	{
		getline(table, line);
		if (line == "") {
			cout << "Product Not found, Please try again!" << endl;
			return false;
			break;
		}
		unpack();
		if (productName == key) {
			pack();
			display();
			return true;
		}
	}

	table.close();
}
void Products::displayAll()
{
	fstream table;
	table.open("Products.txt", ios::in);
	cout << "Here are all the available products:" << endl;
	while (!table.eof()) {
		getline(table, line);
		cout << line << endl;
	}
	table.close();
}
void Products::deleteProduct(string n)
{
	string key;
	key = n;
	fstream f1;
	fstream f2;
	f2.open("updatedData.txt", ios::out | ios::app);
	f1.open("Products.txt", ios::in);
	while (!f1.eof())
	{
		getline(f1, line);
		if (line == "") {
			break;
		}
		unpack();
		if (key == productName) {
			cout << "Deleted!" << endl;
			continue;
		}
		pack();
		f2 << line;
	}
	f1.close();
	f2.close();
	remove("Products.txt");
	rename("updatedData.txt", "Products.txt");
}
void Products::updateProduct() {
	string n;
	cout << "Enter the name of the product: ";
	cin >> n;
	if (searchProducts(n)) {
		deleteProduct(n);
		cout << "Please choose an action from the following: " << endl;
		cout << "Option 1: Edit name." << endl;
		cout << "Option 2: Edit ID." << endl;
		cout << "Option 3: Edit type." << endl;
		cout << "Option 4: Edit Specification. " << endl;
		cout << "Option 5: Edit maker." << endl;
		int choice;
		while (true) {
			cout << "Choose: "; cin >> choice;
			if (choice == 1) {
				cout << "Enter the new product name: "; cin >> productName;
				break;
			}
			else if (choice == 2) {
				cout << "Enter the new product ID: "; cin >> productID;
				break;
			}
			else if (choice == 3) {
				cout << "Enter the new product type: "; cin >> productType;
				break;
			}
			else if (choice == 4) {
				cout << "Enter the new product specification: "; cin >> productSpecification;
				break;
			}
			else if (choice == 5) {
				cout << "Enter the new product maker: "; cin >> productMaker;
				break;
			}
			else {
				cout << "Invalid option, Please try again!" << endl;
			}
		}
		pack();
		fstream table;
		table.open("Products.txt", ios::app);
		table << line;
		table.close();
		cout << "Here are the new results:" << endl;
		display();
	}
	else {
		string choice2;
		cout << "Would you like to try again?(y/n): "; cin >> choice2;
		if (choice2 == "y") {
			updateProduct();
		}
		else {
			NULL;
		}
	}
}
void Products::productStart()
{
	string choice;
	cout << "Please choose an action from the following: " << endl;
	cout << "Option 1: Add a Product." << endl;
	cout << "Option 2: Search for a specific product." << endl;
	cout << "Option 3: Delete a product." << endl;
	cout << "Option 4: Edit an existing product." << endl;
	cout << "Option 5: View all available products." << endl;
	while (true) {
		cout << "Choose: "; cin >> choice;
		if (choice == "1") {
			addProduct();
			break;
		}
		else if (choice == "2") {
			string n;
			cout << "Enter the name of the product: ";
			cin >> n;
			searchProducts(n);
			break;
		}
		else if (choice == "3") {
			string n;
			cout << "Enter the name of the product: ";
			cin >> n;
			deleteProduct(n);
			break;
		}
		else if (choice == "4") {
			updateProduct();
			break;
		}
		else if (choice == "5") {
			displayAll();
			break;
		}
		else {
			cout << "Invalid option, Please try again!" << endl;
		}
	}
	string choice2;
	cout << "Would you like to do something else?(y/n): "; cin >> choice2;
	if (choice2 == "y") {
		productStart();
	}
	else {
		NULL;
	}
}
