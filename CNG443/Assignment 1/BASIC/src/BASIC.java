import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.Scanner;

public class BASIC {
    public static ArrayList<User> users = new ArrayList<User>();
    public static ArrayList<Property> properties = new ArrayList<Property>();

    public static void main(String[] args) {
        PopulateData populateData = new PopulateData();
        users = populateData.users;
        properties = populateData.properties;

        Scanner scanner = new Scanner(System.in);
        int choice;
        int userID;
        int propertyID;

        do {
            menu();
            choice = scanner.nextInt();

            switch (choice) {
                case 1:
                    addUser();
                    break;

                case 2:
                    System.out.print("Please enter the user ID: ");
                    userID = scanner.nextInt();
                    deleteUser(userID);
                    break;

                case 3:
                    System.out.print("Please enter the user ID: ");
                    userID = scanner.nextInt();
                    getUserDetails(userID);
                    break;

                case 4:
                    addProperty();
                    break;

                case 5:
                    System.out.print("Please enter the property ID: ");
                    propertyID = scanner.nextInt();
                    deleteProperty(propertyID);
                    break;

                case 6:
                    System.out.print("Please enter the property ID: ");
                    propertyID = scanner.nextInt();
                    getPropertyDetails(propertyID);
                    break;

                case 7:
                    // Clear the buffer
                    scanner.nextLine();
                    System.out.print("Please enter the user ID: ");
                    userID = scanner.nextInt();
                    System.out.print("Please enter the property ID: ");
                    propertyID = scanner.nextInt();
                    addBooking(userID, propertyID);
                    break;

                case 8:
                    System.out.print("Please enter the user ID: ");
                    userID = scanner.nextInt();
                    getUserBooking(userID);
                    break;

                case 9:
                    System.out.print("Please enter the user ID: ");
                    userID = scanner.nextInt();
                    System.out.print("Please enter the property ID: ");
                    propertyID = scanner.nextInt();
                    getBookingCost(userID, propertyID);
                    break;

                case 10:
                    listUsers();
                    break;

                case 11:
                    listProperties();
                    break;

                case 12:
                    exit();
                    break;
            }
        } while (true);
    }

    /**
     * Checks whether a user with the specified user ID and a property with the specified property ID exist.
     * @param userId The user ID to check for existence.
     * @param propertyId The property ID to check for existence.
     * @return `true` if both the user and the property exist; otherwise, `false`.
     */
    public static boolean isUserAndPropertyExist(int userId, int propertyId) {
        boolean isUserFound = false;
        boolean isPropertyFound = false;

        // Search for the user
        for (User user: users) {
            if (user.getUserId() == userId) {
                isUserFound = true;
                break;
            }
        }

        // Search for the property
        for (Property property: properties) {
            if (property.getPropertyId() == propertyId) {
                isPropertyFound = true;
                break;
            }
        }

        return isUserFound && isPropertyFound;
    }

    /**
     * Calculates the total booking cost for a user and a property based on their respective IDs.
     * If the user or property does not exist, it prints a message indicating their non-existence.
     * @param userId The ID of the user for whom the booking cost is to be calculated.
     * @param propertyId The ID of the property for which the booking cost is to be calculated.
     */
    public static void getBookingCost(int userId, int propertyId) {
        float totalCost = 0;
        if (isUserAndPropertyExist(userId, propertyId)) {
            for (User user: users) {
                if (user.getUserId() == userId) {
                    for (Booking booking: user.getBookings()) {
                        if (booking.getPropertyId() == propertyId) {
                            totalCost += booking.totalCost();
                        }
                    }
                    System.out.println("-------------------");
                    System.out.println("The total cost: " + totalCost);
                    System.out.println("-------------------");

                    break;
                }
            }
        } else {
            System.out.println("The property or user doesn't exist!");
        }
    }

    /**
     * Displays the booking details for a user with the specified user ID.
     * If the user has no bookings, it prints a message indicating that there are no bookings.
     * @param userId The ID of the user for whom booking details are to be displayed.
     */
    public static void getUserBooking(int userId) {
        boolean isUserFound = false;

        for (User user: users) {
            if (user.getUserId() == userId) {
                isUserFound = true;
                if (user.getBookings().isEmpty()) {
                    System.out.println("The user has no bookings.");
                } else {
                    ArrayList<Booking> bookings = new ArrayList<>();
                    bookings = user.getBookings();
                    SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");

                    for (Booking booking: bookings) {
                        String formattedStartDate = dateFormat.format(booking.getStartDate());
                        String formattedEndDate = dateFormat.format(booking.getEndDate());

                        System.out.println("\n----- Booking Info -----");
                        System.out.println("Start Date: " + formattedStartDate);
                        System.out.println("End Date: " + formattedEndDate);
                        System.out.println("------------------------");
                    }

                    break;
                }
            }
        }

        if (!isUserFound) {
            System.out.println("The user doesn't exist!");
        }
    }

    /**
     * Adds a booking for a user and a property based on their respective IDs.
     * Before adding the booking, it checks if the specified user and property exist.
     * If they exist, it prompts the user for booking details with the specified start and end dates.
     * @param userId The ID of the user for whom the booking is being added.
     * @param propertyId The ID of the property for which the booking is being added.
     */
    public static void addBooking(int userId, int propertyId) {
        Scanner scanner = new Scanner(System.in);

        if (isUserAndPropertyExist(userId, propertyId)) {
            // Prompt the information for the booking
            System.out.print("Enter the start date (dd/mm/yyyy): ");
            String userDate = scanner.nextLine();
            Date startDate = parseDate(userDate);
            System.out.print("Enter the end date (dd/mm/yyyy): ");
            userDate = scanner.nextLine();
            Date endDate = parseDate(userDate);

            for (User user: users) {
                if (user.getUserId() == userId) {
                    Booking booking = new Booking(startDate, endDate, getPropertyById(propertyId));
                    user.getBookings().add(booking);
                    break;
                }
            }

            System.out.println("Booking has been successfully added.");
        } else {
            System.out.println("The property or user doesn't exist!");
        }
    }

    /**
     * Return the property with the specified ID. Don't recommended to be used without checking if the
     * property exist.
     * @param propertyId The ID of the property to be returned.
     * @return A Property object.
     */
    public static Property getPropertyById(int propertyId) {
        for (Property property: properties) {
            if (property.getPropertyId() == propertyId) {
                return property;
            }
        }
        return null;
    }

    /**
     * Parses a date string in the format "dd/mm/yyyy" entered by the user and returns a Date object.
     * If the input does not match the expected format, the user is prompted to enter a valid date format.
     * @param userDate The date string to be parsed in "dd/mm/yyyy" format.
     * @return A Date object representing the parsed date.
     */
    public static Date parseDate(String userDate) {
        Scanner scanner = new Scanner(System.in);
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
        Date date = null;

        while (date == null) {
            try {
                date = dateFormat.parse(userDate);
                if (!userDate.equals(dateFormat.format(date))) {
                    date = null;
                    System.out.print("Invalid date format. Please use dd/mm/yyyy. Please try again: ");
                    userDate = scanner.nextLine();
                }
            } catch (ParseException e) {
                System.out.print("Invalid date format. Please use dd/mm/yyyy. Please try again: ");
            }
        }

        return date;
    }

    /**
     * Displays the details of a property with the specified property ID.
     * @param propertyID The ID of the property for which details are to be displayed.
     */
    public static void getPropertyDetails(int propertyID) {
        boolean isPropertyFound = false;

        for (Property property: properties) {
            if (property.getPropertyId() == propertyID) {
                isPropertyFound = true;
                System.out.println("\n------- Property Info -------");
                System.out.println("Property ID: " + property.getPropertyId());
                System.out.println("Number of bedrooms: " + property.getNoBedrooms());
                System.out.println("Number of rooms: " + property.getNoRooms());
                System.out.println("City: " + property.getCity());
                System.out.println("Price per day: " + property.getPricePerDay());
                System.out.println("-----------------------------\n");
            }
        }

        if (!isPropertyFound) {
            System.out.println("Property with ID " + propertyID + " not found.");
        }
    }

    /**
     * Deletes a property with the specified property ID from the list of properties.
     * @param propertyId The ID of the property to be deleted.
     */
    public static void deleteProperty(int propertyId) {
        boolean isPropertyDeleted = false;

        Iterator<Property> iterator = properties.iterator();
        while (iterator.hasNext()) {
            Property property = iterator.next();
            if (property.getPropertyId() == propertyId) {
                iterator.remove(); // Safe removal
                isPropertyDeleted = true;
            }
        }

        if (isPropertyDeleted) {
            System.out.println("Property has been deleted successfully.");
        } else {
            System.out.println("Property with ID: " + propertyId + " not found.");
        }
    }

    /**
     * Prompts the user to enter details for a new property with the specified the number of bedrooms, number of rooms,
     * city, price per day, and host ID. Creates a Property object with the entered details and adds it to the
     * properties list.
     */
    public static void addProperty() {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Please enter the number of bedrooms: ");
        int noBedrooms = scanner.nextInt();
        System.out.print("Please enter the number of rooms: ");
        int noRooms = scanner.nextInt();

        // Consume the newline character
        scanner.nextLine();

        System.out.print("Please enter the city: ");
        String city = scanner.nextLine();
        System.out.print("Please enter the price per day: ");
        float pricePerDay = scanner.nextFloat();
        System.out.print("Please enter the host ID: ");
        int hostId = scanner.nextInt();

        Property property = new Property(properties.size(), noBedrooms, noRooms, city, pricePerDay, hostId);
        properties.add(property);
    }

    /**
     * Displays the details of a user with the specified user ID.
     * @param userId The ID of the user for which details are to be displayed.
     */
    public static void getUserDetails(int userId) {
        boolean userFound = false;
        for (User user: users) {
            if (user.getUserId() == userId) {
                userFound = true;
                System.out.println("\n------- User Info -------");
                System.out.println("User ID: " + user.getUserId());

                // Parse the date into format "dd/mm/yyyy"
                SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
                String formattedBirthday = dateFormat.format(user.getDateOfBirth());

                System.out.println("Birthday: " + formattedBirthday);
                System.out.println("Firstname: " + user.getFirstName());
                System.out.println("Lastname: " + user.getLastName());
                System.out.println("-------------------------\n");
            }
        }

        if (!userFound) {
            System.out.println("User with ID " + userId + " not found.");
        }
    }

    /**
     * Deletes a user with the specified user ID from the users list.
     * @param userId The ID of the user to be deleted.
     */
    public static void deleteUser(int userId) {
        boolean isUserDeleted = false;

        Iterator<User> iterator = users.iterator();
        while (iterator.hasNext()) {
            User user = iterator.next();
            if (user.getUserId() == userId) {
                iterator.remove(); // Safe removal
                isUserDeleted = true;
            }
        }

        if (isUserDeleted) {
            System.out.println("User has been successfully deleted.");
        } else {
            System.out.println("User has not been found.");
        }
    }


    /** Add user by prompting their birthday, the first name and the last name.
     * Parse the date by using SimpleDateFormat, and ask the user again if s/he
     * enters the date incorrectly.
     */
    public static void addUser() {
        Scanner scanner = new Scanner(System.in);

        // Parse the date
        System.out.print("Enter the date of birth (dd/mm/yyyy): ");
        String userInput = scanner.nextLine();
        Date dateOfBirth = parseDate(userInput);

        System.out.print("Enter the first name: ");
        String firstName = scanner.nextLine();

        System.out.print("Enter the last name: ");
        String lastName = scanner.nextLine();

        User user = new User(users.size(), dateOfBirth, firstName, lastName);
        users.add(user);

        System.out.println("\nUser has been successfully added.");
    }

    /** Terminate the program
     */
    public static void exit() {
        System.exit(0);
    }

    /** Display properties with details
     */
    public static void listProperties() {
        for (Property property: properties) {
            getPropertyDetails(property.getPropertyId());
        }
    }

    /** Display all the users with their details
     */
    public static void listUsers() {
        for (User user: users) {
            getUserDetails(user.getUserId());
        }
    }

    /** Display the interaction menu to the user
     */
    public static void menu() {
        System.out.println("----------------------------------");
        System.out.println("1.  Add user");
        System.out.println("2.  Delete user");
        System.out.println("3.  Get user details");
        System.out.println("4.  Add property");
        System.out.println("5.  Delete property");
        System.out.println("6.  Get property details");
        System.out.println("7.  Add booking");
        System.out.println("8.  Get booking information");
        System.out.println("9.  Get the booking cost");
        System.out.println("10. List users");
        System.out.println("11. List properties");
        System.out.println("12. Exit");
        System.out.println("----------------------------------");
        System.out.print("Please select your choice: ");
    }

    /**
     * Constructor with the specified ArrayList of User, and ArrayList of Property.
     * @param users The specified users.
     * @param properties The specified properties.
     */
    public BASIC(ArrayList<User> users, ArrayList<Property> properties) {
        BASIC.users = users;
        BASIC.properties = properties;
    }

    /** Constructor with the specified ArrayList of User
     */
    public BASIC(ArrayList<User> users) {
        BASIC.users = users;
    }

    /** Default constructor
     */
    public BASIC() {
    }
}
