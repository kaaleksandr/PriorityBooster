#include <Windows.h>
#include <stdio.h>
#include "../PriorityBooster/PriorityBoosterCommon.h"

int Error(const char* message)
{
    printf("%s (error=%d)\n", message, GetLastError());
    return 1;
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("Usage: Booster <threadid> <priority>");
        return 0;
    }

    HANDLE hDevice = CreateFileW(
        L"\\\\.\\PriorityBooster",
        GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (hDevice == INVALID_HANDLE_VALUE)
        return Error("FAiled to open device");

    ThreadData data;
    data.ThreadId = atoi(argv[1]);
    data.Priority = atoi(argv[2]);

    DWORD returned;
    BOOL success = DeviceIoControl(
        hDevice,
        IOCTL_PRIORITY_BOOSTER_SET_PRIORITY,
        &data, sizeof(data),
        NULL, 0,
        &returned, NULL);

    if (success)
        printf("Priority change succeeded!\n");
    else
        Error("Priority change failed!\n");

    CloseHandle(hDevice);
}

