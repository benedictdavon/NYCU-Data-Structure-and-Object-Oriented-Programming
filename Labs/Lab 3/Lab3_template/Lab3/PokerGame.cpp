#include "PokerGame.h"

PokerGame::PokerGame() {
	//TO_DO: initial constructor
}

void PokerGame::distribute(bool usedCards[52]) {
	//TO_DO: Random generate five cards to player
	//Hint: Use usedCards to record which card have been distributed
}

void PokerGame::set(vector<int> cards) {
	//TO_DO: Set the cards to player
}

void PokerGame::printCards() {
	cout << "Player cards:" << endl;
	for (int i = 0; i < 5; i++) {
		//TO_DO: Print the player's cards.
		// For example: "C1" "S2" "H3" ...
	}

	cout << endl;
}

void PokerGame::sortCards() {
	//TO_DO: Sort the cards accroding to thier number
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
}

bool PokerGame::isStraight() {
	//TO_DO: Check whether the hand of cards is Straight or not and set the maxNumber
	return false;
}

bool PokerGame::isFlush() {
	//TO_DO: Check whether the hand of cards is Flush or not and set the maxNumber
	return false;
}

bool PokerGame::isFourOfKind() {
	//TO_DO: Check whether the hand of cards is FourOfaKind or not and set the maxNumber
	return false;
}

bool PokerGame::isFullHouse() {
	//TO_DO: Check whether the hand of cards is FullHouse or not and set the maxNumber
	return false;
}

bool PokerGame::isThreeOfKind() {
	//TO_DO: Check whether the hand of cards is ThreeOfaKind or not and set the maxNumber
	return false;
}

bool PokerGame::isTwoPairs() {
	//TO_DO: Check whether the hand of cards is TwoPairs or not and set the maxNumber
	return false;
}

bool PokerGame::isOnePair() {
	//TO_DO: Check whether the hand of cards is OnePair or not and set the maxNumber
	return false;
}