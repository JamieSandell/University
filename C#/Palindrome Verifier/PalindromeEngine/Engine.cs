using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace PalindromeEngine
{

    public interface IPalindrome
    {
        /// <summary>
        /// Verify if the entered text is a palindrome
        /// </summary>
        /// <param name="textToVerify">The entered text to be verified</param>
        /// <param name="wasPalindrome">Stores the status of the verification</param>
        /// <returns>An empty string if the text was successfully verified, otherwise an error message. </returns>
        string VerifyText(string textToVerify, out bool isPalindrome);
    }

    public class Palindrome : IPalindrome
    {
        public string VerifyText(string textToVerify, out bool isPalindrome)
        {
// 	String x;
//    Boolean f;
//    integer a, z,g;
//    x = readinput
//    g = length of x
//    z = g minus one;
//    a = zero
//    if g = 1  then f = 1
//        else	
//            f = 1;
//            while (f=1 and a less than z)
//while character at a of x is one of [whitespace,comma,semicolon, or full stop] 
//    a++;
//while character at z of x is one of [whitespace,comma,semicolon, or full stop]
//    z--;
//if  the toUpperCase of character at a of x is identical to
//    the toUpperCase of character at z of x
//    then a++ and z--;
//                else f=0;
//if f=0 then print out appropriate message
//        else print out other appropriate message

            string x;
            bool f;
            int a, z, g;
            x = textToVerify; // user input
            char[] ch = x.ToCharArray(); // Array of characters for string manipulation
            g = x.Length;
            z = g - 1;
            a = 0;


            /// The algorithm is a palindrome checker, however, white spaces are ignored
            /// which means that whilst "mum dad" is a palindrome it isn't seen as one by the computer,
            /// this is because the computer sees it as "mumdad" which isn't a palindrome.
            if (g == 1)
            {
                f = true;
            }
            else
            {
                f = true;
            }

            while( f == true && a < z)
            {
                while (x[a] == ' ' || x[a] == ',' || x[a] == '.' || x[a] == ';')
                {
                    a++;
                }

                while (x[z] == ' ' || x[z] == ',' || x[z] == '.' || x[z] == ';')
                {
                    z--;
                }
                
                if (Char.ToUpper(x[a]) == Char.ToUpper(x[z]))
                {
                    a++;
                    z--;
                }
                else
                {
                    f = false;
                }
            }
            if (f == false)
            {
                isPalindrome = false;
            }
            else
            {
                isPalindrome = true;
            }

            return "";
        }
    }
}
