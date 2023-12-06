def find_common_item(first_compartment, second_compartment):
    for item in first_compartment:
        if(second_compartment.find(item) != -1):
            if(ord(item) > 64 and ord(item) < 91):
                return ord(item) - 38
            else:
                return ord(item) - 96 

def part1():
    first_compartment = ''
    second_compartment = ''
    sum = 0
    with open('input.txt') as input:
        for line in input:
            first_compartment = line[:len(line)//2]
            second_compartment = line[len(line)//2:]
            sum += find_common_item(first_compartment, second_compartment)
    return sum

def find_badge(group_items):
    for item in group_items[0]:
        if(group_items[1].find(item) != -1 and group_items[2].find(item) != -1):
            if(ord(item) > 64 and ord(item) < 91):
                return ord(item) - 38
            else:
                return ord(item) - 96 

def part2():
    group_items = []
    lines_read = 0
    sum = 0
    with open('input.txt') as input:
        for line in input:
            lines_read += 1
            group_items.append(line)
            if(lines_read % 3 == 0):
                sum += find_badge(group_items)
                group_items = []
    return sum
            


print('Part 1 solution: ', part1())
print('Part 2 solution: ', part2())
