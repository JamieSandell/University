Note: netsh http add urlacl url=http://+:8731/Design_Time_Addresses/WCFDataCentreServer/Service1/.  user=DESKTOP-8CKG02O\jammy
netsh http add urlacl url=http://+:8733/Design_Time_Addresses/.  user=DESKTOP-8CKG02O\jammy
netsh http add urlacl url=http://localhost:8731/Design_Time_Addresses/WCFDataCentreServer/Service1/.  user=DESKTOP-8CKG02O\jammy
netsh http add urlacl url=http://+:8731/Design_Time_Addresses/WCFDataCentreServer/Service1/.  user=DESKTOP-8CKG02O\jammy

There are a number of weighing stations (Weighing Station 1, Weighing Station 2)
in the 'Executables' folder to run, along with the server and mis applications.
Weighing Station 1 and Weighing Station 2 are identical, except in their configuration
files they have their weighing station ids set accordingly (i.e. 1 and 2).

If you start up the Server from the executable/server/bin/release folder
it will say Service running.
Then start up Weighing Station 1 from the executable/weighing station 1/bin/release folder
and set the nominal weight and product name.
Do the same for Weighing Station 2.
Whilst they are running launch the mis application from the
executable/mis/bin/release/folder