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
    int cnt = 0;
    while (true)
    {
        int n = sigpending(&pending);
        if (n<0) continue;
        // 打印pending
        PrintPending(pending);
        sleep(1);
        cnt++;
        if (cnt == 10) {
            cout << "unlock signal 2" << endl;
            sigprocmask(SIG_SETMASK, &oset, nullptr);
            // 将会在ctrl+c后退出，或者在10s前ctrl+c了，10秒后立即退出
        }
    }

    return 0;
}

