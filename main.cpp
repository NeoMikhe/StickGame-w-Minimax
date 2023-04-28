#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

const int MAX = std::numeric_limits<int>::max();
const int MIN = std::numeric_limits<int>::min();

void printVector(std::vector<std::string> sticks){
    for(int i = 0; i < sticks.size(); i++) {
        std::cout << sticks[i] << " ";
    }
    std::cout << std::endl;
}

std::vector<std::string> removeSticks(std::vector<std::string> sticks, int deleteStick){
    for(int i = 0; i < deleteStick; i++){
        sticks.pop_back();
    }
    return sticks;
}

int minimax(std::vector<std::string> state, int depth, bool isMaxPlayer) {
    if (state.size() == 1) {
        if (isMaxPlayer) {
            return MIN;
        } else {
            return MAX;
        }
    }

    if (depth == 0) {
        return 0;
    }

    if (isMaxPlayer) {
        int bestValue = MIN;
        for (int i = 1; i <= 3; i++) {
            if (state.size() >= i) {
                std::vector<std::string> newState = removeSticks(state, i);
                int value = minimax(newState, depth - 1, false);
                bestValue = std::max(bestValue, value);
            }
        }
        return bestValue;
    } else {
        int bestValue = MAX;
        for (int i = 1; i <= 3; i++) {
            if (state.size() >= i) {
                std::vector<std::string> newState = removeSticks(state, i);
                int value = minimax(newState, depth - 1, true);
                bestValue = std::min(bestValue, value);
            }
        }
        return bestValue;
    }
}

std::vector<std::string> ia(std::vector<std::string> sticks){
    std::srand(std::time(nullptr));
    int bestValue = MIN;
    int bestMove = 1;
    for (int i = 1; i <= 3; i++) {
        if (sticks.size() >= i) {
            std::vector<std::string> newState = removeSticks(sticks, i);
            int value = minimax(newState, 5, false);
            if (value > bestValue) {
                bestValue = value;
                bestMove = i;
            }
        }
    }
    std::cout << "IA elige " << bestMove << " palitos." << std::endl;
    return removeSticks(sticks, bestMove);
}

int main() {
    std::vector<std::string> sticks;
    for(int i = 0; i < 11; i++){
    sticks.push_back(" | ");
    }
    printVector(sticks);
    int deleteStick = 0;

    do{
        std::cout << "Turno jugador: " << std::endl;
        std::cin >> deleteStick;
        if(deleteStick != 1 && deleteStick != 2 && deleteStick != 3){
            do{
                std::cout << "Solo puedes elegir entre 1 y 3 palitos para quitar: " << std::endl;
                std::cin >> deleteStick;
            }while(deleteStick != 1 && deleteStick != 2 && deleteStick != 3);
        }
        std::cout << deleteStick << std::endl;
        sticks = removeSticks(sticks, deleteStick);
        if(sticks.size() == 1) {
            std::cout << "GANADOR: JUGADOR " << std::endl;
            return 0;
        }
        printVector(sticks);
        std::cout << "Turno IA: " << std::endl;
        sticks = ia(sticks);
        printVector(sticks);
        if(sticks.size() == 1) {
            std::cout << "GANADOR: IA " << std::endl;
            return 0;
        }
    }while(!sticks.empty());

    return 0;
}
