using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Collections;
using Logging;

namespace whereisserver
{
    public interface IServer
    {
        /// <summary>
        /// Calls WaitForAndAcceptConnection and ReceiveDataAndDisconnect using the listener it receives
        /// <param name="listener">A listener</param>
        /// </summary>
        /// <returns>
        /// Nothing
        /// </returns>
        void StartListen(TcpListener listener);

        /// <summary>
        /// Waits for a connection and accepts it 
        /// </summary>
        /// <param name="listener">Reference to a TcpListener</param>
        /// <returns>
        /// The TcpClient who is connected
        /// </returns>
        TcpClient WaitForAndAcceptConnection(ref TcpListener listener);

        /// <summary>
        /// Receives data from the client
        /// <param name="listener">A reference to a listener</param>
        /// <param name="client">A reference to the connected client</param>
        /// <param name="myDatabase">A reference to the database</param>
        /// <returns>
        /// An empty string if successful, else an error message
        /// </returns>
        /// </summary>
        //string ReceiveData(ref TcpListener listener, ref TcpClient client, 
           // ref Database myDatabase);
string ReceiveData(ref TcpListener listener, ref TcpClient client);

        /// <summary>
        /// Parses the string from the client and decides whether it's a name or name and location
        /// <param="inString">String to parse</param>
        /// <param name="outName">The name</param>
        /// <param name="outLocation">The location</param>
        /// </summary>
        /// <returns>
        /// An int, 1 = name, 2 =  name and location, -1 = an error occurred
        /// </returns>
        int ParseString(string inString, out string outName, out string outLocation);

        /// <summary>
        /// Validates the string
        /// </summary>
        /// <param="inString">String to validate</param>
        /// <returns>
        /// An empty string if successful, else an error message
        /// </returns>
        string ValidateString(string inString);

    }

    public class Server : IServer
    {
        private Database myDatabase = new Database();
        private LoggingSystem log = new LoggingSystem();

        public Server()
        {
            TcpListener listener = new TcpListener(43);
            string reply = "";

            // Load the database first
            reply = myDatabase.LoadDatabase();
            if (reply != "") // Something went wrong
            {
                Console.WriteLine(reply);
            }
            listener.Start();
            StartListen(listener);
        }

        public void StartListen(TcpListener listener)
        {
            TcpClient client = null;
            bool running = true;
            string reply = "";

            Console.WriteLine("New thread open for someone to connect:");
            while (running)
            {
                try
                {
                    client = WaitForAndAcceptConnection(ref listener);
                    client = listener.AcceptTcpClient();
                    log.WriteToLog("NEW CLIENT CONNECTED", ".//log.txt",
                        "OK", client.Client.RemoteEndPoint.ToString());
                    Console.WriteLine(client.Client.RemoteEndPoint.ToString() +
                        " Connected");
                    // Now someone has connected create a new thread allowing someone else to connect
                    ThreadStart th = delegate { StartListen(listener); }; // delegate allows parameter
                    // passing
                    new Thread(th).Start();
                    //reply = ReceiveData(ref listener, ref client, ref myDatabase);
                    reply = ReceiveData(ref listener, ref client);
                    StreamWriter sw = new StreamWriter(client.GetStream());
                    sw.WriteLine(reply); // Send the reply back to the connected client
                    sw.Flush();
                    client.Close();
                }
                catch (System.Exception e)
                {
                    Console.WriteLine("ERROR: Check the log for details.");
                    log.WriteToLog(e.ToString(), ".//log.txt", "", "");
                }
            }
        }

        public TcpClient WaitForAndAcceptConnection(ref TcpListener listener)
        {
            TcpClient connectedClient = null; // So getstream becomes available
            bool connected = false;
            while (!connected)
            {
                connected = listener.Pending();
            }
            return connectedClient;
        }

        //public string ReceiveData(ref TcpListener listener, ref TcpClient connectedClient, 
           // ref Database myDatabase)
        public string ReceiveData(ref TcpListener listener, ref TcpClient connectedClient)
        {
            string error = "";
            string name = "";
            string location = "";
            int intError = 0;
            StreamReader sr = new StreamReader(connectedClient.GetStream());
            string response = "";
            bool boolResponse = false;

            try
            {
                response = sr.ReadLine(); // Get the input from the client
                Console.WriteLine("RECEIVED: " + connectedClient.Client.RemoteEndPoint.ToString()
                            + " " + "'" + response + "'");
                error = ValidateString(response); // Make sure the input is in the correct format
                if (error != "") // Something went wrong
                {
                    Console.WriteLine("SENT: " + connectedClient.Client.RemoteEndPoint.ToString() +
                            " " + "'" + error + "'");
                    return error;
                }
                intError = ParseString(response, out name, out location); // Check whether name/name+location
                if (intError == -1) // Something went wrong
                {
                    error = "ERROR: Use <name> or <name><space><location>";
                    Console.WriteLine("SENT: " + connectedClient.Client.RemoteEndPoint.ToString() +
                            " " + "'" + error + "'");
                    return error;
                }
                if (location == "") // No location specified, only name specified
                {
                    boolResponse = myDatabase.DoesPersonExist(name); // Makes logging easier
                    if (boolResponse)
                    {
                        error = "OK";
                        log.WriteToLog("GET " + name, ".//log.txt",
                            error, connectedClient.Client.RemoteEndPoint.ToString());
                        error = myDatabase.GetLocation(name); // For returning the location or "Error:..."
                        Console.WriteLine("SENT: " + connectedClient.Client.RemoteEndPoint.ToString() +
                            " " + "'" + error + "'");
                        return error;
                    }
                    else // Person doesn't exist
                    {
                        error = "UNKNOWN";
                        log.WriteToLog("GET " + name, ".//log.txt",
                            error, connectedClient.Client.RemoteEndPoint.ToString());
                        Console.WriteLine("SENT: " + connectedClient.Client.RemoteEndPoint.ToString() +
                            " " + "'" + error + "'");
                        return error;
                    }
                }
                else // name and location both specified
                {
                    error = myDatabase.ValidateName(name);
                    if (error != "") // Something went wrong
                    {
                        Console.WriteLine("SENT: " + connectedClient.Client.RemoteEndPoint.ToString() +
                            " " + "'" + error + "'"); ;
                        return error;
                    }
                    error = myDatabase.ValidateLocation(location);
                    if (error != "") // Something went wrong
                    {
                        Console.WriteLine("SENT: " + connectedClient.Client.RemoteEndPoint.ToString() +
                            " " + "'" + error + "'");
                        return error;
                    }
                    boolResponse = myDatabase.DoesPersonExist(name);
                    if (boolResponse) // Person exists so update their location
                    {
                        error = myDatabase.SetLocation(name, location);
                        error = "OK";
                        log.WriteToLog("SET " + name + " " + location, ".//log.txt",
                            error, connectedClient.Client.RemoteEndPoint.ToString());
                        Console.WriteLine("SENT: " + connectedClient.Client.RemoteEndPoint.ToString() +
                            " " + "'" + error + "'");
                    }
                    else // Person doesn't exist so add them and their location
                    {
                        myDatabase.AddPerson(name, location);
                        error = "OK";
                        log.WriteToLog("SET " + name + " " + location, ".//log.txt",
                            error, connectedClient.Client.RemoteEndPoint.ToString());
                        Console.WriteLine("SENT: " + connectedClient.Client.RemoteEndPoint.ToString() +
                            " " + "'" + error + "'");
                    }
                }
                return error;
            }
            catch (System.Exception e)
            {
                error = "Could not get a response from the client, check the logs for more details";
                log.WriteToLog("Could not get a response from the client: " + e.ToString(), ".//log.txt",
                            "", connectedClient.Client.RemoteEndPoint.ToString());
                Console.WriteLine(error);
                return error;
	
            }       
        }

        public int ParseString(string inString, out string outName, out string outLocation)
        {
            string name = "";
            string location = "";
            int lengthOfInString = inString.Length;
            int endPosition = 0;
            int counter = -1; // for keeping track of position within the string

            foreach (char c in inString)
            {
                counter++;
                if (c == ' ') // If there's a space then a name and a location has been given
                {
                    endPosition = lengthOfInString - counter; // Gives the endpoint for the name
                    name = inString.Remove(counter); // Remove the location part
                    int tempLength = 0;
                    tempLength = lengthOfInString - name.Length;
                    // Below counter+1 is there because otherwise the space would be counted
                    // Below tempLength-1 is there because otherwise outOfBounds (see line above)
                    location = inString.Substring((counter + 1), (tempLength - 1)); // Removes the name part
                    outName = name;
                    outLocation = location;
                    return 2; // Both name and location
                }
            }
            // If here then only a name has been specified
            outName = inString;
            outLocation = location;
            return 1; // Only a name
        }

        public string ValidateString(string inString)
        {
            // The string shouldn't have more than 1 space because max is
            // <name><space><location>
            int counter = 0; // Keep track of spaces
            string reply = "";

            foreach (char c in inString)
            {
                if (c == ' ')
                {
                    counter++;
                }
            }

            if (counter > 1)
            {
                reply = "ERROR: <name> or <name><space><location>.";
                return reply;
            }
            return reply; // If here everything went OK
        }
    }
}
