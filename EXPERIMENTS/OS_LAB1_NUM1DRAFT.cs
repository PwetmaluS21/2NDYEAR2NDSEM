using System;
using System.Runtime.InteropServices;

class Program
{
    // NtQuerySystemInformation is a native system call in ntdll.dll
    [DllImport("ntdll.dll")]
    private static extern int NtQuerySystemInformation(
        int SystemInformationClass,
        IntPtr SystemInformation,
        int SystemInformationLength,
        out int ReturnLength
    );

    static void Main()
    {
        int returnLength;
        IntPtr buffer = IntPtr.Zero;

        // Call the system call directly
        int status = NtQuerySystemInformation(0, buffer, 0, out returnLength);

        Console.WriteLine($"System call returned status: {status}, length needed: {returnLength}");
    }
}