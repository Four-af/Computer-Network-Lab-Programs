#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Playfair
{

public:
    char keyMatrix[5][5];
    string getKey()
    {
        string k;
        cout << "Enter the key : ";
        cin >> k;
        return k;
    }
    string getMessage()
    {
        string m;
        cout << "Enter the message : ";
        cin >> m;
        return m;
    }
    void encrypt(string msg, string key)
    {
        makeKeyMatrix(key);
        cout << "\n----------Encryption Process------------\n"
             << endl;
        string bg = getBigrams(msg);
        int n = bg.length();
        vector<char> ct(n);
        int x = 0;
        while (x < n)
        {
            int a_row = 0, a_col = 0, b_row = 0, b_col = 0;
            char ca = ' ', cb = ' ';
            getPosition(bg[x], bg[x + 1], a_row, a_col, b_row, b_col);
            if (a_row == b_row)
            {
                ca = keyMatrix[a_row][mod((a_col + 1), 5)];
                cb = keyMatrix[b_row][mod((b_col + 1), 5)];
            }
            else if (a_col == b_col)
            {
                ca = keyMatrix[mod((a_row + 1), 5)][a_col];
                cb = keyMatrix[mod((b_row + 1), 5)][b_col];
            }
            else
            {
                ca = keyMatrix[a_row][b_col];
                cb = keyMatrix[b_row][a_col];
            }

            cout << bg[x] << bg[x + 1] << "--->" << ca << cb << endl;
            ct[x] = ca;
            ct[x + 1] = cb;
            x += 2;
        }
        cout << "\n>>The cipher text is :  ";
        for (int i = 0; i < n; i++)
        {
            cout << ct[i];
        }
        cout << endl;
    }

    // function for decryption
    void decrypt(string msg, string key)
    {
        makeKeyMatrix(key);
        cout << "\n----------Decryption Process------------" << endl;
        // string bg = getBigrams(msg);
        int n = msg.length();
        vector<char> pt(n);
        int x = 0;
        while (x < n)
        {
            int a_row = 0, a_col = 0, b_row = 0, b_col = 0;
            char pa = ' ', pb = ' ';
            char c1 = toupper(msg[x]);
            char c2 = toupper(msg[x + 1]);
            getPosition(c1, c2, a_row, a_col, b_row, b_col);
            // cout<<a_row<<","<<a_col<<","<<b_row<<","<<b_col;
            if (a_row == b_row)
            {
                pa = keyMatrix[a_row][mod((a_col - 1), 5)];
                pb = keyMatrix[b_row][mod((b_col - 1), 5)];
            }
            else if (a_col == b_col)
            {
                pa = keyMatrix[mod((a_row - 1), 5)][a_col];
                pb = keyMatrix[mod((b_row - 1), 5)][b_col];
            }
            else
            {
                pa = keyMatrix[a_row][b_col];
                pb = keyMatrix[b_row][a_col];
            }

            cout << msg[x] << msg[x + 1] << "--->" << pa << pb << endl;
            pt[x] = pa;
            pt[x + 1] = pb;
            x += 2;
        }
        cout << "\n>>The plain text is :  ";
        for (int i = 0; i < n; i++)
        {
            cout << pt[i];
        }
        cout << endl;
    }

private:
    string getBigrams(string msg)
    {
        int len = msg.length();
        vector<char> a(len);
        int n = 0;
        string bigrams(len, ' ');
        for (int i = 0; i < len; i++)
        {
            if (msg[i] == ' ')
            { // ignore space
                continue;
            }
            else if (msg[i] == 'j' || msg[i] == 'J')
            {
                a[n] = 'I'; // replace j or J  with I
                n++;
            }
            else
            {
                a[n] = toupper(msg[i]);
                n++;
            }
        }
        int k = 0;
        char filler = 'X';
        bool filled = false;
        for (int i = 0; i < n; i += 2)
        {
            bigrams[k] = a[i];
            k++;
            if (i + 1 != n)
            {
                if (a[i] == a[i + 1] && filled == false)
                {
                    bigrams[k] = filler;
                    k++;
                    bigrams[k] = a[i + 1];
                    k++;
                    filled = true;
                    continue;
                }
                else
                {
                    bigrams[k] = a[i + 1];
                    k++;
                }
            }
        }
        if (k % 2 != 0)
        {
            bigrams[k] = filler;
            bigrams[k + 1] = '\0';
        }
        else
        {
            bigrams[k] = '\0';
        }
        return bigrams;
    }

    // function to generate key matrix
    void makeKeyMatrix(string text)
    {
        int len = text.length();
        vector<char> ca(len);
        int n = 0;
        for (int i = 0; i < len; i++)
        {
            if (text[i] == ' ')
            {
                continue;
            }
            ca[n] = toupper(text[i]);
            n++;
        }

        // array of alphabets
        char alphabets[26];
        for (int i = 0; i < 26; i++)
        {
            alphabets[i] = i + 65;
        }

        char oneD[26];
        int p = 0;
        oneD[0] = ca[0];
        for (int i = 1; i < n; i++)
        {
            bool duplicate = false;
            for (int j = 0; j < i; j++)
            {
                if (ca[i] == ca[j])
                { // avoid duplicates
                    duplicate = true;
                    break;
                }
            }
            if (duplicate == false)
            {
                oneD[++p] = ca[i];
            }
        }
        if (p < 26)
        {
            for (int i = 0; i < 26; i++)
            {
                bool duplicate = false;
                for (int j = 0; j < p; j++)
                {
                    if (alphabets[i] == oneD[j])
                    {
                        duplicate = true;
                        break;
                    }
                }
                if (duplicate == false)
                {
                    oneD[++p] = alphabets[i];
                }
            }
            p = 0;
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    if (oneD[p] == 'J')
                    {
                        p++;
                    }
                    keyMatrix[i][j] = oneD[p];
                    p++;
                }
            }
            cout << "\n|| Key matrix for Playfair Cipher for given key ||\n";

            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {

                    cout << keyMatrix[i][j] << " ";
                }
                cout << "\n";
            }
        }
    }

    void getPosition(char a, char b, int &a_row, int &a_column, int &b_row, int &b_column)
    {
        bool match_a = false;
        bool match_b = false;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (keyMatrix[i][j] == a && match_a != true)
                {
                    a_row = i;
                    a_column = j;
                    // cout<<keyMatrix[i][j];
                    match_a = true;
                }
                if (keyMatrix[i][j] == b && match_b != true)
                {
                    b_row = i;
                    b_column = j;
                    // cout<<keyMatrix[i][j];
                    match_b = true;
                }
            }
            if (match_a && match_b)
            {
                break;
            }
        }
    }
    int mod(int a, int b)
    { // to handle modulo operation
        int c = a % b;
        if (c >= 0)
            return c;
        else
            return b + c;
    }
};
int main()
{
    cout << "\n____Aiman Fatima 20BCS008___\n";
    cout << "\n----Playfair Cipher----\n";
    int choice;
    Playfair p;
    string m, k;
    while (1)
    {
        cout << "\n_____MENU____\n";
        cout << "1. Encrypt your text\n";
        cout << "2. Decrypt some encrypted text\n";
        cout << "3. Exit\n";
        cout << "\nEnter your choice : ";
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
            k = p.getKey();
            m = p.getMessage();
            p.encrypt(m, k);
            break;
        case 2:
            k = p.getKey();
            m = p.getMessage();
            p.decrypt(m, k);
            break;
        case 3:
            cout << "The End.\n\n";
            return 0;
        default:
            cout << "Wrong Choice!!\n";
        }
    }
    return 0;
}