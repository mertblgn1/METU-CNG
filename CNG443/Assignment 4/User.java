import java.io.Serializable;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * An abstract class representing a user with basic information such as user ID, date of birth, first name,
 * last name, and registration date.
 *
 * This class provides constructors for creating instances with different sets of information and getter and
 * setter methods for accessing and modifying the user's attributes.
 *
 * @author Mert Can Bilgin
 * @version 1.0
 */
public abstract class User implements Serializable {
    private int userId;
    private Date dateOfBirth;
    private String firstName;
    private String lastName;
    private Date registrationDate;

    /**
     * Default constructor
     */
    public User() {}

    /**
     * Construct a user with the specified user ID, first name, last name, registration date and date of birth.
     * @param userId The user ID.
     * @param dateOfBirth The date of birth of the User.
     * @param firstName The first name of the user.
     * @param lastName The last name of the user.
     * @param registrationDate The registration date of the user.
     */
    public User(int userId, Date dateOfBirth, String firstName, String lastName, Date registrationDate) {
        this.userId = userId;
        this.dateOfBirth = dateOfBirth;
        this.firstName = firstName;
        this.lastName = lastName;
        this.registrationDate = registrationDate;
    }

    /**
     * Construct a user with the specified user ID, first name and last name.
     * @param userId The user ID.
     * @param firstName The first name of the user.
     * @param lastName The last name of the user.
     */
    public User(int userId, String firstName, String lastName) {
        this.userId = userId;
        this.firstName = firstName;
        this.lastName = lastName;
    }

    /**
     * Return user ID.
     * @return The user ID.
     */
    public int getUserId() {
        return userId;
    }

    /**
     * Return the date of birth of the User.
     * @return The date of birth of the User.
     */
    public Date getDateOfBirth() {
        return dateOfBirth;
    }

    /**
     * Get the first name of the user.
     * @return The first name of the user.
     */
    public String getFirstName() {
        return firstName;
    }

    /**
     * Get the last name of the user.
     * @return The last name of the user.
     */
    public String getLastName() {
        return lastName;
    }

    /**
     * Get the registration date of the user.
     * @return The registration date.
     */
    public Date getRegistrationDate() {
        return registrationDate;
    }

    /**
     * Set the user ID.
     * @param userId The new user ID to be set.
     */
    public void setUserId(int userId) {
        this.userId = userId;
    }

    /**
     * Set the date of birth.
     * @param dateOfBirth The new date of birth to be set.
     */
    public void setDateOfBirth(Date dateOfBirth) {
        this.dateOfBirth = dateOfBirth;
    }

    /**
     * Set the first name of the user.
     * @param firstName The new first name to be set.
     */
    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    /**
     * Set the last name of the user.
     * @param lastName The new last name to be set.
     */
    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    /**
     * Set the registration date of the user.
     * @param registrationDate The new registration date to be set.
     */
    public void setRegistrationDate(Date registrationDate) {
        this.registrationDate = registrationDate;
    }

    /**
     * Print the user
     * @return The template string of the user.
     */
    @Override
    public String toString() {
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
        String formattedBirthday = dateFormat.format(dateOfBirth);
        String formattedRegistrationDate = dateFormat.format(registrationDate);
        return "\n--------User Info---------" +
                "\nUser ID: " + userId +
                "\nBirthday: " + formattedBirthday +
                "\nFirst name: " + firstName +
                "\nLast name: " + lastName +
                "\nRegistration date: " + formattedRegistrationDate +
                "\n-------------------------\n";
    }
}
