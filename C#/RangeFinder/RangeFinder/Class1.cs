using System;
using System.IO;

namespace ProfitCalculator
{
    public class RangeFinder
    {
        /// <summary>
        /// Performs a search to find the start and end of the "best" period and the
        /// total amount of sales over that period.
        /// </summary>
        /// <param name="data">the data to be examined</param>
        /// <param name="bestStart">the start point found by the search</param>
        /// <param name="bestEnd">the end point found by the search</param>
        /// <param name="bestTotal">the total sales over that period</param>
        /// <param name="loops">the number of executions of the inner loop</param>
        public static void Search(double[] data, out int bestStart,
            out int bestEnd, out double bestTotal, out int loops)
        {
            /// 1st search algo
            /// For every possible start position // every array index
            ///   For every possible end position // rest of array  from current start
            ///     {
            ///        Set subtotal to 0
            ///        For every value in subseq // between current and end
            ///             Add profit value to subtotal
            ///        Update subseq info when subtotal exceeds current best total
            ///     }
            /// 

            bestTotal = 0;
            bestStart = 0;
            bestEnd = 0;
            loops = 0;
            double subTotal = 0;     

            for (int i = 0; i < data.Length; i++)
            {
                for (int j = i; j < data.Length; j++)
                {
                    subTotal = 0;
                    for (int k = i; k >=i && k <= j && k < data.Length; k++)
                    {
                        subTotal = subTotal + data[k];
                        loops++;
                    }
                    if (subTotal > bestTotal)
                    {
                        bestTotal = subTotal;
                        bestStart = i;
                        bestEnd = j;
                    }
                }
            }
        }

        public static void Search2(double[] data, out int bestStart,
            out int bestEnd, out double bestTotal, out int loops)
        {
            /// 2nd search algo
            /// For every possible start position
            ///     Set subtotal to 0
            ///     For every possible end position
            ///     {
            ///         Add end position's profit value to subtotal
            ///         Update subseq if subtotal exceeds current best total
            ///     }
            ///     

            bestTotal = 0;
            bestStart = 0;
            bestEnd = 0;
            loops = 0;
            double subTotal = 0;

            for (int i = 0; i < data.Length; i++)
            {
                subTotal = 0;
                for (int j = i; j < data.Length; j++)
                {
               
                    subTotal = subTotal + data[j];
                    loops++;
                    if (subTotal > bestTotal)
                    {
                        bestTotal = subTotal;
                        bestStart = i;
                        bestEnd = j;
                    }
                }

            }
        }

        public static void Search3(double[] data, out int bestStart,
    out int bestEnd, out double bestTotal, out int loops)
        {
            /// 3rd search algo
            /// Set start position to 0, subtotal to 0
            /// For every profit value... // index from 0 to end of array as end position
            /// {
            ///     Add value to subtotal
            ///     Keep subseq info (start, end, total) if total exceeds current best
            ///     If total is less than 0,
            ///         set start position to next index and set total to 0
            /// }
            ///     

            double subTotal = 0;


            bestTotal = 0;
            bestStart = 0;
            bestEnd = 0;
            loops = 0;
            int startTemp = 0;

            for (int i = 0; i < data.Length; i++)
            {
                loops++;
                subTotal += data[i];


                if (subTotal > bestTotal)
                {
                    bestStart = startTemp;
                    bestEnd = i;
                    bestTotal = subTotal;
                }

                else if (subTotal < 0)
                {
                    startTemp = i + 1;
                    subTotal = 0;
                }



            }
        }

        /// <summary>
        /// Tests the Profits Calculator
        /// </summary>
        class Test
        {
            /// <summary>
            /// The main entry point for the application
            /// </summary>
            static void Main()
            {
                double [] data;
                int bestStart, bestEnd;
                double bestTotal;
                int loops;

                /// name of the file and the number of readings
                string filename = "week208.txt";
                int items = 208;

                data = new double[items];

                try
                {
                    TextReader textIn = new StreamReader(filename);
                    for (int i = 0; i < items; i++)
                    {
                        string line = textIn.ReadLine();
                        data[i] = double.Parse(line);
                    }
                    textIn.Close();
                }
                catch
                {
                    Console.WriteLine("Failed to read file " + filename);
                    Console.ReadLine();
                    return;
                }

                RangeFinder.Search(
                    data, out bestStart, out bestEnd, out bestTotal, out loops);

                Console.WriteLine("Start : {0} End : {1} Total  {2} Loops {3}",
                    bestStart, bestEnd, bestTotal, loops);

                Console.ReadLine();

                RangeFinder.Search2(
                    data, out bestStart, out bestEnd, out bestTotal, out loops);

                Console.WriteLine("Start : {0} End : {1} Total  {2} Loops {3}",
                    bestStart, bestEnd, bestTotal, loops);

                Console.ReadLine();

                RangeFinder.Search3(
                    data, out bestStart, out bestEnd, out bestTotal, out loops);

                Console.WriteLine("Start : {0} End : {1} Total  {2} Loops {3}",
                    bestStart, bestEnd, bestTotal, loops);

                Console.ReadLine();

            }
        }
    }
}