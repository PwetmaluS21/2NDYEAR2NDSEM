using System;
using System.Diagnostics;

class Program
{
    static void Main(string[] args)
    {
        Process process = new Process();

        try
        {
            process.StartInfo.FileName = "whoami";
            process.StartInfo.UseShellExecute = false;
            process.StartInfo.RedirectStandardOutput = true;

            process.Start();

            Console.WriteLine("\n Process ID is:   {0}\n", Process.GetCurrentProcess().Id);

            string output = process.StandardOutput.ReadToEnd();
            process.WaitForExit();

            Console.WriteLine(output);
        }
        catch (Exception e)
        {
            Console.WriteLine("Process start failed: " + e.Message);
            Environment.Exit(1);
        }

        Environment.Exit(0);
    }
}