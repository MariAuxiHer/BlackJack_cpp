/********************************************************************************************************************************************************
    Maria Hernandez 
    COSC202
    09/21/2022
    CardDeck.h
    This program allows one user (player) to play a blackjack game with a programmed dealer. In this .h file, we develop the interface 
    for the CardDeck class.
***********************************************************************************************************************************************************/

#ifndef CardDeck_H 
#define CardDeck_H 

#include <iostream>

/* 
    The CardDeck class contains two private data members: a pointer to integers 'deck', which will allow us to dynamically allocate the deck on the heap, and an integer 'size' 
    which will store the size of the deck. It also contains a non-default constructor, a copy constructor, a destructor to deallocate memory once a variable pointing to that memory
    goes out of scope, and five other public member functions that will return the size of the current deck, shuffle the deck, display the deck in the console, deal cards to player 
    and dealer, and calculate the score each time a player or dealer draws a new cards.
*/ 

class CardDeck {
private: 
    int *deck;
    int size;
public: 
    CardDeck(int n = 52); 
    CardDeck(const CardDeck &obj); 
    ~CardDeck(); 
    const CardDeck &operator=(const CardDeck &obj);
    int getSize(); 
    void shuffle(); 
    void display(); 
    void deal(int *&hand, int size); 
    int score(int *&hand, int size); 
};

#endif