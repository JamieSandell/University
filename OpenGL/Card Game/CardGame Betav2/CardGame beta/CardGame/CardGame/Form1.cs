using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CardGame
{

    public partial class frontScreen : Form
    {
        public frontScreen()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {

            Player myPlayer = new Player(textBox1.Text);

            if (textBox1.Text.Length > 0)
            {
                if (myPlayer.validateName(textBox1.Text).Length == 0)
                {
                    CardGame.runGame(myPlayer);
                }

                else
                {
                    MessageBox.Show("Please Enter a Valid Name", "Invalid Name",
                        MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
            }

            else
            {
                MessageBox.Show("Please Enter a Valid Name", "Invalid Name",
                   MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }

        }

        private void startGameToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            Player myPlayer = new Player(textBox1.Text);

            if (textBox1.Text.Length > 0)
            {
                if (myPlayer.validateName(textBox1.Text).Length == 0)
                {
                    CardGame.runGame(myPlayer);
                }

                else
                {
                    MessageBox.Show("Please Enter a Valid Name", "Invalid Name",
                        MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
            }

            else
            {
                MessageBox.Show("Please Enter a Valid Name", "Invalid Name",
                   MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }

        private void frontScreen_Load(object sender, EventArgs e)
        {

        }


        private void exitToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            Environment.Exit(0);
        }
    }
}