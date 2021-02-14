using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Configuration;
using System.Web;
using WCFDataCentreServer;
using Utilities;

namespace DataCentreServer
{
    class Program
    {
        static void Main(string[] args)
        {
            ServiceReference1.DataServiceClient data = new DataCentreServer.ServiceReference1.DataServiceClient();
            ServiceHost myHost = new ServiceHost(typeof(DataService));
            Settings mySettings = new Settings();

#if DEBUG
            myHost.AddServiceEndpoint(typeof(IDataService),
                new WSHttpBinding(), mySettings.GetAppSettings("ServerAddress", "DataCentreServer.vshost.exe"));
#else
            myHost.AddServiceEndpoint(typeof(IDataService),
                new BasicHttpBinding(), mySettings.GetAppSettings("ServerAddress", "DataCentreServer.exe"));
#endif
            myHost.Open();
            Console.WriteLine("DataService running...");
            data.PopulateVariables();
            //data.ChangeAppSettings("NumberOfWeighingStations", "0");
            Console.ReadLine();
            myHost.Close();
        }
    }
}
