import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Represents a Gold-level customer, extending the Customer class.
 *
 * This class includes additional information about the gold level of the customer. It provides constructors for
 * creating Gold customers with different sets of information and getter and setter methods for accessing and modifying
 * the gold level details.
 *
 * @author Mert Can Bilgin
 * @version 1.0
 * @see Customer
 */
public class Gold extends Customer {
    private int goldLevel;

    /**
     * Constructor with the specified user ID, date of birth, first name, last name,
     * registration date, preferred payment method and gold level.
     * @param userId User ID.
     * @param dateOfBirth Date of birth.
     * @param firstName First name.
     * @param lastName Last name.
     * @param registrationDate Registration date.
     * @param preferredPaymentMethod Preferred payment method.
     * @param goldLevel Gold level.
     */
    public Gold(int userId, Date dateOfBirth, String firstName, String lastName, Date registrationDate, String preferredPaymentMethod, int goldLevel) {
        super(userId, dateOfBirth, firstName, lastName, registrationDate, preferredPaymentMethod);
        this.goldLevel = goldLevel;
    }

    /**
     * Default constructor.
     */
    public Gold() {}

    /**
     * Constructor with the specified gold level.
     * @param goldLevel The gold level.
     */
    public Gold(int goldLevel) {
        this.goldLevel = goldLevel;
    }

    /**
     * Constructor with the specified user ID, first name, last name,
     * preferred payment method and gold level.
     * @param userId User ID.
     * @param firstName First name.
     * @param lastName Last name.
     * @param preferredPaymentMethod Preferred payment method.
     * @param goldLevel Gold level.
     */
    public Gold(int userId, String firstName, String lastName, String preferredPaymentMethod, int goldLevel) {
        super(userId, firstName, lastName, preferredPaymentMethod);
        this.goldLevel = goldLevel;
    }

    /**
     * Get the gold level.
     * @return The gold level.
     */
    public int getGoldLevel() {
        return goldLevel;
    }

    /**
     * Set the gold level.
     * @param goldLevel The new gold level to be set.
     */
    public void setGoldLevel(int goldLevel) {
        this.goldLevel = goldLevel;
    }

    /**
     * The discount percentage according to the gold level of the user.
     * @return The discount percentage.
     */
    @Override
    public double discountPercentage() {
        return goldLevel * 0.01;
    }

    /**
     * Print the Gold class customer.
     * @return The template string of Gold customer.
     */
    @Override
    public String toString() {
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
        String formattedBirthday = dateFormat.format(super.getDateOfBirth());
        String formattedRegistrationDate = dateFormat.format(super.getRegistrationDate());
        return "\n--------User Info---------" +
                "\nUser ID: " + super.getUserId() +
                "\nBirthday: " + formattedBirthday +
                "\nFirst name: " + super.getFirstName() +
                "\nLast name: " + super.getLastName() +
                "\nRegistration date: " + formattedRegistrationDate +
                "\nPreferred payment method: " + super.getPreferredPaymentMethod() +
                "\nType: Gold" +
                "\nGold level: " + goldLevel +
                "\n-------------------------\n";
    }
}
