#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <string_view>

class ChessBoard;

class Player {
protected:
    inline static constexpr std::string_view pieceValue = "KQRNBP";
    bool isWhite;
    int pieceRemaining;

public:
    explicit Player(bool whiteSide, int startingPieces = 16);
    virtual ~Player() = default;

    bool isWhiteSide() const;
    int getRemainingPieces() const;
    void setRemainingPieces(int count);

    virtual bool isComputer() const = 0;
};

class HumanPlayer final : public Player {
public:
    explicit HumanPlayer(bool whiteSide, int startingPieces = 16);
    bool isComputer() const override;
};

class ComputerPlayer final : public Player {
    int level; // e.g., 1..4 based on validGame ("computer1"..)

    std::string findThreat(const ChessBoard& board) const;
    std::string findTarget(const ChessBoard& board) const;

public:
    ComputerPlayer(bool whiteSide, int aiLevel, int startingPieces = 16);
    bool isComputer() const override;
    int getLevel() const;
    std::string sendMove(const ChessBoard& board) const;
};

#endif