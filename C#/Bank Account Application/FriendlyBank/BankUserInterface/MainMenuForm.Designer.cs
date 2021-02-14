namespace BankUserInterface
{
    partial class MainMenuForm
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
            this.inputLabel = new System.Windows.Forms.Label();
            this.nameTextBox = new System.Windows.Forms.TextBox();
            this.newAccountButton = new System.Windows.Forms.Button();
            this.findAccountByNumberButton = new System.Windows.Forms.Button();
            this.removeAccountByNumberButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // inputLabel
            // 
            this.inputLabel.AutoSize = true;
            this.inputLabel.Location = new System.Drawing.Point(12, 5);
            this.inputLabel.Name = "inputLabel";
            this.inputLabel.Size = new System.Drawing.Size(34, 13);
            this.inputLabel.TabIndex = 1;
            this.inputLabel.Text = "Input:";
            // 
            // nameTextBox
            // 
            this.nameTextBox.Location = new System.Drawing.Point(55, 5);
            this.nameTextBox.Name = "nameTextBox";
            this.nameTextBox.Size = new System.Drawing.Size(326, 20);
            this.nameTextBox.TabIndex = 2;
            // 
            // newAccountButton
            // 
            this.newAccountButton.Location = new System.Drawing.Point(55, 49);
            this.newAccountButton.Name = "newAccountButton";
            this.newAccountButton.Size = new System.Drawing.Size(91, 34);
            this.newAccountButton.TabIndex = 3;
            this.newAccountButton.Text = "Create Account by Name";
            this.newAccountButton.UseVisualStyleBackColor = true;
            this.newAccountButton.Click += new System.EventHandler(this.newAccountButton_Click);
            // 
            // findAccountByNumberButton
            // 
            this.findAccountByNumberButton.Location = new System.Drawing.Point(169, 49);
            this.findAccountByNumberButton.Name = "findAccountByNumberButton";
            this.findAccountByNumberButton.Size = new System.Drawing.Size(91, 34);
            this.findAccountByNumberButton.TabIndex = 4;
            this.findAccountByNumberButton.Text = "Find Account by Number";
            this.findAccountByNumberButton.UseVisualStyleBackColor = true;
            this.findAccountByNumberButton.Click += new System.EventHandler(this.findAccountByNumberButton_Click);
            // 
            // removeAccountByNumberButton
            // 
            this.removeAccountByNumberButton.Location = new System.Drawing.Point(281, 49);
            this.removeAccountByNumberButton.Name = "removeAccountByNumberButton";
            this.removeAccountByNumberButton.Size = new System.Drawing.Size(100, 34);
            this.removeAccountByNumberButton.TabIndex = 5;
            this.removeAccountByNumberButton.Text = "Remove Account by Number";
            this.removeAccountByNumberButton.UseVisualStyleBackColor = true;
            this.removeAccountByNumberButton.Click += new System.EventHandler(this.removeAccountByNumberButton_Click);
            // 
            // MainMenuForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(416, 96);
            this.Controls.Add(this.removeAccountByNumberButton);
            this.Controls.Add(this.findAccountByNumberButton);
            this.Controls.Add(this.newAccountButton);
            this.Controls.Add(this.nameTextBox);
            this.Controls.Add(this.inputLabel);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(424, 123);
            this.Name = "MainMenuForm";
            this.Text = "Friendly Bank";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label inputLabel;
        private System.Windows.Forms.TextBox nameTextBox;
        private System.Windows.Forms.Button newAccountButton;
        private System.Windows.Forms.Button findAccountByNumberButton;
        private System.Windows.Forms.Button removeAccountByNumberButton;
    }
}

