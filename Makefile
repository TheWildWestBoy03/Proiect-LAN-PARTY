build:
	gcc listOfTeams.c listOfTeams.h Player.h files.c main.c matchesQueue.c matchesQueue.h stackOfWinners.c stackOfWinners.h -o lanparty
clean:
	rm -f lanparty
