import ikt111_games

snake = ikt111_games.Snake()


# Making a class for the nodes
class Node:

    # This is an initializer for the node
    def __init__(self, position, parent, cost, action):
        self.position = position
        self.action = action
        self.parent = parent
        self.cost = cost
        self.depth = 0
        if parent:
            self.depth = self.parent.depth + 1

    # This is a comparison definition to make it easier to compare if two nodes are at the same position
    def __eq__(self, other):
        return self.position == other.position

    # This function traces back the path when a route to the apple has been found
    def trace(self):
        route = []
        node = self
        while node.parent:
            route.append(node.action)
            node = node.parent
        route.reverse()
        return route

    # Handles the right move option
    def move_right(self):
        # Checking if the move is valid
        if snake.is_legal(self.trace() + ["right"]):
            position = snake.simulate_move(self.position, "right")
            apple = snake.get_apple_position()
            # Creating a new node, and calculating the cost of the node
            new_node = Node(position, self, abs(apple[0] - position[0]) + abs(apple[1] - position[1]) + self.depth + 1,
                            "right")
            return new_node
        else:
            # Returning False if the move is not valid
            return False

    # Handles the left move option
    def move_left(self):
        # Checking if the move is valid
        if snake.is_legal(self.trace() + ["left"]):
            position = snake.simulate_move(self.position, "left")
            apple = snake.get_apple_position()
            # Creating a new node, and calculating the cost of the node
            new_node = Node(position, self, abs(apple[0] - position[0]) + abs(apple[1] - position[1]) + self.depth + 1,
                            "left")
            return new_node
        else:
            # Returning False if the move is not valid
            return False

    # Handles the up move option
    def move_up(self):
        # Checking if the move is valid
        if snake.is_legal(self.trace() + ["up"]):
            position = snake.simulate_move(self.position, "up")
            apple = snake.get_apple_position()
            # Creating a new node, and calculating the cost of the node
            new_node = Node(position, self, abs(apple[0] - position[0]) + abs(apple[1] - position[1]) + self.depth + 1,
                            "up")
            return new_node
        else:
            # Returning False if the move is not valid
            return False

    # Handles the down move option
    def move_down(self):
        # Checking if the move is valid
        if snake.is_legal(self.trace() + ["down"]):
            position = snake.simulate_move(self.position, "down")
            apple = snake.get_apple_position()
            # Creating a new node, and calculating the cost of the node
            new_node = Node(position, self, abs(apple[0] - position[0]) + abs(apple[1] - position[1]) + self.depth + 1,
                            "down")
            return new_node
        else:
            # Returning False if the move is not valid
            return False


def make_route():
    open_list = [Node(snake.get_snake_head_position(), None, 0, None)]
    closed_list = []

    while True:
        if len(open_list) == 0:
            break
        # Sorting the list of nodes based on their cost
        open_list.sort(key=lambda n: n.cost)
        # Adding the first node in the sorted node to the end of the closed list
        closed_list.append(open_list.pop(0))
        # Setting current node to the last node in the closed list
        node = closed_list[-1]
        # Simulating all the moves
        right_node = node.move_right()
        left_node = node.move_left()
        up_node = node.move_up()
        down_node = node.move_down()

        # Checking if the node is valid
        if right_node and right_node not in closed_list and right_node not in open_list:
            if right_node.position == snake.get_apple_position():
                # If the node is a winner it runs the trace function witch return the path of the winning route
                return right_node.trace()
            else:
                # If it is not a winner it is added to the open_list
                open_list.append(right_node)

        # Checking if the node is valid
        if left_node and left_node not in closed_list and left_node not in open_list:
            if left_node.position == snake.get_apple_position():
                # If the node is a winner it runs the trace function witch return the path of the winning route
                return left_node.trace()
            else:
                # If it is not a winner it is added to the open_list
                open_list.append(left_node)

        # Checking if the node is valid
        if up_node and up_node not in closed_list and up_node not in open_list:
            if up_node.position == snake.get_apple_position():
                # If the node is a winner it runs the trace function witch return the path of the winning route
                return up_node.trace()
            else:
                # If it is not a winner it is added to the open_list
                open_list.append(up_node)

        # Checking if the node is valid
        if down_node and down_node not in closed_list and down_node not in open_list:
            if down_node.position == snake.get_apple_position():
                # If the node is a winner it runs the trace function witch return the path of the winning route
                return down_node.trace()
            else:
                # If it is not a winner it is added to the open_list
                open_list.append(down_node)


@snake.register_ai
def super_ai():
    return make_route()


snake.start(use_ai=True)
