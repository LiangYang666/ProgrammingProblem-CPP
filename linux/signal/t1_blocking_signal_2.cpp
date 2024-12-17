//
// Created by chenyang.yl on 12/17/24.
//
#include <signal.h>
#include <iostream>
#include <unistd.h>
using namespace std;


void PrintPending(sigset_t pending) {
    cout << "Pending signals bitmap: ";
    for (int i = NSIG - 1; i > 0; i--) {
        if (sigismember(&pending, i)) {
            cout << "1"; // 如果信号 i 在 pending 中，打印 1
        } else {
            cout << "0"; // 否则打印 0
        }
    }
    cout << endl; // 添加换行
}

int main() {
    sigset_t bset;
    sigset_t oset;
    sigemptyset(&bset);
    sigemptyset(&oset);
    sigaddset(&bset, 2);
    sigprocmask(SIG_SETMASK, &bset, &oset);

    sigset_t pending;
    while (true)
    {
        int n = sigpending(&pending);
        if (n<0) continue;
        // 打印pending
        PrintPending(pending);
        sleep(1);
    }

    return 0;
}

