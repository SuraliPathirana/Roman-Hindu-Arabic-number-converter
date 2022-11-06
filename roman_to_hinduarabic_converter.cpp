/*****************************************************
--Programming  Quest 02--
Name            :W.P.S.V.PATHIRANA
Index Number    :19/ENG/073
Assignment      :02
Date            :13/09/2021
******************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;

/******************************************************
Function name:getValue
description:returns the value of each letter in the roman number
i/p :charcter in the roman number     o/p:character in hindu arabic 
*/

int getValue(char r)
{
    if (r == 'i')
        return 1;
    if (r == 'v')
        return 5;
    if (r == 'x')
        return 10;
    if (r == 'l')
        return 50;
    else if (r == 'c')
        return 100;
}

/*****************************************************
Function name:checkString
description:checks if there are invalid characters in the input
i/p :s-input roman number       o/p:true if no invalid characters
*/

bool checkString(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (!(s[i] == 'i' || s[i] == 'v' || s[i] == 'x' || s[i] == 'l' || s[i] == 'c'))
        {
            return false;
        }
    }
    return true;
}
/*********************************************************************
Function name:checkXOrder
description:check if 4 consecutive x are found(error-x can be in the number 4 times but they cannot be consecutive)
i/p :s-input roman number           o/p:true if 4 x are not in a row
*/
bool checkXOrder(string s)
{
    for (int i = 0; i < s.length() - 3; i++)
    {

        if (s[i] == 'x' && s[i + 1] == 'x' && s[i + 2] == 'x' && s[i + 3] == 'x')
        {
            return false;
        }
    }
    return true;
}
/*********************************************************************
Function name:checkRepeatCount
description:checks the repeating counts of the letters 
i/p :s-input roman number       o/p:true if valid counts
*/
bool checkRepeatCount(string s)
{
    int array[5] = {0, 0, 0, 0, 0}; //   column 0-i     column 1-v   column 2-x     column 3-l      column 4-c
    for (int i = 0; i < s.length(); i++)
    {
        switch (s[i])
        {
        case 'i':
        {
            array[0]++;
            break;
        }
        case 'v':
        {
            array[1]++;
            break;
        }
        case 'x':
        {
            array[2]++;
            break;
        }
        case 'l':
        {
            array[3]++;
            break;
        }
        case 'c':
        {
            array[4]++;
            break;
        }
        }

        if (array[1] > 1 || array[3] > 1) //l and v cannot repeat
        {
            return false;
        }
        if (array[2] == 4)
        {

            if (!checkXOrder(s)) //checks if 4 x are in a row
                return false;
        }
        if (array[0] > 3 || array[2] > 4 || array[4] > 3) // i and c can only repeat 3 times and x can only repeat 4 times
        {
            return false;
        }
    }
    return true;
}

/******************************************************************** 
Function name:checkOrderErrors
description:checks the errors in the order of the letters
i/p :s-input roman number           o/p:true if valid order

*/
bool checkOrderErrors(string s)
{

    if (s.length() >= 2)
    {
        if (s.length() >= 3)
        {
            vector<int> vec;

            for (int i = 0; i < s.length(); i++)
            {
                vec.push_back(getValue(s[i]));
            }

            for (int i = 0; i < vec.size() - 2; i++)
            {

                if (vec[i] == vec[i + 1] && vec[i + 1] < vec[i + 2]) //2 or more= numbers before a larger number is invalid -iix,iiix
                {
                    return false;
                }
                if (vec[i] < vec[i + 1] && vec[i + 1] < vec[i + 2]) //3 numbers in ascending order is invalid ex:ivx invalid
                {
                    return false;
                }
            }

            for (int i = 0; i < s.length() - 1; i++) // i with x,v,l,c can come only at the end    ix-valid     ixv-invalid
            {
                if (s[i] == 'i' && (s[i + 1] == 'x' || s[i + 1] == 'v' || s[i + 1] == 'c') && i + 1 != s.length() - 1)
                {
                    return false;
                }
            }
        }
        for (int i = 0; i < s.length() - 1; i++) // i  cannot come befor l or c  xil-invalid
        {
            if (s[i] == 'i' && (s[i + 1] == 'c' || s[i + 1] == 'l'))
            {
                return false;
            }
        }
    }

    return true;
}

/**********************************************************
Function name:calculateNumber
description:calculates the arabic number
i/p :s-input roman number           o/p:hindu arabic number
*/

int calculateNumber(string s)
{

    int sum = 0;
    for (int i = 0; i < s.length(); i++)
    {
        int d1 = getValue(s[i]);
        if (i + 1 < s.length())
        {
            int d2 = getValue(s[i + 1]);
            if (d1 >= d2) //add if 1st num is greater than 2nd num
            {
                sum = sum + d1;
            }
            else
            {
                if (s[i] != 'v' && s[i] != 'l') // v and l are not substracted
                {
                    sum = sum + d2 - d1; //substract if 1st num is greater than 2nd num
                    i++;
                }
                else
                {
                    return -1;
                }
            }
        }
        else
            sum = sum + d1;
    }
    return sum;
}

int main()
{
    const int digits = 8; //max  roman letters in input
    //to scale up to 300,change 8->10
    string romanNum;

    cout << "\n  ********Roman-Hindu Arabic converter********  " << endl;
    cout << "\tlimit - upto 100 (8 roman digits)\n"
         << endl;

    ifstream romanNumberFile("numbers.txt"); //read from the input file
    if (!romanNumberFile.is_open())
    {
        cout << "Cannot open file!" << endl;
        return 0;
    }
    while (!romanNumberFile.eof())
    {
        string romanNum;
        romanNumberFile >> romanNum;
        if (romanNumberFile.eof()) //to stop duplicating the last line
            break;

        std::transform(romanNum.begin(), romanNum.end(), romanNum.begin(), ::tolower); //convert string to lower case
        cout << "Roman number =" << romanNum << setw(25 - romanNum.length()) << right << " ";

        if (romanNum.length() > digits)
        {
            cout << "Input is out of range!" << endl;
        }
        else if (!checkString(romanNum) || !checkRepeatCount(romanNum) || !checkOrderErrors(romanNum)) //validate input
        {
            cout << "Invalid input!" << endl;
        }

        else
        {

            if (calculateNumber(romanNum) == -1)
            {
                cout << "Invalid input!" << endl;
            }
            else
            {
                cout << "Hindu Arabic:" << calculateNumber(romanNum) << endl;
            }
        }
    }
    romanNumberFile.close(); // Close the file
    cout << "\n End of file...." << endl;
}