class Solution {
    int get_digit_cnt( int x){
        int cnt = 0;
        while(x!=0){
            cnt ++;
            x /= 10;
        }
        return cnt;
    }
public:
    bool isPalindrome(int x) {
        if (x<0)    return false;
        //x>=0
        const int cnt = get_digit_cnt(x);
        for(int i=1; i<=cnt/2; i++){
            int x2 = x, a=-1, b=-1;

            for( int j=1; j<=cnt+1-i-1; j++){
                if(j==i) {
                    a = x2%10;
                }
                x2 /= 10;
            }
            b = x2 % 10;
            if(a!=b) return false;
        }
        return true;
    }
};
