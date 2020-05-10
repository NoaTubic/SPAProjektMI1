#include <iostream>
#include "CarVersion.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <list>
#include <algorithm>
#include <stack>
using namespace chrono;
using namespace std;

void printBigTitle() //11
{
    cout << R"(
 ___________________________________________________________________________________
|________/\\\\\\\\\_____/\\\\\\\\\_______/\\\\\\\\\_________/\\\\\\\\\\\____________|
|______/\\\////////____/\\\\\\\\\\\\\___/\\\///////\\\_____/\\\/////////\\\_________|
|____/\\\/____________/\\\/////////\\\_\/\\\_____\/\\\____\//\\\______\///__________|
|_____/\\\_____________\/\\\_______\/\\\_\/\\\\\\\\\\\/______\////\\\_______________|
|_____\/\\\_____________\/\\\\\\\\\\\\\\\_\/\\\//////\\\_________\////\\\___________|
|______\//\\\____________\/\\\/////////\\\_\/\\\____\//\\\___________\////\\\_______|
|________\///\\\__________\/\\\_______\/\\\_\/\\\_____\//\\\___/\\\______\//\\\_____|
|___________\////\\\\\\\\\_\/\\\_______\/\\\_\/\\\______\//\\\_\///\\\\\\\\\\\/_____|
|_______________\/////////__\///________\///__\///________\///____\///////////______|
|___________________________________________________________________________________|
)" << '\n';
}


void printMainMenu() 
{   
    cout << '\n' << "-----------------" << '\n' << "|   Main menu   |" << '\n' << "-----------------" << '\n' << endl;
    cout << "                                            ---------------------------------------------------------" << endl;
    cout << "Choose one option (type 1, 2, 3, 4, 5): " 
        << "    | NOTE* Import data first to use other functionalities! |" << endl;
    cout << "                                            ---------------------------------------------------------" << endl;
    cout << " 1.) Data import from files " << endl;
    cout << " 2.) Copy file " << endl;
    cout << " 3.) Process by manufacturer " << endl;
    cout << " 4.) Show version statistics " << endl;
    cout << " 5.) Search models by engine displacement with SELECT " << endl;
}


int convert(string& s)
{
    stringstream converter(s);
    int n;
    converter >> n;
    return n;
}


//13
void dataImport(ifstream &in, ifstream& in2, ifstream& in3, vector<CarVersion> &cars) 
{
    auto begin = high_resolution_clock::now();

    //input VERSIONS table
    string line;
    string versionName, manID, modID, IDv;
    int year, price;
    string temp;
    getline(in, line); //skip first line
    while (getline(in, line))
    {
        stringstream ss(line);
        getline(ss, IDv, ',');
        getline(ss, manID, ',');
        getline(ss, modID, ',');
        getline(ss, versionName, ',');
        getline(ss, temp, ',');
        year = convert(temp);
        getline(ss, temp);
        price = convert(temp);

        cars.emplace_back(versionName, manID, modID, year, price);
    }

    //join MODELS table
    string IDMod, ModelName;
    getline(in2, line); //skip first line
    while (getline(in2, line))
    {
        stringstream ss(line);
        getline(ss, IDMod, ',');
        getline(ss, manID, ',');
        getline(ss, ModelName);

        for (auto it = cars.begin(); it != cars.end(); ++it)
        {

            if (IDMod.compare(it->get_model()) == 0)
            {
                it->set_model(ModelName);
            }
        }
    }
    ////join MANUFACTURERS table
    string IDMan, ManufacturerName, noneed;
    getline(in3, line); //skip first line
    while (getline(in3, line))
    {
        stringstream ss(line);
        getline(ss, IDMan, ',');
        getline(ss, ManufacturerName, ',');
        getline(ss, noneed);


        for (auto it = cars.begin(); it != cars.end(); ++it)
        {
            if (IDMan.compare(it->get_manufacturer()) == 0)
            {
                it->set_manufacturer(ManufacturerName);
            }
        }
    }

    auto end = high_resolution_clock::now();
    cout    << "Data import successful!" << '\n'
            << "Duration of data import: "
            << duration_cast<chrono::seconds>(end - begin).count()
            << " s" << '\n'<< endl;

}


//15
void sortManufacturers(vector<CarVersion>& cars, vector< pair<string, int> > &manPairM)
{
    int counter = 1;
    for (unsigned int i = 1; i < cars.size(); i++)
    {
        if (cars.at(i).get_manufacturer().compare(cars.at(i - 1).get_manufacturer()) == 0)
        {
            counter++;
        }
        else
        {
            manPairM.emplace_back(make_pair(cars.at(i - 1).get_manufacturer(), counter));
            counter = 0;
        }

    }

    sort(manPairM.begin(), manPairM.end(), [](auto& left, auto& right) {
        return left.second > right.second;
        });

    cout << "Manufactures by nr. of model versions desc: " << endl;
    cout << "--------------------------------------------" << endl;
    for (int i = 0; i < manPairM.size(); i++)
    {
        cout << i << ".) " << manPairM.at(i).first << "   " << manPairM.at(i).second << endl;

    }
}


//16
bool sortDesc(int i, int j) { return i > j; }

void sortByEngineDisplacement(vector<CarVersion>& cars, vector<double>& displacemnts)
{
    string versionFull;
    string doubleConvert;
    double engineDis = 0.0;
    for (unsigned int j = 0; j < 11041; j++)
    {
        versionFull = cars.at(j).get_version();

        for (unsigned int i = 2; i < versionFull.length(); i++)
        {
            if (isdigit(versionFull.at(i - 2)) && versionFull.at(i - 1) == '.'
                && isdigit(versionFull.at(i)))
            {
                doubleConvert = versionFull.substr(i - 2, 3);
                stringstream dstream(doubleConvert);
                dstream >> engineDis;
                displacemnts.push_back(engineDis);

                break;
            }
        }
    }

    sort(displacemnts.begin(), displacemnts.end(), sortDesc);
    for (unsigned int i = 0; i < 5; i++)
    {
        cout << (i + 1) << ".) " << displacemnts.at(i) << endl;
    }
}



//21 load selected file
void load(ifstream& in, stack<string>& s, int file)
{
    if (file == 1 || file == 2)
    {
        //cvs2 and cvs1
        string line;
        string IDMod, manID, ModelName;
        getline(in, line); //skip first line
        while (getline(in, line))
        {
            stringstream ss(line);
            getline(ss, IDMod, ',');
            getline(ss, manID, ',');
            getline(ss, ModelName);
            string stringCopy = IDMod + "  " + manID + "  " + ModelName;
            s.push(stringCopy);
        }
    }
    else
    {
        //cvs3
        string line;
        string versionName, manID, modID, IDv, year, price;
        getline(in, line); //skip first line
        while (getline(in, line))
        {
            stringstream ss(line);
            getline(ss, IDv, ',');
            getline(ss, manID, ',');
            getline(ss, modID, ',');
            getline(ss, versionName, ',');
            getline(ss, year, ',');
            getline(ss, price);
            string stringCopy = IDv + "  " + manID + "  " + modID + "  " + 
                versionName + "  " + year + "  " + price;
            s.push(stringCopy);
        }
    }



}


//21
void saveRev(ofstream& out, stack<string>& s)
{
    while (!s.empty())
    {
        out << s.top() << endl;
        s.pop();

    }
}


//21
void save(ofstream& out, stack<string>& s)
{
    stack<string> temp;
    while (!s.empty())
    {
        temp.push(s.top());
        s.pop();
    }
    while (!temp.empty())
    {
        string t = temp.top();
        out << t << endl;
        temp.pop();
    }
}


//22
void print(CarVersion& cv)
{
    cout << cv.to_string() << endl;
}


//22
void processByManufacturer(vector<CarVersion> &cars, list<CarVersion> &carsList, string manName)
{
    
    for (unsigned i = 0; i < cars.size(); i++) // copy to list 
    {
        if (manName.compare(cars.at(i).get_manufacturer()) == 0)
        {
            carsList.push_back(cars.at(i));
        }
    }

    for (auto it = carsList.begin(); it != carsList.end(); ) //delete where price = 0
    {
        if (it->get_price() < 1)
        {
            it = carsList.erase(it);
        }

        else
        {
            ++it;
        }
    }

    carsList.reverse();
    for_each(carsList.begin(), carsList.end(), print);
}


//24 draw statistics
void drawHash(int counter)
{
    int n;
    if (counter < 10)
    {
        cout << "#";
    }
    else
    {
        n = counter / 10;
        if (counter % 10 > 0)
        {
            n++;
        }
        for (int i = 0; i < n; i++)
        {
            cout << "#";
        }
    }
}


//25
string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end() -4, ' '), str.end() -4);
    return str;
}


//25
void select(vector<CarVersion>& cars)
{
    string command_line;
    string command;
    double argument;

    cout << "------------------------------------------------------------------------------" << endl;
    cout << "Enter command (This format only - SELECT * FROM Cars WHERE Displacement = 'n'): " << endl;
    cout << "------------------------------------------------------------------------------" << endl;

    getline(cin, command_line);
    command_line = removeSpaces(command_line);
    stringstream ss(command_line);
    ss >> command;
    ss >> argument;
    if (command == "SELECT*FROMCarsWHEREDisplacement=")
    {
        string versionFull;
        string doubleConvert;
        double engineDis = 0.0;
        for (unsigned int j = 0; j < 11041; j++)
        {
            versionFull = cars.at(j).get_version();

            for (unsigned int i = 2; i < versionFull.length(); i++)
            {
                if (isdigit(versionFull.at(i - 2)) && versionFull.at(i - 1) == '.'
                    && isdigit(versionFull.at(i)))
                {
                    doubleConvert = versionFull.substr(i - 2, 3);
                    stringstream dstream(doubleConvert);
                    dstream >> engineDis;
                    if (argument == engineDis)
                    {
                        cout << versionFull << endl;
                    }
                     
                    break;
                }
            }
        }


    }
    else
    {
        cout << "Command not supported!" << endl;
    }

}




int main() {

	//11
    printBigTitle();

    //12 test
   /* CarVersion cv1("test", "test", "test");
    cout << cv1.to_string() << endl;*/

    int optionSelection;
    vector<CarVersion> cars;
    auto begin = 0;
    auto end = 0;
    do
    {
        printMainMenu();
        cin >> optionSelection;
    if (optionSelection == 1) //IMPORT DATA FROM FILES
    {
        //13 //14
        ifstream in("SPA_PROJ_008_CARS_data_3.csv"), in2("SPA_PROJ_008_CARS_data_2.csv"), in3("SPA_PROJ_008_CARS_data_1.csv");
        if (!in || !in2 || !in3)
        {
            cout << "Can't access file!" << endl;
            return 1;
        }
        dataImport(in, in2, in3, cars);
        in.close();
        in2.close();
        in3.close();

        //15
        vector< pair<string, int> > manPairM;
        sortManufacturers(cars, manPairM);

        //16
        vector<double> displacemnts;
        cout << "----------------------------" << endl;
        cout << '\n' << "Top 5. engine displacements: " << endl;
        cout << "----------------------------" << endl;

        sortByEngineDisplacement(cars, displacemnts);

    }
    else if (optionSelection == 2) // COPY FILE
    {
        system("cls");
        //21
        string fileName;
        int fileCopy;
        int copyOrder;
        cout << "What file do you want to copy? (1,2,3) ";
        cin >> fileCopy;
        switch (fileCopy)
        {
        case 1:
            fileName = "SPA_PROJ_008_CARS_data_1.csv";
            break;
        case 2:
            fileName = "SPA_PROJ_008_CARS_data_2.csv";
            break;
        case 3:
            fileName = "SPA_PROJ_008_CARS_data_3.csv";
            break;
        default:
            break;
        }
        cout << "In what order?(0 - Normal, 1 - Reversed) ";
        cin >> copyOrder;
        ifstream in4(fileName);
        ofstream out("Copy.txt");
        if (!in4 || !out)
        {
            cout << "Can't access file!" << endl;
            return 1;
        }

        stack<string> s;

        load(in4, s, fileCopy);
        in4.close();

        if (copyOrder == 1)
        {
            saveRev(out, s);
            out.close();
        }
        else
        {
            save(out, s);
            out.close();
        }
        cout << endl;
        cout << "File copied correctly!" << '\n' << endl;

    }
    else if (optionSelection == 3) //PROCCES BY MANUFACTURER
    {
        system("cls");
        //22
        list<CarVersion> carsList;
        cout << "Choose manufacturer: ";
        string manName;
        cin.ignore();
        getline(cin, manName);
        cout << "----------------------------------" << endl;
        cout << "Processing by chosen manufacturer; " << endl;
        cout << "----------------------------------" << endl;

        processByManufacturer(cars, carsList,manName);

        //23
        cout << "------------------------" << endl;
        cout << '\n' << "Functionality 23: " << endl;
        cout << "------------------------" << endl;

        stack<CarVersion> rev;
        for (auto it = cars.rbegin(); it != cars.rend(); ++it)
        {
            if (rev.empty())
            {
                rev.push(*it);
            }
                
            if (it->get_model().compare(rev.top().get_model()) == 0)
            {
                rev.push(*it);
            }
            if (it->get_model().compare(rev.top().get_model()) != 0)
            {
                while (!rev.empty())
                    rev.pop();
                rev.push(*it);
            }
        }

        while (!rev.empty())
        {
            cout << rev.top().to_string() << endl;
            rev.pop();
        }

    }
    else if (optionSelection == 4)
    {
        system("cls");
        cout << "---------------------------------------" << endl;
        cout << "Model statistics by number of versions:" << endl;
        cout << "---------------------------------------" << endl;
        //24 version statistics
        int counter = 1;
        string comparer = cars.at(1).get_model();
        for (unsigned int i = 1; i < cars.size(); i++)
        {
            if (comparer.compare(cars.at(i).get_model()) == 0)
            {
                counter++;
            }
            else
            {
                cout << comparer << "  ";
                drawHash(counter);
                cout << " (" << counter << ")" << endl;
                comparer = cars.at(i).get_model();
                counter = 1;

            }
        }

    }
    else
    {
    system("cls");
    cin.ignore();
    select(cars); //25  Search by SELECT
    }
    } while (true);

    return 0;
}






