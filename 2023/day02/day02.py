import re

def parseLine(line):
    red_cubes = []
    green_cubes = []
    blue_cubes = []
    for r in re.findall(r'[0-9]+ red', line):
        red_cubes.append(int(re.match(r'[0-9]+', r).group(0)))
    for g in re.findall(r'[0-9]+ green', line):
        green_cubes.append(int(re.match(r'[0-9]+', g).group(0)))
    for b in re.findall(r'[0-9]+ blue', line):    
        blue_cubes.append(int(re.match(r'[0-9]+', b).group(0)))
    return red_cubes, green_cubes, blue_cubes

def possibleGames():
    game_id = 1
    id_sum = 0
    with open('input.txt') as input_file:
        for line in input_file:
            red_cubes, green_cubes, blue_cubes = parseLine(line)
            if max(red_cubes) <= 12 and max(green_cubes) <= 13 and max(blue_cubes) <= 14:
                id_sum += game_id
            game_id += 1
    return id_sum

def sumPowers():
    power_sum = 0
    with open('input.txt') as input_file:
        for line in input_file:
            red_cubes, green_cubes, blue_cubes = parseLine(line)
            power_sum += max(red_cubes) * max(green_cubes) * max(blue_cubes)
    return power_sum

print('Part 1 solution:', possibleGames())
print('Part 2 solution:', sumPowers())