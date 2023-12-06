def contains(first_range, second_range):
    first_range_int = [int(first_range[0]), int(first_range[1])]
    second_range_int = [int(second_range[0]), int(second_range[1])]
    min_max = [min(first_range_int[0], second_range_int[0]), max(first_range_int[1], second_range_int[1])]
    if(min_max == first_range_int or min_max == second_range_int):
        return True
    return False

def part1():
    pair = []
    count = 0
    
    with open('input.txt') as input:
        for line in input:
            pair = line.rstrip('\n').split(',')
            if(contains(pair[0].split('-'), pair[1].split('-'))):
                count += 1
    return count

def find_overlapping(first_range, second_range):
    if((int(second_range[0]) < int(first_range[0]) and int(second_range[1]) < int(first_range[0])) 
        or (int(second_range[0]) > int(first_range[0]) and int(second_range[0]) > int(first_range[1]))):   
        return False
    return True

def part2():
    pair = []
    count = 0
    
    with open('input.txt') as input:
        for line in input:
            pair = line.rstrip('\n').split(',')
            if(find_overlapping(pair[0].split('-'), pair[1].split('-'))):
                count += 1
    return count


print('Part 1 solution: ', part1())
print('Part 2 solution: ', part2())