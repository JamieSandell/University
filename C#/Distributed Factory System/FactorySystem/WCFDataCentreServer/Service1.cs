using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Configuration;
using System.Text;
using System.Threading;
using Utilities;
using System.Windows.Forms;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;


namespace WCFDataCentreServer
{
    //[ServiceBehavior(InstanceContextMode = InstanceContextMode.Single,
    //             ConcurrencyMode = ConcurrencyMode.Multiple)]
    // NOTE: If you change the class name "Service1" here, you must also update the reference to "Service1" in App.config.
    //[DataContract]
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single,
                 ConcurrencyMode = ConcurrencyMode.Multiple)]
    [DataContract]
    public class DataService : IDataService
    {
        private int numberOfWeighingStations;
        private int numberOfMaximumWeighingStations;
        private Settings mySettings = new Settings();
        private List<ArrayList> listWeighingStation = new List<ArrayList>();
        private object writing = new object();
        private object reading = new object();
        private ArrayList lastTenList = new ArrayList();
        private ArrayList underweightList = new ArrayList();
        private ReaderWriterLock rwl = new ReaderWriterLock();

        public DataService()
        {
        }

        public void PopulateVariables()
        {
            ArrayList tempList = new ArrayList();
            numberOfWeighingStations = Int32.Parse(mySettings.GetAppSettings("NumberOfWeighingStations", "DataCentreServer.vshost.exe"));
            numberOfMaximumWeighingStations = Int32.Parse(mySettings.GetAppSettings("NumberOfWeighingStationsAllowed", "DataCentreServer.vshost.exe"));
            numberOfWeighingStations = Int32.Parse(mySettings.GetAppSettings("NumberOfWeighingStations", "DataCentreServer.exe"));
            numberOfMaximumWeighingStations = Int32.Parse(mySettings.GetAppSettings("NumberOfWeighingStationsAllowed", "DataCentreServer.exe"));
            for (int i = 0; i < numberOfMaximumWeighingStations; i++)
            {
                tempList = new ArrayList();
                tempList.Add(i + 1);
                listWeighingStation.Add(tempList); // add the weighingstation to the weighingstation list
            }
        }

        public void CalculateLastTenItems()
        {
            List<ArrayList> copyOfWeighingList = new List<ArrayList>(listWeighingStation);

            lastTenList.Clear();
            ArrayList tempArrayList = new ArrayList();
            List<ArrayList> tempList = new List<ArrayList>(); // get arraylists of the current weighing stations
            ArrayList weighingID = new ArrayList();
            ArrayList tempArrayList2 = new ArrayList();
            ArrayList sArrayList = new ArrayList();
            for (int i = 0; i < copyOfWeighingList.Count; i++)
            {
                tempArrayList2 = new ArrayList(); // stop values been overwritten in the wrong places
                tempList.Add(copyOfWeighingList[i]); // get all of the weighing station arraylists
                tempList[i] = (ArrayList)copyOfWeighingList[i].Clone();
                tempList[i].RemoveAt(0); // Remove the non-string id value
                tempList[i].Reverse(); // flip the list because the last 10 results are wanted
                if (tempList[i].Count < 10)
                {
                    tempArrayList = tempList[i].GetRange(0, tempList[i].Count);
                }
                else
                {
                    tempArrayList = tempList[i].GetRange(0, 10);
                }
                foreach (ArrayList al in tempArrayList)
                {
                    foreach (string s in al)
                    {
                        tempArrayList2.Add(s); // Convert them to strings so we're not sending arraylists of
                        // arraylists
                    }
                }
                //lastTenList.Add(tempArrayList2);
                lastTenList.Insert(i, tempArrayList2);
            }
        }

        public void CalculateUnderweightItems()
        {
            List<ArrayList> copyOfWeighingList = new List<ArrayList>(listWeighingStation);

            underweightList.Clear();
            ArrayList tempArrayList = new ArrayList();
            List<ArrayList> tempList = new List<ArrayList>(); // get arraylists of the current weighing stations
            ArrayList weighingID = new ArrayList();
            ArrayList tempArrayList2 = new ArrayList();
            ArrayList sArrayList = new ArrayList();

            for (int i = 0; i < copyOfWeighingList.Count; i++)
            {
                tempArrayList2 = new ArrayList(); // stop values been overwritten in the wrong places
                tempList.Add(copyOfWeighingList[i]); // get all of the weighing station arraylists
                tempList[i] = (ArrayList)copyOfWeighingList[i].Clone();
                tempList[i].RemoveAt(0); // Remove the non-string id value
                
                tempArrayList = tempList[i].GetRange(0, tempList[i].Count); // get all of the elements

                foreach (ArrayList al in tempArrayList)
                {
                    //foreach (string s in al)
                    //{
                    //    if (counter == 1) // want the 2nd element, index starts at 0
                    //    {
                    //        DateTime converted = DateTime.Parse(s);
                    //        DateTime twentyFourHoursAgo = converted.AddHours(-24);
                    //        tempArrayList2.Add(s); // Convert them to strings so we're not sending arraylists of
                    //        // arraylists
                    //    }
                    //    if (counter > 4) // 5 elements starting at index 0
                    //    {
                    //        counter = 0;
                    //    }
                    //    counter++;
                    //}

                    for (int j = 0; j < al.Count; j++)
                    {
                        if (j == 1) // want the 2nd element, index starts at 0
                        {
                            DateTime converted = DateTime.Parse(al[j].ToString());
                            DateTime today = DateTime.Now;
                            DateTime twentyFourHoursAgo = today.AddHours(-24);

                            string[] sArray = (string [])al.ToArray(typeof(string));

                            if ((converted<=today)&&(converted>=twentyFourHoursAgo))
                            {
                                if (Convert.ToDouble(sArray[j + 1]) < Convert.ToDouble(sArray[j + 3])) // weight < nominalWeight
                                {
                                    for (int k = 0; k < al.Count; k++)
                                    {
                                        // add the underweight bag to the arraylist
                                        tempArrayList2.Add(al[k]);
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
                //lastTenList.Add(tempArrayList2);
                underweightList.Insert(i, tempArrayList2);
            }
        }

        public string SendWeighingData(ArrayList inData)
        {
            try
            {
                rwl.AcquireWriterLock(1000);
                int weighingStationID = Int32.Parse(inData[0].ToString());
                 //Add the data
                //listWeighingStation.Capacity = 1000;
                listWeighingStation[weighingStationID-1].Add(inData);
            }
            catch (System.Exception e)
            {
                MessageBox.Show(e.ToString());
            }
            finally
            {
                rwl.ReleaseWriterLock();
            }

            return ""; // Everything went OK
        }

        public string AddWeighingStation(ref int outWeighingStation)
        {
            string reply = "";
            rwl.AcquireWriterLock(1000);

                if (numberOfWeighingStations < numberOfMaximumWeighingStations)
                {
                    numberOfWeighingStations++;
                    SetAmountOfWeighingStations(numberOfWeighingStations);
                    outWeighingStation = numberOfWeighingStations;
                    ArrayList tempList = new ArrayList();
                    tempList.Add(numberOfWeighingStations);
                }
                else
                {
                    reply = "Number of weighing stations is equal to or greater than the number of maximum weighing"
                        + " stations allowed.";
                }
                rwl.ReleaseWriterLock();
            return reply;
        }

        public int GetAmountOfWeighingStations()
        {
            return numberOfWeighingStations;
        }

        public string SetAmountOfWeighingStations(int inValue)
        {
            string reply = "";
            rwl.AcquireWriterLock(1000);
                if (inValue < 0)
                {
                    reply = "You cannot have less than zero weighing stations.";
                }
                else
                {
                    numberOfWeighingStations = inValue;
                    mySettings.ChangeAppSettings("NumberOfWeighingStations", numberOfWeighingStations.ToString(), "DataCentreServer.vshost.exe");
                    mySettings.ChangeAppSettings("NumberOfWeighingStations", numberOfWeighingStations.ToString(), "DataCentreServer.exe");
                }
                rwl.ReleaseWriterLock();
            return reply;
        }

        public int GetAmountOfMaximumWeighingStations()
        {
            return numberOfMaximumWeighingStations;
        }

        public string SetAmountOfMaximumWeighingStations(int inValue)
        {
            string reply = "";
            rwl.AcquireWriterLock(1000);
                if (inValue < 0)
                {
                    reply = "You cannot have less than zero maximum weighing station.";
                }
                else
                {
                    numberOfMaximumWeighingStations = inValue;
                    mySettings.ChangeAppSettings("NumberOfWeighingStationsAllowed", numberOfMaximumWeighingStations.ToString(), "DataCentreServer.vshost.exe");
                    mySettings.ChangeAppSettings("NumberOfWeighingStationsAllowed", numberOfMaximumWeighingStations.ToString(), "DataCentreServer.exe");
                }
                rwl.ReleaseWriterLock();
            return reply;
        }

        public ArrayList GetLastTenItems()
        {
            try
            {
                rwl.AcquireReaderLock(1000);
                CalculateLastTenItems();
            }
            catch (System.Exception e)
            {
                MessageBox.Show(e.ToString());
            }
            finally
            {
                rwl.ReleaseReaderLock();
            }
            
            
            return lastTenList;
        }

        public ArrayList GetUnderweightItems()
        {
            try
            {
                rwl.AcquireReaderLock(1000);
                CalculateUnderweightItems();
            }
            catch (System.Exception e)
            {
                MessageBox.Show(e.ToString());
            }
            finally
            {
                rwl.ReleaseReaderLock();
            }


            return underweightList;
        }
    }
}
