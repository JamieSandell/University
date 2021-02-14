namespace BankUserInterface
{
    partial class AccountManageForm
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
            this.nameLabel = new System.Windows.Forms.Label();
            this.nameTextBox = new System.Windows.Forms.TextBox();
            this.addressLabel = new System.Windows.Forms.Label();
            this.addressTextBox = new System.Windows.Forms.TextBox();
            this.balanceLabel = new System.Windows.Forms.Label();
            this.balanceValueLabel = new System.Windows.Forms.Label();
            this.payInButton = new System.Windows.Forms.Button();
            this.withdrawButton = new System.Windows.Forms.Button();
            this.amountTextBox = new System.Windows.Forms.TextBox();
            this.doneButton = new System.Windows.Forms.Button();
            this.setOverdraftButton = new System.Windows.Forms.Button();
            this.valueLabel = new System.Windows.Forms.Label();
            this.overdraftLabel = new System.Windows.Forms.Label();
            this.availableFundsLabel = new System.Windows.Forms.Label();
            this.availableFundsValueLabel = new System.Windows.Forms.Label();
            this.overdraftLimitValueLabel = new System.Windows.Forms.Label();
            this.accountNumberValueLabel = new System.Windows.Forms.Label();
            this.accountNumberLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // nameLabel
            // 
            this.nameLabel.AutoSize = true;
            this.nameLabel.Location = new System.Drawing.Point(4, 71);
            this.nameLabel.Name = "nameLabel";
            this.nameLabel.Size = new System.Drawing.Size(35, 13);
            this.nameLabel.TabIndex = 0;
            this.nameLabel.Text = "Name";
            // 
            // nameTextBox
            // 
            this.nameTextBox.Location = new System.Drawing.Point(71, 71);
            this.nameTextBox.Name = "nameTextBox";
            this.nameTextBox.Size = new System.Drawing.Size(200, 20);
            this.nameTextBox.TabIndex = 1;
            // 
            // addressLabel
            // 
            this.addressLabel.AutoSize = true;
            this.addressLabel.Location = new System.Drawing.Point(4, 97);
            this.addressLabel.Name = "addressLabel";
            this.addressLabel.Size = new System.Drawing.Size(45, 13);
            this.addressLabel.TabIndex = 2;
            this.addressLabel.Text = "Address";
            // 
            // addressTextBox
            // 
            this.addressTextBox.Location = new System.Drawing.Point(71, 97);
            this.addressTextBox.Multiline = true;
            this.addressTextBox.Name = "addressTextBox";
            this.addressTextBox.Size = new System.Drawing.Size(200, 71);
            this.addressTextBox.TabIndex = 3;
            // 
            // balanceLabel
            // 
            this.balanceLabel.AutoSize = true;
            this.balanceLabel.Location = new System.Drawing.Point(68, 45);
            this.balanceLabel.Name = "balanceLabel";
            this.balanceLabel.Size = new System.Drawing.Size(55, 13);
            this.balanceLabel.TabIndex = 6;
            this.balanceLabel.Text = "Balance : ";
            // 
            // balanceValueLabel
            // 
            this.balanceValueLabel.AutoSize = true;
            this.balanceValueLabel.Location = new System.Drawing.Point(186, 45);
            this.balanceValueLabel.Name = "balanceValueLabel";
            this.balanceValueLabel.Size = new System.Drawing.Size(22, 13);
            this.balanceValueLabel.TabIndex = 7;
            this.balanceValueLabel.Text = "0.0";
            // 
            // payInButton
            // 
            this.payInButton.Location = new System.Drawing.Point(189, 208);
            this.payInButton.Name = "payInButton";
            this.payInButton.Size = new System.Drawing.Size(82, 23);
            this.payInButton.TabIndex = 4;
            this.payInButton.Text = "Pay In";
            this.payInButton.UseVisualStyleBackColor = true;
            this.payInButton.Click += new System.EventHandler(this.payInButton_Click);
            // 
            // withdrawButton
            // 
            this.withdrawButton.Location = new System.Drawing.Point(189, 179);
            this.withdrawButton.Name = "withdrawButton";
            this.withdrawButton.Size = new System.Drawing.Size(82, 23);
            this.withdrawButton.TabIndex = 5;
            this.withdrawButton.Text = "Withdraw";
            this.withdrawButton.UseVisualStyleBackColor = true;
            this.withdrawButton.Click += new System.EventHandler(this.withdrawButton_Click);
            // 
            // amountTextBox
            // 
            this.amountTextBox.Location = new System.Drawing.Point(80, 192);
            this.amountTextBox.Name = "amountTextBox";
            this.amountTextBox.Size = new System.Drawing.Size(100, 20);
            this.amountTextBox.TabIndex = 8;
            // 
            // doneButton
            // 
            this.doneButton.Location = new System.Drawing.Point(72, 284);
            this.doneButton.Name = "doneButton";
            this.doneButton.Size = new System.Drawing.Size(199, 25);
            this.doneButton.TabIndex = 9;
            this.doneButton.Text = "Done";
            this.doneButton.UseVisualStyleBackColor = true;
            this.doneButton.Click += new System.EventHandler(this.doneButton_Click);
            // 
            // setOverdraftButton
            // 
            this.setOverdraftButton.Location = new System.Drawing.Point(189, 237);
            this.setOverdraftButton.Name = "setOverdraftButton";
            this.setOverdraftButton.Size = new System.Drawing.Size(82, 23);
            this.setOverdraftButton.TabIndex = 10;
            this.setOverdraftButton.Text = "Set Overdraft";
            this.setOverdraftButton.UseVisualStyleBackColor = true;
            this.setOverdraftButton.Click += new System.EventHandler(this.setOverdraftButton_Click);
            // 
            // valueLabel
            // 
            this.valueLabel.AutoSize = true;
            this.valueLabel.Location = new System.Drawing.Point(4, 192);
            this.valueLabel.Name = "valueLabel";
            this.valueLabel.Size = new System.Drawing.Size(70, 13);
            this.valueLabel.TabIndex = 11;
            this.valueLabel.Text = "Enter a value";
            // 
            // overdraftLabel
            // 
            this.overdraftLabel.AutoSize = true;
            this.overdraftLabel.Location = new System.Drawing.Point(68, 19);
            this.overdraftLabel.Name = "overdraftLabel";
            this.overdraftLabel.Size = new System.Drawing.Size(84, 13);
            this.overdraftLabel.TabIndex = 12;
            this.overdraftLabel.Text = "Overdraft Limit : ";
            this.overdraftLabel.Click += new System.EventHandler(this.overdraftLabel_Click);
            // 
            // availableFundsLabel
            // 
            this.availableFundsLabel.AutoSize = true;
            this.availableFundsLabel.Location = new System.Drawing.Point(68, 32);
            this.availableFundsLabel.Name = "availableFundsLabel";
            this.availableFundsLabel.Size = new System.Drawing.Size(91, 13);
            this.availableFundsLabel.TabIndex = 13;
            this.availableFundsLabel.Text = "Available Funds : ";
            // 
            // availableFundsValueLabel
            // 
            this.availableFundsValueLabel.AutoSize = true;
            this.availableFundsValueLabel.Location = new System.Drawing.Point(186, 32);
            this.availableFundsValueLabel.Name = "availableFundsValueLabel";
            this.availableFundsValueLabel.Size = new System.Drawing.Size(22, 13);
            this.availableFundsValueLabel.TabIndex = 14;
            this.availableFundsValueLabel.Text = "0.0";
            // 
            // overdraftLimitValueLabel
            // 
            this.overdraftLimitValueLabel.AutoSize = true;
            this.overdraftLimitValueLabel.Location = new System.Drawing.Point(186, 19);
            this.overdraftLimitValueLabel.Name = "overdraftLimitValueLabel";
            this.overdraftLimitValueLabel.Size = new System.Drawing.Size(22, 13);
            this.overdraftLimitValueLabel.TabIndex = 15;
            this.overdraftLimitValueLabel.Text = "0.0";
            // 
            // accountNumberValueLabel
            // 
            this.accountNumberValueLabel.AutoSize = true;
            this.accountNumberValueLabel.Location = new System.Drawing.Point(186, 6);
            this.accountNumberValueLabel.Name = "accountNumberValueLabel";
            this.accountNumberValueLabel.Size = new System.Drawing.Size(13, 13);
            this.accountNumberValueLabel.TabIndex = 17;
            this.accountNumberValueLabel.Text = "0";
            // 
            // accountNumberLabel
            // 
            this.accountNumberLabel.AutoSize = true;
            this.accountNumberLabel.Location = new System.Drawing.Point(69, 6);
            this.accountNumberLabel.Name = "accountNumberLabel";
            this.accountNumberLabel.Size = new System.Drawing.Size(96, 13);
            this.accountNumberLabel.TabIndex = 16;
            this.accountNumberLabel.Text = "Account Number : ";
            // 
            // AccountManageForm
            // 
            this.ClientSize = new System.Drawing.Size(284, 324);
            this.Controls.Add(this.accountNumberValueLabel);
            this.Controls.Add(this.accountNumberLabel);
            this.Controls.Add(this.overdraftLimitValueLabel);
            this.Controls.Add(this.availableFundsValueLabel);
            this.Controls.Add(this.availableFundsLabel);
            this.Controls.Add(this.overdraftLabel);
            this.Controls.Add(this.valueLabel);
            this.Controls.Add(this.setOverdraftButton);
            this.Controls.Add(this.doneButton);
            this.Controls.Add(this.amountTextBox);
            this.Controls.Add(this.payInButton);
            this.Controls.Add(this.withdrawButton);
            this.Controls.Add(this.balanceValueLabel);
            this.Controls.Add(this.balanceLabel);
            this.Controls.Add(this.addressTextBox);
            this.Controls.Add(this.addressLabel);
            this.Controls.Add(this.nameTextBox);
            this.Controls.Add(this.nameLabel);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(292, 351);
            this.Name = "AccountManageForm";
            this.Text = "Account Management";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label nameLabel;
        private System.Windows.Forms.TextBox nameTextBox;
        private System.Windows.Forms.Label addressLabel;
        private System.Windows.Forms.TextBox addressTextBox;
        private System.Windows.Forms.Label balanceLabel;
        private System.Windows.Forms.Label balanceValueLabel;
        private System.Windows.Forms.Button payInButton;
        private System.Windows.Forms.Button withdrawButton;
        private System.Windows.Forms.TextBox amountTextBox;
        private System.Windows.Forms.Button doneButton;
        private System.Windows.Forms.Button setOverdraftButton;
        private System.Windows.Forms.Label valueLabel;
        private System.Windows.Forms.Label overdraftLabel;
        private System.Windows.Forms.Label availableFundsLabel;
        private System.Windows.Forms.Label availableFundsValueLabel;
        private System.Windows.Forms.Label overdraftLimitValueLabel;
        private System.Windows.Forms.Label accountNumberValueLabel;
        private System.Windows.Forms.Label accountNumberLabel;
    }
}