from copy import deepcopy


class Game:
    # Initialize the game with the chocolate bar and players
    def __init__(self, rows, cols, mode):
        self.chocolate_bar = ChocolateBar(rows, cols)
        self.players = []
        self.current_player_index = 0
        self.game_mode = mode

    # Add a player to the game
    def add_player(self, player):
        self.players.append(player)

    def start_game(self):
        print("Game Started!")
        current_player = self.players[self.current_player_index]
        # Start the game loop
        while not self.is_game_over():
            self.chocolate_bar.display()
            current_player = self.players[self.current_player_index]
            print(str(current_player.__class__.__name__))
            if self.game_mode == 1:
                print("\n" + str(current_player.__class__.__name__) + " " + str(self.current_player_index) + "' turn:")
            else:
                if current_player.__class__.__name__ == "Human":
                    print("\nHuman's turn:")
                else:
                    print("\n AI's turn:")
            self.play_turn()
        print("Game Over!")
        if self.game_mode == 1:
            print(str(current_player.__class__.__name__) + " " + str(self.current_player_index) + " won!")
        else:
            print(str(self.players[self.current_player_index].__class__.__name__) + " won!")

    def play_turn(self):
        current_player = self.players[self.current_player_index]
        if current_player.move(self.chocolate_bar):
            self.current_player_index = (self.current_player_index + 1) % len(self.players)
        else:
            print("You can't play there. Try again!")

    # Check if the game is over
    def is_game_over(self):
        for player in self.players:
            if player.is_finished(self.chocolate_bar.get_chocolate_bar()):
                return True
        return False


class ChocolateBar:
    # Constructor
    # Fill the board with X and P, where P represents Poisonous square
    def __init__(self, rows, cols):
        self.rows = rows
        self.cols = cols
        self.board = [['X' for _ in range(cols)] for _ in range(rows)]
        self.board[0][0] = 'P'  # Set the top-left square as poisonous

    # Display the chocolate bar
    def display(self):
        print("\n")
        for row in self.board:
            print(' '.join(row))

    # Getter and setter functions
    def get_chocolate_bar(self):
        return self.board

    def set_chocolate_bar(self, board):
        self.board = board

    def is_game_over(self):
        for row in self.get_chocolate_bar():
            for square in row:
                if square == 'X':
                    return False
        return True

    # Set the value of a square on the chocolate bar
    def set_square(self, x, y, element):
        self.board[x][y] = element


class Player:
    # Initialize the player with its position and states
    def __init__(self, row, column):
        self.row = row
        self.column = column
        self.states = []

    # Check if the player has finished the game
    def is_finished(self, chocolate_bar):
        for row in chocolate_bar:
            for square in row:
                if square == 'X' or square == 'P':
                    return False
        return True

    # Get possible moves for the player
    def get_possible_moves(self):
        possible_moves = []

        if self.states:
            for column in range(self.column):
                for row in range(self.row):
                    if self.states[-1][row][column] == 'X' or self.states[-1][row][column] == 'P':
                        possible_moves.append((row, column))

        return possible_moves

    def move(self, board):
        pass


class Human(Player):
    def move(self, board):
        x = int(input("Enter the X coordinate: "))
        y = int(input("Enter the Y coordinate: "))

        self.states.append(deepcopy(board.get_chocolate_bar()))
        if (x, y) in self.get_possible_moves():
            for i in range(x, board.rows):
                for j in range(y, board.cols):
                    self.states[-1][i][j] = ''

            board.set_chocolate_bar(self.states[-1])
            self.states = self.states[:-1]
            return True
        else:
            self.states = self.states[:-1]
            return False


class AI(Player):
    def __init__(self, row, column):
        super().__init__(row, column)
        self.nodes_visited = 0  # Initialize the counter for visited nodes

    def move(self, board):
        self.states.append(deepcopy(board.get_chocolate_bar()))
        _, move = self.minimax(deepcopy(board), 3, True)
        x, y = move

        for i in range(x, board.rows):
            for j in range(y, board.cols):
                self.states[-1][i][j] = ''

        board.set_chocolate_bar(self.states[-1])
        self.states = self.states[:-1]
        print("Number of visited nodes: " + str(self.nodes_visited))
        self.nodes_visited = 0
        return True

    def minimax(self, board, depth, maximizing):
        self.nodes_visited += 1  # Increment the counter for visited nodes
        if depth == 0 or board.is_game_over():
            return self.evaluate(board), None

        possible_moves = self.get_possible_moves()

        if maximizing:
            max_eval = float('-inf')
            best_move = None
            for move in possible_moves:
                new_board = deepcopy(board)
                self.make_move(new_board, move)
                evaluated, _ = self.minimax(new_board, depth - 1, False)
                if evaluated >= max_eval:
                    max_eval = evaluated
                    best_move = move
            return max_eval, best_move
        else:
            min_eval = float('inf')
            best_move = None
            for move in possible_moves:
                new_board = deepcopy(board)
                self.make_move(new_board, move)
                evaluated, _ = self.minimax(new_board, depth - 1, True)
                if evaluated <= min_eval:
                    min_eval = evaluated
                    best_move = move
            return min_eval, best_move

    def make_move(self, board, move):
        x, y = move
        for i in range(x, board.rows):
            for j in range(y, board.cols):
                board.set_square(i, j, '')

    def evaluate(self, board):
        chocolate_bar = board.get_chocolate_bar()
        count = 0
        for row in chocolate_bar:
            count += row.count('X')
        return count


def main():
    # Ask the board size to the user
    m = int(input("Enter the number of rows: "))
    n = int(input("Enter the number of columns: "))

    # Get the game mode from the user. 1 for Human vs Human, 2 for AI vs Human
    game_mode = int(input("\n1) Human vs Human\n2) AI vs Human\nSelect the game mode: "))

    if game_mode == 1:
        # Human vs Human

        # Create two Human players
        player1 = Human(row=m, column=n)
        player2 = Human(row=m, column=n)

        # Create the game
        game = Game(m, n, game_mode)
        game.add_player(player1)
        game.add_player(player2)

        # Start the game
        game.start_game()
    elif game_mode == 2:
        # AI vs Human

        # Ask the user if s/he wants to start first
        start_first = input("Do you want to start first? (yes/no): ")
        # Create an AI and a Human Player
        if start_first == "yes":
            player1 = Human(row=m, column=n)
            player2 = AI(row=m, column=n)
        else:
            player1 = AI(row=m, column=n)
            player2 = Human(row=m, column=n)

        # Create the game
        game = Game(m, n, game_mode)
        game.add_player(player1)
        game.add_player(player2)

        # Start the game
        game.start_game()


if __name__ == "__main__":
    main()
