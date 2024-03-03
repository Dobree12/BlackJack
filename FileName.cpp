#include <iostream>
#include<string>
#include <random>
using namespace std;

//random function
    void generateNumber(int &random) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 52);
        random = dis(gen);
    }


    bool isNumber(const string& s){
    for (char c : s)
    {
        if (!isdigit(c))
            return false;
     }
     return true;
    }

    void generate_deck(string deck[], string values[], string colors[], int cards_score[]) {
        int q=0;
        int k=0;
        
        for (int i = 0; i < 4; i++) // colors
            for (int j = 0; j < 13; j++) //values
            {
                deck[k++] = values[j] + colors[i];
                if (j == 12)
                    //if (k > 0 && pachet[k - 1][0] == 'A')
                    //card_score[q++] = 1;
                    //else
                    cards_score[q++] = 11; // A A it s 22
                else if (j > 8)
                    cards_score[q++] = 10; // 10 J Q K
                else
                    cards_score[q++] = j + 2; //rest of the deck
            }

    }

    void get_user_balance(float &balance) {
        string input;
         do {
            cout << "Please insert the amount you want to play: " << "$";
            cin >> input;

            if (!isNumber(input)) {
                cout << "Invalid input. Please enter a number." << endl;
            }
            else {
                int balanceAmount = stoi(input);

                if (balanceAmount <= 0) 
                    cout << "Bet should be higher than 0!" << endl;
                
                else {
                    balance = balanceAmount;
                    return;
                }
            }
        } while (true);
    }
    
    void get_user_bet(int& bet, float balance) {
        string input;
        do {
            cout << "How much you want to bet?" << endl << "$";
            cin >> input;

            if (!isNumber(input)) {
                cout << "Invalid input. Please enter a number." << endl;
            }
            else {
                int betAmount = stoi(input);
                if (betAmount <= 0) {
                    cout << "Bet should be higher than 0!" << endl;
                }
                else if (betAmount > balance) {
                    cout << "Bet is higher than your current balance. Please select a correct amount!" << endl;
                }
                else {
                    bet = betAmount;
                    return;
                }
            }
        } while (true);
    }


    void dealer_first_card(string deck[],string dealer_cards[],int &nr_cards_dealer,int &dealer_score,int cards_score[]) {
        int random;
        cout << "--------------------------------------------------\n";
        //generate dealer first hand
        generateNumber(random);
        cout << "Dealer:| " << deck[random] << " | " << endl;

        dealer_cards[nr_cards_dealer++] = deck[random]; //dealer first hand
        dealer_score += cards_score[random];
    }
    void player_hand(int &player_score, int cards_score[],string deck[],string player_cards[], string player_cards_score[]) {
        int random;
        cout << "You:";
        for (int i = 0; i < 2; i++)
        {
            generateNumber(random);
            player_score += cards_score[random];
            cout << " | " << deck[random] << " | ";
            if (i == 0)
            {
                player_cards[0] = deck[random];// player first card
                player_cards_score[0] = cards_score[random];
            }
            else
            {
                player_cards[1] = deck[random]; //player second card
                player_cards_score[1] = cards_score[random];
            }
        }
        cout << "\nYour score: " << player_score;
        cout << "\n--------------------------------------------------\n";

    }
    void hit_or_stand(float &balance,int &bet, int &player_score, int cards_score[], string player_cards[],int nr_carti,string deck[],int &dealer_score,string dealer_cards[], int &nr_cards_dealer) {
        string option;
        int random;
        do
        {
            cout << "Hit or stand (H / S): ";
            cin >> option;
            cout << endl;

            if (option != "H" && option != "h" && option != "S" && option != "s")
            {
                cout << "Invalid option. Please enter H or S." << endl;
            }
        } while (option != "H" && option != "h" && option != "S" && option != "s");

        while (option == "H" || option == "h")
        {   //generate more cards for player
            generateNumber(random);
            player_score += cards_score[random];
            player_cards[nr_carti++] = deck[random];
            
            //print player's cards
            cout << "You: ";
            for (int j = 0; j < nr_carti; j++)
                cout << player_cards[j] << " | ";

            cout << "\nScor: " << player_score << endl;

            //check for bust
            if (player_score > 21)
            {
                cout << "Bust!" << endl;
                balance -= bet;
                break;
            }
            cout << "--------------------------------------------------\n";
            cout << "Hit or stand ( H / S ): ";
            cin >> option;
            cout << "\n";
        }
        if (option == "S" || option == "s")
        {
            
            while (dealer_score < 17)
            {
              // generate dealer's second hand
                generateNumber(random);
                dealer_score += cards_score[random];
                dealer_cards[nr_cards_dealer++] = deck[random];
                //check for dealer's blackjack
                if (dealer_score == 21 && nr_cards_dealer == 2)
                { 
                    cout << "Blackjack for Dealer!" << endl;
                    for (int j = 0; j < nr_cards_dealer; j++)
                        cout << "| " << dealer_cards[j] << " | ";
                    break;
                }
                cout << "Dealer: ";
               //print dealer's cards
                for (int j = 0; j < nr_cards_dealer; j++)
                    cout << "| " << dealer_cards[j] << " | ";
                cout << "\nScor dealer: " << dealer_score << endl;
            }
        }

    }
    void play_blackjack() {
        float balance;
        int bet;
        int random;
        int player_score = 0; //
        int dealer_score = 0;
        int nr_player_cards = 2;
        int nr_cards_dealer = 0;
        int cards_score[55]; // retain each card value
        string option;
        string deck[60];
        string player_cards[10];
        string dealer_cards[10];
        string player_cards_score[10];
        string colors[4] = { "of Heart","of Club","of Spade","of Diamond" };
        string values[14] = { "2 ","3 ","4 ","5 ","6 ","7 ","8 ","9 ","10 ","J ","Q ","K ","A " };
        get_user_balance(balance);
        generate_deck(deck, values, colors, cards_score);

        while (balance)
        {
            get_user_bet(bet,balance);
            
            dealer_first_card( deck, dealer_cards, nr_cards_dealer, dealer_score, cards_score);
            player_hand(player_score, cards_score, deck, player_cards, player_cards_score);

            if (player_score == 21)
            {
                cout << "Blackjack!" << endl;
                balance += 1.5 * bet;
                // play again?
            }
            else
            {
                while (player_score < 21)
                {
                    hit_or_stand(balance,bet, player_score, cards_score, player_cards, nr_player_cards, deck, dealer_score, dealer_cards, nr_cards_dealer);

                    if (player_score > dealer_score && player_score < 21)
                    {
                        cout << "You won!" << endl;
                        balance += bet;
                        break;
                    }
                    else if (dealer_score > 21)
                    {
                        cout << "Congrats, the dealer bust." << endl; 
                        balance += bet;
                        break;
                    }
                    else if (player_score < dealer_score && dealer_score < 22)
                    {
                        cout << "You lost, dealer have: " << dealer_score << endl;
                        balance -= bet;
                        break;
                    }
                    else if (player_score == dealer_score)
                    {
                        cout << "Push!" << endl;
                        break;

                    }
                }
            }
            //resetam scorurile
            player_score = 0;
            dealer_score = 0;
            nr_cards_dealer = 0;

            cout << "--------------------------------------------------\n";
            cout << "Your balance is:$ " << balance << endl;
            if (balance == 0)
            {
                cout << "You lost all your money!";
                exit(0);
            }
            else
            do
            {
                cout << "Do you want to continue playing? (Y/N): ";
                cin >> option;

                if (option == "Y" || option == "y")
                {
                    system("cls");
                    cout << "Balance: $" << balance << endl;
                    break;
                }
                else if (option == "N" || option == "n")
                {
                    cout << "Thanks for playing, have a great day!";
                    exit(0);
                }
                else
                {
                    cout << "Invalid option. Please enter Y or N." << endl;
                }
            } while (option != "N" && option != "n");
        }

    }

int main()
{
    play_blackjack();

    return 0;

}
