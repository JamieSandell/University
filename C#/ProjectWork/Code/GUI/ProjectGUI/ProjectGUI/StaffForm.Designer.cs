namespace ProjectGUI
{
    partial class StaffForm
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
            this.labelSelectTask = new System.Windows.Forms.Label();
            this.comboBoxSelectTask = new System.Windows.Forms.ComboBox();
            this.buttonStartTimer = new System.Windows.Forms.Button();
            this.buttonStopTimer = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // labelSelectTask
            // 
            this.labelSelectTask.AutoSize = true;
            this.labelSelectTask.Location = new System.Drawing.Point(27, 26);
            this.labelSelectTask.Name = "labelSelectTask";
            this.labelSelectTask.Size = new System.Drawing.Size(64, 13);
            this.labelSelectTask.TabIndex = 0;
            this.labelSelectTask.Text = "SelectTask:";
            // 
            // comboBoxSelectTask
            // 
            this.comboBoxSelectTask.FormattingEnabled = true;
            this.comboBoxSelectTask.Location = new System.Drawing.Point(119, 23);
            this.comboBoxSelectTask.Name = "comboBoxSelectTask";
            this.comboBoxSelectTask.Size = new System.Drawing.Size(121, 21);
            this.comboBoxSelectTask.TabIndex = 1;
            // 
            // buttonStartTimer
            // 
            this.buttonStartTimer.Location = new System.Drawing.Point(52, 146);
            this.buttonStartTimer.Name = "buttonStartTimer";
            this.buttonStartTimer.Size = new System.Drawing.Size(75, 23);
            this.buttonStartTimer.TabIndex = 2;
            this.buttonStartTimer.Text = "Start Timer";
            this.buttonStartTimer.UseVisualStyleBackColor = true;
            // 
            // buttonStopTimer
            // 
            this.buttonStopTimer.Location = new System.Drawing.Point(188, 146);
            this.buttonStopTimer.Name = "buttonStopTimer";
            this.buttonStopTimer.Size = new System.Drawing.Size(75, 23);
            this.buttonStopTimer.TabIndex = 3;
            this.buttonStopTimer.Text = "Stop Timer";
            this.buttonStopTimer.UseVisualStyleBackColor = true;
            // 
            // StaffForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 273);
            this.Controls.Add(this.buttonStopTimer);
            this.Controls.Add(this.buttonStartTimer);
            this.Controls.Add(this.comboBoxSelectTask);
            this.Controls.Add(this.labelSelectTask);
            this.Name = "StaffForm";
            this.Text = "StaffForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelSelectTask;
        private System.Windows.Forms.ComboBox comboBoxSelectTask;
        private System.Windows.Forms.Button buttonStartTimer;
        private System.Windows.Forms.Button buttonStopTimer;
    }
}