import java.sql.*;
import java.util.ArrayList;
import java.util.Date;

public class DataStorage {
    // JDBC connection parameters
    private static final String JDBC_URL = "jdbc:mysql://localhost:3306/BasicDB";
    private static final String USERNAME = "cng443user";
    private static final String PASSWORD = "1234";

    // Load users from the database
    public static ArrayList<User> loadUsers() {
        ArrayList<User> users = new ArrayList<>();

        try (Connection connection = DriverManager.getConnection(JDBC_URL, USERNAME, PASSWORD);
             PreparedStatement statement = connection.prepareStatement("SELECT * FROM User");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                // Populate user data from result set
                int userID = resultSet.getInt("userID");
                Date dateOfBirth = new Date(resultSet.getDate("dateOfBirth").getTime());
                String firstName = resultSet.getString("firstName");
                String lastName = resultSet.getString("lastName");
                Date registrationDate = new Date(resultSet.getDate("registrationDate").getTime());
                String type = resultSet.getString("type");
                String preferredPaymentMethod = resultSet.getString("preferredPaymentMethod");
                double taxNumber = resultSet.getDouble("taxNumber");
                int goldLevel = resultSet.getInt("goldLevel");

                if (type.equals("h")) {
                    Host host = new Host(userID, dateOfBirth, firstName, lastName, registrationDate, taxNumber);
                    users.add(host);
                } else if (type.equals("g")) {
                    Gold gold = new Gold(userID, dateOfBirth, firstName, lastName, registrationDate, preferredPaymentMethod, goldLevel);
                    users.add(gold);
                } else if (type.equals("s")) {
                    Standard standard = new Standard(userID, dateOfBirth, firstName, lastName, registrationDate, preferredPaymentMethod);
                    users.add(standard);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return users;
    }

    public static ArrayList<Property> loadProperties() {
        ArrayList<Property> properties = new ArrayList<>();

        try (Connection connection = DriverManager.getConnection(JDBC_URL, USERNAME, PASSWORD);
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM Property");
            ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                // Populate property data from result set
                int propertyID = resultSet.getInt("propertyID");
                int noBedRooms = resultSet.getInt("noBedRooms");
                int noRooms = resultSet.getInt("noRooms");
                String city = resultSet.getString("city");
                double pricePerDay = resultSet.getDouble("pricePerDay");
                String type = resultSet.getString("type");

                if (type.equals("f")) {
                    double propertySize = resultSet.getDouble("propertySize");
                    FullProperty fullProperty = new FullProperty(propertyID, noBedRooms, noRooms, city, pricePerDay, propertySize);
                    properties.add(fullProperty);
                } else {
                    SharedProperty sharedProperty = new SharedProperty(propertyID, noBedRooms, noRooms, city, pricePerDay);
                    properties.add(sharedProperty);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return properties;
    }

    // Store users to the database
    public static void storeUsers(ArrayList<User> users) {
        try (Connection connection = DriverManager.getConnection(JDBC_URL, USERNAME, PASSWORD);
             PreparedStatement deleteStatement = connection.prepareStatement("DELETE FROM User");
             PreparedStatement statement = connection.prepareStatement("INSERT INTO User VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)")) {

            // Delete existing data
            deleteStatement.executeUpdate();

            for (User user: users) {
                // Set parameters for the statement
                statement.setInt(1, user.getUserId());
                statement.setDate(2, new java.sql.Date(user.getDateOfBirth().getTime()));
                statement.setString(3, user.getFirstName());
                statement.setString(4, user.getLastName());
                statement.setDate(5, new java.sql.Date(user.getRegistrationDate().getTime()));

                String type = "";
                // Set values according to type
                if (user instanceof Gold) {
                    type = "g";
                    statement.setString(6, type);
                    statement.setString(7, ((Gold) user).getPreferredPaymentMethod());
                    statement.setNull(8, java.sql.Types.DOUBLE);
                    statement.setInt(9, ((Gold) user).getGoldLevel());
                } else if (user instanceof Standard) {
                    type = "s";
                    statement.setString(6, type);
                    statement.setString(7, ((Standard) user).getPreferredPaymentMethod());
                    statement.setNull(8, java.sql.Types.DOUBLE);
                    statement.setNull(9, Types.INTEGER);
                } else if (user instanceof Host) {
                    type = "h";
                    statement.setString(6, type);
                    statement.setNull(7, Types.VARCHAR);
                    statement.setDouble(8, ((Host) user).getTaxNumber());
                    statement.setNull(9, Types.INTEGER);
                }

                statement.addBatch();
            }

            // Execute batch update
            statement.executeBatch();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    // Store properties to the database
    public static void storeProperties(ArrayList<Property> properties) {
        try (Connection connection = DriverManager.getConnection(JDBC_URL, USERNAME, PASSWORD);
             PreparedStatement deleteStatement = connection.prepareStatement("DELETE FROM Property");
             PreparedStatement statement = connection.prepareStatement("INSERT INTO Property VALUES (?, ?, ?, ?, ?, ?, ?)")) {

            // Delete existing data
            deleteStatement.executeUpdate();

            for (Property property: properties) {
                // Set parameters for the statement
                statement.setInt(1, property.getPropertyId());
                statement.setInt(2, property.getNoBedRooms());
                statement.setInt(3, property.getNoRooms());
                statement.setString(4, property.getCity());
                statement.setDouble(5, property.getPricePerDay());

                if (property instanceof FullProperty) {
                    statement.setString(6, "f");
                    statement.setDouble(7, ((FullProperty) property).getPropertySize());
                } else if (property instanceof SharedProperty) {
                    statement.setString(6, "s");
                    statement.setNull(7, Types.DOUBLE);
                }

                statement.addBatch();
            }

            // Execute batch update
            statement.executeBatch();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
