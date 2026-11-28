#include "Player.h"
#include "ChessBoard.h"

Player::Player(bool whiteSide, int startingPieces)
    : isWhite(whiteSide), pieceRemaining(startingPieces) {}

bool Player::isWhiteSide() const {
    return isWhite;
}

int Player::getRemainingPieces() const {
    return pieceRemaining;
}

void Player::setRemainingPieces(int count) {
    pieceRemaining = count;
}

HumanPlayer::HumanPlayer(bool whiteSide, int startingPieces)
    : Player(whiteSide, startingPieces) {}

bool HumanPlayer::isComputer() const {
    return false;
}

ComputerPlayer::ComputerPlayer(bool whiteSide, int aiLevel, int startingPieces)
    : Player(whiteSide, startingPieces), level(aiLevel) {}

bool ComputerPlayer::isComputer() const {
    return true;
}

int ComputerPlayer::getLevel() const {
    return level;
}

std::string ComputerPlayer::findThreat(const ChessBoard& /*board*/) const {
    // TODO: Return coordinate of a threatened friendly piece, or "" if none
    return "";
}

std::string ComputerPlayer::findTarget(const ChessBoard& /*board*/) const {
    // TODO: Return coordinate of a capturable enemy piece, or "" if none
    return "";
}

std::string ComputerPlayer::sendMove(const ChessBoard& /*board*/) const {
    // TODO: Generate a valid "e2 e4"-style move using pieceValue, findThreat, findTarget
    return "";
}

void ComputerPlayer::generateMoves(); // Generate every possible legal move