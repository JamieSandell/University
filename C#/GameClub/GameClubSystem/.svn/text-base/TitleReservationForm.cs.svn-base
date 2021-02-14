using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using GameClubControlClasses;

namespace GameClubWindowsGUI
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class TitleReservationForm : System.Windows.Forms.Form
	{
		private System.Windows.Forms.Label memberNameLabel;
		private System.Windows.Forms.TextBox memberNameTextBox;
		private System.Windows.Forms.TextBox gameNameTextBox;
		private System.Windows.Forms.Button findNameButton;
		private System.Windows.Forms.Button findGameButton;
		private System.Windows.Forms.Label gameNameLabel;
		private System.Windows.Forms.Button reserveButton;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		private ITitleReservationMessages reservationControl;

		public TitleReservationForm( ITitleReservationMessages inReservationControl )
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			reservationControl = inReservationControl ;
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.memberNameLabel = new System.Windows.Forms.Label();
			this.memberNameTextBox = new System.Windows.Forms.TextBox();
			this.gameNameTextBox = new System.Windows.Forms.TextBox();
			this.findNameButton = new System.Windows.Forms.Button();
			this.findGameButton = new System.Windows.Forms.Button();
			this.gameNameLabel = new System.Windows.Forms.Label();
			this.reserveButton = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// memberNameLabel
			// 
			this.memberNameLabel.Location = new System.Drawing.Point(16, 32);
			this.memberNameLabel.Name = "memberNameLabel";
			this.memberNameLabel.Size = new System.Drawing.Size(112, 16);
			this.memberNameLabel.TabIndex = 0;
			this.memberNameLabel.Text = "Club Member Name";
			// 
			// memberNameTextBox
			// 
			this.memberNameTextBox.Location = new System.Drawing.Point(128, 32);
			this.memberNameTextBox.Name = "memberNameTextBox";
			this.memberNameTextBox.Size = new System.Drawing.Size(136, 20);
			this.memberNameTextBox.TabIndex = 2;
			this.memberNameTextBox.Text = "";
			this.memberNameTextBox.TextChanged += new System.EventHandler(this.memberNameTextBox_TextChanged);
			// 
			// gameNameTextBox
			// 
			this.gameNameTextBox.Location = new System.Drawing.Point(128, 64);
			this.gameNameTextBox.Name = "gameNameTextBox";
			this.gameNameTextBox.Size = new System.Drawing.Size(136, 20);
			this.gameNameTextBox.TabIndex = 3;
			this.gameNameTextBox.Text = "";
			this.gameNameTextBox.TextChanged += new System.EventHandler(this.gameNameTextBox_TextChanged);
			// 
			// findNameButton
			// 
			this.findNameButton.Location = new System.Drawing.Point(288, 32);
			this.findNameButton.Name = "findNameButton";
			this.findNameButton.Size = new System.Drawing.Size(96, 24);
			this.findNameButton.TabIndex = 4;
			this.findNameButton.Text = "Find";
			this.findNameButton.Click += new System.EventHandler(this.findNameButton_Click);
			// 
			// findGameButton
			// 
			this.findGameButton.Location = new System.Drawing.Point(288, 64);
			this.findGameButton.Name = "findGameButton";
			this.findGameButton.Size = new System.Drawing.Size(96, 24);
			this.findGameButton.TabIndex = 5;
			this.findGameButton.Text = "Find";
			this.findGameButton.Click += new System.EventHandler(this.findGameButton_Click);
			// 
			// gameNameLabel
			// 
			this.gameNameLabel.Location = new System.Drawing.Point(16, 64);
			this.gameNameLabel.Name = "gameNameLabel";
			this.gameNameLabel.Size = new System.Drawing.Size(112, 16);
			this.gameNameLabel.TabIndex = 1;
			this.gameNameLabel.Text = "Game Name";
			// 
			// reserveButton
			// 
			this.reserveButton.Enabled = false;
			this.reserveButton.Location = new System.Drawing.Point(16, 104);
			this.reserveButton.Name = "reserveButton";
			this.reserveButton.Size = new System.Drawing.Size(376, 32);
			this.reserveButton.TabIndex = 6;
			this.reserveButton.Text = "Reserve";
			this.reserveButton.Click += new System.EventHandler(this.reserveButton_Click);
			// 
			// ReservationForm
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(408, 142);
			this.Controls.Add(this.reserveButton);
			this.Controls.Add(this.findGameButton);
			this.Controls.Add(this.findNameButton);
			this.Controls.Add(this.gameNameTextBox);
			this.Controls.Add(this.memberNameTextBox);
			this.Controls.Add(this.gameNameLabel);
			this.Controls.Add(this.memberNameLabel);
			this.Name = "ReservationForm";
			this.Text = "Reservation Form";
			this.ResumeLayout(false);

		}
		#endregion

		
		private void findNameButton_Click(object sender, System.EventArgs e)
		{
			if ( reservationControl.SelectMemberByName ( memberNameTextBox.Text ) )
			{
				memberNameTextBox.ForeColor = Color.Green;
				if ( gameNameTextBox.ForeColor == Color.Green ) 
				{
					reserveButton.Enabled = true;
				}
			}
		}

		private void findGameButton_Click(object sender, System.EventArgs e)
		{
			if ( reservationControl.SelectTitleByName ( gameNameTextBox.Text ) )
			{
				gameNameTextBox.ForeColor = Color.Green;
				if ( memberNameTextBox.ForeColor == Color.Green ) 
				{
					reserveButton.Enabled = true;
				}
			}
		}

		private void memberNameTextBox_TextChanged(object sender, System.EventArgs e)
		{
			memberNameTextBox.ForeColor = Color.Red;
			reserveButton.Enabled = false;
		}

		private void gameNameTextBox_TextChanged(object sender, System.EventArgs e)
		{
			gameNameTextBox.ForeColor = Color.Red;
			reserveButton.Enabled = false;
		}

		private void reserveButton_Click(object sender, System.EventArgs e)
		{
			if ( !reservationControl.ReserveTitle () ) 
			{
				MessageBox.Show ( "Reservation not created", "Make Reservation");
				return;
			}
			Close();
		}
	}
}
