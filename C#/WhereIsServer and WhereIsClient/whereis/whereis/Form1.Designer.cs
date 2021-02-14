namespace whereis
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.buttonSend = new System.Windows.Forms.Button();
            this.richTextBoxResponse = new System.Windows.Forms.RichTextBox();
            this.labelResponse = new System.Windows.Forms.Label();
            this.labelInputName = new System.Windows.Forms.Label();
            this.labelLocation = new System.Windows.Forms.Label();
            this.textBoxInputName = new System.Windows.Forms.TextBox();
            this.textBoxInputLocation = new System.Windows.Forms.TextBox();
            this.textBoxServer = new System.Windows.Forms.TextBox();
            this.labelServer = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // buttonSend
            // 
            this.buttonSend.Location = new System.Drawing.Point(154, 127);
            this.buttonSend.Name = "buttonSend";
            this.buttonSend.Size = new System.Drawing.Size(75, 23);
            this.buttonSend.TabIndex = 0;
            this.buttonSend.Text = "Send";
            this.buttonSend.UseVisualStyleBackColor = true;
            this.buttonSend.Click += new System.EventHandler(this.buttonSend_Click);
            // 
            // richTextBoxResponse
            // 
            this.richTextBoxResponse.Location = new System.Drawing.Point(29, 213);
            this.richTextBoxResponse.Name = "richTextBoxResponse";
            this.richTextBoxResponse.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.ForcedVertical;
            this.richTextBoxResponse.Size = new System.Drawing.Size(293, 113);
            this.richTextBoxResponse.TabIndex = 1;
            this.richTextBoxResponse.Text = "";
            // 
            // labelResponse
            // 
            this.labelResponse.AutoSize = true;
            this.labelResponse.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelResponse.Location = new System.Drawing.Point(25, 181);
            this.labelResponse.Name = "labelResponse";
            this.labelResponse.Size = new System.Drawing.Size(95, 20);
            this.labelResponse.TabIndex = 2;
            this.labelResponse.Text = "Response:";
            // 
            // labelInputName
            // 
            this.labelInputName.AutoSize = true;
            this.labelInputName.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelInputName.Location = new System.Drawing.Point(25, 9);
            this.labelInputName.Name = "labelInputName";
            this.labelInputName.Size = new System.Drawing.Size(60, 20);
            this.labelInputName.TabIndex = 3;
            this.labelInputName.Text = "Name:";
            // 
            // labelLocation
            // 
            this.labelLocation.AutoSize = true;
            this.labelLocation.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelLocation.Location = new System.Drawing.Point(25, 45);
            this.labelLocation.Name = "labelLocation";
            this.labelLocation.Size = new System.Drawing.Size(83, 20);
            this.labelLocation.TabIndex = 4;
            this.labelLocation.Text = "Location:";
            // 
            // textBoxInputName
            // 
            this.textBoxInputName.Location = new System.Drawing.Point(123, 13);
            this.textBoxInputName.Name = "textBoxInputName";
            this.textBoxInputName.Size = new System.Drawing.Size(160, 20);
            this.textBoxInputName.TabIndex = 5;
            // 
            // textBoxInputLocation
            // 
            this.textBoxInputLocation.Location = new System.Drawing.Point(123, 45);
            this.textBoxInputLocation.Name = "textBoxInputLocation";
            this.textBoxInputLocation.Size = new System.Drawing.Size(160, 20);
            this.textBoxInputLocation.TabIndex = 6;
            // 
            // textBoxServer
            // 
            this.textBoxServer.Location = new System.Drawing.Point(123, 82);
            this.textBoxServer.Name = "textBoxServer";
            this.textBoxServer.Size = new System.Drawing.Size(160, 20);
            this.textBoxServer.TabIndex = 8;
            // 
            // labelServer
            // 
            this.labelServer.AutoSize = true;
            this.labelServer.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelServer.Location = new System.Drawing.Point(25, 80);
            this.labelServer.Name = "labelServer";
            this.labelServer.Size = new System.Drawing.Size(66, 20);
            this.labelServer.TabIndex = 7;
            this.labelServer.Text = "Server:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(349, 338);
            this.Controls.Add(this.textBoxServer);
            this.Controls.Add(this.labelServer);
            this.Controls.Add(this.textBoxInputLocation);
            this.Controls.Add(this.textBoxInputName);
            this.Controls.Add(this.labelLocation);
            this.Controls.Add(this.labelInputName);
            this.Controls.Add(this.labelResponse);
            this.Controls.Add(this.richTextBoxResponse);
            this.Controls.Add(this.buttonSend);
            this.Name = "Form1";
            this.Text = "whereis";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonSend;
        private System.Windows.Forms.RichTextBox richTextBoxResponse;
        private System.Windows.Forms.Label labelResponse;
        private System.Windows.Forms.Label labelInputName;
        private System.Windows.Forms.Label labelLocation;
        private System.Windows.Forms.TextBox textBoxInputName;
        private System.Windows.Forms.TextBox textBoxInputLocation;
        private System.Windows.Forms.TextBox textBoxServer;
        private System.Windows.Forms.Label labelServer;
    }
}