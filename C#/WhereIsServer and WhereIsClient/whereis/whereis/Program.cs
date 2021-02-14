using System;
using System.Net.Sockets;
using System.IO;
using System.Windows.Forms;
using System.Threading;
using Logging;

namespace whereis
{
    public class Whois
    {
        // Parameters passed in will populate these variables
        private string inName;
        private string inLocation;
        private string inServer;

        public string WriteToLog(string message, string status, string server) // Write to the log file
        {
            LoggingSystem log = new LoggingSystem();
            string reply = log.WriteToLog(message, ".\\log.txt", status, server);
            return reply;
        }

        public void PopulateLocation(string[] inArgs) // Populate the location parameter
        {
            inLocation = inArgs[2];
        }

        public void PopulateServer(string[] inArgs) // Populate the server parameter
        {
            inServer = inArgs[0];
        }

        public void PopulateName(string[] inArgs) // Populate the name parameter
        {
            inName = inArgs[1];
        }

        public string ConnectAndReceive(string[] args, out string response) // Connect to the server
            // and receive data from the server
        {
            string errorReply = "";
            response = "";

            // Console validation - using ui
            if (args.Length < 2)
            {
                errorReply = "You didn't specify a name.";
                return errorReply;
            }

            // Form validation - using gui
            if (args[0] == "")
            {
                errorReply = "You didn't specify a server.";
                return errorReply;
            }

            if (args[1] == "")
            {
                errorReply = "You didn't specify a name.";
                return errorReply;
            }
            // If here then passed the validation tests
            TcpClient client = new TcpClient(); // Initialise a new client

            client.SendTimeout = 1000; // Set the timeout to 1 second (100ms)
            try
            {
                client.Connect(args[0], 43); // [0] == the server
                StreamWriter sw = new StreamWriter(client.GetStream());
                StreamReader sr = new StreamReader(client.GetStream());
                // Find out if they specified a location and act accordingly
                if (args.Length > 2) // So don't go out of bounds when using the console ui
                {
                    if (args[2] != "") // Then they specified a name and location
                    {
                        sw.WriteLine(args[1] = args[1] + " " + args[2]); // [1] == person's name [2] == location
                        WriteToLog("SENT: " + args[1], "", args[0]); // Keep a log of client's actions
                    }
                    else // Location specified was ""
                    {
                        sw.WriteLine(args[1]); // [1] == person's name
                        WriteToLog("SENT: " + args[1], "", args[0]);
                    }
                }
                else // Specified a name and not a location
                {
                    sw.WriteLine(args[1]); // [1] == person's name
                    WriteToLog("SENT: " + args[1], "", args[0]);
                }
                sw.Flush();
                response = sr.ReadToEnd();
                WriteToLog("RECEIVED: " + response, "", args[0]);
            }
            catch (Exception e)
            {
                errorReply = "An error occurred whilst connecting to the server, check the log for further details.";
                WriteToLog("ERROR: " + e.ToString(), "", "Local Client");
                return errorReply;
            }
            //client.Close(); // disconnect from server - don't do this, this is the servers job
            return errorReply; // Everything went ok if here
        }

        static void Main(string[] args)
        {
            Whois a = new Whois(); // Setup a new instance
            int argumentLength;
            int minimumArgumentsAllowed = 1;
            int maximumArgumentsAllowed = 3;
            string response;
            string reply;

            // Validate console arguments been passed in
            argumentLength = args.GetLength(0);
            if ((argumentLength < minimumArgumentsAllowed) ||
                (argumentLength > maximumArgumentsAllowed)) // Too few or too many arguments
            {
                Console.WriteLine("You have specified an incorrect number of arguments.");
                Console.WriteLine("Try whereis.exe <server ip/name><space><name>");
                Console.WriteLine("or");
                Console.WriteLine("whereis.exe <server ip/name><space><name><space><location>");
                Console.ReadLine(); // Don't exit until user has hit Enter
            }
            else // Arguments number correct so populate the corresponding variables
            {
                if (argumentLength == 2) // name and server specified
                {
                    a.PopulateName(args);
                    a.PopulateServer(args);
                }
                if (argumentLength == 3) // name, server, and location specified
                {
                    a.PopulateName(args);
                    a.PopulateServer(args);
                    a.PopulateLocation(args);
                }
                if (args[0] == "form") // Chosen to use the gui
                {
                    Application.Run(new Form1());
                }
                else // using the console as the ui
                {
                    reply = a.ConnectAndReceive(args, out response);
                    if (reply != "") // Something went wrong
                    {
                        Console.WriteLine(reply);
                    }
                    else // Everything went ok
                    {
                        Console.WriteLine(response);
                    }
                    Console.WriteLine("Press 'Enter' to quit.");
                    Console.ReadLine(); // Don't quit unless the user has pressed a key
                }
                }
            }
        }
    }