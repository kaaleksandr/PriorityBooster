#include <ntddk.h>

void PriorityBoosterUnload(_In_ PDRIVER_OBJECT DriverObject);

extern "C"
NTSTATUS DriverOBject(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
	DriverObject->DriverUnload = PriorityBoosterUnload;

	return STATUS_SUCCESS;
}

void PriorityBoosterUnload(_In_ PDRIVER_OBJECT DriverObject)
{

}