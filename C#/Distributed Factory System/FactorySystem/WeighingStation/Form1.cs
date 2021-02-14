using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Configuration;
using Utilities;
using _08346ACW;

namespace WeighingStation
{
    public partial class FormWeighingStation : Form
    {
        private double nominalWeight;
        private bool bResult; // used for method calls
        private bool errorFlag; // Used for determining if error messages need to be shown
        private string messageBoxCaption = "Weighing Station";
        private int weighingStationID = 0;
        private MyWeighingDataSource myWeighingDataSource = new MyWeighingDataSource();
        private Validation myValidater;
        private Settings mySettings = new Settings();
        private ServiceReference1.DataServiceClient data = new WeighingStation.ServiceReference1.DataServiceClient();

        public FormWeighingStation()
        {
            InitializeComponent();

            CheckWeighingStationID();

            myValidater = new Validation();
            myWeighingDataSource.CycleTime = 1;
        }

        // If the weighing station id is 0 (not been set) then try and assign a new one
        private void CheckWeighingStationID()
        {
            weighingStationID = Int32.Parse(mySettings.GetAppSettings("WeighingStationID", "WeighingStation.vshost.exe"));
            int weighingStationID2 = Int32.Parse(mySettings.GetAppSettings("WeighingStationID", "WeighingStation.exe"));
            if (weighingStationID+weighingStationID2 == 0)
            {
                string reply = AssignWeighingStationID();
                if (reply=="")
                {
                    // Update the config file
                    mySettings.ChangeAppSettings("WeighingStationID", weighingStationID.ToString(), "WeighingStation.vshost.exe");
                mySettings.ChangeAppSettings("WeighingStationID", weighingStationID.ToString(), "WeighingStation.exe");
                }
            }
            else
            {
                weighingStationID = Int32.Parse(mySettings.GetAppSettings("WeighingStationID", "WeighingStation.vshost.exe"));
                weighingStationID = Int32.Parse(mySettings.GetAppSettings("WeighingStationID", "WeighingStation.exe"));
            }
            // Update the form to display the ID
            this.Text = this.Text + " | ID : " + weighingStationID.ToString();
        }

        // Check with the server to see if an id can be assigned for the weighing station
        private string AssignWeighingStationID()
        {
            string reply = "";
            try
            {
                reply = data.AddWeighingStation(ref weighingStationID);
            }
            catch (Exception e)
            {
                MessageBox.Show("The server could not be contacted.\n"
                    + "The Weighing Station could not be assigned a number.", messageBoxCaption,
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                MessageBox.Show(e.ToString());
            }
            finally
            {
                if (reply!="")
                {
                    MessageBox.Show(reply, messageBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            if (reply != "")
            {
                return reply;
            }
            else
            {
                return ""; // Everything went OK
            }
        }

        private void buttonSet_Click(object sender, EventArgs e)
        {
            // Validate the Nominal Weight field
            bResult = myValidater.IsNumber(textBoxNominalWeight.Text, out nominalWeight);
            SetErrorFlagIfNeeded(bResult);
            if (!bResult) // If something went wrong inform the user
            {
                ChangeLabelText(labelNominalWeightError, "That was not a valid number.");
            }
            else
            {
                // Reset the error message
                ChangeLabelText(labelNominalWeightError, "");
                // Change the current value textboxes
                textBoxNominalWeightCurrentValue.Text = textBoxNominalWeight.Text;
            }
            // Validate the ProductName Name field
            bResult = myValidater.IsValidString(textBoxProductName.Text);
            SetErrorFlagIfNeeded(bResult);
            if (!bResult) // If something went wrong inform the user
            {
                ChangeLabelText(labelProductNameError, "The 'Product Name' cannot be\n blank and must not begin with\n a blank space.");
            }
            else
            {
                // Reset the error message
                ChangeLabelText(labelProductNameError, "");
                // Change the current value textboxes
                textBoxProductNameCurrentValue.Text = textBoxProductName.Text;
            }
            // If the error flag is true, show the error message
            if (errorFlag)
            {
                MessageBox.Show("Some fields are invalid, please correct them", messageBoxCaption,
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                errorFlag = false;
            }
            else // No error has been raised so send the information to the server
            {
                string reply = "";
                // Make sure an ID is assigned for the weighing station
                if (weighingStationID<=0)
                {
                    reply = AssignWeighingStationID();
                }
                if (reply=="")
                {
                    // Tell the user that everything went fine and that information
                    // will be sent to the server
                    MessageBox.Show("Product Name and Nominal weight set correctly.\nIncoming weights will now be sent to the server.", messageBoxCaption,
                        MessageBoxButtons.OK, MessageBoxIcon.Information);
                    // set the product name, nominal weight, and weighing station id
                    myWeighingDataSource.ProductName = textBoxProductName.Text;
                    myWeighingDataSource.NominalWeight = Convert.ToDouble(textBoxNominalWeight.Text);
                    myWeighingDataSource.WeighingStationID = weighingStationID;
                    // Start the timer
                    myWeighingDataSource.Start();
                }
            }

        }

        private void SetErrorFlagIfNeeded(bool inFlag)
        {
            if (!inFlag)
            {
                // Set the error flag
                errorFlag = true;
            }
        }

        private void ChangeLabelText(Label inLabel, string inString)
        {
            inLabel.Text = inString;
        }
    }

    public class MyWeighingDataSource : WeighingDataSource
    {
        private ServiceReference1.DataServiceClient data = new WeighingStation.ServiceReference1.DataServiceClient();
        private ArrayList dataToSend = new ArrayList();

        private string m_productName;
        public string ProductName
        {
            set
            {
                m_productName = value;
            }
        }
        private int m_weighingStationID;
        public int WeighingStationID
        {
            set
            {
                m_weighingStationID = value;
            }
        }
        private double m_nominalWeight;
        public double NominalWeight
        {
            set
            {
                m_nominalWeight = value;
            }
        }

        protected override void OnWeightDataEvent(WeightDataEventArgs e)
        {
            try
            {
                //data = new WeighingStation.ServiceReference1.DataServiceClient();
                dataToSend.Clear();
                dataToSend.Add(m_weighingStationID.ToString());
                dataToSend.Add(DateTime.Now.ToString());
                dataToSend.Add(e.Weight.ToString());
                dataToSend.Add(m_productName.ToString());
                dataToSend.Add(m_nominalWeight.ToString());
                //data.Open();
                data.SendWeighingData(dataToSend);
            }
            catch (System.Exception j)
            {
                MessageBox.Show(j.ToString());
            }
        }
    }
}
