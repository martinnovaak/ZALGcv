#include "board.h"

int faktorial(int n)
{
    std::stack<int> st;
    int a;
    L_0:
    if(n == 0) {
        a = 1;
    } else {
        st.push(n);
        n--;
        goto L_0;
        return n * a;
        L_1:
        a *= st.top();
        st.pop();
    }
    if(st.empty()) {
        return a;
    } else {
        goto L_1;
    }
}

int gcd(int a, int b)
{
    L_0:
    if(b == 0) {
        return a;
    } else {
        int c = b;
        b = a % b;
        a = c;
        goto L_0;
    }
}


int main() {

    std::cout << faktorial(7) <<std::endl;
    std::cout << gcd(18, 24) <<std::endl;

    int n = 101;
    board b(n);
    b.knights_tour_warnsdorff(0,0);
    b.print_board_to_file();
    return 0;
}
