import javax.swing.*;
import java.io.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.DateTimeException;
import java.time.LocalDate;
import java.time.ZoneId;
import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;

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
     * Start a thread to check for modifications in serialized User objects during startup.
     */
    private static void checkForModifications() {
        new Thread(() -> {
            try {
                String storedMD5 = readMD5FromFile("md5.txt");
                String regeneratedMD5 = generateMD5("users.ser");

                if (!storedMD5.equals(regeneratedMD5)) {
                    // Warn the user about modifications
                    MainMenu.showModificationWarningDialog();
                }
            } catch (NoSuchAlgorithmException | IOException e) {
                e.printStackTrace();
            }
        }).start();
    }

    private static String readMD5FromFile(String filePath) throws IOException {
        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            return reader.readLine();
        }
    }

    /**
     * Add a shutdown hook to store data to the database when the application is closed.
     */
    private static void addShutdownHook() {
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            DataStorage.storeUsers(users);
            DataStorage.storeProperties(properties);

            // Serialize User objects
            serializeUsers();
        }));
    }

    private static void serializeUsers() {
        try (ObjectOutputStream objectOutputStream = new ObjectOutputStream(new FileOutputStream("users.ser"))) {
            objectOutputStream.writeObject(users);

            // Generate MD5 hash for serialized data
            String md5 = generateMD5("users.ser");
            writeMD5ToFile(md5);
        } catch (IOException | NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }

    private static String generateMD5(String filePath) throws NoSuchAlgorithmException, IOException {
        MessageDigest md = MessageDigest.getInstance("MD5");
        try (InputStream is = new FileInputStream(filePath)) {
            byte[] buffer = new byte[8192];
            int read;
            while ((read = is.read(buffer)) > 0) {
                md.update(buffer, 0, read);
            }
        }
        byte[] md5sum = md.digest();
        return bytesToHex(md5sum);
    }

    private static void writeMD5ToFile(String md5) {
        try (PrintWriter writer = new PrintWriter("md5.txt")) {
            writer.println(md5);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    private static String bytesToHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    /**
     * Perform the operations, and manage the system.
     * @param args The arguments.
     */
    public static void main(String[] args) {
        users.addAll(DataStorage.loadUsers());
        properties.addAll(DataStorage.loadProperties());
        registeredUsers = users.size();
        registeredProperties = properties.size();

        // Add the shutdown hook
        addShutdownHook();

        // Check for modifications during startup
        checkForModifications();

        SwingUtilities.invokeLater(() -> {
            BASIC basic = new BASIC();
            basic.showMainMenu();
        });
    }

    /**
     * Create and show the main GUI
     */
    private void showMainMenu() {
        SwingUtilities.invokeLater(() -> {
            MainMenu mainMenu = new MainMenu();
        });
    }

    /**
     * Compare the properties' prices per day
     * @param propertyId1 First property ID to be compared
     * @param propertyId2 Second property ID to be compared
     * @return Cheaper one
     */
    public static int comparePropertyPricesPerDay(int propertyId1, int propertyId2) {
        try {
            if (getPropertyById(propertyId1).compareTo(getPropertyById(propertyId2)) == 1) {
                return 2;
            } else if (getPropertyById(propertyId1).compareTo(getPropertyById(propertyId2)) == -1) {
                return 1;
            } else {
                return 0;
            }
        } catch (NullPointerException e) {
            System.out.println(e.getMessage());
        }
        return -1;
    }

    /**
     * Add an inspection to the property.
     * @param propertyId The property ID.
     * @param inspectionText The inspection text.
     */
    public static boolean addInspectionToProperty(int propertyId, String inspectionText) {
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
                        // Update data files
                        if (property instanceof FullProperty) {
                            FullPropertyIO.writeToFile(properties);
                        } else if (property instanceof SharedProperty) {
                            SharedPropertyIO.writeToFile(properties);
                        }
                    } catch (NullPointerException e) {
                        System.out.println(e.getMessage());
                    }
                }
            }
        }
        return propertyFound;
    }

    /**
     * Displays the booking details for a user with the specified user ID.
     * If the user has no bookings, it prints a message indicating that there are no bookings.
     * @param userId The ID of the user for whom booking details are to be displayed.
     * @return Bookings of the user.
     */
    public static ArrayList<Booking> getUserBooking(int userId) {
        for (User user: users) {
            if (user.getUserId() == userId && user instanceof Customer customer) {
                if (customer.getBookings().isEmpty()) {
                    System.out.println("The user has no bookings.");
                } else {
                    ArrayList<Booking> bookings;
                    bookings = customer.getBookings();
                    return bookings;
                }
            }
        }

        return null;
    }

    /**
     * Calculates the total booking cost for a user and a property based on their respective IDs.
     * If the user or property does not exist, it prints a message indicating their non-existence.
     * @param userId The ID of the user for whom the booking cost is to be calculated.
     * @param propertyId The ID of the property for which the booking cost is to be calculated.
     */
    public static double getBookingCost(int userId, int propertyId) {
        if (isUserAndPropertyExist(userId, propertyId)) {
            for (User user: users) {
                if (user.getUserId() == userId && user instanceof Customer) {
                    for (Booking booking: ((Customer) user).getBookings()) {
                        if (booking.getProperty().getPropertyId() == propertyId) {
                            double totalCost = booking.totalCost();
                            totalCost -= totalCost * getDiscountPercentageForUser(userId);
                            return totalCost;
                        }
                    }
                }
            }
        }

        return -1;
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
     * @return If booking is added
     */
    public static boolean addBooking(int userId, int propertyId, String startDateStr, String endDateStr) {
        if (isUserAndPropertyExist(userId, propertyId)) {
            // Parse dates
            Date startDate = parseDate(startDateStr);
            Date endDate = parseDate(endDateStr);

            for (User user: users) {
                if (user.getUserId() == userId && user instanceof Customer customer) {
                    Booking booking = new Booking(startDate, endDate, false, getPropertyById(propertyId));
                    customer.getBookings().add(booking);
                    break;
                }
            }
            return true;
        } else {
            return false;
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
     * @return If property is deleted.
     */
    public static boolean deleteProperty(int propertyID) {
        boolean isPropertyDeleted = false;

        Iterator<Property> iterator = properties.iterator();
        while (iterator.hasNext()) {
            Property property = iterator.next();
            if (property.getPropertyId() == propertyID) {
                iterator.remove(); // Safe removal
                isPropertyDeleted = true;

                // Update files
                if (property instanceof SharedProperty) {
                    SharedPropertyIO.writeToFile(properties);
                } else if (property instanceof FullProperty) {
                    FullPropertyIO.writeToFile(properties);
                }
            }
        }

        return isPropertyDeleted;
    }

    /**
     * Delete the user from the list.
     * @param userID The user ID to be deleted.
     * @return if the user is deleted
     */
    public static boolean deleteUser(int userID) {
        boolean isUserDeleted = false;

        Iterator<User> iterator = users.iterator();
        while (iterator.hasNext()) {
            User user = iterator.next();
            if (user.getUserId() == userID) {
                iterator.remove(); // Safe removal
                isUserDeleted = true;

                // Update files
                if (user instanceof Gold) {
                    GoldIO.writeToFile(users);
                } else if (user instanceof Standard) {
                    StandardIO.writeToFile(users);
                } else if (user instanceof Host) {
                    HostIO.writeToFile(users);
                }
            }
        }

        return isUserDeleted;
    }

    /**
     * Add a full property
     * @param noBedrooms Number of bedrooms
     * @param noRooms Number of rooms
     * @param city City
     * @param pricePerDay Price per day
     * @param hostId Host id
     * @param propertySize Property size
     * @return
     */
    public static boolean addProperty(int noBedrooms, int noRooms, String city, double pricePerDay, int hostId, double propertySize) {
        Host host = new Host();
        if (!isUserAvailable(hostId)) {
            return false;
        } else {
            host = getHost(hostId);
        }

        registeredProperties++;
        FullProperty fullProperty = new FullProperty(registeredProperties, noBedrooms, noRooms, city, pricePerDay, propertySize, host);
        properties.add(fullProperty);

        // Update files
        FullPropertyIO.writeToFile(properties);
        return true;
    }

    /**
     * Add a shared property.
     * @param noBedrooms Number of bedrooms
     * @param noRooms Number of rooms
     * @param city City
     * @param pricePerDay Price per day
     * @param hostId Host id
     * @return if it returns false
     */
    public static boolean addProperty(int noBedrooms, int noRooms, String city, double pricePerDay, int hostId) {
        Host host = new Host();
        if (!isUserAvailable(hostId)) {
            return false;
        } else {
            host = getHost(hostId);
        }

        registeredProperties++;
        SharedProperty sharedProperty = new SharedProperty(registeredProperties, noBedrooms, noRooms, city, pricePerDay, host);
        properties.add(sharedProperty);

        // Update file
        SharedPropertyIO.writeToFile(properties);

        return true;
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
     * Add a Host to the users list. If parsing error happens, return false.
     * @param dob Date of birth
     * @param firstName First name
     * @param lastName Last name
     * @param regDate Registration date
     * @param taxNumber Tax number
     */
    public static boolean addUser(String dob, String firstName, String lastName, String regDate, double taxNumber) {
        // Parse the dates
        Date dateOfBirth = parseDate(dob);
        Date registrationDate = parseDate(regDate);

        if (dateOfBirth == null || registrationDate == null) {
            return false;
        }

        registeredUsers++;
        Host host = new Host(registeredUsers, dateOfBirth, firstName, lastName, registrationDate, taxNumber);
        users.add(host);

        // Update file
        HostIO.writeToFile(users);

        return true;
    }

    /**
     * Add a Gold user to the list. If parsing error happens, return false.
     * @param dob Date of birth
     * @param firstName First name
     * @param lastName Last name
     * @param regDate Registration date
     * @param preferredPaymentMethod Preferred payment method
     * @param goldLevel Gold level
     */
    public static boolean addUser(String dob, String firstName, String lastName, String regDate, String preferredPaymentMethod, int goldLevel) {
        // Parse the dates
        Date dateOfBirth = parseDate(dob);
        Date registrationDate = parseDate(regDate);

        if (dateOfBirth == null || registrationDate == null) {
            return false;
        }

        registeredUsers++;
        Gold goldUser = new Gold(registeredUsers, dateOfBirth, firstName, lastName, registrationDate, preferredPaymentMethod, goldLevel);
        users.add(goldUser);

        // Update file
        GoldIO.writeToFile(users);

        return true;
    }

    /**
     * Add standard user to the list.  If parsing error happens, return false.
     * @param dob Date of birth
     * @param firstName First name
     * @param lastName Last name
     * @param regDate Registration date
     * @param preferredPaymentMethod Preferred payment method
     */
    public static boolean addUser(String dob, String firstName, String lastName, String regDate, String preferredPaymentMethod) {
        // Parse the dates
        Date dateOfBirth = parseDate(dob);
        Date registrationDate = parseDate(regDate);

        if (dateOfBirth == null || registrationDate == null) {
            return false;
        }

        registeredUsers++;
        Standard standardUser = new Standard(registeredUsers, dateOfBirth, firstName, lastName, registrationDate, preferredPaymentMethod);
        users.add(standardUser);

        // Update file
        StandardIO.writeToFile(users);

        return true;
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
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
        Date date = null;

        try {
            date = dateFormat.parse(userDate);
            if (!userDate.equals(dateFormat.format(date))) {
                date = null;
            }
        } catch (ParseException e) {
            System.out.print("Invalid date format. Please use dd/mm/yyyy. Please try again: ");
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
