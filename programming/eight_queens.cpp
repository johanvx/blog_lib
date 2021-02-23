#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int counter = 0;
vector<int> list;

bool isValid(int pos)
{
    bool ret = true;
    for (auto x: list) {
        if ((pos & 007) == (x & 007) ||
            ((pos & 007) > (x & 007) && (pos - x) % 011 == 0 && (pos - x) / 011 == ((pos & 070) >> 3) - ((x & 070) >> 3)) ||
            ((pos & 007) < (x & 007) && (pos - x) % 007 == 0 && (pos - x) / 007 == ((pos & 070) >> 3) - ((x & 070) >> 3))) {
            ret = false;
            break;
        }
    }
    return ret;
}

void generate(int row)
{
    for (int i = 0; i < 8; i++) {
        int pos = stoi("0" + to_string(row) + to_string(i), 0, 8);
        if (row == 0) {
            list.clear();
        }
        if (isValid(pos)) {
            list.push_back(pos);
            if (list.size() == 8) {
                counter++;
                cout << "COUNTER = " << dec << counter << endl;
                cout << "Current list:";
                for (auto x: list) {
                    cout << " " << setw(2) << setfill('0') << oct << x;
                }
                cout << endl;
                cout << "----------------------------" << endl;
                list.pop_back();
                list.pop_back();
                return ;
            } else {
                generate(row + 1);
            }
        }
    }
    if (list.size() != 0) {
        list.pop_back();
    }
}

int main()
{
    generate(0);
    cout << "There are in total " << dec << counter << " results." << endl;
    return 0;
}