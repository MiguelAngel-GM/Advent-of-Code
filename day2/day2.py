def round_score(opponent_move, my_move):
    moves = {'A': 1, 'B': 2, 'C': 3, 'X': 1, 'Y': 2, 'Z': 3}

    if(moves[my_move] == moves[opponent_move]):     # draw
        return moves[my_move] + 3

    loose_condition = moves[my_move] + 1
    if(loose_condition > 3): loose_condition = 1 

    if(moves[opponent_move] == loose_condition):
        return moves[my_move]

    return moves[my_move] + 6     

def part1():
    score = 0
    round = []
    with open('input.txt') as input:
        for line in input:
            round = line.rstrip('\n').split(' ')
            score += round_score(round[0], round[1])
    return score

def choose_move(opponent_move, outcome):
    opp_moves = {'A': 1, 'B': 2, 'C': 3}
    my_moves = {'X': 1, 'Y': 2, 'Z': 3}
    keys = list(my_moves.keys())
    values = list(my_moves.values())
    
    if(outcome == 'X'):  # I loose
        my_move = (opp_moves[opponent_move] - 1)
        if my_move < 1:
            my_move = 3
        return keys[values.index(my_move)]
    elif(outcome == 'Y'):     # The round ends in a draw
        return keys[values.index(opp_moves[opponent_move])]
    else:   # I win
        my_move = (opp_moves[opponent_move] + 1)
        if my_move > 3:
            my_move = 1
        return keys[values.index(my_move)]

def part2():
    score = 0
    round = []
    my_move = 0
    with open('input.txt') as input:
        for line in input:
            round = line.rstrip('\n').split(' ')
            my_move = choose_move(round[0], round[1])
            score += round_score(round[0], my_move)
    return score
            

print('Part 1 solution: ', part1())
print('Part 2 solution: ', part2())