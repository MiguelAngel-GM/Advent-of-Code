def part1():
    cicle = 0
    x_register = 1
    sum_signal_str = 0

    with open('input.txt') as input:
        for line in input:
            instruction = line.split()
        
            cicle += 1
            if cicle in [20, 60, 100, 140, 180, 220]:
                sum_signal_str += cicle * x_register
            
            if len(instruction) > 1:
                cicle += 1
                if cicle in [20, 60, 100, 140, 180, 220]:
                    sum_signal_str += cicle * x_register
                
                increment = int(instruction[1])
                x_register += increment

    return sum_signal_str

def update_sprite_pos(x_register):
    new_sprite_pos = ''

    for _ in range(x_register-1):
        new_sprite_pos += '.'
    
    for _ in range(x_register-1, x_register+2):
        new_sprite_pos += '#'

    for _ in range(x_register+2, 40):
        new_sprite_pos += '.'

    new_sprite_pos = new_sprite_pos[:40]

    return new_sprite_pos

def draw_pixel(crt, sprite_pos, cicle):
    crt[(cicle-1)//40] += sprite_pos[(cicle-1)%40]

def part2():
    cicle = 0
    x_register = 1
    sprite_pos = '###.....................................'
    crt = ['', '', '', '', '', '']

    with open('input.txt') as input:
        for line in input:
            instruction = line.split()

            sprite_pos = update_sprite_pos(x_register)
            cicle += 1
            draw_pixel(crt, sprite_pos, cicle)
            
            if len(instruction) > 1:
                cicle += 1
                draw_pixel(crt, sprite_pos, cicle)
                
                increment = int(instruction[1])
                x_register += increment

    return '\n'.join(crt)


print('Part 1 solution: ', part1())
print('Part 2 solution:')
print(part2())