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
    cout << "357石頭遊戲 請輸入ABC堆初始石頭數量" << endl;
    cin >> a >> b >> c;

    cout << "是否先手？(y/n): ";
    cin >> first;

    bool playerTurn = (first == 'y');
    int playerTurnCount = 0;
    srand(time(0));

    while (true) {
        printStatus(a, b, c);
        if (isGameOver(a, b, c)) {
            if (playerTurn) cout << "你輸了！" << endl;
            else cout << "你贏了！" << endl;
            break;
        }

        if (playerTurn) {
            ++playerTurnCount;
            cout << "輪到你操作，請輸入區域與顆數（如 A 2）：";
            if (playerTurnCount >= 3) {
                cout << "需要提示可輸入 h" << endl;
            }

            string input;
            cin >> input;

            if (input == "h") {
                if (canWin(a, b, c)) {
                    cout << "你要聽建議策略嗎？" << endl;
                    // 輸出合法且導致對手輸的建議
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
                    cout << "哈哈你輸定了" << endl;
                }
                continue; // 不消耗回合
            }

            char area = input[0];
            int count;
            cin >> count;

            if (!isValidMove(area, count, a, b, c)) {
                cout << "輸入不符合規範，請重新輸入。" << endl;
                continue;
            }
            applyMove(area, count, a, b, c);
            cout << "你拿了 " << count << " 顆 → 剩餘局面：" << endl;
        } else {
            // AI 回合
            bool moved = false;
            for (int take = 1; take <= 3 && !moved; ++take) {
                if (a >= take && !canWin(a - take, b, c)) {
                    cout << "AI 拿了 A " << take << " 顆 → 剩餘局面：" << endl;
                    a -= take; moved = true; break;
                }
                if (b >= take && !canWin(a, b - take, c)) {
                    cout << "AI 拿了 B " << take << " 顆 → 剩餘局面：" << endl;
                    b -= take; moved = true; break;
                }
                if (c >= take && !canWin(a, b, c - take)) {
                    cout << "AI 拿了 C " << take << " 顆 → 剩餘局面：" << endl;
                    c -= take; moved = true; break;
                }
            }
            // 若沒找到讓玩家輸的招式，隨機合法出招
            if (!moved) {
                while (true) {
                    int take = rand() % 3 + 1;
                    int areaIdx = rand() % 3;
                    if (areaIdx == 0 && a >= take) {
                        cout << "AI 拿了 A " << take << " 顆 → 剩餘局面：" << endl;
                        a -= take; break;
                    }
                    if (areaIdx == 1 && b >= take) {
                        cout << "AI 拿了 B " << take << " 顆 → 剩餘局面：" << endl;
                        b -= take; break;
                    }
                    if (areaIdx == 2 && c >= take) {
                        cout << "AI 拿了 C " << take << " 顆 → 剩餘局面：" << endl;
                        c -= take; break;
                    }
                }
            }
        }
        playerTurn = !playerTurn;
    }

    return 0;
}
