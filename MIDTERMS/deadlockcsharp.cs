using System;

class BankersAlgorithm
{
    static void Main()
    {
        int[,] alloc = new int[10, 10];
        int[,] max = new int[10, 10];
        int[,] need = new int[10, 10];
        int[] avail = new int[10];
        int[] work = new int[10];
        int[] total = new int[10];
        char[] finish = new char[10];

        int n, m;
        int count = 0;

        Console.Write("Enter the number of processes and resources: ");
        string[] input = Console.ReadLine().Split();
        n = int.Parse(input[0]);
        m = int.Parse(input[1]);

        // Initialize finish array correctly
        for (int i = 0; i < n; i++)
            finish[i] = 'n';

        // Claim (max) matrix input row by row
        Console.WriteLine("Enter the claim (max) matrix (each row space-separated):");
        for (int i = 0; i < n; i++)
        {
            string[] row = Console.ReadLine().Split();
            if (row.Length != m) throw new Exception($"Row {i+1} must have {m} values.");
            for (int j = 0; j < m; j++)
                max[i, j] = int.Parse(row[j]);
        }

        // Allocation matrix input row by row
        Console.WriteLine("Enter the allocation matrix (each row space-separated):");
        for (int i = 0; i < n; i++)
        {
            string[] row = Console.ReadLine().Split();
            if (row.Length != m) throw new Exception($"Row {i+1} must have {m} values.");
            for (int j = 0; j < m; j++)
                alloc[i, j] = int.Parse(row[j]);
        }

        // Resource vector input in one line
        Console.WriteLine("Enter the resource vector (space-separated):");
        string[] resRow = Console.ReadLine().Split();
        if (resRow.Length != m) throw new Exception($"Resource vector must have {m} values.");
        for (int i = 0; i < m; i++)
            total[i] = int.Parse(resRow[i]);

        // Calculate available resources
        for (int j = 0; j < m; j++)
        {
            int sum = 0;
            for (int i = 0; i < n; i++)
                sum += alloc[i, j];
            avail[j] = total[j] - sum;
        }

        // Initialize work vector
        for (int j = 0; j < m; j++)
            work[j] = avail[j];

        // Calculate need matrix
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                need[i, j] = max[i, j] - alloc[i, j];

        bool progress = true;

        while (count < n && progress)
        {
            progress = false;
            for (int i = 0; i < n; i++)
            {
                if (finish[i] == 'n')
                {
                    bool canExecute = true;
                    for (int j = 0; j < m; j++)
                    {
                        if (need[i, j] > work[j])
                        {
                            canExecute = false;
                            break;
                        }
                    }

                    if (canExecute)
                    {
                        Console.WriteLine("All resources can be allocated to Process {0}", i + 1);
                        Console.WriteLine("Available resources after execution: ");
                        for (int k = 0; k < m; k++)
                        {
                            work[k] += alloc[i, k];
                            Console.Write("{0,4}", work[k]);
                        }
                        Console.WriteLine();
                        finish[i] = 'y';
                        Console.WriteLine("Process {0} executed?: {1}", i + 1, finish[i]);
                        count++;
                        progress = true;
                    }
                }
            }
        }

        if (count == n)
        {
            Console.WriteLine("\nSystem is in safe mode");
            Console.WriteLine("The given state is safe state");
        }
        else
        {
            Console.WriteLine("\nSystem is NOT in a safe state");
        }
    }
}