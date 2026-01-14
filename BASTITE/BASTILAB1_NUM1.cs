using System;
using System.Diagnostics;

class Program
{
    static void Main(string[] args)
    {
        try
        {
            Process process = new Process();
            process.StartInfo.FileName = "whoami";
            process.StartInfo.UseShellExecute = false;
            process.StartInfo.RedirectStandardOutput = true;

            process.Start();
            Console.WriteLine("\n Process ID is:   {0}", Process.GetCurrentProcess().Id);
            process.WaitForExit();
            string output = process.StandardOutput.ReadToEnd();
            Console.WriteLine("Child process output: " + output.Trim());
        }
        catch (Exception ex)
        {
            Console.WriteLine("Process creation failed: " + ex.Message);
            Environment.Exit(1);
        }
    }
}