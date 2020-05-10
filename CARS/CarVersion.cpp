#include "CarVersion.h"
#include <sstream>

CarVersion::CarVersion(string version, string manufacturer, string model)
{
	this->version = version;
	this->manufacturer = manufacturer;
	this->model = model;
}

CarVersion::CarVersion(string version, string manufacturer, string model, int releaseYear, int price)
{
	this->version = version;
	this->manufacturer = manufacturer;
	this->model = model;
	this->releaseYear = releaseYear;
	this->price = price;
}


string CarVersion::get_version()
{
	return version;
}
void CarVersion::set_version(string version)
{
	this->version = version;
}

string CarVersion::get_manufacturer()
{
	return manufacturer;
}
void CarVersion::set_manufacturer(string manufacturer)
{
	this->manufacturer = manufacturer;
}


string CarVersion::get_model()
{
	return model;
}
void CarVersion::set_model(string model)
{
	this->model = model;
}

int CarVersion::get_releaseYear()
{
	return releaseYear;
}
void CarVersion::set_releaseYear(int releaseYear)
{
	this->releaseYear = releaseYear;
}


int CarVersion::get_price()
{
	return price;
}
void CarVersion::set_price(int price)
{
	this->price = price;
}



string CarVersion::to_string()
{
	stringstream ss;
	ss
		<< "Version: " << version << '\n'
		<< "Manufacturer: " << manufacturer << '\n'
		<< "Model: " << model << '\n'
		<< "Release year: " << releaseYear << '\n';
		if (price == 0)
		{
		ss << "Price: Unknown price." << endl;
		}
		else
		{
		ss << "Price: "<< price << ".000 $" << endl;
		}
	return ss.str();
}
