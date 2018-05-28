// Time:  O(n^2)
// Space: O(n)

/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
class Solution {
public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        vector<vector<int>> H(wordlist.size(), vector<int>(wordlist.size()));
        for (int i = 0; i < wordlist.size(); ++i) {
            for (int j = 0; j < wordlist.size(); ++j) {
                H[i][j] = match(wordlist[i], wordlist[j]);
            }
        }

        unordered_set<int> lookup;
        vector<int> possible(wordlist.size());
        iota(possible.begin(), possible.end(), 0);
        int n = 0;
        while (!possible.empty() && n < 6) {
            auto guess = solve(H, possible, lookup);
            n = master.guess(wordlist[guess]);
            vector<int> new_possible;
            for (const auto& j : possible) {
                if (H[guess][j] == n) {
                    new_possible.emplace_back(j);
                }
            }
            lookup.emplace(guess);
            possible = new_possible;
        }
    }

private:
    int solve(const vector<vector<int>>& H,
              const vector<int>& possible,
              const unordered_set<int>& lookup) {

        vector<int> min_max_group = possible;
        int best_guess = -1; 
        for (int guess = 0; guess < H.size(); ++guess) {
            if (!lookup.count(guess)) {
                vector<vector<int>> groups(7);
                for (const auto& j : possible) {
                    if (j != guess) {
                        groups[H[guess][j]].emplace_back(j);
                    }
                }
                int max_group_i = 0;
                for (int i = 0; i < groups.size(); ++i) {
                    if (groups[i].size() > groups[max_group_i].size()) {
                        max_group_i = i;
                    }
                }
                if (groups[max_group_i].size() < min_max_group.size()) {
                    min_max_group = groups[max_group_i];
                    best_guess = guess;
                }
            }
        }
        return best_guess;
    }

    int match(const string& a, const string& b) {
        int matches = 0;
        for (int i = 0; i < a.length(); ++i) {
            if (a[i] == b[i]) {
                ++matches;
            }
        }
        return matches;
    }
};

// Time:  O(n^2)
// Space: O(n)
class Solution2 {
public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        for (int i = 0, n = 0; i < 10 && n < 6; ++i) {
            unordered_map<string, int> count;
            for (const auto& w1 : wordlist) {
                for (const auto& w2 : wordlist) {
                    if (match(w1, w2) == 0) {
                        ++count[w1];
                    }
                }
            }
            string guess;
            for (const auto& w : wordlist) {
                if (guess.empty() ||
                    count[w] < count[guess]) {
                    guess = w;
                }
            }
            n = master.guess(guess);
            vector<string> new_wordlist;
            for (const auto& w : wordlist) {
                if (match(w, guess) == n) {
                    new_wordlist.emplace_back(w);
                }
            }
            wordlist = new_wordlist;
        }
    }

private:
    int match(const string& a, const string& b) {
        int matches = 0;
        for (int i = 0; i < a.length(); ++i) {
            if (a[i] == b[i]) {
                ++matches;
            }
        }
        return matches;
    }
};
