﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Net.Sockets;
using System.IO;

namespace whereis
{
    public partial class Form1 : Form
    {

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.Activate(); // Bring the form to the front
        }

        private void buttonSend_Click(object sender, EventArgs e)
        {
            Whois a = new Whois();
            string[] args = new string[3];
            string reply;
            string response;
            args[0] = textBoxServer.Text;
            args[1] = textBoxInputName.Text;
            args[2] = textBoxInputLocation.Text;

            reply = a.ConnectAndReceive(args, out response); // Send the arguments to the server
            if (reply != "") // Something went wrong
            {
                MessageBox.Show(reply, "Whereis", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
            else
            {
                richTextBoxResponse.Text = response; // Response from the server
            }
        }
    }
}