/********************************************************************************************************************************************************
    Maria Hernandez 
    COSC202
    09/21/2022
    main.cpp
    This program allows one user (player) to play a blackjack game with a programmed dealer. Both will work off of the same deck of 52 cards, 
    so no cards will be duplicated between the dealer and player. Each card has a single value from 2 to 11. Cards 2 to 10 have respective values of 2 to 10 points. 
    There are four cards for each value from 2 - 9 and sixten cards equal to 10, given that 10, Jack, Queen, and King are all worth 10. 
    In this version of blackjack Aces are always 11. The point of the game is to get to the value 21 without going over. If either the player or the dealer gets 21, 
    the one who gets it automatically wins. If a score is above 21, it is called a "bust" and whoever has a bust automatically loses.
    The player has two options, either 'h' or 's' (case sensitive).  If the player hits, the dealer hands them another card. Once the player stands, the dealer hits 
    if the total score of their cards is less than 17. If the player and dealer have not gone above 21, then the scores are compared. Whoever has the higher score wins. 
    If both have the same score, they tie in a "draw". This program gives the user the option of keep playing as many times as they want, and updates the 
    number of times each one has won as well as the number of ties.
***********************************************************************************************************************************************************/

#include <iostream> 
#include "CardDeck.h"
// #include "CardDeck.cpp"

using namespace std; 

int main () {
    //  We create an instance of the CardDeck class and pass a size of 10 to the non-default constructor. 
    CardDeck *deck; 
    deck = new CardDeck(10); 
    deck->display(); 
    deck->shuffle();
    deck->display(); 

    //  Then, we deallocate the deck and instantiate a new deck with default value (52).
    delete deck; 
    printf("\n");
    deck = new CardDeck(); 
    deck->shuffle();

    //  We create two pointers (one to store the player's hand and another to store the dealer's hand).
    int *player_hand = NULL;
    int *dealer_hand = NULL; 
    int size_player_hand = 0, size_dealer_hand = 0;

    //  We initialize the won games of the player and dealer to 0 as well as the number of ties.
    int player_win = 0, dealer_win = 0, tie = 0; 
    char choice, hit_stand; 

    do {
        // We check for fewer than 15 cards.
        if (deck->getSize() < 15) {
            delete deck; 
            deck = new CardDeck(); 
            for (int i = 0; i <(rand() % 10) + 1; i++) {
                deck->shuffle(); 
            }
        }
        
        //  We print the board indicating how many times the player and dealer have won and how many ties.
        printf("--------------------\n"); 
        printf("player [%d] | dealer [%d] | tie [%d]\n", player_win, dealer_win,tie); 
        printf("--------------------\n"); 

        //  We draw the first hand to the dealer (first two cards).
        for (int i = 0; i < 2; i++) { 
            deck->deal(dealer_hand,i);
            size_dealer_hand++; 
        }

        //  We draw the first hand to the player (first two cards).
        for (int i = 0; i < 2; i++) { 
            deck->deal(player_hand, i); 
            size_player_hand++;  
        }
    
        //  We print the dealer and player's initial hand. 
        cout << "dealer: "; 
        for (int i = 0; i < size_dealer_hand; i++) {
            cout << dealer_hand[i] << " "; 
        }
        printf("(%d)\n",deck->score(dealer_hand, size_dealer_hand));

        cout << "player: "; 
        for (int i = 0; i < size_player_hand; i++) {
            cout << player_hand[i] << " "; 
        }
        printf("(%d)\n",deck->score(player_hand, size_player_hand));
        cout << endl; 

        //  Prompt user for a response.
        cout << "(h)it/(s)tand: "; 
        cin >> hit_stand; 
        //  If user enters 'h', the player will hit until either deciding to stand or until their score is 21 or more.
        while (hit_stand == 'h') {
            //  We deal a new card to the player, increase the size of their hand, and display their new hand and score.
            deck->deal(player_hand, size_player_hand);
            size_player_hand++;       
            cout << "player: ";
            for (int i = 0; i < size_player_hand; i++) {
                cout << player_hand[i] << " "; 
            }
            printf("(%d)\n",deck->score(player_hand, size_player_hand));

            if(deck->score(player_hand, size_player_hand) >= 21) break; 

            cout << "(h)it/(s)tand: "; 
            cin >> hit_stand; 
        }

        // If the player enters 's' is the dealer's turn.
        if (hit_stand == 's') {
            //  We display the dealer's hand and score.
            cout << "dealer: ";
            for (int i = 0; i < size_dealer_hand; i++) {
                cout << dealer_hand[i] << " "; 
            }
            printf("(%d)\n",deck->score(dealer_hand, size_dealer_hand)); 

            //  Dealer will draw cards until their score is 17 or greater.
            while (deck->score(dealer_hand, size_dealer_hand) < 17) {
                //  We deal a new card to the dealer, increase the size of their hand, and display their new hand and score.
                deck->deal(dealer_hand, size_dealer_hand);
                size_dealer_hand++;
                cout << "dealer: ";
                for (int i = 0; i < size_dealer_hand; i++) {
                    cout << dealer_hand[i] << " "; 
                }
                printf("(%d)\n",deck->score(dealer_hand, size_dealer_hand)); 
            }
        }

        //  Finally, we decide the final result and display a message to the user indicating it and update the results (who won) to show in the board
        //  if the user decides to keep playing.
        if (deck->score(player_hand, size_player_hand) > 21) {
            printf("Player busts, dealer wins! \n");
            dealer_win++;
        }
        else if (deck->score(dealer_hand, size_dealer_hand) > 21) {
            printf("Dealer busts, player wins! \n");
            player_win++;
        }
        else if (deck->score(player_hand, size_player_hand) > deck->score(dealer_hand, size_dealer_hand) || deck->score(player_hand, size_player_hand) == 21) { 
            printf("Player wins! \n");
            player_win++;
        }
        else if (deck->score(dealer_hand, size_dealer_hand) > deck->score(player_hand, size_player_hand) || deck->score(dealer_hand, size_dealer_hand) == 21) {
            printf("Dealer wins! \n");
            dealer_win++;
        }
        else if (deck->score(dealer_hand, size_dealer_hand) == deck->score(player_hand, size_player_hand)) { 
            printf("Player and dealer draw. \n");
            tie++;
        }   

        //  We give the option to the user to keep playing.
        printf("\nDo you wish to continue? (y/n): ");
        cin >> choice; 
        cout << endl; 

        //  If the user decides to keep playing, we reset the hands of both player and dealer and the size of their hands. 
        if (choice == 'y') {
            player_hand = NULL; 
            dealer_hand = NULL; 
            size_player_hand = 0; 
            size_dealer_hand = 0; 
            continue; 
        } else break; 

    } while (true);
}
