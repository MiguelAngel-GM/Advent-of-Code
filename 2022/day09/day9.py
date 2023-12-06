def move_tail(tail_pos, head_pos):
    dx = 0 if head_pos[0] == tail_pos[0] else (head_pos[0] - tail_pos[0]) / abs(head_pos[0] - tail_pos[0])
    dy = 0 if head_pos[1] == tail_pos[1] else (head_pos[1] - tail_pos[1]) / abs(head_pos[1] - tail_pos[1])
    
    return (tail_pos[0] + dx, tail_pos[1] + dy)


def part1():
    tail_visited = [(0, 0)]
    head_pos = [0, 0]

    with open('input.txt') as input:
        for line in input:
            direction, moves = line.split()
            for _ in range(int(moves)):
                if direction == 'U':
                    head_pos[1] += 1
                elif direction == 'D':
                    head_pos[1] -= 1
                elif direction == 'R':
                    head_pos[0] += 1
                else:
                    head_pos[0] -= 1
                
                if abs(head_pos[0] - tail_visited[-1][0]) > 1 or abs(head_pos[1] - tail_visited[-1][1]) > 1:
                    tail_visited.append(move_tail(tail_visited[-1], head_pos))

    return len(set(tail_visited))


def part2():
    tail_visited = set()
    knots_pos = [[0, 0] for _ in range(10)]

    with open('input.txt') as input:
        for line in input:
            direction, moves = line.split()
            for _ in range(int(moves)):

                if direction == 'U':
                    knots_pos[0][1] += 1
                elif direction == 'D':
                    knots_pos[0][1] -= 1
                elif direction == 'R':
                    knots_pos[0][0] += 1
                else:
                    knots_pos[0][0] -= 1
                
                for i in range(len(knots_pos)-1):
                    if abs(knots_pos[i][0] - knots_pos[i+1][0]) > 1 or abs(knots_pos[i][1] - knots_pos[i+1][1]) > 1:
                        knots_pos[i+1] = list(move_tail(knots_pos[i+1], knots_pos[i]))
                tail_visited.add(tuple(knots_pos[-1]))

    return len(tail_visited)

print('Part 1 solution: ', part1())
print('Part 2 solution: ', part2())