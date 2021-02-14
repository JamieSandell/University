using System;
using System.Collections.Generic;
using System.Text;
using AccountManagement;

namespace AccountTests
{

    class BankTests
    {
        public void DoAccountTests (IAccount account)
        {
            // If the action was successful an empty string is returned
            // Every test should pass, a pass remark does not mean the action was successful,
            // a pass mark simply means that the correct action was taking (e.g. allowing/disallowing a withdrawl)
            bool inTheRed = false;
            int failureCounter = 0;

            Console.WriteLine("Account Tests");
            Console.WriteLine("-------------");
            string reply;

            reply = account.SetName("");
            if (reply.Length != 0)
            {
                Console.WriteLine("Account SetName empty string test - Failed");
                failureCounter++;
            }
            else
            {
                Console.WriteLine("Account SetName empty string test - Passed");
            }

            reply = account.SetName("1234");
            if (reply.Length != 0)
            {
                Console.WriteLine("Account SetName numbers in name test Failed");
                failureCounter++;
            }
            else
            {
                Console.WriteLine("Account SetName numbers in name test - Passed");
            }

            reply = account.SetName("Fred");
            if (reply.Length != 0)
            {
                Console.WriteLine("Account SetName Fred - Failed");
                failureCounter++;
            }
            else
            {
                Console.WriteLine("Account SetName Fred - Passed");
            }

            reply = account.PayInFunds(-1, ref inTheRed);
            if (reply.Length == 0)
            {
                Console.WriteLine("Account PayInFunds -1 test - Failed");
                failureCounter++;
            }
            else
            {
                Console.WriteLine("Account PayInFunds -1 test - Passed");
            }

            reply = account.PayInFunds(-10, ref inTheRed);
            if (reply.Length == 0)
            {
                Console.WriteLine("Account PayInFunds -10 test - Failed");
                failureCounter++;
            }
            else
            {
                Console.WriteLine("Account PayInFunds -10 test - Passed");
            }

            reply = account.PayInFunds(1, ref inTheRed);
            if (reply.Length != 0)
            {
                Console.WriteLine("Account PayInFunds 1 test - Failed");
                failureCounter++;
            }
            else
            {
                Console.WriteLine("Account PayInFunds 1 test - Passed");
            }

            reply = account.WithdrawFunds(-1, ref inTheRed);
            if (reply.Length == 0)
            {
                Console.WriteLine("Account WithdrawFunds -1 test - Failed");
                failureCounter++;
            }
            else
            {
                Console.WriteLine("Account WithdrawFunds -1 test - Passed");
            }

            reply = account.WithdrawFunds(-10, ref inTheRed);
            if (reply.Length == 0)
            {
                Console.WriteLine("Account WithdrawFunds -10 test - Failed");
                failureCounter++;
            }
            else
            {
                Console.WriteLine("Account WithdrawFunds -10 test - Passed");
            }

            reply = account.WithdrawFunds(500, ref inTheRed);
            if (reply.Length == 0)
            {
                Console.WriteLine("Account WithdrawFunds 500 test - Failed");
                failureCounter++;
            }
            else
            {
                Console.WriteLine("Account WithdrawFunds 500 test - Passed");
            }

            reply = account.WithdrawFunds(1500, ref inTheRed);
            if (reply.Length == 0)
            {
                Console.WriteLine("Account WithdrawFunds 1500 test - Failed");
                failureCounter++;
            }
            else
            {
                Console.WriteLine("Account WithdrawFunds 1500 test - Passed");
            }

            reply = account.WithdrawFunds(300, ref inTheRed);
            if (reply.Length == 0)
            {
                Console.WriteLine("Account WithdrawFunds 300 test - Failed");
                failureCounter++;
            }
            else
            {
                Console.WriteLine("Account WithdrawFunds 300 test - Passed");
            }

            Console.WriteLine();
            Console.WriteLine("Test Analysis");
            Console.WriteLine("-------------");
            if (failureCounter > 0)
            {
                Console.WriteLine("There where " + failureCounter + " failures, the code needs fixing.");
            }
            else
            {
                Console.WriteLine("There where " + failureCounter + " failures, the code works correctly.");
            }


        }
    }

    class TestProgram
    {
        static void Main(string[] args)
        {
            BankTests tester = new BankTests();
            Account testAccount = new Account("", "", 1);

            tester.DoAccountTests(testAccount); // Run the tests
            Console.Write("Press return to continue");
            Console.ReadLine();
        }
    }
}
