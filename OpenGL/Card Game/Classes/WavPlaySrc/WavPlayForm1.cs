//Bill Nolde BillCo Systes 2003
//   billnolde@ieee.org

using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Runtime.InteropServices;


namespace WavPlayTest
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	
	public class WAVSounds
	{
		[DllImport("WinMM.dll")]
		public static extern bool  PlaySound(byte[]wfname, int fuSound);

		//  flag values for SoundFlags  argument on PlaySound
		public int SND_SYNC            = 0x0000;  // play synchronously (default) 
		public int SND_ASYNC           = 0x0001;  // play asynchronously 
		public int SND_NODEFAULT       = 0x0002;  // silence (!default) if sound not found 
		public int SND_MEMORY          = 0x0004;  // pszSound points to a memory file 
		public int SND_LOOP            = 0x0008;  // loop the sound until next sndPlaySound 
		public int SND_NOSTOP          = 0x0010;  // don't stop any currently playing sound 

		public int SND_NOWAIT      = 0x00002000; // don't wait if the driver is busy 
		public int SND_ALIAS       = 0x00010000; // name is a registry alias 
		public int SND_ALIAS_ID    = 0x00110000; // alias is a predefined ID 
		public int SND_FILENAME    = 0x00020000; // name is file name 
		public int SND_RESOURCE    = 0x00040004; // name is resource name or atom 
		public int SND_PURGE           = 0x0040;  // purge non-static events for task 
		public int SND_APPLICATION     = 0x0080;  // look for application specific association 

//--------------------------------------------------------------------
public WAVSounds()
{
}
//-------------------------------------------------------------------
~WAVSounds()
{
}
//-------------------------------------------------------------------
public void Play(string wfname,int SoundFlags)
{
	byte[] bname = new Byte[256];		//Max path length
	bname = System.Text.Encoding.ASCII.GetBytes(wfname);
	PlaySound(bname,SoundFlags);
}
//--------------------------------------------------------------------
public void StopPlay()
{
	PlaySound(null,SND_PURGE);
}
//----------------------------------------------------------------------
}   //End WAVSounds class
//----------------------------------------------------------------------


//----------------------------------------------------------------------	
	public class Form1 : System.Windows.Forms.Form
	{
		[DllImport("user32.dll")]
		public static extern int   MessageBox(int hWnd, String text, 
			String caption, uint type);

		private System.Windows.Forms.Button FindFileButton;
		private System.Windows.Forms.OpenFileDialog openFileDialog1;
		private System.Windows.Forms.TextBox m_wav_file;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Button ExitButton;
		private System.Windows.Forms.Button PlayButton;
		private System.Windows.Forms.Button AboutButton;
		private System.Windows.Forms.Button StopButton;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public Form1()
		{
	
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			openFileDialog1.Title = "Select a Wave Sound File";
			openFileDialog1.Filter = "Wav Files(*.wav)|*.wav| All Files(*.*)|*.*";
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
			this.ExitButton = new System.Windows.Forms.Button();
			this.FindFileButton = new System.Windows.Forms.Button();
			this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
			this.m_wav_file = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.PlayButton = new System.Windows.Forms.Button();
			this.AboutButton = new System.Windows.Forms.Button();
			this.StopButton = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// ExitButton
			// 
			this.ExitButton.Location = new System.Drawing.Point(387, 30);
			this.ExitButton.Name = "ExitButton";
			this.ExitButton.Size = new System.Drawing.Size(69, 22);
			this.ExitButton.TabIndex = 0;
			this.ExitButton.Text = "Exit";
			this.ExitButton.Click += new System.EventHandler(this.ExitButtonClick);
			// 
			// FindFileButton
			// 
			this.FindFileButton.Location = new System.Drawing.Point(190, 114);
			this.FindFileButton.Name = "FindFileButton";
			this.FindFileButton.Size = new System.Drawing.Size(68, 21);
			this.FindFileButton.TabIndex = 1;
			this.FindFileButton.Text = "Find File";
			this.FindFileButton.Click += new System.EventHandler(this.FindFileButton_Click);
			// 
			// m_wav_file
			// 
			this.m_wav_file.Location = new System.Drawing.Point(95, 68);
			this.m_wav_file.Name = "m_wav_file";
			this.m_wav_file.Size = new System.Drawing.Size(256, 20);
			this.m_wav_file.TabIndex = 2;
			this.m_wav_file.Text = "..\\..\\hi.wav";
			this.m_wav_file.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(183, 38);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(91, 22);
			this.label1.TabIndex = 3;
			this.label1.Text = "Wav Filename";
			// 
			// PlayButton
			// 
			this.PlayButton.Location = new System.Drawing.Point(387, 70);
			this.PlayButton.Name = "PlayButton";
			this.PlayButton.Size = new System.Drawing.Size(69, 22);
			this.PlayButton.TabIndex = 4;
			this.PlayButton.Text = "Play";
			this.PlayButton.Click += new System.EventHandler(this.OnPlayButtonClick);
			// 
			// AboutButton
			// 
			this.AboutButton.Location = new System.Drawing.Point(387, 150);
			this.AboutButton.Name = "AboutButton";
			this.AboutButton.Size = new System.Drawing.Size(69, 21);
			this.AboutButton.TabIndex = 8;
			this.AboutButton.Text = "About";
			this.AboutButton.Click += new System.EventHandler(this.AboutButtonClick);
			// 
			// StopButton
			// 
			this.StopButton.Location = new System.Drawing.Point(387, 110);
			this.StopButton.Name = "StopButton";
			this.StopButton.Size = new System.Drawing.Size(69, 22);
			this.StopButton.TabIndex = 7;
			this.StopButton.Text = "Stop Play";
			this.StopButton.Click += new System.EventHandler(this.StopButton_Click);
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(520, 218);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.AboutButton,
																		  this.StopButton,
																		  this.PlayButton,
																		  this.label1,
																		  this.m_wav_file,
																		  this.FindFileButton,
																		  this.ExitButton});
			this.Name = "Form1";
			this.Text = "Wav File player in C#, Bill Nolde 2003 billnolde@ieee.org ";
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new Form1());
		}
//------------------------------------------------------------------------
private void ExitButtonClick(object sender, System.EventArgs e)
{
	Application.Exit();	
}
//---------------------------------------------------------------------
private void FindFileButton_Click(object sender, System.EventArgs e)
{
	openFileDialog1.FileName = m_wav_file.Text;
	openFileDialog1.ShowDialog();
	m_wav_file.Text = openFileDialog1.FileName;
}
//---------------------------------------------------------------------------
private void OnPlayButtonClick(object sender, System.EventArgs e)
{
	WAVSounds ws = new WAVSounds();
	ws.Play(m_wav_file.Text,ws.SND_ASYNC);	
}
//-------------------------------------------------------------------------
private void StopButton_Click(object sender, System.EventArgs e)
{
	WAVSounds ws = new WAVSounds();
	ws.StopPlay();			
}
//-------------------------------------------------------------------------
private void AboutButtonClick(object sender, System.EventArgs e)
{
	MessageBox(0,"Simple C# class for playing .WAV files" +
		"\n      for the .NET Framework" +
		"\n              Bill Nolde 2003" +
		"\n        billnolde@ieee.org","",0);		
}
//-------------------------------------------------------------------------

	}	//end class
}		//end name space

