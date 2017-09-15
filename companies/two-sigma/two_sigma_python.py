

# visit the i-th person
def helper_dfs(friends, i, visited):
    if visited[i]: return
    visited[i] = True
    s = friends[i]
    for j in range(len(s)):
        if s[j] == 'Y':
            # if someone is a friend, visit his friends
            helper_dfs(friends, j, visited)


def friend_circles(friends):
    n = len(friends)
    visited = [False]*n
    count = 0
    for i in range(n):
        if visited[i]: continue
        # get the connected components
        helper_dfs(friends, i, visited)
        count += 1
    return count


def friend_circles4(friends):
    n = len(friends)
    visited = [False]*n
    count = 0
    stk = [] # stack
    for i in range(n):
        if visited[i]: continue
        # get the connected components
        stk.append(i)
        while len(stk) != 0:
            j = stk.pop()
            if visited[j]: continue
            visited[j] = True
            for k in range(n):
                if friends[j][k] == 'Y':
                    stk.append(k)

        count += 1
    return count


# method2: combine graph components
def friend_circles2(friends):
    n = len(friends)
    circles = [i for i in range(n)] # circle_num of each person
    dict = {} # map from circle_num to the circle components
    for i in range(n):
        dict[i] = [i] # initially, each circle only has one person

    for i in range(n):
        for j in range(i+1, n):
            ch = friends[i][j]
            # if i and j are friends, then combine their circles
            if ch == 'Y':
                circle1, circle2 = circles[i], circles[j]
                for k in dict[circle2]:
                    circles[k] = circle1
                dict[circle1].extend(dict[circle2])
                del dict[circle2]

    return len(dict)


from collections import deque 
# using bfs
def friend_circles3(friends):
    n = len(friends)
    visited = [False]*n
    count = 0
    for i in range(n):
        if visited[i]: continue
        q = deque([i])
        while len(q) != 0:
            j = q.pop()
            visited[j] = True
            for k in range(n):
                if visited[k]: continue
                if friends[j][k] == 'Y':
                    q.appendleft(k)
        count += 1
    return count


def run1():
    friends = ['YYNN', 'YYYN', 'NYYN', 'NNNY']
    print friend_circles3(friends)


def get_length(word, word_set, result_saver = {}):
    if len(word) == 1: return 1
    if word in result_saver: 
        return result_saver[word]

    res = 1
    for i in range(0, len(word)):
        new_word = word[0:i] + word[i+1:]
        if new_word in word_set:
            res = max(res, 1 + get_length(new_word, word_set, result_saver))
    result_saver[word] = res
    return res


def string_chains(words):
    if len(words) == 0: return 0

    # words.sort(cmp=lambda x,y: len(x) - len(y))
    words.sort(key = lambda x: len(x), reverse=True)
    word_set = set(words)
    res = 0
    # iterate from the longest word
    for word in words:
        if len(word) <= res: break
        res = max(res, get_length(word, word_set))
    return res


def run2():
    words = ['bdca', 'a', 'b', 'ba', 'bca', 'bda']
    print string_chains(words)


if __name__ == '__main__':
    run1()

