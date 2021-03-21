#include <cstdio>
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <thread>
#include <chrono>
#include <map>
#include <vector>
#include <algorithm>

namespace Lab6 {

class Object {
    public:
    std::string name;
    double price;
    float quantity;
    std::string unit ;
    double Sum()
    {
        return price*quantity;
    }
};
class ShoppingList {
    public:
    std::vector <Lab6::Object> items;
    double TotalSum()
    {
        double totalSum=0;
        for(int i=0;i<items.size();i++) {
            totalSum+= items.at(i).Sum();
        }
        return totalSum;
    }
};
enum class ColLab{
    white,
    red,
    yellow,
    grey,
    cyan,
    purple
};
enum class ErrLab{
    noMem,
    noObj,
    wrongPos,
};
enum class Operation{
    bigger,
    lower,
    equal,
    startingWith,
    null
};

bool IsPositionValid(int pos, int max_pos)
{
    if(pos >= max_pos || pos < 0)
    return false;
    else return true;
}
inline int ToGuiPosition(int position)
{
    return ++position;
}
inline int ToGenPosition(int position)
{
    return --position;
}
inline void ChangeColor(ColLab colorName)
{
    const std::map <ColLab, int> Colors {{ColLab::white,7},{ColLab::grey, 8},{ColLab::purple, 9},{ColLab::cyan, 11},{ColLab::red, 12},{ColLab::yellow, 14}};
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), Colors.at(colorName) );
}
void PrintAuthor()
{
    ChangeColor(ColLab::white);
    system("cls");
    std::cout << "Author: Kacper Aleks\n\n" ;
}
void PrintError(ErrLab errorName)
{
    const std::map <ErrLab, std::string> Errors {{ErrLab::wrongPos,"Wrong number!"},{ErrLab::noObj,"There are no objects!"},{ErrLab::noMem,"There is no memory left :("}};
    ChangeColor(ColLab::red);
    std::cout << Errors.at(errorName) << "\n";
    std::this_thread::sleep_for (std::chrono::seconds(1));
    system("cls");
}
Operation ConvertOperation(char c)
{
    switch(c){
        case '=':
        return Operation::equal;
        case '>':
        return Operation::bigger;
        case '<':
        return Operation::lower;
        case '|':
        return Operation::startingWith;
        default:
        break;
    }
    return Operation::null;
}
bool CmpNameAttr(Object object, Operation op, std::string givenValue)
{
    if(op == Operation::equal){
        if(object.name == givenValue) return true;
        else return false;
    }
    else {
        if(object.name[0] == givenValue[0]) return true;
        else return false;
    }
}
template <typename Member> bool CmpGenericAttr(Member value ,Member givenValue,Operation op)
{
    if(op == Operation::equal) {
        if(value == givenValue) return true;
        else return false;
    }
    if(op == Operation::bigger) {
        if(value > givenValue) return true;
        else return false;
    }
    if(op == Operation::lower) {
        if(value < givenValue) return true;
        else return false;
    }
    return false;
}
void ReadObject(Object & item)
{
    fflush(stdin);
    ChangeColor(ColLab::cyan);
    printf("============================\n");
    ChangeColor(ColLab::yellow);
    std::cout << "Enter object's name: ";
    std::cin >> item.name;
    std::cout << "Enter object's price per measurement unit: ";
    std::cin >> item.price;
    std::cout << "Enter object's quantity: ";
    std::cin >> item.quantity;
    std::cout << "Enter measurement unit: ";
    std::cin >> item.unit;
}
void PrintObject(Object item, int number)
{
    ChangeColor(ColLab::cyan);
    printf("Object number [%d]:\n",number);
    ChangeColor(ColLab::purple);
    std::cout << "Name: ";
    ChangeColor(ColLab::yellow);
    std::cout<< item.name<< "\t";
    ChangeColor(ColLab::purple);
    std::cout << "Price: ";
    ChangeColor(ColLab::yellow);
    std::cout << item.price<< "\t";
    ChangeColor(ColLab::purple);
    std::cout << "Quantity: ";
    ChangeColor(ColLab::yellow);
    std::cout << item.quantity<< "\t";
    ChangeColor(ColLab::purple);
    std::cout << "Measurement unit: ";
    ChangeColor(ColLab::yellow);
    std::cout << item.unit<< "\n\n";
}
void PrintTable(ShoppingList list)
{
    int tableSize= list.items.size();
    ChangeColor(ColLab::red);
    if(tableSize == 0) PrintError(ErrLab::noObj);
    else{
        ChangeColor(ColLab::cyan);
        printf("Current shopping list\n\n\n");
        for(int i=0;i<tableSize;i++){
            PrintObject(list.items.at(i), ToGuiPosition(i));
        }
        std::cout << "Total sum is: " << list.TotalSum()<< ";\n\n";
        system("Pause");
    }
}
void PrintSelected(ShoppingList list)
{
    int tableSize= list.items.size();
    if(tableSize == 0 ) {
        PrintError(ErrLab::noObj);
        return;
    }
    printf("Welcome to the condition printing creator!\n\n");
    while(true){
        std::string attribute;
        char c;
        system("cls");
        ChangeColor(ColLab::cyan);
        std::cout << "[Attributes => price; name; quantity]\n[Operations => = ; > ; < ; |]\n\n";
        ChangeColor(ColLab::white);
        std::cout << "Enter the search [Write \"0 0\" to leave] : ";
        fflush(stdin);
        std::cin >> attribute >> c;
        Operation op = ConvertOperation(c);

        if(attribute == "0" || c == '0') return;
        if(attribute == "name"){
            std::string refStr;
            std::cout << "Enter reference value: ";
            std::cin >> refStr;
            system("cls");
            for(int i =0; i<tableSize; i++){
                std::string tmp;
                if(CmpNameAttr(list.items.at(i), op, refStr)) {
                    PrintObject(list.items.at(i), ToGuiPosition(i));
                }
            }
        }
        if(attribute == "price") {
            double refDoub;
            std::cout << "Enter reference value: ";
            std::cin >> refDoub;
            system("cls");
            for(int i =0; i<tableSize; i++){
                if( CmpGenericAttr <double> (list.items.at(i).price, refDoub, op)) {
                    PrintObject(list.items.at(i), ToGuiPosition(i));
                }
            }
        }
        if(attribute == "quantity") {
            float refFloa;
            std::cout << "Enter reference value: ";
            std::cin >> refFloa;
            system("cls");
            for(int i =0; i<tableSize; i++){
                if(CmpGenericAttr <float> (list.items.at(i).quantity, refFloa ,op)) {
                    PrintObject(list.items.at(i), ToGuiPosition(i));
                }
            }
        }
        system("pause");
    }
}
void InitNewTab(ShoppingList & list)
{
    int tableSize;
    ChangeColor(ColLab::yellow);
    printf("Enter the table size: ");
    std::cin >> tableSize;
    if(tableSize == 0);
    else list.items.resize(tableSize);
    std::for_each(list.items.begin(), list.items.end(), [](Object &n){ReadObject(n);});
}
void DelTab(ShoppingList & list)
{  
    if(!list.items.empty()) list.items.clear();
    else  PrintError(ErrLab::noObj);
}
void AddObject(ShoppingList & list)
{
    Object tmp;
    ReadObject( tmp);
    list.items.push_back(tmp);
}
void DelObjectPos(ShoppingList & list)
{
    int tableSize= list.items.size();
    int pos;
    if(list.items.empty()) {
        PrintError((ErrLab::noObj));
        return;
    }
    while(true){
        PrintTable(list);
        ChangeColor(ColLab::yellow);
        std::cout << "\nWhat position should be deleted? [Enter \'0\' to leave]: ";
        fflush(stdin);
        std::cin >> pos;
        if(pos == 0) return;
        pos = ToGenPosition(pos);
        if(!IsPositionValid(pos, tableSize))  PrintError(ErrLab::wrongPos);
        else break;
    }

    if(tableSize == 1) list.items.clear();
    else {
        for(int i = pos ; i< tableSize-1; i++) list.items.at(i) = list.items.at(i+1);
        list.items.erase(list.items.end());
    }
}
int Menu(ShoppingList & list)
{
    PrintAuthor();
    std::cout << "Address of the table's first element: " << &list << "\nCurrent size of table: " << list.items.size() << "\n";
    printf("\n\n");
    ChangeColor(ColLab::cyan);
    printf("Welcome to the program that imitates a paper shopping list!\n");
    ChangeColor(ColLab::yellow);
    printf("[1] Create new table\n[2] Delete table\n[3] Add one object \n[4] Delete object at certain position\n[5] Print table \n[6] Print selected objects\nExit [K]\n");
    fflush(stdin);
    char c=getch();
    switch(c){
        case '1':
        system("cls");
        InitNewTab(list);
        break;

        case '2':
        system("cls");
        DelTab(list);
        break;

        case '3':
        system("cls");
        AddObject(list);
        break;

        case '4':
        system("cls");
        DelObjectPos(list);
        break;

        case '5':
        system("cls");
        PrintTable(list);
        break;

        case '6':
        system("cls");
        PrintSelected(list);
        system("Pause");
        break;

        case 'k':
        return 0;

        case 'K':
        return  0;

        default:
        PrintError(ErrLab::wrongPos);
    }
    return 1;
}

}

int main() {
    Lab6::ShoppingList list;
    while (Lab6::Menu(list));
    return 0;
}