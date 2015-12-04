using System;
using System.Collections.Generic;
using System.IO;
class Solution
{
    static void displayPathtoPrincess(int n, String[] grid)
    {
        Console.WriteLine("No of lines: " + n);
        int myLocationX = -1, myLocationY = -1;
        for (int i = 0; i < n; i++)
        {
            if (myLocationX == -1)
            {
                myLocationX = grid[i].IndexOf('m');
                if (myLocationX != -1)
                {
                    myLocationY = i;
                }
            }
        }
        Console.WriteLine(myLocationX + " " + myLocationY);
    }
    static void Main(String[] args)
    {
        int m;

        m = int.Parse(Console.ReadLine());

        String[] grid = new String[m];
        for (int i = 0; i < m; i++)
        {
            grid[i] = Console.ReadLine();
        }

        displayPathtoPrincess(m, grid);
    }
}
