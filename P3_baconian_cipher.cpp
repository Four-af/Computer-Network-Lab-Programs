#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;
map<char, string> cipherMap{{'a', "aaaaa"}, {'b', "aaaab"}, {'c', "aaaba"}, {'d', "aaabb"}, {'e', "aabaa"}, {'f', "aabab"}, {'g', "aabba"}, {'h', "aabbb"}, {'i', "abaaa"}, {'j', "abaab"}, {'k', "ababa"}, {'l', "ababb"}, {'m', "abbaa"}, {'n', "abbab"}, {'o', "abbba"}, {'p', "abbbb"}, {'q', "baaaa"}, {'r', "baaab"}, {'s', "baaba"}, {'t', "baabb"}, {'u', "babaa"}, {'v', "babab"}, {'w', "babba"}, {'x', "babbb"}, {'y', "bbaaa"}, {'z', "bbaab"}};

int main()
{
    cout << "\n____Aiman Fatima 20BCS008___\n";
    cout << "\n----Baconian Cipher----\n";
    string code;
    int option;
    while (1)
    {
        cout << "\n_____MENU____\n";
        cout << "1. Encrypt your text\n";
        cout << "2. Decrypt some encrypted text\n";
        cout << "3. Exit\n";
        cout << "\nEnter your choice : ";
        cin >> option;
        cin.ignore();
        char temp;
        if (option == 1)
        {
            cout << "Enter the string\n";
            getline(cin, code);
            for (int i = 0; i < code.length(); i++)
            {
                if (isalpha(code[i]))
                {
                    temp = tolower(code[i]);
                    cout << cipherMap.at(temp);
                }
                else if (isspace(code[i]))
                {
                    cout << " ";
                }
                else
                {
                    cout << code[i];
                }
            }
            cout << endl;
        }
        if (option == 2)
        {
            string s;
            cout << "Enter the encrypted string\n ";
            getline(cin, code);
            for (int i = 0; i < code.length(); i++)
            {
                code[i] = tolower(code[i]);
            }
            for (int i = 0; i < code.length(); i = i + 5)
            {
                for (int j = 0; j < 5; j++)
                {
                    s = s + code[i + j];
                }
                for (auto m : cipherMap)
                {
                    if (m.second == s)
                    {
                        cout << m.first;
                    }
                }
                s = "";
            }
            cout << endl;
        }
        if (option == 3)
        {
            cout << "\nThe End.\n\n";
            break;
        }
        cout << "\nDo you want to continue? (y/n) :  ";
        cin >> temp;
        if (temp == 'n')
        {
            cout << "\nThe End.\n\n";
            break;
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}