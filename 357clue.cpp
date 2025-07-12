#include <bits/stdc++.h>
using namespace std;

map<string, bool> memo;

string makeKey(int a, int b, int c) {
    char buf[20];
    sprintf(buf, "%d,%d,%d", a, b, c);
    return string(buf);
}

bool canWin(int a, int b, int c) {
    string key = makeKey(a, b, c);
    if (memo.count(key)) return memo[key];
    if (a == 0 && b == 0 && c == 0) return memo[key] = false;

    for (int take = 1; take <= 3; ++take) {
        if (a >= take && !canWin(a - take, b, c)) return memo[key] = true;
        if (b >= take && !canWin(a, b - take, c)) return memo[key] = true;
        if (c >= take && !canWin(a, b, c - take)) return memo[key] = true;
    }
    return memo[key] = false;
}

void printStatus(int a, int b, int c) {
    cout << "A " << a << endl;
    cout << "B " << b << endl;
    cout << "C " << c << endl;
}

bool isGameOver(int a, int b, int c) {
    return a == 0 && b == 0 && c == 0;
}

bool isValidMove(char area, int count, int a, int b, int c) {
    if (count < 1 || count > 3) return false;
    if (area == 'A' && a >= count) return true;
    if (area == 'B' && b >= count) return true;
    if (area == 'C' && c >= count) return true;
    return false;
}

void applyMove(char area, int count, int &a, int &b, int &c) {
    if (area == 'A') a -= count;
    else if (area == 'B') b -= count;
    else if (area == 'C') c -= count;
}

int main() {
    int a, b, c;
    char first;
    cout << "357���Y�C�� �п�JABC���l���Y�ƶq" << endl;
    cin >> a >> b >> c;

    cout << "�O�_����H(y/n): ";
    cin >> first;

    bool playerTurn = (first == 'y');
    int playerTurnCount = 0;
    srand(time(0));

    while (true) {
        printStatus(a, b, c);
        if (isGameOver(a, b, c)) {
            if (playerTurn) cout << "�A��F�I" << endl;
            else cout << "�AĹ�F�I" << endl;
            break;
        }

        if (playerTurn) {
            ++playerTurnCount;
            cout << "����A�ާ@�A�п�J�ϰ�P���ơ]�p A 2�^�G";
            if (playerTurnCount >= 3) {
                cout << "�ݭn���ܥi��J h" << endl;
            }

            string input;
            cin >> input;

            if (input == "h") {
                if (canWin(a, b, c)) {
                    cout << "�A�nť��ĳ�����ܡH" << endl;
                    // ��X�X�k�B�ɭP���骺��ĳ
                    for (int take = 1; take <= 3; ++take) {
                        if (a >= take && !canWin(a - take, b, c))
                            cout << "A " << take << endl;
                    }
                    for (int take = 1; take <= 3; ++take) {
                        if (b >= take && !canWin(a, b - take, c))
                            cout << "B " << take << endl;
                    }
                    for (int take = 1; take <= 3; ++take) {
                        if (c >= take && !canWin(a, b, c - take))
                            cout << "C " << take << endl;
                    }
                } else {
                    cout << "�����A��w�F" << endl;
                }
                continue; // �����Ӧ^�X
            }

            char area = input[0];
            int count;
            cin >> count;

            if (!isValidMove(area, count, a, b, c)) {
                cout << "��J���ŦX�W�d�A�Э��s��J�C" << endl;
                continue;
            }
            applyMove(area, count, a, b, c);
            cout << "�A���F " << count << " �� �� �Ѿl�����G" << endl;
        } else {
            // AI �^�X
            bool moved = false;
            for (int take = 1; take <= 3 && !moved; ++take) {
                if (a >= take && !canWin(a - take, b, c)) {
                    cout << "AI ���F A " << take << " �� �� �Ѿl�����G" << endl;
                    a -= take; moved = true; break;
                }
                if (b >= take && !canWin(a, b - take, c)) {
                    cout << "AI ���F B " << take << " �� �� �Ѿl�����G" << endl;
                    b -= take; moved = true; break;
                }
                if (c >= take && !canWin(a, b, c - take)) {
                    cout << "AI ���F C " << take << " �� �� �Ѿl�����G" << endl;
                    c -= take; moved = true; break;
                }
            }
            // �Y�S��������a�骺�ۦ��A�H���X�k�X��
            if (!moved) {
                while (true) {
                    int take = rand() % 3 + 1;
                    int areaIdx = rand() % 3;
                    if (areaIdx == 0 && a >= take) {
                        cout << "AI ���F A " << take << " �� �� �Ѿl�����G" << endl;
                        a -= take; break;
                    }
                    if (areaIdx == 1 && b >= take) {
                        cout << "AI ���F B " << take << " �� �� �Ѿl�����G" << endl;
                        b -= take; break;
                    }
                    if (areaIdx == 2 && c >= take) {
                        cout << "AI ���F C " << take << " �� �� �Ѿl�����G" << endl;
                        c -= take; break;
                    }
                }
            }
        }
        playerTurn = !playerTurn;
    }

    return 0;
}
