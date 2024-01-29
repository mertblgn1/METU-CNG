import socket
import threading
from threading import *
from datetime import datetime
from collections import Counter

# Define file paths
USERS_FILE = "users.txt"
BOOKS_FILE = "items.txt"
OPERATIONS_FILE = "operations.txt"

# Define server settings
HOST = "127.0.0.1"
PORT = 5019

# Initialize thread lock
lock = RLock()

# Initialize global variables
users = []
items = []
operations = []


def load_data():
    with lock:
        global users
        global items
        global operations

        users = []
        items = []
        operations = []

        # Load data from users.txt
        try:
            with open(USERS_FILE, "r") as users_file:
                for line in users_file:
                    user_data = line.strip().split(";")
                    users.append(user_data)
        except FileNotFoundError:
            print(f"Error: {USERS_FILE} not found.")

        # Load data from books.txt
        try:
            with open(BOOKS_FILE, "r") as books_file:
                for line in books_file:
                    book_data = line.strip().split(";")
                    items.append(book_data)
        except FileNotFoundError:
            print(f"Error: {BOOKS_FILE} not found.")

        # Load data from operations.txt
        try:
            with open(OPERATIONS_FILE, "r") as operations_file:
                for line in operations_file:
                    operation_data = line.strip().split(";")
                    operations.append(operation_data)
        except FileNotFoundError:
            print(f"Error: {OPERATIONS_FILE} not found.")


def authenticate_user(username, password):
    with lock:
        # Check if the user exists in the user.txt file
        for user in users:
            stored_username, stored_password, role = user
            if username == stored_username and password == stored_password:
                return role

        return None


def rent_book(librarian_name, client_username, date, item_ids):
    with lock:
        # Check if the user has returned all previously rented books
        if has_unreturned_books(client_username):
            return "renterror"

        for item_id in item_ids:
            copiesAvailable = int(items[int(item_id) - 1][-1])
            if copiesAvailable <= 0:
                return "availabilityerror"

        # Perform the rent
        update_copies_available(item_ids)

        # Add operation record to operations.txt
        record_rent_operation(librarian_name, client_username, date, item_ids)
        save_items()

        return "rentsuccess"


def record_rent_operation(librarian_name, client_username, date, item_ids):
    with lock:
        rent_operation = ["rent", librarian_name, client_username, date] + item_ids
        operations.append(rent_operation)
        save_operations()


def save_items():
    try:
        with open(BOOKS_FILE, "w") as books_file:
            for item in items:
                books_file.write(";".join(item) + "\n")
    except FileNotFoundError:
        print(f"Error: {OPERATIONS_FILE} not found.")
    load_data()


def update_copies_available(item_ids):
    for item_id in item_ids:
        item_index = int(item_id) - 1
        if 0 <= item_index < len(items):
            copies_available = int(items[item_index][-1])
            if copies_available > 0:
                items[item_index][-1] = str(copies_available - 1)


def has_unreturned_books(client_username):
    with lock:
        for operation in operations:
            if operation[2] == client_username and operation[0] == "rent":
                rented_item_ids = operation[4:]
                for return_operation in operations:
                    if (
                        return_operation[1] == client_username
                        and return_operation[0] == "return"
                        and return_operation[5:] == rented_item_ids
                    ):
                        # The user has returned the rented books
                        break
                else:
                    # No corresponding return operation found, meaning the user hasn't returned the books
                    return True
    return False


def is_book_rented(client_username, item_id):
    rent_counter = 0
    return_counter = 0

    for operation in operations:
        if item_id in operation[4:]:
            if operation[0] == 'rent' and operation[2] == client_username:
                rent_counter += 1
            elif operation[0] == 'return' and operation[2] == client_username:
                return_counter += 1

    return rent_counter > return_counter


def is_book_returned(client_username, item_id):
    return not is_book_rented(client_username, item_id)


def record_return_operation(librarian_name, client_username, date, return_cost, item_ids):
    operation = ["return", librarian_name, client_username, date, return_cost] + item_ids
    operations.append(operation)
    save_operations()


def return_book(librarian_name, client_username, date, item_ids):
    with lock:
        # Check if the books are rented and not returned
        for item_id in item_ids:
            if not is_book_rented(client_username, item_id):
                return "returnerror"

        # Check if the books have already been returned in a previous operation
        for item_id in item_ids:
            if is_book_returned(client_username, item_id):
                print("here return")
                return "returnerror"

        # Calculate return cost and update copiesAvailable
        return_cost = calculate_return_cost(item_ids, client_username, date)
        update_copies_available(item_ids)

        # Add operation to operations.txt
        record_return_operation(librarian_name, client_username, date, str(return_cost), item_ids)

        return f"returnsuccess;{return_cost:.2f}"


def calculate_return_cost(item_ids, client_username, date):
    total_cost = 0.0

    for item_id in item_ids:
        for operation in operations:
            if operation[0] == 'rent' and item_id in operation[4:] and operation[2] == client_username:
                price_per_day = float(items[int(item_id) - 1][-2])
                rental_date = datetime.strptime(operation[3], "%d.%m.%Y")
                print(rental_date)

                return_date = datetime.strptime(date, "%d.%m.%Y")
                print(return_date)
                rental_days = (return_date - rental_date).days
                total_cost += rental_days * price_per_day

    return total_cost


def get_rental_date(item_id):
    for operation in operations:
        if operation[0] == 'rent' and item_id in operation[4:]:
            date = datetime.strptime(operation[3], "%d.%m.%Y")
            return date
    return None


def save_operations():
    try:
        with open(OPERATIONS_FILE, "w") as operations_file:
            for operation in operations:
                operations_file.write(";".join(operation) + "\n")
    except FileNotFoundError:
        print(f"Error: {OPERATIONS_FILE} not found.")
    load_data()


def statistics_request(report_code):
    with lock:
        if report_code == "report1":
            books = [
                ("1", "A Tale of Two Cities by C.Dickens"),
                ("2", "The Little Prince by A.Exupery"),
                ("3", "Harry Potter by J.K.Rowling"),
                ("4", "And Then The Were None by A.Christie"),
                ("5", "Dream of the Red Chamber by C.Xueqin"),
                ("6", "The Hobbit by J.Tolkien"),
                ("7", "She: A History of Adventure by H.Haggard"),
                ("8", "Vardi Wala Gunda by V.Sharma"),
                ("9", "The Da Vinci Code by D.Brown"),
                ("10", "The Alchemist by P.Coelho")
            ]

            # Filter rent operations
            rent_operations = [operation for operation in operations if operation[0] == "rent"]

            # Extract book IDs from the rent operations
            rented_book_ids = [book_id for operation in rent_operations for book_id in operation[4:]]

            # Count occurrences of each book ID
            book_counts = Counter(rented_book_ids)

            # Find the most rented books
            most_rented_count = book_counts.most_common(1)[0][1]
            most_rented_books = [book_id for book_id, count in book_counts.items() if count == most_rented_count]
            most_rented_books_info = [book_info[1] for book_info in books if book_info[0] in most_rented_books]
            return f"report1;Most rented book(s) overall: {';'.join(most_rented_books_info)}"
        elif report_code == "report2":
            librarian_operations = Counter()

            for operation in operations:
                librarian_name = operation[1]

                # Count operations
                librarian_operations[librarian_name] += 1

            # Find the maximum
            max_operations = max(librarian_operations.values())

            # Find the librarians with the highest number of operations
            librarians_with_highest_operations = [librarian for librarian, count in librarian_operations.items() if count == max_operations]

            return f"report2;The librarian(s) who have the most operations: {';'.join(librarians_with_highest_operations)}"
        elif report_code == "report3":
            total_revenue = 0.0

            for operation in operations:
                if operation[0] == "return":
                    total_revenue += float(operation[4])

            return f"report3;The total revenue is: {total_revenue}"
        elif report_code == "report4":
            total_rental_days = 0
            rental_count = 0

            for i in range(len(operations)):
                if operations[i][0] == "rent" and "3" in operations[i][4:]:
                    rental_date = datetime.strptime(operations[i][3], "%d.%m.%Y")
                    client_username = operations[i][2]

                    # Check for corresponding return operation
                    for j in range(i + 1, len(operations)):
                        if operations[j][0] == "return" and operations[j][2] == client_username and "3" in \
                                operations[j][5:]:
                            return_date = datetime.strptime(operations[j][3], "%d.%m.%Y")
                            rental_days = (return_date - rental_date).days
                            total_rental_days += rental_days
                            rental_count += 1
                            break  # Break after finding the return operation

            # Calculate average rental period
            if rental_count > 0:
                average_rental_period = total_rental_days / rental_count
            else:
                average_rental_period = 0

            return f"report4;The average rental period is: {average_rental_period}"


def client_connection(client_socket):
    try:
        # Perform initial connection setup, send "connectionsuccess" message
        client_socket.send("connectionsuccess".encode("utf-8"))

        while True:
            # Receive data from the client
            data = client_socket.recv(1024).decode("utf-8")
            if not data:
                break

            # Parse the received message
            parts = data.split(";")
            command = parts[0]

            if command == "login":
                username = parts[1]
                password = parts[2]
                role = authenticate_user(username, password)
                if role:
                    response = f"loginsuccess;{username};{role}"
                else:
                    response = "loginfailure"
                client_socket.send(response.encode())
            elif command == "rent":
                librarian_name = parts[1]
                client_username = parts[2]
                date = parts[3]
                item_ids = parts[4:]
                response = rent_book(librarian_name, client_username, date, item_ids)
                client_socket.send(response.encode())
            elif command == "return":
                librarian_name = parts[1]
                client_username = parts[2]
                date = parts[3]
                item_ids = parts[4:]
                response = return_book(librarian_name, client_username, date, item_ids)
                client_socket.send(response.encode())
            elif command == "report1":
                message = statistics_request(command)
                client_socket.send(message.encode())
            elif command == "report2":
                message = statistics_request(command)
                client_socket.send(message.encode())
            elif command == "report3":
                message = statistics_request(command)
                client_socket.send(message.encode())
            elif command == "report4":
                message = statistics_request(command)
                client_socket.send(message.encode())

    except Exception as e:
        print(f"Error: {str(e)}")
    finally:
        client_socket.close()


def main():
    load_data()

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((HOST, PORT))
    server_socket.listen()

    try:
        while True:
            client_socket, client_address = server_socket.accept()
            client_thread = threading.Thread(target=client_connection, args=(client_socket,))
            client_thread.start()
    except KeyboardInterrupt:
        print("Server shutting down.")
    finally:
        server_socket.close()


if __name__ == "__main__":
    main()
