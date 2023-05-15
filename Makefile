build: listOfTeams.c files.c main.c matchesQueue.c stackOfWinners.c BinarySearchTree.c
	gcc -g -Wall -o lanParty $^
clean:
	rm -f lanParty
