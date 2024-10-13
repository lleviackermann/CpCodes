#include <bits/stdc++.h>
#define ll long long
using namespace std;

unordered_map<string, int> corr;
int num, childs, queries;
void take_input()
{
    string temp;
    for (int i = 0; i < num; i++)
    {
        cin >> temp;
        corr[temp] = i;
    }
}

void print__(string s) {
    cout << s << endl;
}

void for_one()
{
    pair<int, int> hello{-1, -1};
    while (queries--)
    {
        int fir_input, given_id;
        string given_string;
        cin >> fir_input >> given_string >> given_id;
        if (fir_input == 1)
        {
            if (hello.first != -1)
                print__("false");
            else
            {
                hello = {corr[given_string], given_id};
                print__("true");
            }
            continue;
        }
        if (hello.first == corr[given_string] && hello.second == given_id)
        {
            print__("true");
            hello = {-1, -1};
        }
        else
        {
            print__("false");
        }
    }
}

void solve()
{
    cin >> num >> childs >> queries;
    // int cnt = -1;
    take_input();
    if (childs == 1)
    {
        for_one();
        return;
    }

    ll bfs = childs;
    ll prev = 0;
    vector<ll> asc(num, -1);
    ll tem = 1;
    while (tem < num)
    {
        ll curr_val = tem + bfs;
        int st = 0;
        while (tem < curr_val && tem < num)
        {
            st++;
            asc[tem] = prev;
            tem++;
            if (st == childs)
                prev++, st = 0;
        }
        bfs *= childs;
    }
    ll minus_value = -1e10;
    vector<ll> has_or_not(num, minus_value);
    vector<ll> has_child_or_not(num, 0);
    while (queries--)
    {
        int fir_input, given_id;
        string given_string;
        cin >> fir_input >> given_string >> given_id;
        int cor_value = corr[given_string];
        if (fir_input == 1)
        {
            bool anscestors = false;
            int another_flag = cor_value;
            while (another_flag != -1)
            {
                if (has_or_not[another_flag] != minus_value)
                {
                    anscestors = true;
                    break;
                }
                another_flag = asc[another_flag];
            }
            if (has_or_not[cor_value] != minus_value || has_child_or_not[cor_value] > 0 || anscestors)
            {
                print__("false");
            }
            else
            {
                another_flag = cor_value;
                has_or_not[another_flag] = given_id;
                while (another_flag != -1)
                {
                    has_child_or_not[another_flag]++;
                    another_flag = asc[another_flag];
                }
                print__("true");
            }
        }
        else
        {
            if (has_or_not[cor_value] == given_id)
            {
                int x = cor_value;
                has_or_not[cor_value] = minus_value;
                while (cor_value != -1)
                {
                    has_child_or_not[cor_value]--;
                    cor_value = asc[cor_value];
                }
                print__("true");
            }
            else
            {
                print__("false");
            }
        }
    }
}

int main()
{

    int t = 1;
    while (t--)
    {
        solve();
    }
    return 0;
}