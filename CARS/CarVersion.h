#pragma once
#include <string>;
#include <vector>;
using namespace std;

class CarVersion
{
private:
	string version;
	string manufacturer;
	string model;
	int releaseYear;
	int price;

public:
	CarVersion(string version, string manufacturer, string model, int releaseYear, int price);
	CarVersion(string version, string manufacturer, string model);
	string get_version();
	void set_version(string version);
	string get_manufacturer();
	void set_manufacturer(string manufacturer);
	string get_model();
	void set_model(string model);
	int get_releaseYear();
	void set_releaseYear(int releaseYear);
	int get_price();
	void set_price(int price);
	string to_string();
};

   