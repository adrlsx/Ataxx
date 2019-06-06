//
// Created by adrien on 03/06/19.
//

#include <sstream>
#include "ConsoleView.h"
#include "../../Controller/exception/invalid_input.h"
#include "../termcolor/termcolor.hpp"

using std::cout;
using std::endl;
using std::cin;
using std::stringstream;
using std::to_string;

void ConsoleView::update(Subject* subject) {
    Board* board = dynamic_cast<Board*>(subject);

    const array<array<Cell, 7>, 7>& grid = board->getGrid();
    const vector<array<unsigned short, 2>>& moves = board->getAvailableCells();
    if(moves.empty()){
        displayGrid(grid);
    }
    else{
        availableMoves(board);
    }
    nbPawn(board->getNbRedPawn(), board->getNbBluePawn());

}

void ConsoleView::displayGrid(const array<array<Cell, 7>, 7> &grid) noexcept{
    cout << "Current grid:" << endl;
    for(const array<Cell, 7>& row : grid){
        for(const Cell& cell: row){
            if(cell == Red){
                cout << termcolor::red;
            }
            else if(cell == Blue){
                cout << termcolor::blue;
            }
            cout << cell << termcolor::reset << "  ";
        }
        cout << endl;
    }
}

void ConsoleView::availableMoves(Board* board) noexcept{
    cout << "Available moves:" << endl;
    const array<array<Cell, 7>, 7>& grid = board->getGrid();
    for(unsigned short row = 0; row <= 6; row++){
        for(unsigned short column = 0; column <= 6; column++){
            if(board->isAvailableMove(row, column)){
                cout << termcolor::green;
            }
            else if(grid[row][column] == Red){
                cout << termcolor::red;
            }
            else if(grid[row][column] == Blue){
                cout << termcolor::blue;
            }
            cout << grid[row][column] << termcolor::reset << "  ";
        }
        cout << endl;
    }
}

void ConsoleView::nbPawn(unsigned short nbRedPawn, unsigned short nbBluePawn) noexcept{
    cout << endl << "Red Player has: " << nbRedPawn
         << endl << "Blue Player has: " << nbBluePawn << endl;
}

const string ConsoleView::selectPawn(const string& player, unsigned short& row, unsigned short& column) noexcept{
    string input;
    cout << "Please select a pawn coordinates: " << endl << player << "> ";
    getline(cin, input);
    cout << endl;
    return input;
}