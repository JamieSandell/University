//////////////////////////////////////////////////
///////////Author: Jamie Sandell
///////////Signed On: 11:12am - Tuesday 2nd December 2008
///////////Work Done:
///////////Signed Off:
////
//////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;
using CardGame;

namespace TimerTestHarness
{
    class Program
    {
        static void Main(string[] args)
        {
            Timer myTimer = new Timer();
            myTimer.StartTimer();
            Console.WriteLine("Timer started successfully");
            System.Threading.Thread.Sleep(1000);
            Console.WriteLine("Time elapsed = " + myTimer.GetTimeElapsed().ToString());
            myTimer.StopTimer();
            Console.WriteLine("Timer stopped successfully");
            myTimer.ResetTimer();
            Console.WriteLine("Timer reset successfully");
            Console.WriteLine("Press the 'Enter' key to quit...");
            Console.Read();
        }
    }
}
