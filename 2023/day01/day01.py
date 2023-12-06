import re

def parseLine(line, part):
    if part == 1:
        all_digits = re.sub('[a-z]|\n', '', line)
    else:
        all_digits = ''
        letters_to_digits = {'one': '1', 'two': '2', 'three': '3', 'four': '4', 'five': '5', 
                             'six': '6', 'seven': '7', 'eight': '8', 'nine': '9'}
        for i, c in enumerate(line):
            if c.isdigit():
                all_digits += c
            for k in letters_to_digits.keys():
                if line[i:].startswith(k):
                    all_digits += letters_to_digits[k]
    
    return int(all_digits[0] + all_digits[len(all_digits)-1])

def sumCalibrationValues(part):
    total = 0
    
    with open('input.txt') as input_file:
        for line in input_file:
            value = parseLine(line, part)
            total += value

    return total

print('Part 1 solution:', sumCalibrationValues(1))
print('Part 2 solution:', sumCalibrationValues(2))