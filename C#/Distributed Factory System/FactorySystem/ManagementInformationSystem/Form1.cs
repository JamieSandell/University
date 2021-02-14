using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using WCFDataCentreServer;
using Utilities;

namespace ManagementInformationSystem
{
    public partial class Form1 : Form
    {
        private ArrayList lastTen =  new ArrayList();
        private ArrayList underWeight = new ArrayList();
        private ServiceReference1.DataServiceClient data = new ManagementInformationSystem.ServiceReference1.DataServiceClient();

        public Form1()
        {
            InitializeComponent();
        }

        private void buttonGenerateLastTen_Click(object sender, EventArgs e)
        {
            richTextBoxLastTen.Text = "";
            lastTen = data.GetLastTenItems();
            ArrayList formatting = new ArrayList();
            formatting.Add("Weighing Station : ");
            formatting.Add("Date and Time : ");
            formatting.Add("Weight : ");
            formatting.Add("Product Name : ");
            formatting.Add("Nominal Weight : ");

            int formattingCounter = 0;
            richTextBoxLastTen.SelectionColor = Color.Black;

            foreach (ArrayList al in lastTen)
            {
                foreach (string s in al)
                {
                    if (formattingCounter > 4)
                    {
                        formattingCounter = 0;
                    }
                    richTextBoxLastTen.Text += formatting[formattingCounter] + s;
                    richTextBoxLastTen.Text += '\n';
                    formattingCounter++;
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void buttonGenerateUnderweight_Click(object sender, EventArgs e)
        {
            richTextBoxUnderweight.Text = "";
            underWeight = data.GetUnderweightItems();
            ArrayList formatting = new ArrayList();
            formatting.Add("Weighing Station : ");
            formatting.Add("Date and Time : ");
            formatting.Add("Weight : ");
            formatting.Add("Product Name : ");
            formatting.Add("Nominal Weight : ");

            int formattingCounter = 0;
            richTextBoxUnderweight.SelectionColor = Color.Black;

            foreach (ArrayList al in underWeight)
            {
                foreach (string s in al)
                {
                    if (formattingCounter > 4)
                    {
                        formattingCounter = 0;
                    }
                    richTextBoxUnderweight.Text += formatting[formattingCounter] + s;
                    richTextBoxUnderweight.Text += '\n';
                    formattingCounter++;
                }
            }
        }

    }
}
