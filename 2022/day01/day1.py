def part1(lines_threshold=[]):
    max_calories = 0
    max_line = 0
    current_calories = 0
    lines_read = 0

    with open('input.txt') as input:
        for line in input:
            lines_read += 1
            if(line[:-1].isdigit()):
                current_calories += int(line)
                if(current_calories > max_calories and lines_read not in lines_threshold):
                    max_calories = current_calories
                    max_line = lines_read
            else:
                current_calories = 0

    return (max_calories, max_line)

def part2():
    top_three_lines = []
    top_three_sum = 0
    last_line = 0
    last_cals = 0

    for i in range(3):
        last_cals, last_line = part1(lines_threshold=top_three_lines)
        top_three_lines.append(last_line)
        top_three_sum += last_cals

    return top_three_sum



print('Part 1 solution: ', part1()[0])
print('Part 2 solution: ', part2())