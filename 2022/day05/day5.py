def get_move(line):
    move = line.rstrip('\n').split()
    for element in move:
        if not element.isdigit():
            move.remove(element)
    return move

def move_crate(move, stacks, crane_model):
    crates = int(move[0])
    origin = int(move[1])-1
    destiny = int(move[2])-1
    if crane_model == 9000:
        for i in range(crates):
            stacks[destiny].append(stacks[origin].pop())
    else:
        for i in range(crates):
            stacks[destiny].append(stacks[origin][-(crates-i)])
            stacks[origin].pop(-(crates-i))

def get_solution(stacks):
    solution = ''
    for stack in stacks:
        solution += stack[-1]
    return solution
    

def part1():
    stacks = [
        ['R', 'N', 'P', 'G'],
        ['T', 'J', 'B', 'L', 'C', 'S', 'V', 'H'],
        ['T', 'D', 'B', 'M', 'N', 'L'],
        ['R', 'V', 'P', 'S', 'B'],
        ['G', 'C', 'Q', 'S', 'W', 'M', 'V', 'H'],
        ['W', 'Q', 'S', 'C', 'D', 'B', 'J'],
        ['F', 'Q', 'L'],
        ['W', 'M', 'H', 'T', 'D', 'L', 'F', 'V'],
        ['L', 'P', 'B', 'V', 'M', 'J', 'F']
    ]
    move = []

    with open('input.txt') as input:
        for line in input:
            move = get_move(line)
            move_crate(move, stacks, 9000)
  
    return get_solution(stacks)

def part2():
    stacks = [
        ['R', 'N', 'P', 'G'],
        ['T', 'J', 'B', 'L', 'C', 'S', 'V', 'H'],
        ['T', 'D', 'B', 'M', 'N', 'L'],
        ['R', 'V', 'P', 'S', 'B'],
        ['G', 'C', 'Q', 'S', 'W', 'M', 'V', 'H'],
        ['W', 'Q', 'S', 'C', 'D', 'B', 'J'],
        ['F', 'Q', 'L'],
        ['W', 'M', 'H', 'T', 'D', 'L', 'F', 'V'],
        ['L', 'P', 'B', 'V', 'M', 'J', 'F']
    ]
    move = []

    with open('input.txt') as input:
        for line in input:
            move = get_move(line)
            move_crate(move, stacks, 9001)

    return get_solution(stacks)


print('Part 1 solution: ', part1())
print('Part 2 solution: ', part2())