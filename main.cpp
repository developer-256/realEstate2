#include <iostream>
using namespace std;

class Owner
{
private:
    string name;
    string contactNumber;
    string ownerID;

public:
    Owner(string n = "", string cont = "", string oID = "")
    {
        name = n;
        contactNumber = cont;
        ownerID = oID;
    }
    string getName() { return name; }
    string getContact() { return contactNumber; }
    string getOwnerID() { return ownerID; }

    void setName(string n) { name = n; }
    void setContact(string cont) { contactNumber = cont; }
    void setOwnerID(string oID) { ownerID = oID; }
};

class Property : public Owner
{
private:
    string propertyId;
    string address;
    string city;
    string type;
    float size;
    float price;
    string status; // available, sold, rented
    string discription;

public:
    Property(string pID = "", string add = "", string c = "", string typ = "", float s = 0, float pric = 0,
             string stat = "", string oName = "", string oCont = "", string oID = "", string disc = "") : Owner(oName, oCont, oID)
    {
        propertyId = pID;
        address = add;
        city = c;
        type = typ;
        size = s;
        price = pric;
        status = stat;
        discription = disc;
    }

    string getPropertyId() { return propertyId; }
    string getAddress() { return address; }
    string getCity() { return city; }
    string getType() { return type; }
    float getSize() { return size; }
    float getPrice() { return price; }
    string getStatus() { return status; }
    string getDiscription() { return discription; }

    void setPropertyId(string pID) { propertyId = pID; }
    void setAddress(string add) { address = add; }
    void setCity(string c) { city = c; }
    void setType(string typ) { type = typ; }
    void setSize(float s) { size = s; }
    void setPrice(float pric) { price = pric; }
    void setStatus(string stat) { status = stat; }
    void setDiscription(string disc) { discription = disc; }

    void displayProperty();
};
void Property::displayProperty()
{
    cout << "Property ID: " << propertyId << endl;
    cout << "Property Address: " << address << endl;
    cout << "Property City: " << city << endl;
    cout << "Property Type: " << type << endl;
    cout << "Property Size: " << size << endl;
    cout << "Property Price: " << price << endl;
    cout << "Property Status: " << status << endl;
    cout << "Owner Name: " << getName() << endl;
    cout << "Owner Contact ID: " << getContact() << endl;
    cout << "Owner ID: " << getOwnerID() << endl;
    cout << "Property description: " << discription << endl
         << endl;
}

class Client
{
private:
    string name;
    string contactNumber;
    string clientID;
    string propertyID;

public:
    Client(string n = "", string cont = "", string cID = "", string pID = "")
    {
        name = n;
        contactNumber = cont;
        clientID = cID;
        propertyID = pID;
    }
    string getName() { return name; }
    string getContact() { return contactNumber; }
    string getClientID() { return clientID; }
    string getPropertyID() { return propertyID; }
    void setName(string n) { name = n; }

    void setContact(string cont) { contactNumber = cont; }
    void setClientID(string oID) { clientID = oID; }
    void setPropertyID(string pID) { propertyID = pID; }

    void displayClient();
};
void Client::displayClient()
{
    cout << "Client Name: " << name << endl;
    cout << "Client Contact: " << contactNumber << endl;
    cout << "Client ID: " << clientID << endl;
    cout << "Client Property ID: " << propertyID << endl;
}

class RealEstateManagement
{
private:
    Property *allProperties;
    Client *allClients;
    int propertyINIsize; // initial size of dynamic array
    int allP_arraySize;  // no. of objects in array
    int clientINIsize;
    int allC_arraySize;

public:
    RealEstateManagement() : propertyINIsize(10), clientINIsize(10)
    {
        allP_arraySize = 0;
        allProperties = new Property[propertyINIsize];

        allC_arraySize = 0;
        allClients = new Client[clientINIsize];
    }
    void addProperty2Sell(string pID, string add, string c, string typ, float s, float pric, string stat, string oName, string oCont, string oID, string disc);
    void showAllProperties();
    void showPropertyAvailible();
    void showPropertyWithCity(string c);
    void showPropertyWithPropertyID(string id);
    void showPropertyWithType(string t);
    void showPropertyWithOwnerID(string Oid);
    void showPropertySold();
    void showPropertyRentOut();

    void sellProperty(string id, string stat);
    void setClient(string n, string contact, string id, string pID);

    void showAllClients();
    void showClientsWithName(string n);
    void showClientsWithClientID(string cid);
    void showClientsWithPropertyID(string pid);
};
void RealEstateManagement::addProperty2Sell(string pID, string add, string c, string typ, float s, float pric, string stat, string oName, string oCont, string oID, string disc)
{
    if (allP_arraySize != propertyINIsize)
    {
        // first add an employee at index row, then increase row by 1 ie row++;
        allProperties[allP_arraySize] = Property(pID, add, c, typ, s, pric, stat, oName, oCont, oID, disc);
        allP_arraySize++;
    }

    // if capacity is full first increase the capacity, then copy previous array to new array with increased size, then empty previous array, then pass ownership of new array to old one, then perform the tasks.
    else
    {
        // increasing capacity
        propertyINIsize *= 2;

        // make a new database with increased capacity
        Property *newAllProperty = new Property[propertyINIsize];

        // copy previous array to new one
        for (int i = 0; i < allP_arraySize; i++)
        {
            newAllProperty[i] = allProperties[i];
        }

        // delete everything from previous array
        delete[] allProperties;

        // transfer the ownership of new array to old array so that we don't have to change in our code to perform functions on new array. We can just make new array transfer ownership to old array and make changes in old array which we do changes in new array.
        allProperties = newAllProperty; // address of newDatabase is now address of Database

        // now do same as we did in if condition
        allProperties[allP_arraySize] = Property(pID, add, c, typ, s, pric, stat, oName, oCont, oID, disc);
        allP_arraySize++;
    }
}
void RealEstateManagement::showAllProperties()
{
    for (int i = 0; i < allP_arraySize; i++)
    {
        allProperties[i].displayProperty();
    }
}
void RealEstateManagement::showPropertyAvailible()
{
    for (int i = 0; i < allP_arraySize; i++)
    {
        if (allProperties[i].getStatus() == "availible")
        {
            allProperties[i].displayProperty();
        }
    }
}
void RealEstateManagement::showPropertyWithCity(string c)
{
    for (int i = 0; i < allP_arraySize; i++)
    {
        if (allProperties[i].getCity() == c)
        {
            allProperties[i].displayProperty();
        }
    }
}
void RealEstateManagement::showPropertyWithPropertyID(string id)
{
    for (int i = 0; i < allP_arraySize; i++)
    {
        if (allProperties[i].getPropertyId() == id)
        {
            allProperties[i].displayProperty();
        }
    }
}
void RealEstateManagement::showPropertyWithType(string t)
{
    for (int i = 0; i < allP_arraySize; i++)
    {
        if (allProperties[i].getType() == t)
        {
            allProperties[i].displayProperty();
        }
    }
}
void RealEstateManagement::showPropertyWithOwnerID(string Oid)
{
    for (int i = 0; i < allP_arraySize; i++)
    {
        if (allProperties[i].getOwnerID() == Oid)
        {
            allProperties[i].displayProperty();
        }
    }
}
void RealEstateManagement::showPropertySold()
{
    for (int i = 0; i < allP_arraySize; i++)
    {
        if (allProperties[i].getStatus() == "sold")
        {
            allProperties[i].displayProperty();
        }
    }
}
void RealEstateManagement::showPropertyRentOut()
{
    for (int i = 0; i < allP_arraySize; i++)
    {
        if (allProperties[i].getStatus() == "rent")
        {
            allProperties[i].displayProperty();
        }
    }
}
void RealEstateManagement::sellProperty(string id, string stat)
{
    // first find the index at which the person with specific id is, when found that index, shift all array next to it one index behind. In this way, you will delete person of that id, then after for loop decrease no. of rows by 1. Then return from function.
    for (int i = 0; i < allP_arraySize; i++)
    {
        if (allProperties[i].getPropertyId() == id)
        {
            allProperties[i].setStatus(stat);
            return;
        }
    }
}
void RealEstateManagement::setClient(string n, string contact, string id, string pID)
{
    if (allC_arraySize != clientINIsize)
    {
        // first add an employee at index row, then increase row by 1 ie row++;
        allClients[allC_arraySize] = Client(n, contact, id, pID);
        allC_arraySize++;
    }

    // if capacity is full first increase the capacity, then copy previous array to new array with increased size, then empty previous array, then pass ownership of new array to old one, then perform the tasks.
    else
    {
        // increasing capacity
        clientINIsize *= 2;

        // make a new database with increased capacity
        Client *newAllClients = new Client[clientINIsize];

        // copy previous array to new one
        for (int i = 0; i < allC_arraySize; i++)
        {
            newAllClients[i] = allClients[i];
        }

        // delete everything from previous array
        delete[] allClients;

        // transfer the ownership of new array to old array so that we don't have to change in our code to perform functions on new array. We can just make new array transfer ownership to old array and make changes in old array which we do changes in new array.
        allClients = newAllClients; // address of newDatabase is now address of Database

        // now do same as we did in if condition
        allClients[allC_arraySize] = Client(n, contact, id, pID);
        allC_arraySize++;
    }
}
void RealEstateManagement::showAllClients()
{
    for (int i = 0; i < allC_arraySize; i++)
    {
        allClients[i].displayClient();
    }
}
void RealEstateManagement::showClientsWithName(string n)
{
    for (int i = 0; i < allC_arraySize; i++)
    {
        if (allClients[i].getName() == n)
        {
            allClients[i].displayClient();
        }
    }
}
void RealEstateManagement::showClientsWithClientID(string cid)
{
    for (int i = 0; i < allC_arraySize; i++)
    {
        if (allClients[i].getClientID() == cid)
        {
            allClients[i].displayClient();
        }
    }
}
void RealEstateManagement::showClientsWithPropertyID(string pid)
{
    for (int i = 0; i < allC_arraySize; i++)
    {
        if (allClients[i].getPropertyID() == pid)
        {
            allClients[i].displayClient();
        }
    }
}

// funtion declerations
void addproperty(RealEstateManagement *ptrSystem1);
void showProperty(RealEstateManagement *ptrSystem1);
void sellProperty(RealEstateManagement *ptrSystem1);
void showClient(RealEstateManagement *ptrSystem1);

int main()
{
    RealEstateManagement System1;

    int choice;
    do
    {
        cin.clear();   // clear error by complier in previous input like when you take string in int
        fflush(stdin); // clear any buffer values

        cout << "________________________________\n";
        cout << "|---------( Main Page )--------|\n";
        cout << "| Choose one of the following: |\n";
        cout << "********************************\n";
        cout << "| 1: Add property to sell      |\n";
        cout << "| 2: Sell property             |\n";
        cout << "| 3: Show property             |\n";
        cout << "| 4: Show Client               |\n";
        cout << "| 5: Exit                      |\n";
        cout << "********************************\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            addproperty(&System1);
            break;
        case 2:
            system("cls");
            sellProperty(&System1);
            break;
        case 3:
            system("cls");
            showProperty(&System1);
            break;
        case 4:
            system("cls");
            showClient(&System1);
            break;
        case 5:
            system("cls");
            cout << "\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
            cout << "%%% (Thanks for using our REMS) %%%\n";
            cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n";
            break;

        default:
            system("cls");
            cout << "Invalid Input\n";
            break;
        }

    } while (choice != 5);

    return 0;
}

void addproperty(RealEstateManagement *ptrSystem1)
{
    string propertyId;
    string address;
    string city;
    string type;
    float size;
    float price;
    string status = "availible";
    string name;
    string contactNumber;
    string ownerID;
    string discription;

    cout << "Enter Property ID: ";
    getline(cin >> ws, propertyId);
    cout << "Enter Address: ";
    getline(cin >> ws, address);
    cout << "Enter city: ";
    getline(cin >> ws, city);
    cout << "Enter Type: ";
    getline(cin >> ws, type);
    cout << "Enter size: ";
    cin >> size;
    cout << "Enter Price: ";
    cin >> price;
    cout << "Enter Owner Name: ";
    getline(cin >> ws, name);
    cout << "Enter Owner Contact Number: ";
    getline(cin >> ws, contactNumber);
    cout << "Enter Owner ID: ";
    getline(cin >> ws, ownerID);
    cout << "Enter Property discription: ";
    getline(cin >> ws, discription);

    ptrSystem1->addProperty2Sell(propertyId, address, city, type, size, price, status, name, contactNumber, ownerID, discription);
}
void sellProperty(RealEstateManagement *ptrSystem1)
{
    string pID;
    string status;
    string name;
    string contactNumber;
    string clientID;

    ptrSystem1->showPropertyAvailible();
    cout << "Enter property id:";
    getline(cin >> ws, pID);
    cout << "Enter Status(rent or sold): ";
    getline(cin >> ws, status);
    cout << "Enter Client Name: ";
    getline(cin >> ws, name);
    cout << "Enter Client Contact Number: ";
    getline(cin >> ws, contactNumber);
    cout << "Enter Client ID: ";
    getline(cin >> ws, clientID);
    ptrSystem1->sellProperty(pID, status);
    ptrSystem1->setClient(name, contactNumber, clientID, pID);
}

void showProperty(RealEstateManagement *ptrSystem1)
{
    int choice;
    do
    {
        cin.clear();
        fflush(stdin);

        cout << "________________________________\n";
        cout << "| Choose one of the following: |\n";
        cout << "********************************\n";
        cout << "| 1: Show all properties       |\n";
        cout << "| 2: Show availible properties |\n";
        cout << "| 3: Show properties with city |\n";
        cout << "| 4: Show properties with ID   |\n";
        cout << "| 5: Show properties with type |\n";
        cout << "| 6: Show property with owner ID |\n";
        cout << "| 7: Show properties sold      |\n";
        cout << "| 8: Show properties rented out|\n";
        cout << "| 9: Exit                      |\n";
        cout << "********************************\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string city;
        string pID;
        string type;
        string owneri;

        switch (choice)
        {
        case 1:
            system("cls"); // to clear console
            ptrSystem1->showAllProperties();
            break;

        case 2:
            system("cls");
            ptrSystem1->showPropertyAvailible();
            break;
        case 3:
            system("cls");
            cout << "Enter city: ";
            getline(cin >> ws, city);
            ptrSystem1->showPropertyWithCity(city);
            break;
        case 4:
            system("cls");
            cout << "Enter Property ID: ";
            getline(cin >> ws, pID);
            ptrSystem1->showPropertyWithPropertyID(pID);
            break;
        case 5:
            system("cls");
            cout << "Enter Type: ";
            getline(cin >> ws, type);
            ptrSystem1->showPropertyWithType(type);
            break;
        case 6:
            system("cls");
            cout << "Enter Owner ID: ";
            getline(cin >> ws, owneri);
            ptrSystem1->showPropertyWithOwnerID(owneri);
            break;
        case 7:
            system("cls");
            ptrSystem1->showPropertySold();
            break;
        case 8:
            system("cls");
            ptrSystem1->showPropertyRentOut();
            break;
        case 9:
            system("cls");
            break;

        default:
            system("cls");
            cout << "Invalid Input\n";
            break;
        }

    } while (choice != 9);
}
void showClient(RealEstateManagement *ptrSystem1)
{
    int choice;
    do
    {
        cin.clear();
        fflush(stdin);

        cout << "________________________________\n";
        cout << "| Choose one of the following: |\n";
        cout << "********************************\n";
        cout << "| 1: Show all Clients          |\n";
        cout << "| 2: Show Clients by Name      |\n";
        cout << "| 3: Show Clients by ID        |\n";
        cout << "| 4: Show Clients by Property ID|\n";
        cout << "| 5: Exit                      |\n";
        cout << "********************************\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string name;
        string pID;
        string id;

        switch (choice)
        {
        case 1:
            system("cls"); // to clear console
            ptrSystem1->showAllClients();
            break;

        case 2:
            system("cls");
            cout << "Enter Name: ";
            getline(cin >> ws, name);
            ptrSystem1->showClientsWithName(name);
            break;
        case 3:
            system("cls");
            cout << "Enter Client ID: ";
            getline(cin >> ws, id);
            ptrSystem1->showClientsWithClientID(id);
            break;
        case 4:
            system("cls");
            cout << "Enter Property ID: ";
            getline(cin >> ws, id);
            ptrSystem1->showClientsWithPropertyID(id);
            break;
        case 5:
            system("cls");
            break;

        default:
            system("cls");
            cout << "Invalid Input\n";
            break;
        }

    } while (choice != 5);
}