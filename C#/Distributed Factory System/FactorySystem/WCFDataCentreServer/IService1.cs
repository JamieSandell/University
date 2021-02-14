using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Collections;
using System.ServiceModel;
using System.Text;

namespace WCFDataCentreServer
{
    // NOTE: If you change the interface name "IService1" here, you must also update the reference to "IService1" in App.config.
    [ServiceContract]
    public interface IDataService
    {
        [OperationContract]
        /// <summary>
        /// Sends the weighing data to the server, 3 items in the arraylist.
        /// The first is the weighing station id,
        /// the second is the time and date of the transaction,
        /// the third is the weight,
        /// the fourth is the product name,
        /// and the fifth is the nominal weight
        /// Returns an empty string if successful, else an error message.
        /// </summary>
        string SendWeighingData(ArrayList inData);

        [OperationContract]
        /// <summary>
        /// Adds a weighing station if a slot is available.
        /// Returns an empty string if successful, else an error message.
        /// <param name="outWeighingStationID">The weighing station id to assign to</param>
        /// </summary>
        string AddWeighingStation(ref int outWeighingStationID);

        /// <summary>
        /// Gets the current amount of weighing stations (inactive and active)
        /// </summary>
        /// <returns>The amount of weighing stations</returns>
        [OperationContract]
        int GetAmountOfWeighingStations();

        /// <summary>
        /// Sets the amount of weighing stations available (active and inactive).
        /// </summary>
        /// <param name="inValue">The number of weighing stations to allow</param>
        /// <returns>An empty string if OK, else an error message</returns>
        [OperationContract]
        string SetAmountOfWeighingStations(int inValue);

        /// <summary>
        /// Gets the current amount of maximum weighing stations (active and inactive).
        /// </summary>
        /// <returns>The amount of maximum weighing stations</returns>
        [OperationContract]
        int GetAmountOfMaximumWeighingStations();

        /// <summary>
        /// Sets the amount of maximum weighing stations available (active and inactive).
        /// </summary>
        /// <param name="inValue">The number of maximum weighing stations to allow</param>
        /// <returns>An empty string if OK, else an error message</returns>
        [OperationContract]
        string SetAmountOfMaximumWeighingStations(int inValue);

        /// <summary>
        /// Populates the variables, acts as a constructor because a method can't be called from within
        /// a constructor in WCF.
        /// </summary>
        [OperationContract]
        void PopulateVariables();

        /// <summary>
        /// Gets the last ten items sent by each weighing station
        /// </summary>
        /// <returns></returns>
        [OperationContract]
        ArrayList GetLastTenItems();

        /// <summary>
        /// Gets all underweight items for all weighing stations in the last 24 hours
        /// </summary>
        /// <returns></returns>
        [OperationContract]
        ArrayList GetUnderweightItems();

        // TODO: Add your service operations here
    }
}
