using System;
using System.Collections.Generic;
using System.Text;
using PalindromeEngine;

namespace PalindromeTests
{
    class PalindromeTests
    {
        public void DoPalindromeTests(IPalindrome palindrome)
        {
            string reply;
            bool isPalindrome;

            Console.WriteLine("Palindrome Tests");

            reply = palindrome.VerifyText("123321", out isPalindrome);
            if (reply.Length > 0) // VerifyText returns "" if their was no problems.
            {
                Console.WriteLine("Testing Failed");
            }
            else
            {
                Console.WriteLine("Executing the VerifyText method was successful");
            }
            if (isPalindrome == false) // It should equal true for 123321
            {
                Console.WriteLine("Testing Failed");
            }
            else
            {
                Console.WriteLine("isPalindrome is correctly set to true for the palindrome '123321'");
            }

            reply = palindrome.VerifyText("123", out isPalindrome);
            if (reply.Length > 0) // VerifyText returns "" if their was no problems.
            {
                Console.WriteLine("Testing Failed");
            }
            else
            {
                Console.WriteLine("Executing the VerifyText method was successful");
            }
            if (isPalindrome == true) // It should equal false for 123
            {
                Console.WriteLine("Testing Failed");
            }
            else
            {
                Console.WriteLine("isPalindrome is correctly set to false for '123'");
            }

            reply = palindrome.VerifyText("mum, . ;", out isPalindrome);
            if (reply.Length > 0) // VerifyText returns "" if their was no problems.
            {
                Console.WriteLine("Testing Failed");
            }
            else
            {
                Console.WriteLine("Executing the VerifyText method was successful");
            }
            if (isPalindrome == false) // It should equal true for mum, . ;
            {
                Console.WriteLine("Testing Failed");
            }
            else
            {
                Console.WriteLine("isPalindrome is correctly set to true for the palindrome 'mum, . ;'");
            }

        }
    }

    class TestProgram
    {
        static void Main(string[] args)
        {
            PalindromeTests tester = new PalindromeTests(); // use of classes/instances here makes it much more clearer/readable
            Palindrome testPalindrome = new Palindrome();

            tester.DoPalindromeTests(testPalindrome);
            Console.WriteLine("Press return to continue");
            Console.ReadLine();
        }
    }
}
