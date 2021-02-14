[![](http://img.youtube.com/vi/O8LT_GmBJmc/0.jpg)](http://www.youtube.com/watch?v=O8LT_GmBJmc "Distributed Factory System")

ACW1 – Factory system
PROBLEM DESCRIPTION
You are to design and build a distributed application for Crunchibone Pet Foods
Limited. The system will form an important part of the quality monitoring process
for their dog biscuit production lines. The production line requires software at
three different locations:
1. Weighing station
At a weighing station, filled bags of dog biscuits are presented to be weighed at
approximately one second intervals. They are weighed automatically and the
results are sent over the network to a server. There are many weighing
stations in the factory. They are used for different products and different pack
sizes at different times. At any given time, some may be operational while
others are not. Weighing stations operate on Windows PCs and are connected
to the company’s LAN.
2. Data centre server
The data centre server accepts data from weighing stations whenever they
choose to send it, and sends summaries of the data to management information
system terminals on request. The data centre server is connected to the
company LAN and also to the internet.
3. Management information system
The management Information systems (MIS) must present the data from the
server in a readable form. The users want to be able to see simple reports of
production volumes, percentage of underweight product bags, and so on.
Several MIS stations may wish to look at the data at the same time. Some MIS
stations may be operating on site and be connected by the factory LAN, while
others might be at the company’s head office, on a separate site. MIS stations
may be connected or disconnected from the network at any time.

ANALYSIS OF THE PROBLEM
There are several technologies available to you to develop this application. You
have already built systems using some of them in the lab. It is up to you which
technology or combination of technologies you decide to use, but you will be
expected to justify your decision by thorough analysis of the problem you are
trying to solve and investigation of the potential solutions. You will have to write
this analysis and decision making process up in your report.
You will doubtless notice that the information available to you about the problem
domain is far from complete. Where information is lacking, you should make
sensible assumptions, and justify these in your report.
SOFTWARE YOU HAVE TO DESIGN AND BUILD
You must write software for all three components of the system. All three must be
Windows applications written using the .NET framework. Brief descriptions of
these are given below, but it’s part of your task to think about what is required
and to come up with a sensible design. This will probably mean more functionality
than is described here.
Weighing Station
You must write software for the weighing station. Your software should allow a
human user to set the nominal weight and name of the product being weighed at
each station. This data must be passed to the server when it is changed. You will
be provided with a library (downloadable form the module web site) from the
manufacturer of the weighing equipment, which you must use in your weighing
station code. This library will raise an event every time a bag of product is
weighed. Your software must respond to these events and communicate the data
to the server. When you pass data to the server, you should also include (at least)
the date and time at which the measurement was taken and the nominal weight.
Server
The server must receive data from as many weighing stations as wish to send it. It
must store this data and be able to retrieve it on demand. It must provide data to
the management information system terminals on request. The server will need to
be multi-threaded. You are expected to write the server as a standalone
application. You cannot assume that IIS will be running on the server platform.
Management information system terminals
The MIS terminals must connect to the server and be able to request data to create
reports. For the purposes of this project, only two reports will be required
(though you may add others if you wish):
1. A report showing the last 10 readings from each weighing station.
2. A report showing the number of underweight bags for each weighing
station in the last 24 hours.
Any MIS terminal should be able to request and present either of these reports at
any time. The MIS application should be a standalone windows program, not a set
of web pages.
