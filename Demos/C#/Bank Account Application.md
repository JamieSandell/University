[![](http://img.youtube.com/vi/B46WpDiPr78/0.jpg)](http://www.youtube.com/watch?v=B46WpDiPr78 "Bank Account Application")

Account System
For this practical assignment you are required to create a Bank Account management
system. The information that must be held in each account is:
• The name of the account holder
• The address of the account holder
• The balance of the account
• The overdraft limit on the account
This information is to be held in an Account class, and you have been employed to
create this class and a user interface which will interact with it.
The set of behaviours that the customer has asked for is as follows:
• pay money into the account
• draw money out of the account
• view the balance
• change the name and address of the account holder
• change the overdraft limit
• view the overdraft limit
All the methods in the Account class should perform proper validation. In particular:
• It should not be possible to pay in a negative amount of funds.
• It should not be possible to withdraw a negative amount of funds.
• It should not be possible to withdraw more money that is in an account.
• It should not be possible to create an account with a name which contains
numeric digits.
The system should include a set of tests which can be run as evidence that the Account
class performs the above behaviours correctly.
The bank itself will be represented by a Bank class which will provide facilities for storing
and retrieving accounts, based on the account name property. The Bank class should
refuse to store an account which has the same name as an existing one.
User Interface
The system should provide a Windows Forms based user interface which will allow the
above account behaviours to be accessed.
This should include a means by which a given account can be located by account name.
In addition, when displaying the balance of an account this value should be displayed in
red if the account is overdrawn.
Bank Account Application Extensions
If you want to add extensions to the bank system you can also think about adding the
following:
• Bank accounts should have an account number as well as an account holder
name. This number should be unique for every account. It should be possible to
find an account in the bank based on the account number instead of the name.
• The bank account information should be stored in a file when the program exits
and loaded again when the program starts.
You can add further extensions if you wish, once the core features have been
implemented and tested, but you should remember that beyond a certain point it will not
be possible for them to attract further marks for this particular assignment.
