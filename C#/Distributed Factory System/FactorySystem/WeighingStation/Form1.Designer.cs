namespace WeighingStation
{
    partial class FormWeighingStation
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
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPageMain = new System.Windows.Forms.TabPage();
            this.textBoxProductNameCurrentValue = new System.Windows.Forms.TextBox();
            this.labelProductNameCurrentValue = new System.Windows.Forms.Label();
            this.textBoxNominalWeightCurrentValue = new System.Windows.Forms.TextBox();
            this.labelNominalWeightCurrentValue = new System.Windows.Forms.Label();
            this.labelProductNameError = new System.Windows.Forms.Label();
            this.labelNominalWeightError = new System.Windows.Forms.Label();
            this.buttonSet = new System.Windows.Forms.Button();
            this.textBoxProductName = new System.Windows.Forms.TextBox();
            this.textBoxNominalWeight = new System.Windows.Forms.TextBox();
            this.labelProductName = new System.Windows.Forms.Label();
            this.labelNominalWeight = new System.Windows.Forms.Label();
            this.tabPageServerStatus = new System.Windows.Forms.TabPage();
            this.tabPageLogging = new System.Windows.Forms.TabPage();
            this.tabPageOptions = new System.Windows.Forms.TabPage();
            this.tabControl1.SuspendLayout();
            this.tabPageMain.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPageMain);
            this.tabControl1.Controls.Add(this.tabPageServerStatus);
            this.tabControl1.Controls.Add(this.tabPageLogging);
            this.tabControl1.Controls.Add(this.tabPageOptions);
            this.tabControl1.Location = new System.Drawing.Point(0, 1);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(296, 273);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPageMain
            // 
            this.tabPageMain.Controls.Add(this.textBoxProductNameCurrentValue);
            this.tabPageMain.Controls.Add(this.labelProductNameCurrentValue);
            this.tabPageMain.Controls.Add(this.textBoxNominalWeightCurrentValue);
            this.tabPageMain.Controls.Add(this.labelNominalWeightCurrentValue);
            this.tabPageMain.Controls.Add(this.labelProductNameError);
            this.tabPageMain.Controls.Add(this.labelNominalWeightError);
            this.tabPageMain.Controls.Add(this.buttonSet);
            this.tabPageMain.Controls.Add(this.textBoxProductName);
            this.tabPageMain.Controls.Add(this.textBoxNominalWeight);
            this.tabPageMain.Controls.Add(this.labelProductName);
            this.tabPageMain.Controls.Add(this.labelNominalWeight);
            this.tabPageMain.Location = new System.Drawing.Point(4, 22);
            this.tabPageMain.Name = "tabPageMain";
            this.tabPageMain.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageMain.Size = new System.Drawing.Size(288, 247);
            this.tabPageMain.TabIndex = 0;
            this.tabPageMain.Text = "Main";
            this.tabPageMain.UseVisualStyleBackColor = true;
            // 
            // textBoxProductNameCurrentValue
            // 
            this.textBoxProductNameCurrentValue.Location = new System.Drawing.Point(126, 124);
            this.textBoxProductNameCurrentValue.Name = "textBoxProductNameCurrentValue";
            this.textBoxProductNameCurrentValue.ReadOnly = true;
            this.textBoxProductNameCurrentValue.Size = new System.Drawing.Size(100, 20);
            this.textBoxProductNameCurrentValue.TabIndex = 10;
            // 
            // labelProductNameCurrentValue
            // 
            this.labelProductNameCurrentValue.AutoSize = true;
            this.labelProductNameCurrentValue.Location = new System.Drawing.Point(34, 124);
            this.labelProductNameCurrentValue.Name = "labelProductNameCurrentValue";
            this.labelProductNameCurrentValue.Size = new System.Drawing.Size(74, 13);
            this.labelProductNameCurrentValue.TabIndex = 9;
            this.labelProductNameCurrentValue.Text = "Current Value:";
            // 
            // textBoxNominalWeightCurrentValue
            // 
            this.textBoxNominalWeightCurrentValue.Location = new System.Drawing.Point(126, 48);
            this.textBoxNominalWeightCurrentValue.Name = "textBoxNominalWeightCurrentValue";
            this.textBoxNominalWeightCurrentValue.ReadOnly = true;
            this.textBoxNominalWeightCurrentValue.Size = new System.Drawing.Size(100, 20);
            this.textBoxNominalWeightCurrentValue.TabIndex = 8;
            // 
            // labelNominalWeightCurrentValue
            // 
            this.labelNominalWeightCurrentValue.AutoSize = true;
            this.labelNominalWeightCurrentValue.Location = new System.Drawing.Point(34, 48);
            this.labelNominalWeightCurrentValue.Name = "labelNominalWeightCurrentValue";
            this.labelNominalWeightCurrentValue.Size = new System.Drawing.Size(74, 13);
            this.labelNominalWeightCurrentValue.TabIndex = 7;
            this.labelNominalWeightCurrentValue.Text = "Current Value:";
            // 
            // labelProductNameError
            // 
            this.labelProductNameError.AutoSize = true;
            this.labelProductNameError.ForeColor = System.Drawing.Color.Red;
            this.labelProductNameError.Location = new System.Drawing.Point(131, 150);
            this.labelProductNameError.Name = "labelProductNameError";
            this.labelProductNameError.Size = new System.Drawing.Size(0, 13);
            this.labelProductNameError.TabIndex = 6;
            // 
            // labelNominalWeightError
            // 
            this.labelNominalWeightError.AutoSize = true;
            this.labelNominalWeightError.ForeColor = System.Drawing.Color.Red;
            this.labelNominalWeightError.Location = new System.Drawing.Point(129, 70);
            this.labelNominalWeightError.Name = "labelNominalWeightError";
            this.labelNominalWeightError.Size = new System.Drawing.Size(0, 13);
            this.labelNominalWeightError.TabIndex = 5;
            // 
            // buttonSet
            // 
            this.buttonSet.Location = new System.Drawing.Point(108, 191);
            this.buttonSet.Name = "buttonSet";
            this.buttonSet.Size = new System.Drawing.Size(75, 23);
            this.buttonSet.TabIndex = 4;
            this.buttonSet.Text = "Set";
            this.buttonSet.UseVisualStyleBackColor = true;
            this.buttonSet.Click += new System.EventHandler(this.buttonSet_Click);
            // 
            // textBoxProductName
            // 
            this.textBoxProductName.Location = new System.Drawing.Point(126, 101);
            this.textBoxProductName.Name = "textBoxProductName";
            this.textBoxProductName.Size = new System.Drawing.Size(100, 20);
            this.textBoxProductName.TabIndex = 3;
            // 
            // textBoxNominalWeight
            // 
            this.textBoxNominalWeight.Location = new System.Drawing.Point(126, 22);
            this.textBoxNominalWeight.Name = "textBoxNominalWeight";
            this.textBoxNominalWeight.Size = new System.Drawing.Size(100, 20);
            this.textBoxNominalWeight.TabIndex = 2;
            // 
            // labelProductName
            // 
            this.labelProductName.AutoSize = true;
            this.labelProductName.Location = new System.Drawing.Point(34, 101);
            this.labelProductName.Name = "labelProductName";
            this.labelProductName.Size = new System.Drawing.Size(78, 13);
            this.labelProductName.TabIndex = 1;
            this.labelProductName.Text = "Product Name:";
            // 
            // labelNominalWeight
            // 
            this.labelNominalWeight.AutoSize = true;
            this.labelNominalWeight.Location = new System.Drawing.Point(34, 22);
            this.labelNominalWeight.Name = "labelNominalWeight";
            this.labelNominalWeight.Size = new System.Drawing.Size(85, 13);
            this.labelNominalWeight.TabIndex = 0;
            this.labelNominalWeight.Text = "Nominal Weight:";
            // 
            // tabPageServerStatus
            // 
            this.tabPageServerStatus.Location = new System.Drawing.Point(4, 22);
            this.tabPageServerStatus.Name = "tabPageServerStatus";
            this.tabPageServerStatus.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageServerStatus.Size = new System.Drawing.Size(288, 247);
            this.tabPageServerStatus.TabIndex = 1;
            this.tabPageServerStatus.Text = "Server Status";
            this.tabPageServerStatus.UseVisualStyleBackColor = true;
            // 
            // tabPageLogging
            // 
            this.tabPageLogging.Location = new System.Drawing.Point(4, 22);
            this.tabPageLogging.Name = "tabPageLogging";
            this.tabPageLogging.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageLogging.Size = new System.Drawing.Size(288, 247);
            this.tabPageLogging.TabIndex = 3;
            this.tabPageLogging.Text = "Logging";
            this.tabPageLogging.UseVisualStyleBackColor = true;
            // 
            // tabPageOptions
            // 
            this.tabPageOptions.Location = new System.Drawing.Point(4, 22);
            this.tabPageOptions.Name = "tabPageOptions";
            this.tabPageOptions.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageOptions.Size = new System.Drawing.Size(288, 247);
            this.tabPageOptions.TabIndex = 4;
            this.tabPageOptions.Text = "Options";
            this.tabPageOptions.UseVisualStyleBackColor = true;
            // 
            // FormWeighingStation
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 273);
            this.Controls.Add(this.tabControl1);
            this.Name = "FormWeighingStation";
            this.Text = "Weighing Station";
            this.tabControl1.ResumeLayout(false);
            this.tabPageMain.ResumeLayout(false);
            this.tabPageMain.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPageMain;
        private System.Windows.Forms.TabPage tabPageServerStatus;
        private System.Windows.Forms.TextBox textBoxNominalWeight;
        private System.Windows.Forms.Label labelProductName;
        private System.Windows.Forms.Label labelNominalWeight;
        private System.Windows.Forms.Button buttonSet;
        private System.Windows.Forms.TextBox textBoxProductName;
        private System.Windows.Forms.Label labelNominalWeightError;
        private System.Windows.Forms.Label labelProductNameError;
        private System.Windows.Forms.TextBox textBoxProductNameCurrentValue;
        private System.Windows.Forms.Label labelProductNameCurrentValue;
        private System.Windows.Forms.TextBox textBoxNominalWeightCurrentValue;
        private System.Windows.Forms.Label labelNominalWeightCurrentValue;
        private System.Windows.Forms.TabPage tabPageLogging;
        private System.Windows.Forms.TabPage tabPageOptions;
    }
}

