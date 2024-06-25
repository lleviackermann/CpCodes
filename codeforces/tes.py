# class Solution:
#     def arithmetic_slices(self, arr, n) -> int:
#         ans = 0  
#         store = [defaultdict(int) for _ in range(n)]

#         for start in range(1, n):
#             for end in range(start):
#                 diff = arr[start] - arr[end]
#                 store[start][diff] += 1  
#                 if diff in store[end]:
#                     store[start][diff] += store[end][diff]
#                     ans += store[end][diff]

#         return ans
    
# from bisect import bisect

# class Solution:
#     arr = []
#     st = 1
#     en = 100000
#     for start in range(st, en):
#         word1 = int(str(start) + str(start)[::-1])**2
#         word2 = int(str(start)[:-1]  + str(start)[::-1])**2
#         if str(word1) == str(word1)[::-1]: arr += [word1]
#         if str(word2) == str(word2)[::-1]: arr += [word2]

#     arr = sorted(list(set(arr)))

#     def super_palindrome(self, s1, s2):
#         return bisect(self.arr, int(s2)) - bisect(self.arr, int(s1)-1)


# class Solution:
#     def countDigitOne(self, n):
#         ans = 0
#         co = 10
#         zero = 0
#         one = 1
#         temporary = 1
#         while temporary <= n:
#             divider = temporary * co
#             ans += (n // divider) * temporary
#             ans += min(max(n % divider - temporary + one, zero), temporary)
#             temporary *= co
#         return ans 


# class Solution:
#     def minDistance(self, first, second):
#         fir=len(first)+1
#         sec=len(second)+1
#         store=[[-1 for iter in range(sec)] for iter in range(fir)]
#         for st in range(fir):
#             for en in range(sec):
#                 if st==0:
#                     store[st][en]=en
#                 elif en==0:
#                     store[st][en]=i
#                 elif first[st-1]==second[en-1]:
#                     store[st][en]=store[i-1][en-1]
#                 else:
#                     store[st][en]=1+min(store[st-1][en],min(store[st-1][en-1],store[st][en-1]))
#         return store[fir-1][sec-1]


class Solution:
    def maxProfit(self, arra, n, maxt):
        store = [[[0 for emp in range(maxt+1)]for emp in range(2)]for emp in range(n+1)]
        for i in range(n-1,-1,-1):
            for fir in range(2):
                for sec in range(1,maxt+1):
                    if fir == 0:
                        store[i][fir][sec] = max(0+store[i+1][0][sec],-arra[i]+store[i+1][1][sec])
                    elif fir == 1: # Selling 
                        store[i][fir][sec] = max(0+store[i+1][1][sec], arra[i]+store[i+1][0][sec-1])
        return store[0][0][maxt]
    
# def sort_array(self, nums, length):
#         ans = sorted(nums)
#         return ans