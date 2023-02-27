/********************************************************************************************************************************************************
    Maria Hernandez 
    COSC202
    09/21/2022
    CardDeck.cpp
    This program allows one user (player) to play a blackjack game with a programmed dealer. In this .cpp file, we implement the functions
    contained in the CardDeck interface.
***********************************************************************************************************************************************************/

#include <iostream> 
#include <algorithm> // std::random_shuffle
#include <ctime>     // std::time   
#include <cstdlib>   // std::rand, std::srand
#include "CardDeck.h"

using namespace std; 

//  We implement the non-default constructor which dynamically allocate the deck on the heap, initialize it, and initialize its size. 
CardDeck::CardDeck(int n) {
    size = n; 
    deck = new int[size]; 
    int value = 1; 
  
    //  If the size passed to the function is 10, we initialize the deck with values from 2 - 11 since all aces are 11. 
    if (n <= 10) {
        for (int i = 0; i < n; i++) {
            deck[i] = (i%10) + 2; 
        }
    }

    //  Otherwise, we assume that is the fall back value (52). We set up our first 4 cards to 11 - since Aces are only 11. Then, we initialize four cards for each value from 2 - 9. 
    //  Finally, we set sixten cards equal to 10, given that 10, Jack, Queen, and King are all worth 10. 
    else {
        for (int i = 0; i < n; i+=1) {  
            if (i >= 0 && i < 4) {
                deck[i] = 11; 
            }
            else if (i >= 4 && i <= 35) {  
                if (i%4 == 0) {
                    value += 1; 
                }
                deck[i] = value; 
            } 
            else {
                deck[i] = 10; 
            }    
        }
    }
}

//  We implement the copy constructor that initializes the current object's deck to the values of another 'obj' deck. 
CardDeck::CardDeck(const CardDeck &obj) {
    size = obj.size; 
    for (int i = 0; i < size; i++) {
        deck[i] = obj.deck[i];
    }
}

//  We implement the method to overload the assignment operator so that we can copy a given object's deck values into the current object. 
const CardDeck &CardDeck::operator=(const CardDeck &obj) {
    //  First, we prevent self assignment. 
    if (&obj != this) {
        //  If the current object's size is less than the size of the object being passed, we deallocate the memory that our current object is pointing at, resize our current object 
        //  to the size of the object being passed and allocate new memory for our deck. 
        if (size != obj.size) {
            delete [] deck;
            size = obj.size; 
            deck = new int[size];
        }
        // Then, we set each index of the current object's deck array equal to the value stored in the corresponding index of the obj.deck array. 
        for (int i = 0; i < size; i++) {
            deck[i] = obj.deck[i];
        }
    }
    
    //  Dereference this pointer and return a reference to the current object. 
    return *this; 
}

//  We implement the 'getSize()' method that returns the current deck's size. 
int CardDeck::getSize() {
    return size; 
}

//  We implement the 'shuffle()' method that shuffles the deck using the random_shuflle algorithm of the STL. 
void CardDeck::shuffle() {
    std::random_shuffle(&deck[0], &deck[size]); 
}

//  We implement the 'display()' method that displays each element of the current deck to the console. 
void CardDeck::display() {
    for(int i = 0; i < size; i++) {
        cout << deck[i] << " "; 
    }
    cout << endl; 
}

//  We implement the 'deal()' method that deals a card to the player or dealer each time is called.  
void CardDeck::deal(int *&hand, int size) { 

    //  If the hand's size is greater than one, we create a new temporary pointer that allocates [size + 1] continuos memory on the heap 
    //  (size refers to the size of either the dealer or player's hand depending on who is calling the function). 
    if (size >= 1) {
        int *new_hand = new int [size + 1]; 
    
        //  We then copy all the values stored in hand into the new temporary pointer. 
        for (int i = 0; i < size; i++) { 
            new_hand[i] = hand[i]; 
        }

        //  We assign the card at the top (leftmost position) of our current deck to the last index of our temporary pointer.  Then, we deallocate the memory 
        //  the current hand is pointing at, to avoid memory leaks, and assign the temporary pointer to the current hand pointer. 
        new_hand[size] = deck[(this->size)-1];
        delete[] hand;
        hand = new_hand;  
    }

    //  Otherwise, if the current hand's size is less than one, we initialize our hand to the card on the top (leftmost position) of our current deck.
    else {
        hand = new int [size + 1];
        hand[size] = deck[(this->size)-1];
    }

    //  To remove the card dealt from our deck, we create a temporary pointer with size (current deck size - 1), copy the values over from our current 
    //  deck to the temporary pointer, deallocate the memory our current deck is pointing at, assign the temporary pointer to the current deck and 
    //  decrease the deck's size by 1. 
    int *new_deck = new int [(this->size) - 1]; 
    for (int i = 0; i < (this->size)-1; i++) { // copy desk
        new_deck[i] = deck[i]; 
    }
    delete [] deck; 
    deck = new_deck; 
    this->size -= 1; 
}

//  We implement the deconstructor that deallocate all the memory dynamically allocated by a given variable once this variable goes out of scope. 
CardDeck::~CardDeck() {
    delete [] deck; 
}

//  We implement the 'score()' method that calculates and returns the score of the current hand. 
int CardDeck::score(int *&hand, int size) {
    int score = 0;
    for(int i = 0; i < size; i++) {
        score += hand[i];
    }
    return score; 
}
