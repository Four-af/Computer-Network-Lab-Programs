#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <map>

using namespace std;

map<int, int> keyMap;

void setPermutationOrder(string key)
{
    for (int i = 0; i < key.length(); i++)
    {
        keyMap[key[i]] = i;
    }
}

// Encryption
string encrypt(string msg, string key, vector<char> &encrypted)
{
    int row, col, j;
    col = key.length();
    row = msg.length() / col;

    if (msg.length() % col)
        row += 1;
    vector<vector<char>> matrix(row, vector<char>(col, '#'));

    for (int i = 0, k = 0; i < row; i++)
    {
        for (int j = 0; j < col;)
        {
            if (msg[k] == '\0')
            {
                matrix[i][j] = '_';
                j++;
            }

            if (isalpha(msg[k]) || msg[k] == ' ')
            {
                matrix[i][j] = msg[k];
                j++;
            }
            k++;
        }
    }

    for (map<int, int>::iterator ii = keyMap.begin(); ii != keyMap.end(); ++ii)
    {
        j = ii->second;
        for (int i = 0; i < row; i++)
        {
            if (isalpha(matrix[i][j]) || matrix[i][j] == ' ' || matrix[i][j] == '_')
            {
                encrypted.push_back(matrix[i][j]);
            }
        }
    }
    cout << "Encrypted code is : ";
    return string(encrypted.begin(), encrypted.end());
}

// Decryption
string decrypt(vector<char> &cipher, string key)
{
    int col = key.length();
    int row = cipher.size() / col;
    int n = cipher.size();
    cout << "The encrypted code is : ";
    for (int i = 0; i < n; i++)
    {
        cout << cipher[i];
    }
    string kk;
    cout << endl;
    cout << "Enter the key : ";
    cin >> kk;
    if (kk != key)
    {
        cout << "Wrong key entered. Try again.";
        return "";
    }
    vector<vector<char>> cipherMat(row, vector<char>(col, '#'));
    for (int j = 0, k = 0; j < col; j++)
        for (int i = 0; i < row; i++)
            cipherMat[i][j] = cipher[k++];
    int index = 0;
    for (map<int, int>::iterator ii = keyMap.begin(); ii != keyMap.end(); ++ii)
        ii->second = index++;
    vector<vector<char>> decCipher(row, vector<char>(col, '#'));
    map<int, int>::iterator ii = keyMap.begin();
    int k = 0;
    for (int l = 0, j; key[l] != '\0'; k++)
    {
        j = keyMap[key[l++]];
        for (int i = 0; i < row; i++)
        {
            decCipher[i][k] = cipherMat[i][j];
        }
    }
    string msg = "";
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (decCipher[i][j] != '_')
                msg += decCipher[i][j];
        }
    }
    cout << "Decrypted message is : ";
    return msg;
}

int main()
{
    cout << "\n____Aiman Fatima 20BCS008___\n";
    cout << "\n----Transposition Cipher----\n";
    string code, key;
    vector<char> encrypted, e;
    int flag = 0;
    int choice;
    while (1)
    {
        cout << "\n_____MENU____\n";
        cout << "1. Encrypt your text\n";
        cout << "2. Decrypt some encrypted text\n";
        cout << "3. Exit\n";
        cout << "\nEnter your choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "\nEnter a code to encrypt : ";
            // fflush(stdin);
            getchar();
            getline(cin, code);
            cout << "\nEnter a key to encrypt : ";
            cin >> key;
            keyMap.clear();
            setPermutationOrder(key);
            cout << encrypt(code, key, encrypted) << endl;
            e = encrypted;
            encrypted.clear();
            flag = 1;
            break;
        case 2:
            if (flag == 0)
            {
                cout << "\nYou have nothing to decrypt\n";
            }
            else
            {
                cout << decrypt(e, key) << endl;
            }
            break;
        case 3:
            cout << "\nThe End.\n\n";
            return 0;
        default:
            cout << "\nWrong Choice!!\n";
        }
    }
    return 0;
}