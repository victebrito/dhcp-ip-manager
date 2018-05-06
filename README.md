# dhcp-ip-manager
DHCP log analizer for managing IPv4 Addresses

# Quick description:
Process all IPv4 that were used in the messages (DCHP log) files saved in the server and saves a .csv log with the last date they were used. 

The default log location is set to /var/log/messages-*

Requirements:
-Unix like server (tested on Ubuntu and CentOS)
-ip.csv file
-messages-* log file (it opens all the messages* files in the log folder)


There is also a simple .php page that runs the program, formats and shows the .csv data.

# Next updates:

-Store data in MySQL 
-Accept log files from more than 2 years in a row

