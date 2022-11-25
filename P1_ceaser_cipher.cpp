#include <bits/stdc++.h>
using namespace std;

string encrypt(string msg, int key)
{
    string res = "";

    for (auto &i : msg)
    {
        res += (((i - 'a' + key) % 26) + 'a');
    }
    return res;
}

string decrypt(string msg, int key)
{
    string res = "";

    for (auto &i : msg)
    {
        res += ('a' + ((i - 'a' - key + 26) % 26));
    }
    return res;
}

int main()
{
    cout << "\n____Aiman Fatima 20BCS008___\n";
    cout << "\n----Caesar Cipher----\n";
    string msg;
    string hidden_msg, clear_msg;
    int key;
    while (1)
    {
        cout << "\n_____MENU____\n";
        cout << "1. Encrypt your text\n";
        cout << "2. Decrypt some encrypted text\n";
        cout << "3. Exit\n";
        cout << "\nEnter your choice : ";
        int choice;
        cin >> choice;
        msg.clear();
        switch (choice)
        {
        case 1:
            cout << "\nEnter original message : ";
            getchar();
            getline(cin, msg);
            cout << "\nEnter key : ";
            cin >> key;
            hidden_msg = encrypt(msg, key);
            cout << "Cipher Text : " << hidden_msg << "\n";
            break;
        case 2:
            cout << "\nEnter decrypted text : ";
            getchar();
            getline(cin, msg);
            cout << "\nEnter key : ";
            cin >> key;
            clear_msg = decrypt(msg, key);
            cout << "Deciphered Text : " << clear_msg << "\n";
            break;
        case 3:
            cout << "\nThe End.\n\n";
            return 0;
        default:
            cout << "\nWrong Choice!!\n";
        }
    }
}