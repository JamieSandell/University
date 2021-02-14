using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;

namespace Utilities
{
    public interface ISettings
    {
         /// <summary>
         /// Changes the apps config files
         /// <param name="key">The key whose value wants changing</param>
         /// <param name="NewValue">the new value of the key</param>
         /// <param name="applicationName">name of the app</param>
         /// </summary>
         void ChangeAppSettings(string key, string NewValue, string applicationName);

        /// <summary>
        /// Gets a field from the app settings of the program
        /// </summary>
        /// <param name="key">The key whose value wants retrieving</param>
        /// <param name="applicationName">name of the app</param>
        /// <returns>A key value</returns>
         string GetAppSettings(string key, string applicationName);
    }

    public class Settings:ISettings
    {
        public void ChangeAppSettings(string key, string NewValue, string applicationName)
        {
            string exePath = System.IO.Path.Combine(Environment.CurrentDirectory, applicationName);
            Configuration cfg;
            cfg = System.Configuration.ConfigurationManager.OpenExeConfiguration(exePath);

            KeyValueConfigurationElement setting = (KeyValueConfigurationElement)cfg.AppSettings.Settings[key];

            if ((setting != null))
            {
                setting.Value = NewValue;
                cfg.Save(); // Remember the config file is only loaded once
                                // so if access to the variable is needed after the config file has been loaded
                                // use variables that are kept up to date
            }
        }

        public string GetAppSettings(string key, string applicationName)
        {
            string exePath = System.IO.Path.Combine(Environment.CurrentDirectory, applicationName);
            Configuration cfg;
            cfg = System.Configuration.ConfigurationManager.OpenExeConfiguration(exePath);

            KeyValueConfigurationElement setting = (KeyValueConfigurationElement)cfg.AppSettings.Settings[key];

            if ((setting != null))
            {
                return setting.Value;
            }
            return "";
        }
    }
}
