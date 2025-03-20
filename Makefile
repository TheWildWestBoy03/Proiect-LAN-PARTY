build: listOfTeams.c files.c main.c matchesQueue.c stackOfWinners.c BinarySearchTree.c Cerinte.c
	gcc -g -Wall -o lanParty $^
clean:
	rm -f lanParty
