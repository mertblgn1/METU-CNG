import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.DateTimeException;
import java.time.LocalDate;
import java.time.ZoneId;
import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.Scanner;

/**
 * The main class for managing users, properties, and bookings in a basic property management system.
 * This class provides a simple text-based menu interface for user interaction.
 *
 * @author Mert Can Bilgin
 * @version 1.0
 */
public class BASIC {
    public static ArrayList<User> users = new ArrayList<>();
    public static ArrayList<Property> properties = new ArrayList<>();
    public static int registeredUsers;
    public static int registeredProperties;

    /**
     * Perform the operations, and manage the system.
     * @param args The arguments.
     */
    public static void main(String[] args) {
        String s1 = "hami";
        String s2 = "hami";
        System.out.println(s1.startsWith("ha"));
        PopulateData populateData = new PopulateData();
        users = populateData.users;
        properties = populateData.properties;
        registeredUsers = users.size();
        registeredProperties = properties.size();

        Scanner scanner = new Scanner(System.in);
        int choice, userID, propertyID;

        do {
            menu();
            choice = scanner.nextInt();
            scanner.nextLine();

            switch (choice) {
                case 1:
                    addUser();
                    break;
                case 2:
                    System.out.print("Enter the user ID you want to delete: ");
                    userID = scanner.nextInt();
                    scanner.nextLine();
                    deleteUser(userID);
                    break;
                case 3:
                    System.out.print("Enter the user ID: ");
                    userID = scanner.nextInt();
                    getUserDetails(userID);
                    break;
                case 4:
                    addProperty();
                    break;
                case 5:
                    System.out.print("Enter the property ID you want to delete: ");
                    propertyID = scanner.nextInt();
                    scanner.nextLine();
                    deleteProperty(propertyID);
                    break;
                case 6:
                    System.out.print("Enter the property ID: ");
                    propertyID = scanner.nextInt();
                    getPropertyDetails(propertyID);
                    break;
                case 7:
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
                    scanner.nextLine();
                    getBookingCost(userID, propertyID);
                    break;
                case 10:
                    System.out.print("Please enter the property ID: ");
                    propertyID = scanner.nextInt();
                    scanner.nextLine();
                    System.out.print("What is your review: ");
                    String review = scanner.nextLine();
                    addInspectionToProperty(propertyID, review);
                    break;
                case 11:
                    listUsers();
                    break;
                case 12:
                    listProperties();
                    break;
                case 13:
                    System.out.print("Enter the first property ID: ");
                    int propertyID1 = scanner.nextInt();
                    System.out.print("Enter the second property ID: ");
                    int propertyID2 = scanner.nextInt();
                    comparePropertyPricesPerDay(propertyID1, propertyID2);
                    break;
            }
        } while (choice != 14);
    }

    /**
     * Compare the properties' prices per day
     * @param propertyId1 First property ID to be compared
     * @param propertyId2 Second property ID to be compared
     */
    public static void comparePropertyPricesPerDay(int propertyId1, int propertyId2) {
        try {
            if (getPropertyById(propertyId1).compareTo(getPropertyById(propertyId2)) == 1) {
                System.out.println("Property ID " + propertyId2 + "is cheaper");
            } else if (getPropertyById(propertyId1).compareTo(getPropertyById(propertyId2)) == -1) {
                System.out.println("Property ID " + propertyId1 + " is cheaper");
            } else {
                System.out.println("They have the same price");
            }
        } catch (NullPointerException e) {
            System.out.println(e.getMessage());
        }
    }

    /**
     * Add an inspection to the property.
     * @param propertyId The property ID.
     * @param inspectionText The inspection text.
     */
    public static void addInspectionToProperty(int propertyId, String inspectionText) {
        boolean propertyFound = false;
        for (Property property: properties) {
            if (property.getPropertyId() == propertyId) {
                propertyFound = true;

                Date date = new Date();
                try {
                    // Get current date
                    LocalDate today = LocalDate.now();
                    date = Date.from(today.atStartOfDay(ZoneId.systemDefault()).toInstant());
                } catch (DateTimeException e) {
                    System.err.println("Error converting LocalDate to Date: " + e.getMessage());
                }

                if (property.getInspections().containsKey(date)) {
                    System.out.println("An inspection for this date already exists.");
                } else {
                    try {
                        property.getInspections().put(date, inspectionText);
                        System.out.println("Inspection added successfully.");
                    } catch (NullPointerException e) {
                        System.out.println(e.getMessage());
                    }
                }
            }
        }

        if (!propertyFound) {
            System.out.println("Property doesn't exist");
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
            if (user.getUserId() == userId && user instanceof Customer customer) {
                isUserFound = true;
                if (customer.getBookings().isEmpty()) {
                    System.out.println("The user has no bookings.");
                } else {
                    ArrayList<Booking> bookings;
                    bookings = customer.getBookings();
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
     * Calculates the total booking cost for a user and a property based on their respective IDs.
     * If the user or property does not exist, it prints a message indicating their non-existence.
     * @param userId The ID of the user for whom the booking cost is to be calculated.
     * @param propertyId The ID of the property for which the booking cost is to be calculated.
     */
    public static void getBookingCost(int userId, int propertyId) {
        boolean bookingFound = false;
        if (isUserAndPropertyExist(userId, propertyId)) {
            for (User user: users) {
                if (user.getUserId() == userId && user instanceof Customer) {
                    for (Booking booking: ((Customer) user).getBookings()) {
                        if (booking.getProperty().getPropertyId() == propertyId) {
                            double totalCost = booking.totalCost();
                            totalCost -= totalCost * getDiscountPercentageForUser(userId);
                            bookingFound = true;

                            System.out.println("-------------------");
                            System.out.println("Booking Info:");
                            System.out.println(booking);
                            System.out.println("The total cost: " + totalCost);
                            System.out.println("-------------------");
                        }
                    }
                }
            }
        }

        if (!bookingFound) {
            System.out.println("There is no booking");
        }
    }

    /**
     * Get the discount percentage.
     * @param userId The user id.
     * @return The discount percentage
     */
    public static double getDiscountPercentageForUser(int userId) {
        for (User user: users) {
            if (user.getUserId() == userId && user instanceof Customer) {
                return ((Customer) user).discountPercentage();
            }
        }
        return 0;
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
                if (user.getUserId() == userId && user instanceof Customer customer) {
                    Booking booking = new Booking(startDate, endDate, false, getPropertyById(propertyId));
                    customer.getBookings().add(booking);
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
     * Delete the property from the list.
     * @param propertyID The property ID to be deleted.
     */
    public static void deleteProperty(int propertyID) {
        boolean isPropertyDeleted = false;

        Iterator<Property> iterator = properties.iterator();
        while (iterator.hasNext()) {
            Property property = iterator.next();
            if (property.getPropertyId() == propertyID) {
                iterator.remove(); // Safe removal
                isPropertyDeleted = true;
            }
        }

        if (isPropertyDeleted) {
            System.out.println("Property has been deleted successfully.");
        } else {
            System.out.println("Property with ID: " + propertyID + " not found.");
        }
    }

    /**
     * Delete the user from the list.
     * @param userID The user ID to be deleted.
     */
    public static void deleteUser(int userID) {
        boolean isUserDeleted = false;

        Iterator<User> iterator = users.iterator();
        while (iterator.hasNext()) {
            User user = iterator.next();
            if (user.getUserId() == userID) {
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

    /**
     * Add a property to the list.
     */
    public static void addProperty() {
        Scanner scanner = new Scanner(System.in);

        int typeOfProperty;
        do {
            System.out.println("What type of property do you want to add?");
            System.out.println("1) Shared Property\n2) Full Property");
            System.out.print("Enter your choice: ");
            typeOfProperty = scanner.nextInt();
            scanner.nextLine();

            if (typeOfProperty > 2 || typeOfProperty < 1) {
                System.out.println("Please enter a valid property type");
            }
        } while (!((0 < typeOfProperty) && (typeOfProperty < 3)));

        System.out.print("Please enter the number of bedrooms: ");
        int noBedrooms = scanner.nextInt();
        System.out.print("Please enter the number of rooms: ");
        int noRooms = scanner.nextInt();

        // Consume the newline character
        scanner.nextLine();

        System.out.print("Please enter the city: ");
        String city = scanner.nextLine();
        System.out.print("Please enter the price per day: ");
        double pricePerDay = scanner.nextDouble();

        Host host = new Host();
        int hostId;
        do {
            System.out.print("Please enter the host ID: ");
            hostId = scanner.nextInt();
            scanner.nextLine();

            if (!isUserAvailable(hostId)) {
                System.out.println("The host doesn't exist, please enter a valid host ID");
            } else {
                host = getHost(hostId);
            }
        } while (!isUserAvailable(hostId));


        switch (typeOfProperty) {
            case 1:
                registeredProperties++;
                SharedProperty sharedProperty = new SharedProperty(registeredProperties, noBedrooms, noRooms, city, pricePerDay, host);
                properties.add(sharedProperty);
                break;
            case 2:
                registeredProperties++;
                System.out.print("Enter the property size: ");
                double propertySize = scanner.nextDouble();
                FullProperty fullProperty = new FullProperty(registeredProperties, noBedrooms, noRooms, city, pricePerDay, propertySize, host);
                properties.add(fullProperty);
                break;
        }

        System.out.println("Property has been successfully added.");
    }

    /**
     * Get the host.
     * @param hostID The host ID.
     * @return The host.
     */
    public static Host getHost(int hostID) {
        for (User host: users) {
            if (host.getUserId() == hostID && host.getClass() == Host.class) {
                return (Host) host;
            }
        }

        return new Host();
    }

    /**
     * Check if the host is in the users list.
     * @param userID The user ID to be checked.
     * @return True if the user exists, otherwise false.
     */
    public static boolean isUserAvailable(int userID) {
        for (User host: users) {
            if (host.getUserId() == userID && host.getClass() == Host.class) {
                return true;
            }
        }
        return false;
    }

    /**
     * Add a user to the users list.
     */
    public static void addUser() {
        Scanner scanner = new Scanner(System.in);

        int typeOfUser;
        do {
            System.out.println("What type of user do you want to add?");
            System.out.println("1) Gold Customer\n2) Standard Customer\n3) Host");
            System.out.print("Enter your choice: ");
            typeOfUser = scanner.nextInt();
            scanner.nextLine();

            if (typeOfUser > 3 || typeOfUser < 1) {
                System.out.println("Please enter a valid type");
            }
        } while (!((0 < typeOfUser) && (typeOfUser < 4)));

        // Parse the date
        System.out.print("Enter the date of birth (dd/mm/yyyy): ");
        String userInput = scanner.nextLine();
        Date dateOfBirth = parseDate(userInput);

        System.out.print("Enter the first name: ");
        String firstName = scanner.nextLine();

        System.out.print("Enter the last name: ");
        String lastName = scanner.nextLine();

        System.out.print("Enter the registration date (dd/mm/yyyy): ");
        userInput = scanner.nextLine();
        Date registrationDate = parseDate(userInput);

        String preferredPaymentMethod;

        switch (typeOfUser) {
            case 1:
                System.out.print("Enter the preferred payment method: ");
                preferredPaymentMethod = scanner.nextLine();
                int goldLevel;
                do {
                    System.out.print("Enter the gold level (1-3):");
                    goldLevel = scanner.nextInt();
                    scanner.nextLine();
                    if (goldLevel > 3 || goldLevel < 1) {
                        System.out.println("Please enter a valid gold level");
                    }
                } while (!((0 < goldLevel) && (goldLevel < 4)));
                registeredUsers++;
                Gold goldUser = new Gold(registeredUsers, dateOfBirth, firstName, lastName, registrationDate, preferredPaymentMethod, goldLevel);
                users.add(goldUser);
                break;
            case 2:
                System.out.print("Enter the preferred payment method: ");
                preferredPaymentMethod = scanner.nextLine();
                registeredUsers++;
                Standard standardUser = new Standard(registeredUsers, dateOfBirth, firstName, lastName, registrationDate, preferredPaymentMethod);
                users.add(standardUser);
                break;
            case 3:
                System.out.print("Enter the tax number: ");
                double taxNumber = scanner.nextDouble();
                scanner.nextLine();
                registeredUsers++;
                Host host = new Host(registeredUsers, dateOfBirth, firstName, lastName, registrationDate, taxNumber);
                users.add(host);
                break;
        }

        System.out.println("\nUser has been successfully added.");
    }

    /**
     * Get the property details, and print it.
     * @param propertyID The property ID.
     */
    public static void getPropertyDetails(int propertyID) {
        boolean propertyFound = false;
        for (Property property: properties) {
            if (property.getPropertyId() == propertyID) {
                propertyFound = true;
                System.out.println(property);
            }
        }

        if (!propertyFound) {
            System.out.println("User with ID " + propertyID + " not found.");
        }
    }

    /**
     * List the properties with details.
     */
    public static void listProperties() {
        for (Property property: properties) {
            getPropertyDetails(property.getPropertyId());
        }
    }

    /**
     * Get the user details, and print it.
     * @param userID The user ID.
     */
    public static void getUserDetails(int userID) {
        boolean userFound = false;
        for (User user: users) {
            if (user.getUserId() == userID) {
                userFound = true;
                System.out.println(user);
            }
        }

        if (!userFound) {
            System.out.println("User with ID " + userID + " not found.");
        }
    }

    /**
     * List the users with details.
     */
    public static void listUsers() {
        for (User user: users) {
            getUserDetails(user.getUserId());
        }
    }

    /**
     * Displays the menu.
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
        System.out.println("10. Add Inspection");
        System.out.println("11. List users");
        System.out.println("12. List properties");
        System.out.println("13. Compare properties by price per day");
        System.out.println("14. Exit");
        System.out.println("----------------------------------");
        System.out.print("Please select your choice: ");
    }

    public static void exit() {
        System.exit(0);
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
     * Default constructor.
     */
    public BASIC() {
    }
}
