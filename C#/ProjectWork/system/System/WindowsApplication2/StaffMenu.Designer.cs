namespace WindowsApplication1
{
    partial class StaffMenu
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
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxStaffName = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.listViewStaffTasksAssignedTo = new System.Windows.Forms.ListView();
            this.columnHeaderTaskName = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderDateAssigned = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderHoursWorked = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderPercentComplete = new System.Windows.Forms.ColumnHeader();
            this.buttonStaffCancel = new System.Windows.Forms.Button();
            this.buttonStaffOk = new System.Windows.Forms.Button();
            this.textBoxStaffSalary = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.buttonStartTimer = new System.Windows.Forms.Button();
            this.buttonEndTimer = new System.Windows.Forms.Button();
            this.textBoxStaffWage = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.textBoxStaffID = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.textBoxStaffAddress1 = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.textBoxStaffAddress2 = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.textBoxStaffCounty = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.textBoxStaffTelephone = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.textBoxStaffMobile = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.textBoxStaffPostCode = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 40);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(101, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Staff Member Name";
            // 
            // textBoxStaffName
            // 
            this.textBoxStaffName.Location = new System.Drawing.Point(132, 37);
            this.textBoxStaffName.Name = "textBoxStaffName";
            this.textBoxStaffName.Size = new System.Drawing.Size(168, 20);
            this.textBoxStaffName.TabIndex = 1;
            this.textBoxStaffName.Text = "Bertrand";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(8, 280);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(94, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Tasks Assigned to";
            // 
            // listViewStaffTasksAssignedTo
            // 
            this.listViewStaffTasksAssignedTo.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeaderTaskName,
            this.columnHeaderDateAssigned,
            this.columnHeaderHoursWorked,
            this.columnHeaderPercentComplete});
            this.listViewStaffTasksAssignedTo.Location = new System.Drawing.Point(12, 303);
            this.listViewStaffTasksAssignedTo.Name = "listViewStaffTasksAssignedTo";
            this.listViewStaffTasksAssignedTo.Size = new System.Drawing.Size(395, 149);
            this.listViewStaffTasksAssignedTo.TabIndex = 3;
            this.listViewStaffTasksAssignedTo.UseCompatibleStateImageBehavior = false;
            this.listViewStaffTasksAssignedTo.View = System.Windows.Forms.View.Details;
            // 
            // columnHeaderTaskName
            // 
            this.columnHeaderTaskName.Text = "Task Name";
            this.columnHeaderTaskName.Width = 127;
            // 
            // columnHeaderDateAssigned
            // 
            this.columnHeaderDateAssigned.Text = "Date Assigned";
            this.columnHeaderDateAssigned.Width = 95;
            // 
            // columnHeaderHoursWorked
            // 
            this.columnHeaderHoursWorked.Text = "Hours Worked";
            this.columnHeaderHoursWorked.Width = 90;
            // 
            // columnHeaderPercentComplete
            // 
            this.columnHeaderPercentComplete.Text = "% Complete";
            this.columnHeaderPercentComplete.Width = 77;
            // 
            // buttonStaffCancel
            // 
            this.buttonStaffCancel.Location = new System.Drawing.Point(249, 458);
            this.buttonStaffCancel.Name = "buttonStaffCancel";
            this.buttonStaffCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonStaffCancel.TabIndex = 7;
            this.buttonStaffCancel.Text = "Cancel";
            this.buttonStaffCancel.UseVisualStyleBackColor = true;
            // 
            // buttonStaffOk
            // 
            this.buttonStaffOk.Location = new System.Drawing.Point(330, 458);
            this.buttonStaffOk.Name = "buttonStaffOk";
            this.buttonStaffOk.Size = new System.Drawing.Size(75, 23);
            this.buttonStaffOk.TabIndex = 8;
            this.buttonStaffOk.Text = "OK";
            this.buttonStaffOk.UseVisualStyleBackColor = true;
            // 
            // textBoxStaffSalary
            // 
            this.textBoxStaffSalary.Enabled = false;
            this.textBoxStaffSalary.Location = new System.Drawing.Point(132, 218);
            this.textBoxStaffSalary.Name = "textBoxStaffSalary";
            this.textBoxStaffSalary.Size = new System.Drawing.Size(168, 20);
            this.textBoxStaffSalary.TabIndex = 10;
            this.textBoxStaffSalary.Text = "£28,000";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(5, 221);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(102, 13);
            this.label3.TabIndex = 9;
            this.label3.Text = "Staff Member Salary";
            // 
            // buttonStartTimer
            // 
            this.buttonStartTimer.Location = new System.Drawing.Point(12, 458);
            this.buttonStartTimer.Name = "buttonStartTimer";
            this.buttonStartTimer.Size = new System.Drawing.Size(75, 23);
            this.buttonStartTimer.TabIndex = 11;
            this.buttonStartTimer.Text = "Start Timer";
            this.buttonStartTimer.UseVisualStyleBackColor = true;
            this.buttonStartTimer.Click += new System.EventHandler(this.buttonStartTimer_Click);
            // 
            // buttonEndTimer
            // 
            this.buttonEndTimer.Location = new System.Drawing.Point(94, 458);
            this.buttonEndTimer.Name = "buttonEndTimer";
            this.buttonEndTimer.Size = new System.Drawing.Size(75, 23);
            this.buttonEndTimer.TabIndex = 12;
            this.buttonEndTimer.Text = "End Timer";
            this.buttonEndTimer.UseVisualStyleBackColor = true;
            this.buttonEndTimer.Click += new System.EventHandler(this.buttonEndTimer_Click);
            // 
            // textBoxStaffWage
            // 
            this.textBoxStaffWage.Enabled = false;
            this.textBoxStaffWage.Location = new System.Drawing.Point(132, 244);
            this.textBoxStaffWage.Name = "textBoxStaffWage";
            this.textBoxStaffWage.Size = new System.Drawing.Size(168, 20);
            this.textBoxStaffWage.TabIndex = 14;
            this.textBoxStaffWage.Text = "£50";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 244);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(102, 13);
            this.label4.TabIndex = 13;
            this.label4.Text = "Staff Member Wage";
            // 
            // textBoxStaffID
            // 
            this.textBoxStaffID.Location = new System.Drawing.Point(132, 11);
            this.textBoxStaffID.Name = "textBoxStaffID";
            this.textBoxStaffID.ReadOnly = true;
            this.textBoxStaffID.Size = new System.Drawing.Size(168, 20);
            this.textBoxStaffID.TabIndex = 16;
            this.textBoxStaffID.Text = "0";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(8, 14);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(84, 13);
            this.label5.TabIndex = 15;
            this.label5.Text = "Staff Member ID";
            // 
            // textBoxStaffAddress1
            // 
            this.textBoxStaffAddress1.Location = new System.Drawing.Point(132, 63);
            this.textBoxStaffAddress1.Name = "textBoxStaffAddress1";
            this.textBoxStaffAddress1.Size = new System.Drawing.Size(168, 20);
            this.textBoxStaffAddress1.TabIndex = 20;
            this.textBoxStaffAddress1.Text = "Street";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 66);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(120, 13);
            this.label7.TabIndex = 19;
            this.label7.Text = "Staff Member Address 1";
            // 
            // textBoxStaffAddress2
            // 
            this.textBoxStaffAddress2.Location = new System.Drawing.Point(132, 89);
            this.textBoxStaffAddress2.Name = "textBoxStaffAddress2";
            this.textBoxStaffAddress2.Size = new System.Drawing.Size(168, 20);
            this.textBoxStaffAddress2.TabIndex = 22;
            this.textBoxStaffAddress2.Text = "City";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 92);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(120, 13);
            this.label8.TabIndex = 21;
            this.label8.Text = "Staff Member Address 2";
            // 
            // textBoxStaffCounty
            // 
            this.textBoxStaffCounty.Location = new System.Drawing.Point(132, 115);
            this.textBoxStaffCounty.Name = "textBoxStaffCounty";
            this.textBoxStaffCounty.Size = new System.Drawing.Size(168, 20);
            this.textBoxStaffCounty.TabIndex = 24;
            this.textBoxStaffCounty.Text = "County";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(6, 118);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(106, 13);
            this.label9.TabIndex = 23;
            this.label9.Text = "Staff Member County";
            // 
            // textBoxStaffTelephone
            // 
            this.textBoxStaffTelephone.Location = new System.Drawing.Point(132, 166);
            this.textBoxStaffTelephone.Name = "textBoxStaffTelephone";
            this.textBoxStaffTelephone.Size = new System.Drawing.Size(168, 20);
            this.textBoxStaffTelephone.TabIndex = 26;
            this.textBoxStaffTelephone.Text = "0819191";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(6, 169);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(124, 13);
            this.label10.TabIndex = 25;
            this.label10.Text = "Staff Member Telephone";
            // 
            // textBoxStaffMobile
            // 
            this.textBoxStaffMobile.Location = new System.Drawing.Point(132, 192);
            this.textBoxStaffMobile.Name = "textBoxStaffMobile";
            this.textBoxStaffMobile.Size = new System.Drawing.Size(168, 20);
            this.textBoxStaffMobile.TabIndex = 28;
            this.textBoxStaffMobile.Text = "12345678965";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(6, 195);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(104, 13);
            this.label11.TabIndex = 27;
            this.label11.Text = "Staff Member Mobile";
            // 
            // textBoxStaffPostCode
            // 
            this.textBoxStaffPostCode.Location = new System.Drawing.Point(132, 141);
            this.textBoxStaffPostCode.Name = "textBoxStaffPostCode";
            this.textBoxStaffPostCode.Size = new System.Drawing.Size(168, 20);
            this.textBoxStaffPostCode.TabIndex = 30;
            this.textBoxStaffPostCode.Text = "PostCode";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(6, 144);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(119, 13);
            this.label12.TabIndex = 29;
            this.label12.Text = "Staff Member PostCode";
            // 
            // StaffMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(413, 489);
            this.Controls.Add(this.textBoxStaffPostCode);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.textBoxStaffMobile);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.textBoxStaffTelephone);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.textBoxStaffCounty);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.textBoxStaffAddress2);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.textBoxStaffAddress1);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.textBoxStaffID);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textBoxStaffWage);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.buttonEndTimer);
            this.Controls.Add(this.buttonStartTimer);
            this.Controls.Add(this.textBoxStaffSalary);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.buttonStaffOk);
            this.Controls.Add(this.buttonStaffCancel);
            this.Controls.Add(this.listViewStaffTasksAssignedTo);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBoxStaffName);
            this.Controls.Add(this.label1);
            this.Name = "StaffMenu";
            this.Text = "Staff Member";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBoxStaffName;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ListView listViewStaffTasksAssignedTo;
        private System.Windows.Forms.ColumnHeader columnHeaderTaskName;
        private System.Windows.Forms.ColumnHeader columnHeaderDateAssigned;
        private System.Windows.Forms.Button buttonStaffCancel;
        private System.Windows.Forms.Button buttonStaffOk;
        private System.Windows.Forms.ColumnHeader columnHeaderHoursWorked;
        private System.Windows.Forms.ColumnHeader columnHeaderPercentComplete;
        private System.Windows.Forms.TextBox textBoxStaffSalary;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button buttonStartTimer;
        private System.Windows.Forms.Button buttonEndTimer;
        private System.Windows.Forms.TextBox textBoxStaffWage;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBoxStaffID;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBoxStaffAddress1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBoxStaffAddress2;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textBoxStaffCounty;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox textBoxStaffTelephone;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textBoxStaffMobile;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox textBoxStaffPostCode;
        private System.Windows.Forms.Label label12;
    }
}