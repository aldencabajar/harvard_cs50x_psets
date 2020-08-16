#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;



// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }

            /*for (int k = 0; k < candidate_count; k++)
            {
            printf("%i\n", ranks[k]);
            }*/

        }



        record_preferences(ranks);
        /*
        for (int k = 0; k < candidate_count; k++)
        {
            for (int l = 0; l < candidate_count; l++)
            {
                printf("%i", preferences[k][l]);

            }
        }*/

        printf("\n");

    }

    add_pairs();
    /*
    printf("\n%i", pair_count);

    printf("\n");
    for (int i = 0; i < MAX; i++)
    {
        printf("%i,%i\n", pairs[i].winner, pairs[i].loser);
    }
    printf("\n");*/

    sort_pairs();
    /*
    for (int i = 0; i < pair_count; i++)
    {
        printf("%i,%i\n", pairs[i].winner, pairs[i].loser);
    }*/
    lock_pairs();
    /*

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%d", locked[i][j]);
        }
        printf("\n");
        //printf("%d", pairs[i].winner, pairs[i].loser);
    }
    */

    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{

    for (int j = 0; j < candidate_count; j++)
    {
        /* apart from checking the candidate names, we also check
        if detected candidate index were already stored in ranks array*/
        if (strcmp(name, candidates[j]) == 0)
        {
            if (rank > 0)
            {
                int sim = 0;
                for (int k = 0; k < rank; k++)
                {
                    if (ranks[k] != j)
                    {
                        sim++;
                    }
                }
                //printf("sim: %i\nrank: %i", sim, rank);
                if (sim == rank)
                {
                    ranks[rank] = j;
                    return true;
                }
            }
            else
            {
                ranks[rank] = j;
                return true;
            }



        }
    }



    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (i == j)
            {
                preferences[i][j] = 0;
            }
            else
            {
                preferences[ranks[i]][ranks[j]] += 1;
                preferences[ranks[j]][ranks[i]] += 0;
            }

        }
    }
    return;

}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //we will only be looking into the off-diagonals for the preference matrix
    // this struct will be used to store off diagonal coords
    int n_off_diags = ((int)pow((double)candidate_count, (double)2) - candidate_count) / 2;
    //printf("%i", n_off_diags);

    typedef struct
    {
        int x;
        int y;
    }
    xy;


    xy upr[n_off_diags];

    int u = 0;
    // printf("\n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                upr[u].x = i;
                upr[u].y = j;
                u++;
            }
        }

    }


    int winner, loser = 0;
    for (int i = 0; i < n_off_diags; i++)
    {
        int p = preferences[upr[i].x][upr[i].y];
        int op = preferences[upr[i].y][upr[i].x];

        if (p != op)
        {
            pair_count++;
            if (p > op)
            {
                winner = upr[i].x;
                loser = upr[i].y;
            }
            else if (p < op)
            {
                winner = upr[i].y;
                loser = upr[i].x;
            }
            pairs[pair_count - 1].winner = winner;
            pairs[pair_count - 1].loser = loser;


        }



    }


    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    int swp = -1;
    while (swp != 0)
    {
        swp = 0;
        for (int i = 0; i < pair_count - 1; i++)
        {
            int margin_i = preferences[pairs[i].winner][pairs[i].loser];
            int margin_i1 =  preferences[pairs[i + 1].winner][pairs[i + 1].loser];

            if (margin_i < margin_i1)
            {
                int tmp_w = pairs[i + 1].winner;
                int tmp_l = pairs[i + 1].loser;

                pairs[i + 1].winner = pairs[i].winner;
                pairs[i + 1].loser = pairs[i].loser;
                pairs[i].winner = tmp_w;
                pairs[i].loser = tmp_l;

                swp++;
            }
        }
    }


    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //printf("\n%i", pair_count);
    for (int i = 0; i < pair_count; i++)
    {
        // cyclic patterns do not form for n < 3

        if (i < 2)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        else
        {
            //int curr = pairs[i].loser;
            bool cycle = false;
            int curr_size = 1, total_size = 1;
            int stack[100];
            stack[0] = pairs[i].loser;
            int discovered[candidate_count];
            int k = 0;
            int v;


            while ((!cycle) & (curr_size > 0))
            {
                // pop the very first element from stack, decrease size
                v = stack[k];
                curr_size--;

                int match = 0;
                for (int j = 0; j < k; j++)
                {
                    if (discovered[j] == v)
                    {
                        match++;
                    }
                }

                if (match > 0)
                {
                    continue;
                }

                discovered[k] = v;

                //int cnt = 0;
                for (int j = 0; j < candidate_count; j++)
                {
                    if (locked[v][j])
                    {
                        if (j == pairs[i].winner)
                        {
                            cycle = true;
                        }

                        stack[total_size] = j;
                        //cnt++;
                        curr_size++;
                        total_size++;
                    }
                }
                /*
                printf("stack_vals:");
                for (int j = 0; j < total_size; j++)
                {
                    printf("%i ", stack[j]);
                }
                printf("\n");
                */

                k++;

            }
            if (!cycle)
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
            }

        }


    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // calculate colsums of the matrix. The lowest number
    // represent the winner
    int colsums[candidate_count];
    for (int j = 0; j < candidate_count; j++)
    {
        int colsum = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j])
            {
                colsum++;
            }
        }
        colsums[j] = colsum;
    }
    // store original colsums order in another array
    int colsums_orig[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        colsums_orig[i] = colsums[i];
    }
    // arrange rowsums in increasing order. colsums represent
    // the number of arrows going inward the candidate
    int swp = -1;
    while (swp != 0)
    {
        swp = 0;
        for (int i = 0; i < candidate_count - 1; i++)
        {

            if (colsums[i] > colsums[i + 1])
            {
                int tmp = colsums[i + 1];
                colsums[i + 1] = colsums[i];
                colsums[i] = tmp;

                swp++;
            }
        }
    }
    // find from the arranged array the index of the minimum colsums,
    // print the winner with the least colsums
    for (int i = 0; i < candidate_count; i++)
    {
        if (colsums[0] == colsums_orig[i])
        {
            printf("%s", candidates[i]);
        }
    }
    printf("\n");


    return;
}

