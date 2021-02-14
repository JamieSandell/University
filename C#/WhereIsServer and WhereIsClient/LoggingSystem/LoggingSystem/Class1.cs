using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace Logging
{
    public interface ILoggingSystem
    {
        /// <Summary>
        /// Writes to a log file
        /// <param name="message">The message to write to the log file</param>
        /// <param name="file">The file to write to</param>
        /// <param name="status">The status, e.g. SET</param>
        /// <param name="server">The server that is sending or receiving</param>
        /// </Summary>
        /// <Returns>
        /// An empty string if successful, else an error message
        /// </Returns>
        string WriteToLog(string message, string file, string status, string server);
    }

    public class LoggingSystem : ILoggingSystem
    {
        public string WriteToLog(string message, string fileName, string status, string server)
        {
            string reply = "";
            try
            {
                FileInfo file = new FileInfo(fileName);
                DateTime date = DateTime.Now; // Get the current date and time
                string format = date.ToString("dd/MMM/yyyy:hh:mm:ss K"); // format the current date/time
                string formattedMessage = server + " - - [" + format + "]" + " \"" + message + "\""
                    + " " + status; // combine the date/time format with the actual message and format
                // that

                if (!file.Exists) // If the file doesn't exist, create it, else append
                {
                    using (StreamWriter sw = file.CreateText())
                    {
                        sw.WriteLine(formattedMessage);
                    }
                }
                else
                {
                    using (StreamWriter sw = file.AppendText())
                    {
                        sw.WriteLine(formattedMessage);
                    }
                }
            }
            catch (System.Exception e)
            {
                //reply = Convert.ToString(e); // Won't be very useful to the user, and can't write the
                // error to a log file because this occurred when trying to write to a file.
                reply = "There was a problem whilst trying to write to the log file\nplease make sure " + 
                    "the file: " + fileName + " is not already open";
                return reply;
            }
            return reply; // If here then everything went OK
        }
    }
}
