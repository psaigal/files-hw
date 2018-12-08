#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class User
{
    public:
        string name;
        string address;
        string phone;
};

// struct Person {
//     string name;
//     struct Person *next;
// }

void deleteContact(User address_book[], int &count)
{
    cout << "Which contact would you like to delete? Please enter the name" << endl;
    string name_delete;
    getline(cin, name_delete); //input name you want to update
    bool matchFound = false;
    //loop through array to find a matching name
    for (int i = 0; i < count; i++)
    {   
        //enter this statement if name match found
        if (address_book[i].name == name_delete)
        {
            matchFound = true;
            //adjust array elements to overwrite the element that the user wants to remove
            //The logic is as follows:
            //Assume an array with 10 elements. If the user's target element to delete was 4,
            //we'd keep elements 0-3 the same, but move the remaining elements one level down
            //(i.e elements 5 to 10 become elements 4 to 9
            for (int j = i; j < count; j++)
            {
                 address_book[j] = address_book[j+1];
            
            }
            //lower the count for many reasons, but one is so a blank entry is not displayed when invoking listAllContacts again
            count--; 
        }
    }

    if (matchFound == false)
    {
        cout << "No matching entry to delete" << endl;
    }
    
}

void updateContact(User address_book[], int &count)
{
    cout << "Which contact would you like to update? Please enter the name" << endl;
    string name_current;
    getline(cin, name_current); //input name you want to update
    bool matchFound = false;
    for (int i = 0; i < count; i++)
    {
        
        if (name_current == address_book[i].name)
        {
            cout << "The user you want to update is " << address_book[i].name << "." << endl;
            cout << "What is the updated name of " << address_book[i].name << "?" << endl;
            string name_temp;
            getline(cin, name_temp);
            
            cout << "What is the updated number?" << endl;
            string phone_temp;
            getline(cin, phone_temp);
            cout << "What is the updated address?" << endl;
            string address_temp;
            getline(cin, address_temp);
            //update entries
            address_book[i].name = name_temp;
            address_book[i].phone = phone_temp;
            address_book[i].address = address_temp;
            matchFound = true;
        }
    }
    if (matchFound == false)
    {
        cout << "There was no match for that entry" << endl;
    }
}

 void swap(User address_book[], int minValue, int i, int &count)
{
    User swap1= address_book[i];
    address_book[i] = address_book[minValue];
    address_book[minValue] = swap1;
}

void sortUsers(User address_book[], int &count)
{
    for (int i = 0; i < count; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < count; j++)
        {
            if(address_book[j].name[0] < address_book[i].name[0])
            {
                minIndex = j;
            }
        }

        swap(address_book, minIndex, i, count);
    }

}

void listAllContacts(User address_book[], int &count)
{
    string contactInfo;
    ifstream addressFile ("address_book.txt");
    if (addressFile.is_open())
    {
        while ( getline (addressFile,contactInfo) )
        {
            cout << contactInfo << '\n';
        }
        addressFile.close();
    }
    else cout << "Unable to open file"; 

}

void searchContact(User address_book[], int &count)
{
    bool matchFound = false;

    cout << "What is the full name of the user you are searching for?" << endl;

    string findName; 
    getline(cin, findName);


    string line;
    ifstream myfile ("address_book.txt");

    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            if (findName == line)
            {
                matchFound = true;
                cout << "MATCH IS FOUND" << endl;
                for (int i = 0; i < count; i++)
                {
                    if (address_book[i].name == findName)
                    {
                        cout << "Here is the user's information" << endl;
                        cout << address_book[i].name << endl;
                        cout << address_book[i].phone << endl;
                        cout << address_book[i].address << endl;
                    }
                }
            }
        }
        myfile.close();
        if (!matchFound)
        {
            cout << "There was no match for that entry" << endl;
        }
    }
    else cout << "Unable to open file"; 
}

void addEntry(User address_book[], int &count)
{
    string name, phone, address;
    cout << "Add the name of the user:" << endl;
    getline(cin, name);
    cout << "Add the phone of the user:" << endl;
    getline(cin, phone);
    cout << "Add the address of the user:" << endl;
    getline(cin, address);
    // create instance of class user
    User newUser;
    //add in attributes to instance
    newUser.name = name;
    newUser.phone = phone;
    newUser.address = address;

    address_book[count] = newUser;

    count++;
    cout << "User successfully added to address book" << endl << endl;

    ofstream dataFile; 

    if (count == 0)
    {
        cout << "Opening file...\n"; 
        dataFile.open("address_book.txt", ios::out); 
        cout << "Now writing data to the file.\n"; 
        dataFile << "Name: " << newUser.name << endl; // Write line 1
        dataFile << "Phone: " << newUser.phone << endl; // Write line 2
        dataFile << "Address: " << newUser.address << endl; // Write line 3

        cout << "Now closing the file.\n";
        dataFile.close(); // Close the file 
    }

    else if (count > 0)
    {
        cout << "Opening the file again...\n";
        // Open the file in append mode.
        dataFile.open("address_book.txt", ios::out | ios::app);
        cout << "Writing more data to the file.\n";
        dataFile << "Name: " << newUser.name << endl; // Write line 1
        dataFile << "Phone: " << newUser.phone << endl; // Write line 2
        dataFile << "Address: " << newUser.address << endl; // Write line 3
        cout << "Now closing the file.\n";
        dataFile.close(); // Close the file 
    }
}

void displayMenu()
{
    cout << "Menu" << endl;
    cout << "1) Add new contact" << endl;
    cout << "2) Update existing contact" << endl;
    cout << "3) Delete contact" << endl;
    cout << "4) List all contacts" << endl;
    cout << "5) Search for a contact" << endl;
    cout << "6) Quit" << endl;
}

int main(){
    bool keepPlaying = true;
    User address_book[100];
    int count = 0;

    while (keepPlaying) {
        displayMenu();
        
        int SIZE = 40;
        char menu_choice[SIZE];
        cout << "Please choose an option";
        
        cin.getline( menu_choice, SIZE);

        while((menu_choice[0] < 49 || menu_choice[0] > 54) || menu_choice[1] != '\0')
        {
            cout << "Invalid choice, please enter valid choice" << endl;
            cin.getline(menu_choice, SIZE);
        }
        
        //address book array
        if (menu_choice[0] == '1')
        {
            addEntry(address_book, count);
        } 
        else if (menu_choice[0] == '2')
        {
            updateContact(address_book, count);
        }
        else if (menu_choice[0] =='3')
        {
            deleteContact(address_book, count);
        }
        else if (menu_choice[0] == '4')
        {
            listAllContacts(address_book, count);
        }
         else if (menu_choice[0] == '5')
        {
            searchContact(address_book, count);
        }
        else if (menu_choice[0] == '6')
        {
            keepPlaying = false;
        }
    }
    
}


