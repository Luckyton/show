
server : 
	gcc bluescreen/bserver.c -o bin/bserver

client :
	gcc bluescreen/bclient.c -o bin/bclient

clean :
	rm -rf bin/*

all :
	make server
	make client