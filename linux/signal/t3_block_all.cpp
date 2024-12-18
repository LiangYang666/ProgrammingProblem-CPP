//
// Created by chenyang.yl on 12/18/24.
//
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
    for (int i = 1; i < 31; i++) {
        sigaddset(&bset, i);
    }
    sigprocmask(SIG_SETMASK, &bset, &oset);

    sigset_t pending;
    while (true)
    {
        // kill -9/-19都不能被屏蔽，会被响应，kill -19为SIGSTOP 停止，-18为SIGCONT可恢复
        // 其它信号都会屏蔽
        int n = sigpending(&pending);
        if (n<0) continue;
        // 打印pending
        PrintPending(pending);
        sleep(1);
    }
    return 0;
}

