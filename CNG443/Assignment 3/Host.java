import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Represents a host, extending the base User class.
 *
 * This class includes additional information about the host's tax number. It provides constructors for creating hosts
 * with different sets of information and getter and setter methods for accessing and modifying the host details.
 *
 * @author Mert Can Bilgin
 * @version 1.0
 * @see User
 */
public class Host extends User {
    private double taxNumber;

    /**
     * Default constructor.
     */
    public Host() {
    }

    /**
     * Constructor with the specified tax number.
     * @param taxNumber Tax number of Host.
     */
    public Host(double taxNumber) {
        this.taxNumber = taxNumber;
    }

    /**
     * Constructor with the specified user ID, date of birth, first name,
     * last name, registration date and tax number.
     * @param userId The user ID.
     * @param dateOfBirth The date of birth.
     * @param firstName The first name.
     * @param lastName The last name.
     * @param registrationDate The registration date.
     * @param taxNumber The tax number.
     */
    public Host(int userId, Date dateOfBirth, String firstName, String lastName, Date registrationDate, double taxNumber) {
        super(userId, dateOfBirth, firstName, lastName, registrationDate);
        this.taxNumber = taxNumber;
    }

    /**
     * Constructor with the specified user ID, first name,
     * last name, and tax number.
     * @param userId The user ID.
     * @param firstName The first name.
     * @param lastName The last name.
     * @param taxNumber The tax number.
     */
    public Host(int userId, String firstName, String lastName, double taxNumber) {
        super(userId, firstName, lastName);
        this.taxNumber = taxNumber;
    }

    /**
     * Get the tax number.
     * @return Tax number.
     */
    public double getTaxNumber() {
        return taxNumber;
    }

    /**
     * Set the tax number.
     * @param taxNumber The new tax number to be set.
     */
    public void setTaxNumber(double taxNumber) {
        this.taxNumber = taxNumber;
    }

    /**
     * Print the host
     * @return The template string of host.
     */
    @Override
    public String toString() {
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
        String formattedBirthday = dateFormat.format(super.getDateOfBirth());
        String formattedRegistrationDate = dateFormat.format(super.getRegistrationDate());
        return "\n--------Host Info---------" +
                "\nUser ID: " + super.getUserId() +
                "\nBirthday: " + formattedBirthday +
                "\nFirst name: " + super.getFirstName() +
                "\nLast name: " + super.getLastName() +
                "\nRegistration date: " + formattedRegistrationDate +
                "\nType: Host" +
                "\nTax number: " + taxNumber +
                "\n-------------------------\n";
    }
}
