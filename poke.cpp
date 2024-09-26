/* Name: Dudleen Paul
Date: Monday, April 24th, 2023
Assignment: #8 (Final HW Assignment)
Due Date: Friday, April 28th, 2023
About this project: Creating a 2007's Pokemon Go game.
Assumptions: Valid input.

All work below was performed by Dudleen Paul */

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <fstream>
using namespace std;

//pokemon structure
struct Pokemon
{
    int number;
    string name;
    string type;
    string region;
    int catchPercentage;
    string dexEntry;
    int numberOfCaught;
    int numberOfSeen;
};

//FUNCTION DECLARATIONS
void helpMenu(string chosenDestination, Pokemon*dex);
int hunt(Pokemon*dex, int, string, int pokeBalls, int greatBalls, int ultraBalls);
void printStatistics(Pokemon* dex, int numPokemon);
void pokeSecured(Pokemon*dex, int, string);
void showInventory(int pokeBalls, int greatBalls, int ultraBalls);
int chooseBall(int pokeBalls, int greatBalls, int ultraBalls);
int calculateCatch(int basePercentage, int ballChoice, string name);
int foundName(Pokemon * dex, int numberPokemon, string name);
void searchDex(Pokemon *dex, int numRecords);


int main()
{

    /*"dex" will act as the name of your Pokemon array that will be created later on.*/
    
    ifstream pokeyFile;
    pokeyFile.open("poke.txt");
    if (!pokeyFile) 
    {
        cout << "Failed to open file!" << endl;
        return 1;
    }
    
    int numRecords;
    pokeyFile >> numRecords;
    
    Pokemon* dex = new Pokemon[numRecords];
    string line;
    getline(pokeyFile, line); // skip the first line
    
    for (int i = 0; i < numRecords; i++) 
    {
        pokeyFile >> dex[i].number;
        pokeyFile.ignore();
        getline(pokeyFile, dex[i].name,',');
        getline(pokeyFile, dex[i].type,',');
        getline(pokeyFile, dex[i].region,',');
        pokeyFile >> dex[i].catchPercentage;
        pokeyFile.ignore();
        getline(pokeyFile, dex[i].dexEntry);
    //    pokeyFile >> dex[i].numCaught;
    //    pokeyFile >> dex[i].numSeen;
    }
    
    pokeyFile.close();

    int ballSelection;
    int pokeBalls = 10;
    int greatBalls = 10;
    int ultraBalls = 10;
    
    int select;
    string menuChoice;
    string userName;
    string chosenDestination;
    cout << "What's your name, trainer? > ";
    getline(cin, userName);
    
    cout << "\nWelcome, " << userName << ", to the Programming I Safari Zone!";
    cout << "\nYou'll have 30 chances to catch Pokemon, make them count!";
    cout << "\nThe hunt will end when you choose or when you run out of Pokeballs.\n";
    cout << "\nWhich region would you like to visit?";
    cout << "\nEnter Kanto, Johto, Hoenn, or Sinnoh";
    cout << "\n> ";
    getline(cin, chosenDestination);
    
    while (true)
    {
     if (strcasecmp(chosenDestination.c_str(), "kanto") == 0)
        {
            cout << "Travelling to KANTO" << endl;
            cout << endl;
            helpMenu(chosenDestination, dex);
            break;
        }
        else if (strcasecmp(chosenDestination.c_str(), "johto") == 0) 
        {
            cout << "Travelling to JOHTO" << endl;
            cout << endl;
            helpMenu(chosenDestination, dex);
            break;
        }
        else if (strcasecmp(chosenDestination.c_str(), "hoenn") == 0) 
        {
            cout << "Travelling to HOENN" << endl;
            cout << endl;
            helpMenu(chosenDestination, dex);
            break;
        }
        else if (strcasecmp(chosenDestination.c_str(), "sinnoh") == 0)
        {
            cout << "Travelling to SINNOH" << endl;
            cout << endl;
            helpMenu(chosenDestination, dex);
            break;
        }
        else 
        {
            cout << "Which region would you like to visit?" << endl;
            cout << "Enter Kanto, Johto, Hoenn, or Sinnoh" << endl;
            cout << "> ";
            cin >> chosenDestination;
        }
    }
    do 
    {
        cout << "Selection > " << flush;
        cin >> menuChoice;
        cout << endl;
    
        select = 0;
    
        if (strcasecmp(menuChoice.c_str(), "hunt") == 0)
        {
            select = 1;
        }
        else if (strcasecmp(menuChoice.c_str(), "pokemon") == 0)
        {
            select = 2;
        }
        else if (strcasecmp(menuChoice.c_str(), "statistics") == 0)
        {
            select = 3;
        }
        else if (strcasecmp(menuChoice.c_str(), "inventory") == 0)
        {
            select = 4;
        }
        else if (strcasecmp(menuChoice.c_str(), "dex") == 0)
        {
            select = 5;
        }
        else if (strcasecmp(menuChoice.c_str(), "menu") == 0)
        {
            select = 6;
        }
        else if (strcasecmp(menuChoice.c_str(), "exit") == 0)
        {
            select = 7;
        }
    
        switch(select)
        {
          
        case 1: 
            ballSelection = hunt(dex, numRecords, chosenDestination, pokeBalls, greatBalls, ultraBalls);

            if (ballSelection == 1)
            {
                pokeBalls--;
            }
            if (ballSelection == 2)
            {
                greatBalls--;
            }
            if (ballSelection == 3)
            {
                ultraBalls--;
            }
            break;
        case 2: pokeSecured(dex, numRecords, userName);
            break;
        case 3: printStatistics(dex, numRecords);
            break;
        case 4: showInventory(pokeBalls, greatBalls, ultraBalls);
            break;
        case 5: searchDex(dex, numRecords);
            break;
        case 6: helpMenu(chosenDestination, dex);
            break;
        case 7: pokeSecured(dex, numRecords, userName);
            //return 0;
            exit(0);
            break;
        }
    }
    while (1);

    delete[] dex;
    
     return 0;
}


//help declaration
void helpMenu(string chosenDestination, Pokemon *dex)
{
    cout << "HUNT         (Go hunting for Pokemon!)" << endl;
    cout << "POKEMON      (See the Pokemon you've caught.)" << endl;
    cout << "STATISTICS   (See your catch statistics.)" << endl;
    cout << "INVENTORY    (See your current inventory.)" << endl;
    cout << "DEX NAME     (ex: DEX BULBASAUR would view Bulbasaur's Pokedex entry.)" << endl;
    cout << "MENU         (Reprint this menu.)" << endl;
    cout << "EXIT" << endl;
}


//hunt declaration
int hunt(Pokemon * dex, int numberPokemon, string chosenDestination, int pokeBalls, int greatBalls, int ultraBalls)
{
    int selection;
  
    //pokemon index ranges based on the region chosen
    //generate a random number between minimumNumber and maximumNumber inclusively
    int minimumNumber, maximumNumber;
    if (strcasecmp(chosenDestination.c_str(), "kanto") == 0)
    {
        minimumNumber = 1;
        maximumNumber = 151;
    }
    else if (strcasecmp(chosenDestination.c_str(), "johto") == 0) 
    {
        minimumNumber = 152;
        maximumNumber = 251;
    }
    else if (strcasecmp(chosenDestination.c_str(), "hoenn") == 0)
    {
        minimumNumber = 252;
        maximumNumber = 386;
    }
    else if (strcasecmp(chosenDestination.c_str(), "sinnoh") == 0)
    {
        minimumNumber = 387;
        maximumNumber = 493;
    }
    else 
    {
        
    }
    
    srand(time(0));
    int pokemonNumber = rand() % ((maximumNumber - minimumNumber) + 1) + minimumNumber;
    Pokemon pokemonName = dex[pokemonNumber - 1];
    cout << "A wild " << pokemonName.name << " has appeared!" << endl;
    cout << endl;
    int ballChoice = chooseBall(pokeBalls, greatBalls, ultraBalls);
    
    if(dex[pokemonNumber - 1].catchPercentage == 0)
    {
        cout << "Oh! That's a baby Pokemon! We'll take them to the daycare." << endl;
        cout << endl;
    }

    int pokemonMonitored = calculateCatch(dex[pokemonNumber - 1].catchPercentage, ballChoice, dex[pokemonNumber - 1].name);

    if (pokemonMonitored == 1) //pokemon caught and seen
    {
        (dex[pokemonNumber - 1].numberOfCaught)++;
        (dex[pokemonNumber - 1].numberOfSeen)++;
    }
    if (pokemonMonitored == 2) //not caught pokemon
    {
        (dex[pokemonNumber - 1].numberOfSeen)++;
    } 
    return ballChoice;   
}


//choosing a poke great or ultra ball declaration
int chooseBall(int pokeBalls, int greatBalls, int ultraBalls)
{
	int ballChoice = -1;
    bool valid= false;
    
    //available ball options to the player
	cout << "Choose a ball to throw:" << endl;
	cout << "1 - Poke Ball   (You have: " << pokeBalls << ")" << endl;
	cout << "2 - Great Ball  (You have: " << greatBalls << ")" << endl;
	cout << "3 - Ultra Ball  (You have: " << ultraBalls << ")" << endl;
	do
	{
	    cout << "Choose Ball > " << flush;
        cin >> ballChoice;
			
		//available ball options to the player
		//if (ballChoice >= 1 && ballChoice <= 3)
		if (ballChoice == 1) 
        {
           if(pokeBalls == 0)
           {
               valid = false;
               cout << "You have none of them!" << endl;
           }
           else
           {
               cout << "Threw a Poke Ball!";
               valid = true;
           }
           
        }
        else if (ballChoice == 2) 
        {
           if(greatBalls == 0)
           {
               valid = false;
               cout << "You have none of them!" << endl;
           }
           else
           {
               cout << "Threw a Great Ball!";
               valid = true;
           }
        }
        else if (ballChoice == 3) 
        {
           if(ultraBalls == 0)
           {
               valid = false;
               cout << "You have none of them!" << endl;
           }
           else
           {
               cout << "Threw a Ultra Ball!";
               valid = true;
           }
        }
        else
        {
            cin.clear();
			cin.ignore(100,'\n');
            cout << "Invalid Selection. Try again." << endl;   
            valid = false;	
        }
    }
    while (!valid);
    return (ballChoice);	
}


//chance calculations declaration
int calculateCatch(int basePercentage, int ballChoice, string name)
{
    int selection;
    int caughtAndSeen = 1;
    int notCaught = 2;
    
    
    if (ballChoice == 2) 
    {
        basePercentage = basePercentage + 20;
    }
    else if (ballChoice == 3) 
    {
        basePercentage = basePercentage + 40;
    }

    //the chance of catching the Pokemon
    int randomNum = rand() % 100 + 1;
    if (randomNum <= basePercentage) 
    
    {
      cout << "\nCongratulations! You caught " << name << "!" << endl;
      cout << endl;
      selection = caughtAndSeen;
    }
    else 
    {
        //pokemon ran away
        cout << endl;
        cout << name << " ran away. :-(" << endl;
        selection = notCaught;
    }
    return selection;
}


//pokemon function declaration
void pokeSecured(Pokemon *dex, int numberPokemon, string userName)
{
    cout << userName << "'s POKEMON:" << endl;
    bool caughtFound = false ;
    for (int i = 0; i < numberPokemon; i++) 
    {
      if ((dex[i].numberOfCaught) > 0)
        {
            caughtFound = true;
            cout << "no " << dex[i].number << "\t" << dex[i].name << endl;
        }
      // totalCaught = totalCaught + (dex[i].numberOfCaught); 
    }
        if (!caughtFound) 
        {
            cout << "You haven't caught any Pokemon yet!" << endl;
            cout << endl;
        }
}


//inventory declaration
void showInventory(int pokeBalls, int greatBalls, int ultraBalls)
{  //inventory reflects the values of each ball user has left over
    cout << "You have:" << endl;
    cout << pokeBalls << " PokeBalls" << endl;
    cout << greatBalls << " Great Balls" << endl;
    cout << ultraBalls << " Ultra Balls" << endl;
    cout << endl;
}


//dex entry declaration
void searchDex(Pokemon *dex, int numRecords)
{ //search array for pokemon for pokemon the user wants to look up capitalization doesn't matter 

    string myDex, name;
    cin >> name;
   //change to uppercase
    for (int i = 0; i < name.length(); i++)
    {
        name[i] = toupper(name[i]);
    }
    
    
    int index = foundName(dex, numRecords, name);
    if (index)
    {
        cout << "Name: " << dex[index-1].name << endl;
        cout << "Type: " << dex[index-1].type << endl;
        cout << dex[index-1].dexEntry << endl;
        cout << endl;
    } 
    else
    {
        cout << "No Pokedex entry for " << name << endl;
    }
}


//search function for dex function declaration
int foundName(Pokemon * dex, int numPokemon, string name)
{
    int value = 0;
    for (int i = 0; i < numPokemon; i++)
    {
        // if (strcmp(dex[i].name.c_str(), name.c_str()) == 0)
       // if(dex[i].name.compare(name) == 0)
        if (strcasecmp(dex[i].name.c_str(), name.c_str()) == 0)
        {
          value = dex[i].number;  
          //cout << "value = " << value << endl;
        }
    }
  return value;
}


//gettin the stats
void printStatistics(Pokemon* dex, int numPokemon)
{
    int totalCaught = 0;
    int totalSeen = 0;
    
    for (int i = 0; i < numPokemon; i++) 
    {
        totalCaught = totalCaught + (dex[i].numberOfCaught);
        totalSeen = totalSeen + (dex[i].numberOfSeen);
    }
    
    double catchRate = (double)totalCaught / totalSeen * 100;
    if(totalSeen == 0)
    {
        catchRate = 0;
    }
    
    cout << "Total Pokemon caught: " << totalCaught << endl;
    cout << "Total Pokemon Seen: " << totalSeen << endl;
    cout << "Overall Catch Rate: " << fixed << setprecision(2) << catchRate << "%" << endl;
    cout << endl;
}