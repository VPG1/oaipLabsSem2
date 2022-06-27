#include "binarynum.h"

bool k_bit(vector<char> str1, int k)
{
    vector<char> str = str1;
    int bit, i = 0;
    int lenstr = len(str);

    for (; i != k; i++)
    {
        bit = (str[lenstr - 1] - '0') % 2;
        str[lenstr - 1] = str[lenstr - 1] - bit;

        for (int j = lenstr - 1; j >= 0; j--)
        {
            if ((str[j] - '0') % 2 == 0)
            {
                str[j] = (str[j] - '0') / 2 + '0';
            }
            else
            {
                str[j] = (str[j] - '0') / 2 + '0';

                if (j != lenstr - 1)
                {
                    str[j + 1] = str[j + 1] + 5;
                }
            }
        }
    }

    return(bit);
}


int len(vector<char>& a)
{
    int len = 0;

    for (; a[len] != 'q'; len++);

    return(len);
}

vector<char> powstr(vector<char>& str, int k)
{
    vector<char> deg;

    deg.push_back('1');

    if (k == 0)
    {
        deg.push_back('q');
        return(deg);
    }

    for (int i = 0; i < k; i++)
    {
        deg.push_back('0');
    }

    for (int i = deg.size() - 1, j = len(str) - 1; i >= 0 && j >= 0; i--, j--)
    {
        deg[i] = str[j];
    }

    deg.push_back('q');
    return(deg);
}
