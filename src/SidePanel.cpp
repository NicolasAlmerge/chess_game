#include "../include/SidePanel.hpp"

void SidePanel::addMove(MoveList& moves, Move& move) {
    int moveListSize = moves.getMoveList().size();
    bool isPair = moveListSize % 2 != 0;
    string text;

    text = parseMove(move, (moveListSize/2) + 1, isPair);
    textBoxes.emplace_back(text);
}

pair<char,int> SidePanel::findLetterCoord(coor2d target) {
    char letter = letters.at(target.first);
    return make_pair(letter, 8-target.second);
}

string SidePanel::parseMove(Move& move, int moveNumber, bool showNumber) {
    string text = (showNumber)? to_string(moveNumber) + "." : " ";
    MoveType moveType = move.getMoveType();

    // side cases
    if (moveType == MoveType::CASTLE_KINGSIDE) {
        return text + "0-0";
    }
    if (moveType == MoveType::CASTLE_QUEENSIDE) {
        return text + "0-0-0";
    }

    coor2d coord = move.getTarget();
    pair<char, int> letterCoord = findLetterCoord(coord);
    string letterCoordString = (1, letterCoord.first) + to_string(letterCoord.second);;

    switch(move.getSelectedPiece()->getType()) {
        case PieceType::PAWN:
            // TODO fix promotion
            if(moveType == MoveType::CAPTURE || moveType == MoveType::ENPASSANT){
                text += string(1, letters.at(coord.first)) + "x";
                return text + letterCoordString;
            }
            break;
        case PieceType::KNIGHT:
            text += "N";
            break;
        case PieceType::BISHOP:
            text += "B";
            break;
        case PieceType::ROOK:
            text += "R";
            break;
        case PieceType::QUEEN:
            text += "Q";
            break;
        case PieceType::KING:
            text += "k";
            break;
    }
    return text + string((moveType == MoveType::CAPTURE)? "x" : "") + letterCoordString;
}

void SidePanel::drawMoves() {
    if(textBoxes.size() == 0 ) return; // no moves added yet, return

    Font font;
    if (!font.loadFromFile("../assets/fonts/Arial.ttf")) return;

    for(auto& moveText : textBoxes) {
        Text text;
        RectangleShape rectangle;

        text.setString(moveText);
        text.setFont(font);
        text.setCharacterSize(25);
        text.setStyle(Text::Bold);
        text.setFillColor(Color::Black);

        FloatRect textBounds = text.getGlobalBounds();

        if(WINDOW_SIZE + m_xPos + textBounds.width >= 2*WINDOW_SIZE-BORDER_SIZE){
            // Go to next row
            m_yPos += (20 + textBounds.height);
            m_xPos = 10 + BORDER_SIZE;
        }

        Vector2f recSize(textBounds.width, text.getCharacterSize());
        rectangle.setPosition(WINDOW_SIZE + m_xPos, MENUBAR_HEIGHT + m_yPos);
        rectangle.setSize(recSize);
        rectangle.setFillColor(Color::White);
        rectangle.setOutlineThickness(2.f);

        text.setPosition(WINDOW_SIZE + m_xPos, MENUBAR_HEIGHT + m_yPos);
        
        m_window.draw(rectangle);
        m_window.draw(text);

        // update x,y pos for the next move text
        m_xPos += (10 + textBounds.width);
    }
    m_xPos = 10 + BORDER_SIZE; m_yPos = 10; // reset x,y pos back to original for drawing in next tick

}

coor2d SidePanel::findNextAvailableSpot() {
    return make_pair(0,0);
}