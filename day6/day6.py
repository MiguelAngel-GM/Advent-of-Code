from collections import Counter

def solve_puzzle(marker_chars):
    with open('input.txt') as input:
        buffer = input.readline()

    lower_bound = 0
    upper_bound = marker_chars
    processed_chars = marker_chars
    window = ''

    while(upper_bound < len(buffer)):
        window = buffer[lower_bound:upper_bound]
        char_counter = Counter(window)
        
        if(len(char_counter) == marker_chars):
            return processed_chars
        
        lower_bound += 1
        upper_bound += 1
        processed_chars += 1

print('Part 1 solution: ', solve_puzzle(4))
print('Part 2 solution: ', solve_puzzle(14))