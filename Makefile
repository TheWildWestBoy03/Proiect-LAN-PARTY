build: listOfTeams.c files.c main.c matchesQueue.c stackOfWinners.c BinarySearchTree.c
	gcc -o lanparty $^
clean:
	rm -f lanparty
