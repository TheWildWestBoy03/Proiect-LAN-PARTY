build:
	gcc listOfTeams.c listOfTeams.h Player.h main.c -o lanparty
	./lanparty
clean:
	rm -f lanparty
