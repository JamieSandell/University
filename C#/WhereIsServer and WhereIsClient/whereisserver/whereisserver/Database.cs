using System;
using System.IO;
using System.Net;
using System.Text;
using System.Runtime.Serialization.Formatters.Binary;
using System.Collections;

namespace whereisserver
{
    public interface IDatabase
    {
        /// <summary>
        /// Adds a person and corresponding location to the database calls ValidateName and
        /// ValidateLocation, calls SaveDatabase
        /// </summary>
        /// <param="inName">The person's name</param>
        /// <param="inLocation">The person's location</param>
        /// <returns>
        /// An empty string if successful, else an error message
        /// </returns>
        string AddPerson(string inName, string inLocation);

        /// <summary>
        /// Validates the person's name
        /// <param="inName">The person's name</param>
        /// </summary>
        /// <returns>
        /// An empty string if successful, else an error message
        /// </returns>
        string ValidateName(string inName);

        /// <summary>
        /// Validates the person's location
        /// <param="inLocation">The person's location</param>
        /// </summary>
        /// <returns>
        /// An empty string if successful, else an error message
        /// </returns>
        string ValidateLocation(string inLocation);

        /// <summary>
        /// Get the person's location
        /// <param="inName">The person's name to lookup to get their corresponding location</param>
        /// </summary>
        /// <returns>
        /// The person's location if successful else an error message
        /// </returns>
        string GetLocation(string inName);

        /// <summary>
        /// Set the person's location, calls SaveDatabase
        /// <param="inName">The person's name</param>
        /// <param="inLocation">The person's location</param>
        /// </summary>
        /// <returns>
        /// An empty string if successful, else an error message
        /// </returns>
        string SetLocation(string inName, string inLocation);

        /// <summary>
        /// Check to see whether the person already exists in the database
        /// <param="inName">Name to check</param>
        /// </summary>
        /// <returns>
        /// True if the person exists, else false
        /// </returns>
        bool DoesPersonExist(string inName);

        /// <summary>
        /// Loads the database from a file into a hashtable
        /// </summary>
        /// <returns>
        /// An empty string if everything went ok, else an error message
        /// </returns>
        string LoadDatabase();

        /// <summary>
        /// Saves the database from a hashtable into a file
        /// </summary>
        /// <returns>
        /// An empty string if everything went ok, else an error message
        /// </returns>
        string SaveDatabase();
    }

    public class Database : IDatabase
    {
        private Hashtable myDatabase = new Hashtable();

        public string AddPerson(string inName, string inLocation)
        {
            string reply;

            reply = ValidateName(inName);
            if (reply != "") // Something went wrong
            {
                return reply; // No point continuing
            }
            reply = ValidateLocation(inLocation);
            if (reply != "") // Something went wrong
            {
                return reply;
            }

            // Convert the name to uppercase to avoid further validation routines
            myDatabase.Add(inName.ToUpper(), inLocation);
            // Update the database
            reply = SaveDatabase();
            return reply;
        }

        public string ValidateName(string inName)
        {
            string reply = "";

            if (inName.StartsWith(" "))
            {
                reply = "ERROR: The name cannot start with a white space.";
                return reply;
            }
            if (inName == "")
            {
                reply = "ERROR: You must supply a name.";
                return reply;
            }
            return reply; // Everything went OK if here
        }

        public string ValidateLocation(string inLocation)
        {
            string reply = "";

            if(inLocation.StartsWith(" "))
            {
                reply = "ERROR: The location cannot start with a white space.";
                return reply;
            }
            if(inLocation == "")
            {
                reply = "ERROR: You must supply a location.";
                return reply;
            }
            return reply; // Everything went OK if here
        }

        public string GetLocation(string inName)
        {
            string reply = "";
            bool keyPresent = false;

            keyPresent = myDatabase.ContainsKey(inName.ToUpper());
            if (!keyPresent) // The person isn't in the database
            {
                reply = "ERROR: no entries found.";
                return reply;
            }
            inName = inName.ToUpper();
            reply = myDatabase[inName].ToString(); // Get the location corresponding to the name supplied
            return reply; // If here everything went OK
        }

        public string SetLocation(string inName, string inLocation)
        {
            string reply = "";
            inName = inName.ToUpper();
            myDatabase[inName] = inLocation; // Set/Update the location
            // Update the database
            reply = SaveDatabase();
            return reply;
        }

        public bool DoesPersonExist(string inName)
        {
            bool response = false;

            response = myDatabase.ContainsKey(inName.ToUpper());
            return response;
        }

        public string LoadDatabase()
        {
            string reply = "";
            FileInfo fileToCheck = new FileInfo(".//database.txt");
            // Does the database exist to load?
            if (!fileToCheck.Exists)
            {
                reply = "ERROR: The database could not be loaded because it doesn't exist," + 
                    " if this is the first time running the server this error can be ignored.";
            }
            else
            {
                try
                {
                    FileStream file = new FileStream(".//database.txt", FileMode.Open, FileAccess.Read);
                    BinaryFormatter bf = new BinaryFormatter();

                    myDatabase = (Hashtable)bf.Deserialize(file);
                    file.Close();
                }
                catch (System.Exception e)
                {
                    reply = "ERROR: Whilst loading the database this error occurred: " + e.ToString();
                }
            }
            return reply;
        }

        public string SaveDatabase()
        {
            string reply = "";

            try
            {
                FileStream file = new FileStream(".//database.txt", FileMode.OpenOrCreate,
                    FileAccess.Write);
                BinaryFormatter bf = new BinaryFormatter();

                bf.Serialize(file, myDatabase);
                file.Close();
            }
            catch (System.Exception e)
            {
                reply = "ERROR: Whilst saving the database this error occurred: " + e.ToString();
            }
            return reply;
        }
    }
}
