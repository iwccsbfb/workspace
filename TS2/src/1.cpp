/*
 * 1.cpp
 *
 *  Created on: Dec 16, 2016
 *      Author: Zengye
 */


/*
第一题是判断一个long是4的幂数 直接brute force循环写出来了 面试官要我优化 提出了bit manipulation 而且不准使用循环 让我写出来
面试官的hint是写个mask like ip address里面的mask 然后按位搞 当时懵了 没写出来 。
第二题是 给一个random number的generator的interator写interator 其中要求生成的随机数可以被五整除。
这题其实蛮简单的 我写的时候发生了点小bug 后来中午回来无聊又看了那个file 重新写了一遍 感觉三分钟就可以写好。
第三个题忘记了 大概是个比较简单的算法题 给出三个方法（我直接给了最优的 然后还需要提供两个比较差的）。
这轮表现应该是最差的。.
*/
#include "header.h"
// if a number if power of 4
bool power_of_4(long n) {
	// !(n & (n - 1)) --> power of two
	if(sizeof(n) == 4)
		return  (n > 0) && !(n & (n - 1)) && (n & (0X55555555));
	else // (sizeof(n) == 8), must n>0, in case of -2^31
		return  (n > 0) && !(n & (n - 1)) && (n & (0X5555555555555555));

/*
	// 100..000 is not power of 4
    if(num <= 0) return false;
	bool get_first_bit = false;
	for(unsigned int i=0; i< sizeof(num)*8; i++) {
		long mask = 1 << i;
		if(mask & num) {
			// more than one '1' in the bit representation
			if(get_first_bit) return false;
			get_first_bit = true;
			// first '1' is not on the odd-th position
			if(i % 2 != 0) return false;
		}
	}
	return true;*/
}

bool power_of_4_method2(long num) {
	// 100..000 is not power of 4
    if(num <= 0) return false;
    while(num > 1) {
    	if(num % 4 != 0)
    		return false;
    	num /= 4;
    }
	return true;
}


void test_power_of_4() {
	//cout << sizeof(long) << endl;
	cout << power_of_4(4) << endl;
	cout << power_of_4(190) << endl;
	cout << power_of_4(256) << endl;
	cout << power_of_4(-1) << endl;
	cout << power_of_4(0) << endl;
}

// wildcard matching

// - wild card
// https://leetcode.com/problems/wildcard-matching/
// test case: empty str, without * or ?, with *, with ?, with * and ?
    /*
        t[i][j] := whether s[0..i-1] matchs p[0..j-1], i = [0 : s.size()], j = [0, p.size()]
        1. if (s[i-1] == p[j-1] || p[j-1] == '?') -> t[i][j] = t[i-1][j-1]
        2. else if (p[j-1] == '*') -> t[i][j] = t[i-1][j] || t[i][j-1]
        3. else (i.e. s[i] != p[j-1]) -> t[i][j] = false
    */
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();

        vector<vector<bool> > t(m + 1, vector<bool>(n + 1)); // default to all false

        // initialize first column and row
        t[0][0] = true; // s and p are both ""
        for (int j = 1; j <= n; ++ j) {
            if (p[j-1] == '*')
                t[0][j] = true;
            else
                break; // if current is not '*', will not match onwards
        }

        for (int i = 1; i <= m; ++ i) { // note the bound is "<= n""
            for (int j = 1; j <= n; ++ j) {
                if (s[i-1] == p[j-1] || p[j-1] == '?') // if current char match
                    t[i][j] = t[i-1][j-1];
                else if (p[j-1] == '*')
                    t[i][j] = t[i-1][j] || t[i][j-1];
                // else, no match, leave as false
            }
        }

        return t[m][n];
    }

    // 1D Array
    bool isMatch2(const char *s, const char *p) {
        int m = strlen(s), n = strlen(p);
        vector<bool> dp(m+1, false);
        for(int i=0; i<m; i++) {
            bool diag = dp[0];
            dp[0] = i==0 ? true : false;
            for(int j=1; j<n; j++) {
                int temp = dp[j];
                if(p[j-1]==s[i-1] || p[j-1]=='?')
                    dp[j] = i>0 && diag;
                else if(p[j-1]=='*')
                    dp[j] = dp[j-1] || (i>0 && (diag || dp[j]));
                diag = temp;
            }
        }
        return dp[n];
    }

// better
    // Greedy
    // use example: s = "abedc", p = "?b*c" -> true
    bool isMatch3(string s, string p) {
        int m = s.size(), n = p.size();
        int i = 0, j = 0, lastAsterisk = -1, lastMatch = -1; // lastMatch := last asterisk match

        while (i < m) {
            if (j < n && (s[i] == p[j] || p[j] == '?')) { // current is a match
                i ++;
                j ++;
                continue;
            }
            if (j < n && p[j] == '*') {
                lastAsterisk = j;
                lastMatch = i;
                j ++; // only j ++ when p[j] = '*'
                continue;
            }
            // no match
            if (lastAsterisk == -1)
                return false;
            else {
                j = lastAsterisk + 1; // position of lastAsterisk stay the same
                lastMatch ++;
                i = lastMatch;
            }
        }

        // check if remaining p[j] are all *'s
        while (j < n) {
            if (p[j] != '*')
                return false;
            j ++; // remember to increment j
        }

        return true;
    }

class Solution {
	bool isMatch(string s, int idx1, string p, int idx2) {
		//if(idx1 >= s.size() && idx2 >= p.size() ) return true;
		if(idx1 >= s.size()) {
    		for(int i = idx2; i < p.size(); i++) if(p[i] != '*') return false;
    		return true;
		}
		if(idx2 >= p.size() ) return false;

		while(idx1 < s.size() && idx2 < p.size()) {
			if(s[idx1] == p[idx2] || p[idx2] == '?'){
				idx1++;  idx2++;
			}
			else if(p[idx2] == '*'){
			    if(idx2 -1 >=0 && p[idx2-1] == '*') {
			        idx2++; continue;
			    }
				for(int new_idx1 = s.size(); new_idx1 >= idx1; new_idx1--)
					if(isMatch(s, new_idx1, p, idx2+1))
						return true;
				return false;
			} else
				return false;
		}
		return isMatch(s, idx1, p, idx2);
		/*
		while(idx2 < p.size() && p[idx2] == '*')
			idx2 ++;
		if(idx1 < s.size() || idx2 < p.size())
			return false;
		return true;
		*/
	}
public:
    bool isMatch(string s, string p) {
    	//if(s.empty()) {
    		//if(p.empty()) return true;
    	//	for(char ch: p) if(ch != '*') return false;
    	//	return true;
    	//}
    	//if(p.empty()) return false;

    	return isMatch(s, 0, p, 0);
    }
};

void test_wildcard(){
	Solution sol;
	cout<<sol.isMatch("aab", "*a*b") << endl;
	cout<<sol.isMatch("aa", "*") <<endl;
	cout<<sol.isMatch("abcd", "ab*?") <<endl;
	cout<<sol.isMatch("abcd", "*?d") <<endl;
	cout<<sol.isMatch("", "**") <<endl;

}

int minDepth2(TreeNode* root) {
        if (root == nullptr)
            return 0;
        if (root->left == nullptr && root->right != nullptr)
            return minDepth(root->right) + 1;
        if (root->right == nullptr && root->left != nullptr)
            return minDepth(root->left) + 1;
        else
            return min(minDepth(root->left), minDepth(root->right)) + 1;
    }
    int minDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        vector<TreeNode*> v1, v2;
        // bfs
        int depth = 1;
        v1.push_back(root);
        while(!v1.empty()){
            for(auto& node : v1) {
                if(node->left == nullptr && node->right == nullptr) return depth;
                if(node->left != nullptr) v2.push_back(node->left);
                if(node->right != nullptr) v2.push_back(node->right);
            }
            depth ++;
            v1 = std::move(v2);
        }
        return -1; // error
    }






























