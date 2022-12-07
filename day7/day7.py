def read_terminal(input, sizes):
    current_dir = ''
    previous_dirs = []
    
    for line in input:
        if line[0] == '$':
            command = line.rstrip('\n').split()
            if command[1] == 'cd':
                if command[2] == '..':
                    current_dir = previous_dirs[-1]
                    previous_dirs.pop()
                else:
                    previous_dirs.append(current_dir)
                    current_dir = previous_dirs[-1] + '/' + command[2]  # This is a mess but it works :)
                if current_dir not in sizes.keys():
                    sizes[current_dir] = 0
        else:
            file_size = line[0:(line.index(' '))]
            if file_size.isdigit():
                sizes[current_dir] += int(file_size)
                for dir in previous_dirs[1:]:
                    sizes[dir] += int(file_size)

def part1():
    sum = 0
    sizes = {}
    
    with open('input.txt') as input:
        read_terminal(input, sizes)

    for size in sizes.values():
        if size <= 100000:
            sum += size
    return sum

def part2():
    unused_space = 0
    space_to_free = 0
    size_freed = 30000000
    sizes = {}

    with open('input.txt') as input:
        read_terminal(input, sizes)

    unused_space = 70000000 - list(sizes.values())[0]
    space_to_free = 30000000 - unused_space

    for size in sizes.values():
        if size < size_freed and size >= space_to_free:
            size_freed = size

    return size_freed

print('Part 1 solution: ', part1())
print('Part 2 solution: ', part2())