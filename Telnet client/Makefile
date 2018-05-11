all: cli ser

cli: telnetcli.c
	gcc -w -fpermissive -std=c++11 telnetcli.c -o telnetcli -lresolv -lsocket -lnsl
ser: telnetserv.c
	gcc -w -fpermissive -std=c++11 telnetserv.c -o telnetserv -lresolv -lsocket -lnsl