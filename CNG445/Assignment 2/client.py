import socket
import tkinter
from threading import Thread
from tkinter import *
from tkinter import messagebox

# Define server settings
HOST = "127.0.0.1"
PORT = 5019

client_socket = None


class ClientThread(Thread):
    def __init__(self, client):
        Thread.__init__(self)
        self.client = client

    def run(self):
        try:
            self.client.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.client.client_socket.connect((HOST, PORT))
            while True:
                response = self.client.client_socket.recv(1024).decode()
                parts = response.split(";")
                if not response:
                    break

                if response == "loginfailure":
                    messagebox.showerror("Login Failed", "Invalid username or password")
                elif parts[0] == "loginsuccess":
                    role = parts[2]
                    if role == "librarian":
                        self.client.show_librarian_panel(parts[1])
                    elif role == "manager":
                        self.client.show_manager_panel(parts[1])
        except Exception as e:
            print(f"Error: {e}")
        finally:
            self.client.client_socket.close()


class Client:
    def __init__(self, root):
        self.root = root
        self.root.title("Login")

        self.frame1 = Frame()
        self.frame1.pack(padx=5, pady=5)

        self.UserNameLabel = Label(self.frame1, text="Username")
        self.UserNameLabel.pack(side=LEFT, padx=5, pady=5)

        self.username_entry = Entry(self.frame1)
        self.username_entry.pack(side=LEFT, padx=5, pady=5)

        self.frame2 = Frame()
        self.frame2.pack(padx=5, pady=5)

        self.PasswordLabel = Label(self.frame2, text="Password")
        self.PasswordLabel.pack(side=LEFT, padx=5, pady=5)

        self.password_entry = Entry(self.frame2, show="*")
        self.password_entry.pack(side=LEFT, padx=5, pady=5)

        self.frame3 = Frame()
        self.frame3.pack(padx=5, pady=5)

        self.LoginButton = Button(self.frame3, text="Login", command=self.login)
        self.LoginButton.pack(padx=5, pady=5)

        self.date_var = StringVar()
        self.client_name_var = StringVar()

        self.client_socket = None
        self.client_thread = ClientThread(self)
        self.client_thread.start()

    def login(self):
        self.client_socket.send(f"login;{self.username_entry.get()};{self.password_entry.get()}".encode())

    def show_manager_panel(self, username):
        manager_panel = Toplevel(self.root)
        manager_panel.title("Manager Panel")

        reports_label = Label(manager_panel, text="REPORTS", font=("Helvetica", 16, "bold"))
        reports_label.grid(row=0, column=0, pady=10)

        report_code_var = StringVar()

        report_options = [
            ("(1) Most rented book overall", "report1"),
            ("(2) Librarian with the highest number of operations", "report2"),
            ("(3) Total generated revenue by the library", "report3"),
            ("(4) Average rental period for 'Harry Potter'", "report4")
        ]

        report_code_var.set(report_options[0][0])

        for index, (text, code) in enumerate(report_options):
            report_button = Radiobutton(manager_panel, text=text, variable=report_code_var, value=code)
            report_button.grid(row=int(index) + 1, column=0, sticky=W)

        def create_report():
            selected_report_code = report_code_var.get()

            if not selected_report_code:
                messagebox.showwarning("Incomplete Information", "Please select a report.")
                return

            # Send the selected report code to the server
            report_message = f"{selected_report_code}"
            self.client_socket.send(report_message.encode())

            # Receive the server's response
            response = self.client_socket.recv(1024).decode()
            parts = response.split(";")

            if parts[0] == selected_report_code:
                messagebox.showinfo("Report", parts[1:])
            else:
                messagebox.showerror("Report Error", "An unexpected error occurred during reporting.")

        create_button = Button(manager_panel, text="Create", command=create_report, width=20)
        create_button.grid(row=len(report_options) + 2, column=0, padx=10)

        close_button = Button(manager_panel, text="Close", command=manager_panel.destroy, width=10)
        close_button.grid(row=len(report_options) + 2, column=1, padx=10)

    def show_librarian_panel(self, username):
        books = [
            ("1", "A Tale of Two Cities by C.Dickens", BooleanVar()),
            ("2", "The Little Prince by A.Exupery", BooleanVar()),
            ("3", "Harry Potter by J.K.Rowling", BooleanVar()),
            ("4", "And Then The Were None by A.Christie", BooleanVar()),
            ("5", "Dream of the Red Chamber by C.Xueqin", BooleanVar()),
            ("6", "The Hobbit by J.Tolkien", BooleanVar()),
            ("7", "She: A History of Adventure by H.Haggard", BooleanVar()),
            ("8", "Vardi Wala Gunda by V.Sharma", BooleanVar()),
            ("9", "The Da Vinci Code by D.Brown", BooleanVar()),
            ("10", "The Alchemist by P.Coelho", BooleanVar())
        ]

        librarian_panel = tkinter.Toplevel(self.root)
        librarian_panel.title(f"Librarian Panel {username}")

        def rent_books():
            selected_books = [bookid[0] for bookid in books if bookid[2].get()]
            selected_date = self.date_var.get()
            selected_client_name = self.client_name_var.get()

            # Check if all required information is provided
            if not selected_books or not selected_date or not selected_client_name:
                messagebox.showwarning("Incomplete Information", "Please select books, enter a date, and client's name")
                return

            # Construct the rent message
            rent_message = f"rent;{username};{selected_client_name};{selected_date};{';'.join(selected_books)}".encode()
            self.client_socket.send(rent_message)
            response = self.client_socket.recv(1024).decode()

            if response == "rentsuccess":
                messagebox.showinfo("Rent Success", "Books rented successfully")
            elif response == "availabilityerror":
                selected_books_info = [book_info[1] for book_info in books if book_info[0] in selected_books]
                messagebox.showerror("Availability Error", f"The books are not available: {', '.join(selected_books_info)}")
            elif response == "renterror":
                messagebox.showerror("Rent Error", "Please return the books you rent first.")

        def return_books():
            selected_date = self.date_var.get()
            selected_client_name = self.client_name_var.get()
            selected_books = [bookid[0] for bookid in books if bookid[2].get()]

            if not selected_books or not selected_date or not selected_client_name:
                messagebox.showwarning("Incomplete Information", "Please select books, enter a date and client's name.")
                return

            # Construct the return operation message
            return_message = f"return;{username};{selected_client_name};{selected_date};{';'.join(map(str, selected_books))}"
            self.client_socket.send(return_message.encode())

            # Receive the server's response
            response = self.client_socket.recv(1024).decode()
            parts = response.split(";")

            if parts[0] == "returnsuccess":
                cost = float(parts[1])
                messagebox.showinfo("Return Success", f"Books returned successfully. Rent fee: ${cost:.2f}")
            elif parts[0] == "returnerror":
                messagebox.showerror("Return Error", "The books were not rented")
            else:
                messagebox.showerror("Return Error", "An unexpected error occurred during returning.")

        for i, book in enumerate(books):
            book_label = Label(librarian_panel, text=book[1])
            book_checkbox = Checkbutton(librarian_panel, variable=book[2])

            book_label.grid(row=int(i), column=0, padx=5, pady=5, sticky=W)
            book_checkbox.grid(row=int(i), column=1, padx=5, pady=5, sticky=W)

        date_label = Label(librarian_panel, text="Date (dd.mm.yyyy): ")
        date_entry = Entry(librarian_panel, textvariable=self.date_var)

        date_label.grid(row=len(books), column=0, padx=5, pady=5, sticky=W)
        date_entry.grid(row=len(books), column=1, padx=5, pady=5, sticky=W)

        clients_name_label = Label(librarian_panel, text="Client's name: ")
        clients_name_entry = Entry(librarian_panel, textvariable=self.client_name_var)

        clients_name_label.grid(row=len(books) + 1, column=0, padx=5, pady=5, sticky=W)
        clients_name_entry.grid(row=len(books) + 1, column=1, padx=5, pady=5, sticky=W)

        rent_button = Button(librarian_panel, text="Rent", command=rent_books)
        return_button = Button(librarian_panel, text="Return", command=return_books)
        close_button = Button(librarian_panel, text="Close", command=librarian_panel.destroy)

        rent_button.grid(row=len(books) + 2, column=0, padx=5, pady=5)
        return_button.grid(row=len(books) + 2, column=1, padx=5, pady=5)
        close_button.grid(row=len(books) + 2, column=2, padx=5, pady=5)


if __name__ == "__main__":
    root = tkinter.Tk()
    app = Client(root)
    root.mainloop()
