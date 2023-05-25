# Proiect-LAN-PARTY
 -Proiectul de față a fost realizat pentru a îndeplini o serie de cerințe, pe care le voi descrie în detaliu mai jos, pe lângă soluțiile implementate de mine.
 -Inainte de rezolvarea cerintelor propriu-zise, a fost necesara citirea din mai multe fisiere de intrare aferente testelor, folosind doua functii specializate:

 -void readingData(int lastRequest, int *numberOfTeams, FILE **teamsFile, Team **listOfTeamsHead, char *argv[])
   -aceasta inglobeaza mai multe functionalitati tipice listelor inlantuite, cum ar fi crearea, adaugarea de noduri, precum si functii cu rol de atribuire de valori noilor noduri create, precum si de evitare a redundantei codului scris.
    -void addingAtBeginning(Team **listOfTeamHead, Team **current); - functie de adaugare a unui singur nod in lista
    -void addTheTeams(Team **listOfTeamHead, int numberOfTeams, FILE *teamsfile); - functia principala de adaugare in lista
    -void addingPlayer(Player **playerHead, Player *currentPlayer); - adauga playerii in echipe

 -int readTheRequests(FILE **requestsFile, int positionOfTheLastRequest, char *argv[]) - returneaza taskul ce trebuie rezolvat
    -aceasta functionalitate foloseste tehnici de prelucrare a fisierului de intrare, precum deschiderea, parcurgerea, precum si altele evidentiate mai jos:
    -void closeTheFile(FILE **inputFile)
    -void openTheFile(FILE **inputFile, char *mode, char *nameOfFile)
    -void goThroughFile(FILE **requestsFile, int *position);

 -Pentru prima cerință, care presupune extragerea dintr-o serie de fișiere de intrare a datelor ce descriu în detaliu o echipă, am ales să implementez o listă simplu înlănțuită, datorită, în primul rând simplității codului, cât și a eficienței din punct de vedere al comsumului de memorie. Pe scurt, această listă cuprinde date primitive, de exemplu punctajul echipei, declarat ca variabilă de tip double, numele acesteia ca șir de caractere, precum și o structură de tip listă înlănțuită, ce reține date despre jucători. 
 -In privinta functiilor, am implementat o functie, ce inglobeaza mai multe functionalitati, dintre cele mai importante fiind cea de afisare a listei, precum si de stergere a acesteia

 -void solveTheFirstTask(Team *listOfTeamsHead, FILE **outputFile);
 -void displayTheList(Team *listOfTeamHead, FILE **outputFile);
 -Team *deleteTheList(Team *listOfTeamsHead);

 -Pentru a doua cerință, în care trebuiesc eliminate un număr de echipe cu cele mai mici punctaje, până când în lista cu pricina rămâne cea mai mare putere a lui 2, mai mică decât numărul inițial, am implementat un set de funcții. Funcția principală a soluției calculează numărul de echipe ce trebuiesc șterse și apelează funcția eliminateTheTeams, care apelează o funcție specializată în căutarea punctajului minim din listă la fiecare pas, urmând ștergerea propriu-zisă a echipelor găsite. Prototipurile functionalitatilor implementate si folosite pentru rezolvarea acestui task sunt:

 -void displayTheList(Team *listOfTeamHead, FILE **outputFile);
 -void eliminateTheTeamsUtil(Team **listOfTeamsHead, int *numberOfTeams, FILE **outputFile);
 -void eliminateTheTeams(Team **ListOfTeamsHead);
 -Team *deleteTheList(Team *listOfTeamsHead);

 -Al treilea task, a fost, după părerea mea, cel mai complicat din punct de vedere al găsirii unei soluții cât mai eficiente. Pentru simularea jocului trebuiau reținute meciurile create în urma organizării echipelor rămase după taskul 2. Pentru asta am ales să implementez o coadă de meciuri, ale cărei noduri să rețină date despre cele două echipe adversare, cum ar fi numele, punctajele și câte o referință către playerii fiecărei echipe. Echipele câștigătoare le-am introdus la fiecare pas într-o stivă de câștigători, iar cele pierzătoare, într-o stivă de pierzători, pe care ulterior am șters-o conformm cerinței. Toți acești pași au fost îndepliniți până în momentul în care au rămas două echipe. De asemenea, la 16 echipe rămase, după introducerea în stiva de câștigători, am creat o listă simplu înlănțuită cu ultimele opt echipe rămase. La final, am creat meciul final folosind o funcție specializată, urmând găsirea câștigătorului. În cele din urmă, am șters ce a rămas neșters din memorie. Functional, am implementat trei functii ce inglobeaza toate functionalitatile realizate pentru indeplinirea acestui task. Cele mai importante functionalitati implementate:

 -solveTheThirdTaskPt1(&listOfTeamsHead, &outputFile, &numberOfTeams) 
    -realizeaza taskul doi, mai putin stergerea efectiva a listei
 -simulateTheGame(queueOfMatches, &outputFile, listOfTeamsHead, numberOfTeams, &gameWinners, positionOfLastRequest)
    -foloseste o serie de functionalitati cu rol de manipulare a stivelor si a cozii de meciuri
        -Stack *top(Stack *theStack);
        -Stack *pop(Stack **theStack);
        -void pushTheWinner(Stack **theStack, Stack *winnerOrLoserTeam);
        -int isTheStackEmpty(Stack *theStack);
        -void deleteFromStack(Stack **itemToDelete);
        -void deleteStack(Stack **stackToDelete);
        -void enqueueTheMatch(QueueOfMatches *queueOfMatches, QMatch *currentMatch, FILE **outputFile);
        -void enqueueUtil(QueueOfMatches *queueOfMatches, Team *listOfTeamsHead, FILE **outputFile);
        -void deleteTheQueue(QueueOfMatches *queueOfMatches);
        -QMatch *dequeueOfMatches(QueueOfMatches *queueOfMatches, Stack **winnerStack, Stack **loserStack);
        -int isQueueOfMatchesEmpty(QueueOfMatches *queueOfMatches);
        -QMatch *setTheMatch(QMatch *someMatch, QMatch *aux);
        -void deleteTheMatchesQueue(QueueOfMatches *queueOfMatches);

 -La taskul patru am implementat un arbore binar de căutare, folosind lista de câștigători implementată la taskul anterior, folosind funcția de inserare, definire a unui nod tip, precum și de ștergere a arborelui. Ulterior, cu o traversare tip inordine, am scris în fișierul de output numele echipelor și punctajele lor.
 Functionalitatile necesare implica atat cele folosite la taskurile anterioare, cat si cele de prelucrare a arborelui binar de cautare, cat si a listei celor opt invingatori.

-WinnersTree *createTheNode(char *nameOfTeam, double points);
-WinnersTree *addTeamInTree(WinnersTree *BinarySearchTreeRoot, char *nameOfTeam, double points);
-void inorder(WinnersTree *BinarySearchTreeRoot, FILE **outputFile);
-void deleteTheTree(WinnersTree **BinarySearchTreeRoot);
-WinnersList *deleteWinners(WinnersList *winnersList);
-void addTheWinners(WinnersList **winnersListHead, WinnersList *currentTeam);

 -Pentru ultimul task am implementat un AVL, respectiv o serie de funcții de prelucrare, cum ar fi inserarea unei echipe în arbore, ștergerea arborelui la final, inițializarea unui nod tip AVL, precum și afișarea echipelor de pe nivelul doi. De menționat aici, ar fi faptul că am folosit o listă auxiliară creată în urma parcurgerii inordine a BST-ului, utilă în crearea nodurilor pentru AVL. Functionalitatile necesare realizarii taskului acesta sunt cele de la taskurile anterioare, cat si cele de prelucrare a arborelui echilibrat, dar si a leaderboard-ului.

-AVLNode *createAVLNode(char *nameOfTeam, double points);
-AVLNode *rotateToRight(AVLNode *rootSubtree);
-AVLNode *rotateToLeft(AVLNode *rootSubtree);
-AVLNode *insertInAVL(AVLNode *AVLRoot, char *nameOfTeam, double points);
-void deleteAVLTree(AVLNode **AVLRoot);
-void createTheLeaderboard(WinnersList **leaderboard, WinnersTree *BinarySearchTreeRoot);

Din punct de vedere al utilitatii temei, consider ca exercitiul propus reuseste sa promoveze gandirea analitica necesara gasirii si conturarii unei solutii eficiente. 