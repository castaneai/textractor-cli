#include "host.h"
#include "hookcode.h"
#include <io.h>
#include <fcntl.h>
#include <iostream>

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    fflush(stdout);
    Host::Start([](auto) {}, [](auto) {}, [](auto&) {}, [](auto&) {}, [](TextThread& thread, std::wstring& output)
    {
        wprintf_s(L"[%I64X:%I32X:%I64X:%I64X:%I64X:%s:%s] %s\n",
                  thread.handle,
                  thread.tp.processId,
                  thread.tp.addr,
                  thread.tp.ctx,
                  thread.tp.ctx2,
                  thread.name.c_str(),
                  HookCode::Generate(thread.hp, thread.tp.processId).c_str(),
                  output.c_str()
        );
        fflush(stdout);
        return true;
    });
    DWORD processId = 23132;
    Host::InjectProcess(processId);
    while (true)
    {
        Sleep(10000);
    }
    ExitProcess(0);
}
