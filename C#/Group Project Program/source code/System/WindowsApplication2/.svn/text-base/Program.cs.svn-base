using System;
using System.Collections.Generic;
using System.Windows.Forms;
using SystemManagement;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace SystemUserInterface
{    
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            ISystemControl system;

            if (File.Exists("savedDatabase")) // if database exists on the system it is loaded
            {
                Stream myFileStream = File.OpenRead("savedDatabase");
                BinaryFormatter deserializer = new BinaryFormatter();
                system = (ISystemControl)(deserializer.Deserialize(myFileStream));
                myFileStream.Close();
            }
            else
            {
                system = new SystemControl();
            }       
            Application.Run(new MainMenu(system));

        }
    }
}