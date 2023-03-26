build:
	gcc listOfTeams.c listOfTeams.h Player.h files.c main.c -o lanparty
clean:
	rm -f lanparty
