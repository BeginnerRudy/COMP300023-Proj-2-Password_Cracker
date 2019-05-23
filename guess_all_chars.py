from __future__ import division
import numpy

# read the txt file
common_pwd = open("./common_passwords.txt", "r")
pwds = common_pwd.read().split('\n')

# count frequency of each char
freqency_dict = {}
total_num_char = 0
for pwd in pwds:
    for char in pwd:
        if char not in list(freqency_dict.keys()):
            freqency_dict[char] = 1
        else:
            freqency_dict[char] += 1
        total_num_char += 1

# calculate the probability
freq_list = []
for key, value in list(freqency_dict.items()):
    value /= total_num_char

for key, value in list(freqency_dict.items()):
    freq_list.append([key, value])

freq_list.sort(key = lambda x:x[1], reverse = True)

print("symbol prob")
for i in list(range(len(freq_list) - 1)):
    print(str(freq_list[i][0]) + "     : " + str(freq_list[i][1]))
common_pwd.close()

