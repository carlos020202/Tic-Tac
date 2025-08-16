/*
    Tic-Tac-Toe with AI (Minimax Algorithm)
    Made by Carlos Henrique
*/

#include <iostream>
#include <limits>
using namespace std;

char tabuleiro[3][3] = { {'1','2','3'},
                         {'4','5','6'},
                         {'7','8','9'} };

void mostrarTabuleiro() {
    cout << "\n";
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            cout << " " << tabuleiro[i][j] << " ";
            if(j < 2) cout << "|";
        }
        cout << "\n";
        if(i < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}

bool jogadaValida(int pos) {
    int linha = (pos-1)/3;
    int coluna = (pos-1)%3;
    return (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O');
}

void marcar(int pos, char simbolo) {
    int linha = (pos-1)/3;
    int coluna = (pos-1)%3;
    tabuleiro[linha][coluna] = simbolo;
}

bool venceu(char simbolo) {
    for(int i=0; i<3; i++) {
        if(tabuleiro[i][0]==simbolo && tabuleiro[i][1]==simbolo && tabuleiro[i][2]==simbolo) return true;
        if(tabuleiro[0][i]==simbolo && tabuleiro[1][i]==simbolo && tabuleiro[2][i]==simbolo) return true;
    }
    if(tabuleiro[0][0]==simbolo && tabuleiro[1][1]==simbolo && tabuleiro[2][2]==simbolo) return true;
    if(tabuleiro[0][2]==simbolo && tabuleiro[1][1]==simbolo && tabuleiro[2][0]==simbolo) return true;
    return false;
}

bool empate() {
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if(tabuleiro[i][j] != 'X' && tabuleiro[i][j] != 'O')
                return false;
    return true;
}

// ---------- AI (Minimax) ----------
int avaliar() {
    if(venceu('O')) return +10; // AI wins
    if(venceu('X')) return -10; // Player wins
    return 0;
}

int minimax(bool isMax) {
    int score = avaliar();
    if(score == 10) return score;
    if(score == -10) return score;
    if(empate()) return 0;

    if(isMax) { // AI's turn (O)
        int melhor = numeric_limits<int>::min();
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                if(tabuleiro[i][j] != 'X' && tabuleiro[i][j] != 'O') {
                    char backup = tabuleiro[i][j];
                    tabuleiro[i][j] = 'O';
                    melhor = max(melhor, minimax(false));
                    tabuleiro[i][j] = backup;
                }
            }
        }
        return melhor;
    } else { // Player's turn (X)
        int melhor = numeric_limits<int>::max();
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                if(tabuleiro[i][j] != 'X' && tabuleiro[i][j] != 'O') {
                    char backup = tabuleiro[i][j];
                    tabuleiro[i][j] = 'X';
                    melhor = min(melhor, minimax(true));
                    tabuleiro[i][j] = backup;
                }
            }
        }
        return melhor;
    }
}

int melhorJogada() {
    int melhorValor = numeric_limits<int>::min();
    int movimento = -1;

    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(tabuleiro[i][j] != 'X' && tabuleiro[i][j] != 'O') {
                char backup = tabuleiro[i][j];
                tabuleiro[i][j] = 'O';
                int valor = minimax(false);
                tabuleiro[i][j] = backup;

                if(valor > melhorValor) {
                    melhorValor = valor;
                    movimento = (i*3 + j + 1);
                }
            }
        }
    }
    return movimento;
}
// ----------------------------------

int main() {
    int posicao;
    bool fim = false;

    cout << "=== Tic-Tac-Toe with AI (Minimax) ===\n";
    cout << "Made by Carlos Henrique\n\n";
    cout << "You play as X, the AI plays as O\n";
    mostrarTabuleiro();

    while(!fim) {
        cout << "Your turn! Choose a position (1-9): ";
        cin >> posicao;

        if(posicao < 1 || posicao > 9 || !jogadaValida(posicao)) {
            cout << "Invalid move, try again.\n";
            continue;
        }

        marcar(posicao, 'X');
        mostrarTabuleiro();

        if(venceu('X')) {
            cout << "You win!\n";
            break;
        } else if(empate()) {
            cout << "It's a draw!\n";
            break;
        }

        cout << "AI's turn...\n";
        int iaMove = melhorJogada();
        marcar(iaMove, 'O');
        mostrarTabuleiro();

        if(venceu('O')) {
            cout << "AI wins!\n";
            break;
        } else if(empate()) {
            cout << "It's a draw!\n";
            break;
        }
    }
    return 0;
}
