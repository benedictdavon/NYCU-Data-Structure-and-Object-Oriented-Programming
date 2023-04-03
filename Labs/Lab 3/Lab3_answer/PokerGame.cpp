#include "PokerGame.h"

PokerGame::PokerGame() {
	maxNumber = 0;
	type = HighCard;
	maxNumber = 0;
}

void swapNum(int* num1, int* num2) {
	int temp;
	temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

void PokerGame::distribute(bool usedCards[52]) {
	//TO_DO: Random generate five cards to player
	//Hint: Use usedCards to record which card have been distributed
	vector<int> cards;
	int rnd;
	for (int i = 0; i < 5; i++) {
		do {
			rnd = rand() % 51;
		} while (usedCards[rnd]);

		usedCards[rnd] = true;
		cards.push_back(rnd);
	}

	set(cards);
}

void PokerGame::set(vector<int> cards) {
	//TO_DO: Set the cards to player
	playerCards = cards;
	sortCards();
}

void PokerGame::printCards() {
	cout << "Player cards:" << endl;
	/*
	for (int i = 0; i < 5; i++) {
		cout << playerCards[i] << " ";
	}*/
	for (int i = 0; i < 5; i++) {
		if (playerCards[i] / 13 == 0)
			cout << "C";
		if (playerCards[i] / 13 == 1)
			cout << "D";
		if (playerCards[i] / 13 == 2)
			cout << "H";
		if (playerCards[i] / 13 == 3)
			cout << "S";
		
		cout << playerCards[i] % 13 + 1 << " ";
	}

	cout << endl;
}

void PokerGame::sortCards() {
	//TO_DO: Sort the cards accroding to their number
	int smallest = 0;
	for (int i = 0; i < 5; i++) {
		smallest = i;
		for (int j = i; j < 5; j++)
			if (playerCards[j] % 13 < playerCards[smallest] % 13)
				smallest = j;

		swapNum(&playerCards[i], &playerCards[smallest]);
	}
}

void PokerGame::evaluate() {
	sortCards();
	if (this->isStraight() && this->isFlush()) {
		type = StraightFlush;
	}
	else if (this->isFourOfKind()) {
		type = FourOfKind;
	}
	else if (this->isFullHouse()) {
		type = FullHouse;
	}
	else if (this->isFlush()) {
		type = Flush;
	}
	else if (this->isStraight()) {
		type = Straight;
	}
	else if (this->isThreeOfKind()) {
		type = ThreeOfKind;
	}
	else if (this->isTwoPairs()) {
		type = TwoPairs;
	}
	else if (this->isOnePair()) {
		type = OnePair;
	}
	else {
		type = HighCard;
		//TO_DO: Set the maxNumber
		maxNumber = this->playerCards[4];
	}
}

int PokerGame::getType() {
	return type;
}

int PokerGame::getMaxNumber() {
	return maxNumber;
}

void PokerGame::compare(int type_, int maxNumber_) {
	//TO_DO: Compare the type and output who is winner
	//Compare the type of card first. If types are the same, compare which is max the number of card.
	//If the max number is the same, compare the suit of card.
	if (type < type_) {
		cout << "Player2 win" << endl;
		return;
	}
	else if (type > type_){
		cout << "Player1 win" << endl;
		return;
	}
	
	if (type == type_ && maxNumber % 13 != maxNumber_ % 13) {
		cout << "Maxnum1 : " << maxNumber << endl << "Maxnum2 : " << maxNumber_ << endl;
		if (maxNumber % 13 < maxNumber_ % 13)
			cout << "Player2 win" << endl;
		else if (maxNumber % 13 > maxNumber_ % 13)
			cout << "Player1 win" << endl;
	} else {
		if (maxNumber / 13 < maxNumber_ / 13)
			cout << "Player2 win" << endl;
		else
			cout << "Player1 win" << endl;
	}
}

bool PokerGame::isStraight() {
	//TO_DO: Check whether the hand of cards is Straight or not and set the maxNumber
	for (int i = 0; i < 4; i++) {
		if (playerCards[i] % 13 + 1 != playerCards[i + 1] % 13)
			return false;
	}
	maxNumber = playerCards[4];

	return true;
}

bool PokerGame::isFlush() {
	//TO_DO: Check whether the hand of cards is Flush or not and set the maxNumber
	if (playerCards[0] / 13 != playerCards[4] / 13)
		return false;

	for (int i = 0; i < 4; i++) {
		if (playerCards[i] / 13 != playerCards[i + 1] / 13)
			return false;
	}
	maxNumber = playerCards[4];
	return true;
}


// check if a value is in vector arr
bool isInVector(int value, vector<int> arr) {
	for (int i = 0; i < arr.size(); i++)
		if (value == arr[i])
			return true;

	return false;
}

bool PokerGame::isFourOfKind() {
	//TO_DO: Check whether the hand of cards is FourOfaKind or not and set the maxNumber
	for (int i = 0; i < 2; i++) {
		if (playerCards[i] % 13 == playerCards[i + 1] % 13 && playerCards[i + 1] % 13 == playerCards[i + 2] % 13 && playerCards[i + 2] % 13 == playerCards[i + 3] % 13) {
			maxNumber = playerCards[i + 3];
			return true;
		}	
	}

	return false;
}

bool PokerGame::isFullHouse() {
	//TO_DO: Check whether the hand of cards is FullHouse or not and set the maxNumber
	if (playerCards[3] % 13 == playerCards[4] % 13) {
		if (playerCards[0] % 13 == playerCards[1] % 13 && playerCards[1] % 13 == playerCards[2] % 13) {
			maxNumber = playerCards[2];
			return true;
		}
	}
	
	if (playerCards[0] % 13 == playerCards[1] % 13) {
		if (playerCards[2] % 13 == playerCards[3] % 13 && playerCards[3] % 13 == playerCards[4] % 13) {
			maxNumber = playerCards[4];
			return true;
		}
	}

	return false;
}

bool PokerGame::isThreeOfKind() {
	//TO_DO: Check whether the hand of cards is ThreeOfaKind or not and set the maxNumber
	for (int i = 0; i < 3; i++) {
		if (playerCards[i] % 13 == playerCards[i + 1] % 13 && playerCards[i + 1] % 13 == playerCards[i + 2] % 13) {
			maxNumber = playerCards[i + 2];
			return true;
		}
	}
	
	return false;
}

bool PokerGame::isTwoPairs() {
	//TO_DO: Check whether the hand of cards is TwoPairs or not and set the maxNumber
	int totPair = 0, bigger = 0;
	for (int i = 0; i < 4; i++) {
		if (playerCards[i] % 13 == playerCards[i + 1] % 13) {
			totPair++;
			bigger = (playerCards[i + 1] > bigger) ? playerCards[i + 1] : bigger;
			//cout << "Bigger: " << bigger << endl << "Playercard: " << playerCards[i + 1] << endl;
		}
	}

	if (totPair == 2) {
		maxNumber = bigger;
		return true;
	}
	return false;
}

bool PokerGame::isOnePair() {
	//TO_DO: Check whether the hand of cards is OnePair or not and set the maxNumber
	int totPair = 0, bigger = 0;
	for (int i = 0; i < 4; i++) {
		if (playerCards[i] % 13 == playerCards[i + 1] % 13) {
			totPair++;
			bigger = (playerCards[i + 1] > bigger) ? playerCards[i + 1] : bigger;
		}
	}

	if (totPair == 1) {
		maxNumber = bigger;
		return true;
	}
	return false;
}