namespace SystemManagement
{
    partial class StaffReportForm
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
            this.listViewStaffReport = new System.Windows.Forms.ListView();
            this.columnHeaderTaskName = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderPercentCompleted = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderCostPerTask = new System.Windows.Forms.ColumnHeader();
            this.labelStaffName = new System.Windows.Forms.Label();
            this.textBoxStaffName = new System.Windows.Forms.TextBox();
            this.buttonClose = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // listViewStaffReport
            // 
            this.listViewStaffReport.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeaderTaskName,
            this.columnHeaderPercentCompleted,
            this.columnHeaderCostPerTask});
            this.listViewStaffReport.Location = new System.Drawing.Point(1, 47);
            this.listViewStaffReport.Name = "listViewStaffReport";
            this.listViewStaffReport.Size = new System.Drawing.Size(316, 149);
            this.listViewStaffReport.TabIndex = 4;
            this.listViewStaffReport.UseCompatibleStateImageBehavior = false;
            this.listViewStaffReport.View = System.Windows.Forms.View.Details;
            // 
            // columnHeaderTaskName
            // 
            this.columnHeaderTaskName.Text = "Task Name";
            this.columnHeaderTaskName.Width = 127;
            // 
            // columnHeaderPercentCompleted
            // 
            this.columnHeaderPercentCompleted.Text = "% Complete";
            this.columnHeaderPercentCompleted.Width = 95;
            // 
            // columnHeaderCostPerTask
            // 
            this.columnHeaderCostPerTask.Text = "Cost Per Task";
            this.columnHeaderCostPerTask.Width = 90;
            // 
            // labelStaffName
            // 
            this.labelStaffName.AutoSize = true;
            this.labelStaffName.Location = new System.Drawing.Point(-2, 9);
            this.labelStaffName.Name = "labelStaffName";
            this.labelStaffName.Size = new System.Drawing.Size(60, 13);
            this.labelStaffName.TabIndex = 5;
            this.labelStaffName.Text = "Staff Name";
            // 
            // textBoxStaffName
            // 
            this.textBoxStaffName.Location = new System.Drawing.Point(64, 6);
            this.textBoxStaffName.Name = "textBoxStaffName";
            this.textBoxStaffName.ReadOnly = true;
            this.textBoxStaffName.Size = new System.Drawing.Size(100, 20);
            this.textBoxStaffName.TabIndex = 6;
            this.textBoxStaffName.Text = "Name";
            // 
            // buttonClose
            // 
            this.buttonClose.Location = new System.Drawing.Point(127, 219);
            this.buttonClose.Name = "buttonClose";
            this.buttonClose.Size = new System.Drawing.Size(75, 23);
            this.buttonClose.TabIndex = 7;
            this.buttonClose.Text = "Close";
            this.buttonClose.UseVisualStyleBackColor = true;
            this.buttonClose.Click += new System.EventHandler(this.buttonClose_Click);
            // 
            // StaffReportForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(321, 255);
            this.Controls.Add(this.buttonClose);
            this.Controls.Add(this.textBoxStaffName);
            this.Controls.Add(this.labelStaffName);
            this.Controls.Add(this.listViewStaffReport);
            this.Name = "StaffReportForm";
            this.Text = "StaffReportForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListView listViewStaffReport;
        private System.Windows.Forms.ColumnHeader columnHeaderTaskName;
        private System.Windows.Forms.ColumnHeader columnHeaderPercentCompleted;
        private System.Windows.Forms.ColumnHeader columnHeaderCostPerTask;
        private System.Windows.Forms.Label labelStaffName;
        private System.Windows.Forms.TextBox textBoxStaffName;
        private System.Windows.Forms.Button buttonClose;

    }
}