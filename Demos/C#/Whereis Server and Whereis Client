[![](http://img.youtube.com/vi/UPUI7K6zLdk/0.jpg)](http://www.youtube.com/watch?v=UPUI7K6zLdk "Whereis Server and Whereis Client")

CLIENT AND SERVER IN C#
The coursework requires you to implement two C# Windows console applications; one is a client and the other is the server. They should use TCP sockets by means of the appropriate classes in System.Net and System.Net.Sockets. The task is to implement a simple student locating facility. Students will be identified by their computer login name. It is not necessary to implement any form of user interface and simple use of Microsoft Command Prompt interface to run the client is required. If students implement an optional windows interface this should be enabled by a command line switch.

The client, we shall call it whereis can have two arguments, a user name and a string giving location information.

For example:

G:\08241\ whereis cssbct
cssbct is in RB-336
G:\08241\ whereis cssbct "in RB-310 for a meeting"
cssbct location changed to be in RB-310 for a meeting
G:\08241\ whereis cssbct
cssbct is in RB-310 for a meeting
In this example the first call of the client showed the current location of the user cssbct. The second was used to change the location and the third showed the changed response.

Protocol for Coursework
INTRODUCTION
Your coursework should implement the following protocol for communication between the client and server.
If each student invented their own protocol, the there would be no interoperability between different implementations.
Students would also be making assumptions about requirements when implementing their programs which is not generally a good action for a software engineer.
Requiring the implementation of a standard protocol means that every student's implementation should be interoperable with every other, and the working server provided by the lecturer.
So you can develop your client using the lecturer's server, and develop your server later once you are happy with the correctness of your client.
It is necessary to communicate with a reference or external server in addition to your own server in order to demonstrate sucessful client operation for assessment.

You will encode your data to be transferred between client and server as US-ASCII strings terminated by US-ASCII characters 13 then 10 (carriage return then line feed).
There are other more readily available data encoding options in C# such as unicode and object serialization, but using US-ASCII makes our communication easily understandable by other non-C# applications.
