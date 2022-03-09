#include <iostream>

using namespace std;

long double largestPalindromeFromDigits(int digitlength)
{
    if (digitlength > 1)
    {
        long double palindromeMax = 0;
        long double curPalindrome = 0;

        //this calculates the minimum number we start with. example: digitlength = 4, base = 1000
        unsigned long long int base = 1;
        for (int i = 0; i < digitlength - 1; ++i)
        {
            base *= 10;
        }

        //this calculates the max base number we can have. example: digitlength = 4, maxbase = 9999
        unsigned long long int maxbase = 1;
        for (int i = 0; i < digitlength; ++i)
        {
            maxbase *= 10;
        }
        maxbase--;

        //I noticed a pattern with the palindrome. Neither of the multiplied numbers would be larger than 10^(numdigits)-10^(numdigits-4)
        //By ending the nested for loop when this "max difference" is crossed, the runtime significantly decreased with the same results
        unsigned long int maxdifference = 10;

        if (digitlength > 3)
        {

            for (int i = 0; i < digitlength - 4; ++i)
            {
                maxdifference *= 10;
            }
        }

        //cout << base << " " << maxbase;

        //these variables are for checking if the multiplied number matches with its reverse
        //string reversepalindrome;
        //string temppalindrome;
        long double reversepalindrome = 0;
        unsigned long long int temppalindrome;


        //algorithm to check each possible calculation, start from max
        for (unsigned long long int i = maxbase; i >= base; i--)
        {

            for (unsigned long long int j = maxbase; j >= maxbase - maxdifference; j--)
            {
                //calculate current palindrome
                curPalindrome = (unsigned long long int)i * (unsigned long long int)j;

                /* inefficient algorithm, but keeping to show my first thought
                //I had originally calculated the reverse of i*j by converting it to a string
                temppalindrome = to_string(curPalindrome);

                //reverse the current palindrome
                for (int i = temppalindrome.length()-1; i >= 0; --i)
                {
                    reversepalindrome += temppalindrome.at(i);
                }
                */

                temppalindrome = curPalindrome;
                //calculate the reverse current 
                while (temppalindrome != 0)
                {
                    reversepalindrome *= 10;
                    reversepalindrome += temppalindrome % 10;
                    temppalindrome /= 10;
                }
                //check if reversepalindrome equals curPalindrome and curPalindrome is larger than current palindromeMax
                if (reversepalindrome == curPalindrome && curPalindrome > palindromeMax)
                {
                    palindromeMax = curPalindrome;
                    //now that the max palindrome has been found, there is no need to continue. This improves runtime significantly by exiting
                    i = base - 1; j = base - 1;
                }

                reversepalindrome = 0;



            } // end j loop

        } // end i loop



        return palindromeMax;
    }
    else
    {
        //if the input number is not greater than 1, it cannot have a max palindrome. 
        return 0;
    }
}

int main()
{
    double sum = 0;
    clock_t start_s = clock();
    long double test = largestPalindromeFromDigits(7);
    clock_t stop_s = clock();
    sum = ((double)(stop_s - start_s) / CLOCKS_PER_SEC) / 100000; //average time
    cout << fixed << test << endl;
    cout << sum;
    return 0;
}