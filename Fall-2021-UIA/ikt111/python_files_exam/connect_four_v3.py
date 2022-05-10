import random

import ikt111_games

DEPTH = 6

game = ikt111_games.ConnectFour(difficulty="hard")


# This function return the best move
def get_best_move(heuristic, valid_columns):
    temp = -2
    next_move = -1
    # Because the columns were shuffled i dont know which heuristic is for which column, but the heuristic and columns are in the right order
    # Because of that i need to use enumerate
    for it, i in enumerate(valid_columns):
        if temp < heuristic[it]:
            temp = heuristic[it]
            next_move = i
    return next_move


# Main function
def minimax_alpha_beta_pruning(depth, moves, player, alpha, beta):
    # If the depth is 0 it means that i am at the bottom of the tree. So i'll just simulate the moves and return the heuristic for path
    if depth == 0:
        return game.get_heuristic(game.simulate_moves(moves))

    # I cant send in an empty list so i had to make a check if there where any moves
    if moves:
        valid_columns = game.get_all_valid_cols(game.simulate_moves(moves))
        # Im making the columns appear in a random order. If i dint do this the game would be the same every time
        # I noticed that the AI im playing against is not random at all, so he will do exactly the same every time if im not doing anything different
        random.shuffle(valid_columns)

    else:
        valid_columns = game.get_all_valid_cols(game.game_state)
        random.shuffle(valid_columns)

    # Initializing the list with the heuristics for the moves
    heuristic = []

    # It is player 1s turn
    if player == game.player1:
        # Going through every legal move
        for column in valid_columns:
            # Adding the move to the moves list
            moves.append((column, game.player1))
            # Checking if it is a winner move
            if game.is_winner(game.player1, game.simulate_moves(moves)):
                heuristic.append(1)
                alpha = max(alpha, heuristic[-1])
                if alpha >= beta:
                    break
            else:
                # If it is not a winner move, I call the function recursively
                heuristic.append(
                    minimax_alpha_beta_pruning(depth - 1, [(i[0], i[1]) for i in moves], game.player2, alpha, beta))
            if heuristic:
                # I have added alpha beta pruning to make the algorithm a little faster
                alpha = max(alpha, heuristic[-1])
                if alpha >= beta:
                    break
            # After it has checked the move i remove it from the move list
            moves.pop()

        # This checks if it is done. This will only run if the recursion is done
        if DEPTH == depth:
            return get_best_move(heuristic, valid_columns)

        # Returning the move with the maximum heuristics
        return max(heuristic)

    if player == game.player2:

        for column in valid_columns:
            moves.append((column, game.player2))
            if game.is_winner(game.player2, game.simulate_moves(moves)):
                heuristic.append(-1)
                beta = min(beta, heuristic[-1])
                if alpha >= beta:
                    break
            else:
                heuristic.append(
                    minimax_alpha_beta_pruning(depth - 1, [(i[0], i[1]) for i in moves], game.player1, alpha, beta))
            if heuristic:
                beta = min(beta, heuristic[-1])
                if alpha >= beta:
                    break
            moves.pop()
        # Returning the move with the minimum heuristics
        return min(heuristic)


@game.register_ai
def super_ai():
    return minimax_alpha_beta_pruning(DEPTH, [], game.player1, -2, 2)


while True:
    game.start(use_ai=True)
