server : 
	gcc bluescreen/bserver.c -o bin/bserver

client :
	gcc bluescreen/bclient.c -o bin/bclient

screen :
	cp bluescreen/bscreen.jar bin/
	cp attackshs/screen.sh bin/

clean :
	rm -rf bin/*

all : server client screen
