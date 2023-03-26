build:
	gcc listOfTeams.c date/t1/c.in date/t1/d.in listOfTeams.h Player.h files.c main.c -o lanparty
	./lanparty
clean:
	rm -f lanparty
